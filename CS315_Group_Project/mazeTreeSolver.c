/****************************************************************************
* File:     mazeTreeSolver.c
* Author:   Sawyer Curless, Kaden Hayrynen, Joseph Neubert
* Purpose:  Program that reads in a text file of a maze structure, converts it into a tree, performs depth-first search,
*           then outputs the maze's solution.
* Version:  1.0 - Nov 14, 2024
* Resources: N/A
*******************************************************************************/

// Import libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Definitions
#define MAZESZ 61
#define DIRCHR "ULDR"
#define PATCHR "^<v>!"
#define FANCYDISP 1

// Declaration of Maze Tree structure
typedef struct mazeTree{
	struct mazeTree* links[4];
	int location[2];
    int vFlag;
} mazeTree;

// Declaration of Maze String
typedef char mazeStr[MAZESZ][MAZESZ];

// Function prototypes
void readInMaze(char* fileName, mazeStr maze);
mazeTree* convertMaze2Tree(const mazeStr);
mazeTree* dfSearch(mazeTree* tree);
void freeMaze(mazeTree* root);
void printsln(mazeTree* root);
void sln2Maze(mazeTree* sln, mazeStr maze);
void dispMaze(mazeStr maze);

// Main
int main() {
    mazeStr mazeS;
    readInMaze("maze",mazeS);
    printf("Maze read:\n");
    dispMaze(mazeS);
    mazeTree *maze = convertMaze2Tree(mazeS);
    mazeTree *sln = dfSearch(maze);
    printf("solution found:\n");
    printsln(sln);
    sln2Maze(sln,mazeS);
    dispMaze(mazeS);

	return 0;
}

// ALL FUNCTION IMPLEMENTATIONS

// Read in maze to a maze string from a text file
void readInMaze(char* fileName, mazeStr maze) 
{
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

// Convert the maze string into a tree
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
                if(j > 0 && locs[i][j - 1] != NULL){
                    locs[i][j]->links[1] = locs[i][j - 1];
                }
                if(i < MAZESZ - 1 && locs[i + 1][j] != NULL){
                    locs[i][j]->links[2] = locs[i + 1][j];
                }
                if(j < MAZESZ - 1 && locs[i][j + 1] != NULL){
                    locs[i][j]->links[3] = locs[i][j + 1];
                }
            }

            }
        }
        for(int i = 0; i < MAZESZ; i++){
            if(locs[0][i] != NULL)
                return locs[0][i];
        }
        return NULL;
}

// Depth-first search of the maze tree
mazeTree* dfSearch(mazeTree* tree) {
    
	mazeTree* sln = NULL;
    if(tree == NULL)
        return NULL;

    if(tree->location[1] == 0 || tree->location[0] == MAZESZ - 1 || tree->location[1] == MAZESZ-1){
        sln = (mazeTree*) malloc(sizeof(mazeTree));
        for(int q = 0; q < 4; q++)
            sln->links[q] = NULL;
        sln->location[0] = tree->location[0];
        sln->location[1] = tree->location[1];
        sln->vFlag = 4;
        return sln;
    }
    tree->vFlag++;
    for(int i = 0; i < 4; i++){
        sln = (mazeTree*)malloc(sizeof(mazeTree));
        if(tree->links[i] != NULL && tree->links[i]->vFlag == 0){
            for(int q = 0; q < 4; q++)
                sln->links[q] = NULL;
            sln->links[i] = dfSearch(tree->links[i]);
            sln->location[0] = tree->location[0];
            sln->location[1] = tree->location[1];
            if(sln->links[i] != NULL){
                sln->vFlag = i;
                return sln;
            }
        free(sln);
        }
    }
    return NULL;
}

// Prints the letters denoting the directions taken to solve the maze
void printsln(mazeTree* root) {
    if(root == NULL)
        printf("NO SOLUTION");
    //printf("a\n");
    //printf("%p\n",root);
    int i = 0;
    while(root != NULL && root->vFlag < 4){
        printf("%c",DIRCHR[root->vFlag]);
        root = root->links[root->vFlag];
    }
    printf("\n");
}

// Free the allocated data for maze
// Does not currently work, trys to double free entries due to bidirectionality
void freeMaze(mazeTree* root){
    for(int i = 0; i < 4; i++){
        if(root->links[i] != 0){
            freeMaze(root->links[i]);
        }
    }
    free(root);
}

// Convert the maze solution into a graphical representation
void sln2Maze(mazeTree* sln, mazeStr maze) {
    if (sln == NULL)
        return;
    //printf("a\n");
    //printf("%p\n",root);
    int i = 0;
    while (sln->vFlag < 4) {
        maze[sln->location[0]][sln->location[1]] = PATCHR[sln->vFlag];
        sln = sln->links[sln->vFlag];
    }
    maze[sln->location[0]][sln->location[1]] = PATCHR[sln->vFlag];
}

// Display the graphical maze solution determined by sln2Maze
void dispMaze(mazeStr maze){
    for(int i = 0; i < MAZESZ; i++){
        for(int j = 0; j < MAZESZ; j++){
            if(FANCYDISP){
                if(maze[i][j] == ' '){
                    printf("\033[0m");
                }else if('A' <= maze[i][j] && maze[i][j] <= 'Z'){
                    printf("\033[47m");
                }else{
                    printf("\033[42m");
                }
            }
            printf("%c",maze[i][j]);
        }
        if(FANCYDISP)
            printf("\033[0m");
        printf("\n");
    }
}
