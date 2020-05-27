package pariesz.pov;

import android.content.res.Configuration;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentManager;
import androidx.fragment.app.FragmentPagerAdapter;
import androidx.recyclerview.widget.GridLayoutManager;
import androidx.recyclerview.widget.RecyclerView;
import androidx.viewpager.widget.ViewPager;

import java.util.ArrayList;

public class ProgramsFragment extends Fragment {
    private static final String TAG = "ProgramsFragment";
    private static final String ARG_CMD = "cmd";

    private ProgramsRecyclerViewAdaptor recyclerViewAdaptor;
    private RecyclerView recyclerView;
    private WheelService service;
    private String cmd;

    private ArrayList<Program> getMovingPrograms() {
        ArrayList<Program> programs = new ArrayList<>();
        programs.add(new Program(13, R.drawable.ic_timer));
        programs.add(new Program(0, R.drawable.program_nyancat));
        programs.add(new Program(1, R.drawable.program_poo));
        programs.add(new Program(2, R.drawable.program_fist));
        programs.add(new Program(3, R.drawable.program_hamster));
        programs.add(new Program(4, R.drawable.program_rocket));
        programs.add(new Program(5, R.drawable.program_portal));
        programs.add(new Program(6, R.drawable.program_lightning));
        programs.add(new Program(7, R.drawable.program_text));
        programs.add(new Program(8, R.drawable.program_velocity));
        programs.add(new Program(9, R.drawable.program_masacritica));
        programs.add(new Program(10, R.drawable.program_radioactive));
        programs.add(new Program(11, R.drawable.program_shooting_stars));
        programs.add(new Program(12, R.drawable.program_swirl));
        return programs;
    }

    private ArrayList<Program> getStationaryPrograms() {
        ArrayList<Program> programs = new ArrayList<>();
        programs.add(new Program(0, R.drawable.ic_timer));
        programs.add(new Program(1, R.drawable.program_pulse));
        programs.add(new Program(2, R.drawable.program_rainbow));
        programs.add(new Program(3, R.drawable.program_points));
        return programs;
    }

    public static ProgramsFragment newInstance(String cmd) {
        ProgramsFragment fragment = new ProgramsFragment();
        Bundle bundle = new Bundle();
        bundle.putString(ARG_CMD, cmd);
        fragment.setArguments(bundle);
        return fragment;
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        this.service = ((MainActivity)getActivity()).getService();
        this.cmd = getArguments().getString(ARG_CMD);
        return inflater.inflate(R.layout.fragment_programs, container, false);
    }

    @Override
    public void onStart() {
        super.onStart();

        try {
            service.writeMessage(cmd);
        } catch (Exception ex) {
            LogError("Error requesting program.", ex);
        }
    }

    public void onViewCreated(@NonNull View view, Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);

        ArrayList<Program> programs = cmd.equals(WheelService.CMD_MOVING_PROGRAM) ? getMovingPrograms() : getStationaryPrograms();
        recyclerViewAdaptor = new ProgramsRecyclerViewAdaptor(programs, onItemClickListener, cmd);
        recyclerView = view.findViewById(R.id.recyclerView_programs);
        recyclerView.setAdapter(recyclerViewAdaptor);

        boolean portrait = getActivity().getResources().getConfiguration().orientation == Configuration.ORIENTATION_PORTRAIT;
        recyclerView.setLayoutManager(new GridLayoutManager(this.getContext(), portrait ? 3 : 6));

        service.addOnMessageReceivedListener(onMessageReceivedListener);
    }

    private ProgramsRecyclerViewAdaptor.OnItemClickListener onItemClickListener = new ProgramsRecyclerViewAdaptor.OnItemClickListener() {

        @Override
        public void onItemClick(Program program) {
            try {
                service.writeMessage(cmd, program.id);
            } catch (Exception ex) {
                LogError("Error setting program.", ex);
            }
        }
    };

    private WheelService.OnMessageReceivedListener onMessageReceivedListener = new WheelService.OnMessageReceivedListener() {
        @Override
        public void onMessageReceived(WheelMessage message) {
            if (message.getCommand().equals(cmd)) {
                try {
                    recyclerViewAdaptor.setActiveItem(message.getInt());
                } catch (Exception ex) {
                    LogError("Error parsing message: " + message.getMessage(), ex);
                }

            }
        }
    };

    private void LogError(String message) {
        Log.e(TAG, message);
        Toast.makeText(getContext(), message, Toast.LENGTH_SHORT);
    }

    private void LogError(String message, Exception ex) {
        Log.e(TAG, message, ex);
        Toast.makeText(getContext(), message + " " + ex.getMessage(), Toast.LENGTH_SHORT);
    }

    @Override
    public void onDestroyView() {
        service.removeOnMessageReceivedListener(onMessageReceivedListener);
        super.onDestroyView();
    }
}
