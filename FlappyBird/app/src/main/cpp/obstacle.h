//
// Created by Olmo on 13/06/2018.
//

#ifndef FLAPPYBIRD_OBSTACLE_H
#define FLAPPYBIRD_OBSTACLE_H

#include "sprite.h"

class Obstacle {
private:
    void setSpritesPositions();

    Sprite m_upper;
    Sprite m_lower;

    Vec3 m_position;
    Vec3 m_velocity;

    static float m_speed;
    static float m_gap;
    static uint32_t m_global_id;

    uint32_t m_id = 0;

    bool m_available = true;

public:
    Obstacle();
    ~Obstacle();

    Sprite* getUpperSprite();
    Sprite* getLowerSprite();

    bool isAvailable() const;
    void setUnavailable();
    void setAvailable();

    Vec3 getPosition() const;
    void setPosition(const Vec3& position);
    void setPosition(float x, float y, float z);

    uint32_t getID() const;

    void update(float dt);
};

#endif //FLAPPYBIRD_OBSTACLE_H
