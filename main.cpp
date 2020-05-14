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
    sf::Sprite,
    sf::Vector2i;

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
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

        }
        elapsed += clock.restart();
        while (elapsed >= kUpdateMs) {
            if (update) update(kUpdateMs.asSeconds());
            elapsed -= kUpdateMs;
        }
        window.clear({247, 247, 247, 255});
        if (draw) draw(window);
        window.display();
    }
}

void print(const IntRect& rect) {
    std::cout << "{" << rect.top << ", "
              << rect.left << ", "
              << rect.width << ", "
              << rect.height << "}" << std::endl;
}

class Animate {
    Clock clock;
    Time elapsed;
    Time updateTime;
    Texture tex;
    Sprite sprite;
    int start; // first sprite
    int end; // last sprite
    int current; // current sprite
    Vector2i irect = {0, 0};
public:
    Animate (const std::string& filename,
             int start, int end, int current, Vector2i size, Time updateTime):
        start(start), end(end), current(current), irect(size), updateTime(updateTime){
        tex.loadFromFile(filename);
        sprite.setTexture(tex);
    }
    void setCurrentFrame(int value) {
        current = value;
    }
    void setPosition(float x, float y) {
        sprite.setPosition(x, y);
    }
    Sprite& getSprite() {
        return sprite;
    }
    void update() {
        elapsed += clock.restart();
        if (elapsed >= updateTime) {
            IntRect textureRect = {current * irect.x, 0, irect.x, irect.y};
            sprite.setTextureRect(textureRect);
            ++current;
            if (current > end) current = start;
            elapsed -= updateTime;
        }
    }
};

class Ground {
    Texture tex;
    Sprite sprite;
    Ground() {
        tex.loadFromFile("ground.png");
    }
};

class Pterodactyl {
public:
    Animate animate{"ptero.png", 0, 1, 0, {46, 35}, sf::seconds(1.f/5.f)};
    Pterodactyl() {
    }
    void update(float dt) {

    }
    void render(RenderWindow& rw) {
        animate.update();
        rw.draw(animate.getSprite());
    }
};

class Dino {
public:
    enum class State {Idle, Standing, Crouched, Jumping};
    State currentState = State::Idle;
    Time animateSpeed = sf::seconds(1.f/15.);
    Animate standAnimate{"dino-01.png", 1, 3, 1, {48, 45}, animateSpeed};
    Animate crounchAnimate{"dino-02.png", 0, 1, 0, {57, 28}, animateSpeed};
    Dino() {
        idleState();
    }
    void idleState() {
        currentState = State::Idle;
        standAnimate.setCurrentFrame(0);
        standAnimate.getSprite().setTextureRect({0, 0, 48, 45});
    }
    void JumpState() {
        currentState = State::Jumping;
        standAnimate.setCurrentFrame(1);
        standAnimate.getSprite().setTextureRect({48, 0, 48, 45});
    }
    void setPosition(float x, float y) {
        standAnimate.setPosition(x, y);
        crounchAnimate.setPosition(x, y);
    }
    void update(float dt) {
    }
    void render(RenderWindow& rw) {
        static const std::set<State> states = {
          State::Standing,
          State::Crouched
        };
        if (currentState == State::Standing) {
            standAnimate.update();
        } else if (currentState == State::Crouched) {
            crounchAnimate.update();
        } else if (currentState == State::Idle) {
            idleState();
        } else if (currentState == State::Jumping) {
            JumpState();
        }
        if (currentState != State::Crouched) {
            rw.draw(standAnimate.getSprite());
        } else {
            rw.draw(crounchAnimate.getSprite());
        }
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(kWidth, kHeight), "Dino Game");
    Dino p1;
    p1.setPosition(kWidth/2.f, kHeight/2.f);
    Pterodactyl ptero;
    ptero.animate.setPosition(10.f, 10.f);
    Update update = [&](float dt) {
        //p1.update(dt);
    };
    Draw draw = [&](RenderWindow& rw) {
        p1.render(rw);
        ptero.render(rw);
    };
    loop(window, update, draw);
    return 0;
}