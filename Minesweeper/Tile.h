#pragma once
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include <vector>
using namespace std;

class Tile
{
	// Background Tile
	sf::Sprite background;

	// Foreground Tile
	sf::Sprite foreground;

	// Special Tile
	sf::Sprite special;

	bool isHidden;
	bool isFlagged;
	bool isMine;
	bool debug;
	vector<Tile*> neighbors;
	int maxNeighbors;
	int xPos;
	int yPos;

public:
	Tile();
	void ToggleFlag();
	void MineOff();
	bool IsMine();
	bool IsHidden();
	bool IsFlagged();
	vector<Tile*> GetNeighbors();
	void Reveal();
	void DebugToggle();
	void Hide();
	void SetMine();
	void SetNeighbors(vector<Tile*> neighbors);
	void SetMaxNeighbors(int number);
	void SetForeground(string image);
	void SetBackground(string image);
	void SetSpecial(string image);
	void SetPosition(int x, int y);
	void LeftClick(int mouseX, int mouseY);
	void RightClick(int mouseX, int mouseY);
	void Draw(sf::RenderWindow& window);
	sf::Sprite GetSprite();
};

