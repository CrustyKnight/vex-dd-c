#include "main.h"
#include "lemlib/api.hpp"
#include "api.h"


#define INTAKE_BUTTON DIGITAL_R1
#define CLAMP_BUTTON DIGITAL_A

pros::Motor intake_motor(7, pros::MotorGearset::red);
pros::adi::DigitalOut clamp_piston_a('A');
pros::adi::DigitalOut clamp_piston_b('B');



int intake_on_power = 50; // basically, how fast should the intake run when its on
// 50 is a random guess
bool intake_on_state = false; // true if on, false if off.

// Set the motor power for the intake
void set_intake_power(int8_t power) {
  intake_on_power = power;
}

void intake_toggle() {
  intake_on_state = !intake_on_state;
  if (intake_on_state) {
    intake_motor.move(intake_on_power);
  } else {
    intake_motor.move(0);
  }
}
void intake_on() {
  intake_on_state = true;
  intake_motor.move(intake_on_power);
}
void intake_off() {
  intake_on_state = false;
  intake_motor.move(0);
}

// Intake button R1

void drive_intake_hold(pros::Controller master){
  int intake_state = master.get_digital(INTAKE_BUTTON);
  if (intake_state == 1) {
    intake_on();
  } else {
    intake_off();
  }
}


int previous_B_state = 0;

void drive_intake_toggle(pros::Controller master) {
  int intake_state = master.get_digital(pros::E_CONTROLLER_DIGITAL_B);
  if (intake_state != previous_B_state) { // change
    if (intake_state == 1) {
      intake_toggle();
    }
  }
  previous_B_state = intake_state;
}

void drive_intake(pros::Controller master) {
  drive_intake_hold(master);
}


bool clamp_on_state = false;

void clamp_pistons_set(int value) {
    clamp_piston_a.set_value(value);
    clamp_piston_b.set_value(value);
}

void clamp_engage() {
    clamp_on_state = true;
    clamp_pistons_set(1);
}

void clamp_disengage() {
    clamp_on_state = false;
    clamp_pistons_set(0);
}

void clamp_toggle () {
    if (clamp_on_state) {
        clamp_disengage();
    } else {
        clamp_engage();
    }
}

int previous_clamp_button_state = 0;

void drive_clamp(pros::Controller master) {
    int clamp_state = master.get_digital(CLAMP_BUTTON);
    if (clamp_state != previous_clamp_button_state) {
        if(clamp_state == 1) {
            clamp_toggle();
        }
    }
    previous_clamp_button_state = clamp_state;
}
