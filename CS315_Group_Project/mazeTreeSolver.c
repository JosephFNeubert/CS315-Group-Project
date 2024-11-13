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
#define DIRCHR "URDL"

// Declaration of Maze Tree structure
typedef struct mazeTree{
	struct mazeTree* links[4];
	int location[2];
    int vFlag;
} mazeTree;
typedef char mazeStr[MAZESZ][MAZESZ];
// Function prototypes
void readInMaze(char* fileName, mazeStr maze);
mazeTree* convertMaze2Tree(const mazeStr);
mazeTree* dfSearch(mazeTree* tree);
void displayMazeSolution(char* maze,  mazeTree* optimalTree);
int getMazeSolutionSteps(mazeTree* optimalTree);
void freeMaze(mazeTree* root);
void printsln(mazeTree* root);

// Main
int main() {
	// TODO - Joe
    mazeStr mazeS;
    printf("yeah\n");
    readInMaze("maze",mazeS);
    printf("read in \n\n");
    mazeTree *maze = convertMaze2Tree(mazeS);

    printf("converted \n\n");
    printf("%p:(%d,%d)\n",maze,maze->location[0],maze->location[1]);
    mazeTree *sln = dfSearch(maze);
    printf("solution found:\n");
    printsln(sln);
    printf("%p:(%d,%d)\n",sln,sln->location[0],sln->location[1]);
    freeMaze(maze);
    freeMaze(sln);

	return 0;
}

// All function implementations
void readInMaze(char* fileName, mazeStr maze) 
{   
    
	//TODO - Joe (not anymore lol)
    FILE* fp = fopen(fileName,"r");
    if(fp == NULL)
        return;
    for(int i = 0; i < MAZESZ; i++){
        for(int j = 0; j < MAZESZ; j++){
            maze[i][j] = fgetc(fp);
            if(maze[i][j] == '\n')
                j--;
        }

    }
    fclose(fp);
}

mazeTree* convertMaze2Tree(const mazeStr maze)
{
    mazeTree* locs[MAZESZ][MAZESZ];
    for(int i = 0; i < MAZESZ; i++){
        for(int j = 0; j < MAZESZ; j++){
            locs[i][j] = NULL;
            if(maze[i][j] == ' '){
                locs[i][j] = (mazeTree*)malloc(sizeof(mazeTree));
                locs[i][j]->vFlag = 0;
                locs[i][j]->location[0] = i;
                locs[i][j]->location[1] = j;
            }
        }
    }

    for(int i = 0; i < MAZESZ; i++){
        for(int j = 0; j < MAZESZ; j++){
            if(locs[i][j] != NULL){
                for(int q = 0; q < 4; q++)
                    locs[i][j]->links[q] = NULL;
                if(i > 0 && locs[i-1][j] != NULL){
                    locs[i][j]->links[0] = locs[i - 1][j];
                }
                if(j > 0 && locs[i-1][j] != NULL){
                    locs[i][j]->links[1] = locs[i][j - 1];
                }
                if(i < MAZESZ - 1 && locs[i-1][j] != NULL){
                    locs[i][j]->links[2] = locs[i + 1][j];
                }
                if(j < MAZESZ - 1 && locs[i-1][j] != NULL){
                    locs[i][j]->links[3] = locs[i][j + 1];
                }
            }

            }
        }
        for(int i = 0; i < MAZESZ; i++){
            if(locs[0][i] != NULL)
                return locs[0][i];
        }
        return NULL; // uh oh!


}

mazeTree* dfSearch(mazeTree* tree) 
{
    
	mazeTree* sln = NULL;
    if(tree == NULL)
        return NULL;

    if(tree->location[1] == 0 || tree->location[0] == MAZESZ - 1 || tree->location[1] == MAZESZ-1){
        sln = (mazeTree*) malloc(sizeof(mazeTree));
        for(int q = 0; q < 4; q++)
            sln->links[q] = NULL;
        sln->location[0] = tree->location[0];
        sln->location[1] = tree->location[1];
        return sln;
    }
    tree->vFlag++;
    for(int i = 0; i < 4; i++){
        if(tree->links[i] != NULL && tree->links[i]->vFlag == 0){
            printf("%c:%p (%d,%d)\n",DIRCHR[i],tree->links[i],tree->location[0],tree->location[1]);
            sln = (mazeTree*)malloc(sizeof(mazeTree));
            for(int q = 0; q < 4; q++)
                sln->links[q] = NULL;
            sln->links[i] = dfSearch(tree->links[i]);
            sln->location[0] = tree->location[0];
            sln->location[1] = tree->location[1];
            if(sln != NULL){
                return sln;
            }
        }
    }
    return NULL;

}

void printsln(mazeTree* root){
    printf("a\n");
    printf("%p\n",root);
    //while(root != NULL){
        mazeTree* tmp = NULL;
        for(int i = 0; i < 4; i++){
            printf("what!\n");
            if(root->links[i] != NULL){
                printf("what!\n");
                printf("%c",DIRCHR[i]);
                tmp = root->links[i];
                break;
            }
            root = tmp;
        }
    //}
    printf("\n");
}

void freeMaze(mazeTree* root){
    for(int i = 0; i < 4; i++){
        if(root->links[i] != 0){
            freeMaze(root->links[i]);
        }
    }
    free(root);
}



/*
void displayMazeSolution(char* maze, struct mazeTree* optimalTree){ 	//TODO - Kaden
	
    printf("Here is the solved Maze: \n");
	struct mazeTree* currentNode =optimalTree;
	while (current != NULL) {   

        // marks the location in the maze with *
        int row = current->location[0];
        int col = current->location[1];
        maze[row * (int)sqrt(strlen(maze)) + col] = '*';

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

    //printing the completed maze
        int mazeSize = (int)sqrt(strlen(maze));
        for (int x = 0; x < strlen(maze); x++) {
        printf("%c", maze[x]);   //print line of maze
        if ((x+1) % mazeSize == 0) {  // newline for each row
            printf("\n"); //prints new line
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