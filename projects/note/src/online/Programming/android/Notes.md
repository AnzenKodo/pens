# Android

## 1. What is Mobile application?
- A mobile application, most commonly referred to as an app, is a type of
  application software deigned to run on a mobile device, such as a smart phone
  or tablet computer.
- Mobile app development is the process by which a mobile applications is
  developed for mobile devices like Personal Digital Assistants (PDAs), tablet
  computer or mobile smart phones.
- Android is mobile operating system developed by Google, based on a modified
  version of the Linux kernel and other open source software and designed
  primarily for touchscreen mobile devices such as smart phones and tablets.
- Application developers, Android is an open platform that provides exciting
  opportunities for developing virtually app imaginable.

## 3. What is Android?
- The android is a powerful Operating System(OS) and it supports large numbers
  of applications(apps) in smart phones.
- The hardware that supports android software is based on ARM architecture
  platform.
- The android is an open source operating system means that it is free and any
  one can use it.
- The android development supports with the full Java programming language.

## 4. Enlist features of Android OS?
- **Storage** - SQLite a lightweight relational database, is used for data
  storage purpose.
- **Multitasking** - Multitasking of application, with unique handling of
  memory allocation, will be existing.
- **Web Browser** - The web browser available in Android OS is based on the
  open source WebKit layout engine, attached with Chrome's V8 JavaScript engine.
- **Open Source** - Android is open-source operating system.
- **Accessibility** - Built in text to speech in Android OS is provided by Talk
  back for people with low or no vision.
- **Media Support** - Android supports the many media formats like:
  - WenM
  - H.263
  - H.254
  - AAC
  - HE-AAC
  - MPEG-4

## 5. State Advantages and Disadvantages of Android OS?

### Advantages
- Supports 2D and 3D Graphics
- Supports Multiple Languages
- Faster Web Browser
- Video Calling
- Open Source Framework
- Uses of Tools are Very Simple
- Availability of Apps
- Great Social Networking Integration
- Better Notification System
- Update User Interface Design
- At a Time Applications
- Low Chance of Crashing
- Stability
- Multitasking

### Disadvantages
- Need Internet Connection
- Advertising
- Wasteful Battery
- Many Applications
- Slow Response
- Heat

## 6. Describe Architecture of Android diagrammatically.
```
┌──────────────────────────────────────────────────────────────────────────────┐
│ Application                                                                  │
│ ┌────┐ ┌────────┐ ┌─────┐ ┌───────┐ ┌───┐                                    │
│ │Home│ │Contacts│ │Phone│ │Browser│ │***│                                    │
│ └────┘ └────────┘ └─────┘ └───────┘ └───┘                                    │
│                                                                              │
│ ┌────┐ ┌──────┐ ┌─────┐ ┌────────┐ ┌───┐                                     │
│ │SMS │ │E-Mail│ │Clock│ │Calander│ │***│                                     │
│ └────┘ └──────┘ └─────┘ └────────┘ └───┘                                     │
│                                                                              │
├──────────────────────────────────────────────────────────────────────────────┤
│                                                                              │
│ Application Framework                                                        │
│ ┌────────────────┐ ┌──────────────┐ ┌─────────────────┐ ┌───────────┐        │
│ │Activity Manager│ │Window Manager│ │Content Providers│ │View System│        │
│ └────────────────┘ └──────────────┘ └─────────────────┘ └───────────┘        │
│                                                                              │
│ ┌───────────────┐ ┌─────────────────┐ ┌────────────────┐ ┌────────────────┐  │
│ │Package Manager│ │Telephony Manager│ │Resource Manager│ │Location Manager│  │
│ └───────────────┘ └─────────────────┘ └────────────────┘ └────────────────┘  │
│                                                                              │
├──────────────────────────────────────────────┬───────────────────────────────┤
│ Libraries                                    │ Android Runtime               │
│ ┌───────────────┐ ┌───────────────┐ ┌──────┐ │ ┌──────────────┐              │
│ │Surface Manager│ │Media Framework│ │SQLite│ │ │Core Libraries│              │
│ └───────────────┘ └───────────────┘ └──────┘ │ └──────────────┘              │
│                                              │                               │
│ ┌─────────┐ ┌────────┐ ┌──────┐              │ ┌──────────────────────┐      │
│ │OpenGL/ES│ │FreeType│ │WebKit│              │ │Dalvik Virtual Machine│      │
│ └─────────┘ └────────┘ └──────┘              │ └──────────────────────┘      │
│                                              │                               │
│ ┌───┐ ┌───┐ ┌────┐                           │                               │
│ │SGL│ │SSL│ │Libc│                           │                               │
│ └───┘ └───┘ └────┘                           │                               │
│                                              │                               │
├──────────────────────────────────────────────┴───────────────────────────────┤
│ Linux Kernel                                                                 │
│ ┌──────────────┐ ┌─────────────┐ ┌───────────────────┐ ┌───────────────────┐ │
│ │Display Driver│ │Camera Driver│ │Flash Memory Driver│ │Binder (IPC) Driver│ │
│ └──────────────┘ └─────────────┘ └───────────────────┘ └───────────────────┘ │
│                                                                              │
│ ┌─────────────┐ ┌───────────┐ ┌────────────┐ ┌────────────────┐              │
│ │Keypad Driver│ │WiFi Driver│ │Audio Driver│ │Power Management│              │
│ └─────────────┘ └───────────┘ └────────────┘ └────────────────┘              │
│                                                                              │
└──────────────────────────────────────────────────────────────────────────────┘
```

## 7. What is OHA?
- The OHA stands for Open Hardware Alliance.
- Google formed OHA in order to develop an open source software platform for use
  in mobile devices.
- The OHA is the group that is in charge of the Android smart phones OS.
- The primary objective of these companies is to developed open standards for
  mobile devices.
- The members of OHA include handset manufactures, chip makers,
  commercialization companies, software companies and mobile operators/users.

## 8. Explain the term Android ecosystem in detail.
- The learn about Android Operating system and develop Android application, it
  is very important for to understand the entire ecosystem of Android and the
  stakeholders of Android ecosystem.
- The four parts of Android Ecosystem:
  - **Google** - develops android.
  - **OEMs** (Original Equipment Manufactures) manufacture the hardware, and as
    well the custom application components.
  - **Application Development Companies** - are the major contactors to the
    ecosystem and employ developers, and also contract out the product
    development to services companies.
  - **Freelance Android Developers** have the skill-set to contribute to the
    ecosystem for android development, they are who create their own
    applications and publish them on Google Play Store.

## 9. What are the features of Android? Enlist any six of them.
- **Storage** - SQLite a lightweight relational database, is used for data
  storage purpose.
- **Multitasking** - Multitasking of application, with unique handling of
  memory allocation, will be existing.
- **Web Browser** - The web browser available in Android OS is based on the
  open source WebKit layout engine, attached with Chrome's V8 JavaScript engine.
