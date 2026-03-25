#include "UI.h"
#include "bfs.h"
#include "dijkstra.h"
#include <SFML/Graphics.hpp>
#include <chrono>
#include <cctype>
#include <iostream>
using namespace std;

UI::UI(Graph& g, const vector<User>& u) : graph(g), users(u),
      window(sf::VideoMode(800, 600),
      "Friend Recommendations") {

    // font (roboto)
    if (!font.loadFromFile("../FriendAlgorithm/Roboto.ttf")) {
        cout << "Error loading font\n";
    }

///////////////////////////////////////SCREEN 1//////////////////////////////////////////////////////////
    // "Friendorithm" title
    titleText.setFont(font);
    titleText.setCharacterSize(30);

    titleText.setPosition(310, 100);
    titleText.setFillColor(sf::Color::Black);

    subtitleText.setFont(font);
    subtitleText.setString("Graph based friend recommendation system");
    subtitleText.setCharacterSize(16);
    subtitleText.setFillColor(sf::Color(100, 110, 130));
    subtitleText.setPosition(245, 150);

    // user input text
    inputText.setFont(font);
    inputText.setCharacterSize(20);
    inputText.setPosition(270, 263);
    inputText.setFillColor(sf::Color::Black);

    // "User ID" - user input label
    inputLabel.setFont(font);
    inputLabel.setString("User ID");
    inputLabel.setCharacterSize(18);
    inputLabel.setPosition(260, 265);
    inputLabel.setFillColor(sf::Color(120, 120, 120));

    // user input box
    inputBox.setPosition(240, 250);
    inputBox.setSize(sf::Vector2f(320, 50));
    inputBox.setFillColor(sf::Color::White);
    inputBox.setOutlineThickness(2);
    inputBox.setOutlineColor(sf::Color(200, 200, 200));

    // background input card
    inputCard.setSize(sf::Vector2f(400, 200));
    inputCard.setPosition(200, 200);
    inputCard.setFillColor(sf::Color::White);
    inputCard.setOutlineThickness(1);
    inputCard.setOutlineColor(sf::Color(200, 210, 220));

    // "Generate" button
    button.setSize(sf::Vector2f(280, 45));
    button.setPosition(260, 320);
    button.setFillColor(sf::Color(20, 30, 50));

    // "Generate" button text
    buttonText.setFont(font);
    buttonText.setString("Generate Recommendations");
    buttonText.setCharacterSize(18);
    buttonText.setPosition(289, 332);
    buttonText.setFillColor(sf::Color::White);

    // dataset card
    datasetCard.setSize(sf::Vector2f(195, 70));
    datasetCard.setPosition(310, 450);
    datasetCard.setFillColor(sf::Color::White);
    datasetCard.setOutlineThickness(1);
    datasetCard.setOutlineColor(sf::Color(200, 210, 220));

    // "Dataset" subtitle
    datasetTitle.setFont(font);
    datasetTitle.setString("Dataset");
    datasetTitle.setFillColor(sf::Color::Black);
    datasetTitle.setCharacterSize(16);
    datasetTitle.setPosition(378, 462);

    // dataset text
    datasetInfo.setFont(font);
    datasetInfo.setString("100,000 users");
    datasetInfo.setCharacterSize(14);
    datasetInfo.setFillColor(sf::Color(100, 110, 130));
    datasetInfo.setPosition(362, 490);


///////////////////////////////////////SCREEN 2//////////////////////////////////////////////////////////
    // results background card
    resultsCard.setSize(sf::Vector2f(700, 500));
    resultsCard.setPosition(50, 80);
    resultsCard.setFillColor(sf::Color::White);
    resultsCard.setOutlineThickness(1);
    resultsCard.setOutlineColor(sf::Color(200, 210, 220));

    // "BFS Recommendations" subtitle
    bfsTitle.setString("Breadth-First Search (BFS)");
    bfsTitle.setFont(font);
    bfsTitle.setCharacterSize(15);
    bfsTitle.setStyle(sf::Text::Bold);
    bfsTitle.setPosition(125, 98);
    bfsTitle.setFillColor(sf::Color::Black);
    // BFS list of recommendations
    bfsList.setFont(font);
    bfsList.setCharacterSize(13);
    bfsList.setPosition(105, 125);
    bfsList.setFillColor(sf::Color::Black);

    // "Dijkstra Recommendations" subtitle
    dijTitle.setString("Dijkstra");
    dijTitle.setFont(font);
    dijTitle.setCharacterSize(15);
    dijTitle.setStyle(sf::Text::Bold);
    dijTitle.setPosition(530, 98);
    dijTitle.setFillColor(sf::Color(30, 30, 30));
    // Dijkstra list of recommendations
    dijList.setFont(font);
    dijList.setCharacterSize(13);
    dijList.setPosition(450, 125);
    dijList.setFillColor(sf::Color::Black);

    // Analysis Button (green)
    analysisButton.setSize(sf::Vector2f(75, 30));
    analysisButton.setPosition(710, 20);
    analysisButton.setFillColor(sf::Color(9, 121, 105));
    // analysis button text
    analysisButtonText.setFont(font);
    analysisButtonText.setString("Analysis");
    analysisButtonText.setCharacterSize(16);
    analysisButtonText.setPosition(717, 25);

    // Back Button (red)
    resultsBackButton.setSize(sf::Vector2f(75, 30));
    resultsBackButton.setPosition(20, 20);
    resultsBackButton.setFillColor(sf::Color(155,10,10));
    // back button text
    resultsBackButtonText.setFont(font);
    resultsBackButtonText.setString("Back");
    resultsBackButtonText.setCharacterSize(16);
    resultsBackButtonText.setPosition(39, 25);



///////////////////////////////////////SCREEN 3//////////////////////////////////////////////////////////
    // Performance Comparison background card
    perfCard.setSize(sf::Vector2f(700, 220));
    perfCard.setPosition(50, 65);
    perfCard.setFillColor(sf::Color::White);
    perfCard.setOutlineThickness(1);
    perfCard.setOutlineColor(sf::Color(200, 210, 220));

    // "Performance Comparison" subtitle
    perfTitle.setFont(font);
    perfTitle.setString("Performance Comparison");
    perfTitle.setCharacterSize(22);
    perfTitle.setFillColor(sf::Color(30,30,30));
    perfTitle.setPosition(70, 76);

    // purple BFS box
    bfsBox.setSize(sf::Vector2f(300, 90));
    bfsBox.setPosition(420, 116);
    bfsBox.setFillColor(sf::Color(235, 245, 255));
    // blue Dijkstra box
    dijkstraBox.setSize(sf::Vector2f(300, 90));
    dijkstraBox.setPosition(80, 116);
    dijkstraBox.setFillColor(sf::Color(245, 240, 255));
    // green result box
    resultBox.setSize(sf::Vector2f(640, 50));
    resultBox.setPosition(80, 219);
    resultBox.setFillColor(sf::Color(220, 255, 220));

    // Analysis background card
    analysisCard.setSize(sf::Vector2f(700, 260));
    analysisCard.setPosition(50, 300);
    analysisCard.setFillColor(sf::Color::White);
    analysisCard.setOutlineThickness(1);
    analysisCard.setOutlineColor(sf::Color(200, 210, 220));

    // "Analysis" subtitle
    analysisTitle.setFont(font);
    analysisTitle.setString("Analysis");
    analysisTitle.setCharacterSize(22);
    analysisTitle.setFillColor(sf::Color(30,30,30));
    analysisTitle.setPosition(70, 315);

    // Back Button (red)
    backButton.setSize(sf::Vector2f(75, 30));
    backButton.setPosition(20, 20);
    backButton.setFillColor(sf::Color(155,10,10));
    // back button text
    backButtonText.setFont(font);
    backButtonText.setString("Back");
    backButtonText.setCharacterSize(16);
    backButtonText.setPosition(39, 25);

}
// runs program
void UI::run() {
    while (window.isOpen()) {
        handleEvents();
        update();
        render();
    }
}

