# Friendorithm

A graph-based friend recommendation system that simulates a social network of 100,000 users. It compares BFS and Dijkstra’s algorithm to generate and evaluate friend suggestions, giving insight into how each approach performs at scale.

## Requirements
- C++17 or newer
- SFML 2.5 or newer
- CMake 3.x or newer

## Installing SFML

**Mac (Homebrew):**

    brew install sfml

**Windows:**
Download from https://www.sfml-dev.org/download.php and follow the setup instructions for your IDE.

## Building the Project

    mkdir build
    cd build
    cmake ..
    make

## Running the Program

    ./Friendorithm

## How to Use
1. Enter a User ID between 1 and 100,000 in the input box
2. Click **Generate Recommendations**
3. View the top 5 friend recommendations from both BFS and Dijkstra side by side
4. Click **Analysis** to view runtime and performance comparison between the two algorithms
5. Click **Back** to return to the previous screen

## Team
- Cindy Wang - cindywang290
- Sofia Galindo - sofiagalindo5
- Andrew Solomon - AndrewSolomon1
