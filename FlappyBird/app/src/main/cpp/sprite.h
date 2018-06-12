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
    Color m_color;

public:

    Sprite();
    ~Sprite();

    Color getColor() const;
    Vec3 getPosition();

    void update(float dt);
};

#endif //FLAPPYBIRD_SPRITE_H
