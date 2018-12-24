//header file contains libraries and function prototypes
#include "tic_tac_toe.h"

//global variable to keep track of board state and turn
char board[3][3];
int turn;

//sets board and turn to inital state
void newGame(){
    for(int x=0;x<3;x++){
        for(int y=0;y<3;y++){
            board[x][y] = 32;
        }
    }
    turn = 0;
}

//prints current state of board to terminal
void printToScreen(){
    printf("     A   B   C \n");
    printf(" 1  _%c_|_%c_|_%c_\n", board[0][0], board[1][0], board [2][0]);
    printf(" 2  _%c_|_%c_|_%c_\n", board[0][1], board[1][1], board [2][1]);
    printf(" 3   %c | %c | %c \n", board[0][2], board[1][2], board [2][2]);
}

//prompts user to input move, validates move, and returns an encoded version of the move
//because of the coordinate system it was easier to encode and decode the user's input so the values being passed between methods could be integers
int getMove(){
    int result=0, i, d;
    char c;
    printf("Please enter move in coordinte format, example: A,3\n");
    scanf("%c,%d", &c, &d);
    while ((i = getchar()) != '\n') { }
    if((c>67 && c<97) ||c<65 || c>99 || d<1 || d>3){
        printf("\nInvalid format: %c,%d\n\n", c,d);
        return -1;
    }
    if(c == 'a' || c == 'b' || c == 'c'){
        c-=32;
    }
    if(board[c-65][d-1] != 32){
        printf("\nThat space is already taken! Choose Again\n\n");
        return -2;
    }
    result += (d-1);
    if(c=='B'){
        result += 3;
    }
    if(c=='C'){
        result += 6;
    }
    return result;
}

//decodes player move and udates board
//player is the integer value of the 'X' and 'O' characters
int updateBoard(int move, int player){
    int y = move%3;
    int x = move / 3;
    board[x][y] = player;
    return 0;
}

//this method handles alternating between 'X' and 'O' when updating board
int doTurn(){
    int m = -1;
    if(turn == 0){
        printf("player 1's turn(X)\n");
    } else {
        printf("player 2's turn(O)\n");
    }
    while(m < 0){
        m = getMove();
    }
    if(turn == 0){
        updateBoard(m,'X');
    } else {
        updateBoard(m,'O');
    }
    turn = (turn+1) % 2;
    printToScreen();
    return 0;
}

//prompts user for input to play again
int playAgain(){
    char c;
    int i;
    printf("Would you like to play again? : Y/N\n");
    while(1){
        scanf("%c", &c);
        while ((i = getchar()) != '\n') { }
        if((c == 'Y') || (c == 'y')){
            return 1;
        }
        if((c == 'N') || (c == 'n')){
            return 0;
        }
        printf("Please enter a valid input : Y/N\n");
    }
    
}
//hard coded to check for three of the same character in a row, if found returns that character as an int to declare as winner
//also counts number of remaining spaces, if no winner found and no empty spaces left, returns 1 for tie game
int checkBoard(){
    int spaceCount = 0;
    for(int x=0;x<3;x++){
        for(int y=0;y<3;y++){
            if(board[x][y] == 32){
                spaceCount++;
            }
        }
    }
    if((board[0][0] == board[1][0])  && (board[1][0] == board[2][0]) && (board[0][0] != 32)){
        return board[0][0];
    }
    if((board[0][1] == board[1][1])  && (board[1][1] == board[2][1]) && (board[0][1] != 32)){
        return board[0][1];
    }
    if((board[0][2] == board[1][2])  && (board[1][2] == board[2][2]) && (board[0][2] != 32)){
        return board[0][2];
    }
    if((board[0][0] == board[0][1])  && (board[0][1] == board[0][2]) && (board[0][0] != 32)){
        return board[0][0];
    } 
    if((board[1][0] == board[1][1])  && (board[1][1] == board[1][2]) && (board[1][0] != 32)){
        return board[1][0];
    } 
    if((board[2][0] == board[2][1])  && (board[2][1] == board[2][2]) && (board[2][0] != 32)){
        return board[2][0];
    }
    if((board[0][0] == board[1][1])  && (board[1][1] == board[2][2]) && (board[0][0] != 32)){
        return board[0][0];
    }
    if((board[2][0] == board[1][1])  && (board[1][1] == board[0][2]) && (board[2][0] != 32)){
        return board[2][0];
    }
    if(spaceCount == 0){
        return 1;
    }
    return 0;
}
//main game loop
void playGame(){
    newGame();
    printToScreen();
    while(1){
        doTurn();
        int result = checkBoard();
        if(result == 1){
            printf("No moves left, tie game!\n");
            break;
        }
        if(result == 'X'){
            printf("Player 1(X) Wins!\n");
            break;
        }
        if(result == 'O'){
            printf("Player 2(O) Wins!\n");
            break;
        }
    }
}

//main runs system loop to keep playing the game if the user wants to keep going
int main(int argc, char **argv){
    do{
        playGame();
    } while(playAgain() == 1);
    printf("Exiting Game\n");
    return 0;
}