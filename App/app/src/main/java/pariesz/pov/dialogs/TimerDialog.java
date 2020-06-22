package pariesz.pov.dialogs;

import android.app.AlertDialog;
import android.app.Dialog;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.SeekBar;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

import pariesz.pov.R;
import pariesz.pov.WheelEepromMessage;
import pariesz.pov.WheelService;

public class TimerDialog extends ProgramDialog {

    private TextView delayText;
    private SeekBar delaySeeBar;

    @NonNull
    @Override
    public Dialog onCreateDialog(@Nullable Bundle savedInstanceState) {
        super.onCreateDialog(savedInstanceState);

        LayoutInflater inflater = getActivity().getLayoutInflater();
        View view = inflater.inflate(R.layout.dialog_timer, null);

        delayText = view.findViewById(R.id.textView_timer_delay);
        delaySeeBar = view.findViewById(R.id.seekBar_timer_delay);
        delaySeeBar.setOnSeekBarChangeListener(delayChangeListener);

        return new AlertDialog.Builder(getActivity()).setView(view).setTitle("Timer").create();
    }

    private SeekBar.OnSeekBarChangeListener delayChangeListener = new SeekBar.OnSeekBarChangeListener() {
        int progress = 0;

        @Override
        public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
            this.progress = progress;
            setDelayText(progress);
        }

        @Override
        public void onStartTrackingTouch(SeekBar seekBar) { }

        @Override
        public void onStopTrackingTouch(SeekBar seekBar) {
            getService().setEeprom(WheelService.EEPROM_TIMER_FRAMES, (short)progress);
        }
    };

    @Override
    public void onStart() {
        super.onStart();
        getService().getEeprom(WheelService.EEPROM_TIMER_FRAMES, 2);
    }

    @Override
    protected void onEepromMessageReceived(WheelEepromMessage message) {
        switch (message.getAddress()) {
            case WheelService.EEPROM_TIMER_FRAMES:
                int frames = message.getValueInt();
                delaySeeBar.setProgress(frames);
                setDelayText(frames);
        }
    }

    private void setDelayText(int frames) {
        delayText.setText("Delay: " + (frames / 31) + "s");
    }
}
