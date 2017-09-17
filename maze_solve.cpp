#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <set>
/*
	maze_solve.cpp
	David Swanson
	November 1, 2015

	This program uses graphs and Depth First Search to solve a given maze. The maze is given
	in a text file. The all components of the map are assumed to be connected and when a 
	wall is read in, the connection is deleted. DFS is then used to find a path and output
	the path if it has one.
*/

using namespace std;

/* Each node contains its id, a list of connections, and a boolean in the form of an integer
   to tell if a node has already been visited during a depth first search. The edges are 
   in a set so that erasing a component is simple. */

class Node {
  public:
	int id;
	set <int> edges;
	int visited;
};

/* The graph's constructor has two integer parameters, the number of rows and number of 
   columns. The boolean check is false unless DFS finds a path through the maze.*/

class Graph {
  public:
	  Graph(int, int);
	  ~Graph();
	  vector <Node *> nodes;
	  void DFS(int index);
	  int check;
};

/* Deconstructor deletes all nodes */

Graph::~Graph() {
  int i;
  
  for (i = 0; i < nodes.size(); i++) {
	delete nodes[i];
  }
}

/* Constructor for the graph that assumes all the nodes have connections to each other at 
   the start. */

Graph::Graph(int r, int c) {
  int i, j;					/* Induction variables */
  nodes.resize(r*c);
  check = 0;

  /* Each index of nodes is a new node that has not been visited and has id of the index */

  for (i = 0; i < r*c; i++) {
	nodes[i] = new Node;
	nodes[i]->visited = 0;
	nodes[i]->id = i;
	
  }

  /* Assume all nodes have all possible connections at the creation of the graph. */

  for (i = 0; i < r; i++) {
    for (j = 0; j < c; j++) {
	  /* Set all edges in the north direction */
	  if (i != 0) {
		nodes[i*c+j]->edges.insert((i-1)*c+j);
	  }
	  /* Set all edges in the south direction */
	  if (i != r-1) {
		nodes[i*c+j]->edges.insert((i+1)*c+j);
	  }
	  /* Set all edges in the west direction */
	  if (j != 0) {
		nodes[i*c+j]->edges.insert(i*c+(j-1));
	  }
	  /* Set all edges in the east direction */
	  if (j != c-1) {
		nodes[i*c+j]->edges.insert(i*c+(j+1));
	  }
	}
  }
}

/* DFS function that searches for a possible path through the maze. It prints the path if
   it finds one. For the purpose of this lab, the function is called with the last index
   so that it searches backwards. */

void Graph::DFS(int index) {
  set <int>::iterator eit;	/* Used to traverse set of edges */

  /* Once the recursive call reaches node 0, it changes the boolean since it found a path */

  if (nodes[index]->id == 0) {
	check = 1;
	cout << "PATH " << index << endl;
	return;
  }

  /* Sets visited field as the recursive call gets to more nodes.*/

  if (nodes[index]->visited)
    return;
  nodes[index]->visited = 1;

  /* DFS is called for every member of the edges set and once a call returns and the boolean
     is true, we know that node is part of the path. */

  for (eit = nodes[index]->edges.begin(); eit != nodes[index]->edges.end(); eit++) {
	DFS(*eit);
	if (check) {
	  cout << "PATH " << index << endl;
	  return;
	}
  }
}

int main () {
  string s, s1, s2, s3;	/* Strings used to read in Walls */
  int i;				/* Induction variable */
  int r, c;				/* row and column variable */
  int e1, e2;			/* Edges that represent a wall */
  vector <string> walls;/* Holds all the walls that are read in */
  
  /* While the program can read in strings, the strings are combined and push onto walls */

  cin >> s1 >> r >> s2 >> c;
  cout << "ROWS " << r << " COLS " << c << endl;
  while (cin >> s1 >> s2 >> s3) {
	s = s1 + " " + s2 + " " + s3;
	walls.push_back(s);
  }

  /* Graph constructor called with rows and columns */
  Graph g(r, c);

  /* Erases each edge that is corresponding to wall */

  for (i = 0; i < walls.size(); i++) {
	cout << walls[i] << endl;
	sscanf(walls[i].c_str(), "WALL %d %d", &e1, &e2);
	g.nodes[e1]->edges.erase(e2);
	g.nodes[e2]->edges.erase(e1);
  }

  /* DFS called with last node */
  g.DFS(r*c-1);

  return 0;
}
