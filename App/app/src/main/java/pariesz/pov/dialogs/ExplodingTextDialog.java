package pariesz.pov.dialogs;

import android.app.AlertDialog;
import android.app.Dialog;
import android.os.Bundle;
import android.text.Editable;
import android.text.TextWatcher;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.EditText;
import android.widget.SeekBar;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

import java.util.Timer;
import java.util.TimerTask;

import pariesz.pov.R;
import pariesz.pov.WheelEepromMessage;
import pariesz.pov.WheelService;

public class ExplodingTextDialog extends ProgramDialog {
    private static final String TAG = "ExplodingTextDialog";

    private EditText editText;
    private String text;

    @NonNull
    @Override
    public Dialog onCreateDialog(@Nullable Bundle savedInstanceState) {
        super.onCreateDialog(savedInstanceState);

        LayoutInflater inflater = getActivity().getLayoutInflater();
        View view = inflater.inflate(R.layout.dialog_exploding_text, null);

        editText = view.findViewById(R.id.editText_explodingText);
        editText.addTextChangedListener(textWatcher);

        getService().getEeprom(WheelService.EEPROM_EXPLODING_TEXT, 39);
        return new AlertDialog.Builder(getActivity()).setView(view).setTitle("Exploding Text").create();
    }

    private TextWatcher textWatcher = new TextWatcher() {
        private Timer debounceTimer;

        @Override
        public void beforeTextChanged(CharSequence s, int start, int count, int after) {
            // nothing to do here
        }

        @Override
        public void onTextChanged(CharSequence s, int start, int before, int count) {
            // nothing to do here
            if(debounceTimer != null) {
                debounceTimer.cancel();
            }
        }

        @Override
        public void afterTextChanged(Editable s) {
            if(text.equals(editText.getText().toString())) {
                return;
            }

            debounceTimer = new Timer();
            debounceTimer.schedule(new TimerTask() {
                @Override
                public void run() {
                    getService().setEeprom(WheelService.EEPROM_EXPLODING_TEXT, editText.getText().toString());
                }
            }, 600);
        }
    };

    @Override
    protected void onEepromMessageReceived(WheelEepromMessage message) {
        switch (message.getAddress()) {
            case WheelService.EEPROM_EXPLODING_TEXT:
                text = message.getValueString().replaceAll("\\p{C}", "?");

                if(!text.equals(editText.getText().toString())) {
                    // only update if the text has changed or else the cursor will reset
                    editText.setText(text);
                    editText.setSelection(text.length());
                }
        }
    }
}
