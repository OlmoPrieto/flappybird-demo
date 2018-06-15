//
// Created by Mac Mini on 14/06/2018.
//

#ifndef FLAPPYBIRD_PLAYER_H
#define FLAPPYBIRD_PLAYER_H

#include "sprite.h"
#include "obstacle.h"

class Player {
private:
    Sprite m_sprite;

    Vec3 m_velocity;
    float m_y_velocity = 0.0f;
    float m_y_force = 0.0f;
    float m_floor_limit = -0.91f;
    float m_impulse_amount = 0.0018f;

    bool m_can_move = false;

public:
    Player();
    ~Player();

    Sprite* getSprite();

    void addForce();

    bool checkCollision(Obstacle* obs);

    void stop();
    void start();

    void update(float dt);
};

#endif //FLAPPYBIRD_PLAYER_H
