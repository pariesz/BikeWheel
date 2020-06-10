package pariesz.pov;

public class MockWheelEepromMessageReader extends WheelEepromMessageReader {

    public MockWheelEepromMessageReader(byte command) throws Exception {
        super(command);
    }

    @Override
    public boolean consume(byte ch) throws Exception {
        boolean result = super.consume(ch);

        if(position == 3 && command == WheelService.CMD_GET_EEPROM) {
            return true;
        }

        return result;
    }

    public WheelMessage getMessage() {
        if(command == WheelService.CMD_GET_EEPROM) {
            return new WheelEepromMessage(command, address, (byte)value.length);
        }
        return super.getMessage();
    }
}
