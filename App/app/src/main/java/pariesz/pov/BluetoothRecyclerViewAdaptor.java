package pariesz.pov;

import android.bluetooth.BluetoothDevice;
import android.content.Context;
import android.graphics.Color;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.RelativeLayout;
import android.widget.TextView;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import java.util.ArrayList;

public class BluetoothRecyclerViewAdaptor extends RecyclerView.Adapter<BluetoothRecyclerViewAdaptor.ViewHolder> {
    private int connectedItem = -1;
    private static final String TAG = "BluetoothRecyclerViewAdaptor";
    private ArrayList<BluetoothDevice> devices = new ArrayList<>();
    private final OnItemClickListener listener;

    public interface OnItemClickListener {
        void onItemClick(ViewHolder view);
    }

    public BluetoothRecyclerViewAdaptor(OnItemClickListener listener) {
        this.listener = listener;
    }

    public void addDevice(BluetoothDevice device) {
        devices.add(device);
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
        holder.setDevice(device);
    }
    @Override
    public int getItemCount() {
        return devices.size();
    }

    public class ViewHolder extends RecyclerView.ViewHolder {
        private View itemView;
        private BluetoothDevice device;
        private RelativeLayout layout;
        private TextView name;
        private TextView address;
        private TextView paired;
        private ImageView status;

        public ViewHolder(@NonNull View itemView) {
            super(itemView);
            this.itemView = itemView;

            layout = itemView.findViewById(R.id.layout_bluetoothDevice);
            layout.setOnClickListener(layoutClickListener);

            name = itemView.findViewById(R.id.textView_bluetoothDeviceName);
            address = itemView.findViewById(R.id.textView_bluetoothDeviceAddress);
            paired = itemView.findViewById(R.id.textView_bluetoothDevicePaired);
            status = itemView.findViewById(R.id.imageView_bluetoothDeviceStatus);

            // TODO: bluetooth status
            status.setImageResource(R.drawable.ic_bluetooth);
        }

        public BluetoothDevice getDevice() {
            return this.device;
        }

        public Context getContext() {
            return this.itemView.getContext();
        }

        public void setDevice(BluetoothDevice device) {
            this.device = device;

            name.setText(device.getName());

            address.setText(device.getAddress());

            switch(device.getBondState()) {
                case BluetoothDevice.BOND_NONE:
                    paired.setText("NONE");
                    paired.setVisibility(View.INVISIBLE);
                    break;

                case BluetoothDevice.BOND_BONDING:
                    paired.setText("PAIRING");
                    paired.setVisibility(View.VISIBLE);
                    break;

                case BluetoothDevice.BOND_BONDED:
                    paired.setText("PAIRED");
                    paired.setVisibility(View.VISIBLE);
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
