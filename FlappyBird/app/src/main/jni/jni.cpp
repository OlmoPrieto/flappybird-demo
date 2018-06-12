//
// Created by Olmo on 10/06/2018.
//

#include "../cpp/game.h"
#include <jni.h>

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT void JNICALL Java_olmo_zeptolabdemo_com_flappybird_GameLibJNIWrapper_onSurfaceCreated
        (JNIEnv *env, jclass clss) {

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

#ifdef __cplusplus
};
#endif