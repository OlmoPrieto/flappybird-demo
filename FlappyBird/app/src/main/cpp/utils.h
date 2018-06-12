//
// Created by Olmo on 10/06/2018.
//

#ifndef FLAPPYBIRD_UTILS_H
#define FLAPPYBIRD_UTILS_H

#include <cstring>

struct Mat4 {
    float matrix[16];

    Mat4() {
        memset(matrix, 0, sizeof(float) * 16);
    }

    void setIdentity() {
        memset(matrix, 0, sizeof(float) * 16);
        matrix[0]  = 1.0f;
        matrix[5]  = 1.0f;
        matrix[10] = 1.0f;
        matrix[15] = 1.0f;
    }

    void operator =(const Mat4& other) {
        matrix[0]  = other.matrix[0];  matrix[1]  = other.matrix[1];  matrix[2]  = other.matrix[2];  matrix[3]  = other.matrix[3];
        matrix[4]  = other.matrix[4];  matrix[5]  = other.matrix[5];  matrix[6]  = other.matrix[6];  matrix[7]  = other.matrix[7];
        matrix[8]  = other.matrix[8];  matrix[9]  = other.matrix[9];  matrix[10] = other.matrix[10]; matrix[11] = other.matrix[11];
        matrix[12] = other.matrix[12]; matrix[13] = other.matrix[13]; matrix[14] = other.matrix[14]; matrix[15] = other.matrix[15];
    }

    Mat4 operator *(const Mat4& other) {
        Mat4 result;
        result.matrix[0]  = matrix[0] * other.matrix[0] + matrix[1] * other.matrix[4] + matrix[2] * other.matrix[8]  + matrix[3] * other.matrix[12];
        result.matrix[1]  = matrix[0] * other.matrix[1] + matrix[1] * other.matrix[5] + matrix[2] * other.matrix[9]  + matrix[3] * other.matrix[13];
        result.matrix[2]  = matrix[0] * other.matrix[2] + matrix[1] * other.matrix[6] + matrix[2] * other.matrix[10] + matrix[3] * other.matrix[14];
        result.matrix[3]  = matrix[0] * other.matrix[3] + matrix[1] * other.matrix[7] + matrix[2] * other.matrix[11] + matrix[3] * other.matrix[15];

        result.matrix[4]  = matrix[4] * other.matrix[0] + matrix[5] * other.matrix[4] + matrix[6] * other.matrix[8]  + matrix[7] * other.matrix[12];
        result.matrix[5]  = matrix[4] * other.matrix[1] + matrix[5] * other.matrix[5] + matrix[6] * other.matrix[9]  + matrix[7] * other.matrix[13];
        result.matrix[6]  = matrix[4] * other.matrix[2] + matrix[5] * other.matrix[6] + matrix[6] * other.matrix[10] + matrix[7] * other.matrix[14];
        result.matrix[7]  = matrix[4] * other.matrix[3] + matrix[5] * other.matrix[7] + matrix[6] * other.matrix[11] + matrix[7] * other.matrix[15];

        result.matrix[8]  = matrix[8] * other.matrix[0] + matrix[9] * other.matrix[4] + matrix[10] * other.matrix[8]  + matrix[11] * other.matrix[12];
        result.matrix[9]  = matrix[8] * other.matrix[1] + matrix[9] * other.matrix[5] + matrix[10] * other.matrix[9]  + matrix[11] * other.matrix[13];
        result.matrix[10] = matrix[8] * other.matrix[2] + matrix[9] * other.matrix[6] + matrix[10] * other.matrix[10] + matrix[11] * other.matrix[14];
        result.matrix[11] = matrix[8] * other.matrix[3] + matrix[9] * other.matrix[7] + matrix[10] * other.matrix[11] + matrix[11] * other.matrix[15];

        result.matrix[12] = matrix[12] * other.matrix[0] + matrix[13] * other.matrix[4] + matrix[14] * other.matrix[8]  + matrix[15] * other.matrix[12];
        result.matrix[13] = matrix[12] * other.matrix[1] + matrix[13] * other.matrix[5] + matrix[14] * other.matrix[9]  + matrix[15] * other.matrix[13];
        result.matrix[14] = matrix[12] * other.matrix[2] + matrix[13] * other.matrix[6] + matrix[14] * other.matrix[10] + matrix[15] * other.matrix[14];
        result.matrix[15] = matrix[12] * other.matrix[3] + matrix[13] * other.matrix[7] + matrix[14] * other.matrix[11] + matrix[15] * other.matrix[15];

        return result;
    }

    void operator *=(const Mat4& other) {
        *this = *this * other;
    }
};

struct Vec3 {
    float x;
    float y;
    float z;

    Vec3() {
        x = 0.0f;
        y = 0.0f;
        z = 0.0f;
    }

    Vec3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {

    }
};

struct Color {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;

    Color() : r(0), g(0), b(0), a(0) {

    }

    Color(uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a) : r(_r), g(_g), b(_b), a(_a) {

    }

    void set(uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a) {
        r = _r; g = _g; b = _b; a = _a;
    }
};

#endif //FLAPPYBIRD_UTILS_H
