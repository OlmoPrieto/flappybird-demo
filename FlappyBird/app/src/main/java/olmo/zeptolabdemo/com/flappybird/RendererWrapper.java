package olmo.zeptolabdemo.com.flappybird;

import android.opengl.GLSurfaceView.Renderer;
import android.view.MotionEvent;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class RendererWrapper implements Renderer {

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        GameLibJNIWrapper.onSurfaceCreated();
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        // Do nothing
        GameLibJNIWrapper.onSurfaceChanged(width, height);
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        GameLibJNIWrapper.onDrawFrame();
    }

    public void onTouchEvent(float x, float y) {
        GameLibJNIWrapper.onTouchEvent(x, y);
    }

}