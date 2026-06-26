// ============================================================================
// Game.cpp - Главный игровой класс (Russian UTF-8 + Fullscreen + Fixed UI)
// ============================================================================

#include "Game.hpp"
#include <iostream>
#include <cmath>

using namespace Colors;

// All Russian text uses u8"\uXXXX" to guarantee UTF-8 encoding
#define RU_MORSKOY_BOY      u8"\u041C\u043E\u0440\u0441\u043A\u043E\u0439 \u0411\u043E\u0439"
#define RU_KONSOL_BOY       u8"\u041A\u043E\u043D\u0441\u043E\u043B\u044C\u043D\u044B\u0439 \u0431\u043E\u0439 v2.0"
#define RU_NACHAT_IGRU      u8"\u041D\u0430\u0447\u0430\u0442\u044C \u0438\u0433\u0440\u0443"
#define RU_PRAVILA          u8"\u041F\u0440\u0430\u0432\u0438\u043B\u0430"
#define RU_NASTROYKI        u8"\u041D\u0430\u0441\u0442\u0440\u043E\u0439\u043A\u0438"
#define RU_VYHOD            u8"\u0412\u044B\u0445\u043E\u0434"
#define RU_NASTROYKI_TITLE  u8"\u041D\u0410\u0421\u0422\u0420\u041E\u0419\u041A\u0418"
#define RU_SLOZHNOST_BOTA   u8"\u0421\u043B\u043E\u0436\u043D\u043E\u0441\u0442\u044C \u0431\u043E\u0442\u0430"
#define RU_RASSTANOVKA      u8"\u0420\u0430\u0441\u0441\u0442\u0430\u043D\u043E\u0432\u043A\u0430 \u043A\u043E\u0440\u0430\u0431\u043B\u0435\u0439"
#define RU_ZVUK             u8"\u0417\u0432\u0443\u043A"
#define RU_FULLSCREEN       u8"\u041F\u043E\u043B\u043D\u043E\u044D\u043A\u0440\u0430\u043D\u043D\u044B\u0439 \u0440\u0435\u0436\u0438\u043C"
#define RU_NAZAD_MENU       u8"\u041D\u0430\u0437\u0430\u0434 \u0432 \u043C\u0435\u043D\u044E"
#define RU_LEGKIY           u8"\u041B\u0401\u0413\u041A\u0418\u0419"
#define RU_SLOZHNYY         u8"\u0421\u041B\u041E\u0416\u041D\u042B\u0419"
#define RU_AVTO             u8"\u0410\u0412\u0422\u041E"
#define RU_VRUCHNUYU        u8"\u0412\u0420\u0423\u0427\u041D\u0423\u042E"
#define RU_VKL              u8"\u0412\u041A\u041B"
#define RU_VYKL             u8"\u0412\u042B\u041A\u041B"
#define RU_PRAVILA_IGRY     u8"\u041F\u0420\u0410\u0412\u0418\u041B\u0410 \u0418\u0413\u0420\u042B"
#define RU_TSEL             u8"\u0426\u0435\u043B\u044C: \u043F\u043E\u0442\u043E\u043F\u0438\u0442\u044C \u0432\u0435\u0441\u044C \u0444\u043B\u043E\u0442 \u043F\u0440\u043E\u0442\u0438\u0432\u043D\u0438\u043A\u0430."
#define RU_FLOT_10          u8"\u0424\u043B\u043E\u0442 (10 \u043A\u043E\u0440\u0430\u0431\u043B\u0435\u0439):"
#define RU_1X4_AVI          u8"  1 x 4-\u043F\u0430\u043B\u0443\u0431\u043D\u044B\u0439 (\u0430\u0432\u0438\u0430\u043D\u043E\u0441\u0435\u0446)"
#define RU_2X3_KREY         u8"  2 x 3-\u043F\u0430\u043B\u0443\u0431\u043D\u044B\u0445 (\u043A\u0440\u0435\u0439\u0441\u0435\u0440\u0430)"
#define RU_3X2_ESM          u8"  3 x 2-\u043F\u0430\u043B\u0443\u0431\u043D\u044B\u0445 (\u044D\u0441\u043C\u0438\u043D\u0446\u0430)"
#define RU_4X1_MIN          u8"  4 x 1-\u043F\u0430\u043B\u0443\u0431\u043D\u044B\u0445 (\u043C\u0438\u043D\u043E\u043D\u043E\u0441\u0446\u0430)"
#define RU_UPRAVLENIE       u8"\u0423\u043F\u0440\u0430\u0432\u043B\u0435\u043D\u0438\u0435:"
#define RU_STRELKI_PEREM    u8"  \u0421\u0442\u0440\u0435\u043B\u043A\u0438 - \u043F\u0435\u0440\u0435\u043C\u0435\u0449\u0435\u043D\u0438\u0435 \u043F\u0440\u0438\u0446\u0435\u043B\u0430"
#define RU_ENTER_STREL      u8"  ENTER   - \u0432\u044B\u0441\u0442\u0440\u0435\u043B / \u043F\u043E\u0441\u0442\u0430\u0432\u0438\u0442\u044C \u043A\u043E\u0440\u0430\u0431\u043B\u044C"
#define RU_PROBEL_POVOROT   u8"  \u041F\u0420\u041E\u0411\u0415\u041B  - \u043F\u043E\u0432\u043E\u0440\u043E\u0442 \u043A\u043E\u0440\u0430\u0431\u043B\u044F (\u0433\u043E\u0440\u0438\u0437/\u0432\u0435\u0440\u0442)"
#define RU_ESC_MENU         u8"  ESC     - \u043C\u0435\u043D\u044E / \u0432\u044B\u0445\u043E\u0434"
#define RU_DOP_HOD          u8"\u041F\u0440\u0438 \u043F\u043E\u043F\u0430\u0434\u0430\u043D\u0438\u0438 - \u0434\u043E\u043F\u043E\u043B\u043D\u0438\u0442\u0435\u043B\u044C\u043D\u044B\u0439 \u0445\u043E\u0434."
#define RU_POBEDITEL        u8"\u041F\u043E\u0431\u0435\u0436\u0434\u0430\u0435\u0442 \u0442\u043E\u0442, \u043A\u0442\u043E \u043F\u0435\u0440\u0432\u044B\u043C \u043F\u043E\u0442\u043E\u043F\u0438\u0442 \u0444\u043B\u043E\u0442!"
#define RU_NAZHMI_ENTER_ESC u8"\u041D\u0430\u0436\u043C\u0438\u0442\u0435 ENTER \u0438\u043B\u0438 ESC \u0434\u043B\u044F \u0432\u044B\u0445\u043E\u0434\u0430..."
#define RU_RASSTANOVKA_KOR  u8"\u0420\u0410\u0421\u0421\u0422\u0410\u041D\u041E\u0412\u041A\u0410 \u041A\u041E\u0420\u0410\u0411\u041B\u0415\u0419"
#define RU_VASHE_POLE       u8"\u0412\u0430\u0448\u0435 \u043F\u043E\u043B\u0435"
#define RU_KORABL           u8"\u041A\u043E\u0440\u0430\u0431\u043B\u044C:"
#define RU_PALUBNYY         u8"-\u043F\u0430\u043B\u0443\u0431\u043D\u044B\u0439"
#define RU_NAPRAVLENIE      u8"\u041D\u0430\u043F\u0440\u0430\u0432\u043B\u0435\u043D\u0438\u0435:"
#define RU_GORIZ            u8">>> \u0413\u041E\u0420\u0418\u0417\u041E\u041D\u0422\u0410\u041B\u042C\u041D\u041E"
#define RU_VERT             u8"vvv \u0412\u0415\u0420\u0422\u0418\u041A\u0410\u041B\u042C\u041D\u041E"
#define RU_OK_STAVIT        u8"[OK] \u041C\u043E\u0436\u043D\u043E \u0441\u0442\u0430\u0432\u0438\u0442\u044C"
#define RU_MESTO_ZANYATO    u8"[X] \u041C\u0435\u0441\u0442\u043E \u0437\u0430\u043D\u044F\u0442\u043E!"
#define RU_STRELKI_DVIZH    u8"\u0421\u0442\u0440\u0435\u043B\u043A\u0438 - \u0434\u0432\u0438\u0436\u0435\u043D\u0438\u0435"
#define RU_PROBEL_POV       u8"\u041F\u0420\u041E\u0411\u0415\u041B - \u043F\u043E\u0432\u043E\u0440\u043E\u0442"
#define RU_ENTER_POSTAVIT   u8"ENTER - \u043F\u043E\u0441\u0442\u0430\u0432\u0438\u0442\u044C"
#define RU_ESC_MENU_TXT     u8"ESC - \u043C\u0435\u043D\u044E"
#define RU_OSTALOS          u8"\u041E\u0441\u0442\u0430\u043B\u043E\u0441\u044C:"
#define RU_BOY_S_BOTOM      u8"\u0411\u041E\u0419 \u0421 \u0411\u041E\u0422\u041E\u041C"
#define RU_POLE_VRAGA       u8"\u041F\u043E\u043B\u0435 \u0432\u0440\u0430\u0433\u0430"
#define RU_VRAG             u8"\u0412\u0440\u0430\u0433: "
#define RU_KOR              u8" \u043A\u043E\u0440."
#define RU_VY               u8"\u0412\u044B: "
#define RU_PRITSEL          u8"\u041F\u0440\u0438\u0446\u0435\u043B: "
#define RU_BOT_DUMAET       u8"\u0411\u041E\u0422 \u0414\u0423\u041C\u0410\u0415\u0422..."
#define RU_VY_POBEHDILI     u8"\u0412\u042B \u041F\u041E\u0411\u0415\u0414\u0418\u041B\u0418!"
#define RU_FLOT_UNICHTOZHEN u8"\u0424\u043B\u043E\u0442 \u043F\u0440\u043E\u0442\u0438\u0432\u043D\u0438\u043A\u0430 \u0443\u043D\u0438\u0447\u0442\u043E\u0436\u0435\u043D!"
#define RU_ENTER_MENU       u8"ENTER - \u043C\u0435\u043D\u044E | ESC - \u0432\u044B\u0445\u043E\u0434"
#define RU_VY_PROIGRALI     u8"\u0412\u042B \u041F\u0420\u041E\u0418\u0413\u0420\u0410\u041B\u0418..."
#define RU_VASH_FLOT_POTOP  u8"\u0412\u0430\u0448 \u0444\u043B\u043E\u0442 \u043F\u043E\u0442\u043E\u043F\u043B\u0435\u043D."
#define RU_STRELKI_VYBOR    u8"\u0421\u0442\u0440\u0435\u043B\u043A\u0438 ^/v - \u0432\u044B\u0431\u043E\u0440 | ENTER - \u043F\u043E\u0434\u0442\u0432\u0435\u0440\u0434\u0438\u0442\u044C"
#define RU_SFML_VER         u8"SFML v2.0 | C++17"
#define RU_IZMENIT          u8"</> - \u0438\u0437\u043C\u0435\u043D\u0438\u0442\u044C | ENTER/ESC - \u043D\u0430\u0437\u0430\u0434"

