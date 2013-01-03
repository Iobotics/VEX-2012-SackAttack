// Robot.c : implementation file
#include "Robot.h"
#include "Hardware.h"

DefineRobot(&Drive, &Lift, &Intake);

Joystick*    _joystick;
PowerScaler* _scaler;

static LCD* lcd;
static PowerExpander* expand;

static void constructor() {
    _joystick = Joystick_new(1);
    _scaler   = PowerScaler_new("Default");
    PowerScaler_addPoint(_scaler, 0.7, 0.3);

    lcd    = LCD_new("Main LCD", UARTPort_1);
    expand = PowerExpander_new("Expander", PowerExpanderType_Rev_A1, AnalogPort_8);
}  

static void initialize() { 
    VexOS_setupStandardUI();

    // lift control buttons //
    Button_whenPressed(
        Joystick_getButton(_joystick, JoystickHand_Left, JoystickButtonType_Bottom),
        Command_new(&LiftJog, -1));
    Button_whenPressed(
        Joystick_getButton(_joystick, JoystickHand_Left, JoystickButtonType_Top),
        Command_new(&LiftJog, 1));

    // intake control buttons //
    Button_whileHeld(
        Joystick_getButton(_joystick, JoystickHand_Right, JoystickButtonType_Bottom),
        Command_new(&IntakeSet, IntakeDirection_Suck));
    Button_whileHeld(
        Joystick_getButton(_joystick, JoystickHand_Right, JoystickButtonType_Top),
        Command_new(&IntakeSet, IntakeDirection_Blow));
}

// TODO: add user code here






