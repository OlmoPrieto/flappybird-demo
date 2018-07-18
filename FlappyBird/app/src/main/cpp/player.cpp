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

//bool Player::checkCollision(Obstacle *obs) {
//    if (m_can_collide == true) {
//
//        float up = 0.0f;
//        float ri = 0.0f;
//        float bo = 0.0f;
//        float le = 0.0f;
//        float oup = 0.0f;
//        float ori = 0.0f;
//        float obo = 0.0f;
//        float ole = 0.0f;
//
//        Vec3 pos = m_sprite.getPosition();
//        Vec3 scale = m_sprite.getScale();
//
//        Vec3 other_pos;
//        Vec3 other_scale;
//
//        // Check player's upper Bounding Box against the obstacle
//        other_pos = obs->getUpperSprite()->getPosition();
//        other_scale = obs->getUpperSprite()->getScale();
//
//        up = pos.y + scale.y;
//        ri = pos.x + scale.x * 0.85f;
//        bo = pos.y + scale.y * 0.85f;
//        le = pos.x - scale.x * 0.85f;
//
//        oup = other_pos.y + other_scale.y;
//        ori = other_pos.x + other_scale.x;
//        obo = other_pos.y - other_scale.y;
//        ole = other_pos.x - other_scale.x;
//
//        if (ri >= ole && le <= ori && up >= obo && bo <= oup) {
//            //__android_log_print(ANDROID_LOG_INFO, "LOG", "UP Collided with top!\n");
//            return true;
//        } else {
//            other_pos = obs->getLowerSprite()->getPosition();
//            other_scale = obs->getLowerSprite()->getScale();
//
//            oup = other_pos.y + other_scale.y;
//            ori = other_pos.x + other_scale.x;
//            obo = other_pos.y - other_scale.y;
//            ole = other_pos.x - other_scale.x;
//
//            if (ri >= ole && le <= ori && up >= obo && bo <= oup) {
//                //__android_log_print(ANDROID_LOG_INFO, "LOG", "UP Collided with bottom!\n");
//                return true;
//            }
//        }
//
//        // Check player's right Bounding Box against the obstacle
//        other_pos = obs->getUpperSprite()->getPosition();
//        other_scale = obs->getUpperSprite()->getScale();
//
//        up = pos.y + scale.y * 0.85f;
//        ri = pos.x + scale.x;
//        bo = pos.y - scale.y * 0.85f;
//        le = pos.x + scale.x * 0.85f;
//
//        oup = other_pos.y + other_scale.y;
//        ori = other_pos.x + other_scale.x;
//        obo = other_pos.y - other_scale.y;
//        ole = other_pos.x - other_scale.x;
//
//        if (ri >= ole && le <= ori && up >= obo && bo <= oup) {
//            //__android_log_print(ANDROID_LOG_INFO, "LOG", "RIGHT Collided with top!\n");
//            return true;
//        } else {
//            other_pos = obs->getLowerSprite()->getPosition();
//            other_scale = obs->getLowerSprite()->getScale();
//
//            oup = other_pos.y + other_scale.y;
//            ori = other_pos.x + other_scale.x;
//            obo = other_pos.y - other_scale.y;
//            ole = other_pos.x - other_scale.x;
//
//            if (ri >= ole && le <= ori && up >= obo && bo <= oup) {
//                //__android_log_print(ANDROID_LOG_INFO, "LOG", "RIGHT Collided with bottom!\n");
//                return true;
//            }
//        }
//
//        // Check player's bottom Bounding Box against the obstacle
//        other_pos = obs->getUpperSprite()->getPosition();
//        other_scale = obs->getUpperSprite()->getScale();
//
//        up = pos.y - scale.y * 0.85f;
//        ri = pos.x + scale.x * 0.85f;
//        bo = pos.y - scale.y;
//        le = pos.x - scale.x * 0.85f;
//
//        oup = other_pos.y + other_scale.y;
//        ori = other_pos.x + other_scale.x;
//        obo = other_pos.y - other_scale.y;
//        ole = other_pos.x - other_scale.x;
//
//        if (ri >= ole && le <= ori && up >= obo && bo <= oup) {
//            //__android_log_print(ANDROID_LOG_INFO, "LOG", "BOTTOM Collided with top!\n");
//            return true;
//        } else {
//            other_pos = obs->getLowerSprite()->getPosition();
//            other_scale = obs->getLowerSprite()->getScale();
//
//            oup = other_pos.y + other_scale.y;
//            ori = other_pos.x + other_scale.x;
//            obo = other_pos.y - other_scale.y;
//            ole = other_pos.x - other_scale.x;
//
//            if (ri >= ole && le <= ori && up >= obo && bo <= oup) {
//                //__android_log_print(ANDROID_LOG_INFO, "LOG", "BOTTOM Collided with bottom!\n");
//                return true;
//            }
//        }
//
//        // There is no check with the player's left Bounding Box
//        // because it's impossible that the player collided with
//        // an obstacle from behind
//    }
//
//
//    return false;
//}