Game::Game()
    : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE,
             sf::Style::Close | sf::Style::Titlebar),
      state(GameState::Menu), prevState(GameState::Menu),
      cursorR(0), cursorC(0), currentShipIdx(0),
      placingHorizontal(true), botLevel(0),
      botThinking(false), botTimer(0),
      soundEnabled(true), autoPlace(false), fullscreen(false),
      animTimer(0), menuSelection(0), settingsSelection(0) {

    window.setFramerateLimit(60);
    loadResources();

    playerBoard = std::make_unique<Board>(50, 80, false);
    enemyBoard = std::make_unique<Board>(580, 80, true);
}

Game::~Game() {}

void Game::loadResources() {
    if (!font.loadFromFile("assets/fonts/Roboto.ttf")) {
        font.loadFromFile("C:/Windows/Fonts/arial.ttf");
    }
    fontBold = font;
}

void Game::applyFullscreen() {
    window.close();
    if (fullscreen) {
        window.create(sf::VideoMode::getDesktopMode(), WINDOW_TITLE, sf::Style::Fullscreen);
    } else {
        window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE,
                      sf::Style::Close | sf::Style::Titlebar);
    }
    window.setFramerateLimit(60);
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
                if (event.key.code == sf::Keyboard::Up && menuSelection > 0) menuSelection--;
                if (event.key.code == sf::Keyboard::Down && menuSelection < 3) menuSelection++;
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
                if (event.key.code == sf::Keyboard::Up && settingsSelection > 0) settingsSelection--;
                if (event.key.code == sf::Keyboard::Down && settingsSelection < 4) settingsSelection++;
                if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Right) {
                    if (settingsSelection == 0) botLevel = 1 - botLevel;
                    if (settingsSelection == 1) autoPlace = !autoPlace;
                    if (settingsSelection == 2) soundEnabled = !soundEnabled;
                    if (settingsSelection == 3) { fullscreen = !fullscreen; applyFullscreen(); }
                }
                if (event.key.code == sf::Keyboard::Enter && settingsSelection == 4)
                    state = GameState::Menu;
                if (event.key.code == sf::Keyboard::Escape)
                    state = GameState::Menu;
            }
            else if (state == GameState::Rules) {
                if (event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::Enter)
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
                    if (placingHorizontal) { if (cursorC + size > BOARD_SIZE) cursorC = BOARD_SIZE - size; }
                    else { if (cursorR + size > BOARD_SIZE) cursorR = BOARD_SIZE - size; }
                }
                if (event.key.code == sf::Keyboard::Enter) {
                    if (playerBoard->canPlaceShip(cursorR, cursorC, size, placingHorizontal)) {
                        playerBoard->placeShip(cursorR, cursorC, size, placingHorizontal);
                        currentShipIdx++;
                        if (currentShipIdx >= FLEET_COUNT) startBattle();
                    }
                }
                if (event.key.code == sf::Keyboard::Escape) state = GameState::Menu;
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
                        if (enemyBoard->allShipsSunk()) { state = GameState::Victory; }
                        else if (!hit) { state = GameState::BotTurn; botTimer = 0; botThinking = true; }
                    }
                }
                if (event.key.code == sf::Keyboard::Escape) state = GameState::Menu;
            }
            else if (state == GameState::Victory || state == GameState::Defeat) {
                if (event.key.code == sf::Keyboard::Enter) { resetGame(); state = GameState::Menu; }
                if (event.key.code == sf::Keyboard::Escape) state = GameState::Menu;
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
            if (playerBoard->allShipsSunk()) state = GameState::Defeat;
            else state = GameState::Battle;
        }
    }
}

