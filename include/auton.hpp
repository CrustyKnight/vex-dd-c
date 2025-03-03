#ifndef _AUTON_H_
#define _AUTON_H_
#include "api.h"
#include "lemlib/api.hpp"
#include <string>

void autonSkills(lemlib::Chassis*);
// void gameAuton(string startLocation);
void left_red(lemlib::Chassis*);
void right_red(lemlib::Chassis*);
void left_blue(lemlib::Chassis*);
void right_blue(lemlib::Chassis*);
void get_mogo(lemlib::Chassis*, double, double);

#endif
