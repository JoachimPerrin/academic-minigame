#include <iostream>
#include "MapManager.hpp"
#include "Game.hpp"

using namespace ecs;
MapManager::MapManager()
    : currentMap(nullptr), textureID("defaultString"), mapScale(4), tileSize(32)
{
}

MapManager::~MapManager() { delete currentMap; }

void MapManager::AddMap(std::string mapID, std::string mapPath, int sizeX, int sizeY)
{
    maps[mapID] = std::make_tuple(mapPath, sizeX, sizeY);
}

void MapManager::LoadMap(std::string tileMapID, std::string tileSetID)
{
    auto it = maps.find(tileMapID);
    if (it != maps.end())
    {
        delete currentMap;
        currentMap = new Map(tileSetID, mapScale, tileSize);

        // Accéder aux éléments du tuple directement
        std::string path = std::get<0>(it->second);
        int sizeX = std::get<1>(it->second);
        int sizeY = std::get<2>(it->second);

        currentMap->LoadMap(path, sizeX, sizeY);
    }
    else
    {
        std::cerr << "Map ID " << tileMapID << " not found!" << std::endl;
    }
}

/*je veux ajouter un vecteur de coordonnées d'enemis, avec une fonction spawnEnemies qui parcours et créé les entités après avoir clear*/
void MapManager::ChangeMap(std::string newMapID, std::string newSetID)
{
    Game::manager.ClearEntities(-1);
    // SpawnEnemies( enemyType, );
    LoadMap(newMapID, newSetID);
}