// user input/interactions
void UI::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
    // IF USER ❌ OUT OF TAB ---------------------------------------------------------------
        if (event.type == sf::Event::Closed) window.close();

    // IF USER IS TYPING --------------------------------------------------------------------
        if (event.type == sf::Event::TextEntered && isTyping) {
            if (isdigit(event.text.unicode)) // user types a number
                userInput += static_cast<char>(event.text.unicode);
            else if (event.text.unicode == 8 && !userInput.empty()) // user clicks backspace
                userInput.pop_back();
        }

    // IF USER CLICKS SCREEN -------------------------------------------------------------------------------
        if (event.type == sf::Event::MouseButtonPressed) {
            int x = event.mouseButton.x;
            int y = event.mouseButton.y;

        // Screen 1 ..............................................................................
            // input box
            if (currentScreen == INPUT)
                isTyping = inputBox.getGlobalBounds().contains(x, y);

            // Generate button
            if (currentScreen == INPUT && button.getGlobalBounds().contains(x, y)){
                runAlgorithms();
                currentScreen = RESULTS;
                return;
            }

        // Screen 2 ..............................................................................
            // Back button (red)
            if (currentScreen == RESULTS && resultsBackButton.getGlobalBounds().contains(x, y)) {
                currentScreen = INPUT;
                userInput = "";
                isTyping = true;
                return;
            }
            // Analysis button (green)
            if (currentScreen == RESULTS && analysisButton.getGlobalBounds().contains(x, y)) {
                currentScreen = ANALYSIS;
                return;
            }

        // Screen 3 ..............................................................................
            // Back button (red)
            if (currentScreen == ANALYSIS && backButton.getGlobalBounds().contains(x, y)) {
                currentScreen = RESULTS;
                return;
            }
        }
    }
}




