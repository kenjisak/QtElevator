#include "ElevatorControlSystem.h"

ElevatorControlSystem::ElevatorControlSystem(const int& elevnum,const int& flrnum,const int& maxweight,const int& passnum){

    this->numofflrs = flrnum;
    this->numofelevs = elevnum;
    obstaclecount = 0;

    elevators = new Elevator*[elevnum];
    for (int i = 0;i < elevnum;i++){
        elevators[i] = new Elevator(i+1,maxweight,flrnum);
    }

    passengers = new Passenger*[passnum];
    for (int i = 0;i < passnum;i++){
        passengers[i] = new Passenger(i+1,100);//default of 100 lbs per passenger
    }
}

ElevatorControlSystem::~ElevatorControlSystem(){
    delete this;
}

Elevator** ElevatorControlSystem::getelevarr(){
    return elevators;
}

string ElevatorControlSystem::flrreq(string direction,int serveflrnum,int passnum){//when an up or down button from the floor is pressed, this finds an elev and sends it there
    string allactions = "";
    allactions += "\nPassenger "  + to_string(passnum) + " pressed Floor " + to_string(serveflrnum) + " " + direction + " button and lit.";

    // add currstrat check here
    int idleelevnum = elevcenteredstrat(serveflrnum);
    //alloc strat would be finding idle elevator thats closest to the serveflrnum, ex. servelfr = 2, elev 1 is at flr 1, elev 2 is at flr 5, send elev 1

    if (idleelevnum != -1){ // if an elevator is found
        elevators[idleelevnum]->setidle(false);//elevator is no longer idle and is moving/serving a passenger
        allactions += "\nCar " + to_string(elevators[idleelevnum]->getElevNum()) + " Display: Floor " + to_string(elevators[idleelevnum]->getcurrflrnum());
        while (serveflrnum != elevators[idleelevnum]->getcurrflrnum()){//make the elevator move up or down until it reaches the floor that called one
            if(elevators[idleelevnum]->getcurrflrnum() < serveflrnum){// if the elevator is on a floor below the service floor
                allactions += elevators[idleelevnum]->move("up");
            }else{// if the elevator is on a floor above the service floor
                allactions += elevators[idleelevnum]->move("down");
            }
        }

        allactions += "\nCar " + to_string(elevators[idleelevnum]->getElevNum()) + " has arrived.";
        allactions += "\nFloor " + to_string(serveflrnum) + " " + direction + " button off.";
        allactions += elevators[idleelevnum]->openDoor();//change to only opens door, and closes door here after passenger walks in

        allactions += passwalkin(passnum,idleelevnum);//pass walks in and this has an overload check

        allactions += elevators[idleelevnum]->closeDoor();
//        elevators[idleelevnum]->setidle(true);//set it back to idle as its not moving anymore
        //might have to remove/change to show all elevators in use case.

    }else{//else we didnt find an elevator all are in use atm
        allactions += "\nFloor " + to_string(serveflrnum) + " " + direction + " button off.";
        allactions += "\nAll Elevators in Use.";

    }
    return allactions;
}

string ElevatorControlSystem::elevreq(int destflrnum, int elevnum, int passnum){
    string allactions = "";

    allactions += "\nPassenger " + to_string(passnum) + " pressed Floor " + to_string(destflrnum) + " button in Car " + to_string(elevnum);
    elevators[elevnum - 1]->setidle(false);//elevator is no longer idle and is moving/serving a passenger
    allactions += "\nCar " + to_string(elevnum) + " Display: Floor " + to_string(elevators[elevnum - 1]->getcurrflrnum());
    while (destflrnum != elevators[elevnum - 1]->getcurrflrnum()){//make the elevator move up or down until it reaches the dest floor
        if(elevators[elevnum - 1]->getcurrflrnum() < destflrnum){// if the elevator is on a floor below the dest floor
            allactions += elevators[elevnum - 1]->move("up");
        }else{// if the elevator is on a floor above the dest floor
            allactions += elevators[elevnum - 1]->move("down");
        }
    }

    allactions += "\nCar " + to_string(elevnum) + " has arrived.";
    allactions += elevators[elevnum - 1]->openDoor();//change to only opens door, and closes door here after passenger walks in

    allactions += passwalkout(passnum,elevnum,destflrnum);//pass walks out

    allactions += elevators[elevnum - 1]->closeDoor();
    elevators[elevnum - 1]->setidle(true);//set it back to idle as its not moving anymore

    return allactions;
}