- **Open Source** - Android is open-source operating system.
- **Accessibility** - Built in text to speech in Android OS is provided by Talk
  back for people with low or no vision.
- **Media Support** - Android supports the many media formats like:
  - WenM
  - H.263
  - H.254
  - AAC
  - HE-AAC
  - MPEG-4

## 10. Explain the term Android ecosystem in detail.
1. Android 13
2. Android 12
3. Android 11
4. Android 10
5. Android Pie
6. Android Oreo
7. Android Nougat
8. Android Marshmallow
9. Android Lollipop
10. Android KitKat
11. Android Jelly Bean
12. Android Sandwich
13. Android Honeycomb
14. Android Gingerbread
15. Android Froyo
16. Android Eclair
17. Android Donut
18. Android 1.5
19. Android 1.1
20. Android 1.0

## 11. Explain the need of Android.
- **Desktop** -Android-x86 is an open source project that ports Android to the
  x86 platform, allowing you to run it on your computer instead of an ARM-based
  phone or tablet.
- **Connectivity** - On one page/desktop we could be able to have four
  connecting device tool button like, Turn ON/OFF Bluetooth, Turn ON/OFF WiFi,
  Turn ON/OFF mobile network, Turn ON/OFF GPS and so on.
- **Browser** - The Android OS browser is one of the best browser on the mobile
  market. It generally loads pages faster then Safari or any other browser.
- **Open to carrier** - If we know Java programming language then we are open to
  Android world.
- **Market** - Android OS has an android market. The android apps are free and
  work as well.
- **Future** - The future mobile phones are basically going to be smartphones.
- **Notification** - Android phones have multi notification system.
- **Google Integration** - The android has inbuilt Google support. For example:
  Google Map, G-Mail etc.
- **Open Source** - The code of Android OS as well as the apps is available.
- **Endless Personalization** - The Android cell phone allow to configuration
  their mobile to look and behave exactly like they want.

## 14. Explain the following terms:

### (i) Android application
- The top layer of Android architecture is Applications.
- The native and third party applications like Contacts, Email, Music, Gallery,
  Clock, Games, etc.
- Whatever we will build those will be installed on this layer only.
- The application layer runs within the Android run time using the classes an
  services made available from the application framework.

### (ii) Android kernel
- Linux kernel is a bottom layer and heart of the android architecture.
- It exists at the root of android architecture and contains all the low-level
  device drivers fro the various hardware components of an Android device.
- Linux Kernel is responsible for device drivers, power management, memory
  management, device management and resource access.

## 16. Describe OHA with the Help of Digram.
```
┌─────────┐ ┌─────────┐ ┌────────────┐ ┌──────┐ ┌───────────────┐
│Software │ │Mobile   │ │Handset     │ │Chip  │ │Commercializton│
│Companies│ │Operators│ │Manufactures│ │Makers│ │Companies      │
└─────┬───┘ └─────┬───┘ └─────┬──────┘ └───┬──┘ └────────┬──────┘
      │           │           │            │             │
      └───────────┴───────────┼────────────┴─────────────┘
                              │
                       ┌──────┴───────┐
                       │Open Handset  │
                       │Alliance (OHA)│
                       └──────────────┘
```

## 17. Enlist and explain any 4 features of Android.
- **Storage** - SQLite a lightweight relational database, is used for data
  storage purpose.
- **Multitasking** - Multitasking of application, with unique handling of
  memory allocation, will be existing.
- **Web Browser** - The web browser available in Android OS is based on the
  open source WebKit layout engine, attached with Chrome's V8 JavaScript engine.
- **Open Source** - Android is open-source operating system.

## 19. Explain the concept of Android Ecosystem.
- The learn about Android Operating system and develop Android application, it
  is very important for to understand the entire ecosystem of Android and the
  stakeholders of Android ecosystem.
- The four parts of Android Ecosystem:
  - **Google** - develops android.
  - **OEMs** (Original Equipment Manufactures) manufacture the hardware, and as
    well the custom application components.
  - **Application Development Companies** - are the major contactors to the
    ecosystem and employ developers, and also contract out the product
    development to services companies.
  - **Freelance Android Developers** have the skill-set to contribute to the
    ecosystem for android development, they are who create their own
    applications and publish them on Google Play Store.

## 20. Explain any 4 advantages and disadvantages of Android OS.

### Advantages
- Supports 2D and 3D Graphics
- Supports Multiple Languages
- Faster Web Browser
- Video Calling
- Open Source Framework
- Uses of Tools are Very Simple
- Availability of Apps
- Great Social Networking Integration
- Better Notification System
- Update User Interface Design
- At a Time Applications
- Low Chance of Crashing
- Stability
- Multitasking

### Disadvantages
- Need Internet Connection
- Advertising
- Wasteful Battery
- Many Applications
- Slow Response
- Heat

## 21. Describe the concept of Anatomy of Android Application.
- `java` - This contains the `.java` source filed for our project. By default,
  includes an `MainActivity.java` source file having an activity class that runs
  when our app is launched using the app icon.
- `res/drawable-hdpi` - This is directory for drawable objects that are designed
  for high-density screens.
- `res/layout` - This is a directory for other various XML files that contain a
  collection of resources, such as strings and colours definitions.
- `AndroidManifest.xml` - This is the manifest file which describes the
  fundamental characteristics of the app and defines each of its components.
- `Build.gradle` - This is an auto generated file which contains
  `compileSdkVersion`, `buildToolsVersion`, `applicationId`, `minSdkVersion`,
  `targetSdkVersion`, `versionCode` and `versionName`.

