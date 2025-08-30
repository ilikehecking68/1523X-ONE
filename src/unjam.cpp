/*#include "main.h"

// Variables for the algorithm. Store these per motor since it's usually better
// to just unjam the intake stage that's actually jammed.

// Whether the unjam system is enabled or not. Could be useful during some auton
// routines where it's not such a good time to unjam.
bool enabled = true;

// When the current time, obtained with pros::millis() is less than this, it
// means that the motor should be unjamming. When you run the motor, just check
// if pros::millis() < unjam_end and if so run the motor in reverse.
uint32_t unjam_end = 0;

// If the motor efficiency is below this number, then the jam will be activated.
// Motor efficiency will be a number between 0 and 100, and is measured by how
// much the motor is rotating physically, divided by how much power is being put
// into the motor. So say I'm putting like a colossal amount of power into the
// motor but it's not moving, that probably mean's it's jamming.

// Anyways, 15 should be good for you but this may require tuning. If the unjam
// is running too much, decrease this number. If the jam is not running, make
// this number bigger. Be careful though.
const double jam_severity_tolerance = 15;

// How many milliseconds the motor can be jammed before activating the unjam.
// Seems a little counterintuitive, but if this number is too low then you might
// just unjam all the time.

// Again, 100 ms is a good start but tune to your need. Be careful though, since
// too low then the unjam will run when unintended and too high and the system
// will be a little unresponsive.
const uint32_t jam_time_tolerance = 100;

// Stores how long the motor has been jamming
uint32_t current_unjam_time = 0;

// How many milliseconds the unjam should run for. 120 is a good start, but you
// can change this for different stages. Maybe like 60-70 for the bottom stage,
// so you don't spit the balls out, and somewhere around 120 for higher stages
// for consistency.
const uint32_t unjam_time = 120;

// Meat of the algorithm right here. Call this method like every 10 ms or so,
// doesn't matter too much as long as you provide the time you wait as delta.
// What I mean is if you call it every 10 ms, the delta should be 10 and so on.
void unjam(const uint32_t delta) {
    // Store the current time in a variable for consistency and conciseness.
    const uint32_t time = pros::millis();

    // If this condition is true, it means the motor is jamming right now.
    if (
        // First, check if the jam is enabled and that we are not currently
        // running the unjam.
        enabled && unjam_end < time

        // Then, check if the motor is actually supposed to be running.
        && std::abs(target->get_target_velocity()) > 10

        // Lastly, check if the efficiency is less than the tolerance.
        // Efficiency will be a number 0 to 100, and is basically how much the
        // motor is running divided by how much power is being put in. So,
        // putting in a big amount of power but the motor doesn't move means
        // it's jammed.
        && target->get_efficiency() <= jam_severity_tolerance
    ) {
        // Track how many milliseconds the motor has been jammed
        current_jam_time += delta;
    }
    else {
        // If the motor isn't jammed right now, set the time the motor has been
        // jammed to 0.
        current_jam_time = 0;
    }

    // If we're jamming for a long enough time, activate the unjam
    if (current_jam_time >= jam_time_tolerance) {
        unjam_end = time + unjam_time;
        current_jam_time = 0;
    }
}*/