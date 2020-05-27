package pariesz.pov;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.Intent;
import android.content.SharedPreferences;
import android.graphics.LightingColorFilter;
import android.os.Build;
import android.os.Bundle;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.Toolbar;
import androidx.core.content.ContextCompat;
import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentManager;
import androidx.fragment.app.FragmentTransaction;

import android.os.Handler;
import android.util.Log;
import android.util.TypedValue;
import android.view.View;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.ProgressBar;
import android.widget.TextView;
import android.widget.Toast;

import java.io.IOException;
import java.text.DecimalFormat;

public class MainActivity extends AppCompatActivity {
    private static final int REQUEST_ENABLE_BT = 1;
    private static final String TAG = "MainActivity";
    private static final String PREFERENCE_FILE_KEY = "pariesz_pov";
    private static final String PREFERENCE_BT_ADDRESS = "BtAddress";
    private static final long BATTERY_INTERVAL = 60 * 1000;
    private static final DecimalFormat BATTERY_FORMAT = new DecimalFormat("0.0");

    private BluetoothAdapter bluetoothAdapter;
    private LinearLayout bluetoothLayout;
    private TextView bluetoothText;
    private ImageView bluetoothImage;

    private Handler batteryHandler = new Handler();
    private TextView batteryText;
    private ImageView batteryImage;
    private ProgressBar batteryProgressBar;

    private ImageView logoImage;

    private WheelService service = new WheelService();
    public WheelService getService() {
        return service;
    }

