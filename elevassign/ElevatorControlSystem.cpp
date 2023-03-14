#include "ElevatorControlSystem.h"

ElevatorControlSystem::ElevatorControlSystem(const int& elevnum,const int& flrnum,const int& maxweight,const int& passnum){

    this->numofflrs = flrnum;
    this->numofelevs = elevnum;
    obstaclecount = 0;

    floors = new Floor*[flrnum];
    for (int i = 0;i < flrnum;i++){
        floors[i] = new Floor(i+1);
    }

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

Floor** ElevatorControlSystem::getflrarr(){
    return floors;
}

Elevator** ElevatorControlSystem::getelevarr(){
    return elevators;
}

string ElevatorControlSystem::flrreq(string direction,int serveflrnum,int passnum){//when an up or down button from the floor is pressed, this finds an elev and sends it there
    //if up then find a non moving elev and make it move to the serveflrnum

    //go through and find an idle elevator thats possibly on the same floor already
//    for(int i = 0; i < numofelevs;i++){
//        if (elevators[i]->checkidle() == true && elevators[i]->getcurrflrnum() == serveflrnum){
//            idleelevnum = i;
//            break;
//        }
//    }
//    if(idleelevnum == -1){ //if elevator not found then find any idle elevator
//        for(int i = 0; i < numofelevs;i++){
//            if (elevators[i]->checkidle() == true){
//                idleelevnum = i;
//                break;
//            }
//        }
//    }
    string returnallactions = "";
    int idleelevnum = -1;//init so if no idle elevator found theyre all in use atm

    returnallactions += "\nFloor " + to_string(serveflrnum) + " " + direction + " button pressed by Passenger " + to_string(passnum) + " and lit.";
    for(int i = 0; i < numofelevs;i++){//go through and find an idle elevator this section is the alloc strategy of alloc a elev to a floor
        if (elevators[i]->checkidle() == true){
            idleelevnum = i;
            break;
        }
    }

    if (idleelevnum != -1){ // if an elevator is found
        elevators[idleelevnum]->setidle(false);//elevator is no longer idle and is moving/serving a passenger
        while (serveflrnum != elevators[idleelevnum]->getcurrflrnum()){//make the elevator move up or down until it reaches the floor that called one
            if(elevators[idleelevnum]->getcurrflrnum() < serveflrnum){// if the elevator is on a floor below the service floor
                returnallactions += elevators[idleelevnum]->move("up");
            }else{// if the elevator is on a floor above the service floor
                returnallactions += elevators[idleelevnum]->move("down");
            }
        }

        returnallactions += "\nCar " + to_string(elevators[idleelevnum]->getElevNum()) + " has arrived.";
        returnallactions += "\nFloor " + to_string(serveflrnum) + " " + direction + " button off.";
        returnallactions += elevators[idleelevnum]->openDoor();//change to only opens door, and closes door here after passenger walks in
        //have givenpassenger walk into elevator here elev[idle].addpassenger(pass[passgiven - 1].getweight),return is string that given passenger walked into elev
        //update elev selected dropdown to the elevator that arrived
        //update currweight of elev selected
        returnallactions += elevators[idleelevnum]->closeDoor();
    }else{//else we didnt find an elevator so just return -1
        returnallactions += "\nFloor " + to_string(serveflrnum) + " " + direction + " button off.";
        returnallactions += "\nAll Elevators in Use.";

    }
    return returnallactions;
}

string ElevatorControlSystem::safetyreq(string safetyissue){
    string returnallactions = "";
    int safefloor = 1;
    if (safetyissue == "fire" || "powerout"){
        //send all elevators to floor 1 as safe floor
        //send safety messages to elevator to update its display and audio
        //once elevators reached safe floor return true
        //so it only plays once but doesnt show for each elev but is still updated
        returnallactions += "\nDisplay: Theres a " + safetyissue + " in the building, please disembark the elevator once the elevators reach the main floor.";
        returnallactions += "\nAudio: Theres a " + safetyissue + " in the building, please disembark the elevator once the elevators reach the main floor.";

        for(int i = 0; i < numofelevs;i++){//go through and make all elevators move to safe floor
            elevators[i]->setsafetymsg("Theres a " + safetyissue + " in the building, please disembark the elevator once the elevators reach the main floor.");
            while (safefloor != elevators[i]->getcurrflrnum()){//make the elevator move up or down until it reaches the safe floor
                if(elevators[i]->getcurrflrnum() < i){// if the elevator is on a floor below the safe floor
                    returnallactions += elevators[i]->move("up");
                }else{// if the elevator is on a floor above the safe floor
                    returnallactions += elevators[i]->move("down");
                }
            }
            //once there open it rings and holds opens its doors
            returnallactions += elevators[i]->holdOpenDoor();
            elevators[i]->setsafetymsg("");//resets safetymsg
        }
        returnallactions += "\nAll Elevators have safely reached the main floor";
    }

    return returnallactions;//return all appended actions instead
}

string ElevatorControlSystem::elevsafetyreq(string safetyissue, int elevnum){
    string returnallactions = "";
    if(safetyissue == "obstacle"){
        obstaclecount += 1;
        if(obstaclecount < 5){//if interruppted less than 5 times
            returnallactions += elevators[elevnum]->interruptclose();
        }else{//holds open door and plays message
            returnallactions += elevators[elevnum]->holdOpenDoor();
            elevators[elevnum]->setsafetymsg("Theres a " + safetyissue + " blocking the door, please remove it.");
            returnallactions += elevators[elevnum]->displayandplaysafetymsg();
            elevators[elevnum]->setsafetymsg("");//resets safetymsg
        }

    }
    return returnallactions;
}
