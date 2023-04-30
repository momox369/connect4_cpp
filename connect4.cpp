//connect 4 representation implemeted by Maurice T. Salameh
#include "connect4.h"


int main() {

    //These 4 lines of codes have the purpose to make the colors appears in cmd
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    SetConsoleMode(hInput, ENABLE_VIRTUAL_TERMINAL_INPUT);
    HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleMode(hOutput, ENABLE_PROCESSED_OUTPUT | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    //
    
    introConnect4();
    cout << red << "WELCOME TO " << reset << yellow << "CONNECT 4" << magenta << " by maurice ;)\n\n" << reset;

    int mode = modeChooser(); //mode 1 for bot, mode 2 for pvp

    //Taking the players names
    string name1, name2;

    if (mode == 2) {
        cout << "\nEnter a player name " << magenta << "(no space): " << reset;
        cin >> name1;

        cout << "Enter another player name: " << magenta << "(no space): " << reset;
        cin >> name2;
    } else {
        cout << "\nEnter player name " << magenta << "(no space): " << reset;
        cin >> name1;
        name2 = "Computer";
    }

    //Assigning to each player their turns (player 1 or 2)
    player1 = chooseRandomPlayer(name1, name2);
    player2 = (player1.compare(name1) == 0) ? name2 : name1;
    cout << red << "\nPlayer 1 is: " << player1;
    cout << yellow << "\nPlayer 2 is: " << player2 << reset << "\n"; 

    //creating the board for the game
    int** board = initializeBoard();
    
    int numberOfMoves = 0,
    winner = 0, 
    turn = 1; //1 means player 1 turns, and 2 means player 2 turn
    float duration, player1_time = 0, player2_time = 0;
    
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
        clock_t start = clock();
        cout << "\nPlease enter a valid column number: ";      
        cin >> input;

        while (!validInput(board, input)){
            cout << "\nPlease enter a valid column number: ";      
            cin >> input;
        }

        //if the flow of control exits the while loop, then validInput return true
        clock_t end = clock();
        duration = (float)((end-start)/CLOCKS_PER_SEC);

        if (turn == 1) { 
            player1_time += duration;
        }
        else { 
            player2_time += duration;
        }

        int column = stoi(input);
        insertColumn(board, column, turn);
        winner = checkWinnerningMove(board);
        numberOfMoves++;
        turn = (turn == 1) ? 2 : 1; //switch players
    }

    printBoard(board);
    announceWinner(winner, player1_time, player2_time);
    
    return 0;
}

int** initializeBoard(){
    //function that creates a ROWS x COLS board for the game
    //requires: nothing
    //effects: return a 2D array of integers initialized to 0

    int** board = new int*[ROWS];
    for (int i = 0; i < ROWS; i++){
        board[i] = new int[COLS];
    }
    for (int i = 0; i < ROWS; i++){
        for (int j = 0; j < COLS; j++){
            board[i][j] = 0;
        }
    }
    return board;
}


