/**
 * @file Collider.hpp
 * @author Dilhan Emir (dilhan77120@gmail.com)
 * @author Joachim Perrin (joachimperrin1@gmail.com)
 * @brief This file contains the definition of the Collider class, which is a component that allows entities to have a collision box.
 * @version 0.1
 * @date 2025-02-24
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef COLLIDERS_HPP
#define COLLIDERS_HPP

#include "ECS.hpp"
#include "Transform.hpp"
#include <SDL2/SDL.h>
#include <string>
#include <cmath>
#include "Vector2.hpp"

namespace ecs
{
    /**
     * @brief The Collider class is a component that allows entities to have a collision box. This is the base for different shapes of colliders.
     *
     */
    class Collider : public Component
    {
    public:
        virtual void Init() override;
        virtual void Update() override;

        virtual Vector2 IsColliding(Collider &other) = 0;

        std::string tag;
        Transform *transform;
    };

    /**
     * @brief The AABBCollider class is a collider that represents an Axis-Aligned Bounding Box.
     *
     */
    class AABBCollider : public Collider
    {
    public:
        AABBCollider(const std::string &t);

        void Init() override;

        Vector2 IsColliding(Collider &other) override;
    };

    /**
     * @brief The CircularCollider class is a collider that represents a circle.
     *
     */
    class CircularCollider : public Collider
    {
    public:
        CircularCollider(const std::string &t);

        void Init() override;

        float GetRadius() const { return radius; }
        Vector2 GetCenter() const { return center; }
        void SetRadius(float rad) { radius = rad; }
        void SetCenter(float x, float y)
        {
            center.x = x;
            center.y = y;
        }
        Vector2 IsColliding(Collider &other) override;

    private:
        float radius = -1;
        Vector2 center;
    };
}
#endif
