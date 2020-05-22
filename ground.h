#ifndef GROUND_H
#define GROUND_H
#include <SFML/Graphics.hpp>

#include "game-consts.h"
#include "game-random.h"
#include "object.h"

using sf::Texture,
    sf::Sprite;

class Ground: public Object {
    Texture texture;
    Sprite sprite;
public:
    Ground();
    void update(float dt) override;
    void render(RenderWindow& rw) override;
};

/*
class Ground: public Object {
    Texture tex, texTiles;
    Sprite sprite, spriteTiles;
    Vector2f pos = {0, kHeight - 50.f};
    Vector2f tilePos = {kWidth, kHeight - 50.f};
    Vector2i tileSize = {25, 12};
    float speed = 250.f;
    bool showTileGround = false;
public:
    Ground() {
        tex.loadFromFile("ground.png");
        sprite.setTexture(tex);
        sprite.setTextureRect({0, 0, 1200, 12});
        sprite.setPosition(0, kHeight - 50);
        texTiles.loadFromFile("tile-ground.png");
        spriteTiles.setTexture(texTiles);
        spriteTiles.setTextureRect({0, 0, tileSize.x, tileSize.y});
        spriteTiles.setPosition(tilePos);
    }
    void update(float dt) {
        pos.x -= speed * dt;
        if (pos.x < -600.f) {
            pos.x = 0.f;
            showTileGround = true;
            int rx = urd(mt);
            int rw = urd(mt) + 1;
            spriteTiles.setTextureRect({rx * tileSize.x, 0,
                                        rw * tileSize.x, tileSize.y});
        }
        sprite.setPosition(pos);
        if (showTileGround) {
            tilePos.x -= speed * dt;
            if (tilePos.x + spriteTiles.getTextureRect().width < 0) {
                tilePos.x = kWidth;
                showTileGround = false;
            }
            spriteTiles.setPosition(tilePos);
        }
    }
    void render(RenderWindow& rw) {
        rw.draw(sprite);
        rw.draw(spriteTiles);
    }
};
*/

#endif // GROUND_H
