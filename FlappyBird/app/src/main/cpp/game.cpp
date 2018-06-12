//
// Created by Olmo on 09/06/2018.
//

#include <android/log.h>

#include <cstdio>
#include <cstdlib>
#include <string>
#include "game.h"

Game* Game::m_game = nullptr;

Game::Game() {

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
"//attribute vec2 uv;\n"
"void main() {\n"
"  gl_Position = MVP * vec4(position, 1.0);\n"
"}\n";

static const char* fragment_shader_text =
"#version 100\n"
"uniform vec3 color;\n"
"void main() {\n"
"  gl_FragColor = vec4(color, 1.0);\n"
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


    m_vertices[0] = { -1.0f,  1.0f, 0.0f };
    m_vertices[1] = { -1.0f, -1.0f, 0.0f };
    m_vertices[2] = {  1.0f,  1.0f, 0.0f };
    m_vertices[3] = {  1.0f, -1.0f, 0.0f };

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
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices) + sizeof(m_indices), m_vertices, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(m_vertices), sizeof(m_indices), m_indices);
    CheckGLError("glBufferData");
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    CheckGLError("glBindBuffer(0)");

//    glGenBuffers(1, &m_indices_index);
//    CheckGLError("glGenBuffers indices");
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indices_index);
//    CheckGLError("glBindBuffer indices");
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_indices), m_indices, GL_STATIC_DRAW);
//    CheckGLError("glBufferData indices");
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//    CheckGLError("glBindBuffer(0) indices");


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

    m_position_location = glGetAttribLocation(program_id, "position");
    glEnableVertexAttribArray(m_position_location);
    CheckGLError("glEnableVertexAttribArray");


    // Projection matrix
    //   column-major order

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

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    glUseProgram(program_id);
    CheckGLError("glUseProgram");
    glUniformMatrix4fv(m_mvp_location, 1, GL_FALSE, (const GLfloat*)m_projection.matrix);
    CheckGLError("glUniformMatrix4fv");
}

void Game::onSurfaceCreated() {
    setupOpenGL();

    m_sprites.emplace_back(Sprite());
}

void Game::onSurfaceChanged(int width, int height) {
    // Do nothing
}

void Game::onDrawFrame() {
    for (uint32_t i = 0; i < m_sprites.size(); ++i) {
        m_sprites[i].update(16.6f);
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (uint32_t i = 0; i < m_sprites.size(); ++i) {
        Color c = m_sprites[i].getColor();
        glUniform3f(m_color_location, (float)(c.r / 255), (float)(c.g / 255), (float)(c.b / 255));
        CheckGLError(std::string(std::string("glUniform3f") + std::to_string(i)).c_str());

        glBindBuffer(GL_ARRAY_BUFFER, m_vertices_index);
        CheckGLError(std::string(std::string("glBindBuffer") + std::to_string(i)).c_str());
        Vec3 pos = m_sprites[i].getPosition();
        Vec3 vertices[4] = {
                { m_vertices[0].x + pos.x, m_vertices[0].y + pos.y, m_vertices[0].z + pos.z },
                { m_vertices[1].x + pos.x, m_vertices[1].y + pos.y, m_vertices[1].z + pos.z },
                { m_vertices[2].x + pos.x, m_vertices[2].y + pos.y, m_vertices[2].z + pos.z },
                { m_vertices[3].x + pos.x, m_vertices[3].y + pos.y, m_vertices[3].z + pos.z },
        };
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), &vertices);
        CheckGLError(std::string(std::string("glBufferSubData") + std::to_string(i)).c_str());
        glVertexAttribPointer(m_position_location, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
        CheckGLError(std::string(std::string("glVertexAttribPointer") + std::to_string(i)).c_str());

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indices_index);
        CheckGLError("glBindBuffer GL_ELEMENT_ARRAY_BUFFER");
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, m_indices);
        //glDrawArrays(GL_TRIANGLES, 0, 6);
        CheckGLError(std::string(std::string("glDrawElements") + std::to_string(i)).c_str());
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}