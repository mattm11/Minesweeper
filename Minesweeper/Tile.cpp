#include "Tile.h"

Tile::Tile()
{
	background.setTexture(TextureManager::GetTexture("tile_hidden"));
	isHidden = true;
	isFlagged = false;
	isMine = false;
	debug = false;
	xPos = 0;
	yPos = 0;
	SetPosition(xPos, yPos);
}

void Tile::ToggleFlag()
{
	if (!isFlagged && isHidden)
	{
		foreground.setTexture(TextureManager::GetTexture("flag"));
		isFlagged = true;
	}
	else
	{
		string path;
		if (neighbors.size() == maxNeighbors)
		{
			path = "tile_revealed";
			SetForeground(path);
		}
		else
		{
			string path = "number_" + to_string(maxNeighbors - neighbors.size());
			foreground.setTexture(TextureManager::GetTexture(path));
		}
		isFlagged = false;
	}
}

void Tile::MineOff()
{
	isMine = false;
}

bool Tile::IsMine()
{
	return isMine;
}

bool Tile::IsHidden()
{
	return isHidden;
}

bool Tile::IsFlagged()
{
	return isFlagged;
}

vector<Tile*> Tile::GetNeighbors()
{
	return neighbors;
}

void Tile::Reveal()
{
	if (isMine)
		isHidden = false;
	else if (!isFlagged)
	{
		if (neighbors.size() == maxNeighbors && isHidden)
		{
			for (int i = 0; i < neighbors.size(); i++)
			{
				isHidden = false;
				neighbors[i]->Reveal();
			}
		}
		else
			isHidden = false;
	}
}

void Tile::DebugToggle()
{
	if (debug)
		debug = false;
	else
		debug = true;
}

void Tile::Hide()
{
	isHidden = true;
	debug = false;
}

void Tile::SetMine()
{
	isMine = true;
}

void Tile::SetNeighbors(vector<Tile*> neighbors)
{
	this->neighbors = neighbors;
}

void Tile::SetMaxNeighbors(int number)
{
	this->maxNeighbors = number;
}

void Tile::SetForeground(string image)
{
	foreground.setTexture(TextureManager::GetTexture(image));
}

void Tile::SetBackground(string image)
{
	background.setTexture(TextureManager::GetTexture(image));
}

void Tile::SetSpecial(string image)
{
	special.setTexture(TextureManager::GetTexture(image));
}

void Tile::SetPosition(int x, int y)
{
	foreground.setPosition(sf::Vector2f(x, y));
	background.setPosition(sf::Vector2f(x, y));
	special.setPosition(sf::Vector2f(x, y));
}

void Tile::LeftClick(int mouseX, int mouseY)
{
	if (background.getGlobalBounds().contains(mouseX, mouseY))
	{
		Reveal();
	}
}

void Tile::RightClick(int mouseX, int mouseY)
{
	if (background.getGlobalBounds().contains(mouseX, mouseY))
	{
		ToggleFlag();
	}
}

void Tile::Draw(sf::RenderWindow& window)
{
	if (isHidden && !debug)
	{
		background.setTexture(TextureManager::GetTexture("tile_hidden"));
		window.draw(background);
		if (isFlagged)
		{
			foreground.setTexture(TextureManager::GetTexture("flag"));
			window.draw(foreground);
		}
	}
	else if (isHidden && debug)
	{
		background.setTexture(TextureManager::GetTexture("tile_hidden"));
		window.draw(background);
		if (isFlagged)
		{
			foreground.setTexture(TextureManager::GetTexture("flag"));
			window.draw(foreground);
		}
		special.setTexture(TextureManager::GetTexture("mine"));
		window.draw(special);
	}
	else if (!isHidden)
	{
		background.setTexture(TextureManager::GetTexture("tile_revealed"));
		window.draw(background);
		if (isMine)
		{
			foreground.setTexture(TextureManager::GetTexture("mine"));
			window.draw(foreground);
		}
		else
		{
			window.draw(foreground);
		}
	}
}

sf::Sprite Tile::GetSprite()
{
	return background;
}