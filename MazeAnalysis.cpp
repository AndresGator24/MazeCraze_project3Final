#include "MazeAnalysis.h"
using namespace std;
using namespace std::chrono;

typedef high_resolution_clock Clock;

// Default constructor
MazeAnalysis::MazeAnalysis() {
    string mode = "Maze Analysis";
    analysisMaze = new maze(251, 149, mode, 5);

    AnalysisIntro = "BFS\nV.S\nDFS";

    choice = 1;
    index = 0;

    gameJustStarted = true;

    time = milliseconds(300);

    textHandler();
}

// Draws the maze analysis with the maze and the text on the right
void MazeAnalysis::DrawBoard(sf::RenderWindow& window) {

    //Draws the whole maze on the left
    analysisMaze->DrawMaze(window);

    window.draw(text);
    window.draw(Select);
    window.draw(BFSButton);
    window.draw(DFSButton);
    window.draw(selectSpeed);
    window.draw(slow);
    window.draw(normal);
    window.draw(fast);
    window.draw(hyperSpeed);
    window.draw(visited);
    // Changes the number of Nodes visited displayed
    numVisited.setString(to_string(index));
    window.draw(numVisited);
    window.draw(startButton);
    window.draw(restartButton);
    window.draw(backToMenuButton);

    // When the BFS / DFS path is done being showed, show the shortest path and clear the red squares
    if (index == pathSquares.size() && index != 0) {
        for (int i = 0; i < blues.size(); i++) {
            analysisMaze->squares[blues[i]].blue = true;
        }
        for (int i = 0; i < pathSquares.size(); i++) {
            analysisMaze->squares[pathSquares[i]].red = false;
        }
        pathSquares.clear();
    }

    // Displays the BFS / DFS search at a certain speed according to the time variable
    if (!pathSquares.empty() && (steady_clock::now() - start) > time) {
        analysisMaze->squares[pathSquares[index]].red = true;
        //analysisMaze->squares[pathSquares[index]].blue = false;
        index++;
        start = steady_clock::now();
    }

}
//Handles all the text by setting their font, string, size, color, and position
void MazeAnalysis::textHandler() {
    font.loadFromFile("SFCompact.ttf");

    // "BFS V.S DFS"
    text.setFont(font);
    text.setString(AnalysisIntro);
    text.setCharacterSize(80);
    text.setFillColor(sf::Color::Red);
    text.setPosition(analysisMaze->squares[(6 * analysisMaze->getNumColumns()) - 1].SquarePosition().getPosition().x + 15,
        analysisMaze->squares[(3 * analysisMaze->getNumColumns()) - 1].SquarePosition().getPosition().y);

    //" Select Algorithm"
    Select.setFont(font);
    Select.setString("Select Algorithm");
    Select.setCharacterSize(18);
    Select.setFillColor(sf::Color::Blue);
    Select.setStyle(sf::Text::Underlined);
    Select.setPosition(analysisMaze->squares[(18 * analysisMaze->getNumColumns()) - 1].SquarePosition().getPosition().x + 15,
        analysisMaze->squares[(60 * analysisMaze->getNumColumns()) - 1].SquarePosition().getPosition().y);

    // "BFS"
    BFSButton.setFont(font);
    BFSButton.setString("BFS");
    BFSButton.setCharacterSize(25);
    BFSButton.setFillColor(sf::Color::Green);
    BFSButton.setPosition(analysisMaze->squares[(18 * analysisMaze->getNumColumns()) - 1].SquarePosition().getPosition().x + 15,
        analysisMaze->squares[(65 * analysisMaze->getNumColumns()) - 1].SquarePosition().getPosition().y);

    // "DFS"
    DFSButton.setFont(font);
    DFSButton.setString("DFS");
    DFSButton.setCharacterSize(25);
    DFSButton.setFillColor(sf::Color::Blue);
    DFSButton.setPosition(analysisMaze->squares[(18 * analysisMaze->getNumColumns()) - 1].SquarePosition().getPosition().x + 80,
        analysisMaze->squares[(65 * analysisMaze->getNumColumns()) - 1].SquarePosition().getPosition().y);

    // "Select Speed"
    selectSpeed.setFont(font);
    selectSpeed.setString("Select Speed");
    selectSpeed.setCharacterSize(18);
    selectSpeed.setFillColor(sf::Color::Blue);
    selectSpeed.setPosition(analysisMaze->squares[(18 * analysisMaze->getNumColumns()) - 1].SquarePosition().getPosition().x + 15,
        analysisMaze->squares[(75 * analysisMaze->getNumColumns()) - 1].SquarePosition().getPosition().y);

    // "Slow"
    slow.setFont(font);
    slow.setString("Slow");
    slow.setCharacterSize(16);
    slow.setFillColor(sf::Color::Blue);
    slow.setPosition(analysisMaze->squares[(18 * analysisMaze->getNumColumns()) - 1].SquarePosition().getPosition().x + 15,
        analysisMaze->squares[(80 * analysisMaze->getNumColumns()) - 1].SquarePosition().getPosition().y);

    // "Normal"
    normal.setFont(font);
    normal.setString("Normal");
    normal.setCharacterSize(16);
    normal.setFillColor(sf::Color::Green);
    normal.setPosition(analysisMaze->squares[(18 * analysisMaze->getNumColumns()) - 1].SquarePosition().getPosition().x + 63,
        analysisMaze->squares[(80 * analysisMaze->getNumColumns()) - 1].SquarePosition().getPosition().y);

    // "Fast"
    fast.setFont(font);
    fast.setString("Fast");
    fast.setCharacterSize(16);
    fast.setFillColor(sf::Color::Blue);
    fast.setPosition(analysisMaze->squares[(18 * analysisMaze->getNumColumns()) - 1].SquarePosition().getPosition().x + 130,
        analysisMaze->squares[(80 * analysisMaze->getNumColumns()) - 1].SquarePosition().getPosition().y);

    // "Hyper Speed!"
    hyperSpeed.setFont(font);
    hyperSpeed.setString("Hyper Speed!");
    hyperSpeed.setCharacterSize(16);
    hyperSpeed.setFillColor(sf::Color::Blue);
    hyperSpeed.setPosition(analysisMaze->squares[(18 * analysisMaze->getNumColumns()) - 1].SquarePosition().getPosition().x + 38,
        analysisMaze->squares[(85 * analysisMaze->getNumColumns()) - 1].SquarePosition().getPosition().y);

    // "Nodes Visited: "
    visited.setFont(font);
    visited.setString("Nodes Visited: ");
    visited.setCharacterSize(15);
    visited.setFillColor(sf::Color::Cyan);
    visited.setPosition(analysisMaze->squares[(18 * analysisMaze->getNumColumns()) - 1].SquarePosition().getPosition().x + 15,
        analysisMaze->squares[(95 * analysisMaze->getNumColumns()) - 1].SquarePosition().getPosition().y);

    // Displays nodes visited as path is being displayed
    numVisited.setFont(font);
    numVisited.setString("0");
    numVisited.setCharacterSize(15);
    numVisited.setFillColor(sf::Color::Cyan);
    numVisited.setPosition(analysisMaze->squares[(18 * analysisMaze->getNumColumns()) - 1].SquarePosition().getPosition().x + 130,
        analysisMaze->squares[(95 * analysisMaze->getNumColumns()) - 1].SquarePosition().getPosition().y);

    // "START"
    startButton.setFont(font);
    startButton.setString("START");
    startButton.setCharacterSize(35);
    startButton.setFillColor(sf::Color::White);
    startButton.setPosition(analysisMaze->squares[(25 * analysisMaze->getNumColumns()) - 1].SquarePosition().getPosition().x + 15,
        analysisMaze->squares[(110 * analysisMaze->getNumColumns()) - 1].SquarePosition().getPosition().y);

    // "RESTART"
    restartButton.setFont(font);
    restartButton.setString("RESTART");
    restartButton.setCharacterSize(35);
    restartButton.setFillColor(sf::Color::White);
    restartButton.setPosition(analysisMaze->squares[(25 * analysisMaze->getNumColumns()) - 1].SquarePosition().getPosition().x + 15,
        analysisMaze->squares[(120 * analysisMaze->getNumColumns()) - 1].SquarePosition().getPosition().y);

    // "BACK TO MENU"
    backToMenuButton.setFont(font);
    backToMenuButton.setString("BACK TO\n  MENU");
    backToMenuButton.setCharacterSize(35);
    backToMenuButton.setFillColor(sf::Color::Green);
    backToMenuButton.setPosition(analysisMaze->squares[(30 * analysisMaze->getNumColumns()) - 1].SquarePosition().getPosition().x + 15,
        analysisMaze->squares[(130 * analysisMaze->getNumColumns()) - 1].SquarePosition().getPosition().y);
}

