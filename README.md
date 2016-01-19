# LeapMotion-Car-Controller
This is one of my projects of 3C lecture in SJTU. In this project, I aim to use Leap Motion to control a toy car. 
All the things I need are: 

>A leap motion; 

>An android phone with camera; 

>A toy car with MSP-EXP430 and bluetooth;

>A laptop.
 
###Here is how it works:

**1** The mobile phone is fixed on the toy car and take videos of the road.

**2** Mobile phone sends real-time video to my laptop by socket, and my laptop will receive the data stream and show the video on my monitor. This is done by using OpenCV.

**3** After seeing the road situation on the screen, I can try to control the car by my hands. Leap motion will catch the position of my hands.

**4** Laptop will send different commands to my mobile phone via socket, according to the position of my hand.

**5** After receiving command from the laptop, the mobile phone then sends command to the toy car via bluetooth.

**6** The car keeps going.

In fact it doesn't have to be such complex:) I just do it for fun:)


###How to use it
If you want to run this project by yourself, you need to follow the steps below:
* 1.Download this project, make sure you have installed OpenCV on your laptop.
* 2.Open file SampleVS2012.sln in folder /PC/LeapSDK_LFS/samples/ and check the path of *.lib and *.dll that are related to OpenCV.
* 3.Change the ip address in the code to the ip of your phone's.
* 4.Install the android app in folder /android app/SocketCamera/bin/
* 5.Turn on your bluetooth and connect to your toycar. Then run this app.
* 5.Click "setting" and change the ip address to the ip of your laptop's. Then exit the app.
* 6.Plug your Leap Motion to the laptop and start running your VS project
* 7.Then run the app on your phone.
* 8.Click"Start connecting"
* 9.Click"Start transferring"
* 10.If everything is right, you can see the video on your monitor and the toy car will react to your hand's movement

###Demo
You can see a demo for this project here:
https://youtu.be/lNxO1_AHhXg

Notice that the android app is based on the project of 肖泽云.http://download.csdn.net/detail/xwebsite/4973592 .I thank him very much. 
