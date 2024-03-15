#ifndef _ASTEROIDA_HPP_
#define _ASTEROIDA_HPP_

#include <math.h>
#include <SFML/Graphics.hpp>
#include "Stale.hpp"

class Asteroida: public sf::Drawable, public sf::Transformable {
    static const float szybkosc[3];
    static const float promien[3];
    static const float poly[3];

    public:
        Asteroida(int poziom);
        Asteroida(sf::Vector2f pozycja, float kat, int poziom);
        ~Asteroida();

        bool czyZyje();
        int getPoziom();
        bool dotykaPunkt(sf::Vector2f punkt);
        void rozbij();
        void aktualizuj(float klatka);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        int poziom;
        bool czy_zyje;
        sf::Vector2f kierunek;
        sf::CircleShape ksztalt;
};
#endif
