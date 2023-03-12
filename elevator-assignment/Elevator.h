
#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <iostream>
#include <string>
#include <iomanip>
#include <Button.h>
#include <Door.h>
#include <Display.h>
#include <AudioSystem.h>
#include <Passenger.h>


using namespace std;

#define MAXCAPACITY 5

class Elevator {
		
	public:
		//constructor
		Elevator(const int& elevnum, const int& maxweight, const int& flrnum);
		//destructor
		~Elevator();

		//getters
		string getElevNum();
		string getcurrflrnum();
		string getmaxweight();
		string getdestflrnum();


		//other
        void ringbell();
		void stop();//stay at currflr
		void move(string direction);//moves the elevator in a direction supplied, up or down
		void alarm(string safetyissue);//alarm is raised with a safety issue

		void atnewflr(int flrnum);//floor sensor sends the elevator its new floor, probably change this to be simpler
		void detectflr(int flrnum);//floor sensor that detects the floor
		void detectissue(string safetyissue);//safety sensors that detects whatever issue arises
		void notify(int destflrnum);//gets notified from teh buttons what destination floor button has been pressed
		void interruptclose();//when light sensor detects an obstacle, this gets activated to stop the close() of its doors
		void ecsrequest(string msg);//receives what ever request, mainly a safety message to relay and play/display through its audiosys and display

		void addPassengers();//when passenger walks in
		void rmvPassengers();//when passenger walks off

	private:
        int elevnum;
		int currflrnum;
		int maxweight;//given by user input
		int maxcapacity;
		int destflrnum;
		int flrcount;

		bool isnotmoving; 
		
		string alarmmode;//gets set to the safetyissue that was sent from helpBtn,fireBtn, or sensors

		Door* door;

		Button* openBtn;
		Button* closeBtn;

		Button* helpBtn;
		Button* fireBtn;

		Button** destBtns;

		Display* display;
		AudioSystem* audioSys;

		Passenger* passengers[MAXCAPACITY];
};
#endif
