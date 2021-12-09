#pragma once
#include <string>
#include <chrono>
#include <iostream>
#include <vector>
#include <thread>
#include <set>
#include <stack>
#include <unordered_set>
#include <SFML/Graphics.hpp>
#include "maze.h"

class MazeAnalysis
{
    maze* analysisMaze;
    string AnalysisIntro;

    // All of the text being displayed on the right
    sf::Text visited;
    sf::Text numVisited;
    sf::Text text;
    sf::Font font;
    sf::Text Select;
    sf::Text BFSButton;
    sf::Text DFSButton;
    sf::Text backToMenuButton;
    sf::Text startButton;
    sf::Text restartButton;
    sf::Text selectSpeed;
    sf::Text slow;
    sf::Text normal;
    sf::Text fast;
    sf::Text hyperSpeed;

    // stores which algorithm has been selected
    int choice;

    // vector to store all the squares the algorithms have visited in order to display them
    vector<int> pathSquares;

    //Index to be used to iterate through pathSquares and display it
    int index;

    // vector to store locations from which to find the shortest path.
    vector<int> pathFromTo;

    // vector to store squares currently marking path
    vector<int> blues;

    // bool variable to take care of not marking a blue square when Maze Analysis is pressed on the Home Screen 
    bool gameJustStarted;

    // bool variable to check whether the start button has been pressed
    bool startGame;

    // clock variable to make red path show for a given amount of time;
    steady_clock::time_point start;

    // The speed at which the path should be shown
    nanoseconds time;

    // Handles all of the text on the right by setting all of their positions, colors, etc.
    void textHandler();

    // BFS and DFS algorithms
    bool BFS(int src, int dest, int v, map <int, int >& pred, map <int, int>& dist, sf::RenderWindow& window);
    bool DFS(int source, int destination, int numVertices, map <int, int >& predecessor, map <int, int>& distance, sf::RenderWindow& window);

    // Defines the shortest path after BFS or DFS completes
    void ShortestDistance(int s, int dest, int v, int choice, sf::RenderWindow& window);

    // clears the board when restart is pressed
    void restart();

    // clears the board and initializes a new one when the back to menu is pressed
    void reset();
public:
    // tracks the mouse clicks and calls respective functions based off of what was pressed
    void trackMouseClicks(sf::Event& event, sf::RenderWindow& window, string& MODE);
    // Default constructor
    MazeAnalysis();

    // Draws the maze analysis with the maze and the text on the right
    void DrawBoard(sf::RenderWindow& window);
};

