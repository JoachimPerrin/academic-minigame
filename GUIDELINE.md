# Conventions:

## Usage de GIT

1. Une Branche = une fonctionnalité
2. On ne code jamais dans le main (le main doit être toujours une version fonctionnelle)
3. Quand une branche est prête et testée on fait une pull request vers le main actuel (avec un squash, pour réunir tout les commits en un seul). Les merge conflics doivent être résolus dans les branches annexe pour ne merge qu'en ff dans la branche main.
4. Une fois qu'une branche a été merge dans le main, toutes les branches doivent merge (pull) le main pour s'actualiser avec le main.

## Programmation

1. fichiers markdown:
    - README.md pour installation, explication (le jeu, les règles.¸comment lancer le jeu...), (rapport)
    - TODO.md pour les tâches à faire
    - GUIDELINE.md pour les conventions etc...
2. Commentaires:
    - en anglais
    - avec Doxygen
    - en haut des fichiers .hpp pour explication globale de la classe
    - devant chaque fonction, dans le fichier .cpp
    - /**/ Pour les commentaire dvt des fonctions, variables etc. // Pour des ajouts de détails devant des blocs de code obscure
    - Usage de TODO: et FIXME: pour les commentaires temporaires (peuvent s'abstraire aux conventions puisqu'ils tej à l'avenir)
3. Conventions de nommage:
    - en anglais
    - Méthodes commencent par une majuscule, attribut par une minuscule.
    - Usage de camelCase ou PascalCase pour les noms composés
4. Pour l'écriture des classes:
    - public avant private pour montrer l'interface directement.
    - méthodes avant attributs
    - groupements entre les méthodes/attributs de même genre (ex: getters, setters...) si il y en a trop
5. Noms de Variables/Fonction:
    - Nom des inputs de machine a etat: `I_NOM_DE_LA_VARIALE`
    - Nom des actions de machine a etat: `A_NOM_DE_LA_VARIALE`
    - Nom des states de machine a etat: `S_NOM_DE_LA_VARIAL`
    - ...
6. Logique de programmation:
    - Les Managers peuvent uniquement lire et avoir accès aux components des entités par contre c'est uniquement dans ComponentManager qu'existe les fonctions qui modifient les components des entités.
## *eventuellement d'autres choses dans lesquels définir des conventions?*

# Ressources

- Explications Machine à état (FSM): http://tvaira.free.fr/dev/c/automate.pdf
- Playlist de lets make games sur laquelle ce projet est basé: https://youtube.com/playlist?list=PLhfAbcv9cehhkG7ZQK0nfIGJC_C-wSLrx&si=NtFsQrEc0Quqj-22
- Explications relativement complète de git: https://youtu.be/S7XpTAnSDL4?si=PBGJvQREHjxddQ6R
- Playlist de cours en C++ de `formation video` pour un complément par rapport à notre cours: https://youtube.com/playlist?list=PLrSOXFDHBtfFKOzlm5iCBeXDTLxXdmxpx&si=CNymPn_QOT5qgDUn