void Game::botMakeMove() {
    if (botLevel == 0) {
        int r, c;
        do { r = rand() % BOARD_SIZE; c = rand() % BOARD_SIZE; }
        while (playerBoard->getCellState(r, c) == CellState::Hit ||
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
                        if (playerBoard->getCellState(nr, nc) == CellState::Hit) { lastHitR = nr; lastHitC = nc; }
                        else hunting = false;
                        return;
                    }
                }
            }
            hunting = false;
        }
        if (!hunting) {
            int r, c, attempts = 0;
            do { r = rand() % BOARD_SIZE; c = rand() % BOARD_SIZE; attempts++; }
            while (attempts < 200 && ((r + c) % 2 != 0 ||
                     playerBoard->getCellState(r, c) == CellState::Hit ||
                     playerBoard->getCellState(r, c) == CellState::Miss));
            if (attempts >= 200) {
                do { r = rand() % BOARD_SIZE; c = rand() % BOARD_SIZE; }
                while (playerBoard->getCellState(r, c) == CellState::Hit ||
                       playerBoard->getCellState(r, c) == CellState::Miss);
            }
            playerBoard->shoot(r, c);
            if (playerBoard->getCellState(r, c) == CellState::Hit) { lastHitR = r; lastHitC = c; hunting = true; }
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
    drawText(RU_MORSKOY_BOY, WINDOW_WIDTH / 2, 80, 56, TEXT_GOLD, true);
    drawText(RU_KONSOL_BOY, WINDOW_WIDTH / 2, 140, 20, TEXT, true);
    const char* buttons[] = { RU_NACHAT_IGRU, RU_PRAVILA, RU_NASTROYKI, RU_VYHOD };
    for (int i = 0; i < 4; i++) {
        float y = 250 + i * 70;
        drawButton(buttons[i], WINDOW_WIDTH / 2 - 150, y, 300, 50, false, i == menuSelection);
    }
    drawText(RU_STRELKI_VYBOR, WINDOW_WIDTH / 2, 560, 16, sf::Color(150, 150, 170), true);
    drawText(RU_SFML_VER, WINDOW_WIDTH / 2, 700, 14, sf::Color(100, 100, 120), true);
}

