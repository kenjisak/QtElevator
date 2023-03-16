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
        void atnewflr(int flrnum, int elevnum);//prob dont need this too complex
        string elevreq(int destflrnum,int elevnum,int passnum);
        string elevsafetyreq(string safetyissue, int elevnum);//safety issue in a single elev
        string safetyreq(string safetyissue);//safety issue with all elevs

        string passwalkin(int passnum, int elevnum);
        string passwalkout(int passnum, int elevnum, int destflrnum);

		void timestrat();//implement time alloc strat. this will be set as the currstrat from init of ecs until ordered to changed and use the other strat functions instead
		void opportunisticstrat();//implement opportunistic alloc strat


	private:
		string currstrat;
		Elevator** elevators;
        Passenger** passengers;

        int numofelevs;
        int numofflrs;
        int obstaclecount;
};
#endif
