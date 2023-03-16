
#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <iostream>
#include <string>
#include <iomanip>
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
        int getElevNum();
        int getcurrflrnum();
        int getmaxweight();
        int getdestflrnum();
        int getcurrweight();

		//other
        string move(string direction);//moves the elevator in a direction supplied, up or down
        string ringbell();
        string closeDoor();
        string openDoor();
        string holdOpenDoor();
        bool checkidle();
        void setidle(bool ismoving);
        void setsafetymsg(string msg);
        string interruptclose();//when light sensor detects an obstacle, this gets activated to stop the close() of its doors
        string displayandplaysafetymsg();

        void addPassengers(int passweight);//when passenger walks in
        void rmvPassengers(int passweight);//when passenger walks off

	private:
        int elevnum;
		int currflrnum;
        int maxweight;
        int currweight;
		int maxcapacity;
		int destflrnum;
		int flrcount;

        bool isidle;
		
        string safetymsg;//gets set to the safety message given from ecs
        string display;
        string audioSys;
};
#endif
