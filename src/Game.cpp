// ============================================================================
// Game.cpp - v4.0 Pirate Edition (Victory fix + Sprites + Explosions + Phrases)
// ============================================================================

#include "Game.hpp"
#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>

using namespace Colors;

// ===== Pirate UTF-8 Text =====
#define RU_MORSKOY_BOY  u8"\u2620 \u041C\u041E\u0420\u0421\u041A\u041E\u0419 \u0411\u041E\u0419 \u2620"
#define RU_SUBTITLE     u8"\u041F\u0438\u0440\u0430\u0442\u0441\u043A\u0430\u044F \u043C\u043E\u0440\u0441\u043A\u0430\u044F \u0431\u0438\u0442\u0432\u0430 v4.0"
#define RU_NACHAT       u8"\u041D\u0430\u0447\u0430\u0442\u044C \u0431\u043E\u0439!"
#define RU_PRAVILA      u8"\u041A\u0430\u0440\u0442\u0430 \u0441\u043E\u043A\u0440\u043E\u0432\u0438\u0449"
#define RU_NASTROYKI    u8"\u041D\u0430\u0441\u0442\u0440\u043E\u0439\u043A\u0438 \u043A\u043E\u0440\u0430\u0431\u043B\u044F"
#define RU_VYHOD        u8"\u041F\u043E\u043A\u0438\u043D\u0443\u0442\u044C \u043A\u043E\u0440\u0430\u0431\u043B\u044C"
#define RU_NAST_TITLE   u8"\u041D\u0410\u0421\u0422\u0420\u041E\u0419\u041A\u0418"
#define RU_BOT_LVL      u8"\u0421\u043B\u043E\u0436\u043D\u043E\u0441\u0442\u044C \u0431\u043E\u0442\u0430"
#define RU_RASST        u8"\u0420\u0430\u0441\u0441\u0442\u0430\u043D\u043E\u0432\u043A\u0430"
#define RU_ZVUK         u8"\u0417\u0432\u0443\u043A"
#define RU_FULLSCR      u8"\u041F\u043E\u043B\u043D\u044B\u0439 \u044D\u043A\u0440\u0430\u043D"
#define RU_NAZAD        u8"\u041D\u0430\u0437\u0430\u0434"
#define RU_LEGKIY       u8"\u041B\u0401\u0413\u041A\u0418\u0419"
#define RU_HARD         u8"\u0421\u041B\u041E\u0416\u041D\u042B\u0419"
#define RU_AVTO         u8"\u0410\u0412\u0422\u041E"
#define RU_RUCH         u8"\u0412\u0420\u0423\u0427\u041D\u0423\u042E"
#define RU_VKL          u8"\u0412\u041A\u041B"
#define RU_VYKL         u8"\u0412\u042B\u041A\u041B"
#define RU_RULES_TITLE  u8"\u041A\u0410\u0420\u0422\u0410 \u0421\u041E\u041A\u0420\u041E\u0412\u0418\u0429"
#define RU_R1           u8"\u0426\u0435\u043B\u044C: \u043F\u043E\u0442\u043E\u043F\u0438\u0442\u044C \u0432\u0435\u0441\u044C \u0444\u043B\u043E\u0442 \u043F\u0440\u043E\u0442\u0438\u0432\u043D\u0438\u043A\u0430 (20 \u043F\u0430\u043B\u0443\u0431)."
#define RU_R2           u8"\u0424\u043B\u043E\u0442: 1x4, 2x3, 3x2, 4x1 \u043A\u043E\u0440\u0430\u0431\u043B\u044F."
#define RU_R3           u8"\u041A\u043E\u0440\u0430\u0431\u043B\u0438 \u043D\u0435 \u043A\u0430\u0441\u0430\u044E\u0442\u0441\u044F (\u043E\u0440\u0435\u043E\u043B \u0432\u043E\u043A\u0440\u0443\u0433)."
#define RU_R4           u8"\u041F\u0440\u0438 \u043F\u043E\u043F\u0430\u0434\u0430\u043D\u0438\u0438 - \u0435\u0449\u0451 \u0445\u043E\u0434!"
#define RU_R5           u8"\u041F\u0440\u0438 \u0443\u043D\u0438\u0447\u0442\u043E\u0436\u0435\u043D\u0438\u0438 - \u043E\u0440\u0435\u043E\u043B \u0430\u0432\u0442\u043E-\u0432\u044B\u0447\u0435\u0440\u043A\u0438\u0432\u0430\u0435\u0442\u0441\u044F."
#define RU_R6           u8"\u0421\u0442\u0440\u0435\u043B\u043A\u0438 - \u0434\u0432\u0438\u0436\u0435\u043D\u0438\u0435  |  ENTER - \u0432\u044B\u0441\u0442\u0440\u0435\u043B"
#define RU_R7           u8"\u041F\u0420\u041E\u0411\u0415\u041B - \u043F\u043E\u0432\u043E\u0440\u043E\u0442  |  ESC - \u041C\u0435\u043D\u044E"
#define RU_R8           u8"\u041F\u0435\u0440\u0432\u044B\u0439 \u0445\u043E\u0434 \u043E\u043F\u0440\u0435\u0434\u0435\u043B\u044F\u0435\u0442\u0441\u044F \u043C\u043E\u043D\u0435\u0442\u043A\u043E\u0439 (50/50)."
#define RU_R9           u8"\u041F\u043E\u0431\u0435\u0436\u0434\u0430\u0435\u0442 \u0442\u043E\u0442, \u043A\u0442\u043E \u043F\u0435\u0440\u0432\u044B\u043C \u0443\u043D\u0438\u0447\u0442\u043E\u0436\u0438\u0442 20 \u043F\u0430\u043B\u0443\u0431!"
#define RU_PRESS        u8"\u041D\u0430\u0436\u043C\u0438 ENTER \u0438\u043B\u0438 ESC..."
#define RU_PLACE_TITLE  u8"\u0420\u0410\u0421\u0421\u0422\u0410\u041D\u041E\u0412\u041A\u0410 \u0424\u041B\u041E\u0422\u0410"
#define RU_VASHE        u8"\u0412\u0430\u0448\u0435 \u043F\u043E\u043B\u0435"
#define RU_KORABL       u8"\u041A\u043E\u0440\u0430\u0431\u043B\u044C:"
#define RU_PALUB        u8"-\u043F\u0430\u043B\u0443\u0431\u043D\u044B\u0439"
#define RU_NAPR         u8"\u041D\u0430\u043F\u0440\u0430\u0432\u043B\u0435\u043D\u0438\u0435:"
#define RU_GORIZ        u8">>> \u0413\u041E\u0420\u0418\u0417\u041E\u041D\u0422\u0410\u041B\u042C\u041D\u041E"
#define RU_VERT         u8"vvv \u0412\u0415\u0420\u0422\u0418\u041A\u0410\u041B\u042C\u041D\u041E"
#define RU_OK           u8"[OK] \u041C\u043E\u0436\u043D\u043E \u0441\u0442\u0430\u0432\u0438\u0442\u044C"
#define RU_BAD          u8"[X] \u041C\u0435\u0441\u0442\u043E \u0437\u0430\u043D\u044F\u0442\u043E!"
#define RU_STRELKI      u8"\u0421\u0442\u0440\u0435\u043B\u043A\u0438 - \u0434\u0432\u0438\u0436\u0435\u043D\u0438\u0435"
#define RU_PROBEL       u8"\u041F\u0420\u041E\u0411\u0415\u041B - \u043F\u043E\u0432\u043E\u0440\u043E\u0442"
#define RU_ENT          u8"ENTER - \u043F\u043E\u0441\u0442\u0430\u0432\u0438\u0442\u044C"
#define RU_ESC          u8"ESC - \u041C\u0435\u043D\u044E"
#define RU_OST          u8"\u041E\u0441\u0442\u0430\u043B\u043E\u0441\u044C:"
#define RU_BOY          u8"\u0411\u041E\u0419 \u0421 \u0411\u041E\u0422\u041E\u041C"
#define RU_POLE_V       u8"\u041F\u043E\u043B\u0435 \u0432\u0440\u0430\u0433\u0430"
#define RU_BOT_DUM      u8"\u0411\u041E\u0422 \u0414\u0423\u041C\u0410\u0415\u0422..."
#define RU_WIN          u8"\u0412\u042B \u041F\u041E\u0411\u0415\u0414\u0418\u041B\u0418!"
#define RU_WIN2         u8"\u0412\u0441\u0435 \u043A\u043E\u0440\u0430\u0431\u043B\u0438 \u043F\u0440\u043E\u0442\u0438\u0432\u043D\u0438\u043A\u0430 \u043D\u0430 \u0434\u043D\u0435!"
#define RU_LOSE         u8"\u0412\u042B \u041F\u0420\u041E\u0418\u0413\u0420\u0410\u041B\u0418..."
#define RU_LOSE2        u8"\u0412\u0430\u0448 \u0444\u043B\u043E\u0442 \u043F\u043E\u0442\u043E\u043F\u043B\u0435\u043D!"
#define RU_MENU2        u8"ENTER - \u041C\u0435\u043D\u044E  |  ESC - \u0412\u044B\u0445\u043E\u0434"
#define RU_VRAG         u8"\u0412\u0440\u0430\u0433: "
#define RU_KOR          u8" \u043A\u043E\u0440."
#define RU_VY           u8"\u0412\u044B: "
#define RU_PRITSEL      u8"\u041F\u0440\u0438\u0446\u0435\u043B: "
#define RU_PERV_HOD     u8"\u041F\u0435\u0440\u0432\u044B\u0439 \u0445\u043E\u0434: "
#define RU_PERV_VY      u8"\u0412\u044B!"
#define RU_PERV_BOT     u8"\u0411\u043E\u0442"
#define RU_POTOP        u8"\u041F\u043E\u0442\u043E\u043F\u043B\u0435\u043D\u043E: "
#define RU_PALUB_U      u8"\u041F\u0430\u043B\u0443\u0431: "
#define RU_UPR          u8"\u2191\u2193\u2190\u2192 \u0434\u0432\u0438\u0436. | ENTER-\u0432\u044B\u0441\u0442\u0440\u0435\u043B | ESC-\u041C\u0435\u043D\u044E"

