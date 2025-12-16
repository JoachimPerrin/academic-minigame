# Objectifs globaux du jeu
- Système de profondeur basique avec deux groupes (underlay, overlay) respectivement render avant et après le joueur
- Système de craft avec ressources collectable
- inventaire avec livre de recette
- Cycle d'invasions de monstres (jour/nuit) pour passer de phases de farming à pve
    * farming = cultiver la terre, gestion du temps pour récup de la bouffe
        manger = vie++
        faim critique = vie--
    * enemies tentent de détruire les culture ou le joueur
- outils : 
    * hache = récolte bois
    * pioche = récolte ST
    * pelle = cultiver
    * épée = damage cac
    * arc = damage distance
- entitées non hostile
- ressources divisée en 3 types :
    * pierre
    * bois
    * terre
- nourriture diviséé en 2 types :
    * plante
    * viande

Revoir TOUS les fichiers pour :
    laisser uniquement les includes nécessaires
    les faire fonctionner

# À faire au début du projet
Trouver un titre, thème
Graphique : palette + efforts pyxeledit,
Gameplay cool etc

# Idées de tâches à se répartir
- Machine à état (FSM) *(À définir en premier lieu)*

- Système de collisions:  
    - Cirular pour player et enemies ->  collision avec rebond (force normale sur les deux entitées (ajout d'une masse dans les stats?))
    - AABB pour l'environnement -> collisions Circular:AABB avec glissement (force projeté tangeante (amortissement visqueux?))

- Système d'inputs  
    - KeyboardTracking component : permet de stocker les touches actives dans un tableau par exemple  
    - InputManager : selon l'objet, réagit aux inputs

- Système de Widgets  
    
- Multijoueur:  
    Écran Scyndé verticalement
    si deter, faire en sorte que P2 puisse être en réseau

- Système de son avec SDL_mixer  
    component
    manager
    ...

- Enemies  
    Créer une sorte d'ia basique pour les enemies
    Leur donner une zone (cercle autour d'un point)
    Possible d'en faire des meutes

- Système de widgets (UI)  
    Button/Toggle/Slider/Dropdown components (dérivés de Widget?)
    manager pour les utiliser facilement (création du menu etc)

- Possibilité de sauvegarder et charger les parties

- Diagrammes UML  
    - de classes pour décrire tout le system d'ecs
    - de séquence pour décrire le déroulement du jeu
    - d'état pour décrire la fsm  

*Avec plantUml + intégration dans le README*

- Mise au propre du projet
    - Rédaction du README.md
    - Maintenance du repo github (important pour le mettre en publique super propre)
    - Debugging avec valgrind/gdb pour checker les memleaks
    - Messages de debug propre *(ajouter un logger in game?)*
    - Licence pour SDL2?
    - Tests avec CTest *(Boost.Test ??)*    
    - Améliorer la DA


# TODO Rami
- Component : Machine a etat
- Groupe : Controllable, Machine a etat (generique), statique (on peut creer un groupe clickable) (on peut creer un grp en fcontion des entree des machines a etat de chaque entites)
- Remarque: les input managers vont chercher les objet controllable (car ils sont affecte par input) et les objets machine a etat (car ils vont potentiollement changer d'etat)
- Da'utre fonction de logique de jeu appelleront independemment quand il se passe des choses, les composants de machine a etat pr changer leurs etat
- Les fonctions handleevent dans les etats generaux (playingstate...) sont les inputs manager des etats.(d'autre fonction de la classe pr les logique du jeu. Par exemple dans playingstate appelle (dans une autre fonction) les machines etat des entites du jeu au fur et a mesure en fonction de la machine a etat du playing state).
- Le handle event des etats generaux consiste a enoyer les inputs de utilisateur en inputs propre a chaque entites (en fonction de l'etat du playing state), ET a gerer les entrees pour potentiellement changer d'etat generale (passer de menustate a playingstate)
- Game.cpp est notre machine a etat
- Dans les input manager de chaque state on verifie par exemple quand on recupere un mousedown dans le groupe controllable, on envoie l'entre click au bouttons si clickPos est dans le label du bouton, et autre entree aux autres entites
- Machine a etat doit prendre en entree les enums (les inputs et le states)
- Les inputs doivent etre global, accessible par les managers et les entitees
- Les types (state+inputs) et les machines de transition, actions doivent etre prisent en arguments du components machine a etat.
- Exemple de code de Input manager:
    ```
    player.handleinput(input) //input de type PlayerInputs
    button.handleinput(input) //input de type ButtonInputs
    ```
-


- Bouton c'est une entité qui a un component machine a etat et un component labels/sprite
- KeyboardController doit etre supprimé (la logique de keyboardController doit etre transferer a playingstate qui gere les entrées en fonction de l'etat actuel...)

- En gros a créer/modifier:
    - Entite: Bouton
    - Compononent: Labels, FSM
    - Manager: InputManager (Integrant la logique de keygbioard controller et la supprimé), Modifier le handle event du playingstate et le keyboard controller/transform actuel.
    - Implemen

- Changer le event = game.event et garder le meme event partout
## Plus Tard
- Classe Widget abstraite avec bouton enfant de widget (pr ajouter slider etc...)
- Voir comment mettre deux joueurs (un mode en plus dans playing State? ou un deuxieme playing state ou voir comment avec day and night)
- Faire tout un move_joueur_a et move_joueur_b (actions) et faire des fonctions pr chacun et faire en sorte que dans le switch case on rentre dans ca quel que soit la touche appuye (haut bas droite gauche) + OPTIMISER LA FONCTION MOVE (pr prendre en compte haut+ droite etc..)
- Gerer priorite de droite gauche, et haut, bas (+ verifier si pas mieux de tjrs executer l'action MOVE)
- Verifier le tout d'avant, implementer la component machine a etat
-
- Verifier le nombre de input pr chaque machine a etat (creer variable etc...)
- Voir Si peut etre ne pas mettre le mode Running et Idle
- Semaine pro git merge les commits
## Notes
- Chaque entité doit etre dans un groupe (voir si créer nouveau groupe selon besoin). C'est pour les manager qui utilise ce tableau de groupe
- Je pense game.cpp = machine a etat

# Pour aller loiinnn
- Statistiques de performances
- Utiliser des threads pour bien comprendre (pour quels usages?)
- Publier le jeu??? (ultra propre et brillerait cv)
- Faire en sorte qu'avec docker on puisse tester sur plus de platforms (ajouter des dockerfiles, et des services dans le docker-compose)
- Faire ça en réseau pour multijoueur ??? Réseau avec SDL_net ????
- Statistiques de performances
- Utiliser des threads pour bien comprendre (pour quels usages?)
- Publier le jeu??? (ultra propre et brillerait cv)
- Faire en sorte qu'avec docker on puisse tester sur plus de platforms (ajouter des dockerfiles, et des services dans le docker-compose)
- Faire ça en réseau pour multijoueur ??? Réseau avec SDL_net ????
(docker) Créer un stage git ou je récup le projet depuis github et install les dépendances communes aux stages build et devel pour plus rapide
- L'optimiser si vraiment il y a le temps
- L'optimiser si vraiment il y a le temps