// Breadth First Search
bool MazeAnalysis::BFS(int source, int destination, int numVertices, map <int, int >& predecessor, map <int, int>& distance, sf::RenderWindow& window) {

    // Starting a clock to time how long BFS will take
    auto t1 = Clock::now();

    // declare queue
    list<int> queue;

    // use a set to keep track of visited nodes
    unordered_set <int> visited;


    // initialize all distances to max and all predecessors to -1
    for (auto iter = analysisMaze->adjacencyList.begin(); iter != analysisMaze->adjacencyList.end(); iter++) {
        predecessor[(*iter).first] = -1;
        distance[(*iter).first] = INT_MAX;
    }

    // add source to visited, define its distance, and add it to the queue.
    visited.insert(source);
    distance[source] = 0;
    queue.push_back(source);

    // adds the visited squares onto pathSquares in order to later be traversed to show path
    pathSquares.push_back(source);



    while (!queue.empty()) {
        int current = queue.front();
        queue.pop_front();

        for (auto iter = analysisMaze->adjacencyList[current].begin(); iter != analysisMaze->adjacencyList[current].end(); iter++) {

            if (visited.find((*iter).first) == visited.end()) {
                // add on to visited
                visited.insert((*iter).first);
                //update distance and define predecessor
                distance[(*iter).first] = distance[current] + 1;
                predecessor[(*iter).first] = current;
                // add on to queue
                queue.push_back((*iter).first);
                // adds the visited squares onto pathSquares in order to later be traversed to show path
                pathSquares.push_back((*iter).first);


                // if element found return true
                if ((*iter).first == destination) {
                    auto t2 = Clock::now();
                    cout << "Time BFS took: " << duration_cast<nanoseconds>(t2 - t1).count() << endl;

                    cout << "Vertices visited: " << pathSquares.size() << endl;

                    return true;
                }
            }
        }
    }
    auto t2 = Clock::now();
    cout << "Time BFS took: " << duration_cast<nanoseconds>(t2 - t1).count() << endl;

    cout << "Vertices visited: " << pathSquares.size() << endl;

    return false;
}