// Layout
const float P_BX = 45,  P_BY = 75;
const float E_BX = 625, E_BY = 75;
const float INF_X = 45, INF_Y = 545, INF_W = 1040, INF_H = 110;

Game::Game()
    : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE,
             sf::Style::Close | sf::Style::Titlebar),
      state(GameState::Menu), cursorR(0), cursorC(0), currentShipIdx(0),
      placingHorizontal(true), botLevel(0), botThinking(false), botTimer(0),
      soundEnabled(true), autoPlace(false), fullscreen(false), playerTurnFirst(true),
      animTimer(0), menuSelection(0), settingsSelection(0),
      botDirIndex(0), botHunting(false), spritesLoaded(false), messageTimer(0) {

    srand((unsigned)time(nullptr));
    window.setFramerateLimit(60);
    loadResources();
    playerBoard = std::make_unique<Board>(P_BX, P_BY, false);
    enemyBoard = std::make_unique<Board>(E_BX, E_BY, true);
}

Game::~Game() {}

bool Game::loadTexture(sf::Texture& tex, const std::string& path) {
    if (tex.loadFromFile(path)) return true;
    return false;
}

void Game::loadResources() {
    if (!font.loadFromFile("assets/fonts/Roboto.ttf"))
        font.loadFromFile("C:/Windows/Fonts/arial.ttf");

    spritesLoaded = true;
    if (!loadTexture(texFrigate,  "assets/frigate.png"))   spritesLoaded = false;
    if (!loadTexture(texSkeleton, "assets/skeleton.png"))  spritesLoaded = false;
    if (!loadTexture(texTreasure, "assets/treasure.png"))  spritesLoaded = false;
    if (!loadTexture(texPalms,    "assets/palms.png"))     spritesLoaded = false;
    if (!loadTexture(texExplosion,"assets/explosion.png")) spritesLoaded = false;

    if (spritesLoaded) {
        sprFrigate.setTexture(texFrigate);
        sprSkeleton.setTexture(texSkeleton);
        sprTreasure.setTexture(texTreasure);
        sprPalms.setTexture(texPalms);
        sprExplosion.setTexture(texExplosion);

        sprFrigate.setScale(0.55f, 0.55f);
        sprSkeleton.setScale(0.5f, 0.5f);
        sprTreasure.setScale(0.4f, 0.4f);
        sprPalms.setScale(0.45f, 0.45f);

        sprFrigate.setPosition(5, 180);
        sprSkeleton.setPosition(WINDOW_WIDTH - 155, 160);
        sprTreasure.setPosition(WINDOW_WIDTH - 130, 440);
        sprPalms.setPosition(-10, 430);
    }
}

