package pariesz.pov;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;

import androidx.annotation.NonNull;
import androidx.fragment.app.Fragment;
import androidx.recyclerview.widget.DividerItemDecoration;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

public class BluetoothFragment extends Fragment {
    private static final String TAG = "BluetoothFragment";

    private Button discoverButton;
    private RecyclerView recyclerView;
    private BluetoothRecyclerViewAdaptor recyclerAdaptor;
    private BluetoothAdapter bluetoothAdapter;
    private OnDeviceClickListener onDeviceClickListener;

    public interface OnDeviceClickListener {
        void onDeviceClick(BluetoothFragment dialog, BluetoothDevice device);
    }

    public void setOnDeviceClickListener(OnDeviceClickListener value) {
        this.onDeviceClickListener = value;
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        return inflater.inflate(R.layout.fragment_bluetooth, container, false);
    }

    @Override
    public void onViewCreated(@NonNull View view, Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);

        // Create the builder and pass the context 'getActivity()'
        getActivity().registerReceiver(actionFoundReceiver, new IntentFilter(BluetoothDevice.ACTION_FOUND));

        IntentFilter discoveryFilter = new IntentFilter();
        discoveryFilter.addAction(BluetoothAdapter.ACTION_DISCOVERY_FINISHED);
        discoveryFilter.addAction(BluetoothAdapter.ACTION_DISCOVERY_STARTED);
        getActivity().registerReceiver(discoveryReceiver, discoveryFilter);

        bluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
        discoverButton = view.findViewById(R.id.button_bluetoothDialog_discover);
        discoverButton.setOnClickListener(discoverClickListener);

        recyclerAdaptor = new BluetoothRecyclerViewAdaptor(onRecyclerViewDeviceClickListener);
        recyclerView = view.findViewById(R.id.recyclerView_bluetoothDialog);
        recyclerView.addItemDecoration(new DividerItemDecoration(recyclerView.getContext(), DividerItemDecoration.VERTICAL));
        recyclerView.setAdapter(recyclerAdaptor);
        recyclerView.setLayoutManager(new LinearLayoutManager(this.getContext()));

        bluetoothAdapter.getBondedDevices();

        bluetoothAdapter.startDiscovery();
    }

    @Override
    public void onDestroy() {
        Log.d(TAG, "onDestroy");
        bluetoothAdapter.cancelDiscovery();
        getContext().unregisterReceiver(actionFoundReceiver);
        getContext().unregisterReceiver(discoveryReceiver);
        super.onDestroy();
    }

    private BluetoothRecyclerViewAdaptor.OnItemClickListener onRecyclerViewDeviceClickListener = new BluetoothRecyclerViewAdaptor.OnItemClickListener() {

        @Override
        public void onItemClick(BluetoothRecyclerViewAdaptor.ViewHolder viewHolder) {
            Log.d(TAG, "onDeviceClickListener.onClick");

            if(onDeviceClickListener != null) {
                onDeviceClickListener.onDeviceClick(BluetoothFragment.this, viewHolder.getDevice());
            }
        }
    };

    private View.OnClickListener discoverClickListener = new View.OnClickListener() {

        @Override
        public void onClick(View v) {
            Log.d(TAG, "discoverClickListener.onClick");
            bluetoothAdapter.startDiscovery();
        }
    };

    private BroadcastReceiver actionFoundReceiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
            Log.d(TAG, "actionFoundReceiver.onReceive");
            BluetoothDevice device = intent.getParcelableExtra(BluetoothDevice.EXTRA_DEVICE);
            recyclerAdaptor.addDevice(device);
        }
    };

    private BroadcastReceiver discoveryReceiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
            Log.d(TAG, "discoveryReceiver.onReceive");
            boolean discovering = bluetoothAdapter.isDiscovering();
            discoverButton.setText(discovering ? "Discovering..." : "Discover");
            discoverButton.setAlpha(discovering ? 0.3F : 1F);
            discoverButton.setClickable(!discovering);
        }
    };
}