#include <cstring>
#include "Leap.h"
#include "stdio.h"   
#include <winsock2.h>  
#include <string.h>
#include <highgui.h>
#include <windows.h>
#include <WinBase.h>
#pragma comment(lib, "Ws2_32.lib")

using namespace Leap;




DWORD WINAPI Fun(LPVOID lpParamter)
{
	WSADATA   wsaData;
	char   buf[1024];
	int   nBytes = 1024, recvbytes;
	SOCKET   Listening;
	SOCKET   NewConnection;
	SOCKADDR_IN   ServerAddr;
	SOCKADDR_IN   ClientAddr;
	int   ClientAddrLen = sizeof(ClientAddr);
	int   Port = 8888;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	Listening = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	ServerAddr.sin_port = htons(Port);

	bind(Listening, (SOCKADDR *)&ServerAddr, sizeof(ServerAddr));
	listen(Listening, 5);
	printf("waiting   accept....\n");
	cvNamedWindow("win1");
	char *buff = (char*)malloc(sizeof(char)* (240 * 360 + 19));
	FILE *output;
	while (1) {
		NewConnection = accept(Listening, (SOCKADDR   *)&ClientAddr, &ClientAddrLen);
		printf("waiting   recv.....\n");
		output = fopen("test.jpg", "wb");
		unsigned int readBytes = 0;
		while (readBytes != 240 * 360 + 19)
		{
			int ret = recv(NewConnection, buff + readBytes, (240 * 360) - readBytes, 0);
			if (ret <= 0)
			{
				break;
			}
			readBytes += ret;
		}
		fwrite(buff + 19, sizeof(char), readBytes, output);
		fclose(output);

		printf("%s", buff);

		IplImage* image = cvLoadImage("test.jpg", -1);
		cvShowImage("win1", image);
		cvWaitKey(3);
		cvReleaseImage(&image);
	}
}

class SampleListener : public Listener {
  public:
    virtual void onInit(const Controller&);
    virtual void onConnect(const Controller&);
    virtual void onDisconnect(const Controller&);
    virtual void onExit(const Controller&);
	virtual void onFrame(const Controller&);
    virtual void onFocusGained(const Controller&);
    virtual void onFocusLost(const Controller&);
    virtual void onDeviceChange(const Controller&);
    virtual void onServiceConnect(const Controller&);
    virtual void onServiceDisconnect(const Controller&);

  private:
};

const std::string fingerNames[] = {"Thumb", "Index", "Middle", "Ring", "Pinky"};
const std::string boneNames[] = {"Metacarpal", "Proximal", "Middle", "Distal"};
const std::string stateNames[] = {"STATE_INVALID", "STATE_START", "STATE_UPDATE", "STATE_END"};

void SampleListener::onInit(const Controller& controller) {

  std::cout << "Initialized" << std::endl;
}

void SampleListener::onConnect(const Controller& controller) {
  std::cout << "Connected" << std::endl;
  controller.enableGesture(Gesture::TYPE_CIRCLE);
  controller.enableGesture(Gesture::TYPE_KEY_TAP);
  controller.enableGesture(Gesture::TYPE_SCREEN_TAP);
  controller.enableGesture(Gesture::TYPE_SWIPE);
}

void SampleListener::onDisconnect(const Controller& controller) {
  // Note: not dispatched when running in a debugger.
  std::cout << "Disconnected" << std::endl;
}

void SampleListener::onExit(const Controller& controller) {
  std::cout << "Exited" << std::endl;
}

void SampleListener::onFrame(const Controller& controller) {
  // Get the most recent frame and report some basic information
  const Frame frame = controller.frame();
  //Socket
  WSADATA   wsaData;
  char   buf[1024];
  int   nBytes = 1024, recvbytes;
  SOCKET   NewConnection;
  SOCKADDR_IN   ServerAddr;
  int   Port = 8888;
  WSAStartup(MAKEWORD(2, 2), &wsaData);
  NewConnection = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  ServerAddr.sin_family = AF_INET;
  ServerAddr.sin_addr.s_addr = inet_addr("192.168.1.110 ");//ÊÖ»úipµØÖ·
  ServerAddr.sin_port = htons(Port);
  printf("waiting   connect....\n");
  int num = connect(NewConnection, (SOCKADDR   *)&ServerAddr, sizeof(SOCKADDR_IN));
  
  //Gets the position of my hand
  HandList hands = frame.hands();
  for (HandList::const_iterator hl = hands.begin(); hl != hands.end(); ++hl) {
    // Get the first hand
    const Hand hand = *hl;
    std::string handType = hand.isLeft() ? "Left hand" : "Right hand";
	//::SetCursorPos((hand.palmPosition()[0]) * 4 + 620, 600-hand.palmPosition()[1]*1.2);
	if (hand.palmPosition()[0]<-50)
	{
		num = send(NewConnection, "r\n", 4, 0);
		printf("%d %s\n", num, "r");

	}
	else if (hand.palmPosition()[2]>50)
	{
		printf("%s\n", "l");
		num = send(NewConnection, "l\n", 4, 0);
	}
	else if (hand.palmPosition()[2]<-50)
	{
		num = send(NewConnection, "b\n", 4, 0);
		printf("%d %s\n", num, "b");
		
	}
	else if (hand.palmPosition()[2]>50)
	{
		printf("%s\n", "f");
		num = send(NewConnection, "f\n", 4, 0);
	}
  }

  if (!frame.hands().isEmpty() ) {
    std::cout << std::endl;
  }
}

void SampleListener::onFocusGained(const Controller& controller) {
  std::cout << "Focus Gained" << std::endl;
}

void SampleListener::onFocusLost(const Controller& controller) {
  std::cout << "Focus Lost" << std::endl;
}

void SampleListener::onDeviceChange(const Controller& controller) {
  std::cout << "Device Changed" << std::endl;
  const DeviceList devices = controller.devices();

  for (int i = 0; i < devices.count(); ++i) {
    std::cout << "id: " << devices[i].toString() << std::endl;
    std::cout << "  isStreaming: " << (devices[i].isStreaming() ? "true" : "false") << std::endl;
  }
}

void SampleListener::onServiceConnect(const Controller& controller) {
  std::cout << "Service Connected" << std::endl;
}

void SampleListener::onServiceDisconnect(const Controller& controller) {
  std::cout << "Service Disconnected" << std::endl;
}

int main(int argc, char** argv) {

	HANDLE hThread = CreateThread(NULL, 0, Fun, NULL, 0, NULL);
	CloseHandle(hThread);

  // Create a sample listener and controller
  SampleListener listener;
  Controller controller;

	controller.config().setInt32("background_app_mode", 2);
	 controller.config().save();


  // Have the sample listener receive events from the controller
  controller.addListener(listener);
  controller.setPolicy(Leap::Controller::POLICY_BACKGROUND_FRAMES);
  controller.config().setInt32("background_app_mode", 2);
  controller.config().save();

  // Keep this process running until Enter is pressed
  std::cout << "Press Enter to quit..." << std::endl;
  std::cin.get();

  // Remove the sample listener when done
  controller.removeListener(listener);

  return 0;
}
