package pariesz.pov;

import android.content.res.Configuration;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.fragment.app.Fragment;
import androidx.recyclerview.widget.GridLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import java.util.ArrayList;

public class ProgramsFragment extends Fragment {
    private static final String TAG = "ProgramsFragment";
    private static final String ARG_GET_CMD = "GetCmd";
    private static final String ARG_SET_CMD = "SetCmd";

    private ProgramsRecyclerViewAdaptor recyclerViewAdaptor;
    private RecyclerView recyclerView;
    private WheelService service;
    private byte getCmd;
    private byte setCmd;

    public static ProgramsFragment newInstance(byte getCmd, byte setCmd) {
        ProgramsFragment fragment = new ProgramsFragment();
        Bundle bundle = new Bundle();
        bundle.putByte(ARG_GET_CMD, getCmd);
        bundle.putByte(ARG_SET_CMD, setCmd);
        fragment.setArguments(bundle);
        return fragment;
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        this.service = ((MainActivity)getActivity()).getService();
        this.getCmd = getArguments().getByte(ARG_GET_CMD);
        this.setCmd = getArguments().getByte(ARG_SET_CMD);
        return inflater.inflate(R.layout.fragment_programs, container, false);
    }

    @Override
    public void onStart() {
        super.onStart();

        try {
            service.command(getCmd);
        } catch (Exception ex) {
            LogError("Error requesting program.", ex);
        }
    }

    public void onViewCreated(@NonNull View view, Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);
        boolean moving = getCmd == WheelService.CMD_GET_MOVING_PROGRAM;
        ArrayList<Program> programs =  moving ? Program.PROGRAMS_MOVING : Program.PROGRAMS_STATIONARY;
        recyclerViewAdaptor = new ProgramsRecyclerViewAdaptor(getActivity(), programs, onItemClickListener, moving);
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
                service.command(setCmd, program.getId());
            } catch (Exception ex) {
                LogError("Error setting program.", ex);
            }
        }
    };

    private WheelService.OnMessageReceivedListener onMessageReceivedListener = new WheelService.OnMessageReceivedListener() {
        @Override
        public void onMessageReceived(WheelMessage message) {
            if (message.getCommand() == getCmd || message.getCommand() == setCmd) {
                try {
                    recyclerViewAdaptor.setActiveItem(message.getValueInt());
                } catch (Exception ex) {
                    LogError("Error parsing message: " + message, ex);
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
        Toast.makeText(getContext(), message + " " + ex.getMessage(), Toast.LENGTH_SHORT).show();
    }

    @Override
    public void onDestroyView() {
        service.removeOnMessageReceivedListener(onMessageReceivedListener);
        super.onDestroyView();
    }
}
