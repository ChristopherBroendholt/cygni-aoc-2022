#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Structs
typedef struct {
    int height;
    int width;
    int** trees;
} Map;

// PROTOTYPES
int getMapSize();   
Map createMap(int size);
int findVisibleTrees(Map map);
int findBestTreeHouseLocation(Map map);


int main(){
    int mapSize = getMapSize();
    Map treeMap = createMap(mapSize);
    //int visibleTrees = findVisibleTrees(treeMap);
    int bestTreeHouseScore = findBestTreeHouseLocation(treeMap);
    
    free(treeMap.trees);

    return 0;
}

int getMapSize(){
    FILE* filePtr = fopen("input.txt", "r");
    char tree;

    int count = 0;

    if(filePtr == NULL){
        printf("CANNOT READ FILE .1");
        return 0;
    }

    while(1){
        tree = fgetc(filePtr);

        if(tree == '\n'){
            break;
        }
        count = count + 1;
    }

    return count;
}

//PART 1
int findVisibleTrees(Map map){
    int visibleTrees = 0;

    for(int i = 0; i < map.height; i++){
        for(int j = 0; j < map.width; j++){
            if(i == 0 || j == 0 || j == map.width - 1 || i == map.height - 1){
                visibleTrees++;
            }
            else{
                int treeHeight = map.trees[i][j];
                int hidden = 0;
                
                //Up
                for(int k = i - 1; k >= 0; k--){
                    if(map.trees[k][j] >= treeHeight){
                        hidden++;
                        break;
                    }
                }
                //Right
                for(int k = j + 1; k < map.width; k++){
                    if(map.trees[i][k] >= treeHeight){
                        hidden++;
                        break;
                    }
                }
                //Down
                for(int k = i + 1; k < map.height; k++){
                    if(map.trees[k][j] >= treeHeight){
                        hidden++;
                        break;
                    }
                }
                //Left
                for(int k = j - 1; k >= 0; k--){
                    if(map.trees[i][k] >= treeHeight){
                        hidden++;
                        break;
                    }
                }

                if(hidden < 4){
                    printf("\nI: %d, J: %d\n", i, j);
                    visibleTrees++;
                }
            }

            printf("%d", map.trees[i][j]);
            printf("\n------------------------\n");
        }
        
        printf("\n");
    }

    printf("\n%d", visibleTrees);
}

//PART 2
int findBestTreeHouseLocation(Map map){
    int bestViewScore = 0;
    
    for(int i = 0; i < map.height; i++){
        for(int j = 0; j < map.width; j++){
            if(i == 0 || j == 0 || j == map.width - 1 || i == map.height - 1){
                continue;
            }
            else{
                int treeHeight = map.trees[i][j];
                int up = 0;
                int right = 0; 
                int left = 0; 
                int down = 0;
                
                //Up
                for(int k = i - 1; k >= 0; k--){
                    if(map.trees[k][j] >= treeHeight){
                        up++;
                        break;
                    }
                    up++;
                }
                //Right
                for(int k = j + 1; k < map.width; k++){
                    if(map.trees[i][k] >= treeHeight){
                        right++;
                        break;
                    }
                    right++;
                }
                //Down
                for(int k = i + 1; k < map.height; k++){
                    if(map.trees[k][j] >= treeHeight){
                        down++;
                        break;
                    }
                    down++;
                }
                //Left
                for(int k = j - 1; k >= 0; k--){
                    if(map.trees[i][k] >= treeHeight){
                        left++;
                        break;
                    }
                    left++;
                }

                int newViewScore = up * right * down * left;
                

                if(newViewScore > bestViewScore){
                    bestViewScore = newViewScore;
                    printf("UP: %d, RIGHT: %d, DOWN: %d, LEFT: %d\n", up, right, down, left);
                    printf("I: %d, j: %d\n", i, j);
                    printf("VIEW SCORE: %d", newViewScore);
                    printf(" <-- NEW BEST\n");
                    printf("-----------------------\n");
                }
            }
        }
    }

    printf("\n%d", bestViewScore);
}

Map createMap(int size){    
    FILE* filePtr = fopen("input.txt", "r");

    char tree;
    int** trees = (int **)malloc((sizeof(int) * size * size) + 1);

    int* arrPtr = (int *)(trees + size);

    for(int i = 0; i < size; i++){
        trees[i] = (arrPtr + size * i);
    }

    Map map;
    map.height = size;
    map.width = size;

    if(filePtr == NULL){
        free(trees);

        printf("CANNOT READ FILE .2");
        return map;
    }
    
    int wCount = 0;
    int hCount = 0;

    int count = 0;

    fseek(filePtr, 0, SEEK_SET);

    while(1){

        tree = fgetc(filePtr);
        
        if(tree == EOF || tree == -1){ 
            break; 
        }
        
        if(tree == '\n' || tree == '\r'){
            hCount++;
            wCount = 0;
        }
        else{
            trees[hCount][wCount] = atoi(&tree);
            
            wCount++;
        }

        count++;
    }

    map.trees = trees;

    fclose(filePtr);
    return map;
}



// /* You could be lazy and just guess a size of the elements in a global int array larger than you'll ever need,
//  * and you could just keep the size alongside instead of in a struct,
//  * but here's how you could handle it dynamically and safely.
//  */
// typedef struct {
//     int capacity;
//     int size;
//     int *elements;
// } Intlist;

// Intlist* emptyIntlist() {
//     // When we pass stuff around, we probably want to malloc to allocate on the heap,
//     // otherwise we might be passing a pointer to an area on the stack around, which
//     // might get overwritten soon after we return from this scope.
//     Intlist *new = malloc(sizeof(Intlist));
//     new->elements = malloc(10 * sizeof(int));
//     new->capacity = 10;
//     new->size = 0;
//     return new;
// }

// void appendToIntlist(Intlist* list, int element) {
//     if (list->size > list->capacity) {
//         fprintf(stderr, "List size %d exceeds capacity %d\n", list->size, list->capacity);
//         exit(1);
//     } else if (list->size == list->capacity) {
//         list->elements = realloc(list->elements, (list->capacity + 10) * sizeof(int));
//         list->capacity += 10;
//     }
//     list->elements[list->size] = element;
//     list->size++;
// }

// Intlist* readInput() {
//     Intlist *data = emptyIntlist();
//     FILE *in_file  = fopen("input.txt", "r"); // read only 
//     if (in_file == NULL) {
//         fprintf(stderr, "Input file not found");
//         exit(1);
//     }
//     // When reading lines with C, you like it if all lines end with \n
//     int n;
//     while (fscanf(in_file, "%d\n", &n) == 1) {
//         appendToIntlist(data, n);
//     }
//     fclose(in_file);
//     return data;
// }

// int getSolutionPart1(Intlist *data) {
//     int result = 0;
//     for (int i = 0; i < data->size; ++i) {
//         result += data->elements[i];
//     }
//     return result;
// }

// int getSolutionPart2(Intlist *data) {
//     int result = 1;
//     for (int i = 0; i < data->size; ++i) {
//         result *= data->elements[i];
//     }
//     return result;
// }

// int main() {
//     Intlist *data = readInput();

//     printf("C\n");
//     char* part = getenv("part");

//     if (part != NULL && strcmp("part2", part) == 0) {
//         printf("%d\n", getSolutionPart2(data));
//     } else {
//         printf("%d\n", getSolutionPart1(data));
//     }

//    return 0;
// }