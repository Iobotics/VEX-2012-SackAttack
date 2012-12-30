// cmd_AutoDrive.c : implementation file
#include "CommandClass.h"
#include "Robot.h"

DefineCommandClass(AutoDrive, { 
    float distance;
});

static void constructor(va_list argp) {
    self->fields->distance = (float) va_arg(argp, double);    
    setArgs("%f", self->fields->distance);
    require(&Drive);
}

static void initialize() { 
    Drive_startMove(self->fields->distance);
}

static void execute() { }

static bool isFinished() {
    return Drive_isDone();
}

static void end() { 
    Drive_end();
    Drive_setPower(0, 0);
}

static void interrupted() { 
    end();
}
