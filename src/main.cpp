#include "config.hpp"
#include "lemlib/api.hpp"  // IWYU pragma: keep
#include "lemlib/chassis/chassis.hpp"
#include "lemlib/chassis/odom.hpp"
#include "auton.hpp"
#include "main.h"
#include "peak.hpp"
#include "display.h"
#include <math.h>
#include "control.hpp"
#include "intake.hpp"
#include "pros/motors.h"
#include "auton.hpp"
#include "clamp.hpp"

// Important Note: This file has all of our drivetrain and remote control-related code.

// LemLib setup
// TODO
// Setting up of drivetrain sides: side_motors({low_1, high, low 2})
// Technically, order of motors on one side doesn't matter, as they spin in the same direction.
pros::MotorGroup left_motors({-4, -5, -6}, pros::MotorGearset::green);
pros::MotorGroup right_motors({13, 14, 15}, pros::MotorGearset::green);

// Setup of drivetrain, IMU, and odometry sensors (just our IMU for now): using lemlib for odometry functionality.
lemlib::Drivetrain drivetrain(&left_motors, &right_motors, 12.625, lemlib::Omniwheel::NEW_325, 355.55555, 3);
pros::Imu imu(11);
lemlib::OdomSensors sensors(nullptr, nullptr, nullptr, nullptr, &imu);

// kP, kI, kD, anti-windup, small error range, small error range timeout,
// large error range, large error range timeout, max acceleration (slew)
// lemlib::ControllerSettings lateral_controller(10, 0, 3, 3, 1, 100, 3, 500, 20);
// lemlib::ControllerSettings angr_controller(2,  0,  10, 3, 1, 100, 3, 500, 0);
lemlib::ControllerSettings lateral_controller_lvl1(14, 0.2, 20, 2, 0.5, 0, 0, 0, 0);
lemlib::ControllerSettings angular_controller_lvl1(10, 0.5, 27, 2, 0.5, 100, 0, 0, 0);

// TODO: tune PID for each peak level :skull:

lemlib::PID lvl0L(15, 0.5, 20, 0, false);
lemlib::PID lvl0A(15, 0.5, 20, 0, false);
lemlib::PID lvl1L(15, 0.5, 20, 0, false);
lemlib::PID lvl1A(15, 0.5, 20, 0, false);
lemlib::PID lvl2L(15, 0.5, 20, 0, false);
lemlib::PID lvl2A(15, 0.5, 20, 0, false);

lemlib::PID levels[3][2] = {{lvl0L, lvl0A}, {lvl1L, lvl1A}, {lvl2L, lvl2A}};

// Creating lemlib chassis object for enhanced drivetrain functionality with our drivetrain.
lemlib::Chassis chassis(drivetrain, lateral_controller_lvl1, angular_controller_lvl1, sensors);
// Creating expo drive curve
lemlib::ExpoDriveCurve driveCurve(5.00, 12.00, 1.132);

// hack: set PID by adjusting the pointer value
void set_PID(int level) {
  lemlib::Chassis *c = &chassis;
  // this might work.
  // magic from: https://a.opnxng.com/exchange/stackoverflow.com/questions/75840140/why-assignment-operator-implicitly-deleted-for-const-members-in-c
  chassis.lateralPID.~PID();
  //new (&chassis.lateralPID) lemlib::PID(15, 0.5, 20, 0, false);

  //TODO tune these PID constants
  switch(level){
    case 0:
      new (&chassis.lateralPID) lemlib::PID(15, 0.5, 20, 0, false);
    break;
    case 1:
      new (&chassis.lateralPID) lemlib::PID(15, 0.5, 20, 0, false);
    break;
    case 2:
      new (&chassis.lateralPID) lemlib::PID(15, 0.5, 20, 0, false);
    break;
    case 3:
      new (&chassis.lateralPID) lemlib::PID(15, 0.5, 20, 0, false);
    break;
  }
}

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
  pros::lcd::initialize();
  static bool pressed = false;
  pressed = !pressed;
  if (pressed) {
    pros::lcd::set_text(0, "I was pressed!");
  } else {
    pros::lcd::clear_line(2);
  }
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
  intake::init();
  display_init();
  peak::init();
  chassis.calibrate();
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */

void autonomous() {
// DEFENSIVE
#ifdef _ALLIANCE_AUTON_
  peak::raise_to_level(__PEAK_ARG_MOGO);
  pros::delay(1000);
  intake::run_forward(INTAKE_INIT_POWER);
  pros::delay(1000);
  chassis.moveToPoint(0, 57, 10000);  // go forward & run into the ladder.
  // ^ this is a guess. refine this.
#endif
#ifdef _MOGO_AUTON_
  chassis.setPose(0, 0, 180);
  peak::raise_to_level(__PEAK_ARG_MOGO);
  chassis.moveToPoint(0, 24, 30000, {.forwards = false, .maxSpeed = 40, .minSpeed = 20}, false);
  clamp::engage();
  chassis.moveToPoint(0, 27, 5000, {.forwards = false, .maxSpeed = 20}, false);
  pros::delay(100);
  intake::run_forward(120);
  pros::delay(2000);
  intake::off();
  // chassis.moveToPose(57, 24, -45, 10000);
#endif
#ifdef _ALLIANCE_MOGO_AUTON_
  // If we do alliance & get mogo, put that code here.
#endif
#ifdef _SKILLS_AUTON_
  peak::raise_to_level(__PEAK_ARG_MOGO);
  pros::delay(1500);
  intake::run_forward(120);
  pros::delay(2000);
  intake::off();
  chassis.setPose(0, 0, 0);
  chassis.moveToPoint(0, 15.5, 2000);
  // chassis.turnToHeading(90, 5000);
  pros::delay(3000);
  chassis.cancelAllMotions();
  right_motors.move(50);
  left_motors.move(-50);
  pros::delay(595);
  left_motors.move(0);
  right_motors.move(0);
  right_motors.move(-50);
  left_motors.move(-50);
  pros::delay(3300);
  clamp::engage();
  pros::delay(500);
  left_motors.move(0);
  right_motors.move(0);
  right_motors.move(-50);
  left_motors.move(50);
  pros::delay(300);
  left_motors.move(-50);
  right_motors.move(-50);
  pros::delay(4000);
  left_motors.move(0);
  right_motors.move(0);
  // autonSkills(&chassis);
#endif
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
  pros::Controller master(pros::E_CONTROLLER_MASTER);
#ifdef _DEBUG_AUTON_
  autonomous();
#endif
#ifdef _DEBUG_
  master.set_text(1, 4, "DEBUG");
  //pidTestingAngular();
  pidTestingLateral();
#endif
  while (true) {
    // Arcade control scheme
    drive_arcade(master, &left_motors, &right_motors);
    // pros::delay(10);  // Run for 20 ms then update
    drive_intake(master);
    drive_clamp(master);
    drive_peak_levels(master);
    pros::delay(10);
  }
}
