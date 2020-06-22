package pariesz.pov;

import android.app.Activity;
import android.bluetooth.*;
import android.os.Bundle;
import android.view.*;
import android.widget.Button;

import androidx.annotation.NonNull;
import androidx.fragment.app.Fragment;
import androidx.recyclerview.widget.*;

public class BluetoothFragment extends Fragment {
    private static final String TAG = "BluetoothFragment";

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
    }

    private BluetoothRecyclerViewAdaptor.OnItemClickListener onRecyclerViewDeviceClickListener = new BluetoothRecyclerViewAdaptor.OnItemClickListener() {

        @Override
        public void onItemClick(BluetoothRecyclerViewAdaptor.ViewHolder viewHolder) {
            if (onDeviceSelectedListener != null) {
                onDeviceSelectedListener.onDeviceSelected(viewHolder.getDevice());
            }
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
}