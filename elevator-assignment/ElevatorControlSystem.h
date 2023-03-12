#ifndef ELEVATORCONTROLSYSTEM_H
#define ELEVATORCONTROLSYSTEM_H

#include <iostream>
#include <string>
#include <iomanip>
#include <Elevator.h>
#include <Floor.h>

using namespace std;

class ElevatorControlSystem {
		
	public:
		//constructor
		ElevatorControlSystem(const int& elevnum,const int& flrnum,const int& maxweight);

		//destructor
		~ElevatorControlSystem();

		//getters
		string getcurrstrat();
		
		//other
        void flrreq(string direction,int serveflrnum);
		void atnewflr(int flrnum, int elevnum);
		void elevreq(int destflrnum,int elevnum);
		void elevreq(string safetyissue, int elevnum);
		void timestrat();//implement time alloc strat. this will be set as the currstrat from init of ecs until ordered to changed and use the other strat functions instead
		void opportunisticstrat();//implement opportunistic alloc strat

	private:
		string currstrat;
		Elevator** elevators;
		Floor** floors;
};
#endif
