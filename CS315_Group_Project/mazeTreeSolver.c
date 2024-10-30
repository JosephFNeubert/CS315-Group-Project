/****************************************************************************
* File:     mazeTreeSolver.c
* Author:   Sawyer Curless, Kaden Hayrynen, Joseph Neubert
* Purpose:  Maze solver (TODO)
* Version:  1.0 - Oct. 30, 2024
* Resources: N/A
*******************************************************************************/

// Import libraries
#include <stdio.h>
#include <string.h>

// Declaration of Maze Tree structure
struct mazeTree {
	struct mazeTree* left;
	struct mazeTree* center;
	struct mazeTree* right;
	int location[2];
};

// Function prototypes
char* readInMaze();
struct mazeTree* convertMazeInTree(char* maze);
struct mazeTree* runDijkstra(struct mazeTree* tree);
void displayMazeSolution(char* maze, struct mazeTree* optimalTree);
int getMazeSolutionSteps(struct mazeTree* optimalTree);

// Main
int main() {
	// TODO - Joe
	return 0;
}

// All function implementations
char* readInMaze() 
{
	//TODO - Joe
}

struct mazeTree* convertMazeInTree(char* maze)
{
	//TODO - Sawyer
}

struct mazeTree* runDijkstra(struct mazeTree* tree) 
{
	//TODO - Sawyer
}

void displayMazeSolution(char* maze, struct mazeTree* optimalTree) 
{
	//TODO - Kaden
}

int getMazeSolutionSteps(struct mazeTree* optimalTree) 
{
	//TODO - Kaden
}
