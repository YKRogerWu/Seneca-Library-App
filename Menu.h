// Final Project Milestone 5
// Menu Module
// File	Menu.h
// Version 2.0
// Author	Fardad Soleimanloo
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
// Fardad             2021/10/29	       Preliminary release
/////////////////////////////////////////////////////////////////

#ifndef SDDS_MENU_H__
#define SDDS_MENU_H__
#include <iostream>
namespace sdds {
    const unsigned int MAX_MENU_ITEMS = 20;
    class MenuItem {
        private:
            const char *content;

            MenuItem();
            MenuItem(const char *ctx);

            MenuItem(const MenuItem& MI) = delete;
            void operator =(const MenuItem& MI) = delete;

            ~MenuItem();

            operator bool();

            operator const char*()const;

            std::ostream& display(std::ostream& os = std::cout)const;
            friend std::ostream& operator <<(std::ostream& os, const MenuItem& MI);
        
            friend class Menu;
    };

    std::ostream& operator <<(std::ostream& os, const MenuItem& MI);

    class Menu {
        private:
            MenuItem title;
            MenuItem* items[MAX_MENU_ITEMS];

            unsigned int NoOfItems;
            unsigned int selection;

        public:
            Menu();
            Menu(const char *name);

            Menu(const Menu& M) = delete;
            void operator =(const Menu& M) = delete;

            ~Menu();

            unsigned int run();

            operator int();
            operator unsigned int();
            operator bool();
            unsigned int operator ~();

            const char * operator [](unsigned int)const;

            Menu& operator <<(const char *menuitemContent);

            std::ostream& suggestion(std::ostream& os = std::cout)const;
            std::ostream& display(std::ostream& os = std::cout)const;
    };

    std::ostream& operator <<(std::ostream& os, const Menu& M);
}
#endif /* SDDS_MENU_H__ */