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

//#TODO: Test/enhance/modify the game autons below to our needs. Currently, they are set to help us get most of the AWP. 

/*
Scores on one MOGO, then on alliance stake, then touches the ladder.
*/
void negative_red(lemlib::Chassis* chassis) {
  lemlib::Pose start(12, 48, 180);
  chassis->setPose(start);

  //Picking up MOGO on negative side and scoring preload on it
  chassis->moveToPoint(48, 48, 1500, {.forwards = false, .minSpeed = 20}, false);
  clamp::engage();
  intake::on();

  //Grabbing and scoring another donut, then leftmost of 2 touching donuts
  chassis->moveToPoint(48, 12, 1500);
  chassis->moveToPose(60, 12, -45, 1500);

  //Backing up, then scoring rightmost of 2 touching donuts.
  chassis->moveToPoint(48, 9, 1500, {.forwards = false, .minSpeed = 20}, false);
  chassis->moveToPose(60, 36, 45, 1500);

  //Scoring ring nearest to alliance stake onto alliance stake, and dropping MOGO on the way
  chassis->moveToPoint(24, 48, 2000, {.forwards = false, .minSpeed = 20}, false);
  clamp::disengage();
  chassis->turnToHeading(90, 750);
  chassis->moveToPoint(24, 72, 1000);
  intake::off();
  chassis->moveToPose(12, 72, 0, 750);
  intake::digest_donut();

  //Touching the ladder on our auton side's negative side. 
  chassis->moveToPoint(48, 48, 1000);
  chassis->moveToPoint(60, 60, 1000);
}

void positive_red(lemlib::Chassis* chassis){
  lemlib::Pose start(12, 96, 180);
  chassis->setPose(start);

  //Rushing to the central MOGO
  chassis->moveToPose(66, 114, 45, 1500, {.forwards = false, .minSpeed = 20}, false);
  clamp::engage();

  //Not Scoring on "grabbed MOGO" in the event that the other team gets it, but grabbing a donut on the way. 
  chassis->moveToPose(36, 108, 45, 1000);
  intake::eat_donut();
 
  //Letting MOGO go, grabbing the other MOGO on our side, and scoring preload + grabbed ring...
  clamp::disengage();
  chassis->moveToPoint(48, 96, 2000, {.forwards = false, .minSpeed = 20}, false);
  clamp::engage();
  intake::on();

  //Use MOGO to clear out positive corner, then place it there
  chassis->moveToPose(9, 135, 135, 2000);
  chassis->turnToHeading(675, 2000);
  chassis->moveToPoint(6, 138, 1500, {.forwards = false, .minSpeed = 20}, false);
  clamp::disengage();

  //Touching the ladder (and turning intake off before doing so)
  chassis->moveToPose(48, 96, 180, 1500, {.forwards = false, .minSpeed = 20}, false);
  intake::off();
  chassis->moveToPoint(96, 48, 10000, {.forwards = false, .minSpeed = 20}, false);
}

void negative_blue(lemlib::Chassis* chassis){
  lemlib::Pose start(132, 48, 180);
  chassis->setPose(start);

  //Picking up MOGO on negative side and scoring preload on it
  chassis->moveToPoint(96, 48, 1500, {.forwards = false, .minSpeed = 20}, false);
  clamp::engage();
  intake::on();

  //Grabbing and scoring another donut, then rightmost of 2 touching donuts
  chassis->moveToPoint(96, 24, 1500);
  chassis->moveToPose(84, 12, 135, 1500);

  //Backing up, then scoring leftmost of 2 touching donuts.
  chassis->moveToPoint(48, 9, 1500, {.forwards = false, .minSpeed = 20}, false);
  chassis->moveToPose(96, 36, -135, 1500);

  //Scoring ring nearest to alliance stake onto alliance stake, and dropping MOGO on the way
  chassis->moveToPoint(120, 48, 2000, {.forwards = false, .minSpeed = 20}, false);
  clamp::disengage();
  chassis->turnToHeading(90, 750);
  chassis->moveToPoint(120, 72, 1000);
  intake::off();
  chassis->moveToPose(132, 72, 0, 750);
  intake::digest_donut();

  //Touching the ladder on our auton side's negative side. 
  chassis->moveToPoint(96, 48, 1000);
  chassis->moveToPoint(84, 60, 1000);
}
void positive_blue(lemlib::Chassis* chassis){
  lemlib::Pose start(132, 96, 180);
  chassis->setPose(start);

  //Rushing to the central MOGO
  chassis->moveToPose(90, 114, 135, 1500, {.forwards = false, .minSpeed = 20}, false);
  clamp::engage();

  //Not Scoring on "grabbed MOGO" in the event that the other team gets it, but grabbing a donut on the way. 
  chassis->moveToPose(96, 108, 45, 1000);
  intake::eat_donut();
 
  //Letting MOGO go, grabbing the other MOGO on our side, and scoring preload + grabbed ring...
  clamp::disengage();
  chassis->moveToPoint(96, 96, 2000, {.forwards = false, .minSpeed = 20}, false);
  clamp::engage();
  intake::on();

  //Use MOGO to clear out positive corner, then place it there
  chassis->moveToPose(125, 135, 135, 2000);
  chassis->turnToHeading(675, 2000);
  chassis->moveToPoint(138, 138, 1500, {.forwards = false, .minSpeed = 20}, false);
  clamp::disengage();

  //Touching the ladder (and turning intake off before doing so)
  chassis->moveToPose(96, 96, 180, 1500, {.forwards = false, .minSpeed = 20}, false);
  intake::off();
  chassis->moveToPoint(48, 48, 5000, {.forwards = false, .minSpeed = 20}, false);
}
