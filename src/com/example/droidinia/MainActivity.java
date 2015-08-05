package com.example.droidinia;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

import android.app.Activity;
import android.content.Context;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends Activity {

	static {
		System.loadLibrary("droidinia-jni");
	}
    private final String TAG="Droidinia-JNI";
    private int[]     mChoice;
    private CheckBox leukocyte, heartwall, cfdsolver, ludecomp, hotspot, backpropagation,
    				needleman, kmeans, bfs, srad, streamcluster, particlefilter,
    				pathfinder, gaussian, nearestneighbors, lavamd, myocyte, btree, gpudwt, hybridsort;
    private Button runbutton, selectallbutton;
    private TextView tv;

	native private boolean compileKernels();
	native private void runbenchmarks(int[] choice);
	public native String BenchmarksFromJNI(int[] choice);
	
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		addListenerOnRunButton();
		addListenerOnSelectAllButton();
		//Context context = getApplicationContext();
		//CharSequence text = BenchmarksFromJNI();
		//int duration = Toast.LENGTH_LONG;
		//Toast toast = Toast.makeText(context,  text,  duration);
		//toast.show();
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		// Handle action bar item clicks here. The action bar will
		// automatically handle clicks on the Home/Up button, so long
		// as you specify a parent activity in AndroidManifest.xml.
		int id = item.getItemId();
		if (id == R.id.action_settings) {
			return true;
		}
		return super.onOptionsItemSelected(item);
	}
	
	public void addListenerOnRunButton() {
	     runbutton = (Button) findViewById(R.id.runbutton);
	     
	     runbutton.setOnClickListener(new OnClickListener(){
			public void onClick(View v) {
				startTests();
			}
	     });
	}
	
	public void addListenerOnSelectAllButton() {
		selectallbutton = (Button) findViewById(R.id.selectall);
		selectallbutton.setOnClickListener(new OnClickListener() {
			public void onClick(View v) {
				Context context = getApplicationContext();
				CharSequence text = "You hit the select all button";
				int duration = Toast.LENGTH_LONG;
				Toast toast = Toast.makeText(context,  text,  duration);
				toast.show();
				/*leukocyte.setChecked(true);
				heartwall.setChecked(true);
				cfdsolver.setChecked(true);
				ludecomp.setChecked(true);
				hotspot.setChecked(true);
				backpropagation.setChecked(true);
				needleman.setChecked(true);
				kmeans.setChecked(true);
				bfs.setChecked(true);
				srad.setChecked(true);
				streamcluster.setChecked(true);
				particlefilter.setChecked(true);
				pathfinder.setChecked(true);
				gaussian.setChecked(true);
				nearestneighbors.setChecked(true);
				lavamd.setChecked(true);
				myocyte.setChecked(true);
				btree.setChecked(true);
				gpudwt.setChecked(true);
				hybridsort.setChecked(true);*/
			}
		});
	}
	
	
	
	private void copyFile(final String f) {
		InputStream in;
		try {
			//creates the output data
			in = getAssets().open(f);
			final File of = new File(getDir("execdir",MODE_PRIVATE), f);

			final OutputStream out = new FileOutputStream(of);

			final byte b[] = new byte[65535];
			int sz = 0;
			while ((sz = in.read(b)) > 0) {
				out.write(b, 0, sz);
			}
			in.close();
			out.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	public void startTests() {
		
		Context context = getApplicationContext();
		CharSequence text = "Proceeding to run benchmarks...";
		int duration = Toast.LENGTH_LONG;
		Toast toast = Toast.makeText(context,  text,  duration);
		toast.show();
    	tv = (TextView) findViewById(R.id.tv);
    	
    	//create checkboxes for each option
    	leukocyte = (CheckBox) findViewById(R.id.leukocyte);
    	heartwall = (CheckBox) findViewById(R.id.heartwall);
    	cfdsolver = (CheckBox) findViewById(R.id.cfdsolver);
    	ludecomp = (CheckBox) findViewById(R.id.ludecomp);
    	hotspot = (CheckBox) findViewById(R.id.hotspot);
    	backpropagation = (CheckBox) findViewById(R.id.backpropogation);
    	needleman = (CheckBox) findViewById(R.id.needleman);
    	kmeans = (CheckBox) findViewById(R.id.kmeans);
    	bfs = (CheckBox) findViewById(R.id.bfs);
    	srad = (CheckBox) findViewById(R.id.srad);
    	streamcluster = (CheckBox) findViewById(R.id.streamcluster);
    	particlefilter = (CheckBox) findViewById(R.id.particlefilter);
    	pathfinder = (CheckBox) findViewById(R.id.pathfinder);
    	gaussian = (CheckBox) findViewById(R.id.gaussian);
    	nearestneighbors = (CheckBox) findViewById(R.id.nearestneighbors);
    	lavamd = (CheckBox) findViewById(R.id.lavamd);
    	myocyte = (CheckBox) findViewById(R.id.myocyte);
    	btree = (CheckBox) findViewById(R.id.btree);
    	gpudwt = (CheckBox) findViewById(R.id.gpudwt);
    	hybridsort = (CheckBox) findViewById(R.id.hybridsort);
    	
    	int[] choice = new int[19];
    	for (int i = 0; i < 19; i++) {
    		choice[i] = 0;
    	}
    	if (leukocyte.isChecked()) {
    		choice[0]=1;
    	} 
    	if (bfs.isChecked()) {
    		choice[8]=0;
    	}
    	
    	mChoice=choice;
    	try {
            //tv.setText("Running Tests...");
			String returnValue = BenchmarksFromJNI(mChoice);
			text = (CharSequence) returnValue;
			toast = Toast.makeText(context,  text,  duration);
			toast.show();
    	} catch(Exception e) {
    		Log.i(TAG, e.getMessage());
    	}
    }
}
