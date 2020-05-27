#include "pterodactyl.h"

#include "game-consts.h"
#include "game-random.h"

Pterodactyl::Pterodactyl() {
    this->setSpeed(200);
    pos = {kWidth, 0.f};
    randomize();
    animation.getSprite().setPosition(pos);
    this->setPosition(pos);
}

void Pterodactyl::update(float dt) {
    pos.x -= speed * dt;
    if (pos.x + 46.f < 0.f) {
        pos.x = kWidth;
        randomize();
    }
    animation.getSprite().setPosition(pos);
}

void Pterodactyl::render(RenderWindow& rw) {
    animation.update();
    rw.draw(animation.getSprite());
}

void Pterodactyl::randomize() {
    int count = floor(nor(mt) * 3);
    pos.y = kHeight - 73.f - (count * 30);
}
