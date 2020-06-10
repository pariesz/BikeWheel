package pariesz.pov;

import android.graphics.Color;
import android.util.Log;
import android.view.*;
import android.view.animation.*;
import android.widget.*;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatDialogFragment;
import androidx.fragment.app.FragmentActivity;
import androidx.recyclerview.widget.RecyclerView;
import java.util.ArrayList;

public class ProgramsRecyclerViewAdaptor extends RecyclerView.Adapter<ProgramsRecyclerViewAdaptor.ViewHolder> {
    private int clickedItem = -1;
    private int activeItem = -1;

    private static final String TAG = "ProgramsRecyclerViewAda";

    private FragmentActivity activity;
    private ArrayList<Program> programs;

    private final OnItemClickListener listener;
    private boolean rotateAnimate;

    public interface OnItemClickListener {
        void onItemClick(Program program);
    }

    public ProgramsRecyclerViewAdaptor(FragmentActivity activity, ArrayList<Program> programs, OnItemClickListener listener, boolean rotateAnimate) {
        this.activity = activity;
        this.programs = programs;
        this.listener = listener;
        this.rotateAnimate = rotateAnimate;
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

        holder.setImageResource(program.getResourceId());
        holder.setDialogType(program.getDialogType());

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

            if(program.getId() == id) {
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

        private Class dialogType;

        public ViewHolder(@NonNull View itemView) {
            super(itemView);
            layout = itemView.findViewById(R.id.layout_program);
            layout.setOnClickListener(layoutClickListener);
            layout.setOnLongClickListener(layoutLongClickListener);
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
            if(rotateAnimate) {
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
            if(rotateAnimate) {
                Animation animation = gradients.getAnimation();
                if (animation != null) animation.cancel();
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


        private View.OnLongClickListener layoutLongClickListener = new View.OnLongClickListener() {

            @Override
            public boolean onLongClick(View v) {
                Log.d(TAG, "onLongClick");

                if(dialogType != null) {
                    try {
                        AppCompatDialogFragment dialog = (AppCompatDialogFragment)dialogType.getConstructor().newInstance();
                        dialog.show(activity.getSupportFragmentManager(),"program dialog");
                        return true;
                    } catch (Exception e) {
                        Log.e(TAG, "Error constructing dialog: " + dialogType.getName(), e);
                    }
                }
                return false;
            }
        };

        public void setDialogType(Class dialogType) {
            this.dialogType = dialogType;
        }
    }
}
