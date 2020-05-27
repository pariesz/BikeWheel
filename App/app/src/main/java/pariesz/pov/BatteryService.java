package pariesz.pov;

import android.app.Service;
import android.content.Intent;
import android.os.Handler;
import android.os.IBinder;

import androidx.annotation.Nullable;

public class BatteryService extends Service {
    private Handler handler = new Handler();
    private static final long INTERVAL = 10 * 1000;
    private Runnable runnableService = new Runnable() {
        @Override
        public void run() {
            //create AsyncTask here

            handler.postDelayed(runnableService, INTERVAL);
        }
    };
    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        handler.post(runnableService);
        return START_STICKY;
    }

    @Nullable
    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }

    @Override
    public void onDestroy() {
        handler.removeCallbacks(runnableService);
        super.onDestroy();
    }
}
