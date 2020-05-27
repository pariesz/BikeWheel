package pariesz.pov;

import android.os.Bundle;
import android.os.Handler;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.view.animation.Animation;
import android.view.animation.LinearInterpolator;
import android.view.animation.RotateAnimation;
import android.widget.ImageView;
import android.widget.SeekBar;
import android.widget.TextView;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.fragment.app.Fragment;

import org.florescu.android.rangeseekbar.RangeSeekBar;

import java.io.IOException;
import java.text.DecimalFormat;

public class SettingsFragment extends Fragment {
    private static final String TAG = "SettingsFragment";
    private static final DecimalFormat velocityFormat = new DecimalFormat("0.0");
    private static final DecimalFormat batteryFormat = new DecimalFormat("0.0");
    private static final int REQUEST_INTERVAL = 100;

    private Handler requestHandler = new Handler();
    private TextView angleText;
    private TextView velocityText;
    private TextView wheelCircumferenceText;
    private SeekBar wheelCircumferenceSeekBar;
    private SeekBar brightnessSeekBar;
    private ImageView angleImageView;
    private RangeSeekBar<Float> stationaryMovingVelocity;
    private WheelService service;
    private Handler handler = new Handler();

    private int wheelCircumference;
    private int rotationRate;
    private int movingRotationRate;
    private int stationaryRotationRate;

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        service = ((MainActivity)getActivity()).getService();
        return inflater.inflate(R.layout.fragment_settings, container, false);
    }

    @Override
    public void onViewCreated(@NonNull View view, Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);

        angleText = view.findViewById(R.id.textView_settings_angle);
        velocityText = view.findViewById(R.id.textView_settings_velocity);
        wheelCircumferenceSeekBar = view.findViewById(R.id.seekBar_settings_wheelCircumference);
        wheelCircumferenceSeekBar.setOnSeekBarChangeListener(wheelCircumferenceChangeListener);
        wheelCircumferenceText = view.findViewById(R.id.textView_settings_wheelCircumference);
        stationaryMovingVelocity = view.findViewById(R.id.rangeSeekBar_settings_stationaryMovingVelocity);
        stationaryMovingVelocity.setOnRangeSeekBarChangeListener(stationaryMovingVelocityChangeListener);
        brightnessSeekBar = view.findViewById(R.id.seekBar_settings_brightness);
        brightnessSeekBar.setOnSeekBarChangeListener(brightnessChangeListener);
        angleImageView = view.findViewById(R.id.imageView_settings_angle);
        service.addOnMessageReceivedListener(onMessageReceivedListener);

        try {
            // Circumference MUST be first as it is required for velocity readings
            service.writeMessage(WheelService.CMD_CIRCUMFERENCE);
            service.writeMessage(WheelService.CMD_BRIGHTNESS);
            service.writeMessage(WheelService.CMD_MOVING_ROTATION_RATE);
            service.writeMessage(WheelService.CMD_STATIONARY_ROTATION_RATE);
        } catch (IOException ex) {
            LogError("request error", ex);
        }
    }

    private RangeSeekBar.OnRangeSeekBarChangeListener<Float> stationaryMovingVelocityChangeListener = new  RangeSeekBar.OnRangeSeekBarChangeListener<Float>() {

        @Override
        public void onRangeSeekBarValuesChanged(RangeSeekBar<?> bar, Float minValue, Float maxValue) {
            try {
                service.writeMessage(WheelService.CMD_STATIONARY_ROTATION_RATE, kmhToInt16s(minValue));
            } catch (IOException ex) {
                LogError("set stationary velocity:" + minValue + " error", ex);
            }

            try {
                service.writeMessage(WheelService.CMD_MOVING_ROTATION_RATE, kmhToInt16s(maxValue));
            } catch (IOException ex) {
                LogError("set moving velocity:" + maxValue + " error", ex);
            }
        }
    };

    private SeekBar.OnSeekBarChangeListener wheelCircumferenceChangeListener = new SeekBar.OnSeekBarChangeListener() {
        int progress = 0;

        public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
            this.progress = progress;
            wheelCircumferenceText.setText(progress + "mm");
        }

        public void onStartTrackingTouch(SeekBar seekBar) {
            // TODO Auto-generated method stub
        }

        public void onStopTrackingTouch(SeekBar seekBar) {
            try {
                service.writeMessage(WheelService.CMD_CIRCUMFERENCE, progress);
            } catch (IOException ex) {
                LogError("setWheelCircumference:" + progress + " error", ex);
            }
        }
    };

    private SeekBar.OnSeekBarChangeListener  brightnessChangeListener = new SeekBar.OnSeekBarChangeListener() {
        int progress = 0;

        public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
            this.progress = progress;
        }

        public void onStartTrackingTouch(SeekBar seekBar) {
            // TODO Auto-generated method stub
        }

        public void onStopTrackingTouch(SeekBar seekBar) {
            try {
                service.writeMessage(WheelService.CMD_BRIGHTNESS, progress);
            } catch (IOException ex) {
                LogError("setBrightness:" + progress + " error", ex);
            }
        }
    };

    private WheelService.OnMessageReceivedListener onMessageReceivedListener = new WheelService.OnMessageReceivedListener() {

        @Override
        public void onMessageReceived(WheelMessage message) {
            try {
                switch (message.getCommand()) {
                    case WheelService.CMD_ANGLE:
                        int degrees = Utilities.int16ToDegrees(message.getInt());
                        angleText.setText(degrees + "°");
                        angleImageView.setRotation(degrees);
                        angleImageView.setRotation(degrees);
                        handler.postDelayed(angleService, REQUEST_INTERVAL);
                        break;

                    case WheelService.CMD_BRIGHTNESS:
                        brightnessSeekBar.setProgress(message.getInt());
                        break;

                    case WheelService.CMD_CIRCUMFERENCE:
                        wheelCircumference = message.getInt();
                        wheelCircumferenceSeekBar.setProgress(wheelCircumference);

                        if(movingRotationRate != 0) {
                            stationaryMovingVelocity.setSelectedMaxValue(int16sToKmh(movingRotationRate));
                        }

                        if(stationaryRotationRate != 0) {
                            stationaryMovingVelocity.setSelectedMinValue(int16sToKmh(stationaryRotationRate));
                        }

                        if(rotationRate != 0) {
                            velocityText.setText(velocityFormat.format(int16sToKmh(rotationRate)));
                        }
                        break;

                    case WheelService.CMD_STATIONARY_ROTATION_RATE:
                        stationaryRotationRate = message.getInt();

                        if(wheelCircumference != 0) {
                            stationaryMovingVelocity.setSelectedMinValue(int16sToKmh(stationaryRotationRate));
                        }
                        break;

                    case WheelService.CMD_MOVING_ROTATION_RATE:
                        movingRotationRate = message.getInt();

                        if(wheelCircumference != 0) {
                            stationaryMovingVelocity.setSelectedMaxValue(int16sToKmh(movingRotationRate));
                        }
                        break;

                    case WheelService.CMD_ROTATION_RATE:
                        rotationRate = message.getInt();

                        if(wheelCircumference != 0) {
                            velocityText.setText(velocityFormat.format(int16sToKmh(rotationRate)));
                        }

                        handler.postDelayed(rotationRateService, REQUEST_INTERVAL);
                        break;
                }
            } catch (Exception ex) {
                LogError("Invalid integer value: " + message.getMessage(), ex);
            }
        }
    };

    private Runnable angleService = new Runnable() {
        @Override
        public void run() {
            if(service.getStatus() == WheelService.STATUS_CONNECTED) {
                try {
                    service.writeMessage(WheelService.CMD_ANGLE);
                } catch (IOException ex) {
                    Log.e(TAG, WheelService.CMD_ANGLE + " command failure", ex);
                }
            }
        }
    };

    private Runnable rotationRateService = new Runnable() {
        @Override
        public void run() {
            if(service.getStatus() == WheelService.STATUS_CONNECTED) {
                try {
                    service.writeMessage(WheelService.CMD_ROTATION_RATE);
                } catch (IOException ex) {
                    Log.e(TAG, WheelService.CMD_ROTATION_RATE + " command failure", ex);
                }
            }
        }
    };

    // User returns to the activity
    @Override
    public void onResume() {
        handler.postDelayed(rotationRateService, REQUEST_INTERVAL);
        handler.postDelayed(angleService, REQUEST_INTERVAL);
        super.onResume();
    }

    // Another activity comes into the foreground
    @Override
    public void onPause() {
        handler.removeCallbacks(rotationRateService);
        handler.removeCallbacks(angleService);
        super.onPause();
    }

    private float int16sToKmh(int rotationRate) {
        return Utilities.int16sToKmh(rotationRate, wheelCircumference);
    }

    private int kmhToInt16s(float kmh) {
        return Utilities.kmhToInt16s(kmh, wheelCircumference);
    }

    private void LogError(String message, Exception ex) {
        Log.e(TAG, message, ex);
        Toast.makeText(getContext(), message + " " + ex.getMessage(), Toast.LENGTH_SHORT);
    }

    @Override
    public void onDestroyView() {
        super.onDestroyView();
        service.removeOnMessageReceivedListener(onMessageReceivedListener);
    }
}
