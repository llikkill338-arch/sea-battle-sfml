// ============================================================================
// Game.cpp - Главный игровой класс
// ============================================================================

#include "Game.hpp"
#include <iostream>
#include <cmath>

using namespace Colors;

Game::Game()
    : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE,
             sf::Style::Close | sf::Style::Titlebar),
      state(GameState::Menu), prevState(GameState::Menu),
      cursorR(0), cursorC(0), currentShipIdx(0),
      placingHorizontal(true), botLevel(0),
      botThinking(false), botTimer(0),
      soundEnabled(true), autoPlace(false),
      animTimer(0), menuSelection(0), settingsSelection(0) {
    
    window.setFramerateLimit(60);
    loadResources();
    
    playerBoard = std::make_unique<Board>(50, 80, false);
    enemyBoard = std::make_unique<Board>(580, 80, true);
}

Game::~Game() {}

void Game::loadResources() {
    if (!font.loadFromFile("assets/fonts/arial.ttf")) {
    }
    fontBold = font;
}

void Game::run() {
    sf::Clock clock;
    
    while (window.isOpen() && state != GameState::Exit) {
        float dt = clock.restart().asSeconds();
        animTimer += dt;
        
        handleEvents();
        update(dt);
        render();
    }
}

void Game::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            state = GameState::Exit;
        }
        
        if (event.type == sf::Event::KeyPressed) {
            if (state == GameState::Menu) {
                if (event.key.code == sf::Keyboard::Up && menuSelection > 0)
                    menuSelection--;
                if (event.key.code == sf::Keyboard::Down && menuSelection < 3)
                    menuSelection++;
                if (event.key.code == sf::Keyboard::Enter) {
                    switch (menuSelection) {
                        case 0: startPlacement(); break;
                        case 1: state = GameState::Rules; break;
                        case 2: state = GameState::Settings; break;
                        case 3: state = GameState::Exit; break;
                    }
                }
            }
            else if (state == GameState::Settings) {
                if (event.key.code == sf::Keyboard::Up && settingsSelection > 0)
                    settingsSelection--;
                if (event.key.code == sf::Keyboard::Down && settingsSelection < 3)
                    settingsSelection++;
                if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Right) {
                    if (settingsSelection == 0) botLevel = 1 - botLevel;
                    if (settingsSelection == 1) autoPlace = !autoPlace;
                    if (settingsSelection == 2) soundEnabled = !soundEnabled;
                }
                if (event.key.code == sf::Keyboard::Enter && settingsSelection == 3)
                    state = GameState::Menu;
                if (event.key.code == sf::Keyboard::Escape)
                    state = GameState::Menu;
            }
            else if (state == GameState::Rules) {
                if (event.key.code == sf::Keyboard::Escape ||
                    event.key.code == sf::Keyboard::Enter)
                    state = GameState::Menu;
            }
            else if (state == GameState::Placement) {
                int size = FLEET_SIZES[currentShipIdx];
                
                if (event.key.code == sf::Keyboard::Up && cursorR > 0) cursorR--;
                if (event.key.code == sf::Keyboard::Down && cursorR < BOARD_SIZE - 1) cursorR++;
                if (event.key.code == sf::Keyboard::Left && cursorC > 0) cursorC--;
                if (event.key.code == sf::Keyboard::Right && cursorC < BOARD_SIZE - 1) cursorC++;
                
                if (event.key.code == sf::Keyboard::Space) {
                    placingHorizontal = !placingHorizontal;
                    if (placingHorizontal) {
                        if (cursorC + size > BOARD_SIZE) cursorC = BOARD_SIZE - size;
                    } else {
                        if (cursorR + size > BOARD_SIZE) cursorR = BOARD_SIZE - size;
                    }
                }
                
                if (event.key.code == sf::Keyboard::Enter) {
                    if (playerBoard->canPlaceShip(cursorR, cursorC, size, placingHorizontal)) {
                        playerBoard->placeShip(cursorR, cursorC, size, placingHorizontal);
                        currentShipIdx++;
                        if (currentShipIdx >= FLEET_COUNT) {
                            startBattle();
                        }
                    }
                }
                
                if (event.key.code == sf::Keyboard::Escape) {
                    state = GameState::Menu;
                }
            }
            else if (state == GameState::Battle) {
                if (event.key.code == sf::Keyboard::Up && cursorR > 0) cursorR--;
                if (event.key.code == sf::Keyboard::Down && cursorR < BOARD_SIZE - 1) cursorR++;
                if (event.key.code == sf::Keyboard::Left && cursorC > 0) cursorC--;
                if (event.key.code == sf::Keyboard::Right && cursorC < BOARD_SIZE - 1) cursorC++;
                
                if (event.key.code == sf::Keyboard::Enter) {
                    if (enemyBoard->getCellState(cursorR, cursorC) != CellState::Hit &&
                        enemyBoard->getCellState(cursorR, cursorC) != CellState::Miss) {
                        
                        bool hit = enemyBoard->shoot(cursorR, cursorC);
                        if (hit) playHitSound(); else playMissSound();
                        
                        if (enemyBoard->allShipsSunk()) {
                            state = GameState::Victory;
                        } else if (!hit) {
                            state = GameState::BotTurn;
                            botTimer = 0;
                            botThinking = true;
                        }
                    }
                }
                
                if (event.key.code == sf::Keyboard::Escape)
                    state = GameState::Menu;
            }
            else if (state == GameState::Victory || state == GameState::Defeat) {
                if (event.key.code == sf::Keyboard::Enter) {
                    resetGame();
                    state = GameState::Menu;
                }
                if (event.key.code == sf::Keyboard::Escape)
                    state = GameState::Menu;
            }
        }
    }
}

