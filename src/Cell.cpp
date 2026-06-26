// ============================================================================
// Cell.cpp - Реализация клетки
// ============================================================================

#include "Cell.hpp"
#include "Constants.hpp"

using namespace Colors;

Cell::Cell() : state(CellState::Empty), hover(false) {}

CellState Cell::getState() const {
    return state;
}

void Cell::setState(CellState s) {
    state = s;
}

void Cell::setHover(bool h) {
    hover = h;
}

bool Cell::isHovered() const {
    return hover;
}

void Cell::draw(sf::RenderWindow& window, float x, float y, float size,
                bool showShip, bool isCursor) {
    
    sf::RectangleShape shape;
    shape.setSize(sf::Vector2f(size, size));
    shape.setPosition(x, y);
    
    sf::Color fillColor;
    
    switch (state) {
        case CellState::Empty:
            fillColor = WATER;
            break;
        case CellState::Ship:
            fillColor = showShip ? SHIP : WATER;
            break;
        case CellState::Hit:
            fillColor = HIT;
            break;
        case CellState::Miss:
            fillColor = MISS;
            break;
    }
    
    if (isCursor) {
        fillColor = CURSOR;
    }
    
    shape.setFillColor(fillColor);
    
    sf::Color outlineColor = isCursor ? sf::Color::White : GRID_LINE;
    float outlineThickness = isCursor ? 3.0f : 1.0f;
    shape.setOutlineColor(outlineColor);
    shape.setOutlineThickness(outlineThickness);
    
    window.draw(shape);
    
    if (state == CellState::Hit) {
        sf::RectangleShape line1(sf::Vector2f(size * 0.6f, 3));
        line1.setOrigin(line1.getSize() / 2.f);
        line1.setPosition(x + size / 2, y + size / 2);
        line1.setRotation(45);
        line1.setFillColor(sf::Color::White);
        
        sf::RectangleShape line2(sf::Vector2f(size * 0.6f, 3));
        line2.setOrigin(line2.getSize() / 2.f);
        line2.setPosition(x + size / 2, y + size / 2);
        line2.setRotation(-45);
        line2.setFillColor(sf::Color::White);
        
        window.draw(line1);
        window.draw(line2);
    }
    else if (state == CellState::Miss) {
        sf::CircleShape circle;
        circle.setRadius(size * 0.15f);
        circle.setOrigin(size * 0.15f, size * 0.15f);
        circle.setPosition(x + size / 2, y + size / 2);
        circle.setFillColor(sf::Color(150, 150, 150));
        window.draw(circle);
    }
}
