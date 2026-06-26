// ============================================================================
// Ship.cpp - Пиксельный пиратский корабль
// ============================================================================

#include "Ship.hpp"

using namespace Colors;

Ship::Ship(int startR, int startC, int size, bool horizontal)
    : size(size), horizontal(horizontal), startRow(startR), startCol(startC) {
    for (int i = 0; i < size; i++) {
        ShipPart p;
        if (horizontal) { p.r = startR; p.c = startC + i; }
        else            { p.r = startR + i; p.c = startC; }
        p.state = PartState::Intact;
        parts.push_back(p);
    }
}

bool Ship::contains(int r, int c) const {
    for (const auto& p : parts)
        if (p.r == r && p.c == c) return true;
    return false;
}

// NEW: Properly mark part as damaged (no const_cast hack)
bool Ship::hitPart(int r, int c) {
    for (auto& p : parts) {
        if (p.r == r && p.c == c && p.state == PartState::Intact) {
            p.state = PartState::Damaged;
            return true;
        }
    }
    return false;
}

bool Ship::isSunk() const {
    for (const auto& p : parts)
        if (p.state == PartState::Intact) return false;
    return true;
}

const ShipPart& Ship::getPart(int idx) const {
    return parts[idx];
}

void Ship::draw(sf::RenderWindow& window, float offsetX, float offsetY,
                float cellSize, bool showShips, bool isEnemy) const {
    if (!isEnemy || showShips || isSunk()) {
        for (const auto& part : parts) {
            float x = offsetX + part.c * (cellSize + CELL_MARGIN);
            float y = offsetY + part.r * (cellSize + CELL_MARGIN);

            sf::RectangleShape partShape;
            partShape.setSize(sf::Vector2f(cellSize - 2, cellSize - 2));
            partShape.setPosition(x + 1, y + 1);

            if (part.state == PartState::Damaged) {
                partShape.setFillColor(SHIP_HIT);
            } else {
                partShape.setFillColor(SHIP);
            }
            window.draw(partShape);
        }
    }
}