sf::String Game::toUtf8(const std::string& text) const {
    return sf::String::fromUtf8(text.begin(), text.end());
}

void Game::applyFullscreen() {
    window.close();
    if (fullscreen)
        window.create(sf::VideoMode::getDesktopMode(), WINDOW_TITLE, sf::Style::Fullscreen);
    else
        window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE,
                      sf::Style::Close | sf::Style::Titlebar);
    window.setFramerateLimit(60);
}

void Game::run() {
    sf::Clock clock;
    while (window.isOpen() && state != GameState::Exit) {
        float dt = clock.restart().asSeconds();
        animTimer += dt;
        update(dt);
        handleEvents();
        render();
    }
}

void Game::addMessage(const std::string& text, sf::Color color) {
    messages.push_back({text, 2.5f, color});
    lastMessage = text;
    messageTimer = 2.5f;
}

void Game::addExplosion(float x, float y) {
    explosions.push_back({x, y, 0.6f, 0.1f});
}

std::string Game::getRandomHitPhrase() const {
    const char* phrases[] = {
        u8"\u041F\u0440\u044F\u043C\u043E \u0432 \u0446\u0435\u043B\u044C, \u043A\u0430\u043F\u0438\u0442\u0430\u043D!",
        u8"\u0415\u0449\u0451 \u043E\u0434\u0438\u043D \u043A \u0414\u044D\u0432\u0438 \u0414\u0436\u043E\u043D\u0441\u0443!",
        u8"\u0410\u0440\u0440\u0440! \u041E\u0433\u043E\u043D\u044C \u0438 \u043F\u043E\u0440\u043E\u0445!",
        u8"\u041C\u0435\u0442\u043A\u0430\u044F \u043F\u043E\u043F\u0430\u043B!",
        u8"\u041A\u043E\u0440\u0430\u0431\u043B\u044C \u0433\u043E\u0440\u0438\u0442!",
        u8"\u0423\u0434\u0430\u0447\u0430 \u043F\u0438\u0440\u0430\u0442\u0430!"
    };
    return phrases[rand() % 6];
}

std::string Game::getRandomMissPhrase() const {
    const char* phrases[] = {
        u8"\u041C\u0438\u043C\u043E! \u0422\u043E\u043B\u044C\u043A\u043E \u0432\u043E\u043B\u043D\u044B...",
        u8"\u041C\u043E\u0440\u0441\u043A\u0430\u044F \u043F\u0435\u043D\u0430!",
        u8"\u041F\u0440\u043E\u043C\u0430\u0445... \u0412\u0435\u0442\u0435\u0440 \u043F\u043E\u043C\u0435\u0448\u0430\u043B!",
        u8"\u041D\u0435\u0442! \u0417\u0434\u0435\u0441\u044C \u043F\u0443\u0441\u0442\u043E!",
        u8"\u0420\u044B\u0431\u044B \u043F\u043B\u0430\u0432\u0430\u044E\u0442...",
        u8"\u041C\u0438\u043C\u043E! \u0412 \u0441\u043B\u0435\u0434\u0443\u044E\u0449\u0438\u0439 \u0440\u0430\u0437!"
    };
    return phrases[rand() % 6];
}

