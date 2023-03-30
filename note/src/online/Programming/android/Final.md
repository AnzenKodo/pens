# 1. Attempt any FIVE of the following: 10

## a) List any four features of Android operating system.
- Open Source
- Beautiul UI
- Connectivity
- Storage
- Multi-Touch
- Multi-Tasking
- Multi-Language
- Resizable widgets
- Messaging
- Media Support
- Web Browser

## b) Define Dalvik Virtual Machine (DVM).
| JVM                                                              	| DVM                                                                           	|
|------------------------------------------------------------------	|-------------------------------------------------------------------------------	|
| JVM supports multiple OS                                         	| DVM supports only Android Operating system.                                   	|
| JVM forms separate classes in separate `.class` byte code files. 	| DVM forms multiple class in `.dex` byte code file.                            	|
| It is based on stack based virtual machine architecture.         	| It is based on register based virtual machine architecture.                   	|
| JVM runs on more memory                                          	| DVM runs on less memory.                                                      	|
|  The executable format of JVM is JAR.                             	 |  The executable format of DVM is APK.                                          	 |
|                    JVM has different constant pools.                     |                          DVM has common constant pool.                           |
|                   It runs `.class` byte code directly.                   |  The `.class` byte codes are optimize to .odex format before executing in DVM.   |

## c) List any four folders from directory structure of Android project and elaborate in one line.
### Manifests Folder
- Manifests folder contains AndroidManifest.xml for creating our android application.
- This file contains information about our application such as the Android version, metadata, states package for Kotlin file, and other application components.
- It acts as an intermediator between android OS and our application.
### Java folder
- The Java folder contains all the java and Kotlin source code (.java) files that we create during the app development, including other Test files.
### Resource (res) folder
- The resource folder is the most important folder because it contains all the non-code sources like images, XML layouts, and UI strings for our android application.
### res/drawable folder
- It contains the different types of images used for the development of the application.

## d) List any four attributes of check box.
- text - This is the Text to display.
- id - This supplies an identifier name for this view.
- visibility - This controls the initial visibility of the view.
- editable - If set, specifies that this TextView has an input method.

## e) Draw diagram of activity life cycle.
```
                             ┌┬────────┬┐
                             ││Activity││
                             ││launched││
                             └┴────┬───┴┘
                                   │
                              ┌────▼─────┐
         ┌────────────────────►onCreate()│
         │                    └────┬─────┘
         │                         │
         │                    ┌────▼────┐                    ┌───────────┐
         │                    │onStart()◄────────────────────┤onRestart()│
         │                    └────┬────┘                    └───────▲───┘
         │                         │                                 │
User navigates                ┌────▼─────┐                           │
to the activity               │onResume()◄───────────────┐           │
         │                    └────┬─────┘               │           │
         │                         │                     │           │
  ┌┬─────┴─────┬┐            ┌┬────┴───┬┐                │           │
  ││App process││            ││Activity││                │           │
  ││killed     ││            ││Running ││                │           │
  └┴─────▲─────┴┘            └┴────┬───┴┘                │           │
         │                         │                     │           │
         │                         ▼                     │           │
Apps with higher priority   Another activity comes   User returns    │
need memory                 into the foreground      to the activity │
         │                         │                     │           │
         │                         │                     │           │
         │                    ┌────▼────┐                │           │
         │                    │onPause()├────────────────┘           │
         │                    └────┬────┘                            │
         │                         │                                 │
         │                         │                                 │
         │                  The activity is                          │
         │                  no longer visible                        │
         │                         │                        User navigates
         │                         │                        to the activity
         │                    ┌────▼───┐                             │
         └────────────────────┤onStop()├─────────────────────────────┘
                              └────┬───┘
                                   │
                                   │
                            The activity is finishing or
                            being destroyed by the system
                                   │
                                   │
                              ┌────▼──────┐
                              │onDestroy()│
                              └────┬──────┘
                                   │
                             ┌┬────▼────┬┐
                             ││Activity ││
                             ││Shut Down││
                             └┴─────────┴┘
```

## f) State syntax to display built in zoom control.
In Android, Zoom Control is a class that has some set of methods that are used to control the zoom functionality.
```java
ZoomControl zoomControls = (ZoomControls) findViewById(R.id.simpleZoomControl);
```

## g) Name two classes used to play audio and video in Android.
- The following classes are used to play sound and video in the Android framework:
  - MediaPlayer - This class is the primary API for playing sound and video.
  - AudioManager - This class manages audio sources and audio output on a device.

