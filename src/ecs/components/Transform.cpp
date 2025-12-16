#include "Transform.hpp"
#include "Stat.hpp"

namespace ecs
{
    Transform::Transform()
        : position({0.0f, 0.0f}), velocity({0.0f, 0.0f}), size({1.0f, 1.0f}), scale({1.0f, 1.0f}), rotation(0.0f), torque(0.0f)
    {
    }

    Transform::Transform(Vector2 pos, Vector2 vel, Vector2 siz, Vector2 sca, float rot, float tor)
        : position(pos), velocity(vel), size(siz), scale(sca), rotation(rot), torque(tor)
    {
    }

    Vector2 Transform::GetPos() const { return position; }
    Vector2 Transform::GetVel() const { return velocity; }
    Vector2 Transform::GetSize() const { return size; }
    Vector2 Transform::GetScale() const { return scale; }
    float Transform::GetRot() const { return rotation; }
    float Transform::GetTor() const { return torque; }

    void Transform::SetPos(Vector2 pos) { this->position = pos; }
    void Transform::SetVel(Vector2 vel) { this->velocity = vel; }
    void Transform::SetSize(Vector2 siz) { this->size = siz; }
    void Transform::SetScale(Vector2 sca) { this->scale = sca; }
    void Transform::SetRot(float rot) { this->rotation = rot; }
    void Transform::SetTor(float tor) { this->torque = tor; }

    void Transform::Init() {}
    void Transform::Update()
    {
        int speed = 1;
        if (entity->HasComponent<Stat>())
        {
            speed += entity->GetComponent<Stat>().GetSpeed();
        }
        position.x += velocity.x * speed;
        position.y += velocity.y * speed;
        //rotation += torque * speed;
    }
}