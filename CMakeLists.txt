cmake_minimum_required(VERSION 3.16)
project(DS2020)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
include_directories(include/GL)
include_directories(include/GLFW)
link_directories(lib/Win32)
link_directories(lib)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
add_executable(DS2020 src/main.cpp src/DoubleLinkedList.h src/Stack.h src/Queue.h src/sort.h src/test.h src/PriorityQueue.h src/ConvexHull.h src/Tree.h src/Tree23-2.h src/ThreadedBinaryTree.h src/AVLTree.h src/FenwickTree.h src/Tree23.h src/KMP.h src/Dinic.h src/Union.h src/Kruskal.h src/Graph.h src/Euler.h src/Dijkstra.h)
target_link_libraries(DS2020 libfreeglut glfw3 libglfw3 libglfw3dll glew32 glew32s libfreeglut libfreeglut_static)
