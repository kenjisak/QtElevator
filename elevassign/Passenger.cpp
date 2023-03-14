#include "Passenger.h"

Passenger::Passenger(const int& number,const int& weight){
    this->number = number;
    this->weight = weight;
}

Passenger::~Passenger(){
    delete this;
}

int Passenger::getNum(){
    return number;
}

int Passenger::getWeight(){
    return weight;
}
