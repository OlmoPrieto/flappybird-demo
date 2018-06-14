//
// Created by Olmo on 09/06/2018.
//

#ifndef FLAPPYBIRD_GAME_H
#define FLAPPYBIRD_GAME_H

#include <GLES2/gl2.h>

#include <chrono>
#include <queue>
#include <vector>

#include "obstacle.h"
#include "player.h"
#include "sprite.h"
#include "utils.h"

struct Event {
    float x;
    float y;

    Event() : x(0.0f), y(0.0f) {

    }

    Event(float _x, float _y) : x(_x), y(_y) {

    }
};

class Game {
private:
    Game();
    void setupOpenGL();
    void drawSprite(Sprite* sprite);

    Player m_player;

    std::vector<Sprite> m_sprites;
    std::vector<Obstacle> m_obstacles;
    std::queue<Event> m_events;
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
    void registerEvent(float x, float y);
};

#endif //FLAPPYBIRD_GAME_H
