//
// Created by Olmo on 09/06/2018.
//

#include <android/log.h>

#include <cstdio>
#include <cstdlib>
#include <string>
#include <thread>

#include "game.h"

Game* Game::m_game = nullptr;

Game::Game() {
    m_obstacle_index = m_max_obstacles - 1;
}

Game::~Game() {
    delete m_game;
}

Game* Game::Instance() {
    if (m_game == nullptr) {
        m_game = new Game();
    }

    return m_game;
}

static const char* vertex_shader_text =
"#version 100\n"
"uniform mat4 MVP;\n"
"attribute vec3 position;\n"
"attribute vec3 uv;\n"
"varying vec2 o_uv;\n"
"void main() {\n"
"  gl_Position = MVP * vec4(position, 1.0);\n"
"  o_uv = vec2(uv.x, uv.y);\n"
"}\n";

static const char* fragment_shader_text =
"#version 100\n"
"uniform vec4 color;\n"
"varying vec2 o_uv;\n"
"uniform sampler2D tex;\n"
"void main() {\n"
//"  gl_FragColor = vec4(color.x, color.y, color.z, 1.0);\n"
"  gl_FragColor = texture2D(tex, o_uv) * color;\n"
//"  gl_FragColor = vec4(o_uv.x, o_uv.y, 0.0, 1.0);\n"
"}\n";

bool CheckGLError(const char* tag = "") {
    GLenum error = glGetError(); // pops the last error from the queue
    if (error != GL_NO_ERROR) {
        switch (error) {
            case GL_INVALID_OPERATION: {
                __android_log_print(ANDROID_LOG_INFO, "GL_ERROR", "%s : Invalid operation\n", tag);
                break;
            }
            case GL_INVALID_VALUE: {
                __android_log_print(ANDROID_LOG_INFO, "GL_ERROR", "%s : Invalid value\n", tag);
                break;
            }
            case GL_INVALID_ENUM: {
                __android_log_print(ANDROID_LOG_INFO, "GL_ERROR", "%s : Invalid enum\n", tag);
                break;
            }
                //        case GL_STACK_OVERFLOW: {
                //            printf("%s : Stack overflow\n", tag);
                //            break;
                //        }
                //        case GL_STACK_UNDERFLOW: {
                //            printf("%s : Stack underflow\n", tag);
                //            break;
                //        }
            case GL_OUT_OF_MEMORY: {
                __android_log_print(ANDROID_LOG_INFO, "GL_ERROR", "%s : Out of memory\n", tag);
                break;
            }
                // case GL_INVALID_FRAMEBUFFER_OPERATION: {
                //   printf("Invalid framebuffer operation: %s\n", tag);
                //   break;
                // }
            default: {
                __android_log_print(ANDROID_LOG_INFO, "GL_ERROR", "Not handled: %s\n", tag);
                break;
            }
        }
    }

    return error != GL_NO_ERROR;
}

