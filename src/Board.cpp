// ============================================================================
// Board.cpp - Реализация игрового поля
// ============================================================================

#include "Board.hpp"
#include <algorithm>
#include <cstdlib>

using namespace Colors;

Board::Board(float ox, float oy, bool enemy)
    : offsetX(ox), offsetY(oy), isEnemy(enemy) {
    clear();
}

void Board::clear() {
    for (int r = 0; r < BOARD_SIZE; r++)
        for (int c = 0; c < BOARD_SIZE; c++)
            cells[r][c].setState(CellState::Empty);
    ships.clear();
}

bool Board::inBounds(int r, int c) const {
    return r >= 0 && r < BOARD_SIZE && c >= 0 && c < BOARD_SIZE;
}

bool Board::canPlaceShip(int r, int c, int size, bool horizontal) const {
    if (horizontal) { if (c + size > BOARD_SIZE) return false; }
    else            { if (r + size > BOARD_SIZE) return false; }

    int minR = std::max(0, r - 1);
    int maxR = std::min(BOARD_SIZE - 1, (horizontal ? r : r + size - 1) + 1);
    int minC = std::max(0, c - 1);
    int maxC = std::min(BOARD_SIZE - 1, (horizontal ? c + size - 1 : c) + 1);

    for (int rr = minR; rr <= maxR; rr++)
        for (int cc = minC; cc <= maxC; cc++)
            if (cells[rr][cc].getState() == CellState::Ship) return false;

    return true;
}

bool Board::placeShip(int r, int c, int size, bool horizontal) {
    if (!canPlaceShip(r, c, size, horizontal)) return false;

    auto ship = std::make_unique<Ship>(r, c, size, horizontal);

    for (int i = 0; i < size; i++) {
        int rr = horizontal ? r : r + i;
        int cc = horizontal ? c + i : c;
        cells[rr][cc].setState(CellState::Ship);
    }

    ships.push_back(std::move(ship));
    return true;
}

void Board::autoPlace() {
    clear();
    for (int i = 0; i < FLEET_COUNT; i++) {
        int size = FLEET_SIZES[i];
        bool placed = false;
        int attempts = 0;
        while (!placed && attempts < 1000) {
            int r = rand() % BOARD_SIZE;
            int c = rand() % BOARD_SIZE;
            bool horiz = rand() % 2;
            placed = placeShip(r, c, size, horiz);
            attempts++;
        }
    }
}

bool Board::shoot(int r, int c) {
    if (!inBounds(r, c)) return false;

    CellState s = cells[r][c].getState();
    if (s == CellState::Hit || s == CellState::Miss) return false;

    if (s == CellState::Ship) {
        cells[r][c].setState(CellState::Hit);
        // Check if any ship was sunk and mark its aura
        for (auto& ship : ships) {
            if (ship->contains(r, c) && ship->isSunk()) {
                markShipAura(ship->getRow(), ship->getCol(), ship->getSize(), ship->isHorizontal());
            }
        }
        return true;
    } else {
        cells[r][c].setState(CellState::Miss);
        return false;
    }
}

void Board::markShipAura(int r, int c, int size, bool horizontal) {
    int minR, maxR, minC, maxC;
    if (horizontal) {
        minR = std::max(0, r - 1);
        maxR = std::min(BOARD_SIZE - 1, r + 1);
        minC = std::max(0, c - 1);
        maxC = std::min(BOARD_SIZE - 1, c + size);
    } else {
        minR = std::max(0, r - 1);
        maxR = std::min(BOARD_SIZE - 1, r + size);
        minC = std::max(0, c - 1);
        maxC = std::min(BOARD_SIZE - 1, c + 1);
    }
    for (int rr = minR; rr <= maxR; rr++) {
        for (int cc = minC; cc <= maxC; cc++) {
            if (cells[rr][cc].getState() == CellState::Empty) {
                cells[rr][cc].setState(CellState::Miss);
            }
        }
    }
}

