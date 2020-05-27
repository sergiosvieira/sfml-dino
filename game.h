#ifndef GAME_H
#define GAME_H

#include <vector>
#include <deque>
#include <memory>
#include "object.h"
#include "ground.h"
#include "player.h"

using PtrObject = std::shared_ptr<Object>;
using PtrPlayer = std::shared_ptr<Player>;
using VectorObject = std::vector<PtrObject>;

enum class EventType {None, SmallCactus, BigCactus, Pterodactyl};
using GameEvent = struct {
    EventType type = EventType::None;
    sf::Time wait = sf::seconds(0);
};

using VectorEvents = std::vector<GameEvent>;
using Queue = std::deque<GameEvent>;

/**
 * @brief The Game class
 */
class Game {
    PtrPlayer player = nullptr;
    float gameSpeed = 250.f;
    int blinkCount = 0;
    bool showTextScore = true;
    bool blinking = false;
    sf::Clock blinkClock;
    sf::Time blinkElapsed = blinkClock.restart();
    sf::Time blinkWait = sf::seconds(1.f/4.f);

    enum class Level {Easy, Normal, Hard, Hardest};
    Level level = Level::Easy;
    sf::Clock clock, pointClock;
    sf::Time currentTime = clock.restart();
    sf::Time pointElapsed = pointClock.restart();
    sf::Time pointWait = sf::seconds(1.f/7.f);
    VectorObject clouds;
    PtrObject pterodactyl;
    VectorEvents easyEvents;
    VectorEvents normalEvents;
    VectorEvents hardEvents;
    VectorEvents hardestEvents;
    Queue queue;
    VectorObject activatedObjects;
    Ground ground;
    sf::Font font;
    sf::Text text;
    sf::Font fontGameOver;
    sf::Text textGameOver;
    unsigned int points = 0;
    unsigned int blinkPoints = 0;
    bool gameover = false;
    sf::SoundBuffer buffer, goBuffer;
    sf::Sound pointsUp, goSound;
    /**
     * @brief init
     * @param events
     */
    void init(const VectorEvents& events);
    /**
     * @brief initGameLevel
     */
    void initGameLevel();
    /**
     * @brief process
     * @param event
     * @return
     */
    PtrObject process(const GameEvent& event);
public:
    /**
     * @brief Game
     */
    Game(PtrPlayer player);
    /**
     * @brief render
     * @param rw
     */
    void render(sf::RenderWindow& rw);
    /**
     * @brief update
     * @param dt
     */
    void update(float dt);
    /**
     * @brief hasGameOver
     * @return
     */
    bool hasGameOver() const;
};

using PtrGame = std::shared_ptr<Game>;

#endif // GAME_H