    private SharedPreferences preferences;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        Log.d(TAG, "onCreate");

        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Toolbar toolbar = findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);
        getSupportActionBar().setDisplayShowTitleEnabled(false);

        batteryProgressBar = findViewById(R.id.progressBar_battery);
        batteryImage = findViewById(R.id.imageView_battery);
        batteryText = findViewById(R.id.textView_battery);
        bluetoothLayout = findViewById(R.id.layout_bluetooth);
        bluetoothText = findViewById(R.id.textView_bluetooth);
        bluetoothImage = findViewById(R.id.imageView_bluetooth);
        bluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
        preferences = getSharedPreferences(PREFERENCE_FILE_KEY, MODE_PRIVATE);

        logoImage = findViewById(R.id.imageView_main_logo);
        logoImage.setOnClickListener(imageViewClickListener);
        service.addOnMessageReceivedListener(onMessageReceivedListener);
        service.addOnStatusChangeListener(onStatusChangeListener);
    }

    @Override
    protected void onStart() {
        Log.d(TAG, "onStart");

        super.onStart();

        // TODO: temp, remove
        if(true) {
            try {
                setService("Mock", new MockSocket());
            } catch (IOException ex) {
            }
            return;
        }

        if (bluetoothAdapter == null) {
            if(Utilities.isProbablyAnEmulator()) {
                // The emulator does not support Bluetooth
                Log.d(TAG, "Mocking bluetooth");

                try {
                    setService("Mock", new MockSocket());
                } catch (IOException ex) {
                    Log.e(TAG,"MockSocket error", ex);
                }

            } else {
                Log.d(TAG, Build.PRODUCT + " does not support bluetooth");
                setBluetoothDisconnected("Not supported");
            }

            return;
        }

        if (!bluetoothAdapter.isEnabled()) {
            setBluetoothSearching("Enabling");
            Intent enableBtIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
            startActivityForResult(enableBtIntent, REQUEST_ENABLE_BT);
            return;
        }

        onBtEnabled();
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, @Nullable Intent data) {
        super.onActivityResult(requestCode, resultCode, data);

        switch (requestCode) {
            case REQUEST_ENABLE_BT:
                onBtEnabled();
                break;
        }
    }

    private void onBtEnabled() {
        bluetoothLayout.setOnClickListener(bluetoothClickListener);

        String address = preferences.getString(PREFERENCE_BT_ADDRESS, null);

        if (address == null) {
            setBluetoothDisconnected("Not configured");
            return;
        }

        // TODO: connect
        // Always cancel discovery because it will slow down connection
        // bluetoothAdapter.cancelDiscovery();
    }

    private void setService(String deviceName, ISocket socket) {
        service.connect(socket);
        setBluetoothConnected(deviceName);
    }

    private BluetoothFragment.OnDeviceClickListener bluetoothDeviceClickListener = new BluetoothFragment.OnDeviceClickListener() {

        @Override
        public void onDeviceClick(BluetoothFragment dialog, BluetoothDevice device) {
            preferences.edit().putString(PREFERENCE_BT_ADDRESS, device.getAddress()).commit();
            // TODO: connect
        }
    };

    private View.OnClickListener imageViewClickListener = new View.OnClickListener() {
        @Override
        public void onClick(View v) {
            openProgramsFragment();
        }
    };

    private View.OnClickListener bluetoothClickListener = new View.OnClickListener() {
        @Override
        public void onClick(View v) {
            // TODO: bluetooth click
        }
    };

    private void setBluetoothSearching(String text) {
        setBluetoothStatus(text, R.drawable.ic_bluetooth_searching, R.attr.colorControlNormal);
    }
    private void setBluetoothConnected(String text) {
        setBluetoothStatus(text, R.drawable.ic_bluetooth_connected, R.attr.colorControlNormal);
    }
    private void setBluetoothDisconnected(String text) {
        setBluetoothStatus(text, R.drawable.ic_bluetooth_disabled, R.attr.colorError);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        Fragment fragment = GetFragmentForMenuItemId(id);

        if (fragment == null) {
            Log.e(TAG, "menu item did not match fragment.");
            return false;
        }

        FragmentManager fragmentManager = getSupportFragmentManager();

        fragmentManager
                .beginTransaction()
                .replace(R.id.frame_main, fragment)
                .addToBackStack(TAG)
                .commit();

        return true;
    }

    private void openProgramsFragment() {
        if(service == null) {
            Toast.makeText(this, "Bluetooth not connected!", Toast.LENGTH_SHORT);
            return;
        }

        getSupportFragmentManager()
            .beginTransaction()
            .replace(R.id.frame_main, new ProgramsPagerFragment())
            .commit();
    }

    private Fragment GetFragmentForMenuItemId(int menuItemId) {
        if(service == null) {
            Toast.makeText(this, "Bluetooth not connected!", Toast.LENGTH_SHORT);
            return null;
        }

        switch (menuItemId) {
            case R.id.action_settings:
                return new SettingsFragment();
            case R.id.action_console:
                return new ConsoleFragment();
            default:
                return null;
        }
    }

    // User returns to the activity
    @Override
    protected void onResume() {
        batteryHandler.post(batteryService);
        super.onResume();
    }

    // Another activity comes into the foreground
    @Override
    protected void onPause() {
        batteryHandler.removeCallbacks(batteryService);
        super.onPause();
    }

    private Runnable batteryService = new Runnable() {
        @Override
        public void run() {
            if(service.getStatus() == WheelService.STATUS_CONNECTED) {
                requestBattery();
            }
            batteryHandler.postDelayed(batteryService, BATTERY_INTERVAL);
        }
    };

    private WheelService.OnStatusChangeListener onStatusChangeListener = new WheelService.OnStatusChangeListener() {
        @Override
        public void onStatusChange(int status) {
            switch (status) {
                case WheelService.STATUS_CONNECTED:
                    requestBattery();
                    openProgramsFragment();
                    break;

                case WheelService.STATUS_DISCONNECTED:
                    setBluetoothStatus("Disconnected", R.drawable.ic_bluetooth_disabled, R.attr.colorError);
                    // TODO: retry connection?
                    // TODO: open bluetooth fragment
                    break;

                case WheelService.STATUS_CONNECTING:
                    setBluetoothStatus("Connecting", R.drawable.ic_bluetooth_searching, R.attr.colorControlNormal);
                    break;
            }
        }
    };

    private void requestBattery() {
        try {
            service.writeMessage(WheelService.CMD_BATTERY);
        } catch (IOException ex) {
            Log.e(TAG, "Request battery error.", ex);
        }
    }

    private WheelService.OnMessageReceivedListener onMessageReceivedListener = new WheelService.OnMessageReceivedListener() {

        @Override
        public void onMessageReceived(WheelMessage message) {
            if(message.getCommand().equals(WheelService.CMD_BATTERY)) {
                try {
                    float volts = Utilities.analogReadToVolts(message.getInt());
                    int progress = Utilities.voltsToProgress(volts);
                    batteryProgressBar.setProgress(progress);
                    batteryProgressBar.getProgressDrawable().setColorFilter(new LightingColorFilter(0xFF000000, getAttributeColor(progress > 20 ? R.attr.colorAccent : R.attr.colorError)));
                    batteryText.setText(BATTERY_FORMAT.format(volts) + 'v');
                    batteryText.setTextColor(getAttributeColor(progress > 20 ? R.attr.colorControlNormal : R.attr.colorError));
                    batteryImage.setImageResource(progress > 20 ? R.drawable.ic_battery_full : R.drawable.ic_battery_20);
                } catch (Exception ex) {
                    Log.e(TAG, "Invalid battery value.", ex);
                }
            }
        }
    };

    @Override
    protected void onDestroy() {
        service.removeOnMessageReceivedListener(onMessageReceivedListener);
        service.removeOnStatusChangeListener(onStatusChangeListener);
        super.onDestroy();
    }

    private void setBluetoothStatus(String text, int iconResourceId, int colorAttributeId) {
        bluetoothText.setTextColor(getAttributeColor(colorAttributeId));
        bluetoothText.setText(text);
        bluetoothImage.setImageResource(iconResourceId);
    }

    private int getAttributeColor(int attributeId) {
        TypedValue colorValue = new TypedValue();
        getTheme().resolveAttribute(attributeId, colorValue, true);
        return ContextCompat.getColor(this, colorValue.resourceId);
    }
}
