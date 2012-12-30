// sys_Pivot.c : implementation file
#include "Subsystem.h"
#include "Hardware.h"
#include "Robot.h"

DefineSubsystem(Pivot);

static DigitalOut* valve;
//static DebugValue* debug;

static void constructor() {
    valve = DigitalOut_newPneumaticValve("pivot valve", DigitalPort_1);
    //debug = DebugValue_new("pivot",  DebugValueType_String);
}

static void initialize() { 
    setDefaultCommand(Command_new(&PivotSet, PivotPosition_Down));
}

// TODO: add user code here

void Pivot_setPosition(PivotPosition pivot) {
    switch(pivot) {
        case PivotPosition_Up:
            DigitalOut_set(valve, true);
            break;
        case PivotPosition_Down:
            DigitalOut_set(valve, false);
            break;
    }
    //DebugValue_set(debug, (pivot == PivotPosition_Up)? "Up": "Down");
}



