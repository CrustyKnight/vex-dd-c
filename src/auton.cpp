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
  intake::run_forward(120);
  pros::delay(2000);
  intake::run_forward(0);

  //mogo
  chassis->turnToPoint(120, -60, 2000, {.maxSpeed = 90}, false);
  pros::delay(100);
  chassis->moveToPoint(-120, 60, 2000, {.forwards = false, .maxSpeed = 90}, false);
  clamp::engage();

  pros::delay(300);

  //donuts are yummy
  intake::run_forward(120);

  chassis->turnToPoint(-60, 60, 3000, {.maxSpeed = 90}, false);
  pros::delay(100);
  chassis->moveToPoint(-60, 55, 2000, {.maxSpeed = 90, .minSpeed = 30}, false);
  chassis->moveToPoint(-60, 60, 2000, {.maxSpeed = 90}, false);
  pros::delay(100);
  chassis->turnToPoint(-150, 120, 2000, {.maxSpeed = 90}, false);
  chassis->moveToPoint(-150, 120, 7000, {.maxSpeed = 50}, false);

  pros::delay(100);
  chassis->turnToPoint(-120, 150, 2000, {.maxSpeed = 50}, false);
  chassis->moveToPoint(-120, 150, 2000, {.maxSpeed = 50}, false);

  intake::off();
  pros::delay(100);

  chassis->turnToPoint(160, -160, 3000, {.maxSpeed = 50}, false);
  chassis->moveToPoint(-160, 160, 3000, {.forwards = false, .maxSpeed = 100, .minSpeed = 30}, false);
  clamp::disengage();
  chassis->moveToPoint(-145, 157, 3000, {.forwards = true, .maxSpeed = 100}, false);

  pros::delay(100);
  chassis->turnToPoint(0, 150, 3000, {.maxSpeed = 90}, false);
  intake::run_forward(120);
  chassis->moveToPoint(-5, 150, 3000, {.maxSpeed = 90, .minSpeed = 30}, false);
  chassis->moveToPoint(0, 150, 3000, {.maxSpeed = 90}, false);

  pros::delay(100);
  chassis->turnToPoint(0, 170, 4000, {.maxSpeed = 50}, false);

  intake::eat_donut();

  peak::raise_to_level(3);
  pros::delay
  intake::run_forward(120);

}

//#TODO: Test/enhance/modify the game autons below to our needs. Currently, they are set to help us get most of the AWP. 

/*
Scores on one MOGO, then on alliance stake, then touches the ladder.
*/
void negative_red(lemlib::Chassis* chassis) {
    peak::raise_to_level(1);
    lemlib::Pose start(-150, 60, 90);
    chassis->setPose(start);

    pros::delay(400);

    chassis->moveToPoint(-60, 60, 1500, {.forwards = false, .maxSpeed = 90}, false);
    pros::delay(300);
    clamp::engage();
    pros::delay(400);

    chassis->turnToPoint(-60, 120, 1500, {.forwards = true, .maxSpeed = 90}, false);
    pros::delay(500);
    chassis->moveToPoint(-60, 120, 1500, {.forwards = false, .maxSpeed = 30}, false);
    
    intake::on();

    chassis->turnToHeading(0, 1000, {.maxSpeed = 90}, false);
    pros::delay(400);
    chassis->moveToPoint(-9, 130, 1500, {.forwards = true, .maxSpeed = 50}, false);
    pros::delay(400);

    chassis->moveToPoint(-30, 130, 1500, {.maxSpeed = 50}, false);
    chassis->moveToPoint(-41.2, 57.065, 1000, {.maxSpeed = 90}, false);
    pros::delay(300);
    chassis->moveToPoint(-40, 34, 1000, {.maxSpeed = 90}, false);
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

  //Touching the ladder (and turning intake off before doing so)
  chassis->moveToPose(48, 96, 180, 1500, {.forwards = false, .minSpeed = 20}, false);
  intake::off();
  chassis->moveToPoint(96, 48, 10000, {.forwards = false, .minSpeed = 20}, false);
}

void negative_blue(lemlib::Chassis* chassis){
  peak::raise_to_level(1);
  lemlib::Pose start(150, 120, 180);
  chassis->setPose(start);
  peak::raise_to_level(1);
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