void Game::renderSettings() {
    drawText(RU_NASTROYKI_TITLE, WINDOW_WIDTH / 2, 60, 36, TEXT_GOLD, true);
    const char* labels[] = { RU_SLOZHNOST_BOTA, RU_RASSTANOVKA, RU_ZVUK, RU_FULLSCREEN, RU_NAZAD_MENU };
    const char* values[] = {
        botLevel == 0 ? RU_LEGKIY : RU_SLOZHNYY,
        autoPlace ? RU_AVTO : RU_VRUCHNUYU,
        soundEnabled ? RU_VKL : RU_VYKL,
        fullscreen ? RU_VKL : RU_VYKL,
        ""
    };
    for (int i = 0; i < 5; i++) {
        float y = 160 + i * 80;
        sf::Color color = (i == settingsSelection) ? sf::Color::Yellow : TEXT;
        drawText(labels[i], WINDOW_WIDTH / 2 - 220, y, 22, color, false);
        if (strlen(values[i]) > 0) {
            sf::Color valColor = (i == settingsSelection) ? sf::Color::Green : sf::Color(100, 200, 255);
            drawText(values[i], WINDOW_WIDTH / 2 + 140, y, 22, valColor, false);
        }
    }
    drawText(RU_IZMENIT, WINDOW_WIDTH / 2, 650, 16, sf::Color(150, 150, 170), true);
}

