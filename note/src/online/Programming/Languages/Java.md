# Java

## 1) Write a program to check number is even or odd using if else.
```java
import java.util.Scanner;

/**
 * Java Program - Check if Number is Even or Odd
 */

public class Example {

    public static void main(String[] args) {
        //create a scanner to read bytes from console entered by user via keyboard
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter a number : ");
        //read integer from user
        int a = scanner.nextInt();

        //check if the number is even or odd
        if(a%2==0) {
            System.out.println("The number is even.");
        } else {
            System.out.println("The number is odd.");
        }

        //close the scanner
        scanner.close();
    }
}
```
O/P
```
Enter a number : 4
The number is even.
```

## 2) Write a program to check switch case statement using character datatype.
```java
public class SwitchExample {
public static void main(String[] args) {
    //Declaring a variable for switch expression
    String name="a";
    //Switch expression
    switch(name){
    //Case statements
    case "a": System.out.println("Aman is in Database.");
    break;
    case "r": System.out.println("Ravi is in Database.");
    break;
    case "g": System.out.println("Gita is in Database.");
    break;
    //Default case statement
    default:System.out.println("Name is not in database.");
    }
}
}
```
```
Aman is in Database.
```
## 3) Develop a program to print command line argument using for loop.
```java
class CommandLineExample{
    public static void main(String args[]){
        System.out.println("Your first argument is: "+args[0]);
        for (int i; i <= 5; i++) {
            System.out.println(arg[0]);
        }
    }
}
```
O/P
```
> java CommandLineExample Hello
Your first argument is: Hello
Hello
Hello
Hello
Hello
Hello
Hello
```
## 4) Develop a program to show the use of implicit typecasting.
```java
public class ImplicitTypecastingExample {
   public static void main(String args[]) {
      byte p = 12;
      System.out.println("byte value : "+p);
      // Implicit Typecasting
      short q = p;
      System.out.println("short value : "+q);
      int r = q;
      System.out.println("int value : "+r);
      long s = r;
      System.out.println("long value : "+s);
      float t = s;
      System.out.println("float value : "+t);
      double u = t;
      System.out.println("double value : "+u);
   }
}
```
```
byte value : 12
short value : 12
int value : 12
long value : 12
float value : 12.0
double value : 12.0
```
## 5) Write a program to implement different types of constructors to perform addition of complex numbers.
```java
public class ComplexNumber{
   //for real and imaginary parts of complex numbers
   double real, img;

   //constructor to initialize the complex number
   ComplexNumber(double r, double i){
	this.real = r;
	this.img = i;
   }

   public static ComplexNumber sum(ComplexNumber c1, ComplexNumber c2)
   {
	//creating a temporary complex number to hold the sum of two numbers
        ComplexNumber temp = new ComplexNumber(0, 0);

        temp.real = c1.real + c2.real;
        temp.img = c1.img + c2.img;

        //returning the output complex number
        return temp;
    }
    public static void main(String args[]) {
	ComplexNumber c1 = new ComplexNumber(5.5, 4);
	ComplexNumber c2 = new ComplexNumber(1.2, 3.5);
        ComplexNumber temp = sum(c1, c2);
        System.out.printf("Sum is: "+ temp.real+" + "+ temp.img +"i");
    }
}
```
O/P
```
Sum is: 6.7 + 7.5i
```