void Game::update(float dt) {
    if (state == GameState::BotTurn && botThinking) {
        botTimer += dt;
        if (botTimer >= BOT_THINK_DELAY) {
            botMakeMove();
            botThinking = false;
            if (playerBoard->allShipsSunk()) {
                state = GameState::Defeat;
            } else {
                state = GameState::Battle;
            }
        }
    }
}

void Game::botMakeMove() {
    if (botLevel == 0) {
        int r, c;
        do {
            r = rand() % BOARD_SIZE;
            c = rand() % BOARD_SIZE;
        } while (playerBoard->getCellState(r, c) == CellState::Hit ||
                 playerBoard->getCellState(r, c) == CellState::Miss);
        playerBoard->shoot(r, c);
    } else {
        static int lastHitR = -1, lastHitC = -1;
        static bool hunting = false;
        
        if (hunting && lastHitR >= 0) {
            int dirs[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};
            for (auto& d : dirs) {
                int nr = lastHitR + d[0], nc = lastHitC + d[1];
                if (nr >= 0 && nr < BOARD_SIZE && nc >= 0 && nc < BOARD_SIZE) {
                    auto s = playerBoard->getCellState(nr, nc);
                    if (s != CellState::Hit && s != CellState::Miss) {
                        playerBoard->shoot(nr, nc);
                        if (playerBoard->getCellState(nr, nc) == CellState::Hit) {
                            lastHitR = nr; lastHitC = nc;
                        } else {
                            hunting = false;
                        }
                        return;
                    }
                }
            }
            hunting = false;
        }
        
        if (!hunting) {
            int r, c;
            int attempts = 0;
            do {
                r = rand() % BOARD_SIZE;
                c = rand() % BOARD_SIZE;
                attempts++;
            } while (attempts < 200 && ((r + c) % 2 != 0 ||
                     playerBoard->getCellState(r, c) == CellState::Hit ||
                     playerBoard->getCellState(r, c) == CellState::Miss));
            
            if (attempts >= 200) {
                do {
                    r = rand() % BOARD_SIZE;
                    c = rand() % BOARD_SIZE;
                } while (playerBoard->getCellState(r, c) == CellState::Hit ||
                         playerBoard->getCellState(r, c) == CellState::Miss);
            }
            
            playerBoard->shoot(r, c);
            if (playerBoard->getCellState(r, c) == CellState::Hit) {
                lastHitR = r; lastHitC = c;
                hunting = true;
            }
        }
    }
}

