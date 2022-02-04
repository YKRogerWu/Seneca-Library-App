/*
	===============================
	OOP244NDD PROJECT MS-4
	===============================
	Name   : Roger Wu
	ID     : 146740204
	Email  : ywu259@myseneca.ca
	Date   : 2021/11/29
*/
#ifndef SDDS_Publication_H_
#define SDDS_Publication_H_
#include "Lib.h"
#include "Date.h"
#include "Streamable.h"

using namespace std;
namespace sdds {
	class Publication {
		char* m_title;		//max length = 255
		char m_shelfId[SDDS_SHELF_ID_LEN + 1];//Hold the location of the publication in the library
		int m_membership;	//5 digits; "0" means available
		int m_libRef;		//uniquely identify each publication
		Date m_date;
	public:
		Publication();

	//Modifiers
		virtual void set(int member_id);
		void setRef(int value);
		void resetDate();	
	//Queries
		virtual char type()const;
		bool onLoan()const;
		Date checkoutDate()const;
		bool operator==(const char* title)const;
		operator const char* ()const;
		int getRef()const;
	//virtual function implementation
		bool conIO(ios& io)const;
		ostream& write(ostream& os)const;
		istream& read(istream& istr);
		operator bool()const;
	//Rule of three
		Publication(const Publication&);
		Publication& operator=(const Publication&);
		virtual ~Publication();
	//user-defined function
	protected:
		void init(const Publication&);

	friend ostream& operator<<(ostream&, const Publication&);
	friend istream& operator>>(istream&, Publication&);
	};
}
#endif // !SDDS_Publication_H_

