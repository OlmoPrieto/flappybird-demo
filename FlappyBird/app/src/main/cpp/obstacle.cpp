//
// Created by Mac Mini on 13/06/2018.
//

#include <android/log.h>

#include "obstacle.h"

float Obstacle::m_speed = 0.00075f;
float Obstacle::m_gap   = 0.15f;
uint32_t Obstacle::m_global_id = 0;

Obstacle::Obstacle() {
    // Sprite constructors are called first

    m_upper.setScale(0.1f, 1.0f - m_gap, 1.0f);
    m_lower.setScale(0.1f, 1.0f - m_gap, 1.0f);

    uint32_t random = (uint32_t)rand() % 75;    // max of half the screen up or down
    float height = (float)random / 100.0f;

    if (rand() % 1 == 0) {  // decide if up or down
        height = -height;   // multiplying by -1.0f is another operation, so don't do it
    }

    m_upper.setPositionY(0.0f + m_gap + 1.0f + height);
    m_lower.setPositionY(0.0f - m_gap - 1.0f + height);

    Color color(Color::randomColor());

    uint8_t** texture_data = m_upper.getTextureData();
    SetTextureColor(*texture_data, m_upper.getTextureWidth(),
                    m_upper.getTextureHeight(), color);
    m_upper.setTextureData(texture_data);

    texture_data = m_lower.getTextureData();
    SetTextureColor(*texture_data, m_lower.getTextureWidth(),
                    m_lower.getTextureHeight(), color);
    m_lower.setTextureData(texture_data);

    m_velocity.x = -1.0f;   // move to the left

    m_id = ++m_global_id;   // pre-increment global_id;
}

Obstacle::~Obstacle() {

}

Sprite* Obstacle::getUpperSprite() {
    return &m_upper;
}

Sprite* Obstacle::getLowerSprite() {
    return &m_lower;
}

bool Obstacle::isAvailable() const {
    return m_available;
}

void Obstacle::setAvailable() {
    m_available = true;
}

void Obstacle::setUnavailable() {
    m_available = false;
}

Vec3 Obstacle::getPosition() const {
    return m_position;
}

void Obstacle::setSpritesPositions() {
    Vec3 pos = m_upper.getPosition();
    m_upper.setPosition(m_position.x + pos.x, m_position.y + pos.y, m_position.z + pos.z);
    pos = m_lower.getPosition();
    m_lower.setPosition(m_position.x + pos.x, m_position.y + pos.y, m_position.z + pos.z);
}

void Obstacle::setPosition(const Vec3 &position) {
    m_position = position;

    setSpritesPositions();
}

void Obstacle::setPosition(float x, float y, float z) {
    m_position.x = x;
    m_position.y = y;
    m_position.z = z;

    setSpritesPositions();
}

uint32_t Obstacle::getID() const {
    return m_id;
}

void Obstacle::update(float dt) {
    m_position.x -= m_speed * dt;

    Vec3 pos = m_upper.getPosition();
    m_upper.setPositionX(pos.x - m_speed * dt);
    pos = m_lower.getPosition();
    m_lower.setPositionX(pos.x - m_speed * dt);
}