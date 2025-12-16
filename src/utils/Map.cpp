#include "Map.hpp"
#include "ECS.hpp"
#include "Tile.hpp"
#include "Transform.hpp"
#include "Collider.hpp"
#include "Sprite.hpp"
#include "Game.hpp"
#include <iostream>
#include <fstream>

extern ecs::EntitiesManager manager;

Map::Map(std::string texID, int mScale, int tSize)
    : textureID(texID), tileSize(tSize), mapScale(mScale), scaledTileSize(mScale * tSize)
{
}

void Map::LoadMap(std::string path, int sizeX, int sizeY)
{
    bounds.x = sizeX * scaledTileSize;
    bounds.y = sizeY * scaledTileSize;

    std::fstream mapFile;
    mapFile.open(path);
    if (!mapFile.is_open())
    {
        std::cerr << "Was not able to open the tile set file" << std::endl;
        return;
    }

    char c;
    int srcX, srcY;

    for (int y = 0; y < sizeY; y++)
    {
        for (int x = 0; x < sizeX; x++)
        {
            mapFile.get(c);
            srcY = (c - '0') * tileSize; // Convert char to int
            mapFile.get(c);
            srcX = (c - '0') * tileSize; // Convert char to int
            AddTile(srcX, srcY, x * scaledTileSize, y * scaledTileSize);
            mapFile.ignore();
        }
    }
    mapFile.ignore();

    for (int y = 0; y < sizeY; y++)
    {
        for (int x = 0; x < sizeX; x++)
        {
            mapFile.get(c);
            if (c != '-')
            {
                srcY = (c - '0') * tileSize;
                mapFile.get(c);
                srcX = (c - '0') * tileSize;

                int xCentered = x * scaledTileSize + scaledTileSize / 2;
                int yCentered = y * scaledTileSize + scaledTileSize / 2;
                int digit = c - '0';
                auto &tcol(Game::manager.AddEntity());
                tcol.AddComponent<ecs::Transform>();
                tcol.AddComponent<ecs::Sprite>("ColMark", false);
                switch (digit)
                {
                case 0: // barre gauche
                    tcol.GetComponent<ecs::Transform>().SetPos(Vector2(x * scaledTileSize, y * scaledTileSize));
                    tcol.GetComponent<ecs::Transform>().SetSize(Vector2(scaledTileSize / 2, scaledTileSize));
                    tcol.AddComponent<ecs::AABBCollider>("terrain");
                    break;
                case 1: // barre droite
                    tcol.GetComponent<ecs::Transform>().SetPos(Vector2(xCentered, y * scaledTileSize));
                    tcol.GetComponent<ecs::Transform>().SetSize(Vector2(scaledTileSize / 2, scaledTileSize));
                    tcol.AddComponent<ecs::AABBCollider>("terrain");
                    break;
                case 2: // barre haut
                    tcol.GetComponent<ecs::Transform>().SetPos(Vector2(x * scaledTileSize, y * scaledTileSize));
                    tcol.GetComponent<ecs::Transform>().SetSize(Vector2(scaledTileSize, scaledTileSize / 2));
                    tcol.AddComponent<ecs::AABBCollider>("terrain");
                    break;
                case 3: // barre bas
                    tcol.GetComponent<ecs::Transform>().SetPos(Vector2(x * scaledTileSize, yCentered));
                    tcol.GetComponent<ecs::Transform>().SetSize(Vector2(scaledTileSize, scaledTileSize / 2));
                    tcol.AddComponent<ecs::AABBCollider>("terrain");
                    break;
                case 4: // coin bas gauche
                    tcol.GetComponent<ecs::Transform>().SetPos(Vector2(x * scaledTileSize, yCentered));
                    tcol.GetComponent<ecs::Transform>().SetSize(Vector2(scaledTileSize / 2, scaledTileSize / 2));
                    tcol.AddComponent<ecs::AABBCollider>("terrain");
                    break;
                case 5: // coin bas droite
                    tcol.GetComponent<ecs::Transform>().SetPos(Vector2(xCentered, yCentered));
                    tcol.GetComponent<ecs::Transform>().SetSize(Vector2(scaledTileSize / 2, scaledTileSize / 2));
                    tcol.AddComponent<ecs::AABBCollider>("terrain");
                    break;
                case 6: // coin haut gauche
                    tcol.GetComponent<ecs::Transform>().SetPos(Vector2(x * scaledTileSize, y * scaledTileSize));
                    tcol.GetComponent<ecs::Transform>().SetSize(Vector2(scaledTileSize / 2, scaledTileSize / 2));
                    tcol.AddComponent<ecs::AABBCollider>("terrain");
                    break;
                case 7: // coin haut droite
                    tcol.GetComponent<ecs::Transform>().SetPos(Vector2(xCentered, y * scaledTileSize));
                    tcol.GetComponent<ecs::Transform>().SetSize(Vector2(scaledTileSize / 2, scaledTileSize / 2));
                    tcol.AddComponent<ecs::AABBCollider>("terrain");
                    break;
                case 8:
                    tcol.GetComponent<ecs::Transform>().SetPos(Vector2(x * scaledTileSize, y * scaledTileSize));
                    tcol.GetComponent<ecs::Transform>().SetSize(Vector2(scaledTileSize, scaledTileSize));
                    tcol.AddComponent<ecs::AABBCollider>("terrain");
                    break;
                default:
                    break;
                }
                tcol.AddGroup(Game::collidable);
                mapFile.ignore();
            }
            else
            {
                mapFile.ignore();
                mapFile.ignore();
            }
        }
    }
    mapFile.close();
}

void Map::AddTile(int srcX, int srcY, int xpos, int ypos)
{
    auto &tile(Game::manager.AddEntity());
    tile.AddComponent<ecs::Tile>(srcX, srcY, xpos, ypos, tileSize, mapScale, textureID);
    tile.AddGroup(Game::maps);
}