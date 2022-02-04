// Final Project Milestone 5
// LibApp Module
// File	LibApp.cpp
// Version 2.0
// Author	Fardad Soleimanloo
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
// Fardad             2021/10/29		   Preliminary release
// Roger Wu           2021/12/2            update load() function for MS5-1
// Roger Wu           2021/12/3            update load() and removePublication() function for MS5-2
// Roger Wu           2021/12/5            update checkOutPub() function for MS5-3
// Roger Wu           2021/12/7            update returnPub() function about penalty for MS5-4
// Roger Wu           2021/12/7            update search() function for MS5-6
///////////////////////////////////////////////////////////////////////////////////////////////////

#define _CRT_SECURE_NO_WARNINGS
#include <iomanip>
#include <iostream>
#include <cstring>
#include "LibApp.h"
using namespace std;
namespace sdds {
    LibApp::LibApp() :  //initialize the following variables
                        m_mainMenu("Seneca Library Application"), 
                        m_exitMenu("Changes have been made to the data, what would you like to do?"),
                        m_pubSelMenu("Choose the type of publication:") {
        m_changed = false;
        m_llrn = 0;
        m_nolp = 0;

        m_mainMenu << "Add New Publication" << "Remove Publication" << "Checkout publication from library" << "Return publication to library";
        m_exitMenu << "Save changes and exit" << "Cancel and go back to the main menu";
        m_pubSelMenu << "Book" << "Publication";
    }

    LibApp::LibApp(const char *filename) : LibApp () {
        strcpy(m_pubFileName, filename);        
        load();
    }

    LibApp::~LibApp() {
        int i = 0;
        for (i = 0; i < m_nolp; i++) {
            if ('P' == m_ppa[i]->type()) {
                delete m_ppa[i];
            } 
            else if ('B' == m_ppa[i]->type()) {
                delete (Book *)m_ppa[i];
            }
        }
    }

    bool LibApp::confirm(const char* message) {
        Menu M((char *)message);
        M << "Yes";

        if (1 == M.run())
            return true;
        else
            return false;
    }

    void LibApp::load() {
        cout << "Loading Data" << endl;
        ifstream infile(m_pubFileName);
        char type{};
        int i;
        for (i = 0; infile; i++) {
            infile >> type;
            infile.ignore();
            if (infile) {
                if (type == 'P') {
                    (m_ppa[i] = new Publication) && (infile >> *m_ppa[i]) && (m_llrn = m_ppa[i]->getRef()) && (m_nolp++);
                }
                else if (type == 'B') {
                    (m_ppa[i] = new Book) && (infile >> *((Book *)m_ppa[i])) && (m_llrn = ((Book *)m_ppa[i])->getRef()) && (m_nolp++);
                }
            }
        }
        return;
    }

    void LibApp::save() {
        cout << "Saving Data" << endl;
        ofstream outfile(m_pubFileName);
        int i;
        for (i = 0; i < m_nolp; i++) {
            if (NULL == m_ppa[i])
                continue;
            
            if (0 == m_ppa[i]->getRef())
                continue;
            
            if ('B' == m_ppa[i]->type())
                outfile << *((Book *)m_ppa[i]) << endl;
            else if ('P' == m_ppa[i]->type())
                outfile << *m_ppa[i] << endl;
        }
        return;
    }

    void prnPub(Publication* p[], int size, int ref) {
        int i;
        for (i = 0; i < size; i++) 
        {
            if (ref == p[i]->getRef()) {
                if ('B' == p[i]->type()) {
                    cout << *((Book *)p[i]) << endl;
                } else {
                    cout << *p[i] << endl;
                }
                i = size; // Exit the loop.
            }
        }
    }

    int LibApp::search(char mode) {
        PublicationSelector ps("Select one of the following found matches:");

        unsigned int sel = 0;
        char key[256] = "";
        char type;
        sel = m_pubSelMenu.run();
        switch (sel) {
            case 1:
                type = 'B';
                break;
            case 2:
                type = 'P';
                break;
            default:
                break;
        };

        cout << "Publication Title: ";
        //cin >> key;        
        cin.getline(key, '\n'); //use getline to avoid redundant newline key in the buffer
        cin.ignore();

        int i;
        for (i = 0; i < m_nolp; i++) {
            if (m_ppa[i]->type() != type) //type = 'P'
                continue;

            if ('L' == mode && !m_ppa[i]->onLoan()) {
                continue;
            } else if ('A' == mode && m_ppa[i]->onLoan()) {
                continue;
            }
            if (strcmp(key,"") == 0) { //if enter nothing
                ps << m_ppa[i];                
            }
            else if (*m_ppa[i] == key) { 
                ps << m_ppa[i];
            }
        }

        if (ps) {
            ps.sort(); // sort them based on date and title
            int ref = ps.run(); // display the publications and select one
            if (ref) {
                prnPub(m_ppa, 100, ref);
                return ref;
            }
            else {
                cout << "Aborted!" << endl << endl;
                return -1;
            }
        }

        cout << "No matches found!" << endl;
        return 0;
    }

