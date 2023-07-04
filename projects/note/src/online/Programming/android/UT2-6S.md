# MAD QUESTION BANK

## 1. Write the syntax for Intent-Filter tag.
```xml
<intent-fliter
android:icon="drawable resource"
android:label="string resource"
android:priority="integer">
</intent-fliter>
```

## 2. Define Services in Android OS.
- A service is an application component which runs withour direst interaction
  with the user in the background.
- Services are used for repetitive and potentially long running operations:
  - Internet downloads
  - Checking for new data
  - Data processing
  - Updating content
  - Providers and the like
- They typically run in the background to perform long-running operations or
  work for remote processes.

### 1. Started
- The service start with startService() function.
- To stop the service we can use stopService() & stopSelf() function.

### 2. Bound
- A service is bound when an application component binds to it by calling
  bindService().
- To un bound the service we can use unbindService() function.

## 3. Enlist the steps to publish the Android application
- **Step 1** - Sign up or Sign in for an account on the Android Developer
  console.
- **Step 2** - Create a new appplication.
- **Step 3** - Prepare multimedia.
- **Step 4** - Prepare code for release.
- **Step 5** - Build a release-ready APK.
- **Step 6** - Upload APK complete the checklist on the left until all the items
  have a green checkmark.

## 5. What is Date and Time picker with its methods?
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

## 6. Write a program to display circular progress bar.
```xml
<?xml version="1.0" encoding="utf-8"?>
<RelativeLayout
  xmlns:android="https://schemas.android.com/apk/res/android"
  xmlns:app="https://schemas.android.com/apk/res-auto"
  xmlns:tools="https://schemas.android.com/tools"
  android:layout_width="match_parent"
  android:layout_height="match_parent"
  tools:context=".MainActivity">
  <Button
    android:id="@+id/btnDownloadFile"
    android:layout_width="wrap_content"
    android:layout_height="wrap_content"
    android:text="Download File"
    andorid:layout_centerInParent="true" />
</RelativeLayout>
```

## 7. List sensors in Android and explain anyone in detail.
The Android supports broad categories of sensors:
1. Motion Sensors
2. Enviromental Sensors
3. Position Sensors

### Montion Sensors:
- A motion sensor (or motion detector) is an electronic device that is designed
  to detect and measure movements.
- Motion sensors are used primarily in home and business secrity systems.
- These sensors measure accelecation forces and rotational forces along three
  axes.

## 8. Develop the registration form using the following GUI.
```xml
<RelativeLayout
  xmlns:android="https://schemas.android.com/apk/res/android"
  xmlns:tools="https://schemas.android.com/tools"
  android:layout_width="match_parent"
  android:layout_height="match_parent"
  android:paddingBottom="wrap_content"
  android:paddingTop="wrap_content"
  tools:context=".MainActivity">
  <FrameLayout>
    <ImageView
      android:layout_width="wrap_content"
      android:layout_height="wrap_content"
      android:src="@drawable/banner_image" />
  <FrameLayout>
  <EditText
    android:id="@+id/editText1"
    android:hint="Name"
    android:layout_width="wrap_content"
    android:layout_height="wrap_content"
    android:layout_centerHorizontal="true"
    android:layout_centerVertical="true"
    android:drawableLeft="@drawable/name_image" />
  <EditText
    android:id="@+id/editText2"
    android:hint="Email ID"
    android:layout_width="wrap_content"
    android:layout_height="wrap_content"
    android:layout_centerHorizontal="true"
    android:layout_centerVertical="true"
    android:drawbleLeft="@drawable/email_image" />
  <EditText
    android:id="@+id/editText1"
    android:hint="Password"
    android:layout_width="wrap_content"
    android:layout_height="wrap_content"
    android:layout_centerHorizontal="true"
    android:layout_centerVertical="true"
    android:drawableLeft="@drawable/pass_image" />
  <EditText
    android:id="@+id/editText1"
    android:hint="Confirm Password"
    android:layout_width="wrap_content"
    android:layout_height="wrap_content"
    android:layout_centerHorizontal="true"
    android:layout_cneterVertical="true"
    android:drawableLeft="@drawable/conpass_image" />
  <EditText
    android:id="@+id/editText1"
    android:hint="Enter Mobile"
    android:layout_width="wrap_content"
    android:layout_height="wrap_content"
    android:layout_centerHorizontal="true"
    android:layout_centerVertical="true"
    android:drawableLeft="@drawable/mobile_image" />
  <RadioButton
    android:id="@+id/radioMale"
    android:layout_width="wrap_content"
    android:layout_height="wrap_content"
    android:text="Male" />
  <RadioButton
    android:id="@+id/radioFemale"
    android:layout_width="wrap_content"
    android:layout_height="wrap_content"
    android:text="Female" />
  <Button
    android:id="@+id/btnDisplay"
    android:layout_width="wrap_content"
    android:layout_height="wrap_content"
    android:text="Register" />
</RelativeLayout>
```
