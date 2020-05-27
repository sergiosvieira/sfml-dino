#include "game.h"

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "cloud.h"
#include "pterodactyl.h"
#include "cactus.h"

Game::Game(PtrPlayer player) {
    this->player = player;
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
        {EventType::BigCactus, sf::seconds(1.3)},
        {EventType::BigCactus, sf::seconds(1.4)},
        {EventType::Pterodactyl, sf::seconds(1.5)},
        {EventType::Pterodactyl, sf::seconds(0.9)},
        {EventType::BigCactus, sf::seconds(0.9)},
        {EventType::SmallCactus, sf::seconds(1.1)},
    };
    hardEvents = {
        {EventType::None, sf::seconds(1)},
        {EventType::SmallCactus, sf::seconds(1.1)},
        {EventType::SmallCactus, sf::seconds(0.5)},
        {EventType::Pterodactyl, sf::seconds(0.6)},
        {EventType::BigCactus, sf::seconds(0.5)},
        {EventType::Pterodactyl, sf::seconds(0.7)},
        {EventType::Pterodactyl, sf::seconds(0.9)},
        {EventType::SmallCactus, sf::seconds(0.5)},
        {EventType::BigCactus, sf::seconds(0.9)},
        {EventType::BigCactus, sf::seconds(1.1)},
    };
    hardestEvents = {
        {EventType::None, sf::seconds(1)},
        {EventType::BigCactus, sf::seconds(0.8)},
        {EventType::BigCactus, sf::seconds(0.9)},
        {EventType::Pterodactyl, sf::seconds(0.7)},
        {EventType::None, sf::seconds(0.9)},
        {EventType::SmallCactus, sf::seconds(1.5)},
        {EventType::SmallCactus, sf::seconds(0.5)},
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
        {EventType::SmallCactus, sf::seconds(1.1)},
        {EventType::SmallCactus, sf::seconds(0.6)},
        {EventType::Pterodactyl, sf::seconds(1.2)},
        {EventType::None, sf::seconds(0.5)},
        {EventType::SmallCactus, sf::seconds(0.2)},
    };
    initGameLevel();
    buffer.loadFromFile("points.wav");
    pointsUp.setBuffer(buffer);
    goBuffer.loadFromFile("gameover.wav");
    goSound.setBuffer(goBuffer);

    font.loadFromFile("atari.ttf");
    text.setFont(font);

    fontGameOver.loadFromFile("atari.ttf");
    textGameOver.setFont(font);
    textGameOver.setString("Press Enter to Restart");
    textGameOver.setCharacterSize(15);
    textGameOver.setPosition(kWidth/2.f - textGameOver.getGlobalBounds().width/2.f,
                             kHeight/2.f - textGameOver.getGlobalBounds().height/2.f);
    textGameOver.setFillColor(sf::Color(38, 38, 38));

    textPaused.setFont(fontGameOver);
    textPaused.setString("Press Enter to Start");
    textPaused.setCharacterSize(15);
    textPaused.setPosition(kWidth/2.f - textGameOver.getGlobalBounds().width/2.f,
                             kHeight/2.f - textGameOver.getGlobalBounds().height/2.f);
    textPaused.setFillColor(sf::Color(38, 38, 38));

    std::ostringstream ss;
    ss << std::setw(5) << std::setfill('0') << points << "\n";
    text.setString(ss.str());
    text.setPosition(kWidth - 100.f, 10.f);
    text.setFillColor(sf::Color(38, 38, 38));
    text.setCharacterSize(15);
}

void Game::initGameLevel() {
    if (level == Level::Easy) {
        gameSpeed = 300.f;
        init(easyEvents);
    } else if (level == Level::Normal) {
        gameSpeed = 350.f;
        init(normalEvents);
    } else if (level == Level::Hard) {
        gameSpeed = 400.f;
        init(hardEvents);
    } else if (level == Level::Hardest) {
        gameSpeed = 450.f;
        init(hardestEvents);
    }
    ground.setSpeed(gameSpeed);
    for (auto c: clouds) {
        c->setSpeed(gameSpeed);
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
        if (gameover) object->freeze();
        object->render(rw);
        if (player != nullptr
                && !gameover) {
            sf::FloatRect prect = player->getBox();
            sf::FloatRect orect = {
                object->getPosition().x,
                object->getPosition().y,
                object->getSize().x,
                object->getSize().y
            };
            if (prect.intersects(orect)) {
                if (!gameover) goSound.play();
                gameover = true;
                player->DeadState();
            }
        }
    }
    std::ostringstream ss;
    if (blinking) {
        ss << std::setw(5) << std::setfill('0') << blinkPoints << "\n";
    } else {
        ss << std::setw(5) << std::setfill('0') << points << "\n";
    }
    /** Início - Controle de Pontuação **/
    if (!gameover) {
        pointElapsed += pointClock.restart();
        while (pointElapsed > pointWait) {
            ++points;
            if (points % 100 == 0) {
                blinkPoints = points;
                blinking = true;
                pointsUp.play();
            }
            pointElapsed -= pointWait;
        }
        blinkElapsed += blinkClock.restart();
        while (blinkElapsed > blinkWait) {
            blinkElapsed -= blinkWait;
            if (blinking) {
                ++blinkCount;
                showTextScore = !showTextScore;
                if (blinkCount >= 8) {
                    blinkCount = 0;
                    blinking = false;
                    showTextScore = true;
                }
            }
        }
        /** Fim - Controle de Pontuação **/
        // Controle do nível de Dificuldade do Jogo
        if (points > 500 && points < 1000) level = Level::Normal;
        else if (points > 1000 && points < 5000) level = Level::Hard;
        else if (points > 5000) level = Level::Hardest;
        text.setString(ss.str());
    }
    if (showTextScore) rw.draw(text);
    if (gameover) {
        rw.draw(textGameOver);
    }
}

void Game::update(float dt) {
    if (gameover) {
        return;
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
    PtrObject object = nullptr;
    if (event.type == EventType::SmallCactus) {
         object = PtrObject(new Cactus("cactus-small.png", {0, 0, 17, 35}, 327.f));
    } else if (event.type == EventType::BigCactus) {
        object = PtrObject(new Cactus("cactus-big.png", {0, 0, 25, 50}, 315.f));
    } else if (event.type == EventType::Pterodactyl) {
        object = PtrObject(new Pterodactyl());
    }
    object->setSpeed(gameSpeed);
    return object;
}

bool Game::hasGameOver() const {
    return this->gameover;
}
