
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
		
		//other
        void walk(string direction,int elevnum);//into an specific elevator or off of specific elevator
		void press(int destflrnum);//passenger press a destination floor button
		void press(string btn);//passenger press a up or down, hold open or close door, help or fire buttons
		
	private:
        int number;
        int weight;
};
#endif
