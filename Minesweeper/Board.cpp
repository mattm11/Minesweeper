#include "Board.h"

Board::Board()
{
	NewGame();
}

void Board::NewGame()
{
	// If starting new game, make gameWin and gameLose false
	gameWin = false;
	// Clear vector to start new game
	tiles.clear();
	// Getting columns, rows, and mines
	ifstream file;
	file.open("boards/config.cfg");
	string line;
	getline(file, line, '\n');
	this->columns = stoi(line);
	getline(file, line, '\n');
	this->rows = stoi(line);
	getline(file, line, '\n');
	this->mines = stoi(line);
	this->mineCount = mines;

	// Setting UI sprites
	smile.setTexture(TextureManager::GetTexture("face_happy"));
	test1.setTexture(TextureManager::GetTexture("test_1"));
	test2.setTexture(TextureManager::GetTexture("test_2"));
	test3.setTexture(TextureManager::GetTexture("test_3"));
	smile.setPosition(((columns * 32) / 2 - 32), rows * 32);
	test1.setPosition(columns * 32 - (64 * 3), rows * 32);
	test2.setPosition(columns * 32 - (64 * 2), rows * 32);
	test3.setPosition(columns * 32 - (64 * 1), rows * 32);
	// Setting up mine counter
	mineOnes.setTexture(TextureManager::GetTexture("digits"));
	mineOnes.setTextureRect(sf::IntRect(0 * 21, 0, 21, 32));
	mineOnes.setPosition(63, rows * 32);
	mineTens.setTexture(TextureManager::GetTexture("digits"));
	mineTens.setTextureRect(sf::IntRect(0 * 21, 0, 21, 32));
	mineTens.setPosition(42, rows * 32);
	mineHundreds.setTexture(TextureManager::GetTexture("digits"));
	mineHundreds.setTextureRect(sf::IntRect(0 * 21, 0, 21, 32));
	mineHundreds.setPosition(21, rows * 32);
	mineNeg.setTexture(TextureManager::GetTexture("digits"));
	mineNeg.setTextureRect(sf::IntRect(10 * 21, 0, 21, 32));
	mineNeg.setPosition(0, rows * 32);

	// Resizing the rows first to allow for pushing back of column values
	tiles.resize(rows);
	vector<int> randNums;
	int random;
	bool duplicate;
	// Populate random number array in amount of mines
	while (randNums.size() < 50)
	{
		duplicate = false;
		random = Random::Int(0, (columns * rows) - 1);
		for (int i = 0; i < randNums.size(); i++)
		{
			if (random == randNums[i])
				duplicate = true;
		}
		if (duplicate)
			continue;
		else
			randNums.push_back(random);
	}
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			Tile tile;
			// if the random num equals the nth tile in the board, it becomes a mine
			for (int x = 0; x < mines; x++)
			{
				if (randNums[x] == ((i * columns) + j))
				{
					tile.SetForeground("mine");
					tile.SetMine();
				}
			}
			tile.SetPosition(j * 32, i * 32);
			tiles[i].push_back(tile);
		}
	}
	SetNeighbors();
	MineCounter();
	debugMode = false;
}

void Board::TestBoard1()
{
	ifstream file;
	file.open("boards/testboard1.brd");
	string line;
	// Reset game if starting new
	gameWin = false;
	smile.setTexture(TextureManager::GetTexture("face_happy"));
	// Have to resize the amount of rows before we push back to certain rows
	mines = 0;
	tiles.clear();
	tiles.resize(rows);
	while (!file.eof())
	{
		// Iterate by row first
		for (int i = 0; i < rows; i++)
		{
			getline(file, line, '\n');
			// Iterating through each row by amount of columns
			for (int j = 0; j < columns; j++)
			{
				Tile tile;
				// Setting position equal to their appropriate position
				tile.SetPosition(j * 32, i * 32);
				// If the value of the character read is 1, make it a mine
				if (line[j] == '1')
				{
					tile.SetMine();
					mines++;
				}
				// Adding columns amount of tiles until we go onto the next row
				tiles[i].push_back(tile);
			}
		}
	}
	MineCounter();
	SetNeighbors();
}