## 22. Draw and explain the architecture of Android.
```
┌──────────────────────────────────────────────────────────────────────────────┐
│ Application                                                                  │
│ ┌────┐ ┌────────┐ ┌─────┐ ┌───────┐ ┌───┐                                    │
│ │Home│ │Contacts│ │Phone│ │Browser│ │***│                                    │
│ └────┘ └────────┘ └─────┘ └───────┘ └───┘                                    │
│                                                                              │
│ ┌────┐ ┌──────┐ ┌─────┐ ┌────────┐ ┌───┐                                     │
│ │SMS │ │E-Mail│ │Clock│ │Calander│ │***│                                     │
│ └────┘ └──────┘ └─────┘ └────────┘ └───┘                                     │
│                                                                              │
├──────────────────────────────────────────────────────────────────────────────┤
│                                                                              │
│ Application Framework                                                        │
│ ┌────────────────┐ ┌──────────────┐ ┌─────────────────┐ ┌───────────┐        │
│ │Activity Manager│ │Window Manager│ │Content Providers│ │View System│        │
│ └────────────────┘ └──────────────┘ └─────────────────┘ └───────────┘        │
│                                                                              │
│ ┌───────────────┐ ┌─────────────────┐ ┌────────────────┐ ┌────────────────┐  │
│ │Package Manager│ │Telephony Manager│ │Resource Manager│ │Location Manager│  │
│ └───────────────┘ └─────────────────┘ └────────────────┘ └────────────────┘  │
│                                                                              │
├──────────────────────────────────────────────┬───────────────────────────────┤
│ Libraries                                    │ Android Runtime               │
│ ┌───────────────┐ ┌───────────────┐ ┌──────┐ │ ┌──────────────┐              │
│ │Surface Manager│ │Media Framework│ │SQLite│ │ │Core Libraries│              │
│ └───────────────┘ └───────────────┘ └──────┘ │ └──────────────┘              │
│                                              │                               │
│ ┌─────────┐ ┌────────┐ ┌──────┐              │ ┌──────────────────────┐      │
│ │OpenGL/ES│ │FreeType│ │WebKit│              │ │Dalvik Virtual Machine│      │
│ └─────────┘ └────────┘ └──────┘              │ └──────────────────────┘      │
│                                              │                               │
│ ┌───┐ ┌───┐ ┌────┐                           │                               │
│ │SGL│ │SSL│ │Libc│                           │                               │
│ └───┘ └───┘ └────┘                           │                               │
│                                              │                               │
├──────────────────────────────────────────────┴───────────────────────────────┤
│ Linux Kernel                                                                 │
│ ┌──────────────┐ ┌─────────────┐ ┌───────────────────┐ ┌───────────────────┐ │
│ │Display Driver│ │Camera Driver│ │Flash Memory Driver│ │Binder (IPC) Driver│ │
│ └──────────────┘ └─────────────┘ └───────────────────┘ └───────────────────┘ │
│                                                                              │
│ ┌─────────────┐ ┌───────────┐ ┌────────────┐ ┌────────────────┐              │
│ │Keypad Driver│ │WiFi Driver│ │Audio Driver│ │Power Management│              │
│ └─────────────┘ └───────────┘ └────────────┘ └────────────────┘              │
│                                                                              │
└──────────────────────────────────────────────────────────────────────────────┘
```

- The main components of Android architecture are:
  - Application
  - Android Framework
  - Android Runtime
  - Platform Libraries
  - Linux Kernel

### Application
- The top layer of Android architecture is Applications.
- The native and third party applications like Contacts, Email, Music, Gallery,
  Clock, Games, etc.
- Whatever we will build those will be installed on this layer only.
- The application layer runs within the Android run time using the classes an
  services made available from the application framework.

### Application Framework
- The Application framework provides the classes used to create an Android
  application.
- It also provides a generic abstraction for hardware access and manages the
  user interface and application resources.
- It basically provides the services through which we can create the particular
  class and make that class helpful for Application creation.
- The application framework includes services like telephony service, location
  services, notification manager, NFC service, View system, etc.
- Which can use for application development as per our requirements.

### Android Runtime
- Android Runtime environment is an important part of Android rather then an
  internal part and it contains a components like core libraries and the Dalvik
  Virtual Machine(DVM).
- The Android run time is the engine that powers our applications along with the
  libraries and it forms the basis for the application framework.
  - **Dalvik Virtual Machine(DVM)** - is register-based virtual machine like
    Java Virtual Machine(JVM). It is specially designed and optimized for
    Android to ensure that a device can run multiple instance efficiently.
  - The **core libraries** in Android runtime will enable is to implement an
    Android applications using standard Java programming language.

### Platform Libraries
- The Platform Libraries includes various C/C++ core libraries and Java based
  libraries such as SSL, libc,Graphics, SQLite, WebKit, Media, Surface Manger,
  OpenGL etc.

### Linux Kernel
- Linux kernel is a bottom layer and heart of the android architecture.
- It exists at the root of android architecture and contains all the low-level
  device drivers fro the various hardware components of an Android device.
- Linux Kernel is responsible for device drivers, power management, memory
  management, device management and resource access.

## Android Application Components
- **Activates** - They dictate the UI and handle the user interaction to the
  smart phone screen.
- **Services** - They handle background processing associated with an
  application.
- **Broadcast Receivers** - They handle communication between Android OS and
  applications.
- **Content Provides** - They handle data and database management issues.
- **Fragments** - Represents a portion of user interface in an Activity.
- **Views** - UI elements that are drawn on-screen including buttons, lists
  forms etc.
- **Layouts** - View hierarchies that control screen format and appearance of
  the views.
- **Intents** -Messages wiring components together.
- **Resources** - External elements, such as strings, constants and drawable
  pictures.
- **Manifest** - Configuration file for the application.

# 2. Installing and Configuration of Android

## 1. What is OS? Explain OS requirements for Android.
- To develop an Android program, the necessary supporting OS used in a computer
  can be follows:
  - Windows XP, Vista, 7, 8
  - Mac OS x
  - Linux

## 2. What is JDK?
- An Android operating system program is developed in Java programming language
  we have to install Java Development Kit (JDK) in computer.

## 3. What is SDK?
- API libraries, and emulator, documentation, sample code, developer tools, and
  tutorials which help us to build, test and debug apps form Android.
- Android SDK is made up of two main parts namely, the tools and the packages.
- Some Android SDK, features include:
  - No licensing, distribution, or development fees.
  - WiFi hardware access
  - IPC message passing
  - Shared data stores
  - An integrated open source WebKit-based browser.
  - Full support for application that integrate Map controls as part of their
    interface.
  - Peer-to-Peer(P2P) support using Google Talk.

## 5. Describe DVM with diagram.
```
                                 ┌───────────┐
    ┌───────────┬──────────┬─────┤Android SDK├──────────┬───────────┐
    │           │          │     └─────┬─────┘          │           │
    │           │          │           │                │           │
┌───┴────┐ ┌────┴────┐ ┌───┴────┐ ┌────┴────────┐ ┌─────┴─────┐ ┌───┴─────┐
│Debugger│ │Libraries│ │Emulator│ │Documentation│ │Sample Code│ │Tutorials│
└────────┘ └─────────┘ └────────┘ └─────────────┘ └───────────┘ └─────────┘
```

## What is JVM? Compare JVM and DVM?
- Dalvik is register-based Virtual Machine(VM) that's been optimized to ensure
  that a device can run multiple instance efficiently.
- Dalvik VM takes the generated Java class files and combines them into one or
  more Dalvik Executable (`.dev`) files.
- Android OS uses the Dalvik Virtual Machine (DVM) with just-during-time
  compilation to run Dalvik bytecode, with is frequently translated from
  Java bytecode.
- Google has also fine-tuned the collection in the Dalvik VM, but it has chosen
  to remove Just-In-Time (JIT) compiler, in early releases.
- Dalvik VM use a different kind of assembly-code generation, in which it uses
  registers as the primary units of data storage instead of the stack.