void Game::renderRules() {
    drawText(RU_PRAVILA_IGRY, WINDOW_WIDTH / 2, 50, 36, TEXT_GOLD, true);
    const char* rules[] = {
        RU_TSEL, "", RU_FLOT_10, RU_1X4_AVI, RU_2X3_KREY, RU_3X2_ESM, RU_4X1_MIN,
        "", RU_UPRAVLENIE, RU_STRELKI_PEREM, RU_ENTER_STREL, RU_PROBEL_POVOROT,
        RU_ESC_MENU, "", RU_DOP_HOD, RU_POBEDITEL
    };
    for (int i = 0; i < 16; i++) drawText(rules[i], 100, 120 + i * 28, 20, TEXT, false);
    drawText(RU_NAZHMI_ENTER_ESC, WINDOW_WIDTH / 2, 680, 18, TEXT_GOLD, true);
}

void Game::startPlacement() {
    state = GameState::Placement;
    playerBoard->clear(); enemyBoard->clear();
    enemyBoard->autoPlace();
    currentShipIdx = 0; cursorR = 0; cursorC = 0; placingHorizontal = true;
    if (autoPlace) { playerBoard->autoPlace(); startBattle(); }
}

void Game::renderPlacement() {
    drawText(RU_RASSTANOVKA_KOR, WINDOW_WIDTH / 2, 15, 26, TEXT_GOLD, true);
    int size = FLEET_SIZES[currentShipIdx];
    bool valid = playerBoard->canPlaceShip(cursorR, cursorC, size, placingHorizontal);
    playerBoard->draw(window, font, cursorR, cursorC, true, size, placingHorizontal, valid);
    drawText(RU_VASHE_POLE, 50 + BOARD_PIXELS / 2, 55, 18, TEXT_GOLD, true);

    float panelX = 50 + BOARD_PIXELS + 50;
    sf::RectangleShape panel(sf::Vector2f(280, 530));
    panel.setPosition(panelX, 70);
    panel.setFillColor(PANEL_BG);
    panel.setOutlineColor(GRID_LINE);
    panel.setOutlineThickness(1);
    window.draw(panel);

    drawText(RU_KORABL, panelX + 15, 80, 20, TEXT, false);
    drawText(std::to_string(size) + RU_PALUBNYY, panelX + 15, 105, 22, TEXT_GOLD, false);
    drawText(RU_NAPRAVLENIE, panelX + 15, 140, 16, TEXT, false);
    drawText(placingHorizontal ? RU_GORIZ : RU_VERT, panelX + 15, 160, 16, sf::Color(100, 200, 255), false);
    if (valid) drawText(RU_OK_STAVIT, panelX + 15, 190, 16, sf::Color(50, 200, 80), false);
    else       drawText(RU_MESTO_ZANYATO, panelX + 15, 190, 16, sf::Color(255, 80, 80), false);

    drawText(RU_UPRAVLENIE, panelX + 15, 225, 15, sf::Color(150, 150, 170), false);
    drawText(RU_STRELKI_DVIZH, panelX + 15, 245, 15, sf::Color(150, 150, 170), false);
    drawText(RU_PROBEL_POV, panelX + 15, 262, 15, sf::Color(150, 150, 170), false);
    drawText(RU_ENTER_POSTAVIT, panelX + 15, 279, 15, sf::Color(150, 150, 170), false);
    drawText(RU_ESC_MENU_TXT, panelX + 15, 296, 15, sf::Color(150, 150, 170), false);

    drawText(std::to_string(currentShipIdx) + " / " + std::to_string(FLEET_COUNT), panelX + 15, 325, 20, TEXT_GOLD, false);
    drawText(RU_OSTALOS, panelX + 15, 355, 15, sf::Color(150, 150, 170), false);

    int yPos = 375, fontSize = 14, lineHeight = 17;
    int counts[5] = {0, 0, 0, 0, 0};
    for (int i = currentShipIdx; i < FLEET_COUNT; i++) { int s = FLEET_SIZES[i]; if (s >= 1 && s <= 4) counts[4 - s]++; }
    for (int deck = 4; deck >= 1; deck--) {
        int cnt = counts[4 - deck];
        if (cnt > 0) {
            std::string line = std::to_string(cnt) + " x " + std::string(deck, '#') + " (" + std::to_string(deck) + "p)";
            drawText(line, panelX + 15, yPos, fontSize, sf::Color(100, 180, 255), false);
            yPos += lineHeight;
        }
    }
}

