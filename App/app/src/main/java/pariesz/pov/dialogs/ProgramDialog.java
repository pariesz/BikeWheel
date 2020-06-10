package pariesz.pov.dialogs;

import androidx.appcompat.app.AppCompatDialogFragment;

import pariesz.pov.MainActivity;
import pariesz.pov.WheelEepromMessage;
import pariesz.pov.WheelMessage;
import pariesz.pov.WheelService;

public abstract class ProgramDialog extends AppCompatDialogFragment {
    protected WheelService getService() {
        return ((MainActivity)getActivity()).getService();
    }

    private WheelService.OnMessageReceivedListener onMessageReceivedListener = new WheelService.OnMessageReceivedListener() {

        @Override
        public void onMessageReceived(WheelMessage message) {
            switch (message.getCommand()) {
                case WheelService.CMD_GET_EEPROM:
                case WheelService.CMD_SET_EEPROM:
                    onEepromMessageReceived((WheelEepromMessage)message);
            }
        }
    };

    protected abstract void onEepromMessageReceived(WheelEepromMessage message);

    @Override
    public void onStart() {
        super.onStart();
        getService().addOnMessageReceivedListener(onMessageReceivedListener);
    }

    @Override
    public void onStop() {
        super.onStop();
        getService().removeOnMessageReceivedListener(onMessageReceivedListener);
    }
}
