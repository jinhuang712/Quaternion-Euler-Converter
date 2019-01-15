#include "util.h"

#include <stdio.h>
#include <math.h>
#include <cmath>
#include <QtMath>

Quaternion::Quaternion()
{
    this->scalar = 1.0;
    this->x = 0.0;
    this->y = 0.0;
    this->z = 0.0;
}

Quaternion::Quaternion(double scalar, double x, double y, double z)
{
    this->scalar = scalar;
    this->x = x;
    this->y = y;
    this->z = z;
}

Euler Quaternion::toEuler() {
    Euler e;
    // roll (x-axis rotation)
    double sinr_cosp = +2.0 * (scalar * x + y * z);
    double cosr_cosp = +1.0 - 2.0 * (x * x + y * y);
    e.x = atan2(sinr_cosp, cosr_cosp);

    // pitch (y-axis rotation)
    double sinp = +2.0 * (scalar * y - z * x);
    if (fabs(sinp) >= 1)
        e.y = copysign(M_PI_2, sinp); // use 90 degrees if out of range
    else
        e.y = asin(sinp);

    // yaw (z-axis rotation)
    double siny_cosp = +2.0 * (scalar * z + x * y);
    double cosy_cosp = +1.0 - 2.0 * (y * y + z * z);
    e.z = atan2(siny_cosp, cosy_cosp);
    return e;
}


Euler::Euler()
{
    this->x = 0.0;
    this->y = 0.0;
    this->z = 0.0;
}

Euler::Euler(double roll, double pitch, double yaw)
{
    this->x = roll;
    this->y = pitch;
    this->z = yaw;
}

Quaternion Euler::toQuaternion() {
    double cy = cos(z * 0.5);
    double sy = sin(z * 0.5);
    double cp = cos(y * 0.5);
    double sp = sin(y * 0.5);
    double cr = cos(x * 0.5);
    double sr = sin(x * 0.5);

    Quaternion q;
    q.scalar = cy * cp * cr + sy * sp * sr;
    q.x = cy * cp * sr - sy * sp * cr;
    q.y = sy * cp * sr + cy * sp * cr;
    q.z = sy * cp * cr - cy * sp * sr;
    return q;
}