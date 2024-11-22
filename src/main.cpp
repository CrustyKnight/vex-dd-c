#include "lemlib/api.hpp" // IWYU pragma: keep
#include "auton.hpp"
#include "main.h"
#include "display.h"

//Important Note: This file has all of our drivetrain and remote control-related code. 

// LemLib setup
// TODO
// Setting up of drivetrain sides: side_motors({low_1, low_2, -high})
pros::MotorGroup left_motors({1, 2, -3}, pros::MotorGearset::green);
pros::MotorGroup right_motors({-4, -5, 6}, pros::MotorGearset::green);

// Setup of drivetrain, IMU, and odometry sensors (just our IMU for now): using lemlib for odometry functionality. 
lemlib::Drivetrain drivetrain(&left_motors, &right_motors, 13.3, lemlib::Omniwheel::NEW_325, 333.3333, 2);
pros::Imu imu(10);
lemlib::OdomSensors sensors(nullptr, nullptr, nullptr, nullptr, &imu);

// kP, kI, kD, anti-windup, small error range, small error range timeout,
// large error range, large error range timeout, max acceleration (slew)
lemlib::ControllerSettings lateral_controller(10, 0, 3, 3, 1, 100, 3, 500, 20);
lemlib::ControllerSettings angular_controller(2, 0, 10, 3, 1, 100, 3, 500, 0);

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
  display_init();
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

// when testing, put the tests in here
void autonomous() {
	
}

void lateral_move(int distance, int timeout) {
	chassis.setPose(0, 0, 0);
	chassis.moveToPoint(0, distance, timeout);
	}

//TODO: we need to find out if negative degrees and positive degrees are clockwise our counterclockwise for the purpose of our robot. 
void angular_turn(int degrees, int timeout) {
	chassis.setPose(0, 0, 0);
	chassis.turnToHeading(degrees, timeout);
}

void swing_movement(int degrees, int timeout){
	chassis.setPose(0, 0, 0);
	if(degrees < 0){
		chassis.swingToHeading(degrees, DriveSide::LEFT, timeout);
	}
	else{
		chassis.swingToHeading(degrees, DriveSide::RIGHT, timeout);
	}
}

//Driver/Screen Functions: I, Debangshu Pramanik, think we'd like this to be outside opcontrol for organization purposes. 
void printStatus(){ // Prints status of the emulated screen LCDs
	pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
		                 (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
		                 (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);  
} 
// Set up of driver controls...// Arcade control scheme; has it's own function for enhanced organization...
void setArcadeDrive(pros::Controller master){ 
	int dir = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);    // Gets amount forward/backward from left joystick
	int turn = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);  // Gets the turn left/right from right joystick
	left_motors.move(dir - turn);                      // Sets left motor voltage
	right_motors.move(dir + turn);                     // Sets right motor voltage
	pros::delay(20);                               // Run for 20 ms then update
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
	while (true) {
		// Prints status of the emulated LCD. 
		printStatus();
		// Arcade control scheme
		setArcadeDrive(master);

    std::cout << "left motors:" << get_motor_temps()[0];
    display_tick();
    
	}
}

std::vector<double> get_motor_temps(){

  std::vector<double> temps; 

  for(int i = 1; i < 7; i++){
    temps.push_back(pros::c::motor_get_temperature(i));
  }

  return temps; 
}

std::vector<double> get_motor_torques(){

  std::vector<double> torques;

  for(int i = 1; i < 7; i++){
    torques.push_back(pros::c::motor_get_torque(i));
  }

  return torques;

}
