#ifndef ELEVATORCONTROLSYSTEM_H
#define ELEVATORCONTROLSYSTEM_H

#include <iostream>
#include <string>
#include <iomanip>
#include <Elevator.h>
#include <Passenger.h>

using namespace std;

class ElevatorControlSystem {
		
	public:
		//constructor
        ElevatorControlSystem(const int& elevnum,const int& flrnum,const int& maxweight,const int& passnum);

		//destructor
		~ElevatorControlSystem();

		//getters
		string getcurrstrat();
        Elevator** getelevarr();

		//other
        string flrreq(string direction,int serveflrnum,int passnum);
        string elevreq(int destflrnum,int elevnum,int passnum);
        string elevsafetyreq(string safetyissue, int elevnum);//safety issue in a single elev
        string safetyreq(string safetyissue);//safety issue with all elevs

        string passwalkin(int passnum, int elevnum);
        string passwalkout(int passnum, int elevnum, int destflrnum);

        int timedependentstrat(int currtime);//based on time of day, morning(7:30 - 8:30) will prioritize main floor (1)
        int elevcenteredstrat(int serveflrnum);//send the closes idle elev to the floor

	private:
		string currstrat;
		Elevator** elevators;
        Passenger** passengers;

        int numofelevs;
        int numofflrs;
        int obstaclecount;
};
#endif
