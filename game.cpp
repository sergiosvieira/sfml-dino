#include "game.h"

#include <algorithm>
#include <iomanip>
#include <sstream>
#include "cloud.h"
#include "pterodactyl.h"
#include "cactus.h"

Game::Game() {
    clouds = {
        PtrObject(new Cloud()),
        PtrObject(new Cloud()),
        PtrObject(new Cloud()),
        PtrObject(new Cloud()),
        PtrObject(new Cloud()),
        PtrObject(new Cloud()),
    };
    easyEvents = {
        {EventType::None, sf::seconds(1)},
        {EventType::Pterodactyl, sf::seconds(1)},
        {EventType::Pterodactyl, sf::seconds(1)},
        {EventType::Pterodactyl, sf::seconds(1)},
        {EventType::Pterodactyl, sf::seconds(1)},
        {EventType::Pterodactyl, sf::seconds(1)},
        {EventType::SmallCactus, sf::seconds(2)},
        {EventType::Pterodactyl, sf::seconds(2)},
        {EventType::BigCactus, sf::seconds(2)},
        {EventType::None, sf::seconds(3)},
        {EventType::BigCactus, sf::seconds(2)},
        {EventType::BigCactus, sf::seconds(2)},
        {EventType::Pterodactyl, sf::seconds(2)},
        {EventType::Pterodactyl, sf::seconds(1.9)},
    };
    normalEvents = {
        {EventType::None, sf::seconds(1)},
        {EventType::BigCactus, sf::seconds(2)},
        {EventType::BigCactus, sf::seconds(2)},
        {EventType::Pterodactyl, sf::seconds(2)},
        {EventType::Pterodactyl, sf::seconds(2)},
        {EventType::BigCactus, sf::seconds(2)},
        {EventType::SmallCactus, sf::seconds(2)},
    };
    hardEvents = {
        {EventType::None, sf::seconds(1)},
        {EventType::SmallCactus, sf::seconds(2)},
        {EventType::SmallCactus, sf::seconds(2)},
        {EventType::Pterodactyl, sf::seconds(2)},
        {EventType::BigCactus, sf::seconds(2)},
        {EventType::Pterodactyl, sf::seconds(2)},
        {EventType::Pterodactyl, sf::seconds(2)},
        {EventType::SmallCactus, sf::seconds(2)},
        {EventType::BigCactus, sf::seconds(2)},
        {EventType::BigCactus, sf::seconds(2)},
    };
    hardestEvents = {
        {EventType::None, sf::seconds(1)},
        {EventType::BigCactus, sf::seconds(2)},
        {EventType::BigCactus, sf::seconds(2)},
        {EventType::Pterodactyl, sf::seconds(2)},
        {EventType::None, sf::seconds(1)},
        {EventType::SmallCactus, sf::seconds(1.5)},
        {EventType::SmallCactus, sf::seconds(2)},
        {EventType::Pterodactyl, sf::seconds(1)},
        {EventType::BigCactus, sf::seconds(1.)},
        {EventType::Pterodactyl, sf::seconds(0.5)},
        {EventType::Pterodactyl, sf::seconds(1)},
        {EventType::SmallCactus, sf::seconds(1.2)},
        {EventType::BigCactus, sf::seconds(1.3)},
        {EventType::BigCactus, sf::seconds(1.1)},
        {EventType::Pterodactyl, sf::seconds(1.6)},
        {EventType::BigCactus, sf::seconds(1.2)},
        {EventType::Pterodactyl, sf::seconds(0.8)},
        {EventType::Pterodactyl, sf::seconds(1.1)},
        {EventType::SmallCactus, sf::seconds(1.2)},
        {EventType::BigCactus, sf::seconds(1.5)},
        {EventType::BigCactus, sf::seconds(1.8)},
        {EventType::None, sf::seconds(0.5)},
        {EventType::SmallCactus, sf::seconds(2)},
        {EventType::SmallCactus, sf::seconds(2)},
        {EventType::Pterodactyl, sf::seconds(2)},
        {EventType::None, sf::seconds(1)},
        {EventType::SmallCactus, sf::seconds(2)},
    };
    initGameLevel();
    font.loadFromFile("atari.ttf");
    text.setFont(font);
    std::ostringstream ss;
    ss << std::setw(5) << std::setfill('0') << points << "\n";
    //std::string str = std::string(5, '0').append(std::to_string(points));
    text.setString(ss.str());
    text.setPosition(kWidth - 100.f, 10.f);
    text.setFillColor(sf::Color(35, 35, 35));
    text.setCharacterSize(15);
}

void Game::initGameLevel() {
    if (level == Level::Easy) {
        init(easyEvents);
    } else if (level == Level::Normal) {
        init(normalEvents);
    } else if (level == Level::Hard) {
        init(hardEvents);
    } else if (level == Level::Hardest) {
        init(hardestEvents);
    }
}

void Game::init(const VectorEvents& events) {
    for (unsigned int i = 0; i < events.size(); ++i) {
        queue.push_back(events[i]);
    }
}

void Game::render(sf::RenderWindow& rw) {
    for (auto c: clouds) {
        c->render(rw);
    }
    ground.render(rw);
    for (auto object: activatedObjects) {
        object->render(rw);
    }
    std::ostringstream ss;
    ss << std::setw(5) << std::setfill('0') << points << "\n";
    text.setString(ss.str());
    rw.draw(text);
}

void Game::update(float dt) {
    pointElapsed += pointClock.restart();
    if (pointElapsed > pointWait) {
        ++points;
        pointElapsed -= pointWait;
    }
    for (auto c: clouds) {
        c->update(dt);
    }
    ground.update(dt);
    currentTime += clock.restart();
    if (currentTime > queue.front().wait) {
        if (queue.size() > 0) {
            GameEvent event = queue.front();
            if (event.type != EventType::None) {
                PtrObject object = process(queue.front());
                if (object != nullptr) activatedObjects.push_back(object);
            }
            currentTime -= queue.front().wait;
            queue.pop_front();
        }
    }
    bool erase = false;
    for (auto object: activatedObjects) {
        object->update(dt);
        if (object->getPosition().x < 0.f) {
            object->setCanRemove(true);
            erase = true;
        }
    }
    if (erase) {
        activatedObjects.erase(std::remove_if(activatedObjects.begin(),activatedObjects.end(),
                              [](const PtrObject& object){return object->canRemove();}));
        if (queue.empty()) {
            initGameLevel();
        }
    }
}

PtrObject Game::process(const GameEvent& event) {
    if (event.type == EventType::SmallCactus) {
        return PtrObject(new Cactus("cactus-small.png", {0, 0, 17, 35}, 327.f));
    } else if (event.type == EventType::BigCactus) {
        return PtrObject(new Cactus("cactus-big.png", {0, 0, 25, 50}, 315.f));
    } else if (event.type == EventType::Pterodactyl) {
        return PtrObject(new Pterodactyl());
    }
    return nullptr;
}
