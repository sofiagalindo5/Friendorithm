cmake_minimum_required(VERSION 4.1)
project(Friendorithm)

set(CMAKE_CXX_STANDARD 14)

include_directories(FriendAlgorithm/include)

add_executable(Friendorithm
        FriendAlgorithm/include/bfs.h
        FriendAlgorithm/include/dataset.h
        FriendAlgorithm/include/dijkstra.h
        FriendAlgorithm/include/graph.h
        FriendAlgorithm/include/user.h
        FriendAlgorithm/src/bfs.cpp
        FriendAlgorithm/src/dataset.cpp
        FriendAlgorithm/src/dijkstra.cpp
        FriendAlgorithm/src/graph.cpp
        FriendAlgorithm/src/main.cpp
        FriendAlgorithm/src/user.cpp)
