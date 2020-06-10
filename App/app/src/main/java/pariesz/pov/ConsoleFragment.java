package pariesz.pov;

import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import androidx.annotation.NonNull;
import androidx.fragment.app.Fragment;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

public class ConsoleFragment extends Fragment {
    private static final String TAG = "ConsoleFragment";

    private RecyclerView logRecyclerView;
    private ConsoleRecyclerViewAdaptor recyclerAdaptor;
    private WheelService service;

    @Override
    public View onCreateView( LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        service = ((MainActivity)getActivity()).getService();
        return inflater.inflate(R.layout.fragment_console, container, false);
    }

    @Override
    public void onViewCreated(@NonNull View view, Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);

        recyclerAdaptor = new ConsoleRecyclerViewAdaptor(service.getMessages());
        logRecyclerView = view.findViewById(R.id.recyclerView_console);
        logRecyclerView.setAdapter(recyclerAdaptor);

        LinearLayoutManager layoutManager = new LinearLayoutManager(this.getContext());
        layoutManager.setStackFromEnd(true);
        layoutManager.setReverseLayout(true);
        logRecyclerView.setLayoutManager(layoutManager);

        service.addOnMessageSentListener(onMessageSentListener);
        service.addOnMessageReceivedListener(onMessageReceivedListener);
    }

    private WheelService.OnMessageReceivedListener onMessageReceivedListener = new WheelService.OnMessageReceivedListener() {

        @Override
        public void onMessageReceived(WheelMessage message) {
            recyclerAdaptor.notifyDataSetChanged();
        }
    };

    private WheelService.OnMessageSentListener onMessageSentListener = new WheelService.OnMessageSentListener() {

        @Override
        public void onMessageSent(WheelMessage message) {
            recyclerAdaptor.notifyDataSetChanged();
        }
    };

    @Override
    public void onDestroyView() {
        service.removeOnMessageSentListener(onMessageSentListener);
        service.removeOnMessageReceivedListener(onMessageReceivedListener);
        super.onDestroyView();
    }
}