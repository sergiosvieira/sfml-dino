#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <functional>
#include <memory>
#include <iostream>
#include <cmath>
#include <random>

#include "game.h"
#include "animation.h"
#include "game-consts.h"
#include "pterodactyl.h"
#include "ground.h"
#include "cloud.h"
#include "cactus.h"
#include "player.h"

using sf::RenderWindow,
    sf::VideoMode,
    sf::Event,
    sf::Color,
    sf::Vector2f,
    sf::Font,
    sf::Text,
    sf::FloatRect,
    sf::Time,
    sf::Clock,
    sf::Texture,
    sf::IntRect,
    sf::Sprite,
    sf::Vector2i;

using Render = std::function<void(RenderWindow&)>;
using Update = std::function<void(float)>;
using KeyPressed = std::function<void(sf::Event::KeyEvent&)>;
using KeyReleased = std::function<void()>;

void loop(RenderWindow& window,
          Update update = nullptr,
          Render render = nullptr,
          KeyPressed keypressed = nullptr,
          KeyReleased keyreleased = nullptr) {
    Clock clock;
    Time elapsed = clock.restart();
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {
                if (keypressed != nullptr) keypressed(event.key);
            } else if (event.type == sf::Event::KeyReleased) {
                if (keyreleased != nullptr) keyreleased();
            }
        }
        elapsed += clock.restart();
        while (elapsed >= kUpdateMs) {
            if (update) update(kUpdateMs.asSeconds());
            elapsed -= kUpdateMs;
        }
        window.clear({247, 247, 247, 255});
        if (render) render(window);
        window.display();
    }
}

int main() {
    Game game;
    sf::RenderWindow window(sf::VideoMode(kWidth, kHeight), "Dino Game");
    Player p1;
    Update update = [&](float dt) {
        game.update(dt);
        p1.update(dt);
    };
    Render render = [&](RenderWindow& rw) {
        game.render(rw);
        p1.render(rw);
    };
    KeyPressed keyp = [&](sf::Event::KeyEvent& k) {
        p1.keyPressed(k);
    };
    KeyReleased keyr = [&]() {
        p1.keyReleased();
    };
    loop(window, update, render, keyp, keyr);
    return 0;
}
