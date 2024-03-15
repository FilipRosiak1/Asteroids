#include "Laser.hpp"

const float Laser::czaszycia = 1200.0f;
const float Laser::szybkosc = 0.9f;

Laser::Laser(sf::Vector2f pozycja, float kat):
    czy_zyje(true),
    pozostale_zycie(czaszycia),
    kierunek(cos(kat * DEG2RAD), sin(kat * DEG2RAD)) {
    setPosition(pozycja);
}

Laser::~Laser() {
}

bool Laser::czyZyje() {
    return czy_zyje;
}

void Laser::kill() {
    czy_zyje = false;
}

void Laser::aktualizuj(float klatka) {
    if (!czy_zyje) return;

    pozostale_zycie -= klatka;
    if (pozostale_zycie <= 0) czy_zyje = false;

    sf::Vector2f odleglosc = kierunek * szybkosc * klatka;
    move(odleglosc);
}

void Laser::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::Vertex linia[] = {
        sf::Vertex(getPosition()),
        sf::Vertex(getPosition() + (kierunek * 5.0f))
    };
    linia->color = sf::Color::Red;
    target.draw(linia, 2, sf::Lines, states);
}


