#include "main.h"
#include "intake.hpp"
#include "config.hpp"
#include "pros/motors.h"

namespace intake {
int power = 100;
int direction = INTAKE_ON_DIRECTION;
bool state = false;
pros::Motor motor(7, pros::MotorGearset::green);
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
void eat_donut(float dist) {
  motor.move_relative(50, 50);
  lemlib::Pose currentPose = chassis.getPose(true);
  float new_x = (float)(cos(currentPose.theta) * dist);  // Changed sin to cos; x is cos no? (Debangshu)
  float new_y = (float)(sin(currentPose.theta) * dist);
  chassis.moveToPoint(new_x, new_y, 500);  // you might need to tune this
  chassis.moveToPoint(currentPose.x, currentPose.y, 600, {.forwards = false});
}

void eat_donut() {  // default distance, made this up, should probably be changed.
  eat_donut(5);
}
void digest_donut() {
  double revs = -0.6 * INTAKE_RATIO;
  motor.move_relative(revs, 200);
}

void jammed_handler(void* param) {
  // TODO return true if intake is jammed.
  // TODO probably have a function that runs always, looking for jamming,
  // and if it jams undo for like some amount of time, then continue in the same
  // direction with the same power.
  while (true) {
    int power = motor.get_power();
    int velocity = motor.get_actual_velocity();
    if (power > 50 && velocity < 10) {
      // WERE JAMMED!!!!
      motor.move(0);
      motor.move_relative(-30, 100);
      pros::delay(500);
      on();
    }
    pros::delay(250);
  }
}

void init() {
  motor.set_encoder_units(MOTOR_ENCODER_ROTATIONS);
  pros::Task jam_task(jammed_handler);
}

}  // namespace intake
