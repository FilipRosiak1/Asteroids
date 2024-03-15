#include "Gra.hpp"
#include "Level.hpp"
#include "Stale.hpp"


Gra::Gra():
    uruchomiona(true) {
}

Gra::~Gra() {
    window.close();
}

int Gra::uruchom() {
    createWindow();

    Level level;
    sf::Clock clock;
    
    level.start();
    sf::Texture t;
    t.loadFromFile("D:\\Programy VSCode\\Projekt na obiektowe(NEWER)\\back_1.png");
    sf::Sprite s(t);
    while (uruchomiona) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return EXIT_SUCCESS;
            }
            level.onEvent(event);
        }

        window.clear(sf::Color::Black);
        level.aktualizuj(clock.restart().asMilliseconds());
        window.draw(s);
        level.show(window);
        window.display();
    }
    return EXIT_SUCCESS;
}

void Gra::createWindow() {
    if (window.isOpen())
        window.close();

    window.create(sf::VideoMode(APP_SZER, APP_WYS), APP_TYTUL, sf::Style::Close);
    window.setKeyRepeatEnabled(true);
    window.setFramerateLimit(APP_FPS);
}
