#ifndef GAME_H
#define GAME_H

#include <vector>
#include <deque>
#include <memory>
#include "object.h"
#include "ground.h"

using PtrObject = std::shared_ptr<Object>;
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
    unsigned int points = 0;
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
    Game();
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
};

#endif // GAME_H
