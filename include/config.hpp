#ifndef CONFIG_H
#define CONFIG_H

#define INTAKE_BUTTON DIGITAL_R1
#define INTAKE_REVERSE_BUTTON DIGITAL_R2
#define CLAMP_UP_BUTTON DIGITAL_UP
#define CLAMP_DOWN_BUTTON DIGITAL_DOWN
#define CLAMP_ON 1
#define CLAMP_OFF 0
#define CLAMP_PISTON_A_PORT 'H'
#define CLAMP_PISTON_B_PORT 'G'

#define INTAKE_MOTOR_PORT 7
#define PEAK_MOTOR_PORT 8

#define INTAKE_ON_DIRECTION -1
#define INTAKE_INIT_POWER 100

#define PEAK_ON_DIRECTION -1
#define PEAK_ON_POWER 100

#define INTAKE_SPROCKET_TEETH 20.0
#define INTAKE_CHAIN_LINKS 81.0
#define INTAKE_RATIO (INTAKE_CHAIN_LINKS / INTAKE_SPROCKET_TEETH)
#define INTAKE_MOTOR_PER_CHAIN_REV INTAKE_RATIO

#define LINEAR_SLIDE_ALL_TEETH 133
#define LINEAR_SLIDE_SECTION_TEETH 19.0
#define LINEAR_SLIDE_MAX_TEETH_HEIGHT 100
// TODO check this V
// inches
#define LINEAR_SLIDE_SECTION_HEIGHT 2.5
#define LINEAR_SLIDE_TEETH_PER_INCH (LINEAR_SLIDE_SECTION_TEETH / LINEAR_SLIDE_SECTION_HEIGHT)
// inches
#define LINEAR_SLIDE_RANGE 17.5
#define PEAK_GEAR_TEETH 12.0

// degrees
#define PEAK_ANGLE 55
#define PEAK_COSECANT 1.22077458876

// measurments here are in inches
// These are the vertical height
// Stuff for the peak
#define DEFAULT_HEIGHT 0.0
#define ALLIANCE_STAKE_HEIGHT 5.0
#define WALL_STAKE_HEIGHT 10.0
// Ladder height
#define ENDGAME_HEIGHT 7.5

#define _DEBUG_
#ifdef _DEBUG_

#define _DEBUG_AUTON_
#define DEBUG_LATERAL_TEST_BUTTON DIGITAL_A
#define DEBUG_ANGULAR_TEST_BUTTON DIGITAL_B

#endif  // _DEBUG_

#include "lemlib/api.hpp"
extern lemlib::Chassis chassis;

#endif  // CONFIG_H
