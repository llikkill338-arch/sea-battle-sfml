// ============================================================================
// Game.hpp - Главный игровой класс
// ============================================================================

#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include "Board.hpp"

enum class GameState {
    Menu,
    Settings,
    Rules,
    Placement,
    Battle,
    BotTurn,
    Victory,
    Defeat,
    Exit
};

class Game {
public:
    Game();
    ~Game();
    
    void run();

private:
    sf::RenderWindow window;
    sf::Font font;
    sf::Font fontBold;
    
    GameState state;
    GameState prevState;
    
    std::unique_ptr<Board> playerBoard;
    std::unique_ptr<Board> enemyBoard;
    
    int cursorR, cursorC;
    
    int currentShipIdx;
    bool placingHorizontal;
    
    int botLevel;
    bool botThinking;
    float botTimer;
    
    bool soundEnabled;
    bool autoPlace;
    bool fullscreen;
    
    float animTimer;
    int menuSelection;
    int settingsSelection;
    
    sf::SoundBuffer hitBuffer;
    sf::SoundBuffer missBuffer;
    sf::Sound sound;
    
    void loadResources();
    void handleEvents();
    void update(float dt);
    void render();
    
    void applyFullscreen();
    
    void renderMenu();
    void renderSettings();
    void renderRules();
    void renderPlacement();
    void renderBattle();
    void renderBotTurn();
    void renderVictory();
    void renderDefeat();
    
    void startPlacement();
    void startBattle();
    void botMakeMove();
    void resetGame();
    
    void drawText(const std::string& text, float x, float y, int size,
                  sf::Color color, bool center = false);
    void drawButton(const std::string& text, float x, float y, float w, float h,
                    bool hovered, bool selected);
    bool isMouseOver(float x, float y, float w, float h) const;
    void playHitSound();
    void playMissSound();
};