void Game::render() {
    window.clear(BG);
    
    switch (state) {
        case GameState::Menu:       renderMenu(); break;
        case GameState::Settings:   renderSettings(); break;
        case GameState::Rules:      renderRules(); break;
        case GameState::Placement:  renderPlacement(); break;
        case GameState::Battle:     renderBattle(); break;
        case GameState::BotTurn:    renderBotTurn(); break;
        case GameState::Victory:    renderVictory(); break;
        case GameState::Defeat:     renderDefeat(); break;
        default: break;
    }
    
    window.display();
}

void Game::renderMenu() {
    for (int i = 0; i < 5; i++) {
        float x = 100 + i * 200 + sin(animTimer + i) * 20;
        float y = 500 + cos(animTimer * 0.7f + i) * 30;
        sf::RectangleShape wave(sf::Vector2f(CELL_SIZE, CELL_SIZE));
        wave.setPosition(x, y);
        wave.setFillColor(sf::Color(30, 80, 140, 80));
        window.draw(wave);
    }
    
    drawText("MORSKoj BOJ", WINDOW_WIDTH / 2, 80, 56, TEXT_GOLD, true);
    drawText("Konsolednyj boj v2.0", WINDOW_WIDTH / 2, 140, 20, TEXT, true);
    
    const char* buttons[] = {"Nachatx igru", "Prawila", "Nastrojki", "Wyxod"};
    for (int i = 0; i < 4; i++) {
        float y = 250 + i * 70;
        drawButton(buttons[i], WINDOW_WIDTH / 2 - 150, y, 300, 50,
                   false, i == menuSelection);
    }
    
    drawText("Strelki ^/v - wybor | ENTER - podtwerditx", WINDOW_WIDTH / 2, 560, 16, sf::Color(150, 150, 170), true);
    drawText("SFML v2.0 | C++17", WINDOW_WIDTH / 2, 700, 14, sf::Color(100, 100, 120), true);
}

void Game::renderSettings() {
    drawText("NASTROJKI", WINDOW_WIDTH / 2, 60, 36, TEXT_GOLD, true);
    
    const char* labels[] = {
        "Slozhnostx bota",
        "Rasstanowka korablej",
        "Swuk",
        "Nazad w menu"
    };
    const char* values[] = {
        botLevel == 0 ? "LEGKij" : "SLOZhNYJ",
        autoPlace ? "AVTOMAT" : "WRUCHNUJU",
        soundEnabled ? "WKL" : "WYKL",
        ""
    };
    
    for (int i = 0; i < 4; i++) {
        float y = 180 + i * 90;
        sf::Color color = (i == settingsSelection) ? sf::Color::Yellow : TEXT;
        
        drawText(labels[i], WINDOW_WIDTH / 2 - 200, y, 24, color, false);
        if (strlen(values[i]) > 0) {
            sf::Color valColor = (i == settingsSelection) ? sf::Color::Green : sf::Color(100, 200, 255);
            drawText(values[i], WINDOW_WIDTH / 2 + 100, y, 24, valColor, false);
        }
    }
    
    drawText("</> - izmenitx | ENTER/ESC - nazad", WINDOW_WIDTH / 2, 650, 16, sf::Color(150, 150, 170), true);
}

void Game::renderRules() {
    drawText("PRAWILA IGRY", WINDOW_WIDTH / 2, 50, 36, TEXT_GOLD, true);
    
    const char* rules[] = {
        "Celx: potopitx wesx flot protiwnika.",
        "",
        "Flot (10 korablej):",
        "  1 x 4-palubnyj (awianosec)",
        "  2 x 3-palubnyh (krejsera)",
        "  3 x 2-palubnyh (jesminca)",
        "  4 x 1-palubnyh (minonosca)",
        "",
        "Uprawlenie:",
        "  Strelki - peremewenie prizela/kursora",
        "  ENTER   - wystrel / postawitx korablx",
        "  PROBEL  - poworot korablja (goriz/wert)",
        "  ESC     - menu / wyhod",
        "",
        "Pri popadanii - dopolnitelxnyj hod.",
        "Pobezhdaet tot, kto perwym potopit flot!"
    };
    
    for (int i = 0; i < 16; i++) {
        drawText(rules[i], 100, 120 + i * 28, 20, TEXT, false);
    }
    
    drawText("Nazhmite ENTER ili ESC dlja wyhoda...", WINDOW_WIDTH / 2, 680, 18, TEXT_GOLD, true);
}