void Board::TestBoard2()
{
	ifstream file;
	file.open("boards/testboard2.brd");
	string line;
	// Reset game if starting new
	gameWin = false;
	smile.setTexture(TextureManager::GetTexture("face_happy"));
	// Have to resize the amount of rows before we push back to certain rows
	mines = 0;
	tiles.clear();
	tiles.resize(rows);
	while (!file.eof())
	{
		// Iterator by row first
		for (int i = 0; i < rows; i++)
		{
			getline(file, line, '\n');
			// Iterating through each row by amount of columns
			for (int j = 0; j < columns; j++)
			{
				Tile tile;
				// Setting position equal to their position
				tile.SetPosition(j * 32, i * 32);
				// If the value of the character read is 1, make it a mine
				if (line[j] == '1')
				{
					tile.SetMine();
					mines++;
				}
				// Adding columns amount of tiles until we go onto the next row
				tiles[i].push_back(tile);
			}
		}
	}
	MineCounter();
	SetNeighbors();
}

void Board::TestBoard3()
{
	ifstream file;
	file.open("boards/testboard3.brd");
	string line;
	// Reset game if starting new
	gameWin = false;
	smile.setTexture(TextureManager::GetTexture("face_happy"));
	// Have to resize the amount of rows before we push back to certain rows
	mines = 0;
	tiles.clear();
	tiles.resize(rows);
	while (!file.eof())
	{
		// Iterator by row first
		for (int i = 0; i < rows; i++)
		{
			getline(file, line, '\n');
			// Iterating through each row by amount of columns
			for (int j = 0; j < columns; j++)
			{
				Tile tile;
				// Setting position equal to their position
				tile.SetPosition(j * 32, i * 32);
				// If the value of the character read is 1, make it a mine
				if (line[j] == '1')
				{
					tile.SetMine();
					mines++;
				}
				// Adding columns amount of tiles until we go onto the next row
				tiles[i].push_back(tile);
			}
		}
	}
	MineCounter();
	SetNeighbors();
}

void Board::DebugMode()
{
	if (!debugMode)
	{
		for (int i = 0; i < tiles.size(); i++)
		{
			for (int j = 0; j < tiles[0].size(); j++)
			{
				if (tiles[i][j].IsMine())
				{
					tiles[i][j].DebugToggle();
				}
			}
		}
		debugMode = true;
	}
	else if (debugMode)
	{
		for (int i = 0; i < tiles.size(); i++)
		{
			for (int j = 0; j < tiles[0].size(); j++)
			{
				if (tiles[i][j].IsMine())
				{
					tiles[i][j].DebugToggle();
				}
			}
		}
		debugMode = false;
	}
}