string ElevatorControlSystem::passwalkin(int passnum, int elevnum){
    //else trigger overload safety which general Passenger walks out and return that message
    string allactions = "\nPassenger " + to_string(passnum) + " walks into Car " + to_string(elevators[elevnum]->getElevNum());
    if ((passengers[passnum - 1]->getWeight() + elevators[elevnum]->getcurrweight()) <= elevators[elevnum]->getmaxweight()){//if passenger wont overload the elevator
        elevators[elevnum]->addPassengers(passengers[passnum - 1]->getWeight());//need to manually click off and click back to the elev pass is in to see the currweight change
        //(when have extra time) update the currweight label, and selected elevator, might be able to get away with just the elevator selected?
    }else{
        allactions += elevsafetyreq("overload",elevnum + 1);
        //overload button, have a passenger walk into the elevator with max weight being 0.
    }
    return allactions;
}

string ElevatorControlSystem::passwalkout(int passnum, int elevnum, int destflrnum){
    string allactions = "\nPassenger " + to_string(passnum) + " walks onto Floor " + to_string(destflrnum);
    elevators[elevnum - 1]->rmvPassengers(passengers[passnum - 1]->getWeight());//removes weight of pass from elevator
    return allactions;
}

string ElevatorControlSystem::safetyreq(string safetyissue){
    string allactions = "";
    int safefloor = 1;
    if (safetyissue == "fire" || "powerout"){
        //send all elevators to safe floor set
        //send safety messages to elevator to update its display and audio
        //once elevators reached safe floor return true
        //so it only plays once but doesnt show for each elev but is still updated
        allactions += "\nDisplay: Theres a " + safetyissue + " in the building, please disembark the elevator once the elevators reach the main floor.";
        allactions += "\nAudio: Theres a " + safetyissue + " in the building, please disembark the elevator once the elevators reach the main floor.";

        for(int i = 0; i < numofelevs;i++){//go through and make all elevators move to safe floor
            elevators[i]->setsafetymsg("Theres a " + safetyissue + " in the building, please disembark the elevator once the elevators reach the main floor.");
            allactions += "\nCar " + to_string(elevators[i]->getElevNum()) + " Display: Floor " + to_string(elevators[i]->getcurrflrnum());
            while (safefloor != elevators[i]->getcurrflrnum()){//make the elevator move up or down until it reaches the safe floor
                if(elevators[i]->getcurrflrnum() < i){// if the elevator is on a floor below the safe floor
                    allactions += elevators[i]->move("up");
                }else{// if the elevator is on a floor above the safe floor
                    allactions += elevators[i]->move("down");
                }
            }
            //once there open it rings and holds opens its doors
            allactions += elevators[i]->holdOpenDoor();
            elevators[i]->setsafetymsg("");//resets safetymsg
        }
        allactions += "\nAll Elevators have safely reached the main floor";
    }

    return allactions;//return all appended actions instead
}

string ElevatorControlSystem::elevsafetyreq(string safetyissue, int elevnum){
    string allactions = "";
    if(safetyissue == "obstacle"){
        obstaclecount += 1;
        if(obstaclecount < 5){//if interruppted less than 5 times
            allactions += elevators[elevnum]->interruptclose();
        }else{//holds open door and plays message
            allactions += elevators[elevnum]->holdOpenDoor();
            elevators[elevnum]->setsafetymsg("Theres a " + safetyissue + " blocking the door, please remove it.");
            allactions += elevators[elevnum]->displayandplaysafetymsg();
            elevators[elevnum]->setsafetymsg("");//resets safetymsg
        }

    }
    if(safetyissue == "overload"){
        allactions += "\n========Overload Activated=========";
        allactions += "\nPassenger walks out of Car " + to_string(elevnum);
    }
    if(safetyissue == "help"){

    }
    return allactions;
}

int ElevatorControlSystem::elevcenteredstrat(int serveflrnum){
    int idleelevnum = -1;
    for(int i = 0; i < numofelevs;i++){//inits and checks if theres an idle elev
        if (elevators[i]->checkidle() == true){
            idleelevnum = i;
            break;
        }
    }

    if (idleelevnum == -1){// if no idle elev found, all are in use
        return idleelevnum;
    }
    //else there is an idle elevator and we init it as the closest one,
    for(int i = 0; i < numofelevs;i++){//finds closest elevator, goes through again and checks if its idle AND closer than the current closest idle elevator
        if (elevators[i]->checkidle() == true && abs(elevators[i]->getcurrflrnum() - serveflrnum) < abs(elevators[idleelevnum]->getcurrflrnum() - serveflrnum)){
            idleelevnum = i;
        }
    }

    return idleelevnum;
}

/* to do*******
 * implement overload and help buttons
 * implement time allocstrat on flr req, add another param for current time, so if morning, lunch, or 5-6(done work)
 * add checks for currelevstrat set, if its in the times above, then use time strat, else, use elev center
 * figure out how to update selected elev and currweight when passenger walks into elev (last)
 */

