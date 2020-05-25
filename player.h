#ifndef PLAYER_H
#define PLAYER_H

#include "object.h"
#include "animation.h"


/**
 * @brief The Player class
 */
class Player : public Object
{
    enum class State {Idle, Stand, Crouch, Jump};
    State currentState = State::Idle;
    Time animateSpeed = sf::seconds(1.f/15.);
    float gravity = -360.f;
    Animation standAnimate{"dino-01.png", {2, 3, 1, {0, 0, 48, 45}}, animateSpeed};
    Animation crounchAnimate{"dino-02.png", {0, 1, 0, {0, 0, 57, 45}}, animateSpeed};
    Vector2f sBoxSize = {45.f, 45.f};
    Vector2f cBoxSize = {57.f, 28.f};
public:
    /**
     * @brief Player
     */
    Player();
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
};

/*
class Dino {
public:
    Vector2f vel = {0.f, 200.f};
    Vector2f gra = {0.f, -380.f};
    enum class State {Idle, Standing, Crouched, Jumping};
    State currentState = State::Idle;
    Time animateSpeed = sf::seconds(1.f/15.);
    Animation standAnimate{"dino-01.png", {2, 3, 1, {0, 0, 48, 45}}, animateSpeed};
    Animation crounchAnimate{"dino-02.png", {0, 1, 0, {0, 0, 57, 45}}, animateSpeed};
    Dino() {
        idleState();
    }
    void printState() {
        if (currentState == State::Idle) {
            std::cout << "Idle\n";
        } else if (currentState == State::Standing) {
            std::cout << "Standing\n";
        } else if (currentState == State::Crouched) {
            std::cout << "Crouched\n";
        } else if (currentState == State::Jumping) {
            std::cout << "Jumping\n";
        }
    }
    void idleState() {
        currentState = State::Idle;
        standAnimate.getFrame().setCurrentFrame(0);
        standAnimate.getFrame().update();
    }
    void JumpState() {
        currentState = State::Jumping;
        standAnimate.getFrame().setCurrentFrame(1);
    }
    void setPosition(float x, float y) {
        standAnimate.getSprite().setPosition(x, y);
        crounchAnimate.getSprite().setPosition(x, y);
    }
    void update(float dt) {
        if (currentState == State::Jumping) {
            Vector2f pos = standAnimate.getSprite().getPosition();
            pos.y -= vel.y * dt;
            vel += gra * dt;
            if (pos.y > 317.f) {
                pos.y = 317.f;
                currentState = State::Standing;
                vel = {0.f, 200.f};
            }
            setPosition(pos.x, pos.y);
        }
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
    void keyPressed(sf::Event::KeyEvent& key) {
        if (currentState != State::Jumping)
        {
            if (key.code == sf::Keyboard::Up) {
                currentState = State::Jumping;
            } else if (key.code == sf::Keyboard::Down) {
                currentState = State::Crouched;
            }
        }
    }
    void keyReleased() {
        if (currentState != State::Jumping)
        {
            currentState = State::Standing;
        }
    }
};

*/

#endif // PLAYER_H