| JVM                                                              | DVM                                                                              |
|------------------------------------------------------------------|----------------------------------------------------------------------------------|
| JVM supports multiple OS                                         | DVM supports only Android OS                                                     |
| JVM forms separate classes in separate `.class` byte code files. | DVM forms multiple class `.dex` byte code file.                                  |
| It is based on stack based VM architecture.                      | It is based on register based VM architecture.                                   |
| JVM runs on more memory.                                         | DVM runs on less memory.                                                         |
| The executable format of JVM is JAR.                             | The executable format of DVM is APK.                                             |
| JVM has different content pools.                                 | DVM has common constant pool.                                                    |
| It runs `.class` byte code directly.                             | The `.class` byte codes are optimized to `.odex` format before executing in DVM. |

## 7. Explain the term emulator in detail.
- Android Emulator is responsible for running, debugging and testing the
  Android application.
- The Android Emulator mimics all the hardware and software features of typical
  mobile devices except that it can't place annual phone calls.

## 8. What is ADT? Describe in detail.
- Android Development Tool (ADT) in Android is a plugin for the Eclipse IDE
  which provides a suitable environment to develop an Android application where
  creation, compilation and debugging are possible.

## 10. Differentiate between JDK and SDK.
| SDK                                                                                                      | JDK                                                                                            |
|----------------------------------------------------------------------------------------------------------|------------------------------------------------------------------------------------------------|
| Software development kit.                                                                                | Java development kit.                                                                          |
| It is a set of software or development tools used to create an application or a program on any platform. | It is a set of development tools that allows a programmer write a program using Java language. |
| Libraries, sample code, supporting documentation etc.                                                    | Consists of the programming tool's selection components.                                       |
| Android SDK                                                                                              | Java 8, Java 11, etc.                                                                          |

## 11. Define the terms: JDK, SDK, AVD, ADT
- **JDK** - An Android operating system program is developed in Java programming
  language we have to install Java Development Kit (JDK) in computer.
- **SDK** - API libraries, and emulator, documentation, sample code, developer
  tools, and tutorials which help us to build, test and debug apps form Android.
- **AVD** - And Android Virtual Device (AVD) represents a device configuration.
- **ADT** - Android Development Tool (ADT) in Android is a plugin for the
  Eclipse IDE which provides a suitable environment to develop an Android
  application where creation, compilation and debugging are possible.

## Explain AVD in detail.
- And Android Virtual Device(AVD) represents a device configuration.
- An AVD is a configuration that defines the characteristics of an Android phone
  , tablet, Wear OS, Android TV, or Automotive OS device that we want to
  simulate in the Android Emulator.
- An AVD contains:
  - **Hardware profile** - The hardware profile defines the characteristics of a device as shipped from the factory.
  - **System image** - A system image labeled with Google APIs includes access to Google Play services.
  - **Storage area** - The AVD has dedicated storage area on our development
    machine.
  - **Skin** - An emulator skin specifics the appearance of a device.


## 18. Differentiate between JVM and DVM.
| JVM                                                              | DVM                                                                              |
|------------------------------------------------------------------|----------------------------------------------------------------------------------|
| JVM supports multiple OS                                         | DVM supports only Android OS                                                     |
| JVM forms separate classes in separate `.class` byte code files. | DVM forms multiple class `.dex` byte code file.                                  |
| It is based on stack based VM architecture.                      | It is based on register based VM architecture.                                   |
| JVM runs on more memory.                                         | DVM runs on less memory.                                                         |
| The executable format of JVM is JAR.                             | The executable format of DVM is APK.                                             |
| JVM has different content pools.                                 | DVM has common constant pool.                                                    |
| It runs `.class` byte code directly.                             | The `.class` byte codes are optimized to `.odex` format before executing in DVM. |

# 3. UI Components and Layouts

## 2. Explain screen elements for Android.
## 3. What is directory?
## 4. Describe directory structure in detail.

## 5. Explain the term fundamentals of UI design in detail.
- Every item in a User Interfaces (UI) is a subclass of the Android View class
  whic is present inside the package (android.view).
- The android SDK provides a set of pre-built views that can be used to
  construct the UI.

## 6. What is meant by layout?
A layout defines the stucture for User Interface in the application. There are
number of Layouts provided by Android which we will use in almost all the
Android applicatoins to provide different view, look and feel.

## 7. Explain Linearlayout with example.
- Android LinearLayout is View group that aligns all children in either
  vertically or horizontally.
- Vertically or Horizontally direction depends on attribute
  `android:orientation` LinearLayout is simple and easy to use, it creates a
  scroll bar if the length of window exceeds the length of the screen.
- Attributes of LinearLayout: `id`, `orientation`, `layout_height`, `layout_weight`, `gravity`,
  `weight_sum`, `divider`.
- Example:
  ```xml
  <?xml version="1.0" encoding="utf-8" ?>
  <LinearLayout
    xmlns:android="https://schemas.android.com/apk/res/android"
    android:layout_height="match_parent"
    android:layout_width="match_parent"
    android:orientation="vertical"/>
    <Button
      android:id="@id/buttons"
      android:layout_width="wrap_content"
      android:layout_height="wrap_content"
      android:text="Button" />
  </LinearLayout>
  ```

## 8. Describe FrameLayout with example.

## 9. Explain the following terms:
### (i) TableLayout
### (ii) AbsoluteLayout

## 10. Define the term Layout.
A layout defines the stucture for User Interface in the application. There are
number of Layouts provided by Android which we will use in almost all the
Android applicatoins to provide different view, look and feel.

## 11. Write down the control flow of an Android application step by step.
## 13. List the different components of a screen.
## 14. Explain the term fundamentals of UI design in detail.
## 15. List various layouts used in Android UI design.

# 4. Designing User Interface with View

## 1. What is UI?
- User interface basic building block are View class.
- View is superclass for all the UI components.
- Input controls are interactive components in the app's User Interface(UI).

## 2. Enlist elements of UI.
- **View** - View is superclass for all UI compnents.
- **TextView** - displays text to the user and optionally allows them to edit
  it.
- **EditText** - An editable text entry box that accepts multiline entry.
- **Button** -whcih can be pressed, or clicked, by the user to perform an
  action.
- **ImageButton** - shows button with an image that can be pressed or clicked by
  the user.
- **ToggleButton** - is used to display checked andunchecked state of a button.
- **RadioButton** - A radiobutton has two states, either checked or unchecked.
- **RadioGroup** - RadioButton are maninly used together in RadioGroup.
- **CheckBox** - is an On/Off switch that can be toggled by the user.
- **ProgressBar** - is used to show the progress of an operatin.
- **ListView** - dispalys a vertically-scrollable collection of views, where
  each view is positioned immediately below the previous viewin the list.
- **GridView** - shows items in two-dimensional scrolling grid.
- **ImageView** - shows image with help `android.widget.imageView` class.
- **ScrollView** - is a view group that is used to make vertically scrolllable
  views.

## 3. What is TextView? How to create it? Explain with example.
- **TextView** - displays text to the user and optionally allows them to edit
- A standard read-only text label that supports string formatting, multiline
  display and automatic word wrapping.
