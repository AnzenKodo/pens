# MAD VIVA QUESTION
(thk to SaturoGojoo,AK,NEWBIEN00B)

## 1) What is android?
Android is a mobile operating system based on a modified version of the Linux kernel and other open source software, designed primarily for touchscreen mobile devices such as smartphones and tablets.

## 2) Enlist Features of android?
* Open Source
* Beautiul UI
* Connectivity
* Storage
* Multi-Touch
* Multi-Tasking
* Multi-Language
* Resizable widgets
* Messaging
* Media Support
* Web Browser

## 3) Explain android architecture?
- Android architecture contains different number of components to support any android device needs. Android software contains an open-source Linux Kernel having collection of number of C/C++ libraries which are exposed through an application framework services.

- The main components of android architecture are following:
1. **Applications:** Applications is the top layer of android architecture. The pre-installed applications like home, contacts, camera, etc and third party applications will be installed on this layer only.
2. **Application framework:** Application Framework provides several important classes which are used to create an Android application.
3. **Application runtime:** Android Runtime environment contains components like core libraries and the Dalvik virtual machine(DVM).
4. **Platform libraries:** The Platform Libraries includes various C/C++ core libraries and Java based libraries such as Media, Graphics, OpenGL etc. to provide a support for android development.
5. **Linux Kernel:** The linux kernel manages all the available drivers such as display drivers, camera drivers, audio drivers, etc. which are required during the runtime.

## 4) Explain android sdk?
- The Android software development kit(SDK)  allows developers to create applications for the Android platform. The Android SDK is the most important software of Android which is installed.
- The Android SDK provides to test application API libraries and emulator documentation sample code developer tools and tutorials which helps us to build and test the debug apps from Android.
- Android SDK provides the tools and application programming interface(API)  for developers to create applications on the Android platform using Java programming language.

## 5) What is Android AVD?
- An AVD is an emulator configuration that enables to modules an actual device
  by calling hardware and software option to be emulated by the Android
  emulator.
- The AVD manager is an interface that we can launch from android studio which
  helps us to create and manage AVD.
- An AVD contains hardware profile, system image, storage area, skin and other
  properties.
- AVD contains emulator for Wear OS, TV, Mobile Phones, Tables, Automotive.

### Hardware profile
- Hardware profile defines the characteristics of a device as shipped from the
  factory of a device as shipped from the factory.
- The AVD manager comes preloaded with certain hardware profile such as Pixel
  device and we can define or customize the hardware profile as needed.

### System image
- A system image labelled with Google API includes access to Google Play
  services.
- A system image Labelled with Google Play logo in the Play Store includes the
  Google Play Store apps and can access to the Google Play Services.

### Storage Area
- The AVD has dedicated storage area on our development machine.
- It stores the devices data such as installed apps and settings, as well as
  emulated and SD cards.
- If needed we can use the AVD manager to wipe user data so that the devices has
  the same data as if it was a new device.

## 6) What is emulator?
The Android Emulator simulates Android devices on your computer so that you can test your application on a variety of devices and Android API levels without needing to have each physical device.

## 7) Difference between JVM and dVM?

| JVM                                                              	| DVM                                                                           	|
|------------------------------------------------------------------	|-------------------------------------------------------------------------------	|
| JVM supports multiple OS                                         	| DVM supports only Android Operating system.                                   	|
| JVM forms separate classes in separate `.class` byte code files. 	| DVM forms multiple class in `.dex` byte code file.                            	|
| It is based on stack based virtual machine architecture.         	| It is based on register based virtual machine architecture.                   	|
| JVM runs on more memory                                          	| DVM runs on less memory.                                                      	|
| The executable format of JVM is JAR.                             	| The executable format of DVM is APK.                                          	|
| JVM has different constant pools.                                	| DVM has common constant pool.                                                 	|
| It runs `.class` byte code directly.                             	| The `.class` byte codes are optimize to .odex format before executing in DVM. 	|

## 8) What are activities?
1. Activities dictate the UI and handles the user interaction to the smart phone screen.
2. Activities represent a single screen that user interact.

## 9) What are services?
- A service is an application component which runs in the background.
- There are three types of service in Android:

