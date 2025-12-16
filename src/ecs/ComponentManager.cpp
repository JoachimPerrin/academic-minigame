#include "ComponentManager.hpp"

namespace ecs
{

    // Fonctions qui exécute une action pour une entité donnée

    void ComponentManager::JoueurMouvement(const SDL_Scancode keys[], Entity &entity)
    {

        if (!entity.HasComponent<ecs::Transform>())
        {
            std::cerr << "Entity is missing Transform component!" << std::endl;
            return;
        }

        if (!entity.HasComponent<ecs::Sprite>())
        {
            std::cerr << "Entity is missing Sprite component!" << std::endl;
            return;
        }

        // TODO: VERIFIER SI IL A UN TRANSFORM
        Transform &transform = entity.GetComponent<ecs::Transform>();
        Sprite &sprite = entity.GetComponent<ecs::Sprite>();
        const Uint8 *keystates = SDL_GetKeyboardState(NULL);

        if (!keystates)
        {
            std::cerr << "Error: SDL_GetKeyboardState() returned null!" << std::endl;
            return; // Stop the function if keystates is null
        }

        // INITIALISATIONs
        Vector2 vel(0, 0);
        transform.SetVel(vel);
        sprite.spriteflip = SDL_FLIP_NONE;

        vel = transform.GetVel();

        //
        // Gestion des directions
        if (keystates[keys[0]])
        {
            vel.y = -1; // HAUT
            transform.SetRot(-M_PI / 2);
        }
        if (keystates[keys[1]])
        {
            vel.y = 1; // BAS
            transform.SetRot(M_PI / 2);
        }
        if (keystates[keys[0]] && keystates[keys[1]])
            vel.y = 0; // HAUT ET BAS

        if (keystates[keys[2]])
        {
            vel.x = -1; // GAUCHE
            transform.SetRot(M_PI);
        }
        if (keystates[keys[3]])
        {
            vel.x = 1; // DROITE
            transform.SetRot(0);
        }
        if (keystates[keys[2]] && keystates[keys[3]])
            vel.x = 0; // GAUCHE ET DROITE

        if (keystates[keys[0]] && keystates[keys[3]])
        {
            // HAUT ET DROITE
            transform.SetRot(-M_PI/4);
        }
        if (keystates[keys[0]] && keystates[keys[2]])
        {
            // HAUT ET GAUCHE
            transform.SetRot(-3*M_PI/4);
        }
        if (keystates[keys[1]] && keystates[keys[3]])
        {
            // BAS ET DROITE
            transform.SetRot(M_PI/4);
        }
        if (keystates[keys[1]] && keystates[keys[2]])
        {
            // BAS ET GAUCHE
            transform.SetRot(3*M_PI/4);
        }
        // //Normalize velocity
        float mag = std::sqrt(vel.x * vel.x + vel.y * vel.y);
        if (mag > 0)
        {
            vel.x /= mag;
            vel.y /= mag;
        }

        transform.SetVel(vel);

        // Gestion du choix de l'animation
        if (keystates[keys[0]] ||
            keystates[keys[1]] ||
            keystates[keys[2]] ||
            keystates[keys[3]])
            sprite.Play("Walk");
        else
            sprite.Play("Idle");
    }

    void ComponentManager::JoueurStopMouvement(Entity &entity)
    {

        if (entity.HasComponent<ecs::Transform>())
        {
            auto &transform = entity.GetComponent<Transform>();
            transform.SetVel(Vector2(0, 0));
        }
        // Autres actions liées à l'état "Stoppé"
    }

    void ComponentManager::InventaireOpen(Entity &entity)
    {
        JoueurStopMouvement(entity);
        printf("Inventaire opened\n");
    }

    void ComponentManager::InventaireClose(Entity &entity)
    {
        JoueurStopMouvement(entity);
        printf("Inventaire closed\n");
    }

    void ComponentManager::EntitySetVelocity(Entity &entity, Vector2 velocity)
    {
        if (entity.HasComponent<ecs::Transform>())
        {
            auto &transform = entity.GetComponent<Transform>();
            transform.SetVel(velocity);
        }
    }

    void ComponentManager::Tir(const SDL_Scancode keys[], Entity &entity)
    {

        if (!entity.HasComponent<ecs::Transform>())
        {
            std::cerr << "Entity is missing Transform component!" << std::endl;
            return;
        }

        if (!entity.HasComponent<ecs::Stat>())
        {
            std::cerr << "Entity is missing Sprite component!" << std::endl;
            return;
        }

        Transform &transform = entity.GetComponent<ecs::Transform>();
        Stat &stat = entity.GetComponent<ecs::Stat>();
        const Uint8 *keystates = SDL_GetKeyboardState(NULL);
        // Gestion du tir
        if (keystates[keys[5]] && stat.IsShotReady())
        {
            Vector2 projectileVelocity = Vector2(cos(transform.GetRot()), sin(transform.GetRot()));
            std::cout << "Tir" << std::endl;

            // Vérifier si le joueur est en mouvement
            float magnitude = sqrt(projectileVelocity.x * projectileVelocity.x + projectileVelocity.y * projectileVelocity.y);

            if (magnitude > 0.0f)
            {
                // Normalisation pour conserver une vitesse constante du projectile
                float speed = 40.0f;
                projectileVelocity.x = (projectileVelocity.x / magnitude) * speed;
                projectileVelocity.y = (projectileVelocity.y / magnitude) * speed;

                // Création du projectile
                Game::gobjs->CreateProjectile(
                    Vector2(transform.GetPos().x, transform.GetPos().y),
                    projectileVelocity,
                    10000, 2, entity.GetComponent<Stat>().GetWeapon());

                // Mise à jour du cooldown du tir
                stat.SetLastShot();
            }
        }

        unsigned int actionDelay = stat.GetShotDelay();
        unsigned int lastAction = stat.GetLastShot();

        // Changement d'arme
        if (keystates[keys[6]] && SDL_GetTicks() - lastAction > actionDelay)
        {
            std::cout << "Changement d'arme" << std::endl;
            stat.ChangeWeapon();
            stat.SetLastShot();
        }
    }

}