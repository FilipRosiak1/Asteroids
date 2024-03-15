#include "Statek.hpp"

const float Statek::przyspieszenie = 1.0f;
const float Statek::max_szybkosc = 2.0f;
const float Statek::szybkosc_obrotu = 0.3f;
const float skala = 1.5;
Statek::Statek() {
    ksztalt.setPointCount( 20 );
    ksztalt.setPoint(0, sf::Vector2f(skala*15.0f,skala*2.0f));
    ksztalt.setPoint(1, sf::Vector2f(skala*-6.0f,skala*4.0f));
    ksztalt.setPoint(2, sf::Vector2f(skala*-6.0f,skala*6.0f));
    ksztalt.setPoint(3, sf::Vector2f(skala*6.0f,skala*7.5f));
    ksztalt.setPoint(4, sf::Vector2f(skala*6.0f,skala*10.0f));
    ksztalt.setPoint(5, sf::Vector2f(skala*-10.0f,skala*10.0f));
    ksztalt.setPoint(6, sf::Vector2f(skala*-13.0f,skala*4.0f));
    ksztalt.setPoint(7, sf::Vector2f(skala*-15.0f,skala*4.0f));
    ksztalt.setPoint(8, sf::Vector2f(skala*-15.0f,skala*2.0f));
    ksztalt.setPoint(9, sf::Vector2f(skala*-13.0f,skala*2.0f));
    ksztalt.setPoint(10, sf::Vector2f(skala*-13.0f,skala*-2.0f));
    ksztalt.setPoint(11, sf::Vector2f(skala*-15.0f,skala*-2.0f));
    ksztalt.setPoint(12, sf::Vector2f(skala*-15.0f,skala*-4.0f));
    ksztalt.setPoint(13, sf::Vector2f(skala*-13.0f,skala*-4.0f));
    ksztalt.setPoint(14, sf::Vector2f(skala*-10.0f,skala*-10.0f));
    ksztalt.setPoint(15, sf::Vector2f(skala*6.0f,skala*-10.0f));
    ksztalt.setPoint(16, sf::Vector2f(skala*6.0f,skala*-7.5f));
    ksztalt.setPoint(17, sf::Vector2f(skala*-6.0f,skala*-6.0f));
    ksztalt.setPoint(18, sf::Vector2f(skala*-6.0f,skala*-4.0f));
    ksztalt.setPoint(19, sf::Vector2f(skala*15.0f,skala*-2.0f));


    ksztalt.setFillColor(sf::Color::White);
    ksztalt.setOutlineColor(sf::Color::Black);
    ksztalt.setOutlineThickness(1);
    ksztalt.setPosition(0.0f, 0.0f);

    ruch_poz = 0;
    ruch_pion = 0;

    reset();
}

Statek::~Statek() {
}

void Statek::reset() {
    setPosition(APP_SZER / 2, APP_WYS / 2);
    setRotation(0.0f);
    szybkosc.x = 0.0f;
    szybkosc.y = 0.0f;
}

void Statek::onEvent(const sf::Event& event) {
    ruch_poz = 0;
    ruch_pion = 0;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        ruch_pion = 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        ruch_poz = 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        ruch_pion = -1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        ruch_poz = -1;
}

void Statek::aktualizuj(float klatka) {
    if (ruch_poz != 0) {
        rotate(ruch_poz * szybkosc_obrotu * klatka);
    }

    if (ruch_pion != 0) {
        float obrot = getRotation();
        float szybkosc_x = cos(obrot * DEG2RAD);
        float szybkosc_y = sin(obrot * DEG2RAD);

        szybkosc.x += ruch_pion * przyspieszenie * klatka * szybkosc_x / 1000;
        szybkosc.y += ruch_pion * przyspieszenie * klatka * szybkosc_y / 1000;
        if ((szybkosc.x * szybkosc.x) > (max_szybkosc * max_szybkosc))
            szybkosc.x = szybkosc.x > 0 ? max_szybkosc : -max_szybkosc;
        if ((szybkosc.y * szybkosc.y) > (max_szybkosc * max_szybkosc))
            szybkosc.y = szybkosc.y > 0 ? max_szybkosc : -max_szybkosc;
    }
    move(szybkosc);

    sf::Vector2f pozycja = getPosition();

    if (pozycja.x < -10.0f)
        pozycja.x = APP_SZER;
    else if (pozycja.x > APP_SZER)
        pozycja.x = 0.0f;

    if (pozycja.y < -10.0f)
        pozycja.y = APP_WYS;
    else if (pozycja.y > APP_WYS)
        pozycja.y = 0.0f;
    setPosition(pozycja);
}

void Statek::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(ksztalt, states);
}