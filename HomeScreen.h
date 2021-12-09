#include <SFML/Graphics.hpp>
#include <chrono>
#include <vector>
#include "square.h"
#include "maze.h"


#ifndef PROJECT_3_FINAL_HOMESCREEN_H
#define PROJECT_3_FINAL_HOMESCREEN_H

using namespace std;
using namespace std::chrono;

class HomeScreen{
    int screenWidth, screenLength;

    // Text objects
    sf::Font font;
    sf::Text titleText;
    sf::Text GameModeText;
    sf::Text MazeAnalysisText;

    // Chrono object
    steady_clock::time_point start;

    // Vector of squares to draw alternating squares
    vector<square> squares;

    // Helper functions
    void alternateSquares();
    void initializeSquares();
    void setText();
public:
    HomeScreen(int screenWidth, int ScreenLength);
    void drawScreen(sf::RenderWindow &window);
    void trackMouseClicks(sf::Event &event, sf::RenderWindow &window, string& MODE);
};


#endif //PROJECT_3_FINAL_HOMESCREEN_H