/// RUNS ALGORITHMS when user clicks “Generate” button//////////////////////////////////////////
void UI::runAlgorithms() {
    // empty user input
    if (userInput.empty()) return;

    // invalid user id input
    int userId = stoi(userInput);
    if (userId <= 0 || userId > graph.getNumUsers()) return;

    // nodes visited
    int bfsVisited = 0, dijVisited = 0;

    // runs BFS and measures time
    auto BStart = chrono::high_resolution_clock::now();
    auto bfs = bfsRecommend(graph, userId, 2, 5, bfsVisited);
    auto BEnd = chrono::high_resolution_clock::now();
    // runs Dijkstra and measures time
    auto DStart = chrono::high_resolution_clock::now();
    auto dij = getDijkstraRecommendations(graph, userId, 5, dijVisited);
    auto DEnd = chrono::high_resolution_clock::now();

    // converts time to seconds
    double bfsTime = chrono::duration<double>(BEnd - BStart).count();
    double dijTime = chrono::duration<double>(DEnd - DStart).count();


// Screen 2 Output.......................................................................
    // BFS recommendations output
    string bfsOut;
    for (int i = 0; i < bfs.size(); i++) {
        User u = users[bfs[i] - 1];
        bfsOut += to_string(i + 1) + ". ID: " + to_string(u.user_id) + "\n";
        bfsOut += "    Age: " + to_string(u.age) + "\n";
        bfsOut += "    School: " + u.school + "\n";
        bfsOut += "    Major: " + u.major + "\n";
        bfsOut += "    Industry: " + u.industry + "\n\n";
    }
    bfsList.setString(bfsOut);

    // Dijkstra recommendations output
    string dijOut;
    for (int i = 0; i < dij.size(); i++) {
        User u = users[dij[i] - 1];
        dijOut += to_string(i + 1) + ". ID: " + to_string(u.user_id) + "\n";
        dijOut += "    Age: " + to_string(u.age) + "\n";
        dijOut += "    School: " + u.school + "\n";
        dijOut += "    Major: " + u.major + "\n";
        dijOut += "    Industry: " + u.industry + "\n\n";
    }
    dijList.setString(dijOut);


// Screen 3 Output.......................................................................
    // PERFORMANCE ------------------------------------------------------
    // dijkstra performance text (blue)
    dijPerfTest.setFont(font);
    dijPerfTest.setCharacterSize(16);
    dijPerfTest.setPosition(440, 128);
    dijPerfTest.setString("Dijkstra \n"
                              "Nodes Visited: " + to_string(dijVisited) +
                              "\nRuntime: " + to_string(dijTime));
    dijPerfTest.setFillColor(sf::Color(40, 40, 100));

    // bfs performance text (purple)
    bfsPerfText.setFont(font);
    bfsPerfText.setCharacterSize(16);
    bfsPerfText.setPosition(100, 128);
    bfsPerfText.setString("BFS \n"
                             "Nodes Visited: " + to_string(bfsVisited) +
                             "\nRuntime: " + to_string(bfsTime));
    bfsPerfText.setFillColor(sf::Color(100, 40, 100));

    // results text (green)
    resultText.setFont(font);
    resultText.setCharacterSize(16);
    resultText.setPosition(100, 235);
    resultText.setString("The BFS graph traversal algorithm is faster by ~" +
                                        to_string(dijTime / bfsTime) + "x");
    resultText.setFillColor(sf::Color(20, 100, 40));


    // ANALYSIS ------------------------------------------------------
        // BFS analysis text
    bfsAnalysisText.setFont(font);
    bfsAnalysisText.setCharacterSize(16);
    bfsAnalysisText.setFillColor(sf::Color(40, 40, 40));
    bfsAnalysisText.setPosition(80, 360);
    bfsAnalysisText.setString(
    "BFS (Breadth First Search)\n"
        "BFS runs in O(V + E) and focuses on local connections. It only explores \n"
        "nodes within a few degrees of separation from the target user, making it \n"
        "ideal for finding nearby friends in the social graph.\n"
    );
        // Dijkstra analysis text
    dijkstraAnalysisText.setFont(font);
    dijkstraAnalysisText.setCharacterSize(16);
    dijkstraAnalysisText.setFillColor(sf::Color(40, 40, 40));
    dijkstraAnalysisText.setPosition(80, 440);
    dijkstraAnalysisText.setString(
        "\nDijkstra's Algorithm\n"
        "Dijkstra runs in O((V + E) log V) and explores the full graph. It \n"
        "calculates shortest paths to all reachable nodes, providing more thorough \n"
        "results but at a higher computational cost."
    );
}



