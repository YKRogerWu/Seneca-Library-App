
/*Streamable interface*/
#ifndef SDDS_STREAMABLE_H_
#define SDDS_STREAMABLE_H_

#include <iostream>
using namespace std;
namespace sdds {
	class Streamable {
		virtual ostream& write(ostream&)const = 0;
		virtual istream& read(istream&) = 0;
		virtual bool conIO(ios&)const = 0;
		virtual operator bool()const = 0;
	/*	Boolean conversion overloads of this method will 
		return if the Streamable object is in a valid state or not.	*/
		virtual ~Streamable();
		//helper functions
		friend ostream& operator<<(ostream&, const Streamable&);
		friend istream& operator>>(istream&, Streamable&);
	};
}
#endif // !SDDS_STREAMABLE_H_