void Board::MineCounter()
{
	mineCount = mines;
	for (int i = 0; i < tiles.size(); i++)
		for (int j = 0; j < tiles[0].size(); j++)
		{
			if (tiles[i][j].IsFlagged())
				mineCount--;
		}


	// Ones Place
	if (abs(mineCount % 10) == 0)
		mineOnes.setTextureRect(sf::IntRect(0 * 21, 0, 21, 32));
	else if (abs(mineCount % 10) == 1)
		mineOnes.setTextureRect(sf::IntRect(1 * 21, 0, 21, 32));
	else if (abs(mineCount % 10) == 2)
		mineOnes.setTextureRect(sf::IntRect(2 * 21, 0, 21, 32));
	else if (abs(mineCount % 10) == 3)
		mineOnes.setTextureRect(sf::IntRect(3 * 21, 0, 21, 32));
	else if (abs(mineCount % 10) == 4)
		mineOnes.setTextureRect(sf::IntRect(4 * 21, 0, 21, 32));
	else if (abs(mineCount % 10) == 5)
		mineOnes.setTextureRect(sf::IntRect(5 * 21, 0, 21, 32));
	else if (abs(mineCount % 10) == 6)
		mineOnes.setTextureRect(sf::IntRect(6 * 21, 0, 21, 32));
	else if (abs(mineCount % 10) == 7)
		mineOnes.setTextureRect(sf::IntRect(7 * 21, 0, 21, 32));
	else if (abs(mineCount % 10) == 8)
		mineOnes.setTextureRect(sf::IntRect(8 * 21, 0, 21, 32));
	else if (abs(mineCount % 10) == 9)
		mineOnes.setTextureRect(sf::IntRect(9 * 21, 0, 21, 32));
	
	// Tens Place
	if (abs(mineCount % 100) < 10)
		mineTens.setTextureRect(sf::IntRect(0 * 21, 0, 21, 32));
	else if (abs(mineCount % 100) < 20)
		mineTens.setTextureRect(sf::IntRect(1 * 21, 0, 21, 32));
	else if (abs(mineCount % 100) < 30)
		mineTens.setTextureRect(sf::IntRect(2 * 21, 0, 21, 32));
	else if (abs(mineCount % 100) < 40)
		mineTens.setTextureRect(sf::IntRect(3 * 21, 0, 21, 32));
	else if (abs(mineCount % 100) < 50)
		mineTens.setTextureRect(sf::IntRect(4 * 21, 0, 21, 32));
	else if (abs(mineCount % 100) < 60)
		mineTens.setTextureRect(sf::IntRect(5 * 21, 0, 21, 32));
	else if (abs(mineCount % 100) < 70)
		mineTens.setTextureRect(sf::IntRect(6 * 21, 0, 21, 32));
	else if (abs(mineCount % 100) < 80)
		mineTens.setTextureRect(sf::IntRect(7 * 21, 0, 21, 32));
	else if (abs(mineCount % 100) < 90)
		mineTens.setTextureRect(sf::IntRect(8 * 21, 0, 21, 32));
	else if (abs(mineCount % 100) < 100)
		mineTens.setTextureRect(sf::IntRect(9 * 21, 0, 21, 32));

	// Hundreds Place
	if (abs(mineCount % 1000) < 100)
		mineHundreds.setTextureRect(sf::IntRect(0 * 21, 0, 21, 32));
	else if (abs(mineCount % 1000) < 200)
		mineHundreds.setTextureRect(sf::IntRect(1 * 21, 0, 21, 32));
	else if (abs(mineCount % 1000) < 300)
		mineHundreds.setTextureRect(sf::IntRect(2 * 21, 0, 21, 32));
	else if (abs(mineCount % 1000) < 400)
		mineHundreds.setTextureRect(sf::IntRect(3 * 21, 0, 21, 32));
	else if (abs(mineCount % 1000) < 500)
		mineHundreds.setTextureRect(sf::IntRect(4 * 21, 0, 21, 32));
	else if (abs(mineCount % 1000) < 600)
		mineHundreds.setTextureRect(sf::IntRect(5 * 21, 0, 21, 32));
	else if (abs(mineCount % 1000) < 700)
		mineHundreds.setTextureRect(sf::IntRect(6 * 21, 0, 21, 32));
	else if (abs(mineCount % 1000) < 800)
		mineHundreds.setTextureRect(sf::IntRect(7 * 21, 0, 21, 32));
	else if (abs(mineCount % 1000) < 900)
		mineHundreds.setTextureRect(sf::IntRect(8 * 21, 0, 21, 32));
	else if (abs(mineCount % 1000) < 1000)
		mineHundreds.setTextureRect(sf::IntRect(9 * 21, 0, 21, 32));
}

bool Board::CheckWin()
{
	for (int i = 0; i < tiles.size(); i++)
	{
		for (int j = 0; j < tiles[0].size(); j++)
		{
			if (!tiles[i][j].IsMine())
			{
				if (tiles[i][j].IsHidden())
					return false;
			}
			
		}
	}
	gameWin = true;
	return true;
}

bool Board::CheckLose()
{
	for (int i = 0; i < tiles.size(); i++)
	{
		for (int j = 0; j < tiles[0].size(); j++)
		{
			if (tiles[i][j].IsMine())
			{
				if (!tiles[i][j].IsHidden())
					return true;
			}

		}
	}
	return false;
}

void Board::WinBoard()
{
	if (CheckWin())
	{
		for (int i = 0; i < tiles.size(); i++)
			for (int j = 0; j < tiles[0].size(); j++)
				if (tiles[i][j].IsMine())
				{
					// Need to turn off the mine and then toggle flag so
					// it does not flicker between both
					tiles[i][j].MineOff();
					if (!tiles[i][j].IsFlagged())
						tiles[i][j].ToggleFlag();
				}
	}
	gameWin = true;
}

void Board::LoseBoard()
{
	if (CheckLose())
	{
		for (int i = 0; i < tiles.size(); i++)
			for (int j = 0; j < tiles[0].size(); j++)
				if (tiles[i][j].IsMine())
				{
					tiles[i][j].Reveal();
				}
	}
}

