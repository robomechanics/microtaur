#pragma once
#include "motor.h"

typedef std::array<double, 2> Vector2d;

typedef enum {
    M1 = 0,
    M2
} motor_num_t

class Leg{
    private
        Vector2d zeros_;
        Vector2d state_;
        Vector2d cmd_;
        std::array<Motor, 2> motors_;

    public:
        Vector2d fk(Vector2d joints);
        Vector2d ik(Vector2d joints);
        void set_zeros(Vector2d);
        void set(Vector2d joints);
        vod get(Vector2d joints);
        
}