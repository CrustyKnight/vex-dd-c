#include "auton.hpp"
#include "clamp.hpp"
#include "intake.hpp"
#include "peak.hpp"

#include <string>

#define SKILLS_X_START 0
#define SKILLS_Y_START 0
//#TODO: create efficient skills plan...
void autonSkills(lemlib::Chassis chassis) {
  chassis.setPose(SKILLS_X_START, SKILLS_Y_START, 0);
}

//#TODO: create game plan...
void defensiveAuton() {
}

void offensiveAuton() {
}
