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
#include "Book.h"
using namespace std;
namespace sdds
{
    Book::Book() {
        m_author = NULL;
    }

    void Book::set(int member_id) {
        // - invoke the set of the base class to set the member id
        // - reset the date to the current date.
        Publication::set(member_id);
        this->resetDate();
        return;
    }

    char Book::type() const {
        return 'B';
    }

    Book::operator bool() const {
        // return true if the author's name exists and is not empty 
        // and the base class's operator bool() has returned true.
        return (Publication::operator bool() && m_author != NULL && m_author[0]);
    }

    istream& Book::read(istream& istr) {
		char author[MAX_AUTHOR_LEN + 1] = "";
		bool fail = false;

		// Call base class read
		Publication::read(istr);
		if (conIO(istr)) {
			//get author
			cout << "Author: ";
			istr.get(author, MAX_AUTHOR_LEN, '\n');			
        }
		else {
			istr.get(author, MAX_AUTHOR_LEN, '\n');
			if (istr.peek() == EOF) istr.setstate(ios::failbit);
		}
		
		if(fail) istr.setstate(ios::failbit);

		if (!istr.fail()) {
			m_author = new char[strlen(author) + 1];
			strcpy(m_author, author);
		}

        return istr;
    }

    ostream& Book::write(ostream& os)const {
		char author[SDDS_AUTHOR_WIDTH+1] = "";

		if (!(operator bool() && strlen(m_author) > 0)) {
			return os;
		}

		if (strlen(m_author) > SDDS_AUTHOR_WIDTH) {
			strncpy(author, m_author, SDDS_AUTHOR_WIDTH);
		} else {
			strcpy(author, m_author);
		}

        Publication::write(os);
		if (conIO(os) && operator bool()) {
   			os << " " ;
			os << setw(SDDS_AUTHOR_WIDTH) << left << setfill(' ') << author;
			os << " |";
		}
		else if (!conIO(os)) {
			os << '\t' << m_author;
		}
        return os;
    }

	void Book::init(const Book& src) {
		//allocate dynamic memory for the new resource
		if (src.m_author != nullptr) {
			m_author = new char[strlen(src.m_author) + 1];
			strcpy(m_author, src.m_author);
		}
		else m_author = nullptr;
	}

	Book& Book::operator=(const Book& src) {
        Publication::operator=(src);
		if (this != &src) {
			delete[] m_author;
			init(src);
		}
		return *this;
	}

	Book::~Book() {
		delete[] m_author;
	}

    ostream& operator<<(ostream& ostr, const Book& right) {
		return right.write(ostr);		
	}
	istream& operator>>(istream& istr, Book& right) {
		return right.read(istr);
	}
}