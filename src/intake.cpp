#include "main.h"
#include "intake.hpp"
#define INTAKE_ON_DIRECTION 1

pros::Motor intake_m(7, pros::MotorGearset::green);

int intake_power = -100;    // basically, how fast should the intake run when its on
bool intake_state = false;  // true if on, false if off.
int intake_direction = INTAKE_ON_DIRECTION;

// Set the motor power for the intake
void set_intake_power(int power) {
  intake_power = power;
}

void intake_on() {
  intake_state = true;
  intake_m.move(intake_power * intake_direction);
}
void intake_off() {
  intake_state = false;
  intake_m.move(0);
}

void run_intake_forward(int power) {
  set_intake_power(power);
  intake_direction = INTAKE_ON_DIRECTION;
  intake_on();
}
void run_intake_backward(int power) {
  set_intake_power(power);
  intake_direction = INTAKE_ON_DIRECTION * -1;
  intake_on();
}

//In theory, this should only require pulling a donut for 1.2 seconds.
void pull_up_donut(int power){ 
    int time = 0
    while(time < 1200){
        intake_m.move(power);
        pros::delay(200);
        time += 200;
    }
}

// TODO make intake_init to set motor encoder units, and intake_eat_ring to eat
// a ring (turn the motor a specific amount of times)