- Attributes of TextView:
  - **alpha** - This property of the view as value between 0 and 1.
  - **auto-link** - controls whether links such as urls and email addresses.
  - **gravity** - attribute is optional attribute which is used to control the
    alignment of the text left, right, center, top, bottom, center_vertical,
    center_horizontal etc.
  - **text** - is used to set the text in TextView.
  - **textColor** - is used to set the text color.
  - **textSize** - is used to set the size of text.
  - **textStyle** - is used to set the text style.
  - **background** - is used to set the background.
  - **padding** - is used to set hte padding from left, right, top to bottom.
- Example:
  ```xml
  <?xml version="1.0" encoding="utf-8"?>
  <LinearLayout
    xmlns:android="https://scemas.android.com/res/apk/android"
    android:orentation="vertical"
    android:layout_height="match_parent"
    android:layout_width="match_parent">
    <TextView
      android:layout_height="wrap_content"
      android:layout_width="wrap_content"
      android:text="Hello World"
      android:gravity="right"
      android:textColor="#2353"
      android:textSize="10px"
      android:background="#000"
      android:padding="10px"/>
  </LinearLayout>
  ```

## 4. Explain the term Button with example.
- **Button** -whcih can be pressed, or clicked, by the user to perform an
  action.
- There are different types of buttons used in android such as CompoundButton,
  ToggleButton, RadioButton.
- Button is superclass of TextView class and compound button is the subclass of
  button class.
- Properties of Button:
  - **auto-link** - controls whether links such as urls and email addresses are
    automatically found and converted toclickable links.
  - **clickable** - defines whether this viewreacts to click events.
  - **id** - is an attribute used to uniquely identify a text button.
  - **gravity** - is an optional attribute which is used to control the
    alignement of text like left, right, top, bottom, center_vertical,
    center_horizontal etc.
  - **text** - is used to set the text in TextView.
  - **textColor** - is used to set the text color.
  - **textSize** - is used to set the size of text.
  - **textStyle** - is used to set the text style.
  - **background** - is used to set the background.
  - **padding** - is used to set hte padding from left, right, top to bottom.
  - **drawableButton**, **drawableTop**, **drawableRight**, **drawableLeft** -
    we draw drawable to the left, right, top or bottom of text.

## 5. What is ImageButton? How to create it? Explain with example.
- **ImageButton** - shows button with an image that can be pressed or clicked by
  the user.
- Properties of ImageButton:
  - **id** - is an attribute used to uniquely identify a text button.
  - **src** - is used to set a source file of image or we can say image in the
    image button to make layout look attractive.
  - **background** - is used to set the background.
  - **padding** is used to set padding left, right, top or bottom
- Example:
  ```xml
  <?xml version="1.0" encoding="utf-8"?>
  <LinearLayout
    xmlns:android="https://schemas.android.com/apk/res/android"
    android:layout_width="match_parent"
    android:layout_height="match_parent"
    android:orientation="vertical"/>
    <ImageButton
      android:id="@+id/imageButton"
      android:src="@drawable/button"
      android:layout_height="wrap_content"
      android:layout_width="wrap_content"/>
  </LinearLayout>
  ```

## 6. Describe the following UI elements with example.

### (i) ListView
- **ListView** - dispalys a vertically-scrollable collection of views, where
  each view is positioned immediately below the previous viewin the list.
- Properties of ListView:
  - **id** - is an attribute used to uniquely identify a text button.
  - **divider** - This is a drawable or color draw between different list items.
  - **dividerHeight** - This specify the height of divider between list items.
  - **listSelector** - is used to set the selector of the listView.
- Example:
  ```xml
  <?xml version="1.0" endcoding="utf-8"?>
  <LinearLayout
    xmlns:android="https://schemas.android.com/apk/res/android"
    android:layout_width="match_parent"
    android:layout_height="match_parent"
    android:orientation="vertical">
    <ListView
      android:id="@+id/listView"
      android:layout_width="wrap_content"
      android:layout_height="wrap_content"
      android:divider="#000"
      android:dividerHeight="1dp"/>
  </LinearLayout>
  ```
### (ii) ScrollView
- **ScrollView** - is a view group that is used to make vertically scrolllable
- It is a `FrameLayout` which put one child in it containg the whole contents to
  scroll.
- This is useful when we have too much to fit onto a single screen.
- Example:
  ```xml
  <?xml version="1.0" encoding="utf-8"?>
  <androidx.constraintlayout.widget.ConstraintLayout
    xmlns:android="https://schemas.android.com/apk/res/android"
    xmlns:app="https://schemas.android.com/apk/res-auto"
    xmlns:app="https://schemas.android.com/tools"
    android:layout_width="match_parent"
    android:layout_height="match_parent"
    android:tools=".MainActivity">
    <ScrollView
      android:layout_width="match_parent"
      android:layout_height="match_parent">
      <TextView
        android:id="@+id/textView"
        android:layout_height="wrap_content"
        android:layout_width="wrap_content"
        android:text="Hello World"/>
    </ScrollView>
  </androidx.constraintlayout.widget.ConstraintLayout>
  ```

### (iii) GridView
- A GridView is type of AdapterView that dispalyas items in two-dimensional
  scrolling grid.
- Example:
  ```xml
  <?xml version="1.0" encoding="utf-8"?>
  <androidx.contraintlayout.widget.ContraintLayout
    xmlns:android="https://schemas.android.com/apk/res/android"
    xmlns:tools="https://schemas.android.com/tools"
    android:tools=".MainActivity"
    android:layout_width="match_parent"
    android:layout_width="mathc_parent">
    <gridview
      android:id="@+id/idgv"
      android:layout_height="wrap_content"
      android:layout_widht="wrap_content"
      android:numcoumns="2"
      android:verticalspacing="6dp"/>
  </androidx.contraintlayout.widget.contraintlayout>
  ```

### (iv) imageview.
- **imageview** - shows image with help `android.widget.imageview` class.
```xml
<?xml version="1.0" encoding="utf-8"?>
<androidx.contraintlayout.widget.contraintlayout
  xmlns:android="https://schemas.android.com/apk/res/android"
  xmlns:app="https://schemas.android.com/apk/res-auto"
  xmlns:tools="https://schemas.android.com/tools"
  android:tools=".mainactivity"
  android:layout_height="match_parent"
  android:layout_width="match_parent">
  <imageview
    android:id="@+id/imageview"
    android:layout_width="wrap_content"
    android:layout_height="wrap_content"
    android:src="@drawable/image"/>
</androidx.contraintlayout.widget.contraintlayout>
```

