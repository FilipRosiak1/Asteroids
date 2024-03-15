#include "Level.hpp"

Level::Level() {
    for (int i=0; i < 5; i++) {
        Asteroida a(0);
        asteroidy.push_back(a);
    }
}

Level::~Level() {
}

void Level::onEvent(const sf::Event& event) {
    statek.onEvent(event);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        Laser laser(statek.getPosition(), statek.getRotation());
        lasery.push_back(laser);
    }
}

void Level::start() {
}

void Level::show(sf::RenderTarget& target) {
    target.draw(statek);

    for(std::vector<Laser>::iterator it = lasery.begin(); it != lasery.end(); ++it)
        target.draw(*it);

    for(std::vector<Asteroida>::iterator it = asteroidy.begin(); it != asteroidy.end(); ++it)
        target.draw(*it);
}

void Level::aktualizuj(float klatka) {
    statek.aktualizuj(klatka);
    std::vector<Laser>::iterator start_lasery = lasery.begin();
    while (start_lasery != lasery.end()) {
        if (start_lasery->czyZyje()) {
            start_lasery->aktualizuj(klatka);
            ++start_lasery;
        } else
            start_lasery = lasery.erase(start_lasery);
    }

    std::vector<Asteroida>::iterator start_asteroidy = asteroidy.begin();
    while (start_asteroidy != asteroidy.end()) {
        if (start_asteroidy->czyZyje()) {
            start_asteroidy->aktualizuj(klatka);
            ++start_asteroidy;
        } else
            start_asteroidy = asteroidy.erase(start_asteroidy);
    }

    std::vector<Asteroida> nowe_asteroidy;
    
    if(rand()%320 == 0) {
    Asteroida b(rand()%3);
    nowe_asteroidy.push_back(b);
    }

    start_asteroidy = asteroidy.begin();
    while (start_asteroidy != asteroidy.end()) {
        start_lasery = lasery.begin();
        while (start_lasery != lasery.end()) {
            if (!start_lasery->czyZyje()) {
                ++start_lasery;
                continue;
            }

            if (start_asteroidy->dotykaPunkt(start_lasery->getPosition())){
                start_lasery->kill();
                start_asteroidy->rozbij();

                if (start_asteroidy->czyZyje()) {
                    for(int i = 0; i<rand()%2 + 1; i++) {
                    sf::Vector2f pozycja = start_asteroidy->getPosition();
                    float kat = rand() % 360;
                    Asteroida a(pozycja, kat, start_asteroidy->getPoziom());
                    nowe_asteroidy.push_back(a);
                    }
                }
                break;
            }
            ++start_lasery;
        }
        ++start_asteroidy;
    }
    asteroidy.insert(asteroidy.end(), nowe_asteroidy.begin(), nowe_asteroidy.end());
}