void Board::markSurroundingAsMiss() {
    for (int r = 0; r < BOARD_SIZE; r++) {
        for (int c = 0; c < BOARD_SIZE; c++) {
            if (cells[r][c].getState() == CellState::Hit) {
                for (int dr = -1; dr <= 1; dr++) {
                    for (int dc = -1; dc <= 1; dc++) {
                        int nr = r + dr, nc = c + dc;
                        if (inBounds(nr, nc) && cells[nr][nc].getState() == CellState::Empty) {
                            cells[nr][nc].setState(CellState::Miss);
                        }
                    }
                }
            }
        }
    }
}

bool Board::allShipsSunk() const {
    if (ships.empty()) return false;
    for (const auto& ship : ships) {
        if (!ship->isSunk()) return false;
    }
    return true;
}

bool Board::hasShipAt(int r, int c) const {
    return inBounds(r, c) && cells[r][c].getState() == CellState::Ship;
}

int Board::getShipsAlive() const {
    int count = 0;
    for (const auto& ship : ships) {
        if (!ship->isSunk()) count++;
    }
    return count;
}

CellState Board::getCellState(int r, int c) const {
    return inBounds(r, c) ? cells[r][c].getState() : CellState::Empty;
}

void Board::setCellState(int r, int c, CellState s) {
    if (inBounds(r, c)) cells[r][c].setState(s);
}

void Board::draw(sf::RenderWindow& window, sf::Font& font,
                 int cursorR, int cursorC, bool showShips,
                 int ghostSize, bool ghostDir, bool ghostValid) {
    drawGrid(window, font);

    for (int r = 0; r < BOARD_SIZE; r++) {
        for (int c = 0; c < BOARD_SIZE; c++) {
            float x = offsetX + 30 + c * (CELL_SIZE + CELL_MARGIN);
            float y = offsetY + 30 + r * (CELL_SIZE + CELL_MARGIN);

            bool isCursor = (r == cursorR && c == cursorC);
            bool isGhost = false;

            if (ghostSize > 0 && cursorR >= 0 && cursorC >= 0) {
                if (ghostDir) {
                    isGhost = (r == cursorR && c >= cursorC && c < cursorC + ghostSize);
                } else {
                    isGhost = (c == cursorC && r >= cursorR && r < cursorR + ghostSize);
                }
            }

            cells[r][c].draw(window, x, y, CELL_SIZE, showShips, isCursor);

            if (isGhost) {
                sf::RectangleShape ghost;
                ghost.setSize(sf::Vector2f(CELL_SIZE, CELL_SIZE));
                ghost.setPosition(x, y);
                ghost.setFillColor(ghostValid ? GHOST_OK : GHOST_BAD);
                window.draw(ghost);
            }
        }
    }

    for (const auto& ship : ships) {
        ship->draw(window, offsetX + 30, offsetY + 30, CELL_SIZE, showShips, isEnemy);
    }
}

void Board::drawGrid(sf::RenderWindow& window, sf::Font& font) {
    sf::RectangleShape border;
    border.setSize(sf::Vector2f(BOARD_PIXELS + 40, BOARD_PIXELS + 40));
    border.setPosition(offsetX + 8, offsetY + 8);
    border.setFillColor(sf::Color::Transparent);
    border.setOutlineColor(GRID_LINE);
    border.setOutlineThickness(2);
    window.draw(border);

    for (int c = 0; c < BOARD_SIZE; c++) {
        sf::Text text(std::to_string(c + 1), font, 13);
        text.setFillColor(TEXT_GOLD);
        float x = offsetX + 30 + c * (CELL_SIZE + CELL_MARGIN) + CELL_SIZE / 2 - 5;
        text.setPosition(x, offsetY + 10);
        window.draw(text);
    }

    for (int r = 0; r < BOARD_SIZE; r++) {
        char letter = 'A' + r;
        sf::Text text(std::string(1, letter), font, 13);
        text.setFillColor(TEXT_GOLD);
        text.setPosition(offsetX + 12, offsetY + 35 + r * (CELL_SIZE + CELL_MARGIN) + CELL_SIZE / 2 - 8);
        window.draw(text);
    }
}