void Game::startPlacement() {
    state = GameState::Placement;
    playerBoard->clear();
    enemyBoard->clear();
    enemyBoard->autoPlace();
    currentShipIdx = 0;
    cursorR = 0; cursorC = 0;
    placingHorizontal = true;
    
    if (autoPlace) {
        playerBoard->autoPlace();
        startBattle();
    }
}

void Game::renderPlacement() {
    drawText("RASSTANOWKA KORABLEJ", WINDOW_WIDTH / 2, 20, 28, TEXT_GOLD, true);
    
    int size = FLEET_SIZES[currentShipIdx];
    bool valid = playerBoard->canPlaceShip(cursorR, cursorC, size, placingHorizontal);
    playerBoard->draw(window, font, cursorR, cursorC, true, size, placingHorizontal, valid);
    
    drawText("Waswe pole", 50 + BOARD_PIXELS / 2, 55, 18, TEXT_GOLD, true);
    
    float panelX = 50 + BOARD_PIXELS + 60;
    sf::RectangleShape panel(sf::Vector2f(300, 500));
    panel.setPosition(panelX, 80);
    panel.setFillColor(PANEL_BG);
    panel.setOutlineColor(GRID_LINE);
    panel.setOutlineThickness(1);
    window.draw(panel);
    
    drawText("Korablx:", panelX + 20, 100, 22, TEXT, false);
    drawText(std::to_string(size) + "-palubnyj", panelX + 20, 130, 26, TEXT_GOLD, false);
    
    drawText("Naprawlenie:", panelX + 20, 180, 20, TEXT, false);
    drawText(placingHorizontal ? ">>> GORIZONTALxNO" : "vvv WERTIKALxNO",
             panelX + 20, 210, 20, sf::Color(100, 200, 255), false);
    
    if (valid) {
        drawText("[OK] Moshno stawitx", panelX + 20, 260, 20, sf::Color(50, 200, 80), false);
    } else {
        drawText("[X] Mesto zanjato!", panelX + 20, 260, 20, sf::Color(255, 80, 80), false);
    }
    
    drawText("Uprawlenie:", panelX + 20, 320, 18, sf::Color(150, 150, 170), false);
    drawText("Strelki - dwinhenie", panelX + 20, 350, 18, sf::Color(150, 150, 170), false);
    drawText("PROBEL - poworot", panelX + 20, 380, 18, sf::Color(150, 150, 170), false);
    drawText("ENTER - postawitx", panelX + 20, 410, 18, sf::Color(150, 150, 170), false);
    drawText("ESC - menu", panelX + 20, 440, 18, sf::Color(150, 150, 170), false);
    
    drawText(std::to_string(currentShipIdx) + " / " + std::to_string(FLEET_COUNT),
             panelX + 20, 500, 24, TEXT_GOLD, false);
    
    drawText("Ostalosx:", panelX + 20, 540, 18, sf::Color(150, 150, 170), false);
    for (int i = currentShipIdx; i < FLEET_COUNT; i++) {
        std::string bar = "[" + std::string(FLEET_SIZES[i], '=') + "]";
        drawText(bar, panelX + 20, 565 + (i - currentShipIdx) * 22, 18,
                 sf::Color(100, 180, 255), false);
    }
}

void Game::startBattle() {
    state = GameState::Battle;
    cursorR = 0; cursorC = 0;
    botThinking = false;
}

