#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include <iostream>
using std::unordered_map;
using std::string;

class TextureManager
{
	// Static so we don't need to create an instance of TextureManager to access its functions and it can live on in memory
	static unordered_map<string, sf::Texture> textures;
public:
	static void LoadTexture(string textureName); // LoadTexture("space");
	static sf::Texture& GetTexture(string textureName);
	static void Clear(); // Call this once at the end of main()
};