# 2. Attempt any THREE of the following: 12
## a) Describe Android architecture with diagram.
- Android architecture contains different number of components to support any android device needs. Android software contains an open-source Linux Kernel having collection of number of C/C++ libraries which are exposed through an application framework services.
- The main components of android architecture are following:
1. **Applications:** Applications is the top layer of android architecture. The pre-installed applications like home, contacts, camera, etc and third party applications will be installed on this layer only.
2. **Application framework:** Application Framework provides several important classes which are used to create an Android application.
3. **Application runtime:** Android Runtime environment contains components like core libraries and the Dalvik virtual machine(DVM).
4. **Platform libraries:** The Platform Libraries includes various C/C++ core libraries and Java based libraries such as Media, Graphics, OpenGL etc. to provide a support for android development.
5. **Linux Kernel:** The linux kernel manages all the available drivers such as display drivers, camera drivers, audio drivers, etc. which are required during the runtime.

## b) Differentiate between DVM and JVM
| JVM                                                              	| DVM                                                                           	|
|------------------------------------------------------------------	|-------------------------------------------------------------------------------	|
| JVM supports multiple OS                                         	| DVM supports only Android Operating system.                                   	|
| JVM forms separate classes in separate `.class` byte code files. 	| DVM forms multiple class in `.dex` byte code file.                            	|
| It is based on stack based virtual machine architecture.         	| It is based on register based virtual machine architecture.                   	|
| JVM runs on more memory                                          	| DVM runs on less memory.                                                      	|
| The executable format of JVM is JAR.                             	| The executable format of DVM is APK.                                          	|
| JVM has different constant pools.                                	| DVM has common constant pool.                                                 	|
| It runs `.class` byte code directly.                             	| The `.class` byte codes are optimize to .odex format before executing in DVM. 	|

## c) List and elaborate steps to deploy in Android application on Google play store.
- Step 1 - First generate signed apk of your Android App to publish it on Play Store.
- Step 2 - Sign up for Google Play Console to publish and manage your Android App.
- Step 3 - Now click on Create Application.
- Step 4 - Now fill store listing details of your App which include Title, Short and Full description.
- Step 5 - Now Click on ready on publish along with save draft and click on Manage release.
- Step 6 - After Manage production click on edit release.
- Step 7 - Now click on review.
- Step 8 - After review click on Start Rollout to production.

## d) Describe with example, how to create a simple database in SQLite (Assume suitable data).
- SQLite is a opensource SQL database that stores data to a text file on a device. Android comes in with built in SQLite database implementation.
- SQLite supports all the relational database features.
```java
SQLiteDatabase mydatabase = openOrCreateDatabase("your database name",MODE_PRIVATE,null);
```

# 3. Attempt any THREE of the following: 12

## a) Write down the steps to install and configure Android studio.
- Head over to https://developer.android.com/studio to get the Android Studio executable or zip file.
- Click on the Download Android Studio Button.
- After the downloading has finished, open the file from downloads and run it. It will prompt the following dialog box.
- Once “Finish” is clicked, choose the ‘Don’t import Settings option’.
- This will start the Android Studio.
- After it has found the SDK components, it will redirect to the Welcome dialog box.
- Now it is time to download the SDK components.
- Click on Start a new Android Studio project to build a new app.

## b) State syntax to create Text View and Image button with any two attributes of each.
### TextView
```xml
<TextView
    android:id="@+id/student_name"
    android:layout_width="wrap_content"
    android:layout_height="wrap_content"
    android:text="Name:" />
```
- text -  Sets text of the Textview
- id - Gives a unique ID to the Textview

### ImageButton
```xml
<ImageButton
  android:id="@+id/imageButton"
  android:src="@drawable/button"
  android:layout_height="wrap_content"
  android:layout_width="wrap_content"/>
```
- background - This is a drawable to use as the background.
- id - Gives a unique ID to the Textview

## c) Describe Android service life cycle along with diagram.
- A service is an application component which runs withour direst interaction with the user in the background.
- Services are used for repetitive and potentially long running operations:
  - Internet downloads
  - Checking for new data
  - Data processing
  - Updating content
  - Providers and the like
