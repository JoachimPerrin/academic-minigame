#include "Collider.hpp"
#include "Transform.hpp"

namespace ecs
{
    void Collider::Init()
    {
    }

    void Collider::Update()
    {
    }

    AABBCollider::AABBCollider(const std::string &t)
    {
        tag = t;
    }
    void AABBCollider::Init()
    {
        if (!entity->HasComponent<Transform>())
        {
            entity->AddComponent<Transform>();
        }
        transform = &entity->GetComponent<Transform>();
    }

    Vector2 AABBCollider::IsColliding(Collider &other)
    {
        if (!transform)
            return Vector2(0, 0); // Check if transform is valid

        if (AABBCollider *aabb = dynamic_cast<AABBCollider *>(&other))
        {
            if (aabb->transform->GetPos().x + aabb->transform->GetSize().x > transform->GetPos().x)
            {
                Vector2 vec;
                return vec;
            }
        }
        else if (CircularCollider *circle = dynamic_cast<CircularCollider *>(&other))
        {
            if (circle->GetRadius() > 0)
            {
                Vector2 vec;
                return vec;
            }
        }
        Vector2 vec;
        return vec;
    }

    CircularCollider::CircularCollider(const std::string &t)
    {
        tag = t;
    }

    void CircularCollider::Init()
    {
        if (!entity->HasComponent<Transform>())
        {
            entity->AddComponent<Transform>();
        }
        transform = &entity->GetComponent<Transform>();
        if (radius == -1)
            radius = std::min(transform->GetSize().x * transform->GetScale().x, transform->GetSize().y * transform->GetScale().y) / 2;
        SetCenter(transform->GetPos().x + transform->GetSize().x * transform->GetScale().x / 2, transform->GetPos().y + transform->GetSize().y * transform->GetScale().y / 2);
    }

    Vector2 CircularCollider::IsColliding(Collider &other)
    {
        SetCenter(transform->GetPos().x + transform->GetSize().x * transform->GetScale().x / 2, 
                  transform->GetPos().y + transform->GetSize().y * transform->GetScale().y / 2);
        Vector2 centerA = GetCenter();
        if (AABBCollider *aabb = dynamic_cast<AABBCollider *>(&other))
        {
            // AABB vs Circle collision
            Vector2 aabbPos = aabb->transform->GetPos();
            Vector2 aabbSize = aabb->transform->GetSize() * aabb->transform->GetScale();

            // Find closest point on AABB to circle
            float closestX = std::max(aabbPos.x, std::min(centerA.x, aabbPos.x + aabbSize.x));
            float closestY = std::max(aabbPos.y, std::min(centerA.y, aabbPos.y + aabbSize.y));

            // Calculate distance between circle center and closest point
            float dx = centerA.x - closestX;
            float dy = centerA.y - closestY;
            float distanceSquared = (dx * dx) + (dy * dy);

            // Check if distance is less than radius
            if (distanceSquared < (radius * radius))
            {
                return (Vector2(closestX, closestY) - centerA).Normalized();
            }
            return Vector2(0, 0);
        }
        else if (CircularCollider *circle = dynamic_cast<CircularCollider *>(&other))
        {
            // Circle vs Circle collision
            Vector2 centerB = circle->GetCenter();
            float dx = centerA.x - centerB.x;
            float dy = centerA.y - centerB.y;
            float distanceSquared = (dx * dx) + (dy * dy);
            float radiusSum = radius + circle->GetRadius();
            if (distanceSquared < (radiusSum * radiusSum))
            {
                float distance = std::sqrt(distanceSquared);
                float depth = radiusSum - distance;
                Vector2 normal = (centerA - centerB).Normalized();
                return normal * depth;
            }
            return Vector2(0, 0);
        }

        return Vector2(0, 0); // No collision
    }
}
