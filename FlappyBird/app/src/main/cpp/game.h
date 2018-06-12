//
// Created by Olmo on 09/06/2018.
//

#ifndef FLAPPYBIRD_GAME_H
#define FLAPPYBIRD_GAME_H

#include <GLES2/gl2.h>
#include <vector>

#include "sprite.h"
#include "utils.h"

class Game {
private:
    Game();
    void setupOpenGL();

    GLuint m_vertices_index = 0;
    GLuint m_indices_index = 0;
    GLint m_mvp_location = -1;
    GLint m_color_location = -1;
    GLint m_position_location = -1;
    GLuint m_indices[6];
    Vec3 m_vertices[4];

    Mat4 m_projection;

    std::vector<Sprite> m_sprites;

    static Game* m_game;

public:

    static Game* Instance();

    ~Game();

    void onSurfaceCreated();
    void onSurfaceChanged(int width, int height);
    void onDrawFrame();
};

#endif //FLAPPYBIRD_GAME_H
