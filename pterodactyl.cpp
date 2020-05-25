#include "pterodactyl.h"

#include "game-consts.h"
#include "game-random.h"

Pterodactyl::Pterodactyl() {
    this->setSpeed(200);
    this->setPosition({kWidth, kHeight - 73.f});
}

void Pterodactyl::update(float dt) {
    pos.x -= speed * dt;
    if (pos.x + 46.f < 0.f) {
        pos.x = kWidth;
        if (urd(mt) > 1.) {
            pos.y = kHeight - 103.f;
        } else {
            pos.y = kHeight - 73.f;
        }
    }
    animation.getSprite().setPosition(pos);
}
void Pterodactyl::render(RenderWindow& rw) {
    animation.update();
    rw.draw(animation.getSprite());
}