void printBoard(int** board) {
    //prints the passed board
    //requires: dimensions of the board ROWS x COLS
    //effects: prints the board and return nothing

    cout << "\n";
    
    for (int i = 0; i < ROWS; i++){
        cout << "| ";
        for (int j = 0; j < COLS; j++){
            int token = board[i][j];
            if (token == 1){
                cout << player1_token << " ";
            }
            else if (token == 2){
                cout << player2_token << " ";
            }
            else {
                cout << to_string(token) << " ";
            }
            
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


bool validInput (int** board, string input){
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
        if (board[0][inputIntegerRepresentation-1] != 0){
            cout << magenta << "\nINVALID INPUT! GIVEN COLUMN IS FULL!" << reset;
            return false;
        }
        return true;
    }

    return false;
}


void insertColumn(int** board, int column_number, int turn){
    /*
    this funct insert a int in the column the player inserted in, by modyfying the board itself
    requires: the current board game and a valid column number (not array indexed)
    effects: modify the board game and place a 1 for player 1 and a 2 for player 2 in the corresponding column
    */

    for (int row = ROWS-1; row >= 0; row--){
        if (board[row][column_number-1] == 0) { 
            if (turn == 1){
                board[row][column_number-1] = 1;
                break;
            }

            else {
                board[row][column_number-1] = 2;
                break;
            }
        }
    }
}

int checkWinnerningMove(int** board){
    /*
    This function checks if there exists 4 consecutive same int number(1 or 2) in any direction
    requries: the current game board
    effects: return 0 if there is no winner 
             return 1 if player 1 wins
             return 2 if player 2 wins
    */

    int winnerPlayer = 0;

    //checking vertically
    for (int c = 0; c < COLS; c++) {
        for (int r = 0; r < ROWS - 3; r++) {
            if (board[r][c] == 1 &&
                board[r + 1][c] == 1 &&
                board[r + 2][c] == 1 &&
                board[r + 3][c] == 1 ) {

                winnerPlayer = 1;
            }
            else if (board[r][c] == 2 &&
                board[r + 1][c] == 2 &&
                board[r + 2][c] == 2 &&
                board[r + 3][c] == 2) {

                winnerPlayer = 2;
            }
        }
    } 

    //checking horizontally
    for (int c = 0; c < COLS-3; c++) {
        for (int r = 0; r < ROWS; r++) {
            if (board[r][c] == 1 &&
                board[r][c + 1] == 1 &&
                board[r][c + 2] == 1 &&
                board[r][c + 3] == 1) {

                winnerPlayer = 1;
            }
            else if (board[r][c] == 2 &&
                     board[r][c + 1] == 2 &&
                     board[r][c + 2] == 2 &&
                     board[r][c + 3] == 2){

                winnerPlayer = 2;
            }
        }
    }

    //checking diagonaly (positive slope)
    for (int c = 0; c < COLS - 3; c++) {
        for (int r = 0; r < ROWS - 3; r++) {
            if (board[r][c] == 1 &&
                board[r + 1][c + 1] == 1 &&
                board[r + 2][c + 2] == 1 &&
                board[r + 3][c + 3] == 1) {

                winnerPlayer = 1;
            }
            else if (board[r][c] == 2 &&
                    board[r + 1][c + 1] == 2 &&
                    board[r + 2][c + 2] == 2 &&
                    board[r + 3][c + 3] == 2) {

                winnerPlayer = 2;
            }
        }
    }

    //checking diagonaly (negative slope)
    for (int c = 0; c < 7 - 3; c++) {
        for (int r = 3; r < 6; r++) {
            if (board[r][c] == 1 &&
                board[r - 1][c + 1] == 1 &&
                board[r - 2][c + 2] == 1 &&
                 board[r - 3][c + 3] == 1) {

                winnerPlayer = 1;
            }
            else if (board[r][c] == 2 &&
                board[r - 1][c + 1] == 2 &&
                board[r - 2][c + 2] == 2 &&
                 board[r - 3][c + 3] == 2) {

                winnerPlayer = 2;
            }
        }
    }

    return winnerPlayer;
}


void announceWinner(int win, float time_player1, float time_player2){
    /*
    function that decides the winner and in case of tie, compares their players' play time.
    requires: win to be 0, 1 or 2
    effects: prints a winning message for the winning player.
    */
    if (win == 1){
        cout << red << "\nPLAYER 1 WINS THE GAMES. CONGRATS!!!\n" << reset;
    }
    else if (win == 2){
        cout << yellow << "\nPLAYER 2 WINS THE GAMES. CONGRATS!!!\n" << reset;
    }
    else {
        if (time_player2 > time_player1){
            cout << red << "\nPLAYER 1 WINS THE GAMES BY TIME ADVANTAGE. CONGRATS!!!\n" << reset;
        }
        else if (time_player1 > time_player2){
            cout << yellow << "\nPLAYER 2 WINS THE GAMES BY TIME ADVANTAGE. CONGRATS!!!\n" << reset;
        }
        else {
            cout << magenta << "\nNO WINNERS. THE GAME ENDS WITH A TIE!\n" << reset;
        }
    }
}


void introConnect4() {
    /*This function introduce the game and its rule to the players
    requires: nothing
    effects: prints the rules of the games.
    */

    //definition of the game
    cout << mcolored("CONNECT-FOUR") << " is a model of tic-tac-toe game for " << magenta << "TWO PLAYERS "
    << reset << "in which \nplayers alternately place pieces on a vertical board in order \nto " << magenta << 
    "connect 4 identical pieces sequentially in any direction." << reset << "\n\n";

    //Rules
    cout << mcolored("\t\tRULES OF THE GAME\n");
    cout << mcolored("1. ") << "The game board had 7 Columns and 6 Rows.\n";
    cout << mcolored("2. ") << "There are " << rcolored("21 red") << " and " << ycolored("21 yellow") << " token.\n";
    cout << mcolored("3. ") << "Player 1 always starts, with the " << rcolored("Red tokens") << ", and Player 2 takes the " << ycolored("Yellow tokens") << ".\n";
    cout << mcolored("4. ") << "The tokens are inserted at the top of a column, and they will fall down and land \non the ground (if the column was empty) or on top of a previously inserted token.\n";
    cout << mcolored("5. ") << rcolored("Red") << " starts, then " << rcolored("red") << " and " << ycolored("yellow") << " take turns.\n";
    cout << mcolored("6. ") << "A player can only insert " << mcolored("one token") << " in only " << mcolored("one column") << ".\n";
    cout << mcolored("7. ") << "A player can't insert a token in a " << mcolored("full column") << ".\n";
    cout << mcolored("8. ") << "A player wins the game if they manage to form " << mcolored("a line of four tokens") << " of their color. \n(A line consists of several tokens, either in vertical, horizontal, or diagonal form, \nwhich contain only tokens of the same color.\n";
    cout << mcolored("9. ") << "The game " << mcolored("ends") << "if one of the player " << mcolored("wins\n"); 
    cout << mcolored("10. ") << "There will be " << mcolored("no ties") << ". In case of a tie on the board, the player that took " << mcolored("less over-all time") << " wins.\n\n";

}

//function to choose between pvp or computer vs player
int modeChooser() {
    printf("Choose your mode of game\n(1) Play against a robot\n(2) Play against another player\n Enter your choice: ");
    string inp;
    while (inp != "1" && inp != "2"){
        cin >> inp;
        if (inp == "1" || inp == "2")
            break;
        
        printf("\nPlease insert either 1 or 2: ");
    }

    return stoi(inp); 
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

