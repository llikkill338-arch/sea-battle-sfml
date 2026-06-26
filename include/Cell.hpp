// ============================================================================
// Cell.hpp - Клетка поля
// ============================================================================

#pragma once
#include <SFML/Graphics.hpp>

enum class CellState {
    Empty,      // Вода
    Ship,       // Корабль
    Hit,        // Попадание
    Miss        // Промах
};

class Cell {
public:
    Cell();
    
    CellState getState() const;
    void setState(CellState s);
    void setHover(bool h);
    bool isHovered() const;
    
    void draw(sf::RenderWindow& window, float x, float y, float size,
              bool showShip, bool isCursor);

private:
    CellState state;
    bool hover;
};
