#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

// Right-Handed Coordinate Systems (same as OpenGL)
// pitch     yaw      roll
// attitude  heading  bank
// x         y        z
void EulerToQuaternion(float pitch, float yaw, float roll, float *quat)
{
    // Reference: https://github.com/ArduPilot/ardupilot/blob/master/libraries/AP_Math/quaternion.cpp
    // Assuming the angles are in radians.
    float cp2 = cos(pitch * 0.5f);
    float cy2 = cos(yaw * 0.5f);
    float cr2 = cos(roll * 0.5f);
    float sp2 = sin(pitch * 0.5f);
    float sy2 = sin(yaw * 0.5f);
    float sr2 = sin(roll * 0.5f);

    quat[0] = cp2 * cy2 * cr2 + sp2 * sy2 * sr2; // w
    quat[1] = sp2 * cy2 * cr2 + cp2 * sy2 * sr2; // x
    quat[2] = cp2 * sy2 * cr2 - sp2 * cy2 * sr2; // y
    quat[3] = cp2 * cy2 * sr2 - sp2 * sy2 * cr2; // z
}

void QuaternionToEuler(float *q, float &pitch, float &yaw, float &roll)
{
    // Reference: https://github.com/ArduPilot/ardupilot/blob/master/libraries/AP_Math/quaternion.cpp
    // Assuming the angles are in radians.
    pitch = asin(2.0f * (q[0] * q[1] - q[2] * q[3]));
    yaw = atan2(2.0f * (q[0] * q[2] + q[3] * q[1]), 1.0f - 2.0f * (q[1] * q[1] + q[2] * q[2]));
    roll = atan2(2.0f * (q[0] * q[3] + q[1] * q[2]), 1.0f - 2.0f * (q[3] * q[3] + q[1] * q[1]));
}

float DegreesToRadians(float degrees)
{
    return degrees * M_PI / 180;
}

float RadiansToDegrees(float radians)
{
    return radians * 180 / M_PI;
}