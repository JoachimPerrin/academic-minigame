#include "Stat.hpp"

namespace ecs
{
    Stat::Stat()
        : speed(10), hp(1000), lastShot(SDL_GetTicks()), shotDelay(400), weapon(allyProjectile) {} // peut-e^tre faire un choix de perso avec des stats différentes

    bool Stat::IsShotReady()
    {
        return (SDL_GetTicks() - lastShot > shotDelay);
    }

    void Stat::SetLastShot()
    {
        lastShot = SDL_GetTicks();
    }

    void Stat::ChangeWeapon()
    {
        if (weapon == allyProjectile)
        {
            shotDelay = 100;
            weapon = chargedProjectile;
        }
        else
        {
            shotDelay = 1000;
            weapon = allyProjectile;
        }
    }
    void Stat::Update()
    {
        if (hp <= 0)
        {
            entity->Destroy();
        }
    }

    ProjectileType Stat::GetWeapon() { return weapon; }
    int Stat::GetHP() { return hp; }
    int Stat::GetSpeed() { return speed; }
    void Stat::Hurt(int damage) { hp -= damage; }
    void Stat::Healed(int heal) { hp += heal; }
    unsigned int Stat::GetLastShot() { return lastShot; }
    unsigned int Stat::GetShotDelay() { return shotDelay; }
}