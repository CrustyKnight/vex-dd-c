#include "main.h"
#include "lemlib/api.hpp"
#include "api.h"


#define INTAKE_BUTTON DIGITAL_R1
#define INTAKE_REVERSE_BUTTON DIGITAL_R2
#define CLAMP_BUTTON DIGITAL_A
#define CLAMP_UP_BUTTON DIGITAL_UP
#define CLAMP_DOWN_BUTTON DIGITAL_DOWN
#define CLAMP_ON 1
#define CLAMP_OFF 0

pros::Motor intake_motor(7, pros::MotorGearset::green);
pros::adi::DigitalOut clamp_piston_a('H');
pros::Motor ext(8, pros::MotorGearset::red);

//pros::adi::DigitalOut clamp_piston_b('B');



int intake_on_power = -100; // basically, how fast should the intake run when its on
// 50 is a random guess
bool intake_on_state = false; // true if on, false if off.

int ext_on = -100;


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
  int intake_backward_state = master.get_digital(INTAKE_REVERSE_BUTTON);
  if (intake_state == 1) {
    set_intake_power(100);
    intake_on();
  } else if (intake_backward_state == 1) {
    set_intake_power(-100);
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


int level = 0;
int prev_forward = 0;
int prev_reverse = 0;
int going = 0;
void drive_extend(pros::Controller master)
{
	ext.set_encoder_units(pros::E_MOTOR_ENCODER_ROTATIONS);
	int forward = master.get_digital(pros::E_CONTROLLER_DIGITAL_UP);
	int reverse = master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN);

	if ((going = 0) && (forward == prev_forward && reverse == prev_reverse) || ((level == 0 && reverse == 1) || (level == 2 && forward == 1))){
		going = 1;
		return;
	}
	double unit = 19.0/12.0;


	if (reverse == 1){
		level--;
		ext.move_relative(unit, 100);
	}
	else if (forward == 1){
		level++;
		ext.move_relative(-unit, 100);
	}
	going = 0;
	prev_forward = forward;
	prev_reverse = reverse;


}


bool clamp_on_state = false;

void clamp_pistons_set(int value) {
    clamp_piston_a.set_value(value);
    //clamp_piston_b.set_value(value);
}

void clamp_engage() {
    clamp_on_state = true;
    clamp_pistons_set(CLAMP_ON);
}

void clamp_disengage() {
    clamp_on_state = false;
    clamp_pistons_set(CLAMP_OFF);
}

void clamp_toggle () {
    if (clamp_on_state) {
        clamp_disengage();
    } else {
        clamp_engage();
    }
}

int previous_clamp_button_state = 0;

void drive_clamp_toggle(pros::Controller master) {
    int clamp_state = master.get_digital(CLAMP_BUTTON);
    if (clamp_state != previous_clamp_button_state) {
        if(clamp_state == 1) {
            clamp_toggle();
        }
    }
    previous_clamp_button_state = clamp_state;
}

int previous_clamp_up_button_state = 0;
int previous_clamp_down_button_state = 0;
void drive_clamp_up_down(pros::Controller master) {
  int clamp_up_state = master.get_digital(CLAMP_UP_BUTTON);
  int clamp_down_state = master.get_digital(CLAMP_DOWN_BUTTON);
  if (clamp_up_state != previous_clamp_up_button_state && clamp_up_state == 1) {
    clamp_disengage();
  } else if (clamp_down_state != previous_clamp_down_button_state && clamp_down_state == 1) {
    clamp_engage();
  }
  previous_clamp_up_button_state = clamp_up_state;
  previous_clamp_down_button_state = clamp_down_state;
}

void drive_clamp(pros::Controller master) {
  drive_clamp_up_down(master);
}
