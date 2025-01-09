#include "main.h"
#include "lemlib/api.hpp"
#include "control.hpp"
#include "clamp.hpp"
#include "intake.hpp"

#define INTAKE_BUTTON DIGITAL_R1
#define INTAKE_REVERSE_BUTTON DIGITAL_R2
#define CLAMP_BUTTON DIGITAL_A
#define CLAMP_UP_BUTTON DIGITAL_UP
#define CLAMP_DOWN_BUTTON DIGITAL_DOWN
#define CLAMP_ON 1
#define CLAMP_OFF 0
#define CLAMP_PISTON_A_PORT 'H'
#define CLAMP_PISTON_B_PORT 'G'

// pros::Motor intake_motor(7, pros::MotorGearset::green);
pros::Motor ext(8, pros::MotorGearset::red);

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
bool Button::just_pressed() {
  return (previous_state != current_state) && (current_state == 1);
}

Button intake_button(INTAKE_BUTTON);
Button intake_reverse_button(INTAKE_REVERSE_BUTTON);
Button clamp_up_button(CLAMP_UP_BUTTON);
Button clamp_down_button(CLAMP_DOWN_BUTTON);

int ext_on = -100;

// Intake button R1

void drive_intake_hold(pros::Controller master) {
  intake_button.update(master);
  intake_reverse_button.update(master);
  if (intake_button.held()) {
    run_intake_forward(100);
  } else if (intake_reverse_button.held()) {
    run_intake_backward(100);
  } else {
    intake_off();
  }
}

void drive_intake(pros::Controller master) {
  drive_intake_hold(master);
}

int level = 0;
int prev_forward = 0;
int prev_reverse = 0;
int going = 0;
void drive_extend(pros::Controller master) {
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
  double unit = 19.0 / 12.0;

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

int previous_clamp_button_state = 0;

void drive_clamp_toggle(pros::Controller master) {
  int clamp_state = master.get_digital(CLAMP_BUTTON);
  if (clamp_state != previous_clamp_button_state) {
    if (clamp_state == 1) {
      clamp_toggle();
    }
  }
  previous_clamp_button_state = clamp_state;
}

void drive_clamp_up_down(pros::Controller master) {
  clamp_up_button.update(master);
  clamp_down_button.update(master);
  if (clamp_up_button.just_pressed())
    clamp_disengage();
  else if (clamp_down_button.just_pressed())
    clamp_engage();
}

void drive_clamp(pros::Controller master) {
  drive_clamp_up_down(master);
}
