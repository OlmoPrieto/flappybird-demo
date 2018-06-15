//
// Created by Olmo on 10/06/2018.
//

#ifndef FLAPPYBIRD_UTILS_H
#define FLAPPYBIRD_UTILS_H

#include <cstring>
#include <cstdint>
#include <cstdlib>

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

    void operator += (const Vec3& other) {
        x += other.x;
        y += other.y;
        z += other.z;
    }

    void operator -= (const Vec3& other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
    }

    Vec3 operator + (const Vec3& other) {
        Vec3 result;
        result.x = x + other.x;
        result.y = y + other.y;
        result.z = z + other.z;

        return result;
    }

    Vec3 operator - (const Vec3& other) {
        Vec3 result;
        result.x = x - other.x;
        result.y = y - other.y;
        result.z = z - other.z;

        return result;
    }

    void operator += (float f) {
        x += f;
        y += f;
        z += f;
    }

    void operator -= (float f) {
        x -= f;
        y -= f;
        z -= f;
    }

    void operator *= (float f) {
        x *= f;
        y *= f;
        z *= f;
    }
};

struct Color {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;

    Color() : r((uint8_t)255), g((uint8_t)255), b((uint8_t)255), a((uint8_t)255) {

    }

    Color(uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a) : r(_r), g(_g), b(_b), a(_a) {

    }

    void set(uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a) {
        r = _r; g = _g; b = _b; a = _a;
    }

    void setRandom() {
        r = (uint8_t)(rand() % 255);
        g = (uint8_t)(rand() % 255);
        b = (uint8_t)(rand() % 255);

        a = 255; // ??
    }

    static Color randomColor() {
        Color c;

        c.r = (uint8_t)(rand() % 255);
        c.g = (uint8_t)(rand() % 255);
        c.b = (uint8_t)(rand() % 255);

        if (c.r < 128) {
            c.r = 128;
        }
        if (c.g < 128) {
            c.g = 128;
        }
        if (c.b < 128) {
            c.b = 128;
        }

        c.a = 255; // ??

        return c;
    }
};

static void SetTextureColor(uint8_t* texture, uint32_t width, uint32_t height, const Color& c) {
//        uint32_t color = ((c.r << 24) & 0xFF000000) |
//                ((c.g << 24) & 0x00FF0000) |
//                ((c.b << 24) & 0x0000FF00) |
//                ((c.a << 24) & 0x000000FF);
//        //uint32_t color = (c.r << 24) | (c.g << 16) | (c.b << 8) | c.a;
//        memset(texture, color, width * height * 4);

    uint8_t* ptr = texture;
    for (uint32_t i = 0; i < width * height * 4; i += 4) {
        *(ptr + 0) = c.r;
        *(ptr + 1) = c.g;
        *(ptr + 2) = c.b;
        *(ptr + 3) = c.a;

        ptr += 4;
    }
}

// TODO: now it creates an oval. FIX
static void CreateCircleInTexture(uint8_t* texture, uint32_t width, uint32_t height, const Color& c) {
//    uint32_t color = ((c.r << 24) & 0xFF000000) |
//            ((c.g << 24) & 0x00FF0000) |
//            ((c.b << 24) & 0x0000FF00) |
//            ((c.a << 24) & 0x000000FF);

    memset(texture, 0, width * height * 4);

    uint32_t radius = (uint32_t)((float)width * 0.5f);
    uint32_t powered_radius = radius * radius;
    uint32_t x = 0;
    uint32_t y = 0;
    uint8_t* ptr = texture;
    for (uint32_t i = 0; i < width * height * 4; i += 4) {
        x = (uint32_t)(i * 0.25f) / width;
        y = (uint32_t)(i * 0.25f) % width;

        if ((x - radius) * (x - radius) + (y - radius) * (y - radius) < powered_radius) {
            *(ptr + 0) = c.r;
            *(ptr + 1) = c.g;
            *(ptr + 2) = c.b;
            *(ptr + 3) = c.a;
        }
        else {
            *(ptr + 0) = 0;
            *(ptr + 1) = 0;
            *(ptr + 2) = 0;
            *(ptr + 3) = 0;
        }

        ptr += 4;
    }
}

struct BoundingBox {
    float top_left;
    float bottom_left;
    float top_right;
    float bottom_right;

    BoundingBox() : top_left(0.0f), bottom_left(0.0f),
                    top_right(0.0f), bottom_right(0.0f) {

    }

    BoundingBox(float tl, float bl, float tr, float br) :
            top_left(tl), bottom_left(bl),
            top_right(tr), bottom_right(br) {

    }

    bool checkAgainstBoundingBox(const BoundingBox& other) {
        if (top_left >= other.top_left && top_right <= other.top_right &&
                top_left >= other.top_left && bottom_left <= other.bottom_left) {
            return true;
        }

        return false;
    }
};

#endif //FLAPPYBIRD_UTILS_H