// Depth First Search
bool MazeAnalysis::DFS(int source, int destination, int numVertices, map <int, int >& predecessor, map <int, int>& distance, sf::RenderWindow& window) {

    // Starting a clock to time how long BFS will take
    auto t1 = Clock::now();

    // declare stack
    stack<int> stack;

    // use a set to keep track of visited nodes for BFS
    unordered_set <int> visited;

    // initialize all distances to max and all predecessors to -1
    for (auto iter = analysisMaze->adjacencyList.begin(); iter != analysisMaze->adjacencyList.end(); iter++) {
        predecessor[(*iter).first] = -1;
        distance[(*iter).first] = INT_MAX;
    }

    // add source to visited, define its distance, and add it to the stack.
    visited.insert(source);
    distance[source] = 0;
    stack.push(source);



    while (!stack.empty()) {
        int current = stack.top();
        stack.pop();
        // adds the visited squares onto pathSquares in order to later be traversed to show path
        pathSquares.push_back(current);

        for (auto iter = analysisMaze->adjacencyList[current].begin(); iter != analysisMaze->adjacencyList[current].end(); iter++) {

            if (visited.find((*iter).first) == visited.end()) {
                // add on to visited
                visited.insert((*iter).first);
                //update distance and define predecessor
                distance[(*iter).first] = distance[current] + 1;
                predecessor[(*iter).first] = current;
                // add on to stack
                stack.push((*iter).first);


                // if element found return true
                if ((*iter).first == destination) {
                    auto t2 = Clock::now();
                    cout << "Time DFS took: " << duration_cast<nanoseconds>(t2 - t1).count() << endl;

                    cout << "Vertices visited: " << pathSquares.size() << endl;

                    return true;
                }
            }
        }
    }
    auto t2 = Clock::now();
    cout << "Time DFS took: " << duration_cast<nanoseconds>(t2 - t1).count() << endl;

    cout << "Vertices visited: " << pathSquares.size() << endl;

    return false;
}

