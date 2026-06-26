// ============================================================================
// Game.hpp - Главный игровой класс (v4.0 Pirate Edition)
// ============================================================================

#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <string>
#include "Board.hpp"

enum class GameState { Menu, Settings, Rules, Placement, Battle, BotTurn, Victory, Defeat, Exit };

struct BattleMessage {
    std::string text;
    float timer;
    sf::Color color;
};

struct ExplosionEffect {
    float x, y;
    float timer;
    float scale;
};

class Game {
public:
    Game();
    ~Game();
    void run();

private:
    sf::RenderWindow window;
    sf::Font font;

    GameState state;
    std::unique_ptr<Board> playerBoard;
    std::unique_ptr<Board> enemyBoard;

    int cursorR, cursorC, currentShipIdx;
    bool placingHorizontal;
    int botLevel;
    bool botThinking;
    float botTimer;
    bool soundEnabled, autoPlace, fullscreen, playerTurnFirst;
    float animTimer;
    int menuSelection, settingsSelection;

    // Bot AI
    std::vector<std::pair<int,int>> botTargets;
    int botDirIndex;
    bool botHunting;

    // Pirate sprites
    sf::Texture texFrigate, texSkeleton, texTreasure, texPalms, texExplosion;
    sf::Sprite sprFrigate, sprSkeleton, sprTreasure, sprPalms, sprExplosion;
    bool spritesLoaded;

    // Effects
    std::vector<BattleMessage> messages;
    std::vector<ExplosionEffect> explosions;
    float messageTimer;
    std::string lastMessage;

    void loadResources();
    bool loadTexture(sf::Texture& tex, const std::string& path);
    void handleEvents();
    void update(float dt);
    void render();
    void applyFullscreen();

    // Render screens
    void renderMenu();
    void renderSettings();
    void renderRules();
    void renderPlacement();
    void renderBattle();
    void renderBotTurn();
    void renderVictory();
    void renderDefeat();

    // Game logic
    void startPlacement();
    void startBattle();
    void botMakeMove();
    void resetGame();
    void addMessage(const std::string& text, sf::Color color);
    void addExplosion(float x, float y);

    // Drawing helpers
    void drawText(const std::string& text, float x, float y, int size, sf::Color color, bool center);
    void drawButton(const std::string& text, float x, float y, float w, float h, bool hovered, bool selected);
    void drawDecorations();
    void drawInfoPanel();
    sf::String toUtf8(const std::string& text) const;

    // Pirate phrases
    std::string getRandomHitPhrase() const;
    std::string getRandomMissPhrase() const;
    std::string getRandomSunkPhrase() const;
    std::string getRandomBotHitPhrase() const;
};
