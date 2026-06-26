// ============================================================================
// Game.hpp - v5.0 Pixel-Art + Sound Edition (No PNGs, all code-drawn)
// ============================================================================

#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include <vector>
#include <string>
#include "Board.hpp"

enum class GameState {
    Menu, Settings, Rules, Placement, Battle, BotTurn, Victory, Defeat, Exit
};

struct BattleMessage {
    std::string text;
    float timer;
    sf::Color color;
};

struct ExplosionParticle {
    float x, y, vx, vy;
    float timer;
    sf::Color color;
    float size;
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

    // Messages & explosions
    std::vector<BattleMessage> messages;
    std::vector<ExplosionParticle> particles;

    // ===== SOUND =====
    sf::SoundBuffer hitBuf, missBuf, sunkBuf, musicBuf;
    sf::Sound hitSound, missSound, sunkSound;
    sf::Music bgMusic;  // use sf::Music for streaming large files
    bool soundsLoaded;

    void loadResources();
    void loadSounds();
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
    void spawnExplosion(float cx, float cy);

    // Drawing helpers
    void drawText(const std::string& text, float x, float y, int size, sf::Color color, bool center);
    void drawButton(const std::string& text, float x, float y, float w, float h, bool hovered, bool selected);
    void drawInfoPanel();
    sf::String toUtf8(const std::string& text) const;

    // ===== PIXEL ART (all drawn with code) =====
    void drawPixelFrigate(float x, float y);
    void drawPixelSkeleton(float x, float y);
    void drawPixelTreasure(float x, float y);
    void drawPixelPalms(float x, float y);
    void drawPixelExplosion(float x, float y, float scale);
    void drawDecorations();
    void drawParticles();

    // Pirate phrases
    std::string getRandomHitPhrase() const;
    std::string getRandomMissPhrase() const;
    std::string getRandomSunkPhrase() const;
    std::string getRandomBotHitPhrase() const;

    void playHitSound();
    void playMissSound();
    void playSunkSound();
};
