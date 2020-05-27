package pariesz.pov;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.KeyEvent;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.view.inputmethod.EditorInfo;
import android.view.inputmethod.InputMethodManager;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.fragment.app.Fragment;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import java.util.ArrayList;

public class ConsoleFragment extends Fragment {
    private static final String TAG = "ConsoleFragment";

    private EditText transmitEditText;
    private Button transmitButton;
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

        transmitEditText = view.findViewById(R.id.editText_console);
        transmitEditText.setOnFocusChangeListener(transmitEditTextOnFocusChange);
        transmitEditText.setOnEditorActionListener(transmitEditTextOnEditorAction);

        transmitButton = view.findViewById(R.id.button_console);
        transmitButton.setOnClickListener(transmitButtonClickListener);

        recyclerAdaptor = new ConsoleRecyclerViewAdaptor(getContext(), service.getMessages());
        logRecyclerView = view.findViewById(R.id.recyclerView_console);
        logRecyclerView.setAdapter(recyclerAdaptor);

        LinearLayoutManager layoutManager = new LinearLayoutManager(this.getContext());
        layoutManager.setStackFromEnd(true);
        layoutManager.setReverseLayout(true);
        logRecyclerView.setLayoutManager(layoutManager);

        service.addOnMessageSentListener(onMessageSentListener);
        service.addOnMessageReceivedListener(onMessageReceivedListener);
    }

    private void transmit() {
        CharSequence text = transmitEditText.getText();

        if(text != "") {
            try {
                service.writeMessage(text.toString());
            } catch (Exception ex) {
                Log.e(TAG, "writeMessage error: " + text, ex);
                Toast.makeText(getContext(), "writeMessage error: " + text + ". " + ex.getMessage(), Toast.LENGTH_SHORT);
            }

            transmitEditText.setText("");
        }
    }

    private View.OnFocusChangeListener transmitEditTextOnFocusChange = new View.OnFocusChangeListener() {

        @Override
        public void onFocusChange(View v, boolean hasFocus) {
            if(!hasFocus) {
                InputMethodManager imm = (InputMethodManager) v.getContext().getSystemService(Activity.INPUT_METHOD_SERVICE);
                imm.toggleSoftInput(InputMethodManager.HIDE_IMPLICIT_ONLY, 0);
            }
        }
    };

    private View.OnClickListener transmitButtonClickListener = new View.OnClickListener() {

        @Override
        public void onClick(View v) {
            transmit();
            transmitEditText.clearFocus();
        }
    };

    private EditText.OnEditorActionListener transmitEditTextOnEditorAction = new EditText.OnEditorActionListener(){

        @Override
        public boolean onEditorAction(TextView v, int actionId, KeyEvent event) {
            if (actionId == EditorInfo.IME_NULL && event.getAction() == KeyEvent.ACTION_DOWN) {
                transmit();
            }
            return true;
        }
    };

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