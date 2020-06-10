package pariesz.pov;

import android.util.Log;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentManager;
import androidx.fragment.app.FragmentPagerAdapter;

import java.util.ArrayList;

public class ProgramsPagerAdaptor extends FragmentPagerAdapter {
    private static final String TAG = "ProgramsPagerAdaptor";

    public ProgramsPagerAdaptor(@NonNull FragmentManager fm) {
        super(fm, ProgramsPagerAdaptor.BEHAVIOR_RESUME_ONLY_CURRENT_FRAGMENT);
    }

    @NonNull
    @Override
    public Fragment getItem(int position) {
        switch (position) {
            case 0:
                return ProgramsFragment.newInstance(WheelService.CMD_GET_MOVING_PROGRAM, WheelService.CMD_SET_MOVING_PROGRAM);
            case 1:
                return ProgramsFragment.newInstance(WheelService.CMD_GET_STATIONARY_PROGRAM, WheelService.CMD_SET_STATIONARY_PROGRAM);
            default:
                Log.e(TAG, "Invalid position: " + position);
                return getItem(0);
        }
    }

    @Override
    public int getCount() {
        return 2;
    }

    @Nullable
    @Override
    public CharSequence getPageTitle(int position) {
        switch (position) {
            case 0:
                return "Moving";
            case 1:
                return "Stationary";
            default:
                return "Unknown";
        }
    }
}