void Game::startBattle() {
    state = GameState::Battle; cursorR = 0; cursorC = 0; botThinking = false;
}

void Game::renderBattle() {
    drawText(RU_BOY_S_BOTOM, WINDOW_WIDTH / 2, 10, 22, TEXT_GOLD, true);
    enemyBoard->draw(window, font, cursorR, cursorC, false, 0, true, true);
    drawText(RU_POLE_VRAGA, 580 + BOARD_PIXELS / 2, 55, 16, sf::Color(255, 100, 100), true);
    playerBoard->draw(window, font, -1, -1, true, 0, true, true);
    drawText(RU_VASHE_POLE, 50 + BOARD_PIXELS / 2, 55, 16, sf::Color(100, 255, 100), true);

    sf::RectangleShape infoPanel(sf::Vector2f(180, 100));
    infoPanel.setPosition(50, 580); infoPanel.setFillColor(PANEL_BG);
    infoPanel.setOutlineColor(GRID_LINE); infoPanel.setOutlineThickness(1);
    window.draw(infoPanel);

    drawText(RU_VRAG + std::to_string(enemyBoard->getShipsAlive()) + RU_KOR, 65, 590, 16, sf::Color(255, 100, 100), false);
    drawText(RU_VY + std::to_string(playerBoard->getShipsAlive()) + RU_KOR, 65, 615, 16, sf::Color(100, 255, 100), false);
    drawText(u8"\u0421\u0442\u0440\u0435\u043B\u043A\u0438 | ENTER | ESC", 65, 640, 14, sf::Color(150, 150, 170), false);
    drawText(RU_PRITSEL + std::string(1, 'A' + cursorC) + std::to_string(cursorR + 1), 580, 580, 18, TEXT_GOLD, false);
}

