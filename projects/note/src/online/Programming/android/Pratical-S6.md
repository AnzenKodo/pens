## 1. Write a program to place Name, Age, Mobile number linearly(vertical) on the display screen using Linear layout.
```xml
<?xml version="1.0" encoding="utf-8"?>
<LinearLayout xmlns:android="http://schemas.android.com/apk/res/android"
    xmlns:app="http://schemas.android.com/apk/res-auto"
    xmlns:tools="http://schemas.android.com/tools"
    android:layout_width="match_parent"
    android:layout_height="match_parent"
    android:paddingLeft="16dp"
    android:paddingRight="16dp"
    android:paddingTop="16dp"
    android:orientation="vertical"
    tools:context=".MainActivity">
    <TextView
        android:id="@+id/student_name"
        android:layout_width="wrap_content"
        android:layout_height="wrap_content"
        android:text="Name:" />
    <TextView
        android:layout_width="wrap_content"
        android:layout_height="wrap_content"
        android:text="Age:" />
    <TextView
        android:layout_width="wrap_content"
        android:layout_height="wrap_content"
        android:text="Mobile Number:" />
</LinearLayout>
```
[Source](https://codingatharva.blogspot.com/2020/01/program-to-place-ui-component-in-linear-vertical-layout-in-Android-Studio.html)

## 2. Write a program to place Name, Age, Mobile number linearly(vertical) on the display screen using Absolute layout.
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
[Source](https://codingatharva.blogspot.com/2020/01/absolute-layout-centrally-in-Android-Studio.html)
## 3. Write a program to display 5 students basic information in a table form using Table layout.
```xml
<?xml version="1.0" encoding="utf-8"?>
<TableLayout xmlns:android="http://schemas.android.com/apk/res/android"
    xmlns:tools="http://schemas.android.com/tools"
    android:layout_width="match_parent"
    android:layout_height="match_parent"
    android:collapseColumns="*"
    android:shrinkColumns="*"
    tools:context=".MainActivity">
    <TableRow
        android:layout_width="match_parent"
        android:layout_height="wrap_content"
        android:gravity="center_horizontal">
        <TextView
            android:layout_width="match_parent"
            android:layout_height="wrap_content"
            android:text="10 Students Basic Information"
            android:textColor="#86AD33"
            android:textSize="20dp"
            android:textStyle="bold" />
    </TableRow>
    <TableRow
        android:layout_width="match_parent"
        android:layout_height="wrap_content">
        <TextView
            android:layout_width="0dp"
            android:layout_weight="1"
            android:text="Student Numbers"
            android:textColor="#000"
            android:textStyle="bold" />
        <TextView
            android:layout_width="0dp"
            android:layout_weight="1"
            android:text="Name"
            android:textColor="#000"
            android:textStyle="bold" />
        <TextView
            android:layout_width="0dp"
            android:layout_weight="1"
            android:text="RollNo"
            android:textColor="#000"
            android:textStyle="bold" />
        <TextView
            android:layout_width="0dp"
            android:layout_weight="1"
            android:text="Age"
            android:textColor="#000"
            android:textStyle="bold" />
    </TableRow>
    <TableRow
        android:layout_width="match_parent"
        android:layout_height="wrap_content">
        <TextView
            android:layout_width="0dp"
            android:layout_weight="1"
            android:layout_height="wrap_content"
            android:text="Student 1:"
            android:textColor="#86AD33"
            android:textStyle="bold" />
        <EditText
            android:layout_width="0dp"
            android:layout_weight="1"
            android:layout_height="wrap_content"
            />
        <EditText
            android:layout_width="0dp"
            android:layout_weight="1"
            android:layout_height="wrap_content" />
        <EditText
            android:layout_width="0dp"
            android:layout_weight="1"
            android:layout_height="wrap_content" />
    </TableRow>
    <TableRow
        android:layout_width="match_parent"
        android:layout_height="wrap_content">
        <TextView
            android:layout_width="0dp"
            android:layout_weight="1"
            android:text="Student 2:"
            android:textColor="#86AD33"
            android:textStyle="bold" />
        <EditText
            android:layout_width="0dp"
            android:layout_weight="1"
            android:layout_height="wrap_content" />
        <EditText
            android:layout_width="0dp"
            android:layout_weight="1"
            android:layout_height="wrap_content" />
        <EditText
            android:layout_width="0dp"
            android:layout_weight="1"
            android:layout_height="wrap_content" />
    </TableRow>
    <TableRow
        android:layout_width="match_parent"
        android:layout_height="wrap_content">
        <TextView
            android:layout_width="0dp"
            android:layout_weight="1"
            android:text="Student 3:"
            android:textColor="#86AD33"
            android:textStyle="bold" />
        <EditText
            android:layout_width="0dp"
            android:layout_weight="1"
            android:layout_height="wrap_content" />
        <EditText
            android:layout_width="0dp"
            android:layout_weight="1"
            android:layout_height="wrap_content" />
        <EditText
            android:layout_width="0dp"
            android:layout_weight="1"
            android:layout_height="wrap_content" />
    </TableRow>
    <TableRow
        android:layout_width="match_parent"
        android:layout_height="wrap_content">
        <TextView
            android:layout_width="0dp"
            android:layout_weight="1"
            android:text="Student 4:"
            android:textColor="#86AD33"
            android:textStyle="bold" />
        <EditText
            android:layout_width="0dp"
            android:layout_weight="1"
            android:layout_height="wrap_content" />
        <EditText
            android:layout_width="0dp"
            android:layout_weight="1"
            android:layout_height="wrap_content" />
        <EditText
            android:layout_width="0dp"
            android:layout_weight="1"
            android:layout_height="wrap_content" />
    </TableRow>
    <TableRow
        android:layout_width="match_parent"
        android:layout_height="wrap_content">
        <TextView
            android:layout_width="0dp"
            android:layout_weight="1"
            android:text="Student 5:"
            android:textColor="#86AD33"
            android:textStyle="bold" />
        <EditText
            android:layout_width="0dp"
            android:layout_weight="1"
            android:layout_height="wrap_content" />
        <EditText
            android:layout_width="0dp"
            android:layout_weight="1"
            android:layout_height="wrap_content" />
        <EditText
            android:layout_width="0dp"
            android:layout_weight="1"
            android:layout_height="wrap_content" />
    </TableRow>
</TableLayout>
```
[Source](https://codingatharva.blogspot.com/2020/02/program-to-display-10-students-basic-info-in-table-layout-android.html)
## 4. Write a program to accept username and password from the end user using Text View and edit Text.
```xml
<?xml version="1.0" encoding="utf-8"?>
<TableLayout xmlns:android="http://schemas.android.com/apk/res/android"
    xmlns:app="http://schemas.android.com/apk/res-auto"
    xmlns:tools="http://schemas.android.com/tools"
    android:layout_width="match_parent"
    android:layout_height="match_parent"
    android:padding="50dp"
    tools:context=".MainActivity">
    <TextView
        android:layout_width="wrap_content"
        android:layout_height="wrap_content"
        android:gravity="center"
        android:textSize="25dp"
        android:text="Login Page" />
    <TableRow
        android:layout_width="match_parent"
        android:layout_height="wrap_content"
        android:gravity="center_horizontal">
        <TextView
            android:layout_height="wrap_content"
            android:layout_weight="1"
            android:gravity="center"
            android:text="Enter UserName:" />

        <EditText
            android:id="@+id/user"
            android:layout_height="wrap_content"
            android:layout_weight="1"
            android:hint="abc@gmail.com" />
    </TableRow>
    <TableRow
        android:layout_width="match_parent"
        android:layout_height="wrap_content"
        android:gravity="center_horizontal">
        <TextView
            android:layout_height="wrap_content"
            android:layout_weight="1"
            android:gravity="center"
            android:text="Enter Password:" />
        <EditText
            android:id="@+id/pass"
            android:layout_height="wrap_content"
            android:layout_weight="1"
            android:hint="1234" />
    </TableRow>
    <Button
        android:id="@+id/btn1"
        android:layout_width="wrap_content"
        android:layout_height="wrap_content"
        android:layout_marginBottom="172dp"
        android:text="Login" />
</TableLayout>
```
```java
import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;
public class MainActivity extends AppCompatActivity {
   EditText user,pass;
    Button b;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        b= findViewById(R.id.btn1);
        user = findViewById(R.id.user);
        pass = findViewById(R.id.pass);
        b.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(user.getText().toString().equals("atharva") & pass.getText().toString().equals("1234"))
?
                {
                    Toast.makeText( getApplicationContext(),"Login Sucessful",Toast.LENGTH_SHORT).show();
                }
                else
                {
                    Toast.makeText( getApplicationContext(),"Login UnSucessful",Toast.LENGTH_SHORT).show();
                }
            }
        });
    }
}
```
[Source](https://codingatharva.blogspot.com/2020/03/program-to-accept-username-and-password-in-Android-Studio.html)
## 5. Write a program to create a toggle button to display ON/OFF Bluetooth on the display screen.
```xml
<?xml version="1.0" encoding="utf-8"?>
<RelativeLayout xmlns:android="http://schemas.android.com/apk/res/android"
    xmlns:app="http://schemas.android.com/apk/res-auto"
    xmlns:tools="http://schemas.android.com/tools"
    android:layout_width="match_parent"
    android:layout_height="match_parent"
    tools:context=".MainActivity"
    android:padding="20dp">
    <ToggleButton
        android:id="@+id/toggleButton"
        android:layout_width="wrap_content"
        android:layout_height="50dp"
        android:text="ToggleButton"
        android:textOn="ON"
        android:textOff="OFF"
        android:textSize="20sp"
        android:layout_centerInParent="true"/>
    <TextView android:id="@+id/textView"
        android:layout_width="match_parent"
        android:layout_height="wrap_content"
        android:layout_below="@id/toggleButton"
        android:text="Bluetooth is OFF"
        android:gravity="center_horizontal"
        android:layout_marginTop="20dp"
        android:textSize="20sp"
        android:textColor="@color/colorAccent"/>
</RelativeLayout>
```
```java
package com.example.togglebuttonbluetooth;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.CompoundButton;
import android.widget.TextView;
import android.widget.ToggleButton;

public class MainActivity extends AppCompatActivity {

    ToggleButton toggleButton;
    TextView textView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {

        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        toggleButton = findViewById(R.id.toggleButton);
        textView = findViewById(R.id.textView);

        toggleButton.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {

            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {

                if(isChecked)
                {
                    textView.setText("Bluetooth is " + toggleButton.getTextOn());
                }
                else
                {
                    textView.setText("Bluetooth is " + toggleButton.getTextOff());
                }
            }
        });
    }
}
```
[Source](http://www.programmingtutorials4u.com/android-programming/programs/android-toggle-button/)
## 6. Write a program to create a login form for a social networking site.
```xml
<?xml version="1.0" encoding="utf-8"?>
<RelativeLayout xmlns:android="http://schemas.android.com/apk/res/android"
    xmlns:app="http://schemas.android.com/apk/res-auto"
    xmlns:tools="http://schemas.android.com/tools"
    android:layout_width="match_parent"
    android:layout_height="match_parent"
    android:background="#495B8F"
    android:padding="20dp"
    tools:context=".MainActivity">

    <TextView android:id="@+id/logo"
        android:layout_width="match_parent"
        android:layout_height="80dp"
        android:text="F A C E B O O K"
        android:gravity="center"
        android:textSize="40sp"
        android:textStyle="bold"
        android:layout_marginTop="40dp"
        android:textColor="@android:color/white"/>

    <EditText
        android:id="@+id/username"
        android:layout_width="match_parent"
        android:layout_height="60dp"
        android:layout_below="@id/logo"
        android:layout_marginTop="30dp"
        android:background="@android:color/white"
        android:fontFamily="monospace"
        android:hint="Email or phone number"
        android:padding="10dp"
        android:textSize="22sp" />

    <EditText
        android:id="@+id/password"
        android:layout_width="match_parent"
        android:layout_height="60dp"
        android:layout_below="@id/username"
        android:background="@android:color/white"
        android:fontFamily="monospace"
        android:hint="Password"
        android:padding="10dp"
        android:layout_marginTop="20dp"
        android:textSize="22sp" />

    <Button android:id="@+id/btnLogin"
        android:layout_width="match_parent"
        android:layout_height="50dp"
        android:layout_below="@id/password"
        android:layout_marginTop="30dp"
        android:text="Log In"
        android:background="#6D9ADD"
        android:textColor="@android:color/white"
        android:textSize="18sp"/>

    <TextView
        android:layout_width="wrap_content"
        android:layout_height="wrap_content"
        android:layout_centerHorizontal="true"
        android:text="Forgot Password?"
        android:textColor="@android:color/white"
        android:layout_below="@id/btnLogin"
        android:layout_marginTop="10dp"
        android:textSize="16sp"/>

</RelativeLayout>
```
```java
package com.example.socialnetworkingapp;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {

        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }
}
```
[Source](http://www.programmingtutorials4u.com/android-programming/programs/social-networking-login-form/)
## 7. Write a program to show five checkboxes and toast selected checkbox.
```xml
<?xml version="1.0" encoding="utf-8"?>
<LinearLayout xmlns:android="http://schemas.android.com/apk/res/android"
    xmlns:app="http://schemas.android.com/apk/res-auto"
    xmlns:tools="http://schemas.android.com/tools"
    android:layout_width="match_parent"
    android:layout_height="match_parent"
    android:orientation="vertical"
    android:padding="10dp"
    tools:context=".MainActivity">

    <CheckBox
        android:id="@+id/cb1"
        android:layout_width="wrap_content"
        android:layout_height="wrap_content"
        android:text="Android"
        android:textSize="25dp"
        android:layout_gravity="center"
        android:padding="10dp"
        android:checked="false"/>

    <CheckBox
        android:id="@+id/cb2"
        android:layout_width="wrap_content"
        android:layout_height="wrap_content"
        android:text="Pythpn"
        android:textSize="25dp"
        android:layout_gravity="center"
        android:padding="10dp"
        android:checked="false"/>
    <CheckBox
        android:id="@+id/cb3"
        android:layout_width="wrap_content"
        android:layout_height="wrap_content"
        android:text="PHP"
        android:textSize="25dp"
        android:layout_gravity="center"
        android:padding="10dp"
        android:checked="false"/>
    <CheckBox
        android:id="@+id/cb4"
        android:layout_width="wrap_content"
        android:layout_height="wrap_content"
        android:text="C"
        android:textSize="25dp"
        android:layout_gravity="center"
        android:padding="10dp"
        android:checked="false"/>
    <CheckBox
        android:id="@+id/cb5"
        android:layout_width="wrap_content"
        android:layout_height="wrap_content"
        android:text="Java"
        android:textSize="25dp"
        android:layout_gravity="center"
        android:padding="10dp"
        android:checked="false"/>

    <Button
        android:id="@+id/btn"
        android:layout_width="wrap_content"
        android:layout_height="wrap_content"
        android:text="Submit"
        android:textSize="35dp"
        android:layout_gravity="center"
        android:padding="10dp"/>
</LinearLayout>
```
[Source](https://codingatharva.blogspot.com/2020/03/program-demonstrate-checkboxes-in-android-studio.html)
## 8. Write a program to display circular progress bar.
```xml
<?xml version="1.0" encoding="utf-8"?>
<LinearLayout
    xmlns:android="http://schemas.android.com/apk/res/android"
    xmlns:tools="http://schemas.android.com/tools"
    android:layout_width="match_parent"
    android:layout_height="match_parent"
    android:gravity="center_horizontal"
    android:orientation="vertical"
    tools:context=".MainActivity">

    <RelativeLayout
        android:id="@+id/progress_layout"
        android:layout_width="200dp"
        android:layout_height="200dp"
        android:layout_margin="100dp">

        <!--progress bar implementation-->
        <ProgressBar
            android:id="@+id/progress_bar"
            style="?android:attr/progressBarStyleHorizontal"
            android:layout_width="match_parent"
            android:layout_height="match_parent"
            android:background="@drawable/circular_shape"
            android:indeterminate="false"
            android:progressDrawable="@drawable/circular_progress_bar"
            android:textAlignment="center" />

        <!--Text implementation in center of the progress bar-->
        <TextView
            android:id="@+id/progress_text"
            android:layout_width="wrap_content"
            android:layout_height="wrap_content"
            android:layout_alignParentLeft="true"
            android:layout_alignParentRight="true"
            android:layout_centerVertical="true"
            android:gravity="center"
            android:text="---"
            android:textColor="@color/colorPrimary"
            android:textSize="28sp"
            android:textStyle="bold" />
    </RelativeLayout>

</LinearLayout>
```
```java
import android.os.Bundle;
import android.os.Handler;
import android.widget.ProgressBar;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

public class MainActivity extends AppCompatActivity {

    private ProgressBar progressBar;
    private TextView progressText;
    int i = 0;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // set the id for the progressbar and progress text
        progressBar = findViewById(R.id.progress_bar);
        progressText = findViewById(R.id.progress_text);

        final Handler handler = new Handler();
        handler.postDelayed(new Runnable() {
            @Override
            public void run() {
                // set the limitations for the numeric
                // text under the progress bar
                if (i <= 100) {
                    progressText.setText("" + i);
                    progressBar.setProgress(i);
                    i++;
                    handler.postDelayed(this, 200);
                } else {
                    handler.removeCallbacks(this);
                }
            }
        }, 200);
    }
}
```
[Source](https://www.geeksforgeeks.org/how-to-implement-circular-progressbar-in-android/)
## 9. Write a program to display 15 buttons using Grid view.
[Source](https://codingatharva.blogspot.com/2020/03/program-to-display-15-buttons-using-grid-view-in-android-studio.html)
## 10. Write a program to display a toast message
```java
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    Button b1;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        b1 = (Button) findViewById(R.id.toast_button);

        b1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Toast.makeText(MainActivity.this,"You just Toasted me!!!",Toast.LENGTH_LONG).show();
                /*Another way to display a Toast message
                    Toast t=Toast.makeText(MainActivity.this,"You just Toasted me!!!",Toast.LENGTH_LONG);
                    t.show();
                */
            }
        });
    }

}
```
```xml
<RelativeLayout xmlns:android="http://schemas.android.com/apk/res/android"
    xmlns:tools="http://schemas.android.com/tools"
    android:id="@+id/activity_main"
    android:layout_width="match_parent"
    android:layout_height="match_parent"
    android:paddingBottom="@dimen/activity_vertical_margin"
    android:paddingLeft="@dimen/activity_horizontal_margin"
    android:paddingRight="@dimen/activity_horizontal_margin"
    android:paddingTop="@dimen/activity_vertical_margin"
    tools:context="codedost.toast.MainActivity">

    <Button
        android:id="@+id/toast_button"
        android:layout_width="wrap_content"
        android:layout_height="wrap_content"
        android:text="Toast me!"
        android:layout_centerVertical="true"
        android:layout_centerHorizontal="true"
    />

</RelativeLayout>
```
[Source](https://www.javatpoint.com/android-toast-example)
