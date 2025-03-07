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
  lemlib::Pose start(-150, 0, 0);
  chassis->setPose(start);

  pros::delay(1000);
  //alliance stake
  intake::digest_donut();
  pros::delay(2000);

  //grab mogo
  chassis->turnToPoint(120, -60, 1000, {.forwards = true}, false);
  pros::delay(200);
  chassis->moveToPoint(-120, 60, 1000, {.forwards = false, .minSpeed = 30}, false);
  clamp::engage();
  pros::delay(100);
  intake::on();

  chassis->moveToPose(-60, 120, 0, 1000, {.horizontalDrift = 10, .lead = 0.4, .maxSpeed = 60}, false);

  /*
  //get donuts

  chassis->turnToHeading(0, 1000, {.maxSpeed = 120}, false);
  pros::delay(1000);
  chassis->moveToPoint(-60, 60, 1000, {.maxSpeed = 120}, false);
  pros::delay(1000);

  chassis->turnToHeading(180, 1000, {.maxSpeed = 120}, false);
  pros::delay(1000);
  chassis->moveToPoint(-150, 120, 1000, {.maxSpeed = 120}, false);
  pros::delay(1000);

  chassis->turnToHeading(45, 1000, {.maxSpeed = 120}, false);
  pros::delay(1000);
  chassis->moveToPoint(-120, 150, 1000, {.maxSpeed = 120}, false);
  pros::delay(1000);

  chassis->turnToHeading(150, 1000, {.maxSpeed=120}, false);
  pros::delay(1000);
  chassis->moveToPoint(-165, 165, 1000, {.maxSpeed=120}, false);
  pros::delay(1000);
  clamp::disengage();
  */
}

//#TODO: Test/enhance/modify the game autons below to our needs. Currently, they are set to help us get most of the AWP. 

/*
Scores on one MOGO, then on alliance stake, then touches the ladder.
*/
void negative_red(lemlib::Chassis* chassis) {
    peak::raise_to_level(1);
    lemlib::Pose start(-150, 60, 90);
    chassis->setPose(start);

    chassis->moveToPoint(-60, 60, 1500, {.forwards = false}, false);
    pros::delay(3000);
    clamp::engage();
    pros::delay(1000);

    chassis->turnToPoint(-60, 120, 1500, {.forwards = true}, false);
    pros::delay(500);
    chassis->moveToPoint(-60, 120, 1500, {.forwards = false, .maxSpeed = 30}, false);
    
    intake::eat_donut();

    chassis->turnToHeading(0, 1000, {.maxSpeed = 120}, false);
    pros::delay(500);
    chassis->moveToPoint(-9, 130, 1500, {.forwards = true, .maxSpeed = 30}, false);
    pros::delay(500);
    intake::eat_donut();

    chassis->moveToPoint(-30, 130, 1500, {.maxSpeed = 50}, false);
    chassis->moveToPoint(-41.2, 57.065, 1000, {.maxSpeed = 120}, false);
    pros::delay(300);
    chassis->moveToPoint(-40, 34, 1000, {.maxSpeed = 120}, false);
    intake::on();
}

void positive_red(lemlib::Chassis* chassis){
  peak::raise_to_level(1);
  lemlib::Pose start(12, 96, 180);
  chassis->setPose(start);

  //Rushing to the central MOGO
  chassis->turnToPoint(-66, 114, 1500, {.maxSpeed = 50}, false);
  pros::delay(500);
  chassis->moveToPose(-66,114,45, 1500, {.forwards = false, .minSpeed = 20}, false);
  pros::delay(2000);
  clamp::engage();

  //Not Scoring on "grabbed MOGO" in the event that the other team gets it, but grabbing a donut on the way. 
  chassis->turnToPoint(36, 108, 1000, {.maxSpeed = 50}, false);
  pros::delay(500);
  chassis->moveToPose(36, 108, 45, 1000);
  pros::delay(500);
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
  peak::raise_to_level(1);
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
  peak::raise_to_level(1);
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