## 7. explain radiogroup with example.
- **radiobutton** - a radiobutton has two states, either checked or unchecked.
- **radiogroup** - radiobutton are maninly used together in radiogroup.
- Properties of radiobutton:
  - **id** - is an attribute used to uniquely identify a text button.
  - **checked** - in radio button is used to set the current state of radio
    button.
  - **gravity** - is an optional attribute which is used to control the
    alignement of text like left, right, top, bottom, center_vertical,
    center_horizontal etc.
  - **text** - is used to set the text in TextView.
  - **textColor** - is used to set the text color.
  - **textSize** - is used to set the size of text.
  - **textStyle** - is used to set the text style.
  - **background** - is used to set the background.
  - **padding** - is used to set hte padding from left, right, top to bottom.
  - **drawableButton**, **drawableTop**, **drawableRight**, **drawableLeft** -
    we draw drawable to the left, right, top or bottom of text.
- Example:
  ```xml
  <?xml version="1.0" encoding="utf-8"?>
  <LinearLayout
    xmlns:android="https://schemas.android.com/apk/res/android"
    xmlns:tools="https://schemas.android.com/tools"
    android:tools=".MainActivity"
    android:layout_width="match_parent"
    android:layout_height="match_parent"
    android:orientation="vertical">
    <RadioGroup
      android:layout_width="wrap_content"
      android:layout_height="wrap_content"
      android:id="@+id/radioGendar">
      <RadioButton
        android:id="@+id/radioMan"
        android:text="Man"
        android:layout_height="wrap_content"
        android:layout_width="wrap_content"
        android:checked="true"/>
      <RadioButton
        android:id="@+id/radioGirl"
        android:text="Women"
        android:layout_height="wrap_content"
        android:layout_width="wrap_content"
        android:checked="false"/>
    <RadioGroup>
  </LinearLayout>
  ```

## 8. With the help of example describe ToggleButton.
- **ToggleButton** - is used to display checked and unchecked state of a button.
- It is subclass of compound Button.
- Properties of radiobutton:
  - **id** - is an attribute used to uniquely identify a text button.
  - **checked** - in radio button is used to set the current state of radio
    button.
  - **gravity** - is an optional attribute which is used to control the
    alignement of text like left, right, top, bottom, center_vertical,
    center_horizontal etc.
  - **textOn** and **textOff** - is used to set the text when toggle button is
    in checked state.
  - **textColor** - is used to set the text color.
  - **textSize** - is used to set the size of text.
  - **textStyle** - is used to set the text style.
  - **background** - is used to set the background.
  - **padding** - is used to set hte padding from left, right, top to bottom.
  - **drawableButton**, **drawableTop**, **drawableRight**, **drawableLeft** -
    we draw drawable to the left, right, top or bottom of text.
- Example:
  ```xml
  <?xml version="1.0" encoding="utf-8"?>
  <androidx.contraintlayout.widget.ContraintLayout
    xmlns:android="https://schemas.android.com/apk/res/android"
    xmlns:app="https://schemas.android.com/apk/res-auto"
    xmlns:tools="https://schemas.android.com/tools"
    android:tools=".MainActivity"
    android:layout_width="match_parent"
    android:layout_height="match_parent">
    <ToggleButton
      android:id="@+id/simpleToggleButton"
      android:layout_width="wrap_content"
      android:layout_height="wrap_content"
      android:layout_gravity="center_horizontal"
      android:checked="false"
      android:textOn="On"
      android:textOff="Off"/>
  </android.contraintlayout.wiget.ContraintLayout>
  ```

## 10. How to custom toast alert?
- Toast is used to display information for a period of time.
- It contains a message to be displayed quickly and disappears after specified
  period of time.
- It does not block the user interaction.
- Tost are not clickable.
- Exmaple:
  ```java
  Toast.makeText(getApplicationContext(), "Simple Toast in Android",
    Toast.LENGTH_LONG);
  ```

## 11. Describe Date and Time picker with example.

### DatePicker
- DatePicker is a widget used to select a date.
- It allows to select date by date, month and year in our custom UI.
- If we need to show this view as a dialog then wehave to use a DatePickerDialog
  class.
- Example:
  ```xml
  <?xml version="1.0" encoding="utf-8"?>
  <LinearLayout
    xmlns:android="https://schemas.android.com/apk/res/android"
    xmlns:app="https://schemas.android.com/apk/res-auto"
    xmlns:tools="https://schemas.android.com/tools"
    android:tools=".MainActivity"
    android:orentation="vertical"
    android:layout_height="match_parent"
    android:layout_width="mathc_parent"/>
    <DatePicker
      android:id="@+id/datepicker"
      android:layout_width="wrap_content"
      android:layout_height="wrap_content"
      android:datePickerMode="spinner"/>
  </LinearLayout>
  ```
- Method of DatePicker:
  - `setSpinnersShow(boolen show)` - This method is used to set whether the
    sinner of the TimePicker in shown or not.
  - `getDayOfMonth()` - This method is used to get selected day of the month.
  - `getMonth()` - This method is used to get the selected month from a date
    picker.
  - `getYear()` - This method is used to get the selected year from a date
    picker.
  - `getFirstDayOfWeek()` - This method is used to get the first day of the
    week.

- Attributes of DatePicker:
  - **id** - is an attribute used to uniquely identify a text button.
  - **datePickerMode** - This attribute is used to set the DatePicker.

### TimePicker
- Is a widget used for selecting the time of the day in either AM/PM mode or 24
  hours mode.
- The displayed time consist of hours, minutes and clock format.
- Method of TimePicer:
  - `setCurrentHour(integer currentHour)` - This method is used to set the
    current hours in a TimePicker.
  - `setHour(Integer hour)` - This method is used to set the current hours in
    TimePicker.
  - `setCurrentMinute(Integer currentMinute)` - This method is used to set the
    current minutes in a time.
  - `setMinute(Integer minute)` - This method is used to set the current minute
    in time.
  - `setIs24HourView(Boolean is24HourView)` - This method is used to set the
    mode of Time picker either 24 hours mode or AM/PM mode.
  - `is24HourView()` - This method is used to check the current mode of the
    time picker.
  - `setOnTimeChangedListenar()` - This method is used to set the callback that
    indicates the time has been adjusted by the user.
- Attributes of TimePicker:
  - `timePickerMode` - The time picker mode is attribute of time picker used to
    set the mode either spinner or clock.

## 12. What is progress bar? How to create it?
- ProgressBar is used to show the progress of an operation.
- ProgressBar is a visual indicator of progress in a number of operation.
- Attributes of DatePicker:
  - **id** - is an attribute used to uniquely identify a text button.
  - **max** - is an attribute used in android to define maximum value of the
    progress can take.
  - **progress** - is an attribute used in android to define the default
    progress value between 0 and Max.
  - **progressBrawable** - is an attribute used to set the custom drawable for
    the progress mode.
- Example:
  ```xml
  <?xml version="1.0" encoding="utf-8"?>
  <RelativeLayout
    xmlns:android="https://schemas.android.com/apk/res/android"
    xmlns:tools="https://schemas.android.com/tools"
    xmlns:app="https://schemas.android.com/apk/res-auto"
    android:layout_width="match_parent"
    android:layout_height="mathc_parent"/>
    <ProgressBar
      android:id="@+id/progressBar"
      android:layout_width="wrap_content"
      android:layout_height="wrap_content"
      android:max="100"
      android:progress="0"
      android:progressDrawable="@drawable/progress"/>
  </RelativeLayout>
  ```

