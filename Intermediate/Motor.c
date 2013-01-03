// Motor.c : implementation file
#include "Main.h"
#include "Motor.h"

void SetDrive(int left, int right) {
    SetMotor(driveL1, -left);
    SetMotor(driveL2, left);
    SetMotor(driveL3, left);                 //change directions
    SetMotor(driveR1, right);
    SetMotor(driveR2, -right);
    SetMotor(driveR3, right);
}

void SetArm(int pwr) {
    SetMotor(armL, pwr);
    SetMotor(armR, -pwr);
}

void SetIntake(int pwr) {
    SetMotor(intake1, pwr);
    SetMotor(intake2, -pwr);
}












