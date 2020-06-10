package pariesz.pov;

import android.os.Build;

import com.google.android.material.math.MathUtils;

public class Utilities {
    // https://stackoverflow.com/questions/2799097/how-can-i-detect-when-an-android-application-is-running-in-the-emulator
    public static boolean isProbablyAnEmulator() {
        return Build.FINGERPRINT.startsWith("generic")
            || Build.FINGERPRINT.startsWith("unknown")
            || Build.MODEL.contains("google_sdk")
            || Build.MODEL.contains("Emulator")
            || Build.MODEL.contains("Android SDK built for x86")
            || Build.BOARD == "QC_Reference_Phone" //bluestacks
            || Build.MANUFACTURER.contains("Genymotion")
            || Build.HOST.startsWith("Build") //MSI App Player
            || (Build.BRAND.startsWith("generic") && Build.DEVICE.startsWith("generic"))
            || "google_sdk" == Build.PRODUCT;
    }

    public static float analogReadToVolts(int analogRead) {
        // Arduino 0-5v = 0-1023, there is also voltage divider that converts 12v to 5v
        return (float)analogRead / (1023 / 12);
    }

    public static int int16ToDegrees(int rotation) {
        return (360 * rotation) / 65535;
    }

    public static float int16sToKmh(int rotationRate, int circumference) {
        // mms = circumference * rotationRate / 65535
        // kms = mms / (1000 * 1000)
        // kmh = kms * 60 * 60
        return circumference * rotationRate * 60f * 60f / (65535f * 1000f * 1000f);
    }

    public static int kmhToInt16s(float kmh, int circumference) {
        return (int)(kmh  * 65535f * 1000f * 1000f / (circumference * 60f * 60f));
    }

    public static int voltsToProgress(float volts) {
        float progress = (volts - WheelService.VOLTAGE_MIN) / (WheelService.VOLTAGE_MAX - WheelService.VOLTAGE_MIN);
        return (int)Math.min(100, Math.max(0, progress) * 100);
    }

    private final static char[] hexArray = "0123456789ABCDEF".toCharArray();
    public static String bytesToHex(byte[] bytes) {
        char[] hexChars = new char[bytes.length * 2];
        for ( int j = 0; j < bytes.length; j++ ) {
            int v = bytes[j] & 0xFF;
            hexChars[j * 2] = hexArray[v >>> 4];
            hexChars[j * 2 + 1] = hexArray[v & 0x0F];
        }
        return new String(hexChars);
    }
}