//bool Player::checkCollision(Obstacle *obs) {
//    float x_side = 0.0f;
//    float y_side = 0.0f;
//    float dx = 0.0f;
//    float dy = 0.0f;
//    Vec3 other_pos;
//    Vec3 other_scale;
//    Vec3 pos = m_sprite.getPosition();
//    Vec3 scale = m_sprite.getScale();
//
//    float s_radius = scale.x * scale.x; // its the same in x and y
//
//    // check against every side
//
//    //  bottom side
//    other_pos = obs->getUpperSprite()->getPosition();
//    other_scale = obs->getUpperSprite()->getScale();
//
//    x_side = other_pos.x;
//    y_side = other_pos.y - other_scale.y;
//
//    dx = pos.x - x_side;
//    dy = pos.y - y_side;
//
//    dx *= dx;
//    dy *= dy;
//    if (dx + dy <= s_radius) {
//        return true;
//    }
//
//
//    return false;
//}

bool Player::checkCollision(Obstacle *obs) {
    bool result = false;

    Vec3 pos = m_sprite.getPosition();
    Vec3 scale = m_sprite.getScale();

    // Check upper obstacle
    Vec3 other_pos = obs->getUpperSprite()->getPosition();
    Vec3 other_scale = obs->getUpperSprite()->getScale();

    float d_x = fabs(pos.x - other_pos.x);
    float d_y = fabs(pos.y - other_pos.y);

    if (d_x > (other_scale.x + scale.x) || d_y > (other_scale.y + scale.y)) {
        //return false;
    }

    if (d_x <= other_scale.x || d_y <= other_scale.y) {
        __android_log_print(ANDROID_LOG_DEBUG, "LOG", "FUCK MORTY\n");
        //return true;
        result = true;
    }

    float corner_d_sq = (d_x - other_scale.x) * (d_x - other_scale.x) +
                        (d_y - other_scale.y) * (d_y - other_scale.y);

    if (corner_d_sq <= scale.x * scale.x) {
        return true;
    }

    // Check lower obstacle
    other_pos = obs->getLowerSprite()->getPosition();
    other_scale = obs->getLowerSprite()->getScale();
    d_x = fabs(pos.x - other_pos.x);
    d_y = fabs(pos.y - other_pos.y);

    if (d_x > (other_scale.x + scale.x) || d_y > (other_scale.y + scale.y)) {
        //return false;
        result = false;
    }

    if (d_x <= other_scale.x || d_y <= other_scale.y) {
        __android_log_print(ANDROID_LOG_DEBUG, "LOG", "GEEZ RICK\n");
        //return true;
        result = true;
    }

    corner_d_sq = (d_x - other_scale.x) * (d_x - other_scale.x) +
                  (d_y - other_scale.y) * (d_y - other_scale.y);

    if (corner_d_sq <= scale.x * scale.x) {
        return true;
    }

    return result;
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

void Player::update(float dt) {
    if (m_can_move == true) {
        Vec3 pos = m_sprite.getPosition();
        float acceleration = m_y_force + m_gravity;

        m_y_velocity += m_speed + acceleration * dt;

        pos.y += m_y_velocity * dt + 0.5f * acceleration * (dt * dt);

        if (pos.y < m_floor_limit) {
            pos.y = m_floor_limit;
        }

        m_sprite.setPositionY(pos.y);

        m_y_force = 0.0f;
    }
}