### Foreground service
- A foreground service performs some operation that is noticeable to the user.
- For example, an audio app would use a foreground service to play an audio track.
- Foreground services must display a Notification. Foreground services continue running even when the user isn't interacting with the app.

### Backgroud Service**
- A background service performs an operation that isn't directly noticed by the user.
- For example, if an app used a service to compact its storage, that would usually be a background service.

### Bound Service
- A service is bound when an application component binds to it by calling bindService().
-  A bound service offers a client-server interface that allows components to interact with the service, send requests, receive results, and even do so across processes with interprocess communication (IPC).

## 10) What are intents(`Implict` and `explicit` intent)?
### Implicit intent
The implicit intent is the intent where instead of defining the exact components, you define the action that you want to perform for different activities.

### Explicit intent
An explicit intent is an intent where you explicitly define the component that needs to be called by Android System. An explicit intent is one that you use to launch a specific app component, such s a particular activity or service in your app.

## 11) Explain main Activity file ,manifest and layout file?

**MainActivity file**
The main activity. Java file is automatically kept in this folder by Android studio all the classes will be available here and Android studio will even bundle together the package so that we can work with the file without having to go through all the folders.

**Manifest file**
It contains an Android manifest.xml file that is generated by Android studio when we create a project. This file contains the configuration parameters of a project such as Permission services and additional libraries.

**Layout file**
Layout specifies the various widgets to be used in the UI and the relationships between such widgets and their containers. Layout files are stored in "res-> layout" in the Android application.

## 12) What are different types of UI compents?
**TextView**
TextView is a UI Component that displays the text to the user on their Display Screen.
**EditText**
EditText is a user interface control that allows the users to enter some text.
**Button**
This is a UI that is used to perform some action as soon as the user clicks on it.
**ProgressBar**
Progress bars are used to show progress of a task. For example, when you are uploading or downloading something from the internet, it is better to show the progress of download/upload to the user. In android there is a class called Progress Dialog that allows you to create progress bar.

## 13) What are Layouts (`LinearLayout`, `AbsoluteLayout`, `TableLayout`, `FrameLayout`, `RelativeLayout`)?
**LinearLayout** is a view group that aligns all children in a single direction, vertically or horizontally.
**AbsoluteLayout** enables us to specify the exact location of its children.
**TableLayout** is a view that groups views into rows and columns.
**RelativeLayout** is a view group that displays child views in relative positions.
**FrameLayout** is a placeholder on screen that we can use to display a single view.

## 14) Define: `textview`, `Edittextview`, `Button`, `Image button`, `checkbox`(attributes and methods)?
- **TextView** - This control is used to display text to the user.
- **EditTextView** - EditText is a predefined subclass of TextView that includes rich editing capabilities.
- **Button** - A push-button that can be pressed, or clicked, by the user to perform an action.
- **ImageButton** - An ImageButton is an AbsoluteLayout which enables you to specify the exact location of its children. This shows a button with an image (instead of text) that can be pressed or clicked by the user.
- **CheckBox** - An on/off switch that can be toggled by the user. You should use check box when presenting users with a group of selectable options that are not mutually exclusive.

## 15) Explain `listview`, `gridview`, `imageview`, `scrollview`?
- **ListView** - List of scrollable items can be displayed in Android using ListView. It helps you to displaying the data in the form of a scrollable list.
- **GridView** - It is a view group that display items in two dimensional scrolling grid (rows and columns), the grid items are not necessarily predetermined but they are automatically inserted to the layout using a ListAdapter.
- **ImageView** - It is used to display an image file in application.
- **Scrollview** - It is a view group that is used to make vertically scrollable views. A scroll view contains a single direct child only.

## 16) What is toast explain with example?
- Toast is used to display information for a period of time.
- It contains a message to be displayed quickly and disappears after specified period of time.
- It does not block the user interaction.
- Example:
```xml=
Toast.makeText(getApplicationContext(),"Hello Javatpoint",Toast.LENGTH_SHORT).show();
```
## 17) Explain activity lifecycle?
<!-- Android Activity Lifecycle is controlled by 7 methods of android.app.Activity class.
- The android Activity is the subclass of ContextThemeWrapper class.
- An activity is the single screen in android. It is like window or frame of Java.
- By the help of activity, you can place all your UI components or widgets in a single screen.