void Game::renderBotTurn() {
    renderBattle();
    sf::RectangleShape overlay(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    overlay.setFillColor(sf::Color(0, 0, 0, 120));
    window.draw(overlay);
    drawText(RU_BOT_DUMAET, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 36, sf::Color(255, 200, 50), true);
    int dots = (int)(botTimer * 3) % 4;
    drawText(std::string(dots, '.'), WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + 40, 30, sf::Color(255, 200, 50), true);
}

void Game::renderVictory() {
    sf::RectangleShape overlay(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    overlay.setFillColor(sf::Color(0, 30, 0, 180));
    window.draw(overlay);
    drawText(RU_VY_POBEHDILI, WINDOW_WIDTH / 2, 250, 56, sf::Color(50, 255, 100), true);
    drawText(RU_FLOT_UNICHTOZHEN, WINDOW_WIDTH / 2, 330, 24, TEXT, true);
    drawText(RU_ENTER_MENU, WINDOW_WIDTH / 2, 450, 20, TEXT_GOLD, true);
}

void Game::renderDefeat() {
    sf::RectangleShape overlay(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    overlay.setFillColor(sf::Color(30, 0, 0, 180));
    window.draw(overlay);
    drawText(RU_VY_PROIGRALI, WINDOW_WIDTH / 2, 250, 56, sf::Color(255, 50, 50), true);
    drawText(RU_VASH_FLOT_POTOP, WINDOW_WIDTH / 2, 330, 24, TEXT, true);
    drawText(RU_ENTER_MENU, WINDOW_WIDTH / 2, 450, 20, TEXT_GOLD, true);
}

// UTF-8 safe text rendering using SFML's fromUtf8
void Game::drawText(const std::string& text, float x, float y, int size, sf::Color color, bool center) {
    sf::Text t;
    t.setString(sf::String::fromUtf8(text.begin(), text.end()));
    t.setFont(font);
    t.setCharacterSize(size);
    t.setFillColor(color);
    if (center) {
        sf::FloatRect bounds = t.getLocalBounds();
        t.setOrigin(bounds.width / 2, 0);
    }
    t.setPosition(x, y);
    window.draw(t);
}

// UTF-8 safe button rendering
void Game::drawButton(const std::string& text, float x, float y, float w, float h, bool hovered, bool selected) {
    sf::RectangleShape button(sf::Vector2f(w, h));
    button.setPosition(x, y);
    sf::Color fillColor = selected ? BUTTON_HOVER : BUTTON;
    if (hovered) fillColor = BUTTON_HOVER;
    button.setFillColor(fillColor);
    button.setOutlineColor(selected ? sf::Color::Yellow : sf::Color(100, 160, 220));
    button.setOutlineThickness(selected ? 3 : 2);
    window.draw(button);

    sf::Text label;
    label.setString(sf::String::fromUtf8(text.begin(), text.end()));
    label.setFont(font);
    label.setCharacterSize(24);
    label.setFillColor(BUTTON_TEXT);
    sf::FloatRect bounds = label.getLocalBounds();
    label.setOrigin(bounds.width / 2, bounds.height / 2);
    label.setPosition(x + w / 2, y + h / 2 - 5);
    window.draw(label);
}

bool Game::isMouseOver(float x, float y, float w, float h) const {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    return mousePos.x >= x && mousePos.x <= x + w && mousePos.y >= y && mousePos.y <= y + h;
}

void Game::playHitSound() {}
void Game::playMissSound() {}

void Game::resetGame() {
    playerBoard->clear(); enemyBoard->clear();
    cursorR = 0; cursorC = 0; currentShipIdx = 0; menuSelection = 0;
}
