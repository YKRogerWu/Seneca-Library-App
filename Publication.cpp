/*
	===============================
	OOP244NDD PROJECT MS-4
	===============================
	Name   : Roger Wu
	ID     : 146740204
	Email  : ywu259@myseneca.ca
	Date   : 2021/11/29
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <iomanip>
#include <cstring>
#include "Publication.h"
using namespace std;
namespace sdds
{
	Publication::Publication() {
		m_title = nullptr;
		m_shelfId[0] = '\0';
		m_membership = 0;
		m_libRef = -1;
	}

	//Modifiers
	void Publication::set(int member_id) {
		m_membership = member_id;
	}
	void Publication::setRef(int value) {
		m_libRef = value;
	}
	void Publication::resetDate() {
		Date curDay;
		m_date = curDay;
	}

	//Queries
	char Publication::type()const {
		return 'P';
	}
	bool Publication::onLoan()const {
		return m_membership != 0;
	}
	Date Publication::checkoutDate()const {
		return m_date;
	}
	bool Publication::operator==(const char* title)const {
		return strstr(m_title, title) != NULL;
	}
	Publication::operator const char* ()const {
		return m_title;
	}
	int Publication::getRef()const {
		return m_libRef;
	}
	
	bool Publication::conIO(ios& io)const {
		return &io == &cin || &io == &cout;
	}
	ostream& Publication::write(ostream& os)const 
	{
		char title[SDDS_TITLE_WIDTH+1] = "";
		if (!(operator bool() && strlen(m_title) > 0)) {
			return os;
		}

		if (strlen(m_title) > SDDS_TITLE_WIDTH) {
			strncpy(title, m_title, SDDS_TITLE_WIDTH);
		} else {
			strcpy(title, m_title);
		}

		if (conIO(os) && operator bool()) {
			os << "| " << m_shelfId << " | ";
			os << setw(SDDS_TITLE_WIDTH) << left << setfill('.') << title;
			os << " | ";
			
			if (m_membership == 0) { os << " N/A "; }
			else { os << m_membership; }

			os << " | " << m_date << " |";
		}
		else if (!conIO(os)){
			os << type() << "\t" << m_libRef << "\t" << m_shelfId 
			<< "\t" << m_title << "\t" << m_membership << "\t" << m_date;
		}
		return os;
	}
	istream& Publication::read(istream& istr)
	{
		int membership = 0, libRef = -1;
		char shelfId[SDDS_SHELF_ID_LEN + 1] = "";
		char title[MAX_TITLE_LEN] = "";
		Date date;
		bool fail = false;

		/******** for user input ********/
		if (conIO(istr)) {
			//get shelfId
			istr.ignore();
			cout << "Shelf No: ";
			istr.get(shelfId, SDDS_SHELF_ID_LEN + 1);

			if (istr.peek() != '\n') {				
				fail = true;
				istr.setstate(ios::failbit);
			}
			//get title
			istr.ignore(255, '\n');
			cout << "Title: ";
			istr.get(title, MAX_TITLE_LEN, '\n');			

			//get date
			cout << "Date: ";
			date.Date::read(istr);
		}
		/******** for file loading ********/
		else {
			istr >> libRef;
			istr.ignore();
			istr.get(shelfId, SDDS_SHELF_ID_LEN + 1, '\t');
			istr.ignore();
			istr.get(title, MAX_TITLE_LEN, '\t');
			istr.ignore();
			istr >> membership;
			istr.ignore();
			date.Date::read(istr);
			//if (istr.peek() == EOF) istr.setstate(ios::failbit);
		}
		if(fail) istr.setstate(ios::failbit);

		if (!istr.fail()) {
			m_libRef = libRef;
			strcpy(m_shelfId, shelfId);

			m_title = new char[strlen(title) + 1];
			strcpy(m_title, title);

			m_membership = membership;
			m_date = date;
		}

		return istr;
	}
	Publication::operator bool() const {
		return (m_title && m_title[0] && m_shelfId  && m_shelfId[0]);
		//neither of the title or shelfId attributes is null or empty
	}

	//The rule of three:
	Publication::Publication(const Publication& src) {
		init(src);
	}
	Publication& Publication::operator=(const Publication& src) {
		if (this != &src) {
			delete[] m_title;
			init(src);
		}
		return *this;
	}
	Publication::~Publication() {
		delete[] m_title;
	}

	//user-defined function
	void Publication::init(const Publication& src) {
		//shallow copy for the non-resources
		strcpy(m_shelfId, src.m_shelfId);
		m_membership = src.m_membership;
		m_libRef = src.m_libRef;
		m_date = src.m_date;
		//allocate dynamic memory for the new resource
		if (src.m_title != nullptr) {
			m_title = new char[strlen(src.m_title) + 1];
			strcpy(m_title, src.m_title);
		}
		else m_title = nullptr;
	}

	ostream& operator<<(ostream& ostr, const Publication& right) {
		return right.write(ostr);		
	}
	istream& operator>>(istream& istr, Publication& right) {
		return right.read(istr);
	}
}