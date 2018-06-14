//
// Created by Mac Mini on 14/06/2018.
//

#include <android/log.h>

#include "player.h"

Player::Player() {
    m_sprite.setScale(0.15f, 0.09f, 1.0f);

    uint8_t** texture_data = m_sprite.getTextureData();
    CreateCircleInTexture(*texture_data, m_sprite.getTextureWidth(),
                    m_sprite.getTextureHeight(), Color(255, 0, 0, 255));
    m_sprite.setTextureData(texture_data);
}

Player::~Player() {

}

Sprite* Player::getSprite() {
    return &m_sprite;
}

void Player::addForce() {
    m_y_velocity = m_impulse_amount;
    __android_log_print(ANDROID_LOG_INFO, "LOG", "TOUCH!\n");
}

void Player::update(float dt) {
    Vec3 pos = m_sprite.getPosition();
    float gravity = 0.0f;//-0.000001f;
    float speed = -0.000075f;//1.0f;
    float acceleration = m_y_force + gravity;

    m_y_velocity += speed + acceleration * dt;

    pos.y += m_y_velocity * dt + 0.5f * acceleration * (dt * dt);

    if (pos.y < m_floor_limit) {
        pos.y = m_floor_limit;
    }

    m_sprite.setPositionY(pos.y);

    m_y_force = 0.0f;
}