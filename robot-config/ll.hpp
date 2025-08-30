#pragma once

#include "lemlib/api.hpp"
#include "ports.hpp"

lemlib::Drivetrain drivetrain(&left_dt_mg, // left motor group
                              &right_dt_mg, // right motor group
                              12.25, // 10 inch track width
                              lemlib::Omniwheel::NEW_4, // using new 4" omnis
                              400, // drivetrain rpm is 360
                              2 // horizontal drift is 2 (for now)
);

lemlib::TrackingWheel horiz_tracking_wheel(&horiz, lemlib::Omniwheel::NEW_275, 0);
lemlib::OdomSensors sensors(nullptr, nullptr, &horiz_tracking_wheel, nullptr, &imu);

lemlib::ControllerSettings lateral_controller(10, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              3, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              20 // maximum acceleration (slew)
);

// angular PID controller
lemlib::ControllerSettings angular_controller(2, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              10, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in degrees
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in degrees
                                              500, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);