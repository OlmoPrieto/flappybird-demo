//
// Created by Mac Mini on 13/06/2018.
//

#include <android/log.h>

#include "obstacle.h"
#include "game.h"

std::mt19937 Obstacle::m_random_generator;

float Obstacle::m_speed = 0.7f;
float Obstacle::m_gap   = Game::m_render_height * 0.15;
uint32_t Obstacle::m_global_id = 0;
bool Obstacle::m_random_generator_seeded = false;
bool Obstacle::m_can_move = false;

Obstacle::Obstacle() {
    // Sprite constructors are called first

    if (m_random_generator_seeded == false) {
        m_random_generator.seed(std::chrono::duration_cast<std::chrono::duration<int32_t > >(std::chrono::high_resolution_clock::now().time_since_epoch()).count());

        m_random_generator_seeded = true;
    }

    float w = (float)(Game::m_render_width) * 0.08f * Game::m_render_width / Game::m_render_desired_width;
    float h = (float)(Game::m_render_height) * 0.5f * Game::m_render_height / Game::m_render_desired_height - m_gap;
    m_upper.setScale(w, h, 1.0f);
    m_lower.setScale(w, h, 1.0f);

    randomizeHeight();

    Color color(Color::randomColor());

    uint8_t* texture_data = m_upper.getTextureData();
    SetTextureColor(texture_data, m_upper.getTextureWidth(),
                    m_upper.getTextureHeight(), color);
    m_upper.setTextureData(texture_data);

    texture_data = m_lower.getTextureData();
    SetTextureColor(texture_data, m_lower.getTextureWidth(),
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

Vec3 Obstacle::getPosition() const {
    return m_position;
}

void Obstacle::setSpritesPositions() {
    Vec3 pos = m_upper.getPosition();
    m_upper.setPosition(m_position.x + pos.x, m_position.y + pos.y, m_position.z + pos.z);
    pos = m_lower.getPosition();
    m_lower.setPosition(m_position.x + pos.x, m_position.y + pos.y, m_position.z + pos.z);
}

void Obstacle::setSpritesXPositions(float pos) {
    m_upper.setPositionX(pos);
    m_lower.setPositionX(pos);
}

void Obstacle::moveSpritesBy(const Vec3& offset) {
    Vec3 pos = m_upper.getPosition();
    m_upper.setPosition(offset.x + pos.x, offset.y + pos.y, offset.z + pos.z);
    pos = m_lower.getPosition();
    m_lower.setPosition(offset.x + pos.x, offset.y + pos.y, offset.z + pos.z);
}

void Obstacle::setPosition(const Vec3 &position) {
    m_position = position;

    //setSpritesPositions();
}

void Obstacle::setPosition(float x, float y, float z) {
    m_position.x = x;
    m_position.y = y;
    m_position.z = z;
}

uint32_t Obstacle::getID() const {
    return m_id;
}

void Obstacle::randomizeSpritesTint() {
    Color color;
    color.r = (uint8_t)m_random_generator() % 255;
    color.g = (uint8_t)m_random_generator() % 255;
    color.b = (uint8_t)m_random_generator() % 255;
    //color.a = (uint8_t)m_random_generator() % 255;
    color.a = 255;

    if (color.r < 128) {
        color.r = 128;
    }
    if (color.g < 128) {
        color.g = 128;
    }if (color.b < 128) {
        color.b = 128;
    }

    m_upper.setColor(color);
    m_lower.setColor(color);
}

void Obstacle::randomizeHeight() {
    float random = 0;
    // if it only generates once, the distribution isn't that good
    // and repeated or similar values appear
    for (uint8_t i = 0; i < 64; ++i) {
        random = (float)((uint32_t)m_random_generator() % (uint32_t)((float)(Game::m_render_height) * 0.25f));
    }

    if ((uint32_t)m_random_generator() % 100 >= 50) {  // decide if up or down
        random = -random;   // multiplying by -1.0f is another operation, so don't do it
    }

    m_upper.setPositionY((float)(Game::m_render_height) + random);
    m_lower.setPositionY(0.0f + random);
}

void Obstacle::setHeight(float height) {
    m_upper.setPositionY((float)(Game::m_render_height) + height);
    m_lower.setPositionY(0.0f + height);
}

void Obstacle::stop() {
    m_can_move = false;
}

void Obstacle::start() {
    m_can_move = true;
}

void Obstacle::update(float dt) {
    if (m_can_move == true) {
        m_position.x -= m_speed * dt;

        Vec3 pos = m_upper.getPosition();
        m_upper.setPositionX(pos.x - m_speed * dt);
        pos = m_lower.getPosition();
        m_lower.setPositionX(pos.x - m_speed * dt);
    }
}