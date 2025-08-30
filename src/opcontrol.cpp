#include "ports.hpp"
#include "default_pto_mode.hpp"
#include "main.h"

static pto_mode pto_selected_mode = pto_default_selected_mode;

static void update_pto(pros::Controller& controller){
    if (controller.get_digital_new_press(DIGITAL_R1) || controller.get_digital_new_press(DIGITAL_L1) || controller.get_digital_new_press(DIGITAL_R2) || controller.get_digital_new_press(DIGITAL_L2)){
        pto_selected_mode = pto_mode_intake;
        pto.set_value(false);
        return;
    }

    if (controller.get_digital_new_press(DIGITAL_X)){
        pto_selected_mode = pto_mode_dt;
        pto.set_value(true);
    }
}

static void update_dt(pros::Controller& controller){
    const int linear = controller.get_analog(ANALOG_LEFT_Y);
    const int angular = controller.get_analog(ANALOG_RIGHT_X);

    left_dt_mg.move(linear + angular);
    right_dt_mg.move(linear - angular);

    if (pto_selected_mode != pto_mode_dt){
        return;
    }

    left_pto.move(linear + angular);
    right_pto.move(linear - angular);
}

static double low_speed = 1.0;
static bool update_intake_middle(pros::Controller& controller){
    if (controller.get_digital(DIGITAL_R1)){
        right_pto.move(-127);
        left_pto.move(-127 * low_speed);
        return true;
    }

    if (controller.get_digital(DIGITAL_R2)){
        right_pto.move(127);
        left_pto.move(78);
        return true;
    }

    return false;
}

static bool update_intake_high(pros::Controller& controller){
    if (controller.get_digital(DIGITAL_L1)){
        right_pto.move(127);
        left_pto.move(-127 * low_speed);
        return true;
    }

    if (controller.get_digital(DIGITAL_L2)){
        right_pto.move(-127);
        left_pto.move(78);
        return true;
    }

    return false;
}

static void update_intake(pros::Controller& controller){
    if (pto_selected_mode == pto_mode_dt){
        return;
    }

    if (!update_intake_high(controller) && 
        !update_intake_middle(controller)){
        right_pto.move(0);
        left_pto.move(0);
    }
    
}

static bool prev_pto = !pto_default_selected_mode;
static void update_pto_piston(){
    prev_pto = pto_selected_mode;
}

static bool match_loader_state = false;
static void update_match_loader(pros::Controller& controller){
    if (!controller.get_digital_new_press(DIGITAL_DOWN)){
        return;
    }

    match_loader_state = !match_loader_state;
    match_loader.set_value(match_loader_state);
}

static bool park_state = false;
static void update_park(pros::Controller& controller){
    if (!controller.get_digital_new_press(DIGITAL_B)){
        return;
    }

    park_state = !park_state;
    park.set_value(park_state);
}

static bool storing = false;
static bool storing_lower = false;

void update_storing(pros::Controller& controller){
    if (controller.get_digital_new_press(DIGITAL_LEFT)){
        storing = !storing;
    }

    if (!storing){
        low_speed = 1.0;
        return;
    }

    if (distance.get_distance() <= 203){
        low_speed = 0.5;
        right_pto.move(0);
        return;
    } else {
        low_speed = 1.0;
    }

    pto_selected_mode = pto_mode_intake;
    update_pto(controller);
    right_pto.move(127);
}

void opcontrol(){
    odom_raise.set_value(true);
    park.set_value(park_state);
    match_loader.set_value(match_loader_state);
    pros::Controller controller(pros::E_CONTROLLER_MASTER);
    while (true){
        update_dt(controller);
        update_pto(controller); //COMMENT THIS LINE FOR NO PTO
        update_intake(controller);
        update_match_loader(controller);
        update_park(controller);
        update_storing(controller);
        
        pros::delay(5);
    }
}