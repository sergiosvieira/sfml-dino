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
    bool canRemove_ = false;
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
     * @brief getPosition
     * @return
     */
    const Vector2f& getPosition() const {
        return this->pos;
    }
    bool canRemove() const {
        return this->canRemove_;
    }
    /**
     * @brief setCanRemove
     * @param value
     */
    void setCanRemove(bool value) {
        this->canRemove_ = value;
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
