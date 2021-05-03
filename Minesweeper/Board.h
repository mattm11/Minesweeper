#pragma once
#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "Random.h"
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <cmath>
using namespace std;

class Board
{
	sf::Sprite smile;
	sf::Sprite test1;
	sf::Sprite test2;
	sf::Sprite test3;
	sf::Sprite mineOnes;
	sf::Sprite mineTens;
	sf::Sprite mineHundreds;
	sf::Sprite mineNeg;
	int columns;
	int rows;
	int mines;
	int mineCount;
	bool debugMode;
	bool gameWin;
	bool gameLose;
	vector<vector<Tile>> tiles;
public:
	Board();
	void NewGame();
	void TestBoard1();
	void TestBoard2();
	void TestBoard3();
	void DebugMode();
	void MineCounter();
	bool CheckWin();
	bool CheckLose();
	void WinBoard();
	void LoseBoard();
	void SetNeighbors();
	int GetColumns();
	int GetRows();
	void ClickFace(int mouseX, int mouseY);
	void ClickTest1(int mouseX, int mouseY);
	void ClickTest2(int mouseX, int mouseY);
	void ClickTest3(int mouseX, int mouseY);
	void LeftClickTile(int mouseX, int mouseY);
	void RightClickTile(int mouseX, int mouseY);
	void Draw(sf::RenderWindow& window);
	void DrawMineCount(sf::RenderWindow& window);
	vector<vector<Tile>> GetTiles();
};

