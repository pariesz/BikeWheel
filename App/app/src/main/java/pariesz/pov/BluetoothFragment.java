package pariesz.pov;

import android.Manifest;
import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.Build;
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

// TODO: increase bluetooth bitrate using AT commands
public class BluetoothFragment extends Fragment {
    private static final String TAG = "BluetoothFragment";

    private Button discoverButton;
    private Button mockButton;
    private RecyclerView recyclerView;
    private BluetoothAdapter bluetoothAdapter;
    private BluetoothRecyclerViewAdaptor recyclerAdaptor;
    private OnDeviceSelectedListener onDeviceSelectedListener;
    private OnMockClickListener onMockClickListener;

    public interface OnDeviceSelectedListener {
        void onDeviceSelected(BluetoothDevice device);
    }

    public interface OnMockClickListener {
        void onMockClick();
    }

    public void setOnDeviceSelectedListener(OnDeviceSelectedListener callback) {
        this.onDeviceSelectedListener = callback;
    }

    public void setOnMockClickListener(OnMockClickListener callback) {
        this.onMockClickListener = callback;
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        return inflater.inflate(R.layout.fragment_bluetooth, container, false);
    }

    @Override
    public void onViewCreated(@NonNull View view, Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);

        discoverButton = view.findViewById(R.id.button_bluetooth_discover);
        discoverButton.setOnClickListener(discoverClickListener);

        mockButton = view.findViewById(R.id.button_bluetooth_mock);
        mockButton.setOnClickListener(mockClickListener);

        String savedAddress = getActivity().getSharedPreferences(MainActivity.PREFERENCE_FILE_KEY, Activity.MODE_PRIVATE).getString(MainActivity.PREFERENCE_BT_ADDRESS, null);
        recyclerAdaptor = new BluetoothRecyclerViewAdaptor(onRecyclerViewDeviceClickListener, savedAddress);
        recyclerView = view.findViewById(R.id.recyclerView_bluetooth);
        recyclerView.addItemDecoration(new DividerItemDecoration(recyclerView.getContext(), DividerItemDecoration.VERTICAL));
        recyclerView.setAdapter(recyclerAdaptor);
        recyclerView.setLayoutManager(new LinearLayoutManager(this.getContext()));

        bluetoothAdapter = BluetoothAdapter.getDefaultAdapter();

        for (BluetoothDevice device : bluetoothAdapter.getBondedDevices()) {
            recyclerAdaptor.addDevice(device);
        }

        startDiscovery();

        // Create the builder and pass the context 'getActivity()'
        getContext().registerReceiver(actionFoundReceiver, new IntentFilter(BluetoothDevice.ACTION_FOUND));

        IntentFilter discoveryFilter = new IntentFilter();
        discoveryFilter.addAction(BluetoothAdapter.ACTION_DISCOVERY_FINISHED);
        discoveryFilter.addAction(BluetoothAdapter.ACTION_DISCOVERY_STARTED);
        getContext().registerReceiver(discoveryReceiver, discoveryFilter);
    }

    @Override
    public void onDestroy() {
        // Always cancel discovery because it will slow down connection
        bluetoothAdapter.cancelDiscovery();
        getContext().unregisterReceiver(actionFoundReceiver);
        getContext().unregisterReceiver(discoveryReceiver);
        super.onDestroy();
    }

    private BluetoothRecyclerViewAdaptor.OnItemClickListener onRecyclerViewDeviceClickListener = new BluetoothRecyclerViewAdaptor.OnItemClickListener() {

        @Override
        public void onItemClick(BluetoothRecyclerViewAdaptor.ViewHolder viewHolder) {
            if (onDeviceSelectedListener != null) {
                onDeviceSelectedListener.onDeviceSelected(viewHolder.getDevice());
            }
        }
    };

    private View.OnClickListener discoverClickListener = new View.OnClickListener() {

        @Override
        public void onClick(View v) {
            startDiscovery();
        }
    };

    private View.OnClickListener mockClickListener = new View.OnClickListener() {

        @Override
        public void onClick(View v) {
            if (onMockClickListener != null) {
                onMockClickListener.onMockClick();
            }
        }
    };

    private BroadcastReceiver actionFoundReceiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
            BluetoothDevice device = intent.getParcelableExtra(BluetoothDevice.EXTRA_DEVICE);
            recyclerAdaptor.addDevice(device);
        }
    };

    private BroadcastReceiver discoveryReceiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
            boolean discovering = bluetoothAdapter.isDiscovering();
            discoverButton.setText(discovering ? "Discovering..." : "Discover");
            discoverButton.setAlpha(discovering ? 0.5F : 1F);
            discoverButton.setClickable(!discovering);
        }
    };

    private void startDiscovery() {
        checkBTPermissions();

        if (bluetoothAdapter.isDiscovering()) {
            Log.d(TAG, "Canceling discovery.");
            bluetoothAdapter.cancelDiscovery();
        }

        bluetoothAdapter.startDiscovery();
    }

    /**
     * This method is required for all devices running API23+
     * Android must programmatically check the permissions for bluetooth. Putting the proper permissions
     * in the manifest is not enough.
     * NOTE: This will only execute on versions > LOLLIPOP because it is not needed otherwise.
     */
    private void checkBTPermissions() {
        if (Build.VERSION.SDK_INT > Build.VERSION_CODES.LOLLIPOP) {
            int permissionCheck = getActivity().checkSelfPermission("Manifest.permission.ACCESS_FINE_LOCATION");
            permissionCheck += getActivity().checkSelfPermission("Manifest.permission.ACCESS_COARSE_LOCATION");
            if (permissionCheck != 0) {
                this.requestPermissions(new String[]{Manifest.permission.ACCESS_FINE_LOCATION, Manifest.permission.ACCESS_COARSE_LOCATION}, 1001); //Any number
            }
        } else {
            Log.d(TAG, "checkBTPermissions: No need to check permissions. SDK version < LOLLIPOP.");
        }
    }
}