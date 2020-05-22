#ifndef CLOUD_H
#define CLOUD_H

#include <SFML/Graphics.hpp>
#include "object.h"

using sf::Texture,
    sf::Sprite;

/**
 * @brief The Cloud class
 */
class Cloud : public Object
{
    Texture texture;
    Sprite sprite;
public:
    /**
     * @brief Cloud
     */
    Cloud();
    /**
     * @brief update
     * @param dt
     */
    void update(float dt) override;
    /**
     * @brief render
     * @param rw
     */
    void render(RenderWindow& rw) override;
};

#endif // CLOUD_H
