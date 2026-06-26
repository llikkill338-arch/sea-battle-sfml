// ============================================================================
// Board.hpp - Игровое поле
// ============================================================================

#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Cell.hpp"
#include "Ship.hpp"
#include "Constants.hpp"

class Board {
public:
    Board(float ox, float oy, bool enemy);

    void clear();
    bool inBounds(int r, int c) const;
    bool canPlaceShip(int r, int c, int size, bool horizontal) const;
    bool placeShip(int r, int c, int size, bool horizontal);
    void autoPlace();
    bool shoot(int r, int c);
    bool allShipsSunk() const;
    bool hasShipAt(int r, int c) const;
    int getShipsAlive() const;
    CellState getCellState(int r, int c) const;
    void setCellState(int r, int c, CellState s);
    void markShipAura(int r, int c, int size, bool horizontal);
    void markSurroundingAsMiss();

    void draw(sf::RenderWindow& window, sf::Font& font,
              int cursorR, int cursorC, bool showShips,
              int ghostSize, bool ghostDir, bool ghostValid);

private:
    float offsetX, offsetY;
    bool isEnemy;
    Cell cells[BOARD_SIZE][BOARD_SIZE];
    std::vector<std::unique_ptr<Ship>> ships;

    void drawGrid(sf::RenderWindow& window, sf::Font& font);
};
