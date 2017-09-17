# COSC302-Lab7
Solve a maze using Depth First Search algorithm

# maze_solve.cpp
This file uses a graph structure to set up a maze. The graph is assumed to be fully
connected at the start, meaning that each node has a edge to the north, south, east, 
and west (assuming the node is not a boundry condition). A text file containing wall 
data is then read. From there, edges are deleted as the walls are defined. Once the 
graph structure is built, a DFS algorithm is run to find the path through the maze.

# Usage
./maze_solve maze.txt

# Additional Files

# maze_gen
This executable generates a maze give a number of rows and columns
./maze_gen rows columns

# maze_ppm
This executable generates a ppm image when given a maze text file
./maze_ppm maze.txt
