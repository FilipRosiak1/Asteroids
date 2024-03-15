#ifndef _LEVEL_HPP_
#define _LEVEL_HPP_

#include "Laser.hpp"
#include "Asteroida.hpp"
#include "Statek.hpp"
#include <SFML/Graphics.hpp>

class Level {
    public:
        Level();
        ~Level();
        void onEvent(const sf::Event& event);
        void start();
        void show(sf::RenderTarget& target);
        void aktualizuj(float klatka);

    private:
        Statek statek;
        std::vector<Laser> lasery;
        std::vector<Asteroida> asteroidy;
};

#endif
