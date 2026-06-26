// ============================================================================
// Constants.hpp - Все константы игры
// ============================================================================

#pragma once
#include <SFML/Graphics.hpp>

// --- Размеры ---
const int BOARD_SIZE = 10;
const int CELL_SIZE = 48;
const int CELL_MARGIN = 2;
const int BOARD_PIXELS = BOARD_SIZE * (CELL_SIZE + CELL_MARGIN);

// --- Окно ---
const int WINDOW_WIDTH = 1100;
const int WINDOW_HEIGHT = 750;
const char* WINDOW_TITLE = "Morskoj Boj - SFML";

// --- Цвета ---
namespace Colors {
    const sf::Color WATER      (30,  80,  140);
    const sf::Color WATER_DARK (20,  60,  110);
    const sf::Color SHIP       (139, 90,  43);
    const sf::Color SHIP_HIT   (180, 50,  30);
    const sf::Color HIT        (255, 60,  60);
    const sf::Color MISS       (200, 200, 220);
    const sf::Color CURSOR     (255, 255, 0);
    const sf::Color GRID_LINE  (60,  130, 200);
    const sf::Color BG         (10,  25,  50);
    const sf::Color PANEL_BG   (15,  35,  65);
    const sf::Color TEXT       (230, 230, 250);
    const sf::Color TEXT_GOLD  (255, 215, 0);
    const sf::Color GHOST_OK   (50,  200, 80);
    const sf::Color GHOST_BAD  (255, 50,  50);
    const sf::Color EXPLOSION  (255, 140, 0);
    const sf::Color BUTTON     (40,  100, 160);
    const sf::Color BUTTON_HOVER(60, 140, 220);
    const sf::Color BUTTON_TEXT(255, 255, 255);
}

// --- Флот ---
const int FLEET_COUNT = 10;
const int FLEET_SIZES[FLEET_COUNT] = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};

// --- Задержки ---
const float ANIMATION_SPEED = 0.15f;
const float BOT_THINK_DELAY = 0.8f;