    void LibApp::returnPub() {
        cout << "Return publication to the library" << endl;
        int ref = 0;
        int i = 0;

        ref = search('L');      // Search on Loan
        if (0 >= ref) {
            return;
        }

        if (true == confirm("Return Publication?")) {
            /* Do returning */
            for (i = 0; i < m_nolp; i++) {
                if (ref == m_ppa[i]->getRef()) {
                    unsigned int loanDay = 0;
                    unsigned int penDay = 0;
                    
                    Date curDay;
                    loanDay = curDay - m_ppa[i]->checkoutDate();
                    penDay = loanDay - SDDS_MAX_LOAN_DAYS;                    
                    if (penDay > 0 && penDay < 200) {
                        cout.precision(2);
                        cout << "Please pay $" << fixed << setprecision(2) << (0.50* penDay) << " penalty for being " << penDay << " days late!" << endl;
                    }
                    m_ppa[i]->set(0);
                    m_changed = true;
                    cout << "Publication returned\n" << endl;
                    return;
                }
            }
        }

        cout << "Returning publication" << endl;
        cout << "Publication returned\n" << endl;
        m_changed = true;
        cout << endl;
        return;
    }

    void LibApp::newPublication(){
        if (m_nolp >= SDDS_LIBRARY_CAPACITY) {
            cout << "Library is at its maximum capacity!\n" << endl;
            return;
        }

        cout << "Adding new publication to the library" << endl;
        Publication *pubPtr = NULL;
        int sel = 0;
        bool valid;
        sel = m_pubSelMenu.run();
        if (1 == sel) {         // Book
            pubPtr = new Book;
            (NULL != pubPtr) && (cin >> *((Book *)pubPtr)) && (valid = *((Book *)pubPtr));
        } else if (2 == sel) {  // Publication
            pubPtr = new Publication;
            (NULL != pubPtr) && (cin >> *pubPtr) && (valid = *pubPtr);
        } else {
            cout << "Aborted!" << endl << endl;
            return;
        }

        if (true == confirm("Add this publication to the library?")) {
            if (valid) {
                m_ppa[m_nolp] = pubPtr;
                if (m_ppa[m_nolp]) {
                    m_llrn++;
                    m_ppa[m_nolp]->setRef(m_llrn);
                    m_nolp++;
                    m_changed = true;
                    cout << "Publication added" << endl;
                }
            } else {
                cout << "Failed to add publication!" << endl;
            }
        } else {
            cout << "Aborted!" << endl << endl;
        }

        cout << endl;
        return;
    }

    void LibApp::removePublication() {
        cout << "Removing publication from the library" << endl;
        int ref = 0;
        int i = 0;

        ref = search('M');    // Search all 
        if (0 >= ref) {
            return;
        }

        if (true == confirm("Remove this publication from the library?")) {
            /* Do removing */
            for (i = 0; i < m_nolp; i++) {
                if (ref == m_ppa[i]->getRef()) {
                    m_ppa[i]->setRef(0);
                    m_changed = true;
                    cout << "Publication removed" << endl << endl;
                    return;
                }
            }
        }

        cout << endl;
        return;
    }

    void LibApp::checkOutPub() {
        int ref = 0;
        int i = 0;
        unsigned int membership;

        cout << "Checkout publication from the library\n";
        ref = search('A');
        if (0 >= ref) {
            return;
        }

        if (true == confirm("Check out publication?")) {
            /* Do checking out */
            cout << "Enter Membership number: ";
            cin >> membership;
            cin.ignore();

            while (cin.fail() || 9999 >= membership || 100000 <= membership) {
                cout << "Invalid membership number, try again: ";
                cin >> membership;
            }
            
            for (i = 0; i < m_nolp; i++) {
                if (ref == m_ppa[i]->getRef()) {
                    m_ppa[i]->set(membership);
                    m_changed = true;
                    cout << "Publication checked out\n" << endl;
                    return;
                }
            }
        }
        cout << endl;
        return;
    }

    Publication *LibApp::getPub(int libRef) {
        int i;
        for (i = 0; i < m_nolp; i++) {
            if (libRef == m_ppa[i]->getRef()) {
                return m_ppa[i];
            }
        }
        return NULL;
    }

    int LibApp::run() {
        unsigned int sel = 0;
        bool done = false;
        do {
            sel = m_mainMenu.run();
            switch (sel)
            {
            case 1:
                newPublication();
                break;
            case 2:
                removePublication();
                break;
            case 3:
                checkOutPub();
                break;
            case 4:
                returnPub();
                break;
            default:
                if (!m_changed) {
                    done = true;
                } else {
                    sel = m_exitMenu.run();
                    if (1 == sel) {
                        save();
                        done = true;
                    } else if (0 == sel) {
                        if (confirm("This will discard all the changes are you sure?")) {
                            done = true;
                        } else {
                            continue;
                        }
                    } else if (2 == sel) {
                        cout << endl;
                        continue;
                    }
                }
                break;
            };
        } while (!done);

        cout << endl;
        cout << "-------------------------------------------" << endl;
        cout << "Thanks for using Seneca Library Application" << endl;

        return 0;
    }
}