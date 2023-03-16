
#ifndef PASSENGER_H
#define PASSENGER_H

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class Passenger {
		
	public:
		//constructor
        Passenger(const int& number, const int& weight);

		//destructor
		~Passenger();

		//getters
        int getNum();
		int getWeight();
		
	private:
        int number;
        int weight;
};
#endif
