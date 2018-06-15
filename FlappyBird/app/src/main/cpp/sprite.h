//
// Created by Olmo on 10/06/2018.
//

#ifndef FLAPPYBIRD_SPRITE_H
#define FLAPPYBIRD_SPRITE_H

#include <GLES2/gl2.h>
#include "utils.h"

class Sprite {
protected:
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

    void setColor(const Color& color);  // The color is the tint (used in the shader)
    void setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);  // The color is the tint (used in the shader)
    void setPosition(const Vec3& position);
    void setPosition(float x, float y, float z);
    void setPositionX(float x);
    void setPositionY(float y);
    void setPositionZ(float z);
    void setScale(const Vec3& scale);
    void setScale(float x, float y, float z);
    void setScaleX(float x);
    void setScaleY(float y);
    void setScaleZ(float z);

    void setTextureData(uint8_t** data);

    uint32_t getTextureHandler() const;
    uint8_t** getTextureData();
    uint32_t getTextureWidth() const;
    uint32_t getTextureHeight() const;

    void update(float dt);
};

#endif //FLAPPYBIRD_SPRITE_H
