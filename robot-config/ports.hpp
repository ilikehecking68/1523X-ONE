#pragma once

#include "main.h"

typedef std::int8_t robot_port;

//------------------------------------CONFIGURATION----------------------------------------------
//                                                                                              |

inline pros::MotorGroup left_dt_mg({-1, 7, -10});
inline pros::MotorGroup right_dt_mg({11, -20, 15});

inline pros::Motor left_pto(9);
inline pros::Motor right_pto(-2);

inline pros::ADIDigitalOut pto('A');

inline pros::ADIDigitalOut match_loader('H');

inline pros::ADIDigitalOut park('G');

//                                                                                              |
//-----------------------------------------------------------------------------------------------