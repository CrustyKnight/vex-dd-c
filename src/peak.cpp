#include "peak.hpp"
#include "lemlib/api.hpp"  // IWYU pragma: keep

///All functions for now will be written based off the fact that our intake has a angle to the horizontal of ~55*
//For now all these constants ARE ESTIMATES, THEY MUST BE REPLACED WITH REAL NUMBERS NEXT. 
//Constants are estimated heights that are needed 

//Peak power/direction & Different peak heights' constant declarations (in inches)
int peak_power = 100;
int peak_dir = 1;
float DEFAULT_HEIGHT = 0.0;
float ALLIANCE_STAKE_HEIGHT = 5.0;
float WALL_STAKE_HEIGHT = 10.0; 
float ENDGAME_HEIGHT = 7.5;
int PEAK_LENGTH = 14;

//Motor declaration
pros::Motor peak_motor(8, pros::MotorGearset::red);
//Functions written out here
void set_peak_power(int power){
    peak_power = power;
}
//In a right triangle, height is y, and peak length is hypotenuse. Therefore, sin function must be used
void adjust_intake_level(int height, int power){
    if(height < 0){
        peak_dir = -1;
    }
    else{
        peak_dir = 1;
    }
    while(PEAK_LENGTH * sin((double)(peak_motor.get_position())) != height){
        peak_motor.move(peak_dir * peak_power);
    }
}