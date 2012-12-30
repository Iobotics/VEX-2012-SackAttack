// Robot.c : implementation file
#include "Robot.h"
#include "Hardware.h"
#include "API.h"

DefineRobot(&Drive, &Lift, &Intake, &Pivot);

Joystick*    _joystick;
PowerScaler* _scaler;

static LCD* lcd;
static PowerExpander* expand;
static DigitalIn* autoButton;

static void constructor() {
    SetDebugInfo(true);

    _joystick = Joystick_new(1);
    _scaler   = PowerScaler_new("Default");
    PowerScaler_addPoint(_scaler, 0.7, 0.3);

    lcd    = LCD_new("Main LCD", UARTPort_1);
    expand = PowerExpander_new("Expander", PowerExpanderType_Rev_A1, AnalogPort_1);
    PowerExpander_setPWMPorts(expand, PWMPort_5, PWMPort_6, PWMPort_7, PWMPort_8);
    autoButton = DigitalIn_newBump("auto button", DigitalPort_2);
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
    Button_whenPressed(
        Joystick_getButton(_joystick, JoystickHand_Left, JoystickButtonType_Up),
        Command_new(&LiftHome));


    // intake control buttons //
    Button_whileHeld(
        Joystick_getButton(_joystick, JoystickHand_Right, JoystickButtonType_Top),
        Command_new(&IntakeSet, IntakeDirection_Suck));
    Button_whileHeld(
        Joystick_getButton(_joystick, JoystickHand_Right, JoystickButtonType_Bottom),
        Command_new(&IntakeSet, IntakeDirection_Blow));

    // pivot control //
    Button_whileToggled(
        Joystick_getButton(_joystick, JoystickHand_Right, JoystickButtonType_Left),
        Command_new(&PivotSet, PivotPosition_Up));

    // drive testing controls //
    Button_whenPressed(
        Joystick_getButton(_joystick, JoystickHand_Right, JoystickButtonType_Up),
        Command_new(&AutoDrive, 10.0));
    Button_whenPressed(
        Joystick_getButton(_joystick, JoystickHand_Right, JoystickButtonType_Right),
        Command_new(&AutoTurn, 90.0));        
}

// TODO: add user code here









