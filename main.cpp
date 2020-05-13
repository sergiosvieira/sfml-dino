#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <functional>
#include <memory>
#include <iostream>
#include <cmath>

static const int kWidth = 800;
static const int kHeight = 480;
static const int kFPS = 30;
static const sf::Time kUpdateMs = sf::seconds(1.f/static_cast<float>(kFPS));

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
    sf::Sprite;

using Draw = std::function<void(RenderWindow&)>;
using Update = std::function<void(float)>;

void loop(RenderWindow& window,
          Update update = nullptr,
          Draw draw = nullptr) {
    Clock clock;
    Time elapsed = clock.restart();
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        elapsed += clock.restart();
        while (elapsed >= kUpdateMs) {
            if (update) update(kUpdateMs.asSeconds());
            elapsed -= kUpdateMs;
        }
        window.clear();
        if (draw) draw(window);
        window.display();
    }
}

class Dino {
    Texture tex01, tex02;
    Sprite stand, crouch;
public:
    Dino(const std::string& filename1,
         const std::string& filename2) {
        tex01.loadFromFile(filename1);
        stand.setTexture(tex01);
        stand.setTextureRect({0, 0, 48, 45});
        tex02.loadFromFile(filename2);
        crouch.setTexture(tex02);
    }
    void update(float dt) {

    }
    void render(RenderWindow& rw) {
        rw.draw(stand);
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(kWidth, kHeight), "Dino Game");
    Dino p1("dino-01.png", "dino-02.png");
    Update update = [&](float dt) {
    };
    Draw draw = [&](RenderWindow& rw) {
        p1.render(rw);
    };
    loop(window, update, draw);
    return 0;
}