void Game::setupOpenGL() {
    printf("Initializing OpenGL...\n");

    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

    m_vertices[0] = { -1.0f,  1.0f, 0.0f };
    m_vertices[1] = { -1.0f, -1.0f, 0.0f };
    m_vertices[2] = {  1.0f,  1.0f, 0.0f };
    m_vertices[3] = {  1.0f, -1.0f, 0.0f };

    m_uvs[0] = { 0.0f, 1.0f, 0.0f };
    m_uvs[1] = { 0.0f, 0.0f, 0.0f };
    m_uvs[2] = { 1.0f, 1.0f, 0.0f };
    m_uvs[3] = { 1.0f, 0.0f, 0.0f };

    m_indices[0] = 0;
    m_indices[1] = 1;
    m_indices[2] = 2;
    m_indices[3] = 3;
    m_indices[4] = 2;
    m_indices[5] = 1;

    glGenBuffers(1, &m_vertices_index);
    CheckGLError("glGenBuffers");
    glBindBuffer(GL_ARRAY_BUFFER, m_vertices_index);
    CheckGLError("glBindBuffer");
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices) + sizeof(m_uvs) + sizeof(m_indices), m_vertices, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(m_vertices), sizeof(m_uvs), m_uvs);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(m_vertices) + sizeof(m_uvs), sizeof(m_indices), m_indices);
    CheckGLError("glBufferData");
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    CheckGLError("glBindBuffer(0)");


    GLuint  other_vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
    CheckGLError("glCreateShader vertex2");


    // Create and compile vertex shader
    GLuint vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
    CheckGLError("glCreateShader vertex");
    glShaderSource(vertex_shader_id, 1, &vertex_shader_text, nullptr);
    CheckGLError("glShaderSource vertex");
    glCompileShader(vertex_shader_id);
    CheckGLError("glCompileShader vertex");
    GLint vertex_shader_compiling_success = 0;
    glGetShaderiv(vertex_shader_id, GL_COMPILE_STATUS, &vertex_shader_compiling_success);
    CheckGLError("glGetShaderiv vertex");
    if (!vertex_shader_compiling_success) {
        __android_log_print(ANDROID_LOG_INFO, "Shader info log", "Failed to compile vertex shader\n");
        GLint log_size = 0;
        glGetShaderiv(vertex_shader_id, GL_INFO_LOG_LENGTH, &log_size);
        char* log = (char*)malloc(log_size);
        GLint read = 0;
        glGetShaderInfoLog(vertex_shader_id, log_size, &read, log);
        __android_log_print(ANDROID_LOG_INFO, "Shader info log", "Error: %s\n", log);
        free(log);
    }

    // Create and compile fragment shader
    GLuint fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
    CheckGLError("glCreateShader fragment");
    glShaderSource(fragment_shader_id, 1, &fragment_shader_text, nullptr);
    CheckGLError("glShaderSource fragment");
    glCompileShader(fragment_shader_id);
    CheckGLError("glCompileShader fragment");
    GLint fragment_shader_compiling_success = 0;
    glGetShaderiv(fragment_shader_id, GL_COMPILE_STATUS, &fragment_shader_compiling_success);
    if (!fragment_shader_compiling_success) {
        __android_log_print(ANDROID_LOG_INFO, "Shader info log", "Failed to compile fragment shader\n");
        GLint log_size = 0;
        glGetShaderiv(fragment_shader_id, GL_INFO_LOG_LENGTH, &log_size);
        char* log = (char*)malloc(log_size);
        GLint read = 0;
        glGetShaderInfoLog(fragment_shader_id, log_size, &read, log);
        __android_log_print(ANDROID_LOG_INFO, "Shader info log", "Error: %s\n", log);
        free(log);
    }

    GLuint program_id = glCreateProgram();
    CheckGLError("glCreateProgram");
    glAttachShader(program_id, vertex_shader_id);
    CheckGLError("glAttachShader vertex");
    glAttachShader(program_id, fragment_shader_id);
    CheckGLError("glAttachShader fragment");
    glLinkProgram(program_id);
    CheckGLError("glLinkProgram");

    m_mvp_location = glGetUniformLocation(program_id, "MVP");
    m_color_location = glGetUniformLocation(program_id, "color");

    glBindBuffer(GL_ARRAY_BUFFER, m_vertices_index);
    m_position_location = glGetAttribLocation(program_id, "position");
    glEnableVertexAttribArray(m_position_location);
    CheckGLError("glEnableVertexAttribArray position");
    glVertexAttribPointer(m_position_location, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    CheckGLError("glVertexAttribPointer position");

    m_uvs_location = glGetAttribLocation(program_id, "uv");
    glEnableVertexAttribArray(m_uvs_location);
    CheckGLError("glEnableVertexAttribArray uvs");

    //glBindBuffer(GL_ARRAY_BUFFER, m_vertices_index);
    glVertexAttribPointer(m_uvs_location, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)sizeof(m_vertices));
    CheckGLError("glVertexAttribPointer uvs");
    glBindBuffer(GL_ARRAY_BUFFER, 0);


    // Projection matrix
    //   column-major order!

    float right  =  1.0f;
    float left   = -1.0f;
    float top    =  1.0f;
    float bottom = -1.0f;

    float near = 0.1f;
    float far  = 1000.0f;
    float fov  = 60.0f;

    m_projection.matrix[0] = 2.0f / (right - left);
    m_projection.matrix[1] = 0.0f;
    m_projection.matrix[2] = 0.0f;
    m_projection.matrix[3] = 0.0f;

    m_projection.matrix[4] = 0.0f;
    m_projection.matrix[5] = 2.0f / (top - bottom);
    m_projection.matrix[6] = 0.0f;
    m_projection.matrix[7] = 0.0f;

    m_projection.matrix[8] = 0.0f;
    m_projection.matrix[9] = 0.0f;
    m_projection.matrix[10] = 2.0f / (far - near);
    m_projection.matrix[11] = 0.0f;

    m_projection.matrix[12] = 0.0f;
    m_projection.matrix[13] = 0.0f;
    m_projection.matrix[14] = 0.0f;
    m_projection.matrix[15] = 1.0f;

    //glClearColor((float)108 / 255, (float)211 / 255, (float)255 / 255, 0.0f);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    glUseProgram(program_id);
    CheckGLError("glUseProgram");
    glUniformMatrix4fv(m_mvp_location, 1, GL_FALSE, (const GLfloat*)m_projection.matrix);
    CheckGLError("glUniformMatrix4fv");
}

void Game::onSurfaceCreated() {
    // ALWAYS FIRST
    setupOpenGL();

    srand(std::chrono::duration_cast<std::chrono::duration<int32_t > >(m_clock.now().time_since_epoch()).count());

    for (uint32_t i = 0; i < m_max_obstacles; ++i) {
        m_obstacles.emplace_back();
    }
    resetGame();
}

