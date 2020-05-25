#ifndef OBJECT_H
#define OBJECT_H

#include <SFML/Graphics.hpp>

using sf::Vector2f,
    sf::RenderWindow;

/**
 * @brief The Object class
 */
class Object {
protected:
    Vector2f pos = {};
    float speed = 0.f;
public:
    /**
     * @brief update
     * @param dt
     */
    virtual void update(float dt) = 0;
    /**
     * @brief render
     * @param rw
     */
    virtual void render(RenderWindow& rw) = 0;
    /**
     * @brief setPosition
     * @param pos
     */
    virtual void setPosition(const Vector2f& pos) {
        this->pos = pos;
    }
    /**
     * @brief setSpeed
     * @param speed
     */
    void setSpeed(float speed) {
        this->speed = speed;
    }
};

#endif // OBJECT_H
