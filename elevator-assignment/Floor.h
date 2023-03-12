
#ifndef FLOOR_H
#define FLOOR_H

#include <iostream>
#include <string>
#include <iomanip>

#include <Passenger.h>
#include <Button.h>

using namespace std;

class Floor {
		
	public:
		//constructor
		Floor(const int& name);

		//destructor
		~Floor();

		//getters
		int getflrnum();
		
		//other
		void notify(string direction);//btn notifies its pressed.
		void arrived(string direction);//elevator lets floor know its arrived
		
		void addPassengers();//when passenger walks in
		void rmvPassengers();//when passenger walks off

	private:
		int flrnum;
		Button* upBtn;
		Button* downBtn;
		Passenger* passengers[5];
};
#endif
