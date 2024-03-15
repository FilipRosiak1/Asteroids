#ifndef _STATEK_HPP_
#define _STATEK_HPP_

#include <math.h>
#include <SFML/Graphics.hpp>
#include "Stale.hpp"

class Statek: public sf::Drawable, public sf::Transformable {
    static const float przyspieszenie;
    static const float max_szybkosc;
    static const float szybkosc_obrotu;

    public:
        Statek();
        ~Statek();

        void reset();
        void onEvent(const sf::Event& event);
        void aktualizuj(float klatka);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;


    private:
        sf::Vector2f szybkosc;
        sf::ConvexShape ksztalt;
        int ruch_poz, ruch_pion;
};
#endif
