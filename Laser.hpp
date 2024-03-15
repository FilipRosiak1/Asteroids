#ifndef _LASER_HPP
#define _LASER_HPP_

#include <math.h>
#include <SFML/Graphics.hpp>
#include "Stale.hpp"

class Laser: public sf::Drawable, public sf::Transformable {
    static const float czaszycia;
    static const float szybkosc;

    public:
        Laser(sf::Vector2f pozyja, float kat);
        ~Laser();

        bool czyZyje();
        void kill();
        void aktualizuj(float klatka);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        bool czy_zyje;
        float pozostale_zycie;
        sf::Vector2f kierunek;
};
#endif