- They typically run in the background to perform long-running operations or work for remote processes.
```
                             ┌┬────────┬┐
                             ││Activity││
                             ││launched││
                             └┴────┬───┴┘
                                   │
                              ┌────▼─────┐
         ┌────────────────────►onCreate()│
         │                    └────┬─────┘
         │                         │
         │                    ┌────▼────┐                    ┌───────────┐
         │                    │onStart()◄────────────────────┤onRestart()│
         │                    └────┬────┘                    └───────▲───┘
         │                         │                                 │
User navigates                ┌────▼─────┐                           │
to the activity               │onResume()◄───────────────┐           │
         │                    └────┬─────┘               │           │
         │                         │                     │           │
  ┌┬─────┴─────┬┐            ┌┬────┴───┬┐                │           │
  ││App process││            ││Activity││                │           │
  ││killed     ││            ││Running ││                │           │
  └┴─────▲─────┴┘            └┴────┬───┴┘                │           │
         │                         │                     │           │
         │                         ▼                     │           │
Apps with higher priority   Another activity comes   User returns    │
need memory                 into the foreground      to the activity │
         │                         │                     │           │
         │                         │                     │           │
         │                    ┌────▼────┐                │           │
         │                    │onPause()├────────────────┘           │
         │                    └────┬────┘                            │
         │                         │                                 │
         │                         │                                 │
         │                  The activity is                          │
         │                  no longer visible                        │
         │                         │                        User navigates
         │                         │                        to the activity
         │                    ┌────▼───┐                             │
         └────────────────────┤onStop()├─────────────────────────────┘
                              └────┬───┘
                                   │
                                   │
                            The activity is finishing or
                            being destroyed by the system
                                   │
                                   │
                              ┌────▼──────┐
                              │onDestroy()│
                              └────┬──────┘
                                   │
                             ┌┬────▼────┬┐
                             ││Activity ││
                             ││Shut Down││
                             └┴─────────┴┘
```

## d) State and elaborate the syntax of required class and methods for Geocoding.
- A class for handling geocoding and reverse geocoding.
- Geocoding is the process of transforming a street address or other description of a location into a (latitude, longitude) coordinate.
```java
public final class Geocoder
extends Object
```

# 4. Attempt any THREE of the following: 12
## a) Explain with example, code to create GUI using absolute layout (Assume suitable data).
```xml
<?xml version="1.0" encoding="utf-8"?>
<AbsoluteLayout xmlns:android="http://schemas.android.com/apk/res/android"
    xmlns:app="http://schemas.android.com/apk/res-auto"
    xmlns:tools="http://schemas.android.com/tools"
    android:layout_width="match_parent"
    android:layout_height="match_parent"
    android:paddingLeft="16dp"
    android:paddingTop="16dp"
    android:paddingRight="16dp"
    tools:context=".MainActivity">
    <TextView
        android:id="@+id/student_name"
        android:layout_width="wrap_content"
        android:layout_height="wrap_content"
        android:layout_x="125dp"
        android:layout_y="280dp"
        android:text="Name:"
        android:textColor="#86AD33"
        android:textSize="20dp"
        android:textStyle="bold" />
    <TextView
        android:layout_width="wrap_content"
        android:layout_height="wrap_content"
        android:layout_x="125dp"
        android:layout_y="304dp"
        android:text="Age:"
        android:textColor="#86AD33"
        android:textSize="20dp"
        android:textStyle="bold" />
    <TextView
        android:layout_width="wrap_content"
        android:layout_height="wrap_content"
        android:layout_x="125dp"
        android:layout_y="328dp"
        android:text="Mobile Number:"
        android:textColor="#86AD33"
        android:textSize="20dp"
        android:textStyle="bold" />
</AbsoluteLayout>
```

## b) Write a program to demonstrate Date and Time picker.
### Date Picker
- Android Date Picker allows you to select the date consisting of day, month and
  year in your custom user interface.
- Methods of DatePicker:
  - **getDayOfMonth()** - This method gets the selected day of month.
  - **getMonth()** - This method gets the selected month.
  - **getYear()** - This method gets the selected year.
  - **getFirstDayOfWeek()** - This method returns first day of the week.
  - **getCalendarView()** - This method returns calender View.

### TimePicker
- Android Time Picker allows us to select the time of day in either 24h or AM/PM
  mode.
- The time consists of hours, minutes and clock format.
- Methods of TimePicker
1. **setCurrentHour()** - This method sets the current hour.
2. setCurrentMinute() - This method sets the current minute.
3. **is24HoursView()** - This method returns true if this 24 hour view else
   false.
4. **isEnabled()** - This method returns the enabled status for this view.

