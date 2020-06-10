package pariesz.pov;

import android.content.Context;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.core.content.ContextCompat;
import androidx.recyclerview.widget.RecyclerView;

import java.time.format.DateTimeFormatter;
import java.util.LinkedList;
import java.util.Queue;

public class ConsoleRecyclerViewAdaptor extends RecyclerView.Adapter<ConsoleRecyclerViewAdaptor.ViewHolder> {
    private Iterable<WheelMessage> messages;
    private static final String TAG = "ConsoleRecyclerViewAdaptor";

    public ConsoleRecyclerViewAdaptor(Iterable<WheelMessage> messages) {
        this.messages = messages;
    }

    @NonNull
    @Override
    public ViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        View view = LayoutInflater.from(parent.getContext()).inflate(R.layout.layout_console_log, parent, false);
        return new ViewHolder(view);
    }

    @Override
    public void onBindViewHolder(@NonNull ViewHolder holder, int position) {
        Log.d(TAG, "onBindViewHolder: called.");
        WheelMessage message = ((LinkedList<WheelMessage>)messages).get(position);
        holder.setMessage(message);
    }
    @Override
    public int getItemCount() {
        return ((Queue<?>)messages).size();
    }

    public class ViewHolder extends RecyclerView.ViewHolder {
        private  Context context;
        private WheelMessage message;
        private TextView messageText;
        private TextView dateText;
        private DateTimeFormatter dateFormat = DateTimeFormatter.ofPattern("HH:mm:ss");

        public ViewHolder(@NonNull View itemView) {
            super(itemView);
            context = itemView.getContext();
            messageText = itemView.findViewById(R.id.textView_consoleLog_message);
            dateText = itemView.findViewById(R.id.textView_consoleLog_date);
        }

        public WheelMessage getMessage() {
            return message;
        }

        public void setMessage(WheelMessage message) {
            this.message = message;
            this.messageText.setText(message.toString());
            this.messageText.setTextColor(ContextCompat.getColor(context, message.getTransmit() ? R.color.colorTx : R.color.colorRx));
            this.dateText.setText(message.getDate().format(dateFormat));
        }
    }
}