void Board::SetNeighbors()
{
	vector<Tile*> neighbors;
	string path;
	int maxNeighbors;
	for (int i = 0; i < tiles.size(); i++)
	{
		for (int j = 0; j < tiles[0].size(); j++)
		{
			neighbors.clear();
			path = "number_";
			// Top left corner case (3 neighbors max)
			if (i == 0 && j == 0)
			{
				if (!tiles[i][j + 1].IsMine())
					neighbors.push_back(&tiles[i][j + 1]);
				if (!tiles[i + 1][j].IsMine())
					neighbors.push_back(&tiles[i + 1][j]);
				if (!tiles[i + 1][j + 1].IsMine())
					neighbors.push_back(&tiles[i+1][j + 1]);
				maxNeighbors = 3;
			}
			// Top right corner case (3 neighbors max)
			else if (i == 0 && j == tiles[0].size() - 1)
			{
				if (!tiles[i][j - 1].IsMine())
					neighbors.push_back(&tiles[i][j - 1]);
				if (!tiles[i + 1][j - 1].IsMine())
					neighbors.push_back(&tiles[i + 1][j - 1]);
				if (!tiles[i + 1][j].IsMine())
					neighbors.push_back(&tiles[i + 1][j]);
				maxNeighbors = 3;
			}
			// Bottom left corner case (3 neighbors max)
			else if (i == tiles.size() - 1 && j == 0)
			{
				if (!tiles[i-1][j].IsMine())
					neighbors.push_back(&tiles[i - 1][j]);
				if (!tiles[i-1][j+1].IsMine())
					neighbors.push_back(&tiles[i - 1][j + 1]);
				if (!tiles[i][j+1].IsMine())
					neighbors.push_back(&tiles[i][j + 1]);
				maxNeighbors = 3;
			}
			// Bottom right corner case (3 neigbors max)
			else if (i == tiles.size() - 1 && j == tiles[0].size() - 1)
			{
				if (!tiles[i][j-1].IsMine())
					neighbors.push_back(&tiles[i][j - 1]);
				if (!tiles[i-1][j-1].IsMine())
					neighbors.push_back(&tiles[i - 1][j - 1]);
				if (!tiles[i-1][j].IsMine())
					neighbors.push_back(&tiles[i - 1][j]);
				maxNeighbors = 3;
			}
			// Left wall case (5 neighbors max)
			else if (j == 0)
			{
				if (!tiles[i-1][j].IsMine())
					neighbors.push_back(&tiles[i - 1][j]);
				if (!tiles[i-1][j+1].IsMine())
					neighbors.push_back(&tiles[i - 1][j + 1]);
				if (!tiles[i][j+1].IsMine())
					neighbors.push_back(&tiles[i][j + 1]);
				if (!tiles[i+1][j+1].IsMine())
					neighbors.push_back(&tiles[i + 1][j + 1]);
				if (!tiles[i+1][j].IsMine())
					neighbors.push_back(&tiles[i + 1][j]);
				maxNeighbors = 5;
			}
			// Upper wall case (5 neighbors max)
			else if (i == 0)
			{
				if (!tiles[i][j-1].IsMine())
					neighbors.push_back(&tiles[i][j - 1]);
				if (!tiles[i+1][j-1].IsMine())
					neighbors.push_back(&tiles[i + 1][j - 1]);
				if (!tiles[i+1][j].IsMine())
					neighbors.push_back(&tiles[i + 1][j]);
				if (!tiles[i+1][j+1].IsMine())
					neighbors.push_back(&tiles[i + 1][j + 1]);
				if (!tiles[i][j+1].IsMine())
					neighbors.push_back(&tiles[i][j + 1]);
				maxNeighbors = 5;
			}
			// Right wall case (5 neighbors max)
			else if (j == tiles[0].size() - 1)
			{
				if (!tiles[i-1][j].IsMine())
					neighbors.push_back(&tiles[i - 1][j]);
				if (!tiles[i-1][j-1].IsMine())
					neighbors.push_back(&tiles[i - 1][j - 1]);
				if (!tiles[i][j-1].IsMine())
					neighbors.push_back(&tiles[i][j - 1]);
				if (!tiles[i+1][j-1].IsMine())
					neighbors.push_back(&tiles[i + 1][j - 1]);
				if (!tiles[i+1][j].IsMine())
					neighbors.push_back(&tiles[i + 1][j]);
				maxNeighbors = 5;
			}
			// Bottom wall case (5 neighbors max)
			else if (i == tiles.size() - 1)
			{
				if (!tiles[i][j+1].IsMine())
					neighbors.push_back(&tiles[i][j + 1]);
				if (!tiles[i-1][j+1].IsMine())
					neighbors.push_back(&tiles[i - 1][j + 1]);
				if (!tiles[i-1][j].IsMine())
					neighbors.push_back(&tiles[i - 1][j]);
				if (!tiles[i-1][j-1].IsMine())
					neighbors.push_back(&tiles[i - 1][j - 1]);
				if (!tiles[i][j-1].IsMine())
					neighbors.push_back(&tiles[i][j - 1]);
				maxNeighbors = 5;
			}
			// Surrounded case (8 neighbors max)
			else
			{
				if (!tiles[i-1][j].IsMine())
					neighbors.push_back(&tiles[i - 1][j]);
				if (!tiles[i-1][j-1].IsMine())
					neighbors.push_back(&tiles[i - 1][j - 1]);
				if (!tiles[i][j-1].IsMine())
					neighbors.push_back(&tiles[i][j - 1]);
				if (!tiles[i+1][j-1].IsMine())
					neighbors.push_back(&tiles[i + 1][j - 1]);
				if (!tiles[i+1][j].IsMine())
					neighbors.push_back(&tiles[i + 1][j]);
				if (!tiles[i+1][j+1].IsMine())
					neighbors.push_back(&tiles[i + 1][j + 1]);
				if (!tiles[i][j+1].IsMine())
					neighbors.push_back(&tiles[i][j + 1]);
				if (!tiles[i-1][j+1].IsMine())
					neighbors.push_back(&tiles[i - 1][j + 1]);
				maxNeighbors = 8;
			}

			if (neighbors.size() == maxNeighbors)
			{
				path = "tile_revealed";
				tiles[i][j].SetForeground(path);
			}
			else
			{
				path += to_string(maxNeighbors - neighbors.size());
				tiles[i][j].SetForeground(path);
			}

			tiles[i][j].SetNeighbors(neighbors);
			tiles[i][j].SetMaxNeighbors(maxNeighbors);
		}
	}
}