## c) Describe multimedia framework of Android with diagram.
![Multimedia framework of Android diagram](https://source.android.com/static/docs/core/media/images/ape_media_buffer_alloc_n.png)

## d) Discuss developer console with at least four features.
- Multiple User Accounts
- Store Listing Details
- Upload and Instantly Publish
- Alpha and Beta Testing
- Multiple APK Support
- Selling and Pricing Your Products
- In-app Products
- Distribution Controls
- User Reviews and Crash Reports
- App Statistics

## e) Write a program to demonstrate declaring and using permissions with any relevant example.
AndroidManifest.xml
```xml
<?xml version="1.0" encoding="utf-8"?>
    <manifest xmlns:android="http://schemas.android.com/apk/res/android"
            package="org.geeksforgeeks.requestPermission">

        <!--Declaring the required permissions-->
        <uses-permission android:name="android.permission.READ_EXTERNAL_STORAGE" />
        <uses-permission android:name="android.permission.WRITE_EXTERNAL_STORAGE" />
        <uses-permission android:name="android.permission.CAMERA" />

        <application
            android:allowBackup="true"
            android:icon="@mipmap/ic_launcher"
            android:label="@string/app_name"
            android:roundIcon="@mipmap/ic_launcher_round"
            android:supportsRtl="true"
            android:theme="@style/AppTheme">

            <activity
                android:name=".MainActivity">

                <intent-filter>
                    <action
                        android:name="android.intent.action.MAIN" />

                    <category
                        android:name="android.intent.category.LAUNCHER" />
                </intent-filter>

            </activity>
        </application>

</manifest>
```
activity_main.xml
```xml
<?xml version="1.0" encoding="utf-8"?>
<RelativeLayout
    xmlns:android="http://schemas.android.com/apk/res/android"
    xmlns:app="http://schemas.android.com/apk/res-auto"
    xmlns:tools="http://schemas.android.com/tools"
    android:layout_width="match_parent"
    android:layout_height="match_parent"
    tools:context=".MainActivity">

    <!-- To show toolbar-->
    <android.support.v7.widget.Toolbar
        android:id="@+id/toolbar"
        android:layout_width="match_parent"
        android:background="@color/colorPrimary"
        app:title="GFG | Permission Example"
        app:titleTextColor="@android:color/white"
        android:layout_height="?android:attr/actionBarSize"/>

    <!--Button to request storage permission-->
    <Button
        android:id="@+id/storage"
        android:layout_width="wrap_content"
        android:layout_height="wrap_content"
        android:text="Storage"
        android:layout_marginTop="16dp"
        android:padding="8dp"
        android:layout_below="@id/toolbar"
        android:layout_centerHorizontal="true"/>

    <!--Button to request camera permission-->
    <Button
        android:id="@+id/camera"
        android:layout_width="wrap_content"
        android:layout_height="wrap_content"
        android:text="Camera"
        android:layout_marginTop="16dp"
        android:padding="8dp"
        android:layout_below="@id/storage"
        android:layout_centerHorizontal="true"/>

</RelativeLayout>
```
MainActivity.java
```java
import android.Manifest;
import android.content.pm.PackageManager;
import android.support.annotation.NonNull;
import android.support.v4.app.ActivityCompat;
import android.support.v4.content.ContextCompat;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    // Defining Buttons
    private Button storage, camera;

    // Defining Permission codes.
    // We can give any value
    // but unique for each permission.
    private static final int CAMERA_PERMISSION_CODE = 100;
    private static final int STORAGE_PERMISSION_CODE = 101;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        storage = findViewById(R.id.storage);
        camera = findViewById(R.id.camera);

        // Set Buttons on Click Listeners
        storage.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v)
            {
                checkPermission(Manifest.permission.WRITE_EXTERNAL_STORAGE, STORAGE_PERMISSION_CODE);
            }
        });

        camera.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v)
            {
                checkPermission(Manifest.permission.CAMERA, CAMERA_PERMISSION_CODE);
            }
        });
    }

    // Function to check and request permission.
    public void checkPermission(String permission, int requestCode)
    {
        if (ContextCompat.checkSelfPermission(MainActivity.this, permission) == PackageManager.PERMISSION_DENIED) {

            // Requesting the permission
            ActivityCompat.requestPermissions(MainActivity.this, new String[] { permission }, requestCode);
        }
        else {
            Toast.makeText(MainActivity.this, "Permission already granted", Toast.LENGTH_SHORT).show();
        }
    }

    // This function is called when the user accepts or decline the permission.
    // Request Code is used to check which permission called this function.
    // This request code is provided when the user is prompt for permission.

    @Override
    public void onRequestPermissionsResult(int requestCode,
                                        @NonNull String[] permissions,
                                        @NonNull int[] grantResults)
    {
        super.onRequestPermissionsResult(requestCode,
                                        permissions,
                                        grantResults);

        if (requestCode == CAMERA_PERMISSION_CODE) {
            if (grantResults.length > 0 && grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                Toast.makeText(MainActivity.this, "Camera Permission Granted", Toast.LENGTH_SHORT) .show();
            }
            else {
                Toast.makeText(MainActivity.this, "Camera Permission Denied", Toast.LENGTH_SHORT) .show();
            }
        }
        else if (requestCode == STORAGE_PERMISSION_CODE) {
            if (grantResults.length > 0
                && grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                Toast.makeText(MainActivity.this, "Storage Permission Granted", Toast.LENGTH_SHORT).show();
            } else {
                Toast.makeText(MainActivity.this, "Storage Permission Denied", Toast.LENGTH_SHORT).show();
            }
        }
    }
}
```
