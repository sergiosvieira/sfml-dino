#include "cloud.h"

#include "game-consts.h"
#include "game-random.h"

Cloud::Cloud() {
    randomize();
    this->texture.loadFromFile("cloud.png");
    this->sprite.setTexture(this->texture);
    this->sprite.setTextureRect({0, 0, kFrameWidth, 13});
}

void Cloud::update(float dt) {
    pos.x -= speed * dt;
    if (pos.x + kFrameWidth < 0.f) {
        randomize();
    }
    sprite.setPosition(pos);
}

void Cloud::render(RenderWindow& rw) {
    rw.draw(sprite);
}

void Cloud::randomize() {
    pos.x = kWidth + urd(mt) * 100.f;
    if (urd(mt) > 1.) {
        pos.y = kHeight - 100.f - urd(mt) * 100.f;
    } else {
        pos.y = kHeight - 100.f - urd(mt) * 85.f;
    }
    speed = 200.f * nor(mt);
}
