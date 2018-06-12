//
// Created by Olmo on 10/06/2018.
//

#ifndef FLAPPYBIRD_SPRITE_H
#define FLAPPYBIRD_SPRITE_H

#include <GLES2/gl2.h>
#include "utils.h"

class Sprite {
private:
    Vec3 m_position;
    Vec3 m_scale;
    Color m_color;  // m_color is now used as tint in the shader

    GLuint m_texture_id = 0;

    uint32_t m_texture_width = 0;
    uint32_t m_texture_height = 0;
    uint8_t* m_texture = nullptr;

public:

    Sprite();
    ~Sprite();

    Color getColor() const;
    Vec3 getPosition() const;
    Vec3 getScale() const;

    uint32_t getTextureHandler() const;

    void update(float dt);
};

#endif //FLAPPYBIRD_SPRITE_H
