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
typedef char mazeStr[MAZESZ][MAZESZ];
// Function prototypes
void readInMaze(char* fileName, mazeStr maze);
mazeTree* convertMaze2Tree(const mazeStr);
mazeTree* dfSearch(mazeTree* tree);
void displayMazeSolution(char* maze,  mazeTree* optimalTree);
int getMazeSolutionSteps(mazeTree* optimalTree);
void freeMaze(mazeTree* root);
void printsln(mazeTree* root);
void dispMaze(mazeStr maze);
void sln2Maze(mazeTree* sln, mazeStr maze);

// Main
int main() {
	// TODO - Joe
    mazeStr mazeS;
    readInMaze("maze",mazeS);
    printf("Maze read:\n");
    dispMaze(mazeS);
    mazeTree *maze = convertMaze2Tree(mazeS);
    //printf("%p:(%d,%d)\n",maze,maze->location[0],maze->location[1]);
    mazeTree *sln = dfSearch(maze);
    printf("solution found:\n");
    //printf("%p\n",sln);
    printsln(sln);
    sln2Maze(sln,mazeS);
    dispMaze(mazeS);
    //freeMaze(maze);
    //freeMaze(sln);

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
        return NULL; // uh oh!


}

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
        //printf("@edge:(%d,%d)\n",sln->location[0],sln->location[1]);
        return sln;
    }
    tree->vFlag++;
    for(int i = 0; i < 4; i++){
        //printf("%p:%c\n",tree->links[i],DIRCHR[i]);
        sln = (mazeTree*)malloc(sizeof(mazeTree));
        if(tree->links[i] != NULL && tree->links[i]->vFlag == 0){
            //printf("%c:(%d,%d)\n",DIRCHR[i],tree->location[0],tree->location[1]);
            for(int q = 0; q < 4; q++)
                sln->links[q] = NULL;
            sln->links[i] = dfSearch(tree->links[i]);
            sln->location[0] = tree->location[0];
            sln->location[1] = tree->location[1];
            if(sln->links[i] != NULL){
                sln->vFlag = i;
                //printf("TRACEBACK:(%d,%d),L:%p\n",sln->location[0],sln->location[1],sln->links[i]);
                return sln;
            }
        free(sln);
        }
    }
    return NULL;

}

void printsln(mazeTree* root){
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
void freeMaze(mazeTree* root){
    for(int i = 0; i < 4; i++){
        if(root->links[i] != 0){
            freeMaze(root->links[i]);
        }
    }
    free(root);
}

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

void sln2Maze(mazeTree* sln, mazeStr maze){
    if(sln == NULL)
        return;
    //printf("a\n");
    //printf("%p\n",root);
    int i = 0;
    while(sln->vFlag < 4){
        maze[sln->location[0]][sln->location[1]] = PATCHR[sln->vFlag];
        sln = sln->links[sln->vFlag];
    }
    maze[sln->location[0]][sln->location[1]] = PATCHR[sln->vFlag];
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