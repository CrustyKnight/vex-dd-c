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
// TODO test and tune
void autonSkills(lemlib::Chassis* chassis) {
  //peak::raise_to_level(1);
  //chassis->setPose(0, 0, 270);

  /*
  // alliance stake
  intake::run_forward(120);
  pros::delay(2000);
  intake::off();
  */

  /*
  //grab mogo
  chassis->turnToHeading(63, 2000, {}, false);
  chassis->moveToPoint(-13, -13, 1000, {.maxSpeed = 100}, false);
  pros::delay(100);
  clamp::engage();
  */

  clamp::engage(); //testing
  chassis->setPose(-13, -13, 180); //testing
  chassis->turnToHeading(270, 1000, {}, false);
  intake::run_forward(50);

  //intake::run_forward(120);
  chassis->moveToPoint(-36, -12, 1000, {.maxSpeed = 70}, false);
  chassis->turnToHeading(180, 1000, {}, false);
  chassis->moveToPoint(-36, -36, 1000, {.maxSpeed = 70}, false);

  chassis->turnToHeading(90, 1000, {}, false);
  chassis->moveToPoint(0, -36, 6000, {.maxSpeed = 50}, false);

  chassis->turnToHeading(225, 1000, {}, false);
  chassis->moveToPoint(-12, -48, 1000);

  chassis->turnToHeading(60, 2000, {}, false);
  chassis->moveToPoint(9, -55, 1000, {.minSpeed = 20}, false);
  clamp::disengage();
  chassis->moveToPoint(-12, -48, 1000, {.forwards = false}, false);

  intake::off();


}

// #TODO: Test/enhance/modify the game autons below to our needs. Currently, they are set to help us get most of the AWP.

/*
Scores on one MOGO, then on alliance stake, then touches the ladder.
*/

// Note: for game auton: we use jerry.io standards...

void negative_red(lemlib::Chassis* chassis) {
  peak::raise_to_level(1);
  pros::delay(1000);

  chassis->setPose(0, 0, 90);
  // degrees is like on the unit circle, but backwards. (+ is clockwise)

  // Go to the mogo & clamp it.
  // (moving through it works better)
  chassis->moveToPoint(-32, 0, 1500, {.forwards = false, .minSpeed = 30}, false);
  chassis->moveToPoint(-34, 0, 1500, {.forwards = false, .maxSpeed = 30, .minSpeed = 10}, false);
  clamp::engage();
  chassis->moveToPoint(-36, 0, 750, {.forwards = false, .maxSpeed = 60}, false);

  // Run intake to put our preload on the mogo
  intake::run_forward(120);
  pros::delay(1000);

  // Go get another donut!!
  chassis->turnToPoint(-36, 24, 1000, {.minSpeed = 30}, false);
  chassis->turnToPoint(-36, 10, 1000, {.minSpeed = 50}, false);
  // chassis->turnToPoint(24, 48, 1000, {}, false);
  chassis->turnToPoint(-38, 24, 1000, {}, false);
  chassis->moveToPoint(-36, 24, 2000, {.maxSpeed = 70}, false);
  intake::run_forward(120);


  // (testing) chassis->setPose(-36, 24, 0);
  chassis->turnToHeading(270, 1000, {}, false);
  intake::run_forward(120);
  chassis->moveToPoint(-52, 24, 2000, {.maxSpeed = 70, .minSpeed = 20}, false);
  chassis->moveToPoint(-36, 24, 2000, {.forwards = false, .maxSpeed = 50}, false);
  pros::delay(300);
    //TODO idk if this is actually right so
  chassis->turnToHeading(-60, 2000, {}, false);
  chassis->moveToPoint(-24, -12, 3000, {.maxSpeed = 40}, false);

  /*
  lemlib::Pose start(60, 24, 90);
  chassis->setPose(start);

  chassis->moveToPoint(28, 24, 1500, {.forwards = false, .minSpeed = 30});
  chassis->moveToPoint(26, 24, 1500, {.forwards = false, .maxSpeed = 30, .minSpeed = 10});
  clamp::engage();
  chassis->moveToPoint(24, 24, 750, {.forwards = false, .maxSpeed = 60}, false);

  intake::run_forward(120);
  pros::delay(1000);

  chassis->turnToPoint(24, 48, 1000, {.minSpeed = 30}, false);
  chassis->turnToPoint(24, 30, 1000, {.minSpeed = 50}, false);
  //chassis->turnToPoint(24, 48, 1000, {}, false);
  chassis->turnToPoint(24, 48, 1000, {}, false);
  chassis->moveToPoint(24, 49, 2000, {.maxSpeed = 70}, false);
  intake::run_forward(120);
  */

  /*
  chassis->turnToPoint(-24, 48, 1250, {.maxSpeed = 70}, false);
  chassis->moveToPoint(-24, 48, 1250, {.maxSpeed = 70}, false);
  */

  /*
  chassis->moveToPose(-20, 52, 90, 1000, {.lead = 0}, false);
  pros::delay(500);
  chassis->moveToPoint(-24, 48, 1250, {.forwards = false}, false);
  chassis->moveToPose(-28, 52, 90, 1000, {.lead = 0}, false);
  pros::delay(500);
/**/

  //  chassis->moveToPose(-20, 9, 315, 1000, {.maxSpeed = 100});

  /*

  chassis->moveToPoint(-48, 0, 2000, {.maxSpeed = 90}, false);
  pros::delay(500);
  intake::off();
  chassis->moveToPose(-60, 0, 90, 1500, {.lead = 1, .maxSpeed = 80}, false);
  intake::on();
  pros::delay(2500);
  intake::off();

  chassis->moveToPose(-20, 9, 315, 1000, {.maxSpeed = 100});
  */
}

void positive_red(lemlib::Chassis* chassis) {
  peak::raise_to_level(1);
  lemlib::Pose start(-60, -24, 90);
  chassis->setPose(start);

  // Rushing to the central MOGO (10, -40, 120)
  chassis->moveToPose(-10, -40, 60, 1500, {.lead = 0.1, .minSpeed = 80});

  // Not Scoring on "grabbed MOGO" in the event that the other team gets it, but grabbing a donut on the way.
  intake::on();
  chassis->moveToPoint(-24, -48, 750, {.minSpeed = 40}, false);
  pros::delay(500);
  intake::off();

  // Letting MOGO go, grabbing the other MOGO on our side, and scoring preload + grabbed ring...
  clamp::disengage();
  chassis->moveToPoint(-24, -24, 1000, {.forwards = false, .minSpeed = 20});
  clamp::engage();
  intake::on();

  // Touching the ladder (and turning intake off before doing so)
  chassis->moveToPose(-12, -14, 45, 1500, {.forwards = false, .minSpeed = 20}, false);
  intake::off();
  chassis->moveToPoint(-8, -16, 10000, {.forwards = false, .minSpeed = 20}, false);
}

void negative_blue(lemlib::Chassis* chassis) {
  peak::raise_to_level(1);
  pros::delay(1000);
  lemlib::Pose start(60, 24, 90);
  chassis->setPose(start);

  chassis->moveToPoint(28, 24, 1500, {.forwards = false, .minSpeed = 30});
  chassis->moveToPoint(26, 24, 1500, {.forwards = false, .maxSpeed = 30, .minSpeed = 10});
  clamp::engage();
  chassis->moveToPoint(24, 24, 750, {.forwards = false, .maxSpeed = 60}, false);

  intake::run_forward(120);
  pros::delay(1000);

  chassis->turnToPoint(24, 48, 1000, {.minSpeed = 30}, false);
  chassis->turnToPoint(24, 30, 1000, {.minSpeed = 50}, false);
  // chassis->turnToPoint(24, 48, 1000, {}, false);
  chassis->turnToPoint(24, 48, 1000, {}, false);
  chassis->moveToPoint(24, 49, 2000, {.maxSpeed = 70}, false);
  intake::run_forward(120);
  // chassis->moveToPoint(20, 0, 5000, {.forwards = false, .maxSpeed = 50}, false);
  // pros::delay(5000);
  // intake::off();

  /*

  chassis->moveToPoint(24, 48, 1250, {.maxSpeed = 90}, false);

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
  */
}

void positive_blue(lemlib::Chassis* chassis) {
  peak::raise_to_level(1);
  lemlib::Pose start(60, -24, 90);
  chassis->setPose(start);

  // Rushing to the central MOGO (10, -40, 120)
  chassis->moveToPose(10, -40, 60, 1500, {.lead = 0.1, .minSpeed = 80});

  // Not Scoring on "grabbed MOGO" in the event that the other team gets it, but grabbing a donut on the way.
  intake::on();
  chassis->moveToPoint(24, -48, 750, {.minSpeed = 40}, false);
  pros::delay(500);
  intake::off();

  // Letting MOGO go, grabbing the other MOGO on our side, and scoring preload + grabbed ring...
  clamp::disengage();
  chassis->moveToPoint(24, -24, 1000, {.forwards = false, .minSpeed = 20});
  clamp::engage();
  intake::on();

  // Touching the ladder (and turning intake off before doing so)
  chassis->moveToPose(12, -14, 315, 1500, {.forwards = false, .minSpeed = 20}, false);
  intake::off();
  chassis->moveToPoint(8, -16, 10000, {.forwards = false, .minSpeed = 20}, false);
}