![Activity Lifecycle Image](https://i.imgur.com/VKu9fbr.png)-->

- **7 lifecycle methods of android activity.**
    - **onCreate** - called when activity is first created.
    - **onStart** - called when activity is becoming visible to the user.
    - **onResume** - called when activity will start interacting with the user.
    - **onPause** - called when activity is not visible to the user.
    - **onStop** - called when activity is no longer visible to the user.
    - **onRestart** - called after your activity is stopped, prior to start.
    - **onDestroy** - called before the activity is destroyed.

## 18) Explain broadcast receivers?
Broadcast Receivers simply respond to broadcast messages from other applications or from the system itself. These messages are sometime called events or intents.

### Creating the Broadcast Receiver
A broadcast receiver is implemented as a subclass of Broadcast Receiver class and overriding the `onReceive()` method where each message is received as an Intent object parameter.

### Registering Broadcast Receiver
An application listens for specific broadcast intents by registering a broadcast receiver in AndroidManifest.xml file. Consider we are going to register MyReceiver for system generated event `ACTION_BOOT_COMPLETED` which is fired by the system once the Android system has completed the boot process.

## 19) Explain content provider?
Android system allows the content provider to store the application data in several ways. Users can manage to store the application data like images, audio, videos, and personal contact information by storing them in SQLite Database, in files, or even on a network. In order to share the data, content providers have certain permissions that are used to grant or restrict the rights to other applications to interfere with the data.

## 20) What is sensors?
- Most Android-powered devices have built-in sensors that measure motion, orientation, and various environmental conditions.
- These sensors are capable of providing raw data with high precision and accuracy, and are useful if you want to monitor three-dimensional device movement or positioning, or you want to monitor changes in the ambient environment near a device.
- There are three type of sensors in android:

### Mostion sensors
These sensors measure acceleration forces and rotational forces along three axes. This category includes accelerometers, gravity sensors, gyroscopes, and rotational vector sensors.

### Environmental sensors
These sensors measure various environmental parameters, such as ambient air temperature and pressure, illumination, and humidity. This category includes barometers, photometers, and thermometers.

### Position sensors
These sensors measure the physical position of a device. This category includes orientation sensors and magnetometers.

## 21) What is location based services?
**Location Based Services:** Creating the Project, Getting the Maps API Key, Displaying the Map, Displaying the Zoom Control, Navigating to a Specific Location, Adding Markers, Getting Location,Geocoding and Reverse Geocoding, Getting Location Data, Monitoring Location.

## 22) What is Geo code and reverse Geo code?

### Geo code
Geocoding is the process of converting addresses (like a street address) into geographic coordinates (like latitude and longitude), which you can use to place markers on a map, or position the map.

### Reverse Geo code
Reverse geocoding is the process of converting geographic coordinates into a human-readable address.

## 23) Enlist Steps to publish android application?
**Step 1:** First generate signed apk of your Android App to publish it on Play Store.
**Step 2:** Sign up for Google Play Console to publish and manage your Android App.
**Step 3:** Now click on Create Application.
**Step 4:** Now fill store listing details of your App which include Title, Short and Full description.
**Step 5:** Now Click on ready on publish along with save draft and click on Manage release.
**Step 6:** After Manage production click on edit release.
**Step 7:** Now click on review.
**Step 8:** After review click on Start Rollout to production.

## 24) What is Date and time Picker?
### Datepicker
- Datepicker is a widget used to select a date. It allows to select date by day, month and year in your custom UI (user interface).
- Methods of DatePicker inckudes getDayOfMonth(), getMonth(), getYear(), getFirstDayOfWeek()

### Timepicker
- Timepicker is a widget used for selecting the time of the day in either AM/PM mode or 24 hours mode. The displayed time consist of hours, minutes and clock format.
- Methods of Timepicker inckudes setCurrentHour(), setHour(), setCurrentMinute(), getCurrentMinute()