void Game::resetGame() {
    Vec3 pos(m_gap_between_obstacles, 0.0f, 0.0f);
    for (uint32_t i = 0; i < m_max_obstacles; ++i) {
        m_obstacles[i].setPosition(pos.x * (i + 1), pos.y, pos.z);
        m_obstacles[i].setSpritesXPositions(pos.x * (i + 1));

        m_obstacles[i].randomizeSpritesTint();
        m_obstacles[i].randomizeHeight();

        m_obstacles[i].stop();
    }

    m_player.setPosition(0.0f, 0.0f, 0.0f);
    m_player.stop();

    m_time1 = m_clock.now();
    m_time2 = m_clock.now();
    m_prev_time = std::chrono::duration_cast<std::chrono::duration<float> >(m_time2 - m_time1).count();

    m_obstacle_index = m_max_obstacles - 1;

    m_game_over = false;
}

void Game::onSurfaceChanged(int width, int height) {
    // Do nothing
}

void Game::registerEvent(float x, float y) {
    m_events.emplace(x, y );
}

void Game::drawSprite(Sprite* sprite) {
    Color c = sprite->getColor();
    glUniform4f(m_color_location, (float)c.r / (float)255, (float)c.g / (float)255,
                (float)c.b / (float)255, (float)c.a / (float)255);
    CheckGLError("glUniform4f");

    glBindTexture(GL_TEXTURE_2D, sprite->getTextureHandler());

    glBindBuffer(GL_ARRAY_BUFFER, m_vertices_index);
    CheckGLError("glBindBuffer");

    Vec3 scale = sprite->getScale();
    Vec3 pos = sprite->getPosition();
    Vec3 vertices[4] = {
            { m_vertices[0].x * scale.x + pos.x, m_vertices[0].y * scale.y + pos.y, m_vertices[0].z * scale.z + pos.z },
            { m_vertices[1].x * scale.x + pos.x, m_vertices[1].y * scale.y + pos.y, m_vertices[1].z * scale.z + pos.z },
            { m_vertices[2].x * scale.x + pos.x, m_vertices[2].y * scale.y + pos.y, m_vertices[2].z * scale.z + pos.z },
            { m_vertices[3].x * scale.x + pos.x, m_vertices[3].y * scale.y + pos.y, m_vertices[3].z * scale.z + pos.z },
    };
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), &vertices);
    CheckGLError("glBufferSubData");

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indices_index);
    CheckGLError("glBindBuffer GL_ELEMENT_ARRAY_BUFFER");
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, m_indices);
    //glDrawArrays(GL_TRIANGLES, 0, 6);
    CheckGLError("glDrawElements");

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Game::onDrawFrame() {
    m_time1 = m_clock.now();

    // Check for taps
    Event e;
    while (m_events.size() > 0) {
        if (m_game_over == true) {
            if (m_player.isTouchingGround()) {
                resetGame();
            }

            while (m_events.size() > 0) {
                m_events.pop();
            }

            break;
        }

        if (m_can_move == false) {
            m_can_move = true;

            m_player.start();
            Obstacle::start();
        }

        m_player.addForce();

        e = m_events.front();
        m_events.pop();
    }

    //__android_log_print(ANDROID_LOG_INFO, "LOG", "frame_time: %.2f\n", m_prev_time);

    // Update the obstacles
    for (uint32_t i = 0; i < m_max_obstacles; ++i) {
        m_obstacles[i].update(m_prev_time);

        if (m_player.checkCollision(&m_obstacles[i])) {
            m_game_over = true;
            m_can_move = false;
            //m_player.stop();  // don't stop player so it falls
            Obstacle::stop();

            break;
        }

        Vec3 pos = m_obstacles[i].getPosition();
        if (pos.x < -1.5f) {
            __android_log_print(ANDROID_LOG_INFO, "LOG", "%u\n", m_obstacle_index % m_max_obstacles);
            // set that obstacle behind the last one
            pos.x = m_obstacles[m_obstacle_index++ % m_max_obstacles].getPosition().x + m_gap_between_obstacles;

            m_obstacles[i].setPosition(pos);
            m_obstacles[i].setSpritesXPositions(pos.x);
            m_obstacles[i].randomizeSpritesTint();
            m_obstacles[i].randomizeHeight();
        }
    }

    // Update the player
    m_player.update(m_prev_time);
    if (m_player.isTouchingGround()) {
        m_game_over = true;
        m_can_move = false;
        m_player.stop();
        Obstacle::stop();
    }

    // Actual draw
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Draw obstacles
    Obstacle* obstacle = nullptr;
    Sprite*   upper    = nullptr;
    Sprite*   lower    = nullptr;
    for (uint32_t i = 0; i < m_max_obstacles; ++i) {
        obstacle = &m_obstacles[i];
        upper = obstacle->getUpperSprite();
        lower = obstacle->getLowerSprite();

        drawSprite(upper);
        drawSprite(lower);
    }

    // Draw player after so it appears in front of the obstacles
    drawSprite(m_player.getSprite());

    // Lock framerate to 60 fps for fast machines
    // Using a spinlock because std::sleep can be imprecise
    m_time2 = m_clock.now();
    m_prev_time = std::chrono::duration_cast<std::chrono::duration<float> >(m_time2 - m_time1).count();
    m_time1 = m_clock.now();
    while (m_prev_time < 16.6666f) {
        m_time2 = m_clock.now();
        m_prev_time += std::chrono::duration_cast<std::chrono::duration<float> >(m_time2 - m_time1).count();
    }
}