## 14. Describe the following with example:

### (ii) CheckBox.
- Is an On/Off switch that can be toggled by the user.
- A two-state represented by a checked or unchecked box.
- Example:
  ```xml
  <?xml version="1.0" encoding="utf-8"?>
  <RelativeLayout
    xmlns:android="https://schemas.android.com/apk/res/android"
    xmlns:tools="https://schemas.android.com/tools"
    xmlns:app="https://schemas.android.com/apk/res-auto"
    android:layout_width="match_parent"
    android:layout_height="mathc_parent"/>
    <CheckBox
      android:id="@+id/check1"
      android:layout_width="wrap_content"
      android:layout_height="wrap_content"
      android:text="Android"
      android:checked="true"/>
    <CheckBox
      android:id="@+id/check1"
      android:layout_width="wrap_content"
      android:layout_height="wrap_content"
      android:text="ISO"
      android:checked="true"/>
    <CheckBox
      android:id="@+id/check1"
      android:layout_width="wrap_content"
      android:layout_height="wrap_content"
      android:text="KaiOS"
      android:checked="true"/>
  </RelativeLayout>
  ```

## 15. Draw the hierarchy of designing User Interface (UI) with View.
```
┌────┐
│View├───────────────────────┐
└─┬──┤                       │
  │  └────────┐              │
  │           │              │
 ┌┴───────┐ ┌─┴───────┐ ┌────┴────┐
 │TextView│ │ImageView│ │ViewGroup│
 └───┬─┬──┘ └────┬────┘ └─────────┘
     │ │         │
     │ └──────┐  └──────┐
     │        │         │
 ┌───┴────┐ ┌─┴────┐ ┌──┴────────┐
 │EditText│ │Button│ │ImageButton│
 └────────┘ └┬──┬─┬┘ └───────────┘
             │  │ │
    ┌────────┘  │ └──────────┐
    │           │            │
 ┌──┴─────┐ ┌───┴───────┐ ┌──┴─────────┐
 │CheckBox│ │RadioButton│ │ToggleButton│
 └────────┘ └───────────┘ └────────────┘
```

## 16. Describe the term "edit text" with example.
- An editable text enty box that accepts multiline entry, word wrapping and
  hint text.
- A EditText is an overlay over TextView that configures itself to be
  editable.
- Example:
  ```xml
  <?xml version="1.0" encoding="utf-8"?>
  <RelativeLayout
    xmlns:android="https://schemas.android.com/apk/res/android"
    xmlns:tools="https://scheams.android.com/tools"
    xmlns:app="https://scheams.android.com/apk/res-auto"
    android:layout_width="match_parent"
    android:layout_height="match_parent"
    android:tools=".MainActivity">
    <EditText
      android:id="@+id/editIt"
      android:layout_width="wrap_content"
      android:layout_height="wrap_content"
      android:hint="Name:"
      android:selectAllOnFocus="true"
      android:inputType="textPersonName"/>
  </RelativeLayout>
  ```

# 5. Activity & Multimedia with Database

## Activity
- An activity represents a single screen with user interface just like window
  or frame of Java.
- Android activity is the subclass of ContextThemeWrapper class.
- In C, C++ or Java programming language you must have seen that your program
  stats from `main()` function.
- Android sytem iniiates its program with an Activity starting with a call
  `onCreate()` callback method.

## Draw the activity life cycle.
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
## Explain activity lifecycle?
- The android Activity is the subclass of ContextThemeWrapper class.
- An activity is the single screen in android. It is like window or frame of
  Java.
- By the help of activity, you can place all your UI components or widgets in a
  single screen.
- **7 lifecycle methods of android activity.**
 - **onCreate** - called when activity is first created.
 - **onStart** - called when activity is becoming visible to the user.
 - **onResume** - called when activity will start interacting with the user.
 - **onPause** - called when activity is not visible to the user.
 - **onStop** - called when activity is no longer visible to the user.
 - **onRestart** - called after your activity is stopped, prior to start.
 - **onDestroy** - called before the activity is destroyed.

## What are intents(`Implict` and `explicit` intent)?
- Android Intent is the message that is passed between components such as
  activities, content providers, broadcast receivers, services etc.
- It is generally used with `startActivity()` method to invoke activity,
  broadcast receivers etc.  The dictionary meaning of intent is intention or
  purpose.
- So, it can be described as the intention to do action.
- The LabeledIntent is the subclass of android.content.Intent class.
- Android intents are mainly used to:
  - Start the service
  - Launch an activity
  - Display a web page
  - Display a list of contacts
  - Broadcast a message
  - Dial a phone call etc

### Implicit intent
The implicit intent is the intent where instead of defining the exact
components, you define the action that you want to perform for different
activities.

### Explicit intent
An explicit intent is an intent where you explicitly define the component that
needs to be called by Android System. An explicit intent is one that you use to
launch a specific app component, such s a particular activity or service in
your app.

## Explain content provider?
- Android system allows the content provider to store the application data in
  several ways. Users can manage to store the application data like
  - Images
  - Audio
  - Videos
  - Personal contact information by storing them in:
    - SQLite Database
    - Files
    - Network.
- In order to share the data, content providers have certain permissions that
  are used to grant or restrict the rights to other applications to interfere
  with the data.

## List sensors in Android and explain anyone in detail.
The Android platform supports following three broad categories of sensors:
- Motion Sensors
- Environmetal Sensors
- Position sensors

### Motion Sensors:
- A motion sensor (or motion detector) is an electronic device that is designed
  to detect and measure movement.
- Motion sensors are used primarily in home and business security systems.
- These sensors measure acceleration forces and rotational forces along three
  axes.
- This category includes accelerometers, gravity sensors, gyroscopes, and
  rotational vector sensors.

### Position Sensors
These are used to measure the physical position of device.

### Environmental Sensors
These are used to measure the environmental changes such as temperature, humidity
etc

## Define Services in Android OS.
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

## CONTENT URI
- Content URI(Uniform Resource Identifier) is the key concept of Content
providers.
- To access the data from a content provider, URI is used as a query string.
- Structure of a Content URI:
  - content:// – Mandatory part of the URI as it represents that the given URI
    is a Content URI.
  - authority – Signifies the name of the content provider like contacts,
    browser, etc. This part must be unique for every content provider.
  - optionalPath – Specifies the type of data provided by the content provider.
    It is essential as this part helps content providers to support different
    types of data that are not related to each other like audio and video files.
  - optionalID – It is a numeric value that is used when there is a need to
    access a particular record.

## WORKING OF THE CONTENT PROVIDER
- UI components of android applications like Activity and Fragments use an object
  CursorLoader to send query requests to ContentResolver.
