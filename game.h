#pragma once
#include "maze.h"
#include "TextureManager.h"
#include "Random.h"
#include <thread>

#ifndef PROJECT_3_FINAL_GAME_H
#define PROJECT_3_FINAL_GAME_H


class Game {
    int startSquare;
    int destSquare;    //sqaure number of the destination
    int playerSquare;  //square number of the green square that the player will control
    string gameIntro;
    string hintText;
    int secondsLeft;
    int currtime;
    int remainingHints;
    bool showingPath;

    int windowWidth;
    int windowLength;

    bool startGame;

    //game board object that will be worked with
    maze* gameBoard;

    //for hints
    vector<int> blues;

    //clock time point 
    chrono::steady_clock::time_point startTime;
    chrono::steady_clock::time_point elapsedTime;
    chrono::steady_clock::time_point start;
    chrono::steady_clock::time_point startText;

    //texts to be used
    sf::Text time;
    sf::Text text;
    sf::Text hint;
    sf::Font font;
    sf::Text startButton;
    sf::Text restartButton;
    sf::Text backToMenuButton;
    void textHandler();
    //for player and destination drawing/moving
    void DrawPlayer(sf::RenderWindow& window);
    void DrawDestination(sf::RenderWindow& window);
    void movePlayer(sf::RenderWindow& window, string direction);
    void assignStartAndEnd();
    //restart button
    void reset();
    //for the hints
    void ShowHint(sf::RenderWindow& window);
    bool BFS(int source, int destination, int numVertices, map <int, int >& predecessor, map <int, int>& distance);
    void ShortestDistance(int sourceSquare, int destinationSquare, int numVertices);

public:
    //constructor that takes int the complete board
    Game(int windowWidth, int windowLength);
    void DrawGame(sf::RenderWindow& window);
    //for mouse/keyboard interaction
    void trackMouseClicks(sf::Event& event, sf::RenderWindow& window, string& MODE);
    void trackKeyBoard(sf::Event& event, sf::RenderWindow& window);
};


#endif //PROJECT_3_FINAL_GAME_H
