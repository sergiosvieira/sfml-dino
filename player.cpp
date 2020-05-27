#include "player.h"

#include <set>

Player::Player() {
    idleState();
    setPosition(pos);
    speed = 500.f;
    buffer.loadFromFile("jump.wav");
    jump.setBuffer(buffer);
}

void Player::DeadState() {
    currentState = State::Dead;
    standAnimate.getFrame().setCurrentFrame(4);
    standAnimate.setFreeze(true);
    standAnimate.getFrame().updateRect();
    standAnimate.getSprite().setTextureRect(standAnimate.getFrame().getRect());
    freeze();
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
        if (pos.y < 290.f) {
            speed += 3.3f * gravity * dt;
        } else {
            speed += gravity * dt;
        }
        if (pos.y > 317.f) {
            pos.y = 317.f;
            currentState = State::Stand;
            speed = 500.f;
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

//    sf::RectangleShape shape = sf::RectangleShape({getBox().width, getBox().height});
//    shape.setFillColor(sf::Color::Red);
//    shape.setPosition(getBox().left, getBox().top);
//    rw.draw(shape);

    if (currentState != State::Crouch) {
        rw.draw(standAnimate.getSprite());
    } else {
        rw.draw(crounchAnimate.getSprite());
    }
}

void Player::keyPressed(sf::Event::KeyEvent& key) {
    if (freeze_) {

    } else if (currentState != State::Jump)
    {
        if (key.code == sf::Keyboard::Up) {
            currentState = State::Jump;
            jump.play();
        } else if (key.code == sf::Keyboard::Down) {
            currentState = State::Crouch;
        }
    }
}

void Player::keyReleased() {
    if (freeze_) return;
    if (currentState != State::Jump) {
        currentState = State::Stand;
    }
}

void Player::setPosition(const Vector2f& pos) {
    standAnimate.getSprite().setPosition(pos.x, pos.y);
    crounchAnimate.getSprite().setPosition(pos.x, pos.y);
}

sf::FloatRect Player::getBox() {
    if (currentState == State::Crouch) {
        return {getPosition().x + 5.f, getPosition().y + 17.f, cBoxSize.x - 15.f, cBoxSize.y - 5.f};
    }
    return {getPosition().x + 10.f, getPosition().y, sBoxSize.x - 15.f, sBoxSize.y - 10.f};
}
