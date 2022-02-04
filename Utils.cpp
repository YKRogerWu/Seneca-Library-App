/*
	===============================
	OOP244NDD PROJECT MS-4
	===============================
	Name   : Roger Wu
	ID     : 146740204
	Email  : ywu259@myseneca.ca
	Date   : 2021/11/29
*/
#include <iostream>
#include "Utils.h"
using namespace std;
namespace sdds {
	unsigned int foolproof(int upper_limit, int lower_limit) 
	{
		int selection;
		//receive user input
		while (!(cin >> selection) || selection < lower_limit || selection > upper_limit) {
			cout << "Invalid Selection, try again: ";
			//reset the stream state
			cin.clear();
			//discard previous input
			cin.ignore(2000, '\n');
		}
		return selection;
	}
}