## 6) Write a program to show the use of all methods of String class.
```java
public class StringMethodsDemo {
	public static void main(String[] args) {
		String targetString = "Java is fun to learn";
		String s1= "JAVA";
		String s2= "Java";
		String s3 = "  Hello Java  ";

		System.out.println("Char at index 2(third position): " + targetString.charAt(2));
		System.out.println("After Concat: "+ targetString.concat("-Enjoy-"));
		System.out.println("Checking equals ignoring case: " +s2.equalsIgnoreCase(s1));
		System.out.println("Checking equals with case: " +s2.equals(s1));
		System.out.println("Checking Length: "+ targetString.length());
		System.out.println("Replace function: "+ targetString.replace("fun", "easy"));
		System.out.println("SubString of targetString: "+ targetString.substring(8));
		System.out.println("SubString of targetString: "+ targetString.substring(8, 12));
		System.out.println("Converting to lower case: "+ targetString.toLowerCase());
		System.out.println("Converting to upper case: "+ targetString.toUpperCase());
		System.out.println("Triming string: " + s3.trim());
		System.out.println("searching s1 in targetString: " + targetString.contains(s1));
		System.out.println("searching s2 in targetString: " + targetString.contains(s2));

		char [] charArray = s2.toCharArray();
		System.out.println("Size of char array: " + charArray.length);
		System.out.println("Printing last element of array: " + charArray[3]);

	}

}
```
O/P
```
Char at index 2(third position): v
After Concat: Java is fun to learn-Enjoy-
Checking equals ignoring case: true
Checking equals with case: false
Checking Length: 20
Replace function: Java is easy to learn
SubString of targetString: fun to learn
SubString of targetString: fun
Converting to lower case: java is fun to learn
Converting to upper case: JAVA IS FUN TO LEARN
Triming string: Hello Java
searching s1 in targetString: false
searching s2 in targetString: true
Size of char array: 4
Printing last element of array: a
```

