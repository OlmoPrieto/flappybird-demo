package olmo.zeptolabdemo.com.flappybird;

import android.app.ActivityManager;
import android.content.Context;
import android.content.pm.ConfigurationInfo;
//import android.opengl.EGLConfig;
import android.opengl.GLSurfaceView;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
//    static {
//        System.loadLibrary("native-lib");
//    }

    private GLSurfaceView glSurfaceView;
    private boolean rendererSet;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        //setContentView(R.layout.activity_main);

        ActivityManager activityManager = (ActivityManager)getSystemService(Context.ACTIVITY_SERVICE);
        ConfigurationInfo configurationInfo = activityManager.getDeviceConfigurationInfo();

        final boolean supportsES2 = configurationInfo.reqGlEsVersion >= 0x20000;// || isEmulator();
        if (supportsES2) {
            glSurfaceView = new GLSurfaceView(this);

            glSurfaceView.setEGLContextClientVersion(2);
            glSurfaceView.setRenderer(new RendererWrapper());

            rendererSet = true;
            setContentView(glSurfaceView);
        }
        else {
            // Should never happen in production
            Toast.makeText(this, "This device does not support OpenGLES2", Toast.LENGTH_LONG).show();

            return;
        }
    }

    @Override
    protected void onPause() {
        super.onPause();

        if (rendererSet == true) {
            glSurfaceView.onPause();
        }
    }

    @Override
    protected void onResume() {
        super.onResume();

        if (rendererSet == true) {
            glSurfaceView.onResume();
        }
    }



    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
}