// Defines the shortest path after BFS or DFS completes
void MazeAnalysis::ShortestDistance(int sourceSquare, int destinationSquare, int numVertices, int choice, sf::RenderWindow& window) {

    // define to maps to keep track of path
    map <int, int> predecessor;
    map <int, int> distance;

    if (sourceSquare == destinationSquare) {
        cout << "Same square chosen!" << endl << endl;
        blues.push_back(sourceSquare);
        // change squares that are part of the path
        for (int i = 0; i < blues.size(); i++) {
            analysisMaze->squares[blues[i]].blue = true;
        }
    }
    else {
        bool worked = true;
        // perform bfs/dfs to check if elements are connected and if they are not print message
        if (choice == 1) {
            worked = BFS(sourceSquare, destinationSquare, numVertices, predecessor, distance, window);
        }
        if (choice == 2) {
            worked = DFS(sourceSquare, destinationSquare, numVertices, predecessor, distance, window);
        }
        if (!worked) {
            cout << "Vertices are disconnected" << endl << endl;
            for (int i = 0; i < blues.size(); i++) {
                analysisMaze->squares[blues[i]].blue = true;
            }
        }
        // if vertices are connected show path
        else {


            int current = destinationSquare;

            //until we reach the source node
            while (predecessor[current] != -1) {
                blues.push_back(predecessor[current]);
                current = predecessor[current];
            }


            //print path info
            cout << "The shortest path length is : " << distance[destinationSquare] << endl;

            // printing path from source to destination
            cout << "Vertices covered in path : ";
            for (int i = blues.size() - 1; i >= 0; i--)
                cout << blues[i] << " ";
            cout << endl << endl;
            // change squares that are part of the path
            /*for (int i = 0; i < blues.size(); i++) {
                analysisMaze->squares[blues[i]].blue = true;
            }*/
        }
    }
    //define start to know how long to show path for
    start = high_resolution_clock::now();

}

