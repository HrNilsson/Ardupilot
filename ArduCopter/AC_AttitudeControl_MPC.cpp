
#include "AC_AttitudeControl_MPC.h"
//#include "stdio.h"
#include <AP_Math/AP_Math.h>

//inits midaco
void AC_AttitudeControl_MPC::initMPC()
{
    Midaco::midaco_init();
    //fprintf(stderr,"INIT MPC\r\n");
    //fprintf(stderr,"WyG first: %d\r\n",convert(WyG[0][0]));
	/*y[0][0] = 0.218f;
	y[1][0] = -0.074f;
	y[2][0] = 0.0f;
	dx[0][0] = -0.003f;
	dx[1][0] = -0.243f;
	dx[2][0] = 0.0f;
	dx[3][0] = 0.061f;
	dx[4][0] = 0.0f;
	dx[5][0] = 0.0f;
	updateMatrices(0.0f,0.0f,0.0f);
	solve();*/
}

//updates dx and y
void AC_AttitudeControl_MPC::updateState()
{
	float cutoff_freq = 0.1f;
	float dt = 100.0f;
	float rc = 1.0f/(M_2PI_F*cutoff_freq);
	float alpha = constrain_float(dt/(dt+rc), 0.0f, 1.0f);

	dx1_old += ((_ahrs.get_gyro().x - old_x[1]) - dx1_old) * alpha;
	dx3_old += ((_ahrs.get_gyro().y - old_x[3]) - dx3_old) * alpha;
	dx5_old += ((_ahrs.get_gyro().z - old_x[5]) - dx5_old) * alpha;

    dx[0][0] = (double)_ahrs.roll -         old_x[0];
    //dx[1][0] = (double)(_ahrs.get_gyro().x - old_x[1]);
    dx[2][0] = (double)_ahrs.pitch -        old_x[2];
    //dx[3][0] = (double)(_ahrs.get_gyro().y - old_x[3]);
    dx[4][0] = (double)_ahrs.yaw -          old_x[4];
    //dx[5][0] = (double)(_ahrs.get_gyro().z - old_x[5]);

    dx[1][0] = dx1_old;
    dx[3][0] = dx3_old;
    dx[5][0] = dx5_old;

    //dx[1][0] = dx1_filter.apply((double)_ahrs.get_gyro().x - old_x[1], 0.01f);
    //dx[3][0] = dx3_filter.apply((double)_ahrs.get_gyro().y - old_x[3], 0.01f);
    //dx[5][0] = dx5_filter.apply((double)_ahrs.get_gyro().z - old_x[5], 0.01f);

    old_x[0] = (double)_ahrs.roll;
    old_x[1] = (double)_ahrs.get_gyro().x;
    old_x[2] = (double)_ahrs.pitch;
    old_x[3] = (double)_ahrs.get_gyro().y;
    old_x[4] = (double)_ahrs.yaw;
    old_x[5] = (double)_ahrs.get_gyro().z;

    y[0][0] = (double)_ahrs.roll;
    y[1][0] = (double)_ahrs.pitch;
    y[2][0] = (double)_ahrs.yaw;

    //
    /*dx[2][0] = 0;
	dx[3][0] = 0;
	old_x[2] = 0;
	old_x[3] = 0;
	y[1][0] = 0;
    dx[4][0] = 0;
    dx[5][0] = 0;
    old_x[4] = 0;
    old_x[5] = 0;
    y[2][0] = 0;*/

    //fprintf(stderr,"ahrs angle: %d, %d, %d\r\n",convert(_ahrs.roll),convert(_ahrs.pitch),convert(_ahrs.yaw));
    //fprintf(stderr,"ahrs vel: %d, %d, %d\r\n",convert(_ahrs.get_gyro().x),convert(_ahrs.get_gyro().y),convert(_ahrs.get_gyro().z));
    //fprintf(stderr,"y: %d, %d, %d\r\n",convert(y[0][0]),convert(y[1][0]),convert(y[2][0]));
    //fprintf(stderr,"dx: %d, %d, %d, %d, %d, %d\r\n",convert(dx[0][0]),convert(dx[1][0]),convert(dx[2][0]),convert(dx[3][0]),convert(dx[4][0]),convert(dx[5][0]));
}

//calculates f
void AC_AttitudeControl_MPC::updateMatrices(double rollTarget, double pitchTarget, double yawTarget)
{
	_angle_ef_target.x = RadiansToCentiDegrees((float)(rollTarget));
	_angle_ef_target.y = RadiansToCentiDegrees((float)(pitchTarget));
	_angle_ef_target.z = RadiansToCentiDegrees((float)(yawTarget));
	//fprintf(stderr,"Targets: %d, %d, %d\r\n",convert(_angle_ef_target.x),convert(_angle_ef_target.y),convert(_angle_ef_target.z));

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

    /*fprintf(stderr,"f: %d, %d, %d\r\n",convert(f[0][0]),convert(f[1][0]),convert(f[2][0]));
    fprintf(stderr,"f: %d, %d, %d\r\n",convert(_f[0][0]),convert(_f[1][0]),convert(_f[2][0]));
    */
}

//Invokes the midaco solver
void AC_AttitudeControl_MPC::solve()
{
    double ftemp[3];

    // Define starting point x
    for(int i=0; i<3; i++)
    {
        Midaco::g_x[i] = 0.0;
    }

    // convert double pointer to single array
    ftemp[0] = _f[0][0];
    ftemp[1] = _f[1][0];
    ftemp[2] = _f[2][0];

    //fprintf(stderr,"f: %d, %d, %d\r\n",convert(ftemp[0]),convert(ftemp[1]),convert(ftemp[2]));
    //fprintf(stderr,"K: %d, %d, %d\r\n",convert(Midaco::getgK1()),convert(Midaco::getgK2()),convert(Midaco::getgK3()));
    //fprintf(stderr,"x: %d, %d, %d\r\n",convert(Midaco::getgx1()),convert(Midaco::getgx2()),convert(Midaco::getgx3()));
    Midaco::optimize(ftemp);
	//fprintf(stderr,"Solver out: %d, %d, %d\r\n",convert(getx1()),convert(getx2()),convert(getx3()));
}

void AC_AttitudeControl_MPC::outputToMotor()
{
	float magic_number = 700; // TODO: MAGIC NUMBER

	//fprintf(stderr,"Motor setpoints: %d, %d, %d\r\n\r\n\r\n",(int)(magic_number*getx1()),(int)(magic_number*getx2()),(int)(magic_number*getx3()));

    _motors.set_roll(magic_number*getx1());
    _motors.set_pitch(magic_number*getx2());
    // Do not control yaw position, since it is fixed in the testbed.
    _motors.set_yaw(0);//magic_number*getx3());
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

int AC_AttitudeControl_MPC::convert(double d)
{
	return (int)(d*1000);
}

