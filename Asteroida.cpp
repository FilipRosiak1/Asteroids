#include "Asteroida.hpp"

const float Asteroida::szybkosc[3] = {0.03f, 0.05f, 0.07f};
const float Asteroida::promien[3] = {40.0f, 20.0f, 10.0f};
const float Asteroida::poly[3] = {9, 6, 5};


Asteroida::Asteroida(int poziom):
    czy_zyje(true),
    poziom(poziom) {
    int kat = rand() % 360;
    kierunek = sf::Vector2f(cos(kat * DEG2RAD), sin(kat * DEG2RAD));

    int x = rand() % APP_SZER;
    int y = rand() % APP_WYS;
    sf::Vector2f pozycja(x, y);
    setPosition(pozycja);
    ksztalt.setPointCount(poly[poziom]);
    ksztalt.setRadius(promien[poziom]);
    ksztalt.setFillColor(sf::Color(120, 120, 120, 255));
    ksztalt.setOutlineColor(sf::Color::White);
    ksztalt.setOutlineThickness(1);
    ksztalt.setOrigin(promien[poziom], promien[poziom]);
}

Asteroida::Asteroida(sf::Vector2f pozycja, float kat, int poziom):
    czy_zyje(true),
    poziom(poziom) {
    kierunek = sf::Vector2f(cos(kat * DEG2RAD), sin(kat * DEG2RAD));

    setPosition(pozycja);
    ksztalt.setPointCount(poly[poziom]);
    ksztalt.setRadius(promien[poziom]);
    ksztalt.setFillColor(sf::Color(120, 120, 120, 255));
    ksztalt.setOutlineColor(sf::Color::White);
    ksztalt.setOutlineThickness(1);
    ksztalt.setOrigin(promien[poziom], promien[poziom]);
}

Asteroida::~Asteroida() {
}

bool Asteroida::czyZyje() {
    return czy_zyje;
}

int Asteroida::getPoziom() {
    return poziom;
}

bool Asteroida::dotykaPunkt(sf::Vector2f punkt) {
    float ax = getPosition().x;
    float ay = getPosition().y;

    float px = punkt.x;
    float py = punkt.y;

    float sqrOdleglosc = ((ax - px) * (ax - px)) + ((ay - py) * (ay - py));
    float sqrPromien = promien[poziom] * promien[poziom];

    return (sqrOdleglosc <= sqrPromien);
}

void Asteroida::rozbij() {
    poziom++;

    if (poziom > 2) {
        czy_zyje = false;
        return;
    }
    ksztalt.setPointCount(poly[poziom]);
    ksztalt.setRadius(promien[poziom]);
    ksztalt.setOrigin(promien[poziom], promien[poziom]);
    float kat = rand() % 360;
    kierunek = sf::Vector2f(cos(kat * DEG2RAD), sin(kat * DEG2RAD));
    
}

void Asteroida::aktualizuj(float klatka) {
    if (!czy_zyje) return;

    sf::Vector2f odleglosc = kierunek * szybkosc[poziom] * klatka;
    move(odleglosc);

    sf::Vector2f pozycja = getPosition();

    if (pozycja.x < -promien[poziom])
        pozycja.x = APP_SZER;
    else if (pozycja.x > APP_SZER)
        pozycja.x = 0.0f;

    if (pozycja.y < -promien[poziom])
        pozycja.y = APP_WYS;
    else if (pozycja.y > APP_WYS)
        pozycja.y = 0.0f;
    setPosition(pozycja);
}

void Asteroida::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(ksztalt, states);
}
