// Jackson Keyser
// Project 1 - Wordle
// 2/26/2021


#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <cstdlib>
using namespace std;

// Declare and initialize a character constant for yes
string const YES_STRING = "y";
// Declare and initialize a character constant for no
string const NO_STRING = "n";
// Declare and initialize a bool constant for false
bool const FALSE_STRING = false;
// Declare and initalize a bool constant for true
bool const TRUE_STRING = true;
// Everly Wordle word is 5 letters
int const EVERY_WORD_LENGTH = 5;
// Constant for an empty string
string const EMPTY_STRING = "";
// Constant for the blank space on the game board
char const BLANK_SPACE = '_';
// Constant for letter in word and in correct position
char const CORRECT_POSITION = '!';
// Constant for letter in word, but letter is not in the correct position
char const INCORRECT_POSITION = '&';
// Constant for the number of words to be chosen from for the Wordle game
int const NUMBER_OF_WORDS = 15;
// Constant for the max number of guesses the user can have
int const MAX_NUMBER_GUESSES = 6;

string wordPicked(string wordleWordArray[]);

void resetBoard(char gameArray[][EVERY_WORD_LENGTH]);

void printBoard(char gameArray[][EVERY_WORD_LENGTH]);

void printBoardWithUserGuesses(char gameArray[][EVERY_WORD_LENGTH], string arrayUserGuesses[]);

bool userWonCheck(string userGuess, string wordChosen, bool gameWon);

bool userLostCheck(int currentGuess, string userGuess, string wordChosen, bool gameLost);

string gameIsWon(bool gameWon, string wordChosen, string userInput);

string gameIsLost(bool gameLost, string wordChosen, string userInput);

void checkGuess(int wordLength, int currentGuess, string userGuess, string wordChosen, char gameArray[][EVERY_WORD_LENGTH], int usedIndexPositions[], bool letterUsed, int counter);

