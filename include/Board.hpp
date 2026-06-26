// ============================================================================
// Board.hpp - Игровое поле 10x10
// ============================================================================

#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Cell.hpp"
#include "Ship.hpp"

class Board {
public:
    Board(float offsetX, float offsetY, bool isEnemy);
    
    // Расстановка
    bool canPlaceShip(int r, int c, int size, bool horizontal) const;
    bool placeShip(int r, int c, int size, bool horizontal);
    void autoPlace();
    void clear();
    
    // Бой
    bool shoot(int r, int c);
    bool allShipsSunk() const;
    bool hasShipAt(int r, int c) const;
    
    // Отрисовка
    void draw(sf::RenderWindow& window, sf::Font& font,
              int cursorR, int cursorC, bool showShips,
              int ghostSize, bool ghostDir, bool ghostValid);
    
    // Инфо
    int getShipsAlive() const;
    CellState getCellState(int r, int c) const;
    void setCellState(int r, int c, CellState s);
    
    float getOffsetX() const { return offsetX; }
    float getOffsetY() const { return offsetY; }

private:
    Cell cells[BOARD_SIZE][BOARD_SIZE];
    std::vector<std::unique_ptr<Ship>> ships;
    float offsetX, offsetY;
    bool isEnemy;
    
    bool inBounds(int r, int c) const;
    void drawGrid(sf::RenderWindow& window, sf::Font& font);
};
