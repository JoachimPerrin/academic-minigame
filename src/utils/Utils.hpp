#ifndef UTILS_HPP
#define UTILS_HPP

#include <SDL2/SDL.h>
#include <iostream>
#include <string>


// ==================== FSM =============================

// ...


// ----------- PLAYINGSTATE -----------

const int nbGeneralInputs = 8;
enum GeneralInputs { //Commun à, et utilisé par, tous les handleevent des state globaux (playingState, menuState...). (Keyboard inputs ou autre)
    I_SPACE,
    I_ATTACK_P1,
    I_ATTACK_P2,
    I_MOVE_P1,   
    I_MOVE_P2,
    I_INV_P1,
    I_INV_P2,
    I_PAUSE
    // I_TIMER = 7
};

// Définition des états de PlayingState
enum PlayingStates { //TODO: METTRE A JOUR pr l'instant se fier uniquement au tableau
    S_SOLO = 0,
    S_MULTI = 1,
    S_IDLE = 2, //Inventaire dans la fsm du joueur
};

// Il faut rajouter les inputs + action pour changer les states de Playing States (OPTIONEL)
// Il faut rajouter matric transition pour Playingstate + matrice action (OPTIONEL)

// enum PlayingInputs { // Pour changer les etats de Playing State
//     I_PAUSE = 0,
//     I_QUIT = 1,
//     I_SWITCH_DAY = 2, 
//     
// };

enum PlayingActions {   // Actions qui son pour les entites (pas pour playing State)
    A_NONE,
    A_MOVE_P1,
    A_MOVE_P2,
    A_ATTACK_P1,
    A_ATTACK_P2,
    A_JUMP,
    A_RUN,
    A_USE_ITEM,
    A_INVENTORY_P1,
    A_INVENTORY_P2
    // A_CRAFT = 11 ...
};

//Il faut avoir acces aux entrées que prend les machines a etat des joueurs (et compononents avec machine a etat)


// ------------ ENTITIES ------------
// États du Joueur
const int nbPlayerStates = 3;
enum PlayerState { S_IDLE_JOUEUR, S_RUNNING_JOUEUR, S_INVENTORY_JOUEUR };

// Entrées du Joueur
const int nbPlayerInputs = 4;
enum PlayerInput { I_MOVE, I_INVENTORY, I_ATTACK, I_NONE};

// Actions du Joueur
enum PlayerAction { };

// ----------- BOUTTON -----------
// ...
extern SDL_Scancode keysP1[7];
extern SDL_Scancode keysP2[7];

void ExitWithError(const std::string errorMessage, SDL_Window *activeWindow = nullptr, SDL_Renderer *activeRenderer = nullptr);

std::ostream &operator<<(std::ostream &stream, const SDL_Rect &rect);
std::ostream &operator<<(std::ostream &stream, const SDL_FRect &rect);

SDL_Rect FRectToRect(const SDL_FRect &fRect);

#endif