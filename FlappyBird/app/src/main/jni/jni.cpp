//
// Created by Olmo on 10/06/2018.
//

#include "../cpp/game.h"
#include <jni.h>

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT void JNICALL Java_olmo_zeptolabdemo_com_flappybird_GameLibJNIWrapper_onSurfaceCreated
        (JNIEnv *env, jclass clss, jint width, jint height) {

    Game::m_render_width = width;
    Game::m_render_height = height;
    Game::Instance()->onSurfaceCreated();
}

JNIEXPORT void JNICALL Java_olmo_zeptolabdemo_com_flappybird_GameLibJNIWrapper_onSurfaceChanged
        (JNIEnv *env, jclass clss, jint width, jint height) {

    Game::Instance()->onSurfaceChanged(width, height);
}

JNIEXPORT void JNICALL Java_olmo_zeptolabdemo_com_flappybird_GameLibJNIWrapper_onDrawFrame
        (JNIEnv *env, jclass clss) {

    Game::Instance()->onDrawFrame();
}

JNIEXPORT void JNICALL Java_olmo_zeptolabdemo_com_flappybird_GameLibJNIWrapper_onTouchEvent
        (JNIEnv *env, jclass clss, jfloat x, jfloat y) {

    Game::Instance()->registerEvent(x, y);
}

#ifdef __cplusplus
};
#endif