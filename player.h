#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Audio.hpp>
#include "object.h"
#include "animation.h"


/**
 * @brief The Player class
 */
class Player : public Object
{
    enum class State {Idle, Stand, Crouch, Jump, Dead};
    State currentState = State::Idle;
    Time animateSpeed = sf::seconds(1.f/15.);
    float gravity = -560.f;
    Animation standAnimate{"dino-01.png", {2, 3, 1, {0, 0, 48, 45}}, animateSpeed};
    Animation crounchAnimate{"dino-02.png", {0, 1, 0, {0, 0, 57, 45}}, animateSpeed};
    Vector2f sBoxSize = {45.f, 45.f};
    Vector2f cBoxSize = {57.f, 28.f};
    sf::SoundBuffer buffer;
    sf::Sound jump;
public:
    /**
     * @brief Player
     */
    Player();
    /**
     * @brief standState
     */
    void standState();
    /**
     * @brief DeadState
     */
    void DeadState();
    /**
     * @brief idleState
     */
    void idleState();
    /**
     * @brief JumpState
     */
    void JumpState();
    /**
     * @brief update
     * @param dt
     */
    void update(float dt) override;
    /**
     * @brief render
     * @param rw
     */
    void render(RenderWindow &rw) override;
    /**
     * @brief keyPressed
     * @param key
     */
    void keyPressed(sf::Event::KeyEvent& key);
    /**
     * @brief Player::keyReleased
     */
    void keyReleased();
    /**
     * @brief setPosition
     * @param pos
     */
    void setPosition(const Vector2f& pos) override;
    /**
     * @brief getBox
     * @return
     */
    sf::FloatRect getBox();
};

#endif // PLAYER_H
