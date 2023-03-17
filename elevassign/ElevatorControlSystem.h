#ifndef ELEVATORCONTROLSYSTEM_H
#define ELEVATORCONTROLSYSTEM_H

#include <iostream>
#include <string>
#include <iomanip>
#include <Elevator.h>
#include <Passenger.h>
#include <QtWidgets>

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
        string flrreq(string direction,int serveflrnum,int passnum, QTime currenttime, QComboBox* elevdropdown, QLineEdit* currweightdisplay);
        string elevreq(int destflrnum,int elevnum,int passnum,QLineEdit* currweightdisplay);
        string elevsafetyreq(string safetyissue, int elevnum, int passnum);//safety issue in a single elev
        string safetyreq(string safetyissue);//safety issue with all elevs

        string bssconnection(int elevnum, int passnum);
        string call911(int elevnum);

        string passwalkin(int passnum, int elevnum);
        string passwalkout(int passnum, int elevnum, int destflrnum);

        void decideallocstrat(QTime currenttime);//sets currstrat based on time of day,rush hour or normal hours
        int elevcenteredstrat(int serveflrnum);//send the closes idle elev to the floor
        int loadbalancestrat();//distributes load between idle elevators

    private:
        string currstrat;
        Elevator** elevators;
        Passenger** passengers;

        int numofelevs;
        int numofflrs;
        int numofpass;
        int obstaclecount;
};
#endif
