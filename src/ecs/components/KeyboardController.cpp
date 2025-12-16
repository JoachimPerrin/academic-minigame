// #include "KeyboardController.hpp"
// #include "Game.hpp"
// #include "Vector2.hpp"
// #include "Transform.hpp"
// #include "Sprite.hpp"
// #include "Stat.hpp"

// namespace ecs
// {
//     void KeyboardController::Init()
//     {
//         transform = &entity->GetComponent<Transform>();
//         stat = &entity->GetComponent<Stat>();
//         sprite = &entity->GetComponent<Sprite>();
//         dir = 0; // Initialize dir to a default value
//     }

//     void KeyboardController::Update()
//     {
//         transform->velocity.x = 0.0;
//         transform->velocity.y = 0.0;

//         if (Game::event.type == SDL_KEYDOWN && Game::event.key.keysym.sym == SDLK_j)
//         {
//             stat->speed = 10;
//         }
//         if (Game::event.type == SDL_KEYUP && Game::event.key.keysym.sym == SDLK_j)
//         {
//             stat->speed = 6;
//         }

//         // Gestion des entrée de mouvement (dans la SDL, les touches sont par défault en qwerty, j'ai annoté les correspondances azerty)
//         if (keystates[SDL_SCANCODE_W])
//         { // Z -> haut
//             dir = 2;
//             transform->velocity.y = -1.0;
//         }
//         if (keystates[SDL_SCANCODE_S])
//         { // S -> bas
//             dir = 3;
//             transform->velocity.y = 1.0;
//         }
//         if (keystates[SDL_SCANCODE_D])
//         { // D -> droite
//             sprite->spriteflip = SDL_FLIP_NONE;
//             dir = 0;
//             if (keystates[SDL_SCANCODE_W])
//             {                                // -> droite + haut
//                 transform->velocity.x = 0.7; // car sqrt(2x^2) = 1 => x ≈ 0,7
//                 transform->velocity.y = -0.7;
//             }
//             else if (keystates[SDL_SCANCODE_S])
//             { // -> droite + bas
//                 transform->velocity.x = 0.7;
//                 transform->velocity.y = 0.7;
//             }
//             else
//                 transform->velocity.x = 1.0;
//         }
//         if (keystates[SDL_SCANCODE_A])
//         { // Q -> gauche
//             dir = 1;
//             sprite->spriteflip = SDL_FLIP_HORIZONTAL;
//             if (keystates[SDL_SCANCODE_W])
//             { // -> gauche + haut
//                 transform->velocity.x = -0.7;
//                 transform->velocity.y = -0.7;
//             }
//             else if (keystates[SDL_SCANCODE_S])
//             { // -> gauche + bas
//                 transform->velocity.x = -0.7;
//                 transform->velocity.y = 0.7;
//             }
//             else
//                 transform->velocity.x = -1.0;
//         }

//         // Gestion du choix de l'animation
//         if (keystates[SDL_SCANCODE_W] ||
//             keystates[SDL_SCANCODE_S] ||
//             keystates[SDL_SCANCODE_D] ||
//             keystates[SDL_SCANCODE_A])
//             sprite->Play("Walk");
//         else
//             sprite->Play("Idle");

//         // Gestion du tir
//         if (keystates[SDL_SCANCODE_L] && entity->GetComponent<Stat>().IsShotReady())
//         {
//             if (transform->velocity.x == 0.0 && transform->velocity.y == 0.0)
//             { // puisque je définit le projectile en fonction de la vitesse du perso, il faut que je couvre le cas ou il est immobile
//               // + transform->height / 2 * transform->scale.y
//               // + (1 * 8 + transform->width / 2) * transform->scale.x
//                 if (dir == 0)
//                 {
//                     Game::gobjs->CreateProjectile(Vector2(transform->position.x, transform->position.y),
//                                                   Vector2(20.0, 0.0),
//                                                   10000, 2, entity->GetComponent<Stat>().GetWeapon());
//                 }
//                 else if(dir == 1)
//                 {
//                     Game::gobjs->CreateProjectile(Vector2(transform->position.x, transform->position.y),
//                     Vector2(-20.0, 0.0),
//                     10000, 2, entity->GetComponent<Stat>().GetWeapon());
//                 }
//                 else if (dir == 2)
//                 {
//                     Game::gobjs->CreateProjectile(Vector2(transform->position.x, transform->position.y),
//                     Vector2(0.0, -20.0),
//                     10000, 2, entity->GetComponent<Stat>().GetWeapon());
//                 }
//                 else if (dir == 3)
//                 {
//                     Game::gobjs->CreateProjectile(Vector2(transform->position.x, transform->position.y),
//                     Vector2(0.0, 20.0),
//                     10000, 2, entity->GetComponent<Stat>().GetWeapon());
//                 }
//             }
//             else
//                 Game::gobjs->CreateProjectile(Vector2(transform->position.x,  // + (transform->velocity.x * 8 + transform->width/2) * transform->scale,
//                                                       transform->position.y), // + (transform->velocity.y * 8 + transform->height/2) * transform->scale),
//                                               Vector2(transform->velocity.x * 20.0,
//                                                       transform->velocity.y * 20.0),
//                                               10000, 2, entity->GetComponent<Stat>().GetWeapon());
//             entity->GetComponent<Stat>().SetLastShot();

//             // sprite->play("Shoot"); // pas encore animé MDRRRRLOOLOLL
//         }

//         // changement d'arme
//         if (keystates[SDL_SCANCODE_K] && SDL_GetTicks() - lastAction > actionDelay)
//         {
//             std::cout << "changement d'arme" << std::endl;
//             entity->GetComponent<Stat>().ChangeWeapon();
//             lastAction = SDL_GetTicks();
//         }
//     }
// }
