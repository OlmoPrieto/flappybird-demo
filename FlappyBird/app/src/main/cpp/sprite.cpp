//
// Created by Olmo on 10/06/2018.
//

#include "sprite.h"

Sprite::Sprite() {
    m_scale.x = 1.0f;
    m_scale.y = 1.0f;
    m_scale.z = 1.0f;

    //m_color = Color((uint8_t)255, (uint8_t)0, (uint8_t)0, (uint8_t)255);
    m_color.setRandom();

    m_texture_width = 1024;
    m_texture_height = 1024;
    m_texture = (uint8_t*)malloc(m_texture_width * m_texture_height * 4);
    CreateCircleInTexture(m_texture, m_texture_width, m_texture_height, Color(255, 0, 0, 255));

    glGenTextures(1, &m_texture_id);
    glBindTexture(GL_TEXTURE_2D, m_texture_id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_texture_width, m_texture_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_texture);
    glBindTexture(GL_TEXTURE_2D, 0);
}

Sprite::~Sprite() {
    if (m_texture != nullptr) {
        free(m_texture);
    }
}

Color Sprite::getColor() const {
    return m_color;
}

Vec3 Sprite::getPosition() const {
    return m_position;
}

Vec3 Sprite::getScale() const {
    return m_scale;
}

uint32_t Sprite::getTextureHandler() const {
    return m_texture_id;
}

void Sprite::update(float dt) {
    m_position.x += 0.001f * dt;
}