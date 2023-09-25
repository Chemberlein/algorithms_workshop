cmake_minimum_required(VERSION 3.22.5)
project(algorithms_workshop)
# Adding Raylib
include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # don't build the supplied example games

FetchContent_Declare(
    raylib
    GIT_REPOSITORY "https://github.com/raysan5/raylib.git"
    GIT_TAG "master"
    GIT_PROGRESS TRUE
)

FetchContent_MakeAvailable(raylib)
add_executable(${PROJECT_NAME} 
				src/main.cpp 
				src/ChemberleinRaylibUILib/app.cpp
				src/ChemberleinRaylibUILib/config.cpp
				src/ChemberleinRaylibUILib/element.cpp
				src/ChemberleinRaylibUILib/scene.cpp
				src/Algorithms/ConvexHull/ConvexHull.cpp
				src/Algorithms/MinimumSpanningTree/MST.cpp
				src/Algorithms/TravelSalesmanProblem/ConvexHullHeuristicTSP.cpp
				src/Algorithms/TravelSalesmanProblem/InsertionHeuristicTSP.cpp
				src/Algorithms/TravelSalesmanProblem/MSTTSP.cpp
				src/Algorithms/TravelSalesmanProblem/NearestNeighborTSP.cpp
				src/Algorithms/Utils/DSU.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)