#ifndef MAP_H
#define MAP_H

#include <string>

class Map {
    private:
        std::string textureID;
        int scale;
        int tilesize;

    public:
        Map(std::string _textureID, int _scale, int _tileSize);
        ~Map();
        void loadMap(const std::string& _filePath, int _mapSizeX, int _mapSizeY);
        void addTile(int _sourceRectX, int _sourceRectY, int _x, int _y);
};

#endif