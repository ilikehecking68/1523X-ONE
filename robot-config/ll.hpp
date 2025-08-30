#pragma once

#include "lemlib/api.hpp"
#include "ports.hpp"

inline lemlib::Drivetrain drivetrain(&left_dt_mg, // left motor group
                              &right_dt_mg, // right motor group
                              12.25, // 10 inch track width
                              lemlib::Omniwheel::NEW_4, // using new 4" omnis
                              400, // drivetrain rpm is 360
                              2 // horizontal drift is 2 (for now)
);

inline lemlib::TrackingWheel horiz_tracking_wheel(&horiz, lemlib::Omniwheel::NEW_275, 0);
inline lemlib::OdomSensors sensors(nullptr, nullptr, &horiz_tracking_wheel, nullptr, &imu);

inline lemlib::ControllerSettings lateral_controller(10, // proportional gain (kP)
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
inline lemlib::ControllerSettings angular_controller(4, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              10, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in degrees
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in degrees
                                              500, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);

inline lemlib::Chassis chassis(drivetrain, // drivetrain settings
                        lateral_controller, // lateral PID settings
                        angular_controller, // angular PID settings
                        sensors // odometry sensors
);