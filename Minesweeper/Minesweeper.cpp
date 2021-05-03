#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "Board.h"
#include "Tile.h"
#include "Random.h"

int main()
{
    Board board;
    vector<vector<Tile>> tiles = board.GetTiles();
    cout << "Loading..." << endl;
    sf::RenderWindow window(sf::VideoMode(board.GetColumns() * 32, (board.GetRows() * 32) + 88), "Minesweeper");

    sf::Sprite debug;
    debug.setTexture(TextureManager::GetTexture("debug"));
    debug.setPosition(board.GetColumns() * 32 - (64 * 4), board.GetRows() * 32);


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            // Mouse Button Press
            if (event.type == sf::Event::MouseButtonPressed)
            {
                // Left mouse
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    // Get mouse position
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    // Check tiles for click
                    board.LeftClickTile(mousePos.x, mousePos.y);
                    // Check board buttons for click
                    board.ClickFace(mousePos.x, mousePos.y);
                    // Click debug button
                    auto bounds = debug.getGlobalBounds();
                    if (bounds.contains(mousePos.x, mousePos.y))
                        board.DebugMode();
                    // Click test 1, 2, 3
                    board.ClickTest1(mousePos.x, mousePos.y);
                    board.ClickTest2(mousePos.x, mousePos.y);
                    board.ClickTest3(mousePos.x, mousePos.y);

                }
                // Right mouse
                else if (event.mouseButton.button == sf::Mouse::Right)
                {
                    // Get mouse position
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    // Check tiles for click
                    board.RightClickTile(mousePos.x, mousePos.y);
                }
            }
        }
        window.clear();
        // Draw out images
        board.Draw(window);
        window.draw(debug);
        window.display();
    }

    // Clear out any textures before the program ends
    TextureManager::Clear();

    return 0;
}