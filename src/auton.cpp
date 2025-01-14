#include "lemlib/api.hpp"
#include "auton.hpp"
#include "clamp.hpp"
#include "intake.hpp"
#include "peak.hpp"

#include <string>

#define SKILLS_X_START -58
#define SKILLS_Y_START 23
#define SKILLS_THETA_START 180

static void get_mogo(lemlib::Chassis* chassis, double x, double y) {
  chassis->moveToPoint(x, y, 5000, {.forwards = false}, false);
  clamp::engage();
}

//#TODO: create efficient skills plan...
void autonSkills(lemlib::Chassis* chassis) {
  chassis->setPose(SKILLS_X_START, SKILLS_Y_START, SKILLS_THETA_START);
  get_mogo(chassis, -54, 23.5);
  chassis->moveToPose(-58.3, 47.0, 90, 5000);
  intake::eat_donut();
}

//#TODO: create game plan...
void defensiveAuton() {
}

void offensiveAuton() {
}
