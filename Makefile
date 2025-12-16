UNAME_S := $(shell uname -s)

CXX = g++
CXXFLAGS = -Wall -Werror -Wextra -g -std=c++17 -Isrc/ecs/components -Isrc/game -Isrc/man -Isrc/ecs -Isrc/game/game_states -Isrc/utils
LDFLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer # -lSDL2_net 

ifeq ($(UNAME_S), Darwin) # macOS
    CXXFLAGS += -I/opt/homebrew/include
    LDFLAGS += -L/opt/homebrew/lib
else # Linux
    CXXFLAGS += -I/usr/include
    LDFLAGS += -L/usr/lib
endif

ifeq ($(SANITIZE), 1)
    CXXFLAGS += -fsanitize=address
endif

# Fichiers source, objets, et executable
SRC = $(shell find src -name '*.cpp')
OBJ_DIR = build/obj
OBJ = $(patsubst src/%, $(OBJ_DIR)/%, $(SRC:.cpp=.o))
TARGET = build/bin/Game

# Cible par défaut
all: $(TARGET)

# Lien final pour générer l'exécutable
$(TARGET): $(OBJ)
	@ mkdir -p $(dir $@)
	@ $(CXX) $(CXXFLAGS) -o $@ $(OBJ) $(LDFLAGS)
	@ echo "Compilation terminée"

# Compilation des fichiers .cpp en fichiers .o
$(OBJ_DIR)/%.o: src/%.cpp
	@ mkdir -p $(dir $@)
	@ $(CXX) $(CXXFLAGS) -c $< -o $@
	@ echo "Compilation de $<"

# Nettoyage des fichiers générés
clean:
	rm -rf build/

# Exécution de l'exécutable
run: $(TARGET)
	./$(TARGET)
# Si on arrive à faire un script de lancement propre je jouit

# Cibles spéciales
.PHONY: all clean run test