std::string Game::getRandomSunkPhrase() const {
    const char* phrases[] = {
        u8"\u041A\u041E\u0420\u0410\u0411\u041B\u042C \u041D\u0410 \u0414\u041D\u041E!",
        u8"\u0423\u041D\u0418\u0427\u0422\u041E\u0416\u0415\u041D! \u0410\u0440\u0440\u0440!",
        u8"\u041F\u043E\u0442\u043E\u043F\u043B\u0435\u043D! \u0422\u0430\u043A \u0435\u043C\u0443!",
        u8"\u041D\u0430 \u0434\u043D\u043E \u043A\u043E \u0434\u044C\u044F\u0432\u043E\u043B\u0443!",
        u8"\u0412\u0437\u0440\u044B\u0432! \u041A\u043E\u0440\u0430\u0431\u043B\u044C \u0440\u0430\u0437\u043B\u0435\u0442\u0435\u043B\u0441\u044F!"
    };
    return phrases[rand() % 5];
}

std::string Game::getRandomBotHitPhrase() const {
    const char* phrases[] = {
        u8"\u0411\u043E\u0442 \u043F\u043E\u043F\u0430\u043B! \u0412 \u0430\u0441 \u0441\u0442\u0440\u0435\u043B\u044F\u044E\u0442!",
        u8"\u0412\u0440\u0430\u0436\u0435\u0441\u043A\u0430\u044F \u044F\u0434\u0440\u0430!",
        u8"\u041D\u0430\u0448 \u043A\u043E\u0440\u0430\u0431\u043B\u044C \u043F\u043E\u0434 \u043E\u0431\u0441\u0442\u0440\u0435\u043B\u043E\u043C!",
        u8"\u0410\u0440\u0440\u0440! \u0412\u0440\u0430\u0433 \u043F\u043E\u043F\u0430\u043B!",
        u8"\u041A\u043E\u0440\u043F\u0443\u0441 \u0440\u0430\u043D\u0435\u043D!"
    };
    return phrases[rand() % 5];
}

