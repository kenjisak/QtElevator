#include "ElevatorControlSystem.h"

ElevatorControlSystem::ElevatorControlSystem(const int& elevnum,const int& flrnum,const int& maxweight,const int& passnum){

    this->numofflrs = flrnum;
    this->numofelevs = elevnum;
    this->numofpass = passnum;
    obstaclecount = 0;

    elevators = new Elevator*[elevnum];
    for (int i = 0;i < elevnum;i++){
        elevators[i] = new Elevator(i+1,maxweight,flrnum);
    }

    passengers = new Passenger*[passnum + 1];//needed to +1 for the heavy passenger otherwise mem corruption
    for (int i = 0;i < passnum;i++){
        passengers[i] = new Passenger(i+1,100);//default of 100 lbs per passenger
    }
    passengers[passnum] = new Passenger(passnum,10000000);//heavy passenger for overload btn case
}

ElevatorControlSystem::~ElevatorControlSystem(){
    delete this;
}

Elevator** ElevatorControlSystem::getelevarr(){
    return elevators;
}

string ElevatorControlSystem::flrreq(string direction,int serveflrnum,int passnum, QTime currenttime, QComboBox* elevdropdown, QLineEdit* currweightdisplay){//when an up or down button from the floor is pressed, this finds an elev and sends it there
    string allactions = "";
    int idleelevnum;
    allactions += "\nPassenger "  + to_string(passnum) + " pressed Floor " + to_string(serveflrnum) + " " + direction + " button and lit.";

    decideallocstrat(currenttime);

    if (currstrat == "loadbalance"){    //any other time use load balancing for better maintenance for moving parts in the long run
        allactions += "\nLoad Balance Strategy is used as its normal hours.";
        idleelevnum = loadbalancestrat();
    }
    if (currstrat == "elevcentered"){//during rush hours, use elevecentered as itd be faster in servicing
        allactions += "\nElevator Centered Strategy is used as its rush hour.";
        idleelevnum = elevcenteredstrat(serveflrnum);
    }

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

        //update elev dropdown and curr weight
        elevdropdown->setCurrentIndex(idleelevnum);
        QString updatedweight = QString::number(elevators[idleelevnum]->getcurrweight());
        currweightdisplay->setText(updatedweight);


        allactions += elevators[idleelevnum]->closeDoor();
        elevators[idleelevnum]->setidle(true);//set it back to idle as its not moving anymore
        //might have to remove/change to show all elevators in use case.

    }else{//else we didnt find an elevator all are in use atm
        allactions += "\nFloor " + to_string(serveflrnum) + " " + direction + " button off.";
        allactions += "\nAll Elevators in Use.";

    }
    return allactions;
}

string ElevatorControlSystem::elevreq(int destflrnum, int elevnum, int passnum,QLineEdit* currweightdisplay){
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
    //update just currweight, since elev is already selected
    QString updatedweight = QString::number(elevators[elevnum - 1]->getcurrweight());
    currweightdisplay->setText(updatedweight);

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
        allactions += elevsafetyreq("overload",elevnum,passnum);//fixed
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

string ElevatorControlSystem::elevsafetyreq(string safetyissue, int elevnum, int passnum){
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
        elevators[elevnum]->setsafetymsg("Theres a " + safetyissue + " in carrying weight. Please reduce the load.");
        allactions += elevators[elevnum]->displayandplaysafetymsg();
        elevators[elevnum]->setsafetymsg("");//resets safetymsg
        allactions += "\nPassenger " + to_string(passnum) + "walks out of Car " + to_string(elevnum + 1);
    }
    if(safetyissue == "help"){
        allactions += "\n========Help Activated=========";
        allactions += bssconnection(elevnum,passnum);
    }
    return allactions;
}

string ElevatorControlSystem::bssconnection(int elevnum, int passnum){
    string allactions = "";
    allactions += "\nCar " + to_string(elevnum) + " Connected to Building Safety Services.";
    allactions += "\nWaiting for response for 5s from BSS and Passenger " + to_string(passnum);

    srand(time(NULL));
    int bssresponse = rand() % 2;
    int passresponse = rand() % 2;

    if (bssresponse == 0 && passresponse == 0){
        allactions += "\nNo response from Building Safety Services and Passenger " + to_string(passnum);
        allactions += call911(elevnum);
    }else if(passresponse == 0){//bss responds but pass doesnt
        allactions += "\nNo response from Passenger " + to_string(passnum);
        allactions += call911(elevnum);
    }else if(bssresponse == 0){//pass responds but bss doesnt
        allactions += "\nNo response from Building Safety Services.";
        allactions += call911(elevnum);
    }else{
        allactions += "\nBoth Building Safety Services and Passenger responded and are communicating.";
    }

    return allactions;
}

string ElevatorControlSystem::call911(int elevnum){
    return "\nCalling 911 for Car " + to_string(elevnum);
}


void ElevatorControlSystem::decideallocstrat(QTime currenttime){
    if(currenttime.hour() >= 7 && currenttime.hour() <= 8){//morning rush if 7 - 8:59 am,
        currstrat = "elevcentered";
    }else if(currenttime.hour() >= 12 && currenttime.hour() <= 13){//lunch rush if 12 - 1:59 pm,
        currstrat = "elevcentered";
    }else if(currenttime.hour() >= 16 && currenttime.hour() <= 17){//evening rush if 4 - 6:59 pm
        currstrat = "elevcentered";
    }else{//non rush hour time
        currstrat = "loadbalance";
    }
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

int ElevatorControlSystem::loadbalancestrat(){
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
    //else there is an idle elevator and we init it as the lowest load elev
    for(int i = 0; i < numofelevs;i++){//finds lowest load elevator, goes through again and checks if its idle AND lower load than the current lowest load idle elevator
        if (elevators[i]->checkidle() == true && elevators[i]->getcurrweight() < elevators[idleelevnum]->getcurrweight()){
            idleelevnum = i;
        }
    }

    return idleelevnum;
}

/* to do*******
 */
