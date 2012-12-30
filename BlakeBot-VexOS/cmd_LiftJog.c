// cmd_LiftJog.c : implementation file
// cmd_LiftSet.c : implementation file
#include "CommandClass.h"
#include "Robot.h"

DefineCommandClass(LiftJog, { 
    int jogValue;
});

static void constructor(va_list argp) {
    self->fields->jogValue = va_arg(argp, int);
    setArgs("%d", self->fields->jogValue);
    require(&Lift);
}

static void initialize() { 
    LiftPosition pos = Lift_getPosition();
    if(self->fields->jogValue > 0) {
        switch(pos) {
            case LiftPosition_Ground: pos = LiftPosition_Trough; break;
            case LiftPosition_Trough: pos = LiftPosition_Descore; break;
            case LiftPosition_Descore: break;
        }
    } else {
        switch(pos) {
            case LiftPosition_Ground: break;
            case LiftPosition_Trough:  pos = LiftPosition_Ground; break;
            case LiftPosition_Descore: pos = LiftPosition_Trough; break;
        }
    }
    Lift_setPosition(pos);
}

static void execute() {
}

static bool isFinished() {
    return Lift_onTarget();
}

static void end() { }

static void interrupted() { }



