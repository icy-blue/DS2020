cmake_minimum_required(VERSION 3.16)
project(DS2020)

set(CMAKE_CXX_STANDARD 17)

add_executable(DS2020 main.cpp DoubleLinkedList.h Stack.h Queue.h sort.h test.h PriorityQueue.h ConvexHull.h Tree.h ThreadedBinaryTree.h AVLTree.h FenwickTree.h Tree23.h)