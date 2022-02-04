/*
	===============================
	OOP244NDD PROJECT MS-4
	===============================
	Name   : Roger Wu
	ID     : 146740204
	Email  : ywu259@myseneca.ca
	Date   : 2021/11/29
*/
#ifndef SDDS_Book_H_
#define SDDS_Book_H_
#include "Publication.h"

using namespace std;

namespace sdds {
    class Book : public Publication {
        private:
            char *m_author;
        
        public:
            /* Constructor */
            Book();

            /* Rule of three */
		    Book(const Book&);
		    Book& operator=(const Book&);
            virtual ~Book();

	        //Modifiers
		    virtual void set(int member_id);

	        //Queries
		    virtual char type()const;

	        //virtual function implementation
		    operator bool()const;

		    ostream& write(ostream& os)const;
		    istream& read(istream& istr);

		protected:
			void init(const Book&);

		friend ostream& operator<<(ostream&, const Book&);
		friend istream& operator>>(istream&, Book&);
    };
}

#endif /* SDDS_Book_H_ */