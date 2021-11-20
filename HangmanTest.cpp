#include <iostream>
#include <string>
#include <vector>
using namespace std;

//******Word class to store all the needed information about the word to guess******
class Word {
public:
    Word(string mysteryWord);
    void ChooseLetter();
    void DispWord();
    void DispGallows();
    bool CheckIfSolved() { return (charArray == displayedCharArray)? true:false; }
    int numGuesses() { return correctGuesses + incorrectGuesses.size(); }
    int numLetters() { return wordLength; }
private:
    vector<char> charArray;            //Vector to store actual word
    vector<char> displayedCharArray;   //The parts of the word the player will see
    vector<char> incorrectGuesses{};   //Vector to store incorrect guesses
    int correctGuesses = 0;
    int wordLength;
};

//******Constructor for the mystery word******
Word::Word(string mysteryWord) {
    int i;
    wordLength = mysteryWord.size();
    displayedCharArray.resize(wordLength, '_');
    charArray.resize(wordLength, '_');
    wordLength = wordLength;
    for (i = 0; i < wordLength; i++) { charArray.at(i) = mysteryWord[i]; }
}

//******Displays guess information and mystery word with underscores('_') for unguessed letters******
void Word::DispWord() {
    int i;
    cout << "_____________________________________________________" << endl; //Line to make output more readable
    cout << endl << "Correct Guesses: " << correctGuesses << "  Incorrect Guesses: " << incorrectGuesses.size() << endl;
    cout << "Previous incorrect guesses: ";
    for (i = 0; i < incorrectGuesses.size(); i++) {
        cout << incorrectGuesses.at(i) << " ";
    }
    cout << endl << endl;
    for (i = 0; i < wordLength; i++) {
        cout << displayedCharArray.at(i) << " ";
    }
}

//******Displays gallows between every turn******
void Word::DispGallows() {
    int i;

    vector<string> gallows{ "_____________________________________________________\n\n",
        "     ||========| \n",
        "     ||        | \n",
        "     ||       (\")   \n",
        "     ||	      /|\\   \n",
        "     ||	     / | \\  \n",
        "     ||       / \\   \n",
        "     ||      /   \\  \n",
        "     ||                *** YOU DIED :( ***\n",
        " [[[[[]]]]]          (Keep guessing though) \n" };

    vector<string> emptyGallows{ "_____________________________________________________\n\n",
    "     ||========| \n",
    "     ||        | \n",
    "     ||        \n",
    "     ||	    \n",
    "     ||	    \n",
    "     ||        \n",
    "     ||        \n",
    "     ||             \n",
    " [[[[[]]]]]      \n" };

    cout << gallows.at(0) << gallows.at(1) << gallows.at(2);
    for (i = 3; i < 10; i++) {
        if (incorrectGuesses.size() <= (i - 3)) {
            cout << emptyGallows.at(i);
        } else {
            cout << gallows.at(i);
         }
    }
}

//******Primary function for game mechanics. Prompts input and adjusts variables accordingly******
void Word::ChooseLetter() {
    cout << endl << endl << "Choose a new letter:" << endl;
    cout << ">> ";
    char playerGuess;
    cin >> playerGuess;
    int i;
    int guessInstances = 0;
    for (i = 0; i < wordLength; i++) {
        if (charArray.at(i) == toupper(playerGuess)) {
            if (displayedCharArray.at(i) == charArray.at(i)) {
                cout << "You already guessed '" << playerGuess << "'!" << endl;
                return;
            } else {
                displayedCharArray.at(i) = charArray.at(i);
                guessInstances++;
            }
        }
    }
    cout << "'" << playerGuess << "' is in the word " << guessInstances << " times." << endl;
    if (guessInstances > 0) {
        correctGuesses++;
    } else {
        incorrectGuesses.push_back(playerGuess);
    }
}


int main()
{
    vector<string> mysteryWordList{ // Months used for simplicity.If other word set desired, replace words here
        "JANUARY",
        "FEBRUARY",
        "MARCH",
        "APRIL",
        "MAY",
        "JUNE",
        "JULY",
        "AUGUST",
        "SEPTEMBER",
        "OCTOBER"
    };

    srand(time(0));
    Word mysteryWord(mysteryWordList.at(rand() % 9)); //Set the mystery word to random word in set
    char restartPrompt;

    std::cout << 
    " _   _\n"
    "| | | |                                        \n"
    "| |_| | __ _ _ __   __ _ _ __ ___   __ _ _ __  \n"
    "|  _  |/ _` | '_  |/ _` | '_ ` _  |/ _` | '_  |  \n"
    "| | | | (_| | | | | (_| | | | | | | (_| | | | |\n"
    "|_| |_|.__,_|_| |_|___, |_| |_| |_|___,_|_| |_|\n"
    "                    __/ |                      \n"
    "                   |___/                       \n";

    cout << "\n\nWelcome to Hangman!\nIn this game a mystery word will be chosen, and you must guess the word, one letter at a time!\nGood Luck!!!" << endl;
    cout << "\nYour mystery word has " << mysteryWord.numLetters() << " letters in it." << endl;


    //******Main runtime loop******
    mysteryWord.DispWord();
    mysteryWord.ChooseLetter();
    while (!mysteryWord.CheckIfSolved()) {
        mysteryWord.DispGallows();
        mysteryWord.DispWord();
        mysteryWord.ChooseLetter();
    }

    cout << "_____________________________________________________" << endl; //Line to make output more readable
    cout << "Congradulations! You guessed the word!" << endl;
    cout << "It took you " << mysteryWord.numGuesses() << " tries to correctly guess the word." << endl;
    cout << endl << "Would you like to play again? y/n \n>> ";
    cin >> restartPrompt;
    if (tolower(restartPrompt) == 'y') {
        main();
    } else {
        cout << "\nThank you for playing! \nGoodbye!";
        return 0;
    }
}
