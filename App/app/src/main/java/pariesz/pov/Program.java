package pariesz.pov;

import java.util.ArrayList;

import pariesz.pov.dialogs.ExplodingTextDialog;
import pariesz.pov.dialogs.TimerDialog;

public class Program {
    private Class dialogType;
    private int resourceId;
    private int id;

    public Program(int id, int resourceId) {
        this.id = id;
        this.resourceId = resourceId;
    }

    public Program(int id, int resourceId, Class dialogType) {
        this(id, resourceId);
        this.dialogType = dialogType;
    }

    public static final ArrayList PROGRAMS_MOVING = new ArrayList(){{
        add(new Program(0, R.drawable.ic_off));
        add(new Program(1, R.drawable.ic_timer, TimerDialog.class));
        add(new Program(2, R.drawable.program_masacritica));
        add(new Program(3, R.drawable.program_fist));
        add(new Program(4, R.drawable.program_exploding_text, ExplodingTextDialog.class));
        add(new Program(5, R.drawable.program_nyancat));
        add(new Program(6, R.drawable.program_poo));
        add(new Program(7, R.drawable.program_velocity));
        add(new Program(8, R.drawable.program_hamster));
        add(new Program(9, R.drawable.program_portal));
        add(new Program(10, R.drawable.program_rays));
        add(new Program(11, R.drawable.program_shooting_stars));
        add(new Program(12, R.drawable.program_spiral));
        add(new Program(13, R.drawable.program_la_pandora));
        add(new Program(14, R.drawable.program_radioactive));
    }};

    public static final ArrayList PROGRAMS_STATIONARY = new ArrayList(){{
        add(new Program(0, R.drawable.ic_off));
        add(new Program(1, R.drawable.ic_timer, TimerDialog.class));
        add(new Program(2, R.drawable.program_pulse));
        add(new Program(3, R.drawable.program_rainbow));
    }};

    public int getResourceId() {
        return resourceId;
    }

    public Class getDialogType() {
        return dialogType;
    }

    public int getId() {
        return id;
    }
}
