package pariesz.pov;

import android.graphics.Color;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.view.animation.Animation;
import android.view.animation.LinearInterpolator;
import android.view.animation.RotateAnimation;
import android.widget.FrameLayout;
import android.widget.ImageView;
import android.widget.RelativeLayout;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import java.util.ArrayList;

public class ProgramsRecyclerViewAdaptor extends RecyclerView.Adapter<ProgramsRecyclerViewAdaptor.ViewHolder> {
    private int clickedItem = -1;
    private int activeItem = -1;

    private static final String TAG = "ProgramsRecyclerViewAda";

    private ArrayList<Program> programs;

    private final OnItemClickListener listener;
    private String cmd;

    public interface OnItemClickListener {
        void onItemClick(Program program);
    }

    public ProgramsRecyclerViewAdaptor(ArrayList<Program> programs, OnItemClickListener listener, String cmd) {
        this.programs = programs;
        this.listener = listener;
        this.cmd = cmd;
    }

    @NonNull
    @Override
    public ViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        View view = LayoutInflater.from(parent.getContext()).inflate(R.layout.layout_program, parent, false);
        return new ViewHolder(view);
    }

    @Override
    public void onBindViewHolder(@NonNull ViewHolder holder, int position) {
        Program program = programs.get(position);

        holder.setImageResource(program.resourceId);

        if(position == activeItem) {
            holder.setState(ViewHolder.STATE_ACTIVE);
        } else if (position == clickedItem) {
            holder.setState(ViewHolder.STATE_CLICKED);
        } else {
            holder.setState(ViewHolder.STATE_NONE);
        }
    }
    @Override
    public int getItemCount() {
        return programs.size();
    }

    public void setActiveItem(int id) throws Exception {
        for(int i = 0; i < programs.size(); i++) {
            Program program = programs.get(i);

            if(program.id == id) {
                if(activeItem != i && activeItem != -1) {
                    notifyItemChanged(activeItem);
                }
                if(clickedItem != i && clickedItem != activeItem && clickedItem != -1) {
                    notifyItemChanged(clickedItem);
                }

                clickedItem = i;
                activeItem = i;
                notifyItemChanged(i);

                return;
            }
        }

        throw new Exception("program (id:" + id + ") not found.");
    }

    public class ViewHolder extends RecyclerView.ViewHolder {
        public static final int STATE_NONE = 0;
        public static final int STATE_CLICKED = 1;
        public static final int STATE_ACTIVE = 2;

        private ImageView image;
        private ImageView circle;
        private ImageView gradients;
        private RelativeLayout layout;
        private FrameLayout iconLayout;

        public ViewHolder(@NonNull View itemView) {
            super(itemView);
            layout = itemView.findViewById(R.id.layout_program);
            layout.setOnClickListener(layoutClickListener);
            image = itemView.findViewById(R.id.imageView_program);
            circle = itemView.findViewById(R.id.imageView_programCircle);
            gradients = itemView.findViewById(R.id.imageView_programGradients);
            iconLayout = itemView.findViewById(R.id.frameLayout_program);
        }

        public void setImageResource(int resourceId) {
            image.setImageResource(resourceId);
        }

        public void setState(int state) {
            switch(state) {
                case STATE_NONE:
                    image.setAlpha(0.5f);
                    stopAnimation();
                    break;

                case STATE_CLICKED:
                    image.setAlpha(1f);
                    stopAnimation();
                    break;

                case STATE_ACTIVE:
                    image.setAlpha(1f);
                    startAnimation();
                    break;
            }
        }

        private void startAnimation() {
            if(cmd.equals(WheelService.CMD_MOVING_PROGRAM)) {
                RotateAnimation rotate = new RotateAnimation(0, 359, Animation.RELATIVE_TO_SELF, 0.5f, Animation.RELATIVE_TO_SELF, 0.5f);
                rotate.setDuration(3000);
                rotate.setInterpolator(new LinearInterpolator());
                rotate.setRepeatCount(Animation.INFINITE);
                gradients.startAnimation(rotate);
                gradients.setVisibility(View.VISIBLE);
            }

            circle.setVisibility(View.VISIBLE);
            iconLayout.setBackgroundColor(Color.BLACK);
        }

        private void stopAnimation() {
            if(cmd.equals(WheelService.CMD_MOVING_PROGRAM)) {
                Animation animation = gradients.getAnimation();

                if (animation != null) {
                    animation.cancel();
                }

                gradients.setVisibility(View.GONE);
            }

            circle.setVisibility(View.GONE);
            iconLayout.setBackgroundColor(Color.TRANSPARENT);
        }

        private View.OnClickListener layoutClickListener = new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                notifyItemChanged(clickedItem);
                clickedItem = getLayoutPosition();
                notifyItemChanged(clickedItem);

                listener.onItemClick(programs.get(clickedItem));
            }
        };
    }
}
