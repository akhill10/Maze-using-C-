#include<stdio.h>
#include<stdlib.h>
#include<time.h>
 
#define MAX 101 //maxRow + maxColumn + 1
#define WALL 1 //indicate the wall is up
#define PATH 0 //indicate the cells is previous path
#define CELLS 2500 //row * column
#define START 3 //start position
#define END 4 //end position
  
void mazeGenerator( int wMaze[ MAX ][ MAX ], int wSize ); //generate the maze
void startEnd( int wMaze[ MAX ][ MAX ], int wSize, int* wSRow, int* wSCol );//generate start and end position
void printMaze( int wMaze[ MAX ][ MAX ], int wSize );//display the maze

  
int main(void){
    
   int size = 3, sRow = 0, sCol = 0, state;
   int maze[ MAX ][ MAX ]; //maze array 
    
   printf("My Maze Generator\n*****************\n\n");
   printf("Input the size of your desired maze (3 to 50): ");
   do{
      if(size < 3 || size > 50)
         printf("Invalid size! Input again: ");
             
      scanf("%d", &size );//get the desired size from user
   }while(size < 3 || size > 50);
    
   mazeGenerator( maze, size );
   startEnd( maze, size, &sRow, &sCol );
   printMaze( maze, size );
      return 0;
}
//////////////////
//MAZE GENERATOR//
//////////////////
void mazeGenerator( int wMaze[ MAX ][ MAX ], int wSize ){
    
   srand(time( 0 ));
    
   void initMaze( int wMaze[ MAX ][ MAX ] ); //initalize the maze array
   int walled( int wMaze[ MAX ][ MAX ], int wRow, int wCol );//check neighbouring cells
    
   initMaze( wMaze );
    
   int counter = 0, row = 1, col = 1, visited = 1;
   int validNeighbour, valid, randValid, move;
   int neighbourRow[ 4 ];
   int neighbourCol[ 4 ];
   int step[ 4 ];
   int btRow[ CELLS ]; //backtrack row array
   int btCol[ CELLS ];//backtrack column array
    
   //start backtracking with first cell
   btRow[ 0 ] = 1;
   btCol[ 0 ] = 1;
       
   /*while VisitedCells < TotalCells*/
   while(visited < wSize * wSize){
      //initialize
      validNeighbour = -1;
       
      /*find all neighbors of CurrentCell with all walls intact*/
      //NORTH neighbour
      if(row - 2 > 0 && walled( wMaze, row - 2, col )){
         validNeighbour++;
         neighbourRow[ validNeighbour ] = row - 2;
         neighbourCol[ validNeighbour ] = col;
         step[ validNeighbour ] = 1;       
      } 
      //WEST neighbour
      if(col - 2 > 0 && walled( wMaze, row, col - 2 )){
         validNeighbour++;
         neighbourRow[ validNeighbour ] = row;
         neighbourCol[ validNeighbour ] = col - 2;
         step[ validNeighbour ] = 2;         
      }
      //EAST neighbour
      if(col + 2 < wSize * 2 + 1 && walled( wMaze, row, col + 2 )){
         validNeighbour++;
         neighbourRow[ validNeighbour ] = row;
         neighbourCol[ validNeighbour ] = col + 2;
         step[ validNeighbour ] = 3;         
      } 
      //SOUTH neighbour
      //size * 2 + 1 -> size + wall + outerWall
      if(row + 2 < wSize * 2 + 1 && walled( wMaze, row + 2, col )){
         validNeighbour++;
         neighbourRow[ validNeighbour ] = row + 2;
         neighbourCol[ validNeighbour ] = col;
         step[ validNeighbour ] = 4;         
      }
       
      //if one or more found
      if(validNeighbour != -1){
         //choose one at random
         valid = validNeighbour + 1;//number of valid neighbour
         randValid = rand() % valid;
          
         //make the new cell CurrentCell
         row = neighbourRow[ randValid ];
         col = neighbourCol[ randValid ];
          
         counter++;
          
         btRow[ counter ] = row;
         btCol[ counter ] = col;
          
         move = step[ randValid ];
          
         //knock down the wall between it and CurrentCell
         //NORTH
         if(move == 1){
            wMaze[ row + 1 ][ col ] = PATH;        
         }
         //WEST
         else if(move == 2){
            wMaze[ row ][ col + 1 ] = PATH;     
         }
         //EAST
         else if(move == 3){
            wMaze[ row ][ col - 1 ] = PATH;     
         }
         //SOUTH
         else if(move == 4){
            wMaze[ row - 1 ][ col ] = PATH;     
         }
          
         //add 1 to VisitedCells
         visited++;
      }
      //if none found 
      else{
         //backtracking
         row = btRow[ counter ];
         col = btCol[ counter ];
         counter--;      
      }
        
   }                           
}
 
void initMaze( int wMaze[ MAX ][ MAX ] ){
   int a, b;
    
   for(a  = 0; a < MAX; a++){
      for(b = 0; b < MAX; b++){
         if(a % 2 == 0 || b % 2 == 0){
            wMaze[ a ][ b ] = WALL;   
         }else{
            wMaze[ a ][ b ] = PATH;      
         }
      }       
   }     
}
 
void printMaze( int wMaze[ MAX ][ MAX ], int wSize ){
   int row, col;
    
   printf("\n");
    
   for(row = 0; row < wSize * 2 + 1; row++){
            
      if(wMaze[ row ][ 0 ] == START)
         printf(" START -> ");
      else
         printf("          ");
          
      for(col = 0; col < wSize * 2 + 1; col++){
         if(wMaze[ row ][ col ] == WALL)
            printf("#");
         else if(wMaze[ row ][ col ] == START)
            printf("X");
         else
            printf(" ");        
      } 
       
      if(wMaze[ row ][ wSize * 2 ] == END)
         printf(" <- END");
                 
      printf("\n");
   }  
   printf("\n"); 
   system("pause");
   system("cls");     
}
 
int walled( int wMaze[ MAX ][ MAX ], int wRow, int wCol ){
   if(wMaze[ wRow - 1 ][ wCol ] == WALL &&
      wMaze[ wRow + 1 ][ wCol ] == WALL &&
      wMaze[ wRow ][ wCol + 1 ] == WALL &&
      wMaze[ wRow ][ wCol - 1 ] == WALL )
      return 1;
       
   return 0;    
}
void startEnd( int wMaze[ MAX ][ MAX ], int wSize, int* wSRow, int* wSCol ){
   int start, end;
    
   do{
      start = rand() % (wSize * 2);//size + wall
   }while(start == 0 || wMaze[ start ][ 1 ] == WALL );
           
   do{
      end = rand() % (wSize * 2);   
   }while(end == 0 || wMaze[ end ][ (wSize * 2) - 1 ] == WALL);  
    
   wMaze[ start ][ 0 ] =  START;
   wMaze[ end ][ wSize * 2 ] = END; 
    
   *wSRow = start;
   *wSCol = 0; 
}