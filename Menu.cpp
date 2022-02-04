// Final Project Milestone 5
// Menu Module
// File	Menu.cpp
// Version 2.0
// Author	Fardad Soleimanloo
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
// Fardad             2021/10/29		       Preliminary release
/////////////////////////////////////////////////////////////////

#define _CRT_SECURE_NO_WARNINGS
#include <iomanip>
#include <iostream>
#include <cstring>
using namespace std;
#include "Menu.h"
namespace sdds {

    MenuItem::MenuItem() {
        content = NULL;
    }

    MenuItem::MenuItem(const char *ctx) {
        content = ctx;
    }

    MenuItem::~MenuItem() {
        content = NULL;
    }

    MenuItem::operator bool() {
        if (content)
            return (0 != strlen(content));
        else
            return false;
    }

    MenuItem::operator const char*()const {
        return content;
    }
 
    ostream& MenuItem::display(ostream& os)const {
        if (strlen(content))
            os << content;
        return os;
    }

    ostream& operator<<(ostream& os, const MenuItem& MI) {
      return MI.display(os);
   }

    Menu::Menu() {
        title.content = NULL;
        for (unsigned int idx = 0; idx < MAX_MENU_ITEMS; idx ++) {
            items[idx] = NULL;
        }
        NoOfItems = 0;
    }

    Menu::Menu(const char *name) {
        title.content = (char *)name;

        for (unsigned int idx = 0; idx < MAX_MENU_ITEMS; idx ++) {
            items[idx] = NULL;
        }
        NoOfItems = 0;
    }

    Menu::~Menu() {
        title.content = NULL;

        for (unsigned int idx = 0; idx < MAX_MENU_ITEMS; idx ++) {
            if (items[idx] && items[idx]->content)
                delete (items[idx]);
        }
        NoOfItems = 0;
    }

    Menu::operator int() {
        return (int) NoOfItems;
    }

    Menu::operator unsigned int() {
        return (unsigned int) NoOfItems;
    }

    Menu::operator bool() {
        return (0 != NoOfItems);
    }

    unsigned int Menu::run() {
        display();
        cout << "> ";
        cin >> selection;

        while (cin.fail() || 0 > selection || selection > NoOfItems) {

            if (cin.fail()) {
                cin.clear();
            }
            cin.ignore(80, '\n');

            cout << "Invalid Selection, try again: ";
            cin >> selection;
        }

        return selection;
    }

    const char * Menu::operator [](unsigned int idx)const {
        if (idx > NoOfItems)
            return items[idx%NoOfItems]->content;
        else
            return items[idx]->content;
    }

    unsigned int Menu::operator ~() {
        return run();
    }

    ostream& Menu::suggestion(ostream& os)const {
        if (title)
            os << title.content;
        return os;
    }

    ostream& Menu::display(ostream& os)const {
        if (title)
            os << title.content << endl;
        
        for (unsigned int idx = 0; idx < (unsigned int) NoOfItems; idx ++) {
            os << setfill(' ') << setw(2) << right << idx + 1 << "- " ;
            os << items[idx]->content << endl;
        }
        os << setfill(' ') << setw(2) << "0" << "- Exit" << endl; 
        return os;
    }

    ostream& operator <<(ostream& os, const Menu& M) {
      return M.suggestion(os);
    }

    Menu& Menu::operator <<(const char *menuitemContent) {
        if (NoOfItems >= MAX_MENU_ITEMS) {
            return (*this);
        }

        MenuItem *MIP = new MenuItem(menuitemContent);
        items[NoOfItems] = MIP;
        this->NoOfItems++;
        
        return (*this);
    }

}