int main () {
    // Declares and initializes a variable for storing each Worlde word which comes from the given txt file
    string wordleWord = "";
    // Declares a string array and initializes it to 0. Used for storing all possible Wordle words to be chosen from
    string wordleWordArray[NUMBER_OF_WORDS] = {};
    // Declares and initializes an int variable for keeping track of the current index position of where in the array
    // to store the word from the txt file
    int wordleWordArrayStoringIndex = 0;

    // Declares new variable for the file and opens it
    ifstream myFile ("words.txt");

    // If the file has successfully been opened
    if(myFile.is_open()){
        // Lets the user know the file has been opened succesfully
        cout << "Your file was imported!" << endl;
        // While there is another word to read in
        while(myFile >> wordleWord){
            // Prints out the current word
            //cout << "Word: " << wordleWord << endl;
            // Stores the word in the word bank
            wordleWordArray[wordleWordArrayStoringIndex] = wordleWord;
            // Increments the index by 1 so the next word can be stored in the array in the next position
            wordleWordArrayStoringIndex += 1;
            }
        // Lets the user know how many words were retrieved from the txt file
        cout << wordleWordArrayStoringIndex << " words imported." << endl;

        // Declare and initialize a boolean variable for whether the user wants to keep plaing the game. Set to true
        bool keepPlaying = TRUE_STRING;

        while(keepPlaying == TRUE_STRING){
            // Declares and initializes a string variable for storing the word that will be chosen for the game
            string wordChosen = "";
            // Calls the function that will randomly pick the word for the game and store it in a variable
            wordChosen = wordPicked(wordleWordArray);


            // Declares and initializes an int variable for storing the length of the word
            int wordLength = 0;
            // Gets the length of the word
            wordLength = EVERY_WORD_LENGTH;

            // Declare and initialize a character array which will be the board for the game
            char gameArray[MAX_NUMBER_GUESSES][EVERY_WORD_LENGTH] = {};

            // Creates a fresh board
            resetBoard(gameArray);
            // Prints out the fresh board
            printBoard(gameArray);

            // Declares and initializes a bool variable for if the player guesses the word correctly
            bool gameWon = FALSE_STRING;
            // Declares and initializes a bool variable for if the player has used up their 6 guesses
            bool gameLost = FALSE_STRING;
            // Declares and initializes an int variable for storing the current guess the player is on
            int currentGuess = 0;
            // Declares and initializes string variable for storing the guessed user word
            string userGuess = "";
            // Declares and initializes a string array for storing the user guesses
            string arrayUserGuesses[MAX_NUMBER_GUESSES] = {};
            // Array for storing the index positions for the letter that the user guess that was in the incorrect
            // position corresponds to 
            // If the word is "ezzzz" and the user guess is "xeexh" only 1 "e" will have an "&"
            int usedIndexPositions[EVERY_WORD_LENGTH] = {-1, -1, -1, -1, -1};
            // Declare and initialize a counter variable for the index position of "usedIndexPositions" array
            int counter = 0;
            // Declare and initalize a boolean variable for whether the letter in the word has been used for incorrect position
            // Set it to false
            bool letterUsed = FALSE_STRING;
            // Declare and initialize a boolean variable for whether or not the user typed word is in list of words
            bool wordInList = FALSE_STRING;


            // Runs the game
            do{
                // Prompts the user to guess a word
                cout << "What word would you like to guess?" << endl;
                // Stores the guessed user word
                cin >> userGuess;

                // Loops through all Wordle words
                for(int i = 0; i < NUMBER_OF_WORDS; i++){
                    // If user guess is Wordle word
                    if(userGuess == wordleWordArray[i]){
                        // Sets boolean to true
                        wordInList = TRUE_STRING;
                    }
                }

                // If user guess is not a World word
                // Will keeping running until it is
                while(wordInList == FALSE_STRING){
                    cout << "Not a Wordle word. Try again." << endl;
                    cin >> userGuess;

                    // Loops through all Wordle words
                    for(int i = 0; i < NUMBER_OF_WORDS; i++){
                        // If user guess is Wordle word
                        if(userGuess == wordleWordArray[i]){
                            // Sets boolean to true
                            wordInList = TRUE_STRING;
                        }
                    }
                }

                // Sets boolean back to false
                wordInList = FALSE_STRING;

                

                // Stores user guess in array of guesses
                arrayUserGuesses[currentGuess] = userGuess;
                
                // Checks user guess
                checkGuess(wordLength, currentGuess, userGuess, wordChosen, gameArray, usedIndexPositions, letterUsed, counter);
               
                // Prints out game board followed by user guesses
                printBoardWithUserGuesses(gameArray, arrayUserGuesses);

                // Checks to see if the user won the game
                gameWon = userWonCheck(userGuess, wordChosen, gameWon);

                // Increments the player's current guess by 1
                currentGuess = currentGuess + 1;
                // Couts the user's current guess
                //cout << "Current Guess: " << currentGuess << endl;

                // Checks to see if the user lost the game
                gameLost = userLostCheck(currentGuess, userGuess, wordChosen, gameLost);


            // If the user has guessed the word correctly or has used up their 6 guesses
            }while((gameWon != TRUE_STRING) && (gameLost != TRUE_STRING));

            // Declares and initalizes a variable for storing whether the user wants to play another game
            string userInput = "";

            // Prompt for if game was won
            userInput = gameIsWon(gameWon, wordChosen, userInput);

            // Prompt for if game was lost
            userInput = gameIsLost(gameLost, wordChosen, userInput);

            // If the user does not want to keep playing the game
            if(userInput == NO_STRING){
                cout << "Thanks for playing!" << endl;
                keepPlaying = FALSE_STRING;
             }

    }

    // If the file is unable to be opened
    }else{
        // Let the user know that the file was unable to be opened
        cout << "Unable to open file" << endl;
        }

    return 0;
}

string wordPicked(string wordleWordArray[]){
    // Declares and initializes and int variable for storing the random index selected to be used for picking the
    // word that will be used for the game
    int indexSelected = 0;
    // Seeds the random number generator
    srand(time(NULL));
    // Uses rand function to pick the number that will be the index
    indexSelected = rand() % NUMBER_OF_WORDS;
    // Cout statement for index selected
    //cout << "The index selected: " << indexSelected << endl;
    // Declares and initializes a string variable for storing the word that was chosen
    string wordChosen = "";
    // Sets the wordChosen variable to be the word in the word bank at the given random position
    wordChosen = wordleWordArray[indexSelected];
    // Cout statement for the word that will be used for the game
    //cout << "The word is: " << wordChosen << endl;

    // Declares and initializes an int variable for storing the length of the word
    int wordLength = 0;
    // Gets the length of the word
    wordLength = EVERY_WORD_LENGTH;
    // Lets the user know how many letters the word is
    cout << "Okay. I am thinking of a word with " << wordLength << " letters." << endl;


    return wordChosen;
}


void resetBoard(char gameArray[][EVERY_WORD_LENGTH]){
    // Fills the entire board up with underscores
    for(int i = 0; i < MAX_NUMBER_GUESSES; i++){
        for(int j = 0; j < EVERY_WORD_LENGTH; j++){
            gameArray[i][j] = BLANK_SPACE;
        }
    }
}


void printBoard(char gameArray[][EVERY_WORD_LENGTH]){
    // Prints out the board 
    for(int i = 0; i < MAX_NUMBER_GUESSES; i++){
        for(int j = 0; j < EVERY_WORD_LENGTH; j++){
            cout << gameArray[i][j];
        }
        cout << endl; 
    }
}


void printBoardWithUserGuesses(char gameArray[][EVERY_WORD_LENGTH], string arrayUserGuesses[]){
    // Prints out the board 
    for(int i = 0; i < MAX_NUMBER_GUESSES; i++){
        for(int j = 0; j < EVERY_WORD_LENGTH; j++){
            cout << gameArray[i][j];
        }
        cout << endl; 
        // If index in user guesses array is not empty
        if(arrayUserGuesses[i] != EMPTY_STRING){
            cout << arrayUserGuesses[i] << endl;
        }
    }
}


bool userWonCheck(string userGuess, string wordChosen, bool gameWon){
    // If the user guesses the word correctly
    if(userGuess == wordChosen){
        // Set gameWon boolean to true
        gameWon = true;
        //cout << "sweg" << endl;
    }
    return gameWon;
}


bool userLostCheck(int currentGuess, string userGuess, string wordChosen, bool gameLost){
    // If the user used up all of their guesses and did not guess the word on their last attempt
    if(currentGuess == (MAX_NUMBER_GUESSES) && userGuess != wordChosen){
        // Sets game lost boolean to true
        //cout << "no sweg" << endl;
        gameLost = TRUE_STRING;
    }
    return gameLost;
}


string gameIsWon(bool gameWon, string wordChosen, string userInput){
    // If the user won the game
    if(gameWon == TRUE_STRING){
    cout << "Congrats you won!" << endl;
    cout << "The correct word was: " << wordChosen << endl;
    cout << "Another game? y/n" << endl;
    cin >> userInput;
    }
    return userInput;
}


string gameIsLost(bool gameLost, string wordChosen, string userInput){
     // If the user lost the game
    if(gameLost == TRUE_STRING){
    cout << "Sorry you lost!" << endl;
    cout << "The correct word was: " << wordChosen << endl;
    cout << "Another game? y/n" << endl;
    cin >> userInput;
    }
    return userInput;
}


void checkGuess(int wordLength, int currentGuess, string userGuess, string wordChosen, char gameArray[][EVERY_WORD_LENGTH], int usedIndexPositions[], bool letterUsed, int counter){
    // This first "for loop" is for going through each letter of the user's guessed word and one-by-one comparing
        // them to all of the letters of the word
        for(int i = 0; i < wordLength; i++){
            // This second "for loop" is for going through all of the letters of the word
            for(int j = 0; j < wordLength; j++){
                // This is in place for if the 2 letters are in the same spot. That would be a "&" not an "!"
                if(i != j){
                    // If the two letters are the same
                    if(userGuess[i] == wordChosen[j]){
                    // If the letter is not already in the correct position
                    if(gameArray[currentGuess][i] != CORRECT_POSITION){
                        // Loops through used index positions array
                        for(int x = 0; x < EVERY_WORD_LENGTH; x++){
                            // If the letter in the word has already been used for incorrect position
                            if(usedIndexPositions[x] == j){
                                // Sets leter used boolean to true
                                letterUsed = TRUE_STRING;
                            }
                        }
                        if(letterUsed != TRUE_STRING){
                            // Put an "&" in the place of the user's guess for that letter
                            gameArray[currentGuess][i] = INCORRECT_POSITION;
                            // The index position of the used letter in the word is stored in the array
                            usedIndexPositions[counter] = j;
                            // Increments counter by 1 for next index position
                            counter++;
                            }
                        }
                    }
                }
                // If both letters are in the same position
                if(i == j){
                    // If the letters match up
                    if(userGuess[i] == wordChosen[j]){
                        // Put an "!" in the place of the user's guess for that letter
                        gameArray[currentGuess][i] = CORRECT_POSITION;
                    }
                }
            }
        }
        // This loop sends the used index positions all back to -1
        // Example: word is aware and user guessed sweep
        // It would go from _!&__ to _!___ if the user guessed sweep twice in a row since the used index position was not reset
        for(int i = 0; i < EVERY_WORD_LENGTH; i++){
                usedIndexPositions[i] = -1;
            }
}