package pariesz.pov;

public interface WheelMessageReader {
    boolean consume(byte ch) throws Exception;

    WheelMessage getMessage();
}
