#ifndef MINESWEEPER_TEXTUREMANAGER_H
#define MINESWEEPER_TEXTUREMANAGER_H
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>

using namespace std;

/* 
   The texture handler was provided by professor Joshua Fox. 
   He provided the classes when assigning the final project for programming 2 (Minesweeper) 
   which also dealt with SFML and we decided to use them since our project was also helped by their functionality. 
   The texture manager class helps load in image files into sprites.
*/

class TextureManager {

    static unordered_map<string, sf::Texture> textures;
    static void LoadTexture(const string& textureName);
public:
    static sf::Texture& GetTexture(const string& textureName);
    static void Clear();



};


#endif //MINESWEEPER_TEXTUREMANAGER_H

