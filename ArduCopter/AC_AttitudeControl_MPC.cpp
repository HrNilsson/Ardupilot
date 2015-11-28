/*
 * MPC.cpp
 *
 *  Created on: 22/11/2015
 *      Author: Ivan
 */


#include "AC_AttitudeControl_MPC.h"

//inits midaco
void AC_AttitudeControl_MPC::initMPC()
{
    Midaco::midaco_init();

}

//updates dx and y
void AC_AttitudeControl_MPC::updateState()
{
    dx[0][0] = (double)_ahrs.roll -         old_x[0];
    dx[1][0] = (double)_ahrs.get_gyro().x - old_x[1];
    dx[2][0] = (double)_ahrs.pitch -        old_x[2];
    dx[3][0] = (double)_ahrs.get_gyro().y - old_x[3];
    dx[4][0] = (double)_ahrs.yaw -          old_x[4];
    dx[5][0] = (double)_ahrs.get_gyro().z - old_x[5];

    old_x[0] = (double)_ahrs.roll;
    old_x[1] = (double)_ahrs.get_gyro().x;
    old_x[2] = (double)_ahrs.pitch;
    old_x[3] = (double)_ahrs.get_gyro().y;
    old_x[4] = (double)_ahrs.yaw;
    old_x[5] = (double)_ahrs.get_gyro().z;

    y[0][0] = (double)_ahrs.roll;
    y[1][0] = (double)_ahrs.pitch;
    y[2][0] = (double)_ahrs.yaw;

}

//calculates f
void AC_AttitudeControl_MPC::updateMatrices(double rollTarget, double pitchTarget, double yawTarget)
{
    // F
    Mmultiply(_IqTnQ, _dx, 90, 6, 6, 1, _temp1);
    Mmultiply(_IqC, _y, 90, 3, 3, 1, _temp2);
    Madd(_temp1, _temp2,90, 1, _F);

    // R
    for (int i = 0; i < 90; i += 3)
    {
        R[i][0] = rollTarget;
        R[i + 1][0] = pitchTarget;
        R[i + 2][0] = yawTarget;
    }

    // f
    Msubtract(_F, _R, 90, 1, _temp1);
    Mtranspose(_temp1, 90, 1, _temp3);
    Mmultiply(_temp3, _WyG, 1, 90, 90, 3, _temp4);
    MmultiplyScalar(_temp4, 1, 3, 2, _temp4);
    Mtranspose(_temp4, 1, 3, _f);

}

//Invokes the midaco solver
void AC_AttitudeControl_MPC::solve()
{
    double ftemp[3];

    // Define starting point x
    for(int i=0; i<3; i++)
    {
        Midaco::g_x[i] = 0.0;//xl[i]; // Here for example: starting point = lower bounds
    }

    // convert double pointer to single array
    ftemp[0] = _f[0][0];
    ftemp[1] = _f[1][0];
    ftemp[2] = _f[2][0];


    Midaco::optimize(ftemp);

}

void AC_AttitudeControl_MPC::outputToMotor()
{
    _motors.set_roll(50*getx1());
    _motors.set_pitch(50*getx2());
    _motors.set_yaw(50*getx3());
}



double AC_AttitudeControl_MPC::getf1()
{
    return _f[0][0];
}

double AC_AttitudeControl_MPC::getf2()
{
    return _f[1][0];
}

double AC_AttitudeControl_MPC::getf3()
{
    return _f[2][0];
}

double AC_AttitudeControl_MPC::getx1()
{
    return Midaco::getgx1();
}

double AC_AttitudeControl_MPC::getx2()
{
    return Midaco::getgx2();
}

double AC_AttitudeControl_MPC::getx3()
{
    return Midaco::getgx3();
}
