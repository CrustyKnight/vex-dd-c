#ifndef _AUTON_H_
#define _AUTON_H_
#include "api.h"
#include "lemlib/api.hpp"
#include <string>

void autonSkills(lemlib::Chassis*);
// void gameAuton(string startLocation);
void defensiveAuton();
void offensiveAuton();
void get_mogo(lemlib::Chassis*, double, double);

#endif