int Board::GetColumns()
{
	return columns;
}

int Board::GetRows()
{
	return rows;
}

void Board::ClickFace(int mouseX, int mouseY)
{
	if (smile.getGlobalBounds().contains(mouseX, mouseY))
	{
		NewGame();
	}
}

void Board::ClickTest1(int mouseX, int mouseY)
{
	if (test1.getGlobalBounds().contains(mouseX, mouseY))
	{
		TestBoard1();
		cout << "Test 1 Loaded" << endl;
	}
}

void Board::ClickTest2(int mouseX, int mouseY)
{
	if (test2.getGlobalBounds().contains(mouseX, mouseY))
	{
		TestBoard2();
		cout << "Test 2 Loaded" << endl;
	}
}

void Board::ClickTest3(int mouseX, int mouseY)
{
	if (test3.getGlobalBounds().contains(mouseX, mouseY))
	{
		TestBoard3();
		cout << "Test 3 Loaded" << endl;
	}
}

void Board::LeftClickTile(int mouseX, int mouseY)
{
	for (int i = 0; i < tiles.size(); i++)
	{
		for (int j = 0; j < tiles[0].size(); j++)
		{
			if (!tiles[i][j].IsFlagged() && !CheckLose() && !CheckWin())
			{
				tiles[i][j].LeftClick(mouseX, mouseY);
			}
		}
	}
}

void Board::RightClickTile(int mouseX, int mouseY)
{
	for (int i = 0; i < tiles.size(); i++)
	{
		for (int j = 0; j < tiles[0].size(); j++)
		{
			if (!gameWin && !CheckLose())
			{
				tiles[i][j].RightClick(mouseX, mouseY);
			}
		}
	}
}

void Board::Draw(sf::RenderWindow& window)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
			tiles[i][j].Draw(window);
	}
	if (CheckWin())
	{
		WinBoard();
		smile.setTexture(TextureManager::GetTexture("face_win"));
	}
	else if (CheckLose())
	{
		LoseBoard();
		smile.setTexture(TextureManager::GetTexture("face_lose"));
	}
	window.draw(smile);
	/*window.draw(test1);
	window.draw(test2);
	window.draw(test3);*/
	DrawMineCount(window);
}

void Board::DrawMineCount(sf::RenderWindow& window)
{
	MineCounter();
	if (mineCount < 0)
		window.draw(mineNeg);
	window.draw(mineHundreds);
	window.draw(mineTens);
	window.draw(mineOnes);
}

vector<vector<Tile>> Board::GetTiles()
{
	return tiles;
}