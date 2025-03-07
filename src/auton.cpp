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
  lemlib::Pose start(-60, 0, 0);
  chassis->setPose(start);

  pros::delay(1000);
  //alliance stake
  intake::run_forward(120);
  pros::delay(2000);
  intake::run_forward(0);

  //mogo
  chassis->turnToPoint(48, -24, 2000, {.maxSpeed = 90}, false);
  pros::delay(100);
  chassis->moveToPoint(-48, 24, 2000, {.forwards = false, .maxSpeed = 90}, false);
  clamp::engage();

  pros::delay(300);

  //donuts are yummy
  intake::run_forward(120);

  chassis->turnToPoint(-24, 24, 3000, {.maxSpeed = 90}, false);
  pros::delay(100);
  chassis->moveToPoint(-24, 22, 2000, {.maxSpeed = 90, .minSpeed = 30}, false);
  chassis->moveToPoint(-24, 24, 2000, {.maxSpeed = 90}, false);
  pros::delay(100);
  chassis->turnToPoint(-24, 48, 2000, {.maxSpeed = 90}, false);
  chassis->moveToPoint(-24, 48, 7000, {.maxSpeed = 50}, false);

  pros::delay(100);
  chassis->turnToPoint(-48, 48, 2000, {.maxSpeed = 50}, false);
  chassis->moveToPoint(-48, 48, 2000, {.maxSpeed = 50}, false);

  intake::off();
  pros::delay(100);

  chassis->turnToPoint(64, -64, 3000, {.maxSpeed = 50}, false);
  chassis->moveToPoint(-64, 64, 3000, {.forwards = false, .maxSpeed = 100, .minSpeed = 30}, false);
  clamp::disengage();
  chassis->moveToPoint(-57, 62, 3000, {.forwards = true, .maxSpeed = 100}, false);

  pros::delay(100);
  chassis->turnToPoint(24, 48, 3000, {.maxSpeed = 90}, false);
  chassis->moveToPoint(24, 48, 3000, {.maxSpeed = 90}, false);
  intake::swallow();


  pros::delay(100);
  chassis->turnToPoint(0, 60, 4000, {.maxSpeed = 50}, false);
  chassis->moveToPoint(0, 60, 4000, {.maxSpeed = 90}, false);
  intake::swallow();

  peak::raise_to_level(3);
  pros::delay(2000);
  intake::run_forward(120);
  pros::delay(2000);
  intake::off();


}

//#TODO: Test/enhance/modify the game autons below to our needs. Currently, they are set to help us get most of the AWP. 

/*
Scores on one MOGO, then on alliance stake, then touches the ladder.
*/

//Note: for game auton: we use jerry.io standards...

void negative_red(lemlib::Chassis* chassis) {
  peak::raise_to_level(1);
  lemlib::Pose start(-60, 24, 270);
  chassis->setPose(start);

  chassis->moveToPoint(-28, 24, 1500, {.forwards = false});
  chassis->moveToPoint(-24, 24, 750, {.forwards = false, .minSpeed = 30}, false);
  clamp::engage();
  intake::on();

  chassis->moveToPoint(-24, 48, 1250, {.minSpeed = 30}, false);

  chassis->moveToPose(-20, 52, 90, 1000, {.lead = 0, .minSpeed = 30}, false);
  pros::delay(500);
  chassis->moveToPoint(-24, 48, 1250, {.forwards = false}, false);
  chassis->moveToPose(-28, 52, 90, 1000, {.lead = 0}, false);
  pros::delay(500);
  
  chassis->moveToPoint(-48, 0, 2000, {.minSpeed = 60}, false);
  pros::delay(500);
  intake::off();
  chassis->moveToPose(-60, 0, 90, 1500, {.lead = 1, .maxSpeed = 80, .minSpeed = 30}, false);
  intake::on();
  pros::delay(2500);
  intake::off();

  chassis->moveToPose(-20, 9, 315, 1000, {.minSpeed = 60});
}

void positive_red(lemlib::Chassis* chassis){

}

void negative_blue(lemlib::Chassis* chassis){
  peak::raise_to_level(1);
  lemlib::Pose start(60, 24, 90);
  chassis->setPose(start);

  chassis->moveToPoint(28, 24, 1500, {.forwards = false});
  chassis->moveToPoint(24, 24, 750, {.forwards = false, .minSpeed = 30}, false);
  clamp::engage();
  intake::on();

  chassis->moveToPoint(24, 48, 1250, {.minSpeed = 30}, false);

  chassis->moveToPose(20, 52, 270, 1000, {.lead = 0, .minSpeed = 30}, false);
  pros::delay(500);
  chassis->moveToPoint(24, 48, 1250, {.forwards = false}, false);
  chassis->moveToPose(28, 52, 270, 1000, {.lead = 0}, false);
  pros::delay(500);
  
  chassis->moveToPoint(48, 0, 2000, {.minSpeed = 60}, false);
  pros::delay(500);
  intake::off();
  chassis->moveToPose(60, 0, 270, 1500, {.lead = 1, .maxSpeed = 80, .minSpeed = 30}, false);
  intake::on();
  pros::delay(2500);
  intake::off();

  chassis->moveToPose(20, 9, 45, 1000, {.minSpeed = 60});
}
void positive_blue(lemlib::Chassis* chassis){
  peak::raise_to_level(1);
  lemlib::Pose start(60, -24, 90);
  chassis->setPose(start);

  //Rushing to the central MOGO (10, -40, 120)
  chassis->moveToPose(10, -40, 60, 1500, {.lead = 0.1, .minSpeed = 80});

  //Not Scoring on "grabbed MOGO" in the event that the other team gets it, but grabbing a donut on the way. 
  intake::on();
  chassis->moveToPoint(24, -48, 750, {.minSpeed = 40}, false);
  pros::delay(500);
  intake::off();

 
  //Letting MOGO go, grabbing the other MOGO on our side, and scoring preload + grabbed ring...
  clamp::disengage();
  chassis->moveToPoint(24, -24, 1000, {.forwards = false, .minSpeed = 20});
  clamp::engage();
  intake::on();

  //Touching the ladder (and turning intake off before doing so)
  chassis->moveToPose(12, -14, 315, 1500, {.forwards = false, .minSpeed = 20}, false);
  intake::off();
  chassis->moveToPoint(8, -16, 10000, {.forwards = false, .minSpeed = 20}, false);
}
