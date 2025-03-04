#include "lemlib/api.hpp"
#include "auton.hpp"
#include "clamp.hpp"
#include "intake.hpp"
#include "peak.hpp"
// hi
#include <string>

#define ROBOT_WIDTH 14.76
#define ROBOT_HEIGHT 17.52

/*
puts preload into alliance stake
Scores 2 full mogos and puts them into corners 
*/
//TODO test and tune
void autonSkills(lemlib::Chassis* chassis) {
  peak::raise_to_level(1);

  lemlib::Pose starting_pose(-150, 0, 0);
  chassis->setPose(starting_pose);

  //wall stake
  pros::delay(1500);
  intake::run_forward(120);
  pros::delay(2000);
  intake::off();


  //mogo
  chassis->moveToPoint(120, 0, 100000);
  clamp::engage();

  intake::on();

  //donuts
  chassis->turnToHeading(45, 100000);
  chassis->moveToPoint(60, 60, 100000);
  pros::delay(1500);

  chassis->turnToHeading(90, 100000);
  chassis->moveToPoint(60, 120, 100000);
  pros::delay(1500);

  chassis->turnToHeading(180, 100000);
  chassis->moveToPoint(120, 120, 100000);
  pros::delay(3000);

  chassis->moveToPoint(150, 120, 100000);
  pros::delay(3000);

  chassis->turnToHeading(30, 100000);
  chassis->moveToPoint(163, 163, 100000);
  pros::delay(1000);
  clamp::disengage();

  intake::off();

  //TODO tune grabbing of 2 donuts

  chassis->moveToPoint(60, 120, 100000);
  intake::eat_donut();
  chassis->moveToPoint(0, 150, 100000);
  intake::eat_donut();

  //wall stake
  chassis->turnToHeading(90, 100000);
  peak::raise_to_level(3);
  intake::on();
  pros::delay(5000);
  intake::off();
  peak::raise_to_level(1);

  //grab another 2 donuts and put them on mogo
  chassis->turnToHeading(180, 100000);
  chassis->moveToPoint(120, 150, 100000);
  intake::eat_donut();
  pros::delay(500);
  intake::eat_donut();

  chassis->turnToHeading(330, 100000);
  chassis->moveToPoint(150, 60, 100000);
  clamp::engage();
  chassis->turnToHeading(-90, 100000);

  chassis->moveToPose(170, -170, -45, 100000);
  chassis->turnToHeading(45, 100000);

  intake::on();
  chassis->moveToPoint(120, -120, 100000);
  pros::delay(1500);

  chassis->turnToHeading(0, 100000);
  chassis->moveToPoint(60, -120, 100000);
  pros::delay(1500);

  intake::off();

  chassis->turnToHeading(-30, 100000);
  chassis->moveToPoint(0, -150, 100000);
  intake::eat_donut();

  //wall stake 2
  chassis->turnToHeading(-90, 100000);
  peak::raise_to_level(3);

  intake::on();
  pros::delay(1500);
  intake::off();

  peak::raise_to_level(1);

  intake::on();
  chassis->turnToHeading(30, 100000);
  chassis->moveToPoint(-60, 120, 100000);

  chassis->turnToHeading(-30, 100000);
  chassis->moveToPoint(120, -150, 100000);

  chassis->turnToHeading(150, 100000);
  chassis->moveToPoint(-167, -167, 100000);
  clamp::disengage();
  
}

/*
Scores on alliance stake, then on other 2 MOGOs
Drags mogos toward positive corner
x axis is horizontal, y axis is vertical
*/
void negative_red(lemlib::Chassis* chassis) {
  peak::raise_to_level(1);

  lemlib::Pose starting_pose(12, 48, 180);
  chassis->setPose(starting_pose);

  //Moving towards the LEFT MOGO, clamping it, and scoring our preload...~3 seconds...
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

void positive_red(lemlib::Chassis* chassis){
  peak::raise_to_level(1);

}

void negative_blue(lemlib::Chassis* chassis){
  peak::raise_to_level(1);

}
void positive_blue(lemlib::Chassis* chassis){
  peak::raise_to_level(1);

}
