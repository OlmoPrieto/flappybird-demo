package olmo.zeptolabdemo.com.flappybird;

public class GameLibJNIWrapper {
    static {
        System.loadLibrary("game");
    }

    public static native void onSurfaceCreated();
    public static native void onSurfaceChanged(int width, int height);
    public static native void onDrawFrame();
}
