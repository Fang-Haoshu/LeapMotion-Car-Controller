# Leap-Motion-Android-Communication-by-Socket
This is one of my projects of 3C lecture in SJTU. In this project, I aim to use Leap Motion to control a toy car. 
All the things I need are: A leap motion; An android phone with camera; A toy car with MSP-EXP430 and bluetooth; A laptop.
Here is how it works:

1 The mobile phone is fixed on the toy car and take videos of the road.
2 Mobile phone sends real-time video to my laptop by socket, and my laptop will receive the data stream and show the video on my monitor. This is done by using OpenCV.
3 After seeing the road situation on the screen, I can try to control the car by my hands. Leap motion will catch the position of my hands.
4 Laptop will send different commands to my mobile phone via socket, according to the position of my hand.
5 After receiving command from the laptop, the mobile phone then sends command to the toy car via bluetooth.
6 The car keeps going.

Of course it doesn't have to be such complex:) I just do it for fun
