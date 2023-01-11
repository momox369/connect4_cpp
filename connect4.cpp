#include "connect4.h"


int main() {

    //These 4 lines of codes have the purpose to make the colors appears in cmd
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    SetConsoleMode(hInput, ENABLE_VIRTUAL_TERMINAL_INPUT);
    HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleMode(hOutput, ENABLE_PROCESSED_OUTPUT | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    //

    cout << red << "WELCOME TO " << reset << yellow << "CONNECT 4" << magenta << " by maurice ;)\n" << reset;
    
    //Taking the players names
    string name1, name2;
    cout << "\nEnter player name: ";
    cin >> name1;

    cout << "Enter another player name: ";
    cin >> name2;

    //Assigning to each player their turns (player 1 or 2)
    string player1 = chooseRandomPlayer(name1, name2);
    string player2 = (player1.compare(name1) == 0) ? name2 : name1;
    cout << red << "\nPlayer 1 is: " << player1;
    cout << yellow << "\nPlayer 2 is: " << player2 << reset << "\n"; 

    //creating the board for the game
    string** board = initializeBoard();
    

    int numberOfMoves = 0,
    winner = 0, 
    turn = 1; //1 means player 1 turns, and 2 means player 2 turn
    

    while (winner == 0 && numberOfMoves < ROWS * COLS) {
        if (turn == 1){
            cout << "\n\n ==" << red << player1 << reset << "'s turn!==";
        }
        else {
            cout << "\n\n ==" << yellow << player2 << reset << "'s turn!==";
        }

        printBoard(board);
        
        //ask the player for a move (store in a string, since it's easier to test for non-desirable input)
        string input = "";
        cout << "\nPlease enter a valid column number: ";      
        cin >> input;
        
        while (!validInput(board, input)){
            cout << "\nPlease enter a valid column number: ";      
            cin >> input;
        }

        //if the flow of control exits the while loop, then validInput return true
        int column = stoi(input);
        insertColumn(board, column, turn);
        winner = checkWinnerningMove(board);
        numberOfMoves++;
        turn = (turn == 1) ? 2 : 1; //switch players
    }

    printBoard(board);
    
    return 0;
}

string** initializeBoard(){
    //function that creates a ROWS x COLS board for the game
    //requires: nothing
    //effects: return a 2D array of strings

    string** board = new string*[ROWS];
    for (int i = 0; i < ROWS; i++){
        board[i] = new string[COLS];
    }
    for (int i = 0; i < ROWS; i++){
        for (int j = 0; j < COLS; j++){
            board[i][j] = "O";
        }
    }
    return board;
}

void printBoard(string** board) {
    //prints the passed board
    //requires: dimensions of the board ROWS x COLS
    //effects: prints the board and return nothing

    cout << "\n";
    
    for (int i = 0; i < ROWS; i++){
        cout << "| ";
        for (int j = 0; j < COLS; j++){
            cout << board[i][j] << " ";
        }
        cout << "|\n"; 
    }
    cout << "-----------------";
}

string chooseRandomPlayer(string name1, string name2) {
    /*
    if random number is even, return name1
    else if random number is odd, return name2.

    -require: names of the players
    -effects: return a random player name with 50% | 50% chances each
    */
    
    srand(time(0));
    int random = rand() % 10;
    return (random % 2 == 0) ? name1 : name2; 
}

bool validInput (string** board, string input){
    /*
    this function checks the validity of the user's input according to the game's rules
    requires: the current game board along with the user input
    effects: return true if the input is an integer between 1 and 7, and false otherwise.
    */
    bool number = isNumeric(input);
    int inputIntegerRepresentation; 
    if (number) { inputIntegerRepresentation = stoi(input); }

    if (!number){   //sequence of letters characters
        cout << magenta << "\nINVALID INPUT! INSERT A INTEGER NUMBER!" << reset;
        return false;
    }

    else if (number && (0 >= inputIntegerRepresentation || inputIntegerRepresentation >= 8)){
        cout << magenta << "\nINVALID INPUT!  NUMBER SHOULD BE BETWEEN 1 AND 7!" << reset;
        return false;
    }

    else {
        if (!isEqualToEmptyToken(board[0][inputIntegerRepresentation-1])){
            cout << magenta << "\nINVALID INPUT! GIVEN COLUMN IS FULL!" << reset;
            return false;
        }
        return true;
    }

    return false;
}
       
void insertColumn(string** board, int column_number, int turn){
    /*
    this funct insert a colored X in the column the player inserted in, by modyfying the board itself
    requires: the current board game and a valid column number (not array indexed)
    effects: modify the board game and place a red X for player 1 and a yellow X for player 2 in the corresponding column
    */

    for (int row = ROWS-1; row >= 0; row--){
        if (isEqualToEmptyToken(board[row][column_number-1])) { 
            if (turn == 1){
                board[row][column_number-1] = player1_token;
                break;
            }

            else {
                board[row][column_number-1] = player2_token;
                break;
            }
        }
    }
}

int checkWinnerningMove(string** board){
    /*
    This function checks if there exists 4 consecutive same colored X in any direction
    requries: the current game board
    effects: return 0 if there is no winner (4 consecutive same colored X in any direction)
             return 1 if player 1 wins
             return 2 if player 2 wins
    */

    int winnerPlayer = 0;

    //checking vertically
    for (int c = 0; c < COLS; c++) {
        for (int r = 0; r < ROWS - 3; r++) {
            if (board[r][c] == player1_token &&
                board[r + 1][c] == player1_token &&
                board[r + 2][c] == player1_token &&
                board[r + 3][c] == player1_token) {

                winnerPlayer = 1;
            }
            else if (board[r][c] == player2_token &&
                board[r + 1][c] == player2_token &&
                board[r + 2][c] == player2_token &&
                board[r + 3][c] == player2_token) {

                winnerPlayer = 2;
            }
        }
    } 

    //checking horizontally
    for (int c = 0; c < COLS-3; c++) {
        for (int r = 0; r < ROWS; r++) {
            if (board[r][c] == player1_token &&
                board[r][c + 1] == player1_token &&
                board[r][c + 2] == player1_token &&
                board[r][c + 3] == player1_token) {

                winnerPlayer = 1;
            }
            else if (board[r][c] == player2_token &&
                     board[r][c + 1] == player2_token &&
                     board[r][c + 2] == player2_token &&
                     board[r][c + 3] == player2_token){

                winnerPlayer = 2;
            }
        }
    }

    //checking diagonaly (positive slope)
    for (int c = 0; c < COLS - 3; c++) {
        for (int r = 0; r < ROWS - 3; r++) {
            if (board[r][c] == player1_token &&
                board[r + 1][c + 1] == player1_token &&
                board[r + 2][c + 2] == player1_token &&
                board[r + 3][c + 3] == player1_token) {

                winnerPlayer = 1;
            }
            else if (board[r][c] == player2_token &&
                    board[r + 1][c + 1] == player2_token &&
                    board[r + 2][c + 2] == player2_token &&
                    board[r + 3][c + 3] == player2_token) {

                winnerPlayer = 2;
            }
        }
    }

    //checking diagonaly (negative slope)
    for (int c = 0; c < 7 - 3; c++) {
        for (int r = 3; r < 6; r++) {
            if (board[r][c] == player1_token &&
                board[r - 1][c + 1] == player1_token &&
                board[r - 2][c + 2] == player1_token &&
                 board[r - 3][c + 3] == player1_token) {

                winnerPlayer = 1;
            }
            else if (board[r][c] == player2_token &&
                board[r - 1][c + 1] == player2_token &&
                board[r - 2][c + 2] == player2_token &&
                 board[r - 3][c + 3] == player2_token) {

                winnerPlayer = 2;
            }
        }
    }

    return winnerPlayer;
}

//helper functions
bool isNumeric(string s) {
    //This function checks if a string represent an integer
    //requires: nothing
    //effects: return true if given string is a representation of a number

    for (char c : s) {
        if (isdigit(c) == 0)
            return false;
    }
    return true;
}

bool isEqualToEmptyToken (string s){
    //This function checks whether a string is equal to the empty character of the board "O", or not.
    //requires: the string that need to be checked
    //effects: return if string ?= "O"
    if (s.size() >= 2){
        return false;
    }
       return s[0] == 'O';
}
