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
#include <stdlib.h>

#define MAZESZ 20

// Declaration of Maze Tree structure
typedef struct{
	struct *mazeTree links[4];
	int location[2];
} mazeTree;

// Function prototypes
void readInMaze(char* fileName, char maze[MAZESZ][MAZESZ]);
mazeTree* convertMaze2Tree(char maze[MAZESZ][MAZESZ]);
mazeTree* runDijkstra(mazeTree* tree);
void displayMazeSolution(char* maze,  mazeTree* optimalTree);
int getMazeSolutionSteps(mazeTree* optimalTree);

// Main
int main() {
	// TODO - Joe
	return 0;
}

// All function implementations
void readInMaze(char* fileName, char maze[MAZESZ][MAZESZ]) 
{   
    
	//TODO - Joe
    FILE* fp = fopen(fileName,"r");
    for(int i = 0; i < MAZESZ; i++){
        fgets(maze[i], MAZESZ, fp);
    }
    fclose(fp);
}

mazeTree* convertMaze2Tree(const char maze[MAZESZ][MAZESZ])
{
    mazeTree* locs[MAZESZ][MAZESZ];
    int con = 0;
    for(int i = 0; i < MAZESZ; i++){
        for(int j = 0; j < MAZESZ; j++){
            locs[i][j] = NULL;
            if(maze[i][j] == ' '){
                locs[i][j] = (mazeTree*)malloc(sizeof(mazeTree));
                locs[i][j]->location[0] = i;
                locs[i][j]->location[1] = j;
            }
        }
    }

    for(int i = 0; i < MAZESZ; i++){
        for(int j = 0; j < MAZESZ; j++){
            if()

            }
        }


}



mazeTree* runDijkstra(mazeTree* tree) 
{
	//TODO - Sawyer
}
/*
void displayMazeSolution(char* maze,  mazeTree* optimalTree) 	//TODO - Kaden
{
	printf("Here is the solved Maze: \n");
	mazeTree* currentNode =optimalTree;
	while (current != NULL) {
        //track location of maze
        if(currentNode -> left){    //if moved left
            currentNode= currentNode->left;
        }
        else if (currentNode -> center){  //if straight instead
            currentNode -> currentNode ->center;
        }
        else if (currentNode -> right){    //if right
            currentNode = currentNode -> right;
        }
    }

}

int getMazeSolutionSteps(mazeTree* optimalTree)  	//TODO - Kaden
{
    int step=0;
    struct mazeTree* currentNode = optimalTree;
    
    while (currentNode != NULL){ //while nothing is in currentNode
        step++;  //add each step to counter
        
        if(currentNode -> left){    //if moved left
            currentNode= currentNode->left;
        }
        else if (currentNode -> center){  //if moved straight
            currentNode = currentNode -> center;
        }
        else if (currentNode -> right){   //if moved right
            currentNode = currentNode -> right;
        }
    }
    return step;
	printf("%d\n", step);
}
*/