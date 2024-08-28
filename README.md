# Engineering Documentation - Team Violet 
![f3ea4b6a1b1a032c93fc61f042ce0fb9](https://github.com/user-attachments/assets/d4b777cf-579c-41cd-bcf2-25b11e67dbe0)
## Introduction
In this repository you will find all the information related to the construction and assembly of the autonomous robot built by Team Violet for the Future Engineers category in the 2024 Season.
This has been an incredible journey with a lot of obstacles, and we have done our best to come up with a design that we were not only satisfied with, but one that could properly acomplish all of the objectives present in this edition of the "Future Engineers" category.

## Contents
- Team Violet's Members
- Hardware Design
   - Design Process
   - Elements
     - 3D printed
     - Electronics
- Software Design
   - Image and Color Analysis
     - Image Capturing
     - Image Filter (RGB to HSV)
     - Creating Red and Green masks
     - Gray Image with red and green details
     - Color Detection
     - Location Processing and distance from the cones
     - Data Sending
   - Robot Movement
     - Servomotor setting
     - Lane Determination
     - Robot Orientation

# Team Violet's Members
 - Adrian Alvarez:
>Hi, my name is Adrian Alvarez, I'm part of Team Violet 1 and I'm responsible for the 3D designs used in the robot. My expectations of this competition are to learn and to test my skills in robotics.
 - Reinaldo Belmonte:
>eee
 - Jose Zambrano:
>ttt


# Hardware Design
## Design Process
The final design of the robot is intended as a modular design, consisting of 3 modules: lower "traction" module, middle "electronics" module, and upper "power supply and color processing" module.

The robot went through a multitude of changes until it reached its final iteration.

One of these changes was the replacement of the traditional motors that we used before with a Hex Motor, which had a greater strength to the wheels. 

Same thing with the turning system, being the original servomotor replaced with a more efficient and precise model at the moment of the turns.

Another of these changes was the reorganization of its elements, given the changes in the motors used and the space they now occupied, we made a redistribution to most of the elements present in the robot, this time taking into account to make it even more accessible for repairs or adjustments to any of its parts.

With all these changes made, a 3D design for the entire structure of the robot was made, thus facilitating its visualization and analysis.

## Elements

  -  _L298N: The L298N Motor Driver Module is a potent module designed to operate DC and Stepper Motors. It is composed of an L298 motor driver integrated circuit and a 78M05 5V regulator. The L298N Module has the capacity to manage up to 4 DC motors, or it can control 2 DC motors with the ability to adjust direction and speed._
    
  -   _Motors: The robot has 1 direct current (DC) motor and 1 SG90 servomotor that allow it to move in different directions. Meanwhile the DC motor serves as rear wheel drive, the servomotor gives it the ability to turn left or right. The rear wheel drive motor provides the forward or backward motion of the robot, while the turning motor rotates the front wheels to change the orientation of the robot. By combining these two motions, the robot can move in any direction on a flat surface. These motors feature a torque of 35 grams*centimeter, a minimum speed of 0.22m/s and a speed limit of 0.71m/s (NOTE: this is the minimum speed the car can go, the minimum speed for the motor itself is even lower.)_

  -   _Arduino Mega 2560 Wifi R3 + Arduino Custom Shield: The MEGA2560 Wifi is a variant that includes an ESP8266 Wifi chip. The microcontroller is still an Atmel ATmega2560 compatible with Arduino and also has an ESP8266EX all on the same board, the serial-USB converter is a CH340G and through a DIP switch it allows you to configure the board to work independently of the MCU, enable the CH340 to upload code for either the ATmega2560 or ESP8266EX. All of this is complemented by the inserte nomnbre del shield y specs._

  -   _Raspberry Pi 4: The Raspberry Pi 4 is a single-board development board used for entry-level computing, being released the latest version (Raspberry Pi 4) in June 2019. The board is available in four RAM variants: 1 GB, 2 GB, 4 GB, and 8 GB. Model B (the one we are using) is the most common and comes with a Broadcom BCM2711 processor, which is a 1.5GHz quad-core ARM Cortex-A72 processor. Additionally, it has enhanced USB capability with two USB 2.0 ports and two USB 3.0 ports, enabling up to ten times faster data transfers. It also comes with Gigabit Ethernet connectivity, built-in wireless and Bluetooth._

   -   _Ultrasonic Sensor: The robot has 3 HC-SR04 ultrasonic sensors on the left, right and front that function as a sonar, on the left, right and front. The HC-SR04 sensor has two transducers: a piezoelectric transmitter and receiver, in addition to the electronics necessary for its operation. The operation of the sensor is as follows: the piezoelectric transmitter emits 8 ultrasonic pulses (40KHz) after receiving the order on the TRIG pin, the sound waves travel in the air and bounce when meeting an object, the bounce sound is detected by the piezoelectric receiver, then the ECHO pin changes to High (5V) for a time equal to the time the wave took from when it was emitted to when it was detected, the time of the ECHO pulse is measured by the microcontroller and thus the distance can be calculated to the object. Sensor performance is not affected by sunlight or black-colored material (although acoustically soft materials such as cloth or wool can be difficult to detect). All of this in a range of 2 to 450 cm._

   -   _TCS230 Color Sensor: The TCS230 is a programmable color light-to-frequency converter that merges adjustable silicon photodiodes and a current-to-frequency converter into a single CMOS integrated circuit. It produces a square wave output where the frequency is directly related to the intensity of light._
  
   -   _Camera: The robot uses an Argom Tech 720p Cam20 Webcam, (pretty generic honestly but hey, its something i guess.)_


   -   _Power Supply Elements:_
   
   =   _3.7V 18650 Lithium Batteries: These batteries are rechargeable and have a capacity of between 2600 mAh and 3500 mAh (ours have 3500 mAh each). The batteries have a nominal voltage of 3.7V and a maximum voltage of 4.2V. The batteries are connected to the robot through a battery holder that has an on/off switch. The batteries can be charged with a special charger that has a protection circuit against overloads and short circuits.._

   =   _Power Bank: We use a ONN ONA18WIO63 Power Bank to supply Raspberry Pi and the Arduino Mega with energy. It has 1 USB ports, along with a Micro-USB port for charging, with an output voltage of 5V and 2.4A._


    Coding Environments

  -   _ARDUINO Integrated Development Environment (C++): The Arduino Integrated Development Environment (IDE) is a cross-platform software (for Windows, macOS, Linux) written in the Java programming language. It is used to write and upload code to Arduino-compatible boards, as well as other boards from different manufacturers with the help of additional cores._

_It can handle C and C++ languages with specific rules for organizing the code. It also provides a software library from the Wiring project that has many common I/O functions. The code written by users only needs two basic functions: one to start the sketch and one to run the main loop. These functions are compiled and linked with a main() function in a loop using the GNU toolchain, which is also part of the IDE. The Arduino IDE uses a program called avrdude to turn the executable code into a text file with hexadecimal encoding that is transferred to the Arduino board by a loader program in the board’s firmware._

Its function related to code would be to control movements (rear wheel drive, turn left or right), based on the information sent by the camera (more info ahead).

  -   _Python: Python Integrated Development Environment (or Python for short) is a high-level interpreted programming language whose philosophy emphasizes the readability of its code, it is used to develop applications of all kinds, for example: Instagram, Netflix, Spotify, Panda3D, among others. It is a multi-paradigm programming language, since it partially supports object orientation, imperative programming and, to a lesser extent, functional programming. It is an interpreted, dynamic and cross-platform language. Created back in late 80s, Python consistently ranks as one of the most popular programming languages._

Its function related to code would be to detect colors and control the camera, and, subsequently, sends orders to the ESP-32 to move based on that information.

-----------------------------------------------------------------------------------------------------------------------------------------

    HOW THE CAMERA WORKS

_The artificial vision algorithms that are used to recognize objects or colors are computer programs that process the images captured by the camera and extract relevant information from them. For example, to recognize colors, We use an algorithm that converts color images to grayscale and then applies a red, green or blue color mask depending on the color we want to detect. Then, we calculate the percentage of pixels of the desired color in the image and compare it with a predefined threshold to determine whether or not there is presence of the color._

    HOW TO COMPILE THE CODE TO THE VEHICLE
- _Connect the Arduino Mega to the computer through a Micro-USB cable_
- _Look for the button in the Programming Environment to transfer the code_
- _Wait to finish_

  {Raspberry Pi 4 it is not necessary to specify because of course, it can run python natively}

--------------------------------------------------------------------------------------------------------------------------------------

    OBJECTIVE OF THE ROBOTIC SOLUTION.

The purpose of this robotic solution is to showcase the abilities of the field of robotics.

--------------------------------------------------------------------------------------------------------------------------------------
_Thank You. Team Violet - 2024._
======================================================================================================================================
