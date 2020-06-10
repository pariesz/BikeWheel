package pariesz.pov;

import android.bluetooth.BluetoothDevice;
import android.content.Context;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.RelativeLayout;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import java.util.ArrayList;

public class BluetoothRecyclerViewAdaptor extends RecyclerView.Adapter<BluetoothRecyclerViewAdaptor.ViewHolder> {
    private static final String TAG = "BluetoothRecyclerViewAdaptor";
    private ArrayList<BluetoothDevice> devices = new ArrayList<>();
    private final OnItemClickListener listener;
    private String savedAddress;

    public interface OnItemClickListener {
        void onItemClick(ViewHolder view);
    }

    public BluetoothRecyclerViewAdaptor(OnItemClickListener listener, String savedAddress) {
        this.listener = listener;
        this.savedAddress = savedAddress;
    }

    public void addDevice(BluetoothDevice device) {
        Log.d(TAG, "addDevice index:" + devices.size() + ", address:" + device.getAddress());
        devices.add(device);
        notifyItemInserted(devices.size() - 1);
    }

    @NonNull
    @Override
    public ViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        View view = LayoutInflater.from(parent.getContext()).inflate(R.layout.layout_bluetooth_device, parent, false);
        return new ViewHolder(view);
    }

    @Override
    public void onBindViewHolder(@NonNull ViewHolder holder, int position) {
        Log.d(TAG, "onBindViewHolder: called.");
        BluetoothDevice device = devices.get(position);
        holder.setDevice(device, device.getAddress().equals(savedAddress));
    }
    @Override
    public int getItemCount() {
        return devices.size();
    }

    public class ViewHolder extends RecyclerView.ViewHolder {
        private View itemView;
        private BluetoothDevice device;
        private RelativeLayout layout;
        private TextView nameText;
        private TextView addressText;
        private TextView pairedText;
        private TextView savedText;

        public ViewHolder(@NonNull View itemView) {
            super(itemView);
            this.itemView = itemView;

            layout = itemView.findViewById(R.id.layout_bluetoothDevice);
            layout.setOnClickListener(layoutClickListener);

            nameText = itemView.findViewById(R.id.textView_bluetoothDeviceName);
            addressText = itemView.findViewById(R.id.textView_bluetoothDeviceAddress);
            pairedText = itemView.findViewById(R.id.textView_bluetoothDevicePaired);
            savedText = itemView.findViewById(R.id.textView_bluetoothDeviceSaved);
        }

        public BluetoothDevice getDevice() {
            return this.device;
        }

        public Context getContext() {
            return this.itemView.getContext();
        }

        public void setDevice(BluetoothDevice device, boolean saved) {
            this.device = device;

            nameText.setText(device.getName());

            addressText.setText(device.getAddress());

            savedText.setVisibility(saved ? View.VISIBLE : View.INVISIBLE);

            switch(device.getBondState()) {
                case BluetoothDevice.BOND_NONE:
                    pairedText.setText("NONE");
                    pairedText.setVisibility(View.INVISIBLE);
                    break;

                case BluetoothDevice.BOND_BONDING:
                    pairedText.setText("PAIRING");
                    pairedText.setVisibility(View.VISIBLE);
                    break;

                case BluetoothDevice.BOND_BONDED:
                    pairedText.setText("PAIRED");
                    pairedText.setVisibility(View.VISIBLE);
                    break;
            }
        }

        private View.OnClickListener layoutClickListener = new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                listener.onItemClick(ViewHolder.this);
            }
        };
    }
}
