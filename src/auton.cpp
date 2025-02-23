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

// #TODO: create game plan...
void defensiveAuton() {
}

void offensiveAuton() {
}