- The ContentResolver object sends requests (like create, read, update, and
  delete) to the ContentProvider as a client.
- After receiving a request, ContentProvider process it and returns the desired
  result.

## CREATE CONTENT PROVIDER
This involves number of simple steps to create your own content provider.
- First of all you need to create a Content Provider class that extends the
  ContentProviderbaseclass.
- Second, you need to define your content provider URI address which will be
  used to access the content.
- Next you will need to create your own database to keep the content.
- Next you will have to implement Content Provider queries to perform different
  database specific operations.
- Finally register your Content Provider in your activity file using <provider>
  tag.
- Methods which you need to override in Content Provider class:
  1. onCreate() This method is called when the provider is started.
  2. query() This method receives a request from a client. The result
     is returned as a Cursor object.
  3. insert()This method inserts a new record into the content
     provider.
  4. delete() This method deletes an existing record from the content
     provider.
  5. update() This method updates an existing record from the
     content provider.
  6. getType() This method returns the MIME type of the data at the
     given URI.

## FRAGMENT
- A Fragment is a piece of an activity which enable more modular activity
  design.
- You create fragments by extending Fragment class and You can insert a fragment
  into your activity layout by declaring the fragment in the activity's layout
  file, as a <fragment> element.
- A fragment has its own layout and its own behaviour with its own life cycle
  callbacks.
- You can add or remove fragments in an activity while the activity is running.
- You can combine multiple fragments in a single activity to build a multi-pane
  UI.
- A fragment can be used in multiple activities.

## ANDROID FRAGMENT LIFECYCLE METHODS
| Method                                          | Description                                                                                                    |
|-------------------------------------------------|----------------------------------------------------------------------------------------------------------------|
| onAttach(Activity)                              | it is called only once when it is attached with activity.                                                      |
| onCreate(Bundle)                                | It is used to initialize the fragment.                                                                         |
| onCreateView(LayoutInflater, ViewGroup, Bundle) | creates and returns view hierarchy.                                                                            |
| onActivityCreated(Bundle)                       | It is invoked after the completion of onCreate() method.                                                       |
| onViewStateRestored(Bundle)                     | It provides information to the fragment that all the saved state of fragment view hierarchy has been restored. |
| onStart()                                       | makes the fragment visible.                                                                                    |
| onResume()                                      | makes the fragment interactive.                                                                                |
| onPause()                                       | is called when fragment is no longer interactive.                                                              |
| onStop()                                        | is called when fragment is no longer visible.                                                                  |
| onDestroyView()                                 | allows the fragment to clean up resources.                                                                     |
| onDestroy()                                     | allows the fragment to do final clean up of fragment state.                                                    |
| onDetach()                                      | It is called immediately prior to the fragment no longer being associated with its activity.                   |

## MEDIAPLAYER CLASS
- We can play and control the audio files in android by the help of MediaPlayer
  class.
- The android.media.MediaPlayer class is used to control the audio or video
  files.
|                                                Method & description                                                |
|:------------------------------------------------------------------------------------------------------------------:|
| `isPlaying()` This method just returns true/false indicating the song is playing or not                            |
| `seekTo(position)` This method takes an integer, and move song to that particular position millisecond             |
| `getCurrentPosition()` This method returns the current position of song in milliseconds                            |
| `getDuration()` This method returns the total time duration of song in milliseconds                                |
| `reset()` This method resets the media player                                                                      |
| `release()` This method releases any resource attached with MediaPlayer object                                     |
| `setVolume(float leftVolume, float rightVolume)` This method sets the up down volume for this player               |
| `setDataSource(FileDescriptor fd)` This method sets the data source of audio/video file                            |
| `selectTrack(int index)` This method takes an integer, and select the track from the list on that particular index |
| `getTrackInfo()` This method returns an array of track information                                                 |

## TEXTTOSPEECH
- Android allows you convert your text into voice. Not only you can convert it
  but it also allows you to speak text in variety of different languages.
- TextToSpeech class is responsible to convert text into speech.
- It provides a lot of methods to control the speech such as setSpeedRate(),
  setPitch() etc.
|                                               Method & description                                              |
|:---------------------------------------------------------------------------------------------------------------:|
| `addSpeech(String text, String filename)` This method adds a mapping between a string of text and a sound file. |
| `getLanguage()` This method returns a Locale instance describing the language.                                  |
| `isSpeaking()` This method checks whether the TextToSpeech engine is busy speaking.                             |
| `setPitch(float pitch)` This method sets the speech pitch for the TextToSpeech engine.                          |
| `setSpeechRate(float speechRate)` This method sets the speech rate.                                             |
| `shutdown()` This method releases the resources used by the TextToSpeech engine.                                |
| `stop()` This method stop the speak.                                                                            |

## Android AsyncTask example and explanation
- Android AsyncTask going to do background operation on background thread and
  update on main thread.
- In android we cant directly touch background thread to
  main thread in android development. asynctask help us to make communication
  between background thread to main thread.

### Methods of AsyncTask
- `onPreExecute()` − Before doing background operation we should show something
  on screen like progressbar or any animation to user. we can directly
  comminicate background operation using on
- `doInBackground()` -  but for the best practice, we should call all asyncTask
  methods .
- `doInBackground(Params)` − In this method we have to do background operation
  on background thread. Operations in this method should not touch on any
  mainthread activities or fragments.
- `onProgressUpdate(Progress…)` − While doing background operation, if you want
  to update some information on UI, we can use this method.
- `onPostExecute(Result)` − In this method we can update ui of background
  operation result.

### Generic Types in Async Task
- `TypeOfVarArgParams` − It contains information about what type of params used
  for execution.
- `ProgressValue` − It contains information about progress units. While doing
  background operation we can update information on ui using onProgressUpdate().
- `ResultValue` −It contains information about result type.

## LOCATION BASED SERVICES
- Android location APIs make it easy for you to build location-aware
  applications, without needing to focus on the details of the underlying
  location technology.
- This becomes possible with the help of Google Play services, which facilitates
  adding location awareness to your app with automated location tracking,
  geofencing, and activity recognition.
- For this Google provides us a library via Google Play Services for using maps.
- In order to use the Google Maps API, you must register your application on
  the Google Developer Console and enable the API.

## SMS TELEPHONY
- In Android, you can use SmsManager API or devices Built-in SMS application to
  send SMS's.
- SmsManager API
  ```java
  SmsManager smsManager = SmsManager.getDefault();
  sms.sendTextMessage("8802177690", null, "hello javatpoint", pi,null);
  ```
- Built-in SMS application
  ```java
  Intent sendIntent = new Intent(Intent.ACTION_VIEW);
  sendIntent.putExtra("sms_body", "default content");
  sendIntent.setType("vnd.android-dir/mms-sms");
  startActivity(sendIntent);
  ```
- Both need SEND_SMS permission.
  ```xml
  <uses-permission android:name="android.permission.SEND_SMS" />
  ```
