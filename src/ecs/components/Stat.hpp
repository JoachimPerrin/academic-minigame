#ifndef STAT_HPP
#define STAT_HPP

#include "ECS.hpp"
#include "Projectile.hpp"

namespace ecs
{
    class Stat : public Component
    {
    public:
        Stat();

        bool IsShotReady();
        void SetLastShot();
        void ChangeWeapon();
        ProjectileType GetWeapon();
        int GetHP();
        int GetSpeed();
        void Hurt(int damage);
        void Healed(int heal);
        void Update();

        unsigned int GetLastShot();
        unsigned int GetShotDelay();


        friend class KeyboardController;

    private:
        int speed;
        int hp;
        unsigned int lastShot;
        unsigned int shotDelay;
        ProjectileType weapon;
    };
}
#endif