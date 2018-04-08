package com.kinglloy.astar;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;

import java.util.ArrayList;

public class MainActivity extends AppCompatActivity {
    private static final String TAG = "MainActivity";

    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    public native ArrayList<Point> getPath();

    public void getPath(View view) {
        ArrayList<Point> path = getPath();
        for (Point point : path) {
            Log.d(TAG, String.format("%d, %d", point.x, point.y));
        }
    }
}
