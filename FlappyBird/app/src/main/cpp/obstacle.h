//
// Created by Olmo on 13/06/2018.
//

#ifndef FLAPPYBIRD_OBSTACLE_H
#define FLAPPYBIRD_OBSTACLE_H

#include <random>

#include "sprite.h"

class Obstacle {
private:
    static std::mt19937 m_random_generator;

    Sprite m_upper;
    Sprite m_lower;

    Vec3 m_position;
    Vec3 m_velocity;

    static float m_speed;
    static float m_gap;
    static uint32_t m_global_id;
    static bool m_random_generator_seeded;
    static bool m_can_move;

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

    void setSpritesPositions();
    void setSpritesXPositions(float pos);
    void moveSpritesBy(const Vec3& offset);
    void randomizeSpritesTint();
    void randomizeHeight();

    static void stop();
    static void start();

    void update(float dt);
};

#endif //FLAPPYBIRD_OBSTACLE_H
