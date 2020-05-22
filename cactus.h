#ifndef CACTUS_H
#define CACTUS_H

#include "object.h"

/**
 * @brief The Cactus class
 */
class Cactus: public Object
{
public:
    /**
     * @brief Cactus
     * @param filename
     */
    Cactus(const std::string& filename);
};

/*
class Cactus {
-    Texture smallTex, bigTex;
-    Sprite smallSprite, bigSprite;
-    bool showBig = true;
-    Vector2f bigPos = {kWidth, 317};
-    Vector2i bigRect {25, 50};
-    float speed = 250.f;
-public:
-    Cactus() {
-        smallTex.loadFromFile("cactus-small.png");
-        bigTex.loadFromFile("cactus-big.png");
-        smallSprite.setTexture(smallTex);
-        bigSprite.setTexture(bigTex);
-        bigSprite.setTextureRect({0, 0, bigRect.x, bigRect.y});
-    }
-    void update(float dt) {
-        bigPos.x -= speed * dt;
-        if (bigPos.x + 25.f < 0.f) bigPos.x = kWidth;
-        bigSprite.setPosition(bigPos);
-    }
-    void render(RenderWindow& rw) {
-        if (showBig) {
-            rw.draw(bigSprite);
-        } else {
-            rw.draw(smallSprite);
-        }
-    }
-};
*/
#endif // CACTUS_H
