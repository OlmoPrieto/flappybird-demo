//
// Created by Olmo on 10/06/2018.
//

#include "sprite.h"

Sprite::Sprite() {
    m_color = Color(255, 0, 0, 255);
}

Sprite::~Sprite() {

}

Color Sprite::getColor() const {
    return m_color;
}

Vec3 Sprite::getPosition() {
    return m_position;
}

void Sprite::update(float dt) {
    m_position.x += 0.001f * dt;
}