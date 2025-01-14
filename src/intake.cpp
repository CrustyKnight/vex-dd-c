#include "main.h"
#include "intake.hpp"
#include "config.hpp"
#include "pros/motors.h"

namespace intake {
int power = 100;
int direction = INTAKE_ON_DIRECTION;
bool state = false;
pros::Motor motor(7, pros::MotorGearset::green);
void init() {
  motor.set_encoder_units(MOTOR_ENCODER_ROTATIONS);
}
void set_power(int p) { power = p; }
void on() {
  state = true;
  motor.move(power * direction);
}
void off() {
  state = false;
  motor.move(0);
}

void run_forward(int p) {
  set_power(p);
  direction = INTAKE_ON_DIRECTION;
  on();
}
void run_backward(int p) {
  set_power(p);
  direction = INTAKE_ON_DIRECTION * -1;
  on();
}
void eat_donut() {
  motor.move_relative(50, 50);
}
void digest_donut() {
  double revs = 0.6 * INTAKE_RATIO;
  motor.move_relative(revs, 200);
}

}  // namespace intake