/// SCREEN DISPLAY /////////////////////////////////////////////////////////////////////////////
void UI::render() {
    window.clear(sf::Color(245, 247, 250));
    if (currentScreen == INPUT) renderInput();
    else if (currentScreen == RESULTS) renderResults();
    else if (currentScreen == ANALYSIS) renderAnalysis();
    window.display();
}

// Displays Screen 1
void UI::renderInput() {
    titleText.setString("Friendorithm");
    titleText.setPosition(320, 100);

    window.draw(titleText);
    window.draw(subtitleText);
    window.draw(inputCard);
    window.draw(inputBox);
    window.draw(inputLabel);
    window.draw(inputText);
    window.draw(button);
    window.draw(buttonText);
    window.draw(datasetCard);
    window.draw(datasetTitle);
    window.draw(datasetInfo);
}

// Displays Screen 2
void UI::renderResults() {
    titleText.setString("Recommendations for User " + userInput);
    float w = titleText.getLocalBounds().width;
    titleText.setPosition((800-w)/2, 30);

    window.draw(titleText);
    window.draw(resultsCard);
    window.draw(bfsTitle);
    window.draw(dijTitle);
    window.draw(bfsList);
    window.draw(dijList);
    window.draw(analysisButton);
    window.draw(analysisButtonText);
    window.draw(resultsBackButton);
    window.draw(resultsBackButtonText);
}

// Displays Screen 3
void UI::renderAnalysis() {
    titleText.setString("Performance Analysis");
    float w = titleText.getLocalBounds().width;
    titleText.setPosition((800 - w) / 2, 80);

    window.draw(titleText);
    window.draw(perfCard);
    window.draw(perfTitle);
    window.draw(dijkstraBox);
    window.draw(bfsBox);
    window.draw(dijPerfTest);
    window.draw(bfsPerfText);
    window.draw(resultBox);
    window.draw(resultText);
    window.draw(analysisCard);
    window.draw(analysisTitle);
    window.draw(bfsAnalysisText);
    window.draw(dijkstraAnalysisText);
    window.draw(backButton);
    window.draw(backButtonText);
}

// updates screen
void UI::update() {
    if (cursorClock.getElapsedTime().asSeconds() > 0.5f) {
        showCursor = !showCursor;
        cursorClock.restart();
    }
    if (isTyping || !userInput.empty()) {
        inputLabel.setCharacterSize(14);
        inputLabel.setPosition(260, 225);
    } else {
        inputLabel.setCharacterSize(18);
        inputLabel.setPosition(260, 265);
    }
    string displayText = userInput;
    if (isTyping && showCursor) {
        displayText += "|";
    }
    inputText.setString(displayText);
}