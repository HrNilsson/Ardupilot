/// -*- tab-width: 4; Mode: C++; c-basic-offset: 4; indent-tabs-mode: nil -*-

#include "Copter.h"
//#include <AP_HAL/AP_HAL.h>
//#include <AP_HAL/AP_HAL_Namespace.h>
#include "AC_AttitudeControl_MPC.h"




// stabilize_init - initialise stabilize controller
bool Copter::MPC_test_init(bool ignore_checks)
{
    // set target altitude to zero for reporting
    // To-Do: make pos controller aware when it's active/inactive so it can always report the altitude error?
    pos_control.set_alt_target(0);

    /*test_sequence[0] = {0,0};           // Starting position
    test_sequence[1] = {3000,0};        // Roll right
    test_sequence[2] = {0,0};           // Hover
    test_sequence[3] = {-3000,0};       // Roll left
    test_sequence[4] = {0,0};           // Hover
    test_sequence[5] = {0,3000};        // Pitch nose up
    test_sequence[6] = {0,0};           // Hover
    test_sequence[7] = {0,-3000};       // Pitch nose down
    test_sequence[8] = {0,0};           // Hover
    test_sequence[9] = {3000,3000};     // Roll right, nose up
    test_sequence[10] = {0,0};          // Hover
    test_sequence[11] = {3000,-3000};   // Roll right, nose down
    test_sequence[12] = {0,0};          // Hover
    test_sequence[13] = {-3000,3000};   // Roll left, nose up
    test_sequence[14] = {0,0};          // Hover
    test_sequence[15] = {-3000,-3000};  // Roll left, nose down
    test_sequence[16] = {0,0};          // Hover

    // Start the test at the starting position
    test_iterator = 0;

    // Register the advance test function to be called on a timer interrupt from the HAL
    hal.scheduler->register_timer_process(FUNCTOR_BIND_MEMBER(&Copter::advance_test, void));
*/

    attitude_control_mpc.initMPC();


    // stabilize should never be made to fail
    return true;
}


// stabilize_run - runs the main stabilize controller
// should be called at 100hz or more
void Copter::MPC_test_run()
{
    float target_roll, target_pitch;
    float target_yaw_rate = 0;
    int16_t pilot_throttle_scaled;

    // if not armed or throttle at zero, set throttle to zero and exit immediately
    if(!motors.armed() || ap.throttle_zero) {
        attitude_control.set_throttle_out_unstabilized(0,true,g.throttle_filt);
        // slow start if landed
        if (ap.land_complete) {
            motors.slow_start(true);
        }
        return;
    }

    // apply SIMPLE mode transform to pilot inputs
    update_simple_mode();

    // convert pilot input to lean angles
    // To-Do: convert get_pilot_desired_lean_angles to return angles as floats
    get_pilot_desired_lean_angles(channel_roll->control_in, channel_pitch->control_in, target_roll, target_pitch, aparm.angle_max);

    // get pilot's desired yaw rate
    //target_yaw_rate = get_pilot_desired_yaw_rate(channel_yaw->control_in);

    // get pilot's desired throttle
    pilot_throttle_scaled = get_pilot_desired_throttle(channel_throttle->control_in);


    attitude_control_mpc.updateState();
    attitude_control_mpc.updateMatrices(target_roll, target_pitch, target_yaw_rate);
    attitude_control_mpc.solve();
    attitude_control_mpc.outputToMotor();

    // call attitude controller
    //attitude_control.angle_ef_roll_pitch_rate_ef_yaw_smooth(test_sequence[test_iterator].targetRoll, test_sequence[test_iterator].targetPitch, target_yaw_rate, get_smoothing_gain());
    //attitude_control.angle_ef_roll_pitch_rate_ef_yaw_smooth(target_roll, target_pitch, target_yaw_rate, get_smoothing_gain());


    // body-frame rate controller is run directly from 100hz loop

    // output pilot's throttle
    attitude_control.set_throttle_out(pilot_throttle_scaled, true, g.throttle_filt);
}






