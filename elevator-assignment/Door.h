
#ifndef DOOR_H
#define DOOR_H

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class Door {
		
	public:
		//constructor
		Door();

		//destructor
		~Door();

		//getters
		bool getstatus();
		
		//other
        void open();//open the door
		void close();//close the door
	private:
        bool status;//true for open, false for closed
};
#endif
