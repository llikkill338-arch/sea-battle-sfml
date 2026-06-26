// ============================================================================
// Ship.hpp - Пиксельный пиратский корабль
// ============================================================================

#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Constants.hpp"

enum class PartState { Intact, Damaged };

struct ShipPart {
    int r, c;
    PartState state;
};

class Ship {
public:
    Ship(int startR, int startC, int size, bool horizontal);

    bool contains(int r, int c) const;
    bool hitPart(int r, int c);  // NEW: marks part as damaged, returns true if hit
    bool isSunk() const;
    int getSize() const { return size; }
    bool isHorizontal() const { return horizontal; }
    int getRow() const { return startRow; }
    int getCol() const { return startCol; }
    const ShipPart& getPart(int idx) const;

    void draw(sf::RenderWindow& window, float offsetX, float offsetY,
              float cellSize, bool showShips, bool isEnemy) const;

private:
    std::vector<ShipPart> parts;
    int size;
    bool horizontal;
    int startRow, startCol;
};
