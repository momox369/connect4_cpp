#include "connect4.h"


int main() {
    
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
    cout << yellow << "\nPlayer 2 is: " << player2 << reset << "\n\n"; 

    //creating the board for the game
    char** board = initializeBoard();
    
    int numberOfMoves = 0,
    turn = 1; //Player 1 start
    bool win = false;

    while (!win && numberOfMoves < ROWS * COLS) {

        if (turn == 1){
            cout << "\n\n ==" << p1 << "'s turn!==";
        }
        else {
            cout << "\n\n ==" << p2 << "'s turn!==";
        }

        printBoard(board);
        
        //ask the player for a move
        string input = "";
        cout << "\nPlease enter a valid column number: ";      
        cin >> input;
        
        while (!validInput(board, input)){
            cout << "\nPlease enter a valid column number: ";      
            cin >> input;
        }

        //if the flow of control exits the while loop, then validInput return true
        int column = stoi(input);
        cout << "\nINSERTED AN X IN THE COLUMN NUMBER SUCCESSFULLY: " << column; 
        numberOfMoves++;
        turn = (turn == 1) ? 2 : 1; //swipe players
    }

    
    return 0;
}

char** initializeBoard(){
    char** board = new char*[ROWS];
    for (int i = 0; i < ROWS; i++){
        board[i] = new char[COLS];
    }
    for (int i = 0; i < ROWS; i++){
        for (int j = 0; j < COLS; j++){
            board[i][j] = 'O';
        }
    }
    return board;
}

void printBoard(char** board) {
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

bool validInput (char** board, string input){
    bool number = isNumeric(input);
    int inputIntegerRepresentation; 
    if (number) { inputIntegerRepresentation = stoi(input); }

    cout << "\ntesting: number: " << number << ", inputIntegerREpresentation: " << inputIntegerRepresentation << "\n";

    if (!number){   //sequence of letters characters
        cout << magenta << "\nINVALID INPUT! INSERT A INTEGER NUMBER!" << reset;
        return false;
    }

    else if (number && (0 >= inputIntegerRepresentation || inputIntegerRepresentation >= 8)){
        cout << magenta << "\nINVALID INPUT!  NUMBER SHOULD BE BETWEEN 1 AND 7!" << reset;
        return false;
    }

    else {
        if (board[0][inputIntegerRepresentation] != 'O'){
            cout << magenta << "\nINVALID INPUT! COLUMN IS FULL!" << reset;
            return false;
        }
        else {
            return true;
        }
    }
    return false;
}
       
void insertColumn(char** board, int column_number, int turn){

}

bool isNumeric(string s) {
    for (char c : s) {
        if (isdigit(c) == 0)
            return false;
    }
    return true;
}
