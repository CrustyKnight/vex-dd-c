#include "lemlib/api.hpp"
#include "auton.hpp"
#include "clamp.hpp"
#include "intake.hpp"
#include "peak.hpp"
// hi
#include <string>

#define SKILLS_X_START -58
#define SKILLS_Y_START 23
#define SKILLS_THETA_START 180

#define ROBOT_WIDTH 14.76
#define ROBOT_HEIGHT 17.52

#define D1X -22.5
#define D1Y 23

#define D2X 0
#define D2Y 60

#define D3X 23
#define D3Y 47

#define D4X -48
#define D4Y 47

#define D5X 60
#define D5Y 47

#define D6X -47
#define D6Y 60

#define D7X -59
#define D7Y -47

#define D8X -47
#define D8Y -47

#define D9X -47
#define D9Y -59

#define D10X -24
#define D10Y -47

#define D11X 0
#define D11Y -59

// cursed :)
void drop_mogo() {
  clamp::disengage();
}
// Blocking
void get_mogo(lemlib::Chassis* chassis, double x, double y) {
  chassis->moveToPoint(x, y, 10000, {.forwards = false}, false);
  clamp::engage();
}

/* TEST
chassis.moveToPoint(0, -13, 10000, {.forwards = false, .minSpeed = 20}, false);
clamp::engage();
chassis.moveToPoint(0, -16, 10000, {.forwards = false, .maxSpeed = 20}, false);
*/

void grab_mogo(float x, float y, lemlib::Chassis* chassis) {
  chassis->moveToPoint(x, y, 10000, {.forwards = false, .minSpeed = 20,}, false);
  clamp::engage();
  chassis->moveToPoint(x+ 2, y, 10000, {.forwards = false, .minSpeed = 20}, false);
}
// #TODO: create efficient skills plan...
void autonSkills(lemlib::Chassis* chassis) {
  peak::raise_to_level(1);
  chassis->setPose(SKILLS_X_START, SKILLS_Y_START, SKILLS_THETA_START);

  grab_mogo(-55, 23.5, chassis);

  intake::on();

  chassis->moveToPose(D1X, D1Y, 0, 5000);
  pros::delay(300);
  chassis->moveToPoint(D2X, D2Y, 5000);
  pros::delay(300);
  chassis->moveToPose(D3X, D3Y, 180, 5000);
  pros::delay(300);
  chassis->moveToPoint(D4X, D4Y, 5000);
  pros::delay(300);
  chassis->moveToPoint(D5X, D5Y, 5000);

  chassis->turnToHeading(45, 5000);
  chassis->moveToPoint(D6X, D6Y, 5000);

  chassis->moveToPose(-64, -65, -45, 5000);
  drop_mogo();

  /*
  chassis->turnToHeading(-45, 5000);
  get_mogo(chassis, -47, -16);

  chassis->moveToPose(D7X, D7Y, 235, 5000);
  chassis->moveToPose(D8X, D8Y, -90, 5000);
  chassis->moveToPose(D9X, D9Y, 30, 5000);
  chassis->moveToPose(D10X, D10Y, -30, 5000);

  chassis->moveToPose(D11X, D11Y, 30, 5000);
  */
}

// #TODO: create game plan...These functions below are our game autons!!!

//Our plan here is to score on the alliance stake, then score on the other 2 MOGOs, and to also be dragging them toward the positive corner. 
void left_red(lemlib::Chassis* chassis) {
  //For this auton, it was assumed that PID is functioning properly, or at least, accurately enough. 
  //I also assumed that x = horizontal and y = vertical axis, on the image of the field, with (0, 0) being the top left corner...

  //First things first: setting the position of the robot...This is theoretically where we place in on the field...
  lemlib::Pose starting_pose(12, 48, 180);
  chassis->setPose(starting_pose);

  //Opening Moves: Moving towards the LEFT MOGO, clamping it, and scoring our preload...~3 seconds...
  chassis->moveToPoint(48, 48, 2500, {.forwards = false, .minSpeed = 20}, false);
  clamp::engage();
  intake::on();
  
  //Depositing grabbed MOGO near positive corner (right side). This is the meta...
  chassis->moveToPoint(24, 72, 1500);
  chassis->moveToPoint(24, 96, 1500, {.forwards = false, .minSpeed = 20}, false);
  clamp::disengage();

  //Grab 2nd MOGO, return to 'center' of our alliance's side. 
  chassis->moveToPoint(48, 96, 1500, {.forwards = false, .minSpeed = 20}, false);
  clamp::engage();
  chassis->moveToPoint(24, 72, 1500);
  
  //7 seconds used so far...Return to left side with out 2nd MOGO to score 2 remaining rings on it.
  intake::on();
  chassis->moveToPoint(72, 28, 1500);
  chassis->moveToPoint(72, 20, 750);
  intake::off();
  
  //9.25 seconds used so far...Time to bring MOGO back toward positive side, clear positive corner, then grab ladder. 
  chassis->moveToPoint(24, 72, 1500);
  clamp::disengage();
  chassis->moveToPoint(48, 48, 1500);
  chassis->moveToPoint(60, 60, 1500);
}

void right_red(lemlib::Chassis* chassis){

}

void left_blue(lemlib::Chassis* chassis){

}
void right_blue(lemlib::Chassis* chassis){

}