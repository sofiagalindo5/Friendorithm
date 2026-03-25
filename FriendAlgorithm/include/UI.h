#ifndef FRIENDORITHM_UI_H
#define FRIENDORITHM_UI_H
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "user.h"
#include "graph.h"
using namespace std;


class UI {
public:
    UI(Graph& g, const std::vector<User>& u);
    void run();

private:
    Graph& graph;
    vector<User> users;
    string userInput;

    // window
    sf::RenderWindow window;
    sf::Font font;

    // screen state
    enum Screen {INPUT, RESULTS, ANALYSIS};
    Screen currentScreen = INPUT;
    bool showAnalysis = false;
    bool isTyping = false;

    // text
    sf::Text titleText;
    sf::Text inputText;
    sf::Text resultText;
    sf::Text bfsList;
    sf::Text dijList;
    sf::Text analysisText;
    sf::Text bfsTitle;
    sf::Text dijTitle;
    sf::Text inputLabel;
    sf::Text buttonText;
    sf::Text analysisButtonText;
    sf::Text backButtonText;
    sf::Text subtitleText;
    sf::Text perfTitle;
    sf::Text dijPerfTest;
    sf::Text bfsPerfText;
    sf::Text analysisTitle;
    sf::Text bfsAnalysisText;
    sf::Text dijkstraAnalysisText;
    sf::RectangleShape datasetCard;
    sf::Text datasetTitle;
    sf::Text datasetInfo;

    // shapes, buttons, components
    sf::RectangleShape button;
    sf::RectangleShape analysisButton;
    sf::RectangleShape backButton;
    sf::RectangleShape inputCard;
    sf::RectangleShape inputBox;
    sf::RectangleShape resultsCard;
    sf::RectangleShape perfCard;
    sf::RectangleShape dijkstraBox;
    sf::RectangleShape bfsBox;
    sf::RectangleShape resultBox;
    sf::RectangleShape analysisCard;
    sf::RectangleShape resultsBackButton;
    sf::Text resultsBackButtonText;
    sf::Clock cursorClock;
    bool showCursor = true;

    void renderInput();
    void renderResults();
    void renderAnalysis();

    int dijkstraNodesVisited;
    double dijkstraTime;

    int bfsNodesVisited;
    double bfsTimeValue;

    // functions
    void handleEvents();
    void update();
    void render();
    void runAlgorithms();
};

#endif