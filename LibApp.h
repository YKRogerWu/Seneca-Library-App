// Final Project Milestone 5
// LibApp Module
// File	LibApp.cpp
// Version 2.0
// Author	Fardad Soleimanloo
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
// Fardad             2021/10/29		       Preliminary release
/////////////////////////////////////////////////////////////////

#ifndef SDDS_LIBAPP_H
#define SDDS_LIBAPP_H
#include <iostream>
#include <fstream>

using namespace std;
#include "Menu.h"
#include "Book.h"
#include "Publication.h"
#include "PublicationSelector.h"
namespace sdds {
   class LibApp {
      private:
         bool m_changed;

         Menu m_mainMenu;
         Menu m_exitMenu;
         Menu m_pubSelMenu;

         char m_pubFileName[256];
         Publication *m_ppa[SDDS_LIBRARY_CAPACITY];
         
         int m_nolp;
         int m_llrn;

         bool confirm(const char* message);

         void load();  // prints: "Loading Data"<NEWLINE>
         void save();  // prints: "Saving Data"<NEWLINE>
         int search(char mode);  // prints: "Searching for publication"<NEWLINE>


         void returnPub();    /*  Calls the search() method.
                                 prints "Returning publication"<NEWLINE>
                                 prints "Publication returned"<NEWLINE>
                                 sets m_changed to true;
                              */
         
         void newPublication();
         void removePublication();
         void checkOutPub();

      public:
         LibApp();
         LibApp(const char *filename);

         ~LibApp();

         Publication *getPub(int libRef);
         int run();
   };
}
#endif // !SDDS_LIBAPP_H



