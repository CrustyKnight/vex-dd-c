#ifndef CONFIG_H
#define CONFIG_H

/* **MID-COMP ADJUSTMENTS** */

/*game Auton*/
//#define _NEG_RED_
//#define _POS_RED_
//#define _NEG_BLUE_
//#define _POS_BLUE_

/*skills Auton*/
//#define _SKILLS_AUTON_






/* **CONSTANTS** */

//Buttons
#define INTAKE_BUTTON DIGITAL_R2
#define INTAKE_REVERSE_BUTTON DIGITAL_R1
#define CLAMP_UP_BUTTON DIGITAL_B
#define CLAMP_DOWN_BUTTON DIGITAL_A

#define PEAK_HIGH_WALL_BUTTON DIGITAL_UP
#define PEAK_ALLIANCE_WALL_STAKE_BUTTON DIGITAL_LEFT
#define PEAK_MOGO_BUTTON DIGITAL_DOWN
#define PEAK_REST_BUTTON DIGITAL_RIGHT
#define PEAK_MANUAL_UP_BUTTON DIGITAL_L1
#define PEAK_MANUAL_DOWN_BUTTON DIGITAL_L2

#define CLAMP_ON 1
#define CLAMP_OFF 0
#define CLAMP_PISTON_A_PORT 'H'
#define CLAMP_PISTON_B_PORT 'G'

#define INTAKE_MOTOR_PORT 7
#define PEAK_MOTOR_PORT 8

#define INTAKE_ON_DIRECTION -1
#define INTAKE_INIT_POWER 127

#define PEAK_ON_DIRECTION -1
#define PEAK_ON_POWER 200

// peak level (in)
#define PEAK_LEVEL_REST 0
// #define PEAK_LEVEL_MOGO 3.075
#define PEAK_LEVEL_MOGO 2.800
// #define PEAK_LEVEL_MOGO 3.505
#define PEAK_LEVEL_ALLIANCE PEAK_LEVEL_MOGO
// 3.575
#define PEAK_LEVEL_WALL 14.55

#define __PEAK_ARG_MOGO 1
#define __PEAK_ARG_WALL 3
#define __PEAK_ARG_REST 0

#define INTAKE_SPROCKET_TEETH 20.0
#define INTAKE_CHAIN_LINKS 81.0
#define INTAKE_RATIO (INTAKE_CHAIN_LINKS / INTAKE_SPROCKET_TEETH)
#define INTAKE_MOTOR_PER_CHAIN_REV INTAKE_RATIO

#define LINEAR_SLIDE_ALL_TEETH 133
#define LINEAR_SLIDE_SECTION_TEETH 19.0
#define LINEAR_SLIDE_MAX_TEETH_HEIGHT 118
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
#define DEBUG_LATERAL_TEST_BUTTON DIGITAL_L2
#define DEBUG_ANGULAR_TEST_BUTTON DIGITAL_L1

#ifdef _DEBUG_PID_
#ifdef _DEBUG_AUTON_
#error _DEBUG_PID_ and _DEBUG_AUTON_ cant both be active at the same time
#endif  // _DEBUG_AUTON_
#endif  // _DEBUG_PID_

#endif  // _DEBUG_

#include "lemlib/api.hpp"
extern lemlib::Chassis chassis;





/* **ERROR CHECKING** */






#ifdef _SKILLS_AUTON_
#ifdef _POS_RED_
#error "ONLY ONE AUTON AT A TIME"
#endif
#ifdef _NEG_BLUE_
#error "ONLY ONE AUTON AT A TIME"
#endif
#ifdef _POS_BLUE_
#error "ONLY ONE AUTON AT A TIME"
#endif
#ifdef _NEG_RED_
#error "ONLY ONE AUTON AT A TIME"
#endif
#endif

#ifdef _NEG_RED_
#ifdef _POS_RED_
#error "ONLY ONE AUTON AT A TIME"
#endif
#ifdef _NEG_BLUE_
#error "ONLY ONE AUTON AT A TIME"
#endif
#ifdef _POS_BLUE_
#error "ONLY ONE AUTON AT A TIME"
#endif
#ifdef _SKILLS_AUTON_
#error "ONLY ONE AUTON AT A TIME"
#endif
#endif

#ifdef _POS_RED_
#ifdef _NEG_RED_
#error "ONLY ONE AUTON AT A TIME"
#endif
#ifdef _NEG_BLUE_
#error "ONLY ONE AUTON AT A TIME"
#endif
#ifdef _POS_BLUE_
#error "ONLY ONE AUTON AT A TIME"
#endif
#ifdef _SKILLS_AUTON_
#error "ONLY ONE AUTON AT A TIME"
#endif
#endif

#ifdef _NEG_BLUE_
#ifdef _NEG_RED_
#error "ONLY ONE AUTON AT A TIME"
#endif
#ifdef _POS_RED_
#error "ONLY ONE AUTON AT A TIME"
#endif
#ifdef _POS_BLUE_
#error "ONLY ONE AUTON AT A TIME"
#endif
#ifdef _SKILLS_AUTON_
#error "ONLY ONE AUTON AT A TIME"
#endif
#endif

#ifdef _POS_BLUE_
#ifdef _NEG_RED_
#error "ONLY ONE AUTON AT A TIME"
#endif
#ifdef _POS_RED_
#error "ONLY ONE AUTON AT A TIME"
#endif
#ifdef _NEG_BLUE_
#error "ONLY ONE AUTON AT A TIME"
#endif
#ifdef _SKILLS_AUTON_
#error "ONLY ONE AUTON AT A TIME"
#endif

#endif
#endif  // CONFIG_H