## 7) Write a program to implement all methods of StringBuffer class.
```java
class StringBufferExample{
    public static void main(String args[]){
        StringBuffer sb=new StringBuffer("Hello");
        sb.append(" Java");
        System.out.println(sb);
        sb.insert(1,"Java");
        System.out.println(sb);
        sb.replace(1,3,"Java");
        System.out.println(sb);
        sb.delete(1,3);
        System.out.println(sb);
        sb.reverse();
        System.out.println(sb);
        System.out.println(sb.capacity());
        sb.ensureCapacity(10);
        System.out.println(sb.capacity());
    }
}
```
O/P
```
Hello Java
HJavaello Java
HJavavaello Java
Hvavaello Java
avaJ olleavavH
21
21
```
## 8) Write a program to implement single inheritance.
```java
class Animal{
void eat(){System.out.println("eating...");}
}
class Dog extends Animal{
void bark(){System.out.println("barking...");}
}
class TestInheritance{
public static void main(String args[]){
Dog d=new Dog();
d.bark();
d.eat();
}}
```
O/P
```
barking...
eating...
```
## 9) Write a program to implement multilevel inheritance.
```java
class Animal{
void eat(){System.out.println("eating...");}
}
class Dog extends Animal{
void bark(){System.out.println("barking...");}
}
class BabyDog extends Dog{
void weep(){System.out.println("weeping...");}
}
class TestInheritance2{
public static void main(String args[]){
BabyDog d=new BabyDog();
d.weep();
d.bark();
d.eat();
}}
```
O/P
```
weeping...
barking...
eating...
```
## 10) Develop a program to find area of rectangle and circle using interface.
```java
class FindLargestShape {
  public static void main(String arg[]) {
    Rectangle r = new Rectangle(10, 4);
    System.out.println("Rectangle Area : " + r.getArea());
    System.out.println();
  }
}

class Rectangle {
  double length;
  double breadth;
  Rectangle(double length, double breadth) {
    this.length = length;
    this.breadth = breadth;
  }
  double getArea() {
    return length * breadth;
  }

}
```
## 11) Write a program to implement user defined packages in terms of creating a new package and importing the same.
```java
package example;

public class gfg {

    public void show()
    {
        System.out.println("Hello geeks!! How are you?");
    }

    public static void main(String args[])
    {
        gfg obj = new gfg();
        obj.show();
    }
}
```
```java
import example.gfg;

public class GFG {
    public static void main(String args[])
    {
        gfg obj = new gfg();
        System.out.println(obj.show());
    }
}
```
O/P
```
Hello geeks!! How are you?
```
## 12) Write a program to implement two thread use sleep method.
```java
class TestSleepMethod1 extends Thread{
 public void run(){
  for(int i=1;i<5;i++){
  // the thread will sleep for the 500 milli seconds
    try{Thread.sleep(500);}catch(InterruptedException e){System.out.println(e);}
    System.out.println(i);
  }
 }
 public static void main(String args[]){
  TestSleepMethod1 t1=new TestSleepMethod1();
  TestSleepMethod1 t2=new TestSleepMethod1();

  t1.start();
  t2.start();
 }
}
```
```
11
2
2
3
3
4
4
```
## 13) Develop a program to accept a password from the user and throw "Authentication Failure" exception if the password is incorrect.
```java
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

class AuthenticationException extends Exception {

 public AuthenticationException(String message) {

  super(message);
 }
}

public class AuthenticationExcDemo {

 public static void main(String[] args) {

  InputStreamReader isr = new InputStreamReader(System.in);
  BufferedReader br = new BufferedReader(isr);
  String pwd;

  try {

   System.out.print("Enter password :: ");
   pwd = br.readLine();

   if(!pwd.equals("123"))
    throw new AuthenticationException("Incorrect password\nType correct password");
   else
    System.out.println("Welcome User !!!");

  }
  catch (IOException e) {
   e.printStackTrace();
  }
  catch (AuthenticationException a) {
   a.printStackTrace();
  }
  System.out.println("BYE BYE");
 }

}
```
## 14) Develop a program to draw a polygon using applet.
```java
import java.awt.*;
import javax.swing.*;

public class poly extends JApplet {

    // called when applet is started
    public void init()
    {
        // set the size of applet to 300, 300
        setSize(200, 200);
        show();
    }

    // invoked when applet is started
    public void start()
    {
    }

    // invoked when applet is closed
    public void stop()
    {
    }

    public void paint(Graphics g)
    {
        // x coordinates of vertices
        int x[] = { 10, 30, 40, 50, 110, 140 };

        // y coordinates of vertices
        int y[] = { 140, 110, 50, 40, 30, 10 };

        // number of vertices
        int numberofpoints = 6;

        // set the color of line drawn to blue
        g.setColor(Color.blue);

        // draw the polygon using drawPolygon function
        g.drawPolygon(x, y, numberofpoints);
    }
}
```
## 15) Develop an applet for drawing a human face.
```java
import java.applet.*;
import java.awt.*;
public class Human_Face extends Applet
{
    //Initialize the applet
    public void init()
    {
	setBackground(Color.white);
    }
    //Draw the human face
    public void paint(Graphics g)
    {
        //Change color to cream
        Color clr=new Color(255,179,86);
        g.setColor(clr);
        //Draw and fill the face
        g.drawOval(100,100,250,300);
        g.fillOval(100,100,250,300);
        //Change color to black
        g.setColor(Color.black);
        //Draw the left eye
        g.drawOval(160,185,40,25);
        g.fillOval(160,185,40,25);
        //Draw the right eye
        g.drawOval(250,185,40,25);
        g.fillOval(250,185,40,25);
        //Draw the Left Eyebrow
        g.drawArc(160,170,35,10,0,180);
        //Draw the Right Eyebrow
        g.drawArc(250,170,35,10,0,180);
        //Draw the Nose
        g.drawLine(210,265,210,275);
        g.drawLine(240,265,240,275);
        g.drawArc(210,275,30,10,0,-180);
       //Draw the smile
        g.drawArc(175,300,100,50,0,-180);
    }
}
```
## 16) Develop a program to draw square inside a circle using applet.
```java
import java.applet.";
import java.awt.*;
/* <applet code=shapes width=10 height=10> </applet>*/
public class shapes extends Applet {
    public void paint(Graphics g) {
    g.drawString("Square inside a circle", 150,110);
    g.drawOval(180,10,80,80);
    g.drawRect(192,22,55,55):
    g.drawString("Circle inside a square", 290, 110);
    g.drawRect(290, 10, 80, 80);
    g.drawOval(290, 10, 80, 80);
    }
}
```
## 17) Develop a program to copy characters from one file to another.
```java
import java.io.*;
import java.util.*;
class Copyfile {
 public static void main(String arg[]) throws Exception {
  Scanner sc = new Scanner(System.in);
  System.out.print("Provide source file name :");
  String sfile = sc.next();
  System.out.print("Provide destination file name :");
  String dfile = sc.next();
  FileReader fin = new FileReader(sfile);
  FileWriter fout = new FileWriter(dfile, true);
  int c;
  while ((c = fin.read()) != -1) {
   fout.write(c);
  }
  System.out.println("Copy finish...");
  fin.close();
  fout.close();
 }
}
```
