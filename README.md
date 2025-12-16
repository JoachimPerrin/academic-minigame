# ByteQuest IV : Piston Pété  
**Joachim Perrin - Dilhan Emir - Rami Aridi - Grigor Pelibossian**  

## 📀 Installation  
### 🛠️ Dépendances : bibliothèque SDL2  

#### 🔹 Outils essentiels  
Avant de compiler le projet, assurez-vous d'avoir les outils nécessaires installés :  
```bash
apt-get update && apt-get install g++ build-essential make
```

#### 🔹 Installation des dépendances SDL2  

##### 🖥️ macOS  
```bash
brew install sdl2 sdl2_ttf sdl2_image sdl2_mixer
```

##### 🐧 Ubuntu  
```bash
apt-get update && apt-get install libsdl2-2.0-0 libsdl2-image-2.0-0 libsdl2-ttf-2.0-0 libsdl2-mixer-2.0-0
```

---

### 🎮 Installation et exécution du jeu  

Clonez le projet et compilez-le avec `make` :  
```bash
cd /chemin/du/dossier/souhaité
git clone -b semi-final https://github.com/JoachimPerrin/Game.git
cd Game
make
```

Lancez ensuite le jeu avec :  
```bash
make run
```

---

## 📚 Présentation du projet  
ByteQuest IV est un jeu basé sur un **système Entity-Component-System (ECS)** et une **Finite State Machine (FSM)**.  
Voici un aperçu des concepts clés que nous avons développés :  

### 🏗️ **Entity-Component-System (ECS)**  

![Diagramme UML ECS](out/puml/[Classe]ECS/ECS_Class_Diagram.png?raw=true  "Diagramme UML du système ECS")  

L’**ECS** est le socle de notre architecture. Il permet de modéliser chaque objet du jeu comme une **entité** à laquelle on peut attacher divers **composants** (components) qui définissent son comportement et ses caractéristiques.  

- Chaque entité représente un objet du jeu (joueur, ennemis, obstacles...).  
- Les **composants** définissent ses propriétés et actions (position, mouvement, sprites...).  
- L’**EntitiesManager** est responsable de la gestion du cycle de vie des entités et de leur organisation en groupes.  

---

### 🎭 **Finite State Machine (FSM)**  

![Diagramme UML FSM](out/puml/[Classe]FSM_Player/[Classe]FSM_Player.png?raw=true  "Diagramme UML de la FSM du joueur")  
*(Ce diagramme illustre la structure des états du joueur et les transitions possibles.)*  

![Diagramme UML Séquence](out/puml/[State]FSM_Player/[State]FSM_Player.png?raw=true  "Diagramme UML de séquence pour l’exécution du jeu")  
*(Ce diagramme explique la manière dont le jeu gère les états et événements en temps réel.)*  

Notre **FSM** gère les différents états du joueur (ex. : **Idle, Running, Attacking, Inventory**) et les transitions entre ces états en fonction des entrées du joueur.  

---

## 💡 À venir  
Nous avons plusieurs améliorations prévues, notamment :  
✔️ Ajout de nouvelles mécaniques de gameplay.  
✔️ Optimisation des performances du moteur ECS.  
✔️ Amélioration des graphismes et animations.  

Merci d’essayer **ByteQuest IV : Piston Pété** ! 🚀  

