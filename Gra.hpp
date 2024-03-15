#ifndef _GRA_HPP_
#define _GRA_HPP_

#include <SFML/Graphics.hpp>

class Gra {
    public:
        Gra();
        ~Gra();
        int uruchom();

    private:
        void createWindow();
        sf::RenderWindow window;
        bool uruchomiona;
};

#endif
