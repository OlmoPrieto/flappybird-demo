//
// Created by Mac Mini on 14/06/2018.
//

#include <android/log.h>

#include "player.h"
#include "game.h"

Player::Player() {
    float scale = Game::m_render_width * 0.066f;
    m_sprite.setScale(scale, scale, 1.0f);

    m_floor_limit = 0.0f + scale;
    m_ceil_limit = (float)(Game::m_render_height) - scale;

    uint8_t* texture_data = m_sprite.getTextureData();
    CreateCircleInTexture(texture_data, m_sprite.getTextureWidth(),
                    m_sprite.getTextureHeight(), Color(255, 0, 0, 255));
    m_sprite.setTextureData(texture_data);
}

Player::~Player() {

}

Vec3 Player::getPosition() const {
    return m_sprite.getPosition();
}

Sprite* Player::getSprite() {
    return &m_sprite;
}

void Player::setPosition(const Vec3 &pos) {
    m_sprite.setPosition(pos);
}

void Player::setPosition(float x, float y, float z) {
    m_sprite.setPosition(x, y, z);
}

void Player::setYVelocity(float velocity) {
    m_y_velocity = velocity;
}

void Player::addForce() {
    if (m_can_move == true) {
        m_y_velocity = m_impulse_amount;
    }
}

void Player::setCollideState(bool state) {
    m_can_collide = state;
}

bool Player::checkCollisionWithObstaclePart(const Vec3 &o_pos, const Vec3 &o_scale) {
    Vec3 pos = m_sprite.getPosition();
    Vec3 scale = m_sprite.getScale();

    float d_x = fabs(pos.x - o_pos.x);
    float d_y = fabs(pos.y - o_pos.y);

    if (d_x > (o_scale.x + scale.x) || d_y > (o_scale.y + scale.y)) {
        return false;
    }

    if (d_x <= o_scale.x || d_y <= o_scale.y) {
        return true;
    }

    float corner_d_sq = (d_x - o_scale.x) * (d_x - o_scale.x) +
                        (d_y - o_scale.y) * (d_y - o_scale.y);

    if (corner_d_sq <= scale.x * scale.x) {
        return true;
    }

    return false;
}

bool Player::checkCollision(Obstacle *obs) {
    if (m_can_collide == true) {
        return checkCollisionWithObstaclePart(obs->getUpperSprite()->getPosition(),
                                       obs->getUpperSprite()->getScale())

         ||

        checkCollisionWithObstaclePart(obs->getLowerSprite()->getPosition(),
                                       obs->getLowerSprite()->getScale());
    }

    return false;
}

bool Player::isTouchingGround() {
    return m_sprite.getPosition().y == m_floor_limit;
}

bool Player::isTouchingCeiling() {
    return m_sprite.getPosition().y >= m_ceil_limit;
}

void Player::stop() {
    m_can_move = false;
}

void Player::start() {
    m_can_move = true;
}

void Player::placeAtCollisionPoint(Obstacle* obs) {
    float last_dt = Game::Instance()->getLastFrameDT();

    Vec3 pos = getPosition();
    Vec3 upper_pos = obs->getUpperSprite()->getPosition();
    Vec3 lower_pos = obs->getLowerSprite()->getPosition();

    float distance_to_upper = (pos.x - upper_pos.x) * (pos.x - upper_pos.x) +
                              (pos.y - upper_pos.y) * (pos.y - upper_pos.y);
    float distance_to_lower = (pos.x - lower_pos.x) * (pos.x - lower_pos.x) +
                              (pos.y - lower_pos.y) * (pos.y - lower_pos.y);

    move(m_prev_pos, last_dt * 0.1f);
    if (distance_to_upper < distance_to_lower) {
        addForce();
    }

    while (!checkCollision(obs)) {
        move(getPosition(), last_dt * 0.1f);
        if (distance_to_upper < distance_to_lower) {
            addForce();
        }
    }

    m_y_velocity = m_prev_y_velocity;
}

void Player::move(const Vec3& origin_position, float dt) {
    Vec3 pos = origin_position;
    float acceleration = m_y_force + m_gravity;

    m_y_velocity += m_speed + acceleration * dt;

    pos.y += m_y_velocity * dt + 0.5f * acceleration * (dt * dt);

    if (pos.y < m_floor_limit) {
        pos.y = m_floor_limit;
    }

    m_sprite.setPositionY(pos.y);

    m_y_force = 0.0f;
}

void Player::update(float dt) {
    if (m_can_move == true) {
        Vec3 pos = m_sprite.getPosition();
        m_prev_pos = pos;

        move(pos, dt);

        m_prev_y_velocity = m_y_velocity;
    }
}