//
// Created by Mac Mini on 14/06/2018.
//

#ifndef FLAPPYBIRD_PLAYER_H
#define FLAPPYBIRD_PLAYER_H

#include "sprite.h"

class Player {
private:
    Sprite m_sprite;

    Vec3 m_velocity;
    float m_y_velocity = 0.0f;
    float m_y_force = 0.0f;
    float m_floor_limit = -0.91f;
    float m_impulse_amount = 100.0f;

public:
    Player();
    ~Player();

    Sprite* getSprite();

    void addForce();

    void update(float dt);
};

#endif //FLAPPYBIRD_PLAYER_H
