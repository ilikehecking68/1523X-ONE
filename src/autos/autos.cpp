#include "main.h"
#include "ports.hpp"
#include "ll.hpp"

void auto_one_pratham(){
    chassis.setPose(-51.231, -15.395, 90);

    //move towards first 3 balls
    //THIS POSE SHOULD BE EDITED AND TUNED TO MAKE WORK
    chassis.moveToPoint(-25.713, -18.403, 2000, {.minSpeed = 90, .earlyExitRange = 3});
    //intake storage-mode start HERE

    //move through 1st and into 2nd balls of pile
    //THIS POSE SHOULD BE EDITED AND TUNED TO MAKE WORK
    chassis.moveToPoint(-22.905, -24.52, 1500, {.maxSpeed = 30, .earlyExitRange = 1.5});

    //go through third ball
    //THIS POSE SHOULD BE EDITED AND TUNED TO MAKE WORK
    chassis.moveToPoint(-16.441, -24.251, 2000, {.maxSpeed = 35});
    chassis.waitUntilDone();

    //wait for ball to mostly intake
    pros::delay(120);

    //move to in front of goal backwards:
    chassis.moveToPose(-15.404, -15.442, 225, 2200, {.forwards = false, .lead = 0.2, .maxSpeed = 90, .minSpeed = 85, .earlyExitRange = 3});

    //spin around to face goal with intake
    chassis.turnToHeading(45, 1500);
    chassis.waitUntilDone();

    //move to scoring position
    //THIS POSE SHOULD BE EDITED AND TUNED TO MAKE WORK
    chassis.moveToPoint(-11.829, -12.079, 2000, {.maxSpeed = 30});
    //DE-INTAKE HERE OUT OF STORING MODE
    chassis.waitUntilDone();

    //wait for scoring to finish
    pros::delay(1500);

    //move towards matchloader
    chassis.moveToPose(-46.715, -52.036, 346.917, 3000, {.forwards = false, .lead = 0.35, .minSpeed = 105, .earlyExitRange = 3.5});

    //move to face, get in front, and get into matchloader
    chassis.moveToPose(-58.248, -46.949, 275, 2500, {.maxSpeed = 45, .minSpeed = 40});
    //MATCHLOADER DOWN
    //INTAKE STORE MODE ON NOW
    chassis.waitUntilDone();
    
    //HERE ADD SHAKE IF MATCHLOADER NOT WORKING

    //wait for 3 red/blue balls to come into intake
    pros::delay(750);
    
    //move to in front of long goal
    chassis.moveToPoint(-31.876, -47.219, 2000,{.forwards = false, .minSpeed = 100, .earlyExitRange = 5});

    //move to align for scoring with long goal
    chassis.moveToPoint(-28.239, -47.219, 2000, {.forwards = false, .maxSpeed = 30});
    chassis.waitUntilDone();

    //OUTTAKE TO SCORE ON GOAL

    //wait for balls to finish scoring
    pros::delay(1750);

    //move forward to get ready for turning around for ram
    chassis.moveToPose(-37.422, -48.503, 98.167, 2000, {.minSpeed = 110, .earlyExitRange = 4});

    //8M PTO NOW FOR RAM

    //ram
    chassis.moveToPose(-24.751, -47.284, 90, 2500, {.minSpeed = 125});
    chassis.waitUntilDone();
}

void autonomous(){
    auto_one_pratham();
}