void MazeAnalysis::trackMouseClicks(sf::Event& event, sf::RenderWindow& window, string& MODE) {


    if (event.mouseButton.button == sf::Mouse::Left) {

        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

            // Iterate through all tiles and check what tile, if any the mouse is over.
            for (int i = 0; i < analysisMaze->squares.size(); i++) {
                auto currentSquare = analysisMaze->squares[i].SquarePosition().getGlobalBounds();
                //If the mouse is over the tile in question and the game is still going
                if ((currentSquare.contains(mousePos.x, mousePos.y)) && analysisMaze->squares[i].white && !analysisMaze->squares[i].blue && blues.size() < 2) {
                    analysisMaze->squares[i].blue = true;
                    pathFromTo.push_back(analysisMaze->squares[i].numSquare);
                    blues.push_back(analysisMaze->squares[i].numSquare);
                }
                if (pathFromTo.size() == 2 && blues.size() <= 2 && startGame) {
                    ShortestDistance(pathFromTo[0], pathFromTo[1], analysisMaze->getNumVertices(), choice, window);
                }
            }


        auto HomeScreenOption = backToMenuButton.getGlobalBounds();
        if ((HomeScreenOption.contains(mousePos.x, mousePos.y))) {
            MODE = "Home Screen";
            reset();
        }

        auto startOption = startButton.getGlobalBounds();
        if ((startOption.contains(mousePos.x, mousePos.y))) {
            startGame = true;
            // When two blue nodes have been chosen and game has been started
            if (pathFromTo.size() == 2  && blues.size() <= 2) {
                ShortestDistance(pathFromTo[0], pathFromTo[1], analysisMaze->getNumVertices(), choice, window);
            }
        }

        auto restartOption = restartButton.getGlobalBounds();
        //If the mouse is over the tile in question and the game is still going
        if ((restartOption.contains(mousePos.x, mousePos.y))) {
            restart();
        }

        auto BFSOption = BFSButton.getGlobalBounds();
        if ((BFSOption.contains(mousePos.x, mousePos.y)) && blues.size() <= 2) {
            choice = 1;
            // Changes BFS or DFS to Green based on which one is chosen
            BFSButton.setFillColor(sf::Color::Green);
            DFSButton.setFillColor(sf::Color::Blue);
        }

        auto DFSOption = DFSButton.getGlobalBounds();
        if ((DFSOption.contains(mousePos.x, mousePos.y)) && blues.size() <= 2) {
            choice = 2;
            // Changes BFS or DFS to Green based on which one is chosen
            BFSButton.setFillColor(sf::Color::Blue);
            DFSButton.setFillColor(sf::Color::Green);
        }

        auto SlowOption = slow.getGlobalBounds();
        if ((SlowOption.contains(mousePos.x, mousePos.y))) {
            // Changes the speed selection to Green based on which one is chosen
            slow.setFillColor(sf::Color::Green);
            normal.setFillColor(sf::Color::Blue);
            fast.setFillColor(sf::Color::Blue);
            hyperSpeed.setFillColor(sf::Color::Blue);

            time = milliseconds(1000);
        }

        auto normalOption = normal.getGlobalBounds();
        if ((normalOption.contains(mousePos.x, mousePos.y))) {
            // Changes the speed selection to Green based on which one is chosen
            slow.setFillColor(sf::Color::Blue);
            normal.setFillColor(sf::Color::Green);
            fast.setFillColor(sf::Color::Blue);
            hyperSpeed.setFillColor(sf::Color::Blue);

            time = milliseconds(300);
        }

        auto fastOption = fast.getGlobalBounds();
        if ((fastOption.contains(mousePos.x, mousePos.y))) {
            // Changes the speed selection to Green based on which one is chosen
            slow.setFillColor(sf::Color::Blue);
            normal.setFillColor(sf::Color::Blue);
            fast.setFillColor(sf::Color::Green);
            hyperSpeed.setFillColor(sf::Color::Blue);

            time = milliseconds(100);
        }
        auto hyperOption = hyperSpeed.getGlobalBounds();
        if ((hyperOption.contains(mousePos.x, mousePos.y))) {
            // Changes the speed selection to Green based on which one is chosen
            slow.setFillColor(sf::Color::Blue);
            normal.setFillColor(sf::Color::Blue);
            fast.setFillColor(sf::Color::Blue);
            hyperSpeed.setFillColor(sf::Color::Green);

            time = nanoseconds(0);
        }
    }
}
// clears the board when restart is pressed
void MazeAnalysis::restart() {
    // Turning all red squares back to normal
    for (int i = 0; i < pathSquares.size(); i++) {
        analysisMaze->squares[pathSquares[i]].red = false;
    }
    // Turning all blue squares back to normal
    for (int i = 0; i < blues.size(); i++) {
        analysisMaze->squares[blues[i]].blue = false;
    }
    for (int i = 0; i < pathFromTo.size(); i++) {
        analysisMaze->squares[pathFromTo[i]].blue = false;
    }
    pathSquares.clear();
    startGame = false;
    pathFromTo.clear();
    pathFromTo.clear();
    blues.clear();
    index = 0;
}

// clears the board and initializes a new one when the back to menu is pressed
void MazeAnalysis::reset() {
    analysisMaze->reset();
    pathSquares.clear();
    startGame = false;
    pathFromTo.clear();
    blues.clear();
    index = 0;
    choice = 1;
    gameJustStarted = true;
    time = milliseconds(300);
    textHandler();
}