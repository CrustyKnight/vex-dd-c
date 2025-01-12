#include "main.h"
#include "lemlib/api.hpp"
#include "control.hpp"
#include "clamp.hpp"
#include "config.hpp"
#include "intake.hpp"
#include "pros/misc.h"

pros::Motor ext(8, pros::MotorGearset::red);
pros::Controller ic(pros::E_CONTROLLER_MASTER);

/*
#define DIGITAL_L1 pros::E_CONTROLLER_DIGITAL_L1
#define DIGITAL_L2 pros::E_CONTROLLER_DIGITAL_L2
#define DIGITAL_R1 pros::E_CONTROLLER_DIGITAL_R1
#define DIGITAL_R2 pros::E_CONTROLLER_DIGITAL_R2
#define DIGITAL_UP pros::E_CONTROLLER_DIGITAL_UP
#define DIGITAL_DOWN pros::E_CONTROLLER_DIGITAL_DOWN
#define DIGITAL_LEFT pros::E_CONTROLLER_DIGITAL_LEFT
#define DIGITAL_RIGHT pros::E_CONTROLLER_DIGITAL_RIGHT
#define DIGITAL_X pros::E_CONTROLLER_DIGITAL_X
#define DIGITAL_B pros::E_CONTROLLER_DIGITAL_B
#define DIGITAL_Y pros::E_CONTROLLER_DIGITAL_Y
#define DIGITAL_A pros::E_CONTROLLER_DIGITAL_A
*/

class Button {
 public:
  pros::controller_digital_e_t button;
  Button(pros::controller_digital_e_t);
  int previous_state;
  int current_state;
  void update(pros::Controller);
  void update();
  bool just_pressed();
  bool held() { return current_state == 1; };
  bool unheld() { return current_state != 1; };
};
Button::Button(pros::controller_digital_e_t b) {
  button = b;
  current_state = 0;
}
void Button::update(pros::Controller controller) {
  previous_state = current_state;
  current_state = controller.get_digital(button);
}
void Button::update() {
  pros::Controller ic(pros::E_CONTROLLER_MASTER);
  this->update(ic);
}
bool Button::just_pressed() {
  return (previous_state != current_state) && (current_state == 1);
}

Button intake_button(INTAKE_BUTTON);
Button intake_reverse_button(INTAKE_REVERSE_BUTTON);
Button clamp_up_button(CLAMP_UP_BUTTON);
Button clamp_down_button(CLAMP_DOWN_BUTTON);

int ext_on = PEAK_ON_DIRECTION * PEAK_ON_POWER;

// Intake button R1

void drive_intake_hold(pros::Controller master) {
  intake_button.update(master);
  intake_reverse_button.update(master);
  if (intake_button.held()) {
    intake::run_forward(100);
  } else if (intake_reverse_button.held()) {
    intake::run_backward(100);
  } else {
    intake::off();
  }
}

void drive_intake(pros::Controller master) {
  drive_intake_hold(master);
}

int level = 0;
int prev_forward = 0;
int prev_reverse = 0;
int going = 0;
void drive_extend_levels(pros::Controller master) {
  ext.set_encoder_units(pros::E_MOTOR_ENCODER_ROTATIONS);
  int forward = master.get_digital(pros::E_CONTROLLER_DIGITAL_UP);
  int reverse = master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN);

  if (std::floor(ext.get_actual_velocity()) == 0) {
    going = 0;
  } else {
    going = 1;
  }

  if ((going == 1) || (forward == prev_forward && reverse == prev_reverse) /*|| (level == 2 && forward == 1) || (level == 0 && reverse == 1)*/) {
    return;
  }
  double unit = LINEAR_SLIDE_SECTION_TEETH / PEAK_GEAR_TEETH;

  if (forward == 1) {
    level--;
    ext.move_relative(7 * unit, 100);
    going = 1;
  } else if (reverse == 1) {
    level++;
    ext.move_relative(-7 * unit, 100);
    going = 1;
  }
  prev_forward = forward;
  prev_reverse = reverse;
}

Button extend_button(DIGITAL_X);
Button extend_back_button(DIGITAL_B);
void drive_extend_test(pros::Controller master) {
  extend_button.update(master);
  extend_back_button.update(master);
  if (extend_button.held()) {
    ext.move(100);
  } else if (extend_back_button.held()) {
    ext.move(-100);
  } else {
    ext.move(0);
  }
}

void drive_clamp_up_down(pros::Controller master) {
  clamp_up_button.update(master);
  clamp_down_button.update(master);
  if (clamp_up_button.just_pressed())
    clamp::disengage();
  else if (clamp_down_button.just_pressed())
    clamp::engage();
}

void drive_clamp(pros::Controller master) {
  drive_clamp_up_down(master);
}
