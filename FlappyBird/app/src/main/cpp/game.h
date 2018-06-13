//
// Created by Olmo on 09/06/2018.
//

#ifndef FLAPPYBIRD_GAME_H
#define FLAPPYBIRD_GAME_H

#include <GLES2/gl2.h>

#include <chrono>
#include <vector>

#include "obstacle.h"
#include "sprite.h"
#include "utils.h"

class Game {
private:
    Game();
    void setupOpenGL();
    void drawSprite(Sprite* sprite);

    std::vector<Sprite> m_sprites;
    std::vector<Obstacle> m_obstacles;
    std::chrono::high_resolution_clock m_clock;
    std::chrono::high_resolution_clock::time_point m_time1;
    std::chrono::high_resolution_clock::time_point m_time2;

    Vec3 m_vertices[4];
    Vec3 m_uvs[4];

    Mat4 m_projection;

    GLuint m_vertices_index = 0;
    GLuint m_indices_index = 0;
    GLint m_mvp_location = -1;
    GLint m_color_location = -1;
    GLint m_position_location = -1;
    GLint m_uvs_location = -1;
    GLuint m_indices[6];

    uint32_t m_max_obstacles = 7;

    float m_prev_time = 0.0f;

    static Game* m_game;

public:

    static Game* Instance();

    ~Game();

    void onSurfaceCreated();
    void onSurfaceChanged(int width, int height);
    void onDrawFrame();
};

#endif //FLAPPYBIRD_GAME_H
