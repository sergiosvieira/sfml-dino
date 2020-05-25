#include "player.h"

#include <set>

Player::Player() {
    idleState();
    setPosition(pos);
}

void Player::idleState() {
    currentState = State::Idle;
    standAnimate.getFrame().setCurrentFrame(0);
    standAnimate.setFreeze(true);
    standAnimate.getFrame().updateRect();
    standAnimate.getSprite().setTextureRect(standAnimate.getFrame().getRect());
    pos = {50.f, 317.f};
}

void Player::JumpState() {
    currentState = State::Jump;
    standAnimate.getFrame().setCurrentFrame(1);
    standAnimate.setFreeze(true);
    standAnimate.getFrame().updateRect();
    standAnimate.getSprite().setTextureRect(standAnimate.getFrame().getRect());
}

void Player::update(float dt) {
    if (currentState == State::Jump) {
        pos.y -= speed * dt;
        speed += gravity * dt;
        if (pos.y > 317.f) {
            pos.y = 317.f;
            currentState = State::Stand;
            speed = 200.f;
        }
    }
   setPosition(pos);
}

void Player::render(RenderWindow& rw) {
    static const std::set<State> states = {
      State::Stand,
      State::Crouch
    };
    if (currentState == State::Stand) {
        standAnimate.setFreeze(false);
        standAnimate.update();
    } else if (currentState == State::Crouch) {
        standAnimate.setFreeze(false);
        crounchAnimate.update();
    } else if (currentState == State::Idle) {
        idleState();
        standAnimate.getFrame().updateRect();
    } else if (currentState == State::Jump) {
        JumpState();
    }
    if (currentState != State::Crouch) {
        rw.draw(standAnimate.getSprite());
    } else {
        rw.draw(crounchAnimate.getSprite());
    }
}

void Player::keyPressed(sf::Event::KeyEvent& key) {
    if (currentState != State::Jump)
    {
        if (key.code == sf::Keyboard::Up) {
            currentState = State::Jump;
        } else if (key.code == sf::Keyboard::Down) {
            currentState = State::Crouch;
        }
    }
}

void Player::keyReleased() {
    if (currentState != State::Jump) {
        currentState = State::Stand;
    }
}

void Player::setPosition(const Vector2f& pos) {
    standAnimate.getSprite().setPosition(pos.x, pos.y);
    crounchAnimate.getSprite().setPosition(pos.x, pos.y);
}
