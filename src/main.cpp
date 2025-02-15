#include "config.hpp"
#include "lemlib/api.hpp"  // IWYU pragma: keep
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

// Cooked ahh hack (does not work)
// class RightMotorGroup : public virtual pros::MotorGroup {
//  public:
//   virtual std::int32_t move(std::int32_t voltage) const {
//     std::printf("I was moved!\n");
//     return MotorGroup::move(0);
//   }
// };
// RightMotorGroup::MotorGroup cooked_r_motors({13, 14, 15}, pros::MotorGearset::green);

// LemLib setup
// TODO
// Setting up of drivetrain sides: side_motors({low_1, high, low 2})
// Technically, order of motors on one side doesn't matter, as they spin in the same direction.
pros::MotorGroup left_motors({-4, -5, -6}, pros::MotorGearset::green);
pros::MotorGroup right_motors({13, 14, 15}, pros::MotorGearset::green);

// Setup of drivetrain, IMU, and odometry sensors (just our IMU for now): using lemlib for odometry functionality.
lemlib::Drivetrain drivetrain(&left_motors, &right_motors, 12.625, lemlib::Omniwheel::NEW_325, 355.55555, 3);
pros::Imu imu(10);
lemlib::OdomSensors sensors(nullptr, nullptr, nullptr, nullptr, &imu);

// kP, kI, kD, anti-windup, small error range, small error range timeout,
// large error range, large error range timeout, max acceleration (slew)
// lemlib::ControllerSettings lateral_controller(10, 0, 3, 3, 1, 100, 3, 500, 20);
lemlib::ControllerSettings lateral_controller(14, 0.5, 20, 0, 0, 0, 0, 0, 0);
// lemlib::ControllerSettings angr_controller(2,  0,  10, 3, 1, 100, 3, 500, 0);
lemlib::ControllerSettings angular_controller(17, 0.5, 20, 1, 0.5, 100, 0, 0, 0);

// Creating lemlib chassis object for enhanced drivetrain functionality with our drivetrain.
lemlib::Chassis chassis(drivetrain, lateral_controller, angular_controller, sensors);
// Creating expo drive curve
lemlib::ExpoDriveCurve driveCurve(5.00, 12.00, 1.132);
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

void lateral_move(int distance, int timeout) {
  // lemlib::update(); // update the pose
  lemlib::Pose currentPose = chassis.getPose(true);
  float new_x = (int)(cos(currentPose.theta) * distance);  // Changed sin to cos; x is cos no? (Debangshu)
  float new_y = (int)(sin(currentPose.theta) * distance);
  chassis.moveToPoint(new_x, new_y, timeout);
}

// TODO: we need to find out if negative degrees and positive degrees are clockwise our counterclockwise for the purpose of our robot.
void angular_turn(int degrees, int timeout) {
  // lemlib::update(); // update the pose
  lemlib::Pose currentPose = chassis.getPose();
  float new_degrees = currentPose.theta + degrees;
  chassis.turnToHeading(new_degrees, timeout);
}

void swing_movement(int degrees, int timeout) {
  // lemlib::update(); // update the pose
  lemlib::Pose currentPose = chassis.getPose();
  float new_degrees = currentPose.theta + degrees;
  if (degrees < 0) {
    chassis.swingToHeading(new_degrees, DriveSide::LEFT, timeout);
  } else {
    chassis.swingToHeading(new_degrees, DriveSide::RIGHT, timeout);
  }
}

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

// when testing, put the tests in here
void autonomous() {
  chassis.setPose(0, 0, 0);

  // get
  chassis.moveToPoint(0, -13, 10000, {.forwards = false, .minSpeed = 20}, false);
  clamp::engage();
  chassis.moveToPoint(0, -16, 10000, {.forwards = false, .maxSpeed = 20}, false);

  // chassis.moveToPoint(0, 24, 100000);
  // chassis.moveToPoint(0, -24, 100000, {.forwards = false});
  // chassis.turnToHeading(-90, 100000);
  // 1.46
  // 1.38 (was longer)
  // peak::raise_to_level(1);
  // pros::delay(1500);
  // intake::run_forward(100);
  // pros::delay(100);
  // chassis.moveToPoint(0, -12, 1000, {.forwards = false});
  // chassis.moveToPoint(0, 6, 1000);
  // pros::delay(2000);
  // intake::off();
  // pros::delay(5000);
  // peak::raise_to_level(0);

  /*
  intake::on();
  lemlib::update();
  // lateral_move(20, 4000);
  intake::set_power(100);
  intake::on();
  // chassis.moveToPoint(0, 15, 4000);
  left_motors.move(100);
  right_motors.move(100);
  pros::delay(500);
  intake::off();
  left_motors.move(00);
  right_motors.move(00);
  */
}

void do_autonomous() {
  intake::set_power(100);
  intake::on();
}

// Set up of driver controls...// Arcade control scheme; has it's own function for enhanced organization...
void setArcadeDrive(pros::Controller master) {
  int drive = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);  // Gets amount forward/backward from left joystick
  int turn = -master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);   // Gets the turn left/right from right joystick
  left_motors.move(drive - turn);                                    // Sets left motor voltage
  right_motors.move(drive + turn);                                   // Sets right motor voltage
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
#endif
  while (true) {
    // Arcade control scheme
    setArcadeDrive(master);
    pros::delay(10);  // Run for 20 ms then update

    drive_intake(master);
    drive_clamp(master);
    drive_peak_levels(master);
#ifdef _DEBUG_
    drivePIDTest(master);
#endif

    // display_tick();
    pros::delay(2);
  }
}

std::vector<double> get_motor_temps() {
  std::vector<double> temps;

  for (int i = 1; i < 7; i++) {
    temps.push_back(pros::c::motor_get_temperature(i));
  }

  return temps;
}

std::vector<double> get_motor_torques() {
  std::vector<double> torques;

  for (int i = 1; i < 7; i++) {
    torques.push_back(pros::c::motor_get_torque(i));
  }

  return torques;
}

std::vector<double> get_motor_rpms() {
  std::vector<double> rpms;

  for (int i = 1; i < 7; i++) {
    rpms.push_back(pros::c::motor_get_actual_velocity(i));
  }

  return rpms;
}
