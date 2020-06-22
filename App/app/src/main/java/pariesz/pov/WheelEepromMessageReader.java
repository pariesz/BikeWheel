package pariesz.pov;

import androidx.annotation.NonNull;

public class WheelEepromMessageReader implements WheelMessageReader {
    protected byte[] value;
    protected short address;
    protected int position;
    protected byte command;

    public WheelEepromMessageReader(byte command) throws Exception {
        switch (command) {
            case WheelService.CMD_GET_EEPROM:
            case WheelService.CMD_SET_EEPROM:
                this.command = command;
                break;
            default:
                throw new IllegalArgumentException("Invalid command: " + command);
        }
    }

    public boolean consume(byte ch) throws Exception {
        switch (++position) {
            case 1:
                address = ch;
                return false;

            case 2:
                address |= (((short)ch) << 8); // Bytes are sent in host order, Arduino uses little-edian
                if(address > 4095) throw new Exception("invalid address: " + address);
                return false;

            case 3:
                value = new byte[ch];
                return false;

            default:
                value[position - 4] = ch;
                return position - 3 >= value.length;
        }
    }

    @Override
    public WheelMessage getMessage() {
        return new WheelEepromMessage(command, address, value, false);
    }

    @NonNull
    @Override
    public String toString() {
        return getMessage().toString();
    }
}