void Game::renderBattle() {
    drawText("BOJ S BOTOM", WINDOW_WIDTH / 2, 15, 24, TEXT_GOLD, true);
    
    enemyBoard->draw(window, font, cursorR, cursorC, false, 0, true, true);
    drawText("Pole wraga", 580 + BOARD_PIXELS / 2, 55, 18,
             sf::Color(255, 100, 100), true);
    
    playerBoard->draw(window, font, -1, -1, true, 0, true, true);
    drawText("Waswe pole", 50 + BOARD_PIXELS / 2, 55, 18,
             sf::Color(100, 255, 100), true);
    
    sf::RectangleShape infoPanel(sf::Vector2f(200, 120));
    infoPanel.setPosition(50, 580);
    infoPanel.setFillColor(PANEL_BG);
    infoPanel.setOutlineColor(GRID_LINE);
    infoPanel.setOutlineThickness(1);
    window.draw(infoPanel);
    
    drawText("Wrag: " + std::to_string(enemyBoard->getShipsAlive()) + " kor.",
             70, 590, 18, sf::Color(255, 100, 100), false);
    drawText("Wy: " + std::to_string(playerBoard->getShipsAlive()) + " kor.",
             70, 620, 18, sf::Color(100, 255, 100), false);
    drawText("Strelki | ENTER | ESC",
             70, 650, 16, sf::Color(150, 150, 170), false);
    
    drawText("Prizel: " + std::string(1, 'A' + cursorC) + std::to_string(cursorR + 1),
             580, 580, 20, TEXT_GOLD, false);
}

void Game::renderBotTurn() {
    renderBattle();
    
    sf::RectangleShape overlay(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    overlay.setFillColor(sf::Color(0, 0, 0, 120));
    window.draw(overlay);
    
    drawText("BOT DUMAET...", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 36,
             sf::Color(255, 200, 50), true);
    
    int dots = (int)(botTimer * 3) % 4;
    std::string dotStr(dots, '.');
    drawText(dotStr, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + 40, 30,
             sf::Color(255, 200, 50), true);
}

void Game::renderVictory() {
    sf::RectangleShape overlay(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    overlay.setFillColor(sf::Color(0, 30, 0, 180));
    window.draw(overlay);
    
    drawText("WY POBERDILI!", WINDOW_WIDTH / 2, 250, 56,
             sf::Color(50, 255, 100), true);
    drawText("Flot protiwnika unihtowen!", WINDOW_WIDTH / 2, 330, 24, TEXT, true);
    drawText("ENTER - menu | ESC - wyhod", WINDOW_WIDTH / 2, 450, 20, TEXT_GOLD, true);
}

void Game::renderDefeat() {
    sf::RectangleShape overlay(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    overlay.setFillColor(sf::Color(30, 0, 0, 180));
    window.draw(overlay);
    
    drawText("WY PROIGRALI...", WINDOW_WIDTH / 2, 250, 56,
             sf::Color(255, 50, 50), true);
    drawText("Waw flot potoplen.", WINDOW_WIDTH / 2, 330, 24, TEXT, true);
    drawText("ENTER - menu | ESC - wyhod", WINDOW_WIDTH / 2, 450, 20, TEXT_GOLD, true);
}

void Game::drawText(const std::string& text, float x, float y, int size,
                    sf::Color color, bool center) {
    sf::Text t(text, font, size);
    t.setFillColor(color);
    if (center) {
        sf::FloatRect bounds = t.getLocalBounds();
        t.setOrigin(bounds.width / 2, 0);
    }
    t.setPosition(x, y);
    window.draw(t);
}

void Game::drawButton(const std::string& text, float x, float y, float w, float h,
                      bool hovered, bool selected) {
    sf::RectangleShape button(sf::Vector2f(w, h));
    button.setPosition(x, y);
    
    sf::Color fillColor = selected ? BUTTON_HOVER : BUTTON;
    if (hovered) fillColor = BUTTON_HOVER;
    
    button.setFillColor(fillColor);
    button.setOutlineColor(selected ? sf::Color::Yellow : sf::Color(100, 160, 220));
    button.setOutlineThickness(selected ? 3 : 2);
    window.draw(button);
    
    sf::Text label(text, font, 24);
    label.setFillColor(BUTTON_TEXT);
    sf::FloatRect bounds = label.getLocalBounds();
    label.setOrigin(bounds.width / 2, bounds.height / 2);
    label.setPosition(x + w / 2, y + h / 2 - 5);
    window.draw(label);
}

bool Game::isMouseOver(float x, float y, float w, float h) const {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    return mousePos.x >= x && mousePos.x <= x + w &&
           mousePos.y >= y && mousePos.y <= y + h;
}

void Game::playHitSound() {}

void Game::playMissSound() {}

void Game::resetGame() {
    playerBoard->clear();
    enemyBoard->clear();
    cursorR = 0; cursorC = 0;
    currentShipIdx = 0;
    menuSelection = 0;
}
