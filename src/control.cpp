#include "main.h"
#include "peak.hpp"
#include "lemlib/api.hpp"
#include "control.hpp"
#include "clamp.hpp"
#include "config.hpp"
#include "intake.hpp"
#include "pros/misc.h"
#include "pros/misc.hpp"
#include "pros/motor_group.hpp"

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

#ifdef _DEBUG_
Button pid_run_lateral_test_button(DEBUG_LATERAL_TEST_BUTTON);
Button pid_run_angular_test_button(DEBUG_ANGULAR_TEST_BUTTON);

void pidTestingAngular() {
  chassis.setPose(0, 0, 0);
  chassis.turnToHeading(90, 100000);
}

void pidTestingLateral() {
  chassis.setPose(0,0,0);
  chassis.moveToPose(24, 24, -90, 10000, {.horizontalDrift = 50, .lead = 0.6, .maxSpeed = 40}, false);
  /*
  chassis.setPose(0, 0, 0);
  chassis.moveToPoint(0, 24, 5000, {.forwards = true, .maxSpeed = 30}, false);
  pros::delay(100);
  chassis.turnToPoint(24, 24, 5000, {.maxSpeed = 30}, false);
  pros::delay(100);
  chassis.moveToPoint(24, 24, 5000, {.maxSpeed = 30}, false);
  pros::delay(100);
  chassis.turnToPoint(24, 0, 5000, {.maxSpeed = 30}, false);
  pros::delay(100);
  chassis.moveToPoint(24, 0, 5000, {.maxSpeed = 30}, false);
  pros::delay(100);
  chassis.turnToPoint(0, 0, 5000, {.maxSpeed = 30}, false);
  pros::delay(100);
  chassis.moveToPoint(0, 0, 5000, {.maxSpeed = 30}, false);
  */
}

void drivePIDTest(pros::Controller master) {
  pid_run_lateral_test_button.update(master);
  pid_run_angular_test_button.update(master);
  if (pid_run_lateral_test_button.just_pressed())
    pidTestingLateral();
  if (pid_run_angular_test_button.just_pressed())
    pidTestingAngular();
}
#endif

int ext_on = PEAK_ON_DIRECTION * PEAK_ON_POWER;

// Intake button R1

void drive_intake_hold(pros::Controller master) {
  intake_button.update(master);
  intake_reverse_button.update(master);
  if (intake_button.held()) {
    intake::run_forward(INTAKE_INIT_POWER);
  } else if (intake_reverse_button.held()) {
    intake::run_backward(INTAKE_INIT_POWER);
  } else {
    intake::off();
  }
}

void drive_intake(pros::Controller master) {
  drive_intake_hold(master);
}

// Button peak_button(DIGITAL_X);
// Button peak_back_button(DIGITAL_B);
// void drive_extend_test(pros::Controller master) {
//   peak_button.update(master);
//   peak_back_button.update(master);
//   if (peak_button.held()) {
//     ext.move(100);
//   } else if (peak_back_button.held()) {
//     ext.move(-100);
//   } else {
//     ext.move(0);
//   }
// }

int level = 0;
int prev_forward = 0;
int prev_reverse = 0;
int going = 0;
Button peak_rest_button(PEAK_REST_BUTTON);
Button peak_mogo_button(PEAK_MOGO_BUTTON);
Button peak_alliance_button(PEAK_ALLIANCE_WALL_STAKE_BUTTON);
Button peak_wall_button(PEAK_HIGH_WALL_BUTTON);
Button peak_manual_up_button(PEAK_MANUAL_UP_BUTTON);
Button peak_manual_down_button(PEAK_MANUAL_DOWN_BUTTON);
Button peak_stop_it_button(DIGITAL_Y);
void drive_peak_levels(pros::Controller master) {
  try {
    peak_rest_button.update(master);
    peak_mogo_button.update(master);
    peak_alliance_button.update(master);
    peak_wall_button.update(master);
    peak_manual_up_button.update(master);
    peak_manual_down_button.update(master);
    peak_stop_it_button.update(master);

    if (peak_rest_button.just_pressed()) {
      peak::raise_to_level(0);
    } else if (peak_mogo_button.just_pressed()) {
      peak::raise_to_level(1);
    } else if (peak_alliance_button.just_pressed()) {
      peak::raise_to_level(2);
    } else if (peak_wall_button.just_pressed()) {
      peak::raise_to_level(3);
    } else if (peak_manual_up_button.held() && peak_manual_down_button.held()) {
      peak::raise_to_level(-3);
    } else if (peak_manual_down_button.held()) {
      peak::raise_to_level(-1);
    } else if (peak_manual_up_button.held()) {
      peak::raise_to_level(-2);
    } else if (peak_stop_it_button.just_pressed()) {
      peak::raise_to_level(-3);
    }
  } catch (const std::invalid_argument& e) {
    // do nothing;
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

void drive_arcade(pros::Controller master,
                  pros::MotorGroup* lm, pros::MotorGroup* rm) {
  int drive = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);   // Gets amount forward/backward from left joystick
  int turn = -master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);  // Gets the turn left/right from right joystick
  lm->move(drive - turn);                                            // Sets left motor voltage
  rm->move(drive + turn);                                            // Sets right motor voltage
}