void Game::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) state = GameState::Exit;

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
                if (event.key.code == sf::Keyboard::Enter && settingsSelection == 4) state = GameState::Menu;
                if (event.key.code == sf::Keyboard::Escape) state = GameState::Menu;
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
                    CellState cs = enemyBoard->getCellState(cursorR, cursorC);
                    if (cs != CellState::Hit && cs != CellState::Miss) {
                        int shipsBefore = enemyBoard->getShipsAlive();
                        bool hit = enemyBoard->shoot(cursorR, cursorC);
                        int shipsAfter = enemyBoard->getShipsAlive();

                        if (hit) {
                            if (shipsAfter < shipsBefore) {
                                addMessage(getRandomSunkPhrase(), sf::Color(255, 140, 0));
                                addExplosion(E_BX + 30 + cursorC * (CELL_SIZE + CELL_MARGIN),
                                             E_BY + 30 + cursorR * (CELL_SIZE + CELL_MARGIN));
                            } else {
                                addMessage(getRandomHitPhrase(), sf::Color(255, 80, 80));
                            }
                        } else {
                            addMessage(getRandomMissPhrase(), sf::Color(150, 200, 255));
                        }

                        if (enemyBoard->allShipsSunk()) {
                            state = GameState::Victory;
                        } else if (!hit) {
                            state = GameState::BotTurn;
                            botTimer = 0;
                            botThinking = true;
                        }
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
    for (auto& m : messages) m.timer -= dt;
    messages.erase(std::remove_if(messages.begin(), messages.end(),
        [](const BattleMessage& m) { return m.timer <= 0; }), messages.end());
    if (messageTimer > 0) messageTimer -= dt;

    for (auto& e : explosions) { e.timer -= dt; e.scale += dt * 3; }
    explosions.erase(std::remove_if(explosions.begin(), explosions.end(),
        [](const ExplosionEffect& e) { return e.timer <= 0; }), explosions.end());

    if (state == GameState::BotTurn && botThinking) {
        botTimer += dt;
        if (botTimer >= BOT_THINK_DELAY) {
            int shipsBefore = playerBoard->getShipsAlive();
            botMakeMove();
            int shipsAfter = playerBoard->getShipsAlive();

            if (shipsAfter < shipsBefore) {
                addMessage(getRandomSunkPhrase(), sf::Color(255, 140, 0));
            } else if (!botTargets.empty() && botHunting) {
                addMessage(getRandomBotHitPhrase(), sf::Color(255, 100, 100));
            }

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
        do { r = rand() % BOARD_SIZE; c = rand() % BOARD_SIZE; }
        while (playerBoard->getCellState(r, c) == CellState::Hit ||
               playerBoard->getCellState(r, c) == CellState::Miss);
        playerBoard->shoot(r, c);
    } else {
        if (botHunting && !botTargets.empty()) {
            int tr = botTargets[0].first;
            int tc = botTargets[0].second;

            if (botTargets.size() >= 2) {
                bool horizontal = botTargets[0].first == botTargets[1].first;
                int minR = tr, maxR = tr, minC = tc, maxC = tc;
                for (auto& t : botTargets) {
                    minR = std::min(minR, t.first); maxR = std::max(maxR, t.first);
                    minC = std::min(minC, t.second); maxC = std::max(maxC, t.second);
                }
                int nr, nc;
                if (horizontal) {
                    nr = tr; nc = maxC + 1;
                    if (nc >= BOARD_SIZE || playerBoard->getCellState(nr, nc) == CellState::Miss) {
                        nc = minC - 1;
                    }
                } else {
                    nr = maxR + 1; nc = tc;
                    if (nr >= BOARD_SIZE || playerBoard->getCellState(nr, nc) == CellState::Miss) {
                        nr = minR - 1;
                    }
                }
                if (nr >= 0 && nr < BOARD_SIZE && nc >= 0 && nc < BOARD_SIZE &&
                    playerBoard->getCellState(nr, nc) != CellState::Hit &&
                    playerBoard->getCellState(nr, nc) != CellState::Miss) {
                    bool hit = playerBoard->shoot(nr, nc);
                    if (hit) botTargets.push_back({nr, nc});
                    else { botDirIndex++; if (botDirIndex > 3) { botHunting = false; botTargets.clear(); botDirIndex = 0; } }
                    return;
                }
            }

            int dirs[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};
            for (int i = botDirIndex; i < 4; i++) {
                int nr = tr + dirs[i][0], nc = tc + dirs[i][1];
                if (nr >= 0 && nr < BOARD_SIZE && nc >= 0 && nc < BOARD_SIZE &&
                    playerBoard->getCellState(nr, nc) != CellState::Hit &&
                    playerBoard->getCellState(nr, nc) != CellState::Miss) {
                    botDirIndex = i;
                    bool hit = playerBoard->shoot(nr, nc);
                    if (hit) botTargets.push_back({nr, nc});
                    else botDirIndex++;
                    return;
                }
            }
            botHunting = false;
            botTargets.clear();
            botDirIndex = 0;
        }

        if (!botHunting) {
            int r, c, attempts = 0;
            do {
                r = rand() % BOARD_SIZE; c = rand() % BOARD_SIZE; attempts++;
            } while (attempts < 300 && ((r + c) % 2 != 0 ||
                     playerBoard->getCellState(r, c) == CellState::Hit ||
                     playerBoard->getCellState(r, c) == CellState::Miss));
            if (attempts >= 300) {
                do { r = rand() % BOARD_SIZE; c = rand() % BOARD_SIZE; }
                while (playerBoard->getCellState(r, c) == CellState::Hit ||
                       playerBoard->getCellState(r, c) == CellState::Miss);
            }
            bool hit = playerBoard->shoot(r, c);
            if (hit) {
                botHunting = true;
                botTargets.clear();
                botTargets.push_back({r, c});
                botDirIndex = 0;
            }
        }
    }
}

void Game::startPlacement() {
    state = GameState::Placement;
    playerBoard->clear(); enemyBoard->clear();
    enemyBoard->autoPlace();
    currentShipIdx = 0; cursorR = 0; cursorC = 0; placingHorizontal = true;
    messages.clear(); explosions.clear();
    if (autoPlace) { playerBoard->autoPlace(); startBattle(); }
}

void Game::startBattle() {
    state = GameState::Battle;
    cursorR = 0; cursorC = 0; botThinking = false;
    botTargets.clear(); botHunting = false; botDirIndex = 0;
    messages.clear(); explosions.clear();
    playerTurnFirst = (rand() % 2 == 0);
    if (!playerTurnFirst) {
        state = GameState::BotTurn;
        botTimer = 0; botThinking = true;
    }
}

void Game::resetGame() {
    playerBoard->clear(); enemyBoard->clear();
    cursorR = 0; cursorC = 0; currentShipIdx = 0; menuSelection = 0;
    botTargets.clear(); botHunting = false; botDirIndex = 0;
    messages.clear(); explosions.clear();
}

// ===== RENDERING =====

void Game::render() {
    window.clear(BG);
    switch (state) {
        case GameState::Menu:      renderMenu(); break;
        case GameState::Settings:  renderSettings(); break;
        case GameState::Rules:     renderRules(); break;
        case GameState::Placement: renderPlacement(); break;
        case GameState::Battle:    renderBattle(); break;
        case GameState::BotTurn:   renderBotTurn(); break;
        case GameState::Victory:   renderVictory(); break;
        case GameState::Defeat:    renderDefeat(); break;
        default: break;
    }
    window.display();
}

void Game::drawText(const std::string& text, float x, float y, int size, sf::Color color, bool center) {
    sf::Text t;
    t.setString(toUtf8(text));
    t.setFont(font);
    t.setCharacterSize(size);
    t.setFillColor(color);
    if (center) {
        sf::FloatRect b = t.getLocalBounds();
        t.setOrigin(b.width / 2, 0);
    }
    t.setPosition(x, y);
    window.draw(t);
}

void Game::drawButton(const std::string& text, float x, float y, float w, float h, bool hovered, bool selected) {
    sf::RectangleShape btn(sf::Vector2f(w, h));
    btn.setPosition(x, y);
    sf::Color fill = selected ? BUTTON_HOVER : BUTTON;
    if (hovered) fill = BUTTON_HOVER;
    btn.setFillColor(fill);
    btn.setOutlineColor(selected ? sf::Color::Yellow : sf::Color(100, 160, 220));
    btn.setOutlineThickness(selected ? 3 : 2);
    window.draw(btn);

    sf::Text lbl;
    lbl.setString(toUtf8(text));
    lbl.setFont(font);
    lbl.setCharacterSize(22);
    lbl.setFillColor(BUTTON_TEXT);
    sf::FloatRect b = lbl.getLocalBounds();
    lbl.setOrigin(b.width / 2, b.height / 2);
    lbl.setPosition(x + w / 2, y + h / 2 - 4);
    window.draw(lbl);
}

void Game::drawDecorations() {
    if (!spritesLoaded) return;
    if (state == GameState::Menu || state == GameState::Battle ||
        state == GameState::BotTurn || state == GameState::Placement) {
        window.draw(sprFrigate);
        window.draw(sprSkeleton);
        window.draw(sprTreasure);
        window.draw(sprPalms);
    }
}

void Game::drawInfoPanel() {
    sf::RectangleShape panel(sf::Vector2f(INF_W, INF_H));
    panel.setPosition(INF_X, INF_Y);
    panel.setFillColor(PANEL_BG);
    panel.setOutlineColor(GRID_LINE);
    panel.setOutlineThickness(2);
    window.draw(panel);

    // Corner anchors
    sf::RectangleShape aTL(sf::Vector2f(20, 4));
    aTL.setPosition(INF_X, INF_Y); aTL.setFillColor(TEXT_GOLD); window.draw(aTL);
    sf::RectangleShape aTL2(sf::Vector2f(4, 20));
    aTL2.setPosition(INF_X, INF_Y); aTL2.setFillColor(TEXT_GOLD); window.draw(aTL2);

    sf::RectangleShape aTR(sf::Vector2f(20, 4));
    aTR.setPosition(INF_X + INF_W - 20, INF_Y); aTR.setFillColor(TEXT_GOLD); window.draw(aTR);
    sf::RectangleShape aTR2(sf::Vector2f(4, 20));
    aTR2.setPosition(INF_X + INF_W - 4, INF_Y); aTR2.setFillColor(TEXT_GOLD); window.draw(aTR2);

    // Left: ship counts
    std::string shipText = std::string(RU_VY) + std::to_string(playerBoard->getShipsAlive()) + std::string(RU_KOR);
    drawText(shipText, INF_X + 30, INF_Y + 18, 20, sf::Color(100, 255, 150), false);

    std::string enemyText = std::string(RU_VRAG) + std::to_string(enemyBoard->getShipsAlive()) + std::string(RU_KOR);
    drawText(enemyText, INF_X + 30, INF_Y + 50, 20, sf::Color(255, 120, 100), false);

    // Center: crosshair
    std::string aim = std::string(RU_PRITSEL) + char('A' + cursorC) + std::to_string(cursorR + 1);
    drawText(aim, INF_X + INF_W / 2, INF_Y + 25, 26, TEXT_GOLD, true);

    // Right: sunk count + decks
    int sunkPlayer = 10 - enemyBoard->getShipsAlive();
    int sunkEnemy = 10 - playerBoard->getShipsAlive();
    drawText(std::string(RU_POTOP) + std::to_string(sunkPlayer), INF_X + INF_W - 220, INF_Y + 18, 18, sf::Color(255, 180, 50), false);
    drawText(std::string(RU_PALUB_U) + std::to_string(sunkPlayer * 2 + sunkEnemy), INF_X + INF_W - 220, INF_Y + 50, 18, sf::Color(200, 160, 80), false);

    // Bottom
    drawText(RU_UPR, INF_X + INF_W / 2, INF_Y + 82, 15, sf::Color(140, 140, 160), true);
    std::string firstTurn = std::string(RU_PERV_HOD) + (playerTurnFirst ? RU_PERV_VY : RU_PERV_BOT);
    drawText(firstTurn, INF_X + 30, INF_Y + 82, 15, sf::Color(100, 200, 255), false);
}

void Game::renderMenu() {
    drawDecorations();

    for (int i = 0; i < 6; i++) {
        float x = 80 + i * 180 + sin(animTimer * 0.8f + i * 1.3f) * 25;
        float y = 480 + cos(animTimer * 0.6f + i * 0.9f) * 35;
        sf::RectangleShape wave(sf::Vector2f(CELL_SIZE + 4, CELL_SIZE + 4));
        wave.setPosition(x, y);
        int a = 60 + (int)(sin(animTimer + i) * 30);
        wave.setFillColor(sf::Color(30, 90, 150, a));
        window.draw(wave);
    }

    drawText(RU_MORSKOY_BOY, WINDOW_WIDTH / 2, 70, 52, TEXT_GOLD, true);
    drawText(RU_SUBTITLE, WINDOW_WIDTH / 2, 130, 18, sf::Color(180, 160, 100), true);

    sf::RectangleShape sep(sf::Vector2f(400, 2));
    sep.setPosition(WINDOW_WIDTH / 2 - 200, 165);
    sep.setFillColor(GRID_LINE);
    window.draw(sep);

    const char* buttons[] = { RU_NACHAT, RU_PRAVILA, RU_NASTROYKI, RU_VYHOD };
    for (int i = 0; i < 4; i++) {
        float y = 200 + i * 72;
        drawButton(buttons[i], WINDOW_WIDTH / 2 - 150, y, 300, 52, false, i == menuSelection);
    }

    drawText(u8"\u0421\u0442\u0440\u0435\u043B\u043A\u0438 ^/v - \u0432\u044B\u0431\u043E\u0440  |  ENTER - \u043F\u043E\u0434\u0442\u0432\u0435\u0440\u0434\u0438\u0442\u044C",
             WINDOW_WIDTH / 2, 530, 16, sf::Color(140, 140, 160), true);

    if (spritesLoaded) {
        sf::Sprite t = sprTreasure;
        t.setPosition(WINDOW_WIDTH / 2 - 30, 570);
        t.setScale(0.35f, 0.35f);
        window.draw(t);
    }
}

void Game::renderSettings() {
    drawText(RU_NAST_TITLE, WINDOW_WIDTH / 2, 55, 38, TEXT_GOLD, true);

    const char* labels[] = { RU_BOT_LVL, RU_RASST, RU_ZVUK, RU_FULLSCR, RU_NAZAD };
    const char* values[] = {
        botLevel == 0 ? RU_LEGKIY : RU_HARD,
        autoPlace ? RU_AVTO : RU_RUCH,
        soundEnabled ? RU_VKL : RU_VYKL,
        fullscreen ? RU_VKL : RU_VYKL,
        ""
    };
    for (int i = 0; i < 5; i++) {
        float y = 160 + i * 85;
        sf::Color color = (i == settingsSelection) ? sf::Color::Yellow : TEXT;
        drawText(labels[i], WINDOW_WIDTH / 2 - 250, y, 24, color, false);
        if (strlen(values[i]) > 0) {
            sf::Color vc = (i == settingsSelection) ? sf::Color::Green : sf::Color(100, 200, 255);
            drawText(values[i], WINDOW_WIDTH / 2 + 180, y, 24, vc, false);
        }
    }
    drawText(u8"</> - \u0438\u0437\u043C\u0435\u043D\u0438\u0442\u044C  |  ENTER/ESC - \u043D\u0430\u0437\u0430\u0434",
             WINDOW_WIDTH / 2, 650, 16, sf::Color(140, 140, 160), true);
}

void Game::renderRules() {
    drawText(RU_RULES_TITLE, WINDOW_WIDTH / 2, 50, 38, TEXT_GOLD, true);

    const char* lines[] = { RU_R1, RU_R2, RU_R3, RU_R4, RU_R5, RU_R6, RU_R7, RU_R8, RU_R9 };
    for (int i = 0; i < 9; i++) {
        sf::Color color = (i < 5) ? TEXT : sf::Color(180, 180, 200);
        drawText(lines[i], 80, 120 + i * 40, 20, color, false);
    }
    drawText(RU_PRESS, WINDOW_WIDTH / 2, 520, 20, TEXT_GOLD, true);
    drawText(u8"\u041F\u0438\u0440\u0430\u0442\u0441\u043A\u0438\u0435 \u0437\u0430\u043A\u043E\u043D\u044B \u043C\u043E\u0440\u0441\u043A\u043E\u0433\u043E \u0431\u043E\u044F:",
             80, 85, 18, sf::Color(200, 160, 80), false);
}

void Game::renderPlacement() {
    drawText(RU_PLACE_TITLE, WINDOW_WIDTH / 2, 15, 26, TEXT_GOLD, true);

    int size = FLEET_SIZES[currentShipIdx];
    bool valid = playerBoard->canPlaceShip(cursorR, cursorC, size, placingHorizontal);
    playerBoard->draw(window, font, cursorR, cursorC, true, size, placingHorizontal, valid);
    drawText(RU_VASHE, P_BX + BOARD_PIXELS / 2 + 20, 50, 18, sf::Color(100, 255, 150), true);

    float px = P_BX + BOARD_PIXELS + 55;
    sf::RectangleShape panel(sf::Vector2f(260, 430));
    panel.setPosition(px, P_BY);
    panel.setFillColor(PANEL_BG);
    panel.setOutlineColor(GRID_LINE);
    panel.setOutlineThickness(1);
    window.draw(panel);

    drawText(RU_KORABL, px + 15, P_BY + 15, 20, TEXT, false);
    drawText(std::to_string(size) + RU_PALUB, px + 15, P_BY + 42, 22, TEXT_GOLD, false);
    drawText(RU_NAPR, px + 15, P_BY + 80, 16, TEXT, false);
    drawText(placingHorizontal ? RU_GORIZ : RU_VERT, px + 15, P_BY + 100, 16, sf::Color(100, 200, 255), false);

    if (valid) drawText(RU_OK, px + 15, P_BY + 135, 16, sf::Color(50, 200, 80), false);
    else       drawText(RU_BAD, px + 15, P_BY + 135, 16, sf::Color(255, 80, 80), false);

    drawText(RU_STRELKI, px + 15, P_BY + 180, 14, sf::Color(150, 150, 170), false);
    drawText(RU_PROBEL,  px + 15, P_BY + 198, 14, sf::Color(150, 150, 170), false);
    drawText(RU_ENT,     px + 15, P_BY + 216, 14, sf::Color(150, 150, 170), false);
    drawText(RU_ESC,     px + 15, P_BY + 234, 14, sf::Color(150, 150, 170), false);

    drawText(std::to_string(currentShipIdx) + " / " + std::to_string(FLEET_COUNT),
             px + 15, P_BY + 270, 20, TEXT_GOLD, false);
    drawText(RU_OST, px + 15, P_BY + 300, 15, sf::Color(150, 150, 170), false);

    int yPos = P_BY + 325, counts[5] = {0,0,0,0,0};
    for (int i = currentShipIdx; i < FLEET_COUNT; i++) { int s = FLEET_SIZES[i]; if (s >= 1 && s <= 4) counts[4-s]++; }
    for (int deck = 4; deck >= 1; deck--) {
        int cnt = counts[4 - deck];
        if (cnt > 0) {
            std::string line = std::to_string(cnt) + " x " + std::string(deck, '=') + " (" + std::to_string(deck) + "p)";
            drawText(line, px + 15, yPos, 14, sf::Color(100, 180, 255), false);
            yPos += 18;
        }
    }
}

void Game::renderBattle() {
    drawDecorations();
    drawText(RU_BOY, WINDOW_WIDTH / 2, 12, 24, TEXT_GOLD, true);

    drawText(RU_VASHE, P_BX + BOARD_PIXELS / 2 + 20, 50, 17, sf::Color(100, 255, 150), true);
    drawText(RU_POLE_V, E_BX + BOARD_PIXELS / 2 + 20, 50, 17, sf::Color(255, 120, 100), true);

    playerBoard->draw(window, font, -1, -1, true, 0, true, true);
    enemyBoard->draw(window, font, cursorR, cursorC, false, 0, true, true);

    drawInfoPanel();

    // Battle messages
    if (!messages.empty()) {
        float msgY = 540;
        for (auto& m : messages) {
            float alpha = std::min(1.0f, m.timer);
            sf::Color c = m.color;
            c.a = (sf::Uint8)(255 * alpha);
            drawText(m.text, WINDOW_WIDTH / 2, msgY, 20, c, true);
            msgY -= 26;
        }
    }

    // Explosions
    if (spritesLoaded) {
        for (auto& e : explosions) {
            float alpha = e.timer / 0.6f;
            sf::Sprite exp = sprExplosion;
            exp.setPosition(e.x - 30 * e.scale, e.y - 30 * e.scale);
            exp.setScale(e.scale, e.scale);
            exp.setColor(sf::Color(255, 255, 255, (sf::Uint8)(255 * alpha)));
            window.draw(exp);
        }
    }
}

void Game::renderBotTurn() {
    renderBattle();
    sf::RectangleShape overlay(sf::Vector2f(BOARD_PIXELS + 40, BOARD_PIXELS + 40));
    overlay.setPosition(E_BX + 8, E_BY + 8);
    overlay.setFillColor(sf::Color(0, 0, 0, 60));
    window.draw(overlay);

    drawText(RU_BOT_DUM, E_BX + BOARD_PIXELS / 2 + 20, E_BY + BOARD_PIXELS / 2 - 15, 32,
             sf::Color(255, 200, 50), true);
    int dots = (int)(botTimer * 3) % 4;
    drawText(std::string(dots, '.'), E_BX + BOARD_PIXELS / 2 + 20,
             E_BY + BOARD_PIXELS / 2 + 20, 28, sf::Color(255, 200, 50), true);
}

void Game::renderVictory() {
    sf::RectangleShape overlay(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    overlay.setFillColor(sf::Color(0, 20, 0, 200));
    window.draw(overlay);

    if (spritesLoaded) {
        sf::Sprite t = sprTreasure;
        t.setPosition(WINDOW_WIDTH / 2 - 60, 80);
        t.setScale(0.8f, 0.8f);
        window.draw(t);
    }

    drawText(RU_WIN, WINDOW_WIDTH / 2, 240, 56, sf::Color(50, 255, 100), true);
    drawText(RU_WIN2, WINDOW_WIDTH / 2, 320, 24, TEXT, true);

    for (int i = 0; i < 8; i++) {
        float px = 200 + rand() % 800;
        float py = 100 + rand() % 500;
        sf::CircleShape particle(3);
        particle.setPosition(px + sin(animTimer + i) * 20, py + cos(animTimer * 0.7f + i) * 15);
        particle.setFillColor(sf::Color(255, 215, 0, 120 + (int)(sin(animTimer * 2 + i) * 60)));
        window.draw(particle);
    }

    drawText(RU_MENU2, WINDOW_WIDTH / 2, 450, 20, TEXT_GOLD, true);
}

void Game::renderDefeat() {
    sf::RectangleShape overlay(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    overlay.setFillColor(sf::Color(20, 0, 0, 200));
    window.draw(overlay);

    if (spritesLoaded) {
        sf::Sprite s = sprSkeleton;
        s.setPosition(WINDOW_WIDTH / 2 - 80, 60);
        s.setScale(0.7f, 0.7f);
        window.draw(s);
    }

    drawText(RU_LOSE, WINDOW_WIDTH / 2, 280, 56, sf::Color(255, 50, 50), true);
    drawText(RU_LOSE2, WINDOW_WIDTH / 2, 360, 24, TEXT, true);
    drawText(RU_MENU2, WINDOW_WIDTH / 2, 480, 20, TEXT_GOLD, true);
}
