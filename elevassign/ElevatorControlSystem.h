#ifndef ELEVATORCONTROLSYSTEM_H
#define ELEVATORCONTROLSYSTEM_H

#include <iostream>
#include <string>
#include <iomanip>
#include <Elevator.h>
#include <Floor.h>
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
        Floor** getflrarr();
        Elevator** getelevarr();

		//other
        string flrreq(string direction,int serveflrnum,int passnum);
		void atnewflr(int flrnum, int elevnum);
		void elevreq(int destflrnum,int elevnum);
        string elevsafetyreq(string safetyissue, int elevnum);
        string safetyreq(string safetyissue);

        string passwalkin(int passnum, int elevnum);

		void timestrat();//implement time alloc strat. this will be set as the currstrat from init of ecs until ordered to changed and use the other strat functions instead
		void opportunisticstrat();//implement opportunistic alloc strat


	private:
		string currstrat;
		Elevator** elevators;
        Floor** floors;
        Passenger** passengers;

        int numofelevs;
        int numofflrs;
        int obstaclecount;
};
#endif
