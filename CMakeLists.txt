cmake_minimum_required(VERSION 3.16)
project(Friendorithm)

set(CMAKE_CXX_STANDARD 17)

set(SFML_DIR "/opt/homebrew/opt/sfml@2/lib/cmake/SFML")

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

include_directories(FriendAlgorithm/include)

add_executable(Friendorithm
        FriendAlgorithm/src/main.cpp
        FriendAlgorithm/src/graph.cpp
        FriendAlgorithm/src/bfs.cpp
        FriendAlgorithm/src/dijkstra.cpp
        FriendAlgorithm/src/dataset.cpp
        FriendAlgorithm/src/user.cpp
        FriendAlgorithm/src/UI.cpp
)

target_link_libraries(Friendorithm sfml-graphics sfml-window sfml-system)

#cmake_minimum_required(VERSION 4.1)
#project(Friendorithm)
#
#set(CMAKE_CXX_STANDARD 14)
#
#include_directories(FriendAlgorithm/include)
#
#add_executable(Friendorithm
#        FriendAlgorithm/include/bfs.h
#        FriendAlgorithm/include/dataset.h
#        FriendAlgorithm/include/dijkstra.h
#        FriendAlgorithm/include/graph.h
#        FriendAlgorithm/include/user.h
#        FriendAlgorithm/src/bfs.cpp
#        FriendAlgorithm/src/dataset.cpp
#        FriendAlgorithm/src/dijkstra.cpp
#        FriendAlgorithm/src/graph.cpp
#        FriendAlgorithm/src/main.cpp
#        FriendAlgorithm/src/user.cpp
#        FriendAlgorithm/include/UI.h
#        FriendAlgorithm/src/UI.cpp)
