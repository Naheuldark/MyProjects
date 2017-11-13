#include "Camera.h"

#include <iostream>


void computePos(float deltaForward, float deltaRight) 
{
    if (deltaForward) {
        x += deltaForward * lx * 0.1f;
        z += deltaForward * lz * 0.1f;
    }
    if (deltaRight) {
        x -= deltaRight * lz * 0.1f;
        z += deltaRight * lx * 0.1f;
    }
}