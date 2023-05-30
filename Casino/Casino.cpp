#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
#include <string>
#include <chrono>
#include <thread>
#include <map>
#include <list>
#include <algorithm>
#include <time.h>
#include <stdlib.h>
#include <conio.h>

using namespace std;

class Player {
public:
    string name;
    int balance;
    int currentBet;
    int currentGamble;

    Player(string newName, int newBalance) {
        name = newName;
        balance = newBalance;
    }
};

enum actionValue {
    av_undefined,
    av_play,
    av_rules,
    av_help,
    av_quit
};

enum difficultyValue {
    dv_undefined,
    dv_easy,
    dv_medium,
    dv_hard
};

static map<string, actionValue> s_actionMappings = {
    {"play", av_play},
    {"rules", av_rules},
    {"help", av_help},
    {"quit", av_quit}
};

static map<string, difficultyValue> s_difficultyMappings = {
    {"quick", dv_easy},
    {"easy", dv_easy},
    {"long", dv_medium},
    {"medium", dv_medium},
    {"ceo", dv_hard},
    {"hard", dv_hard}
};

static map<difficultyValue, int> s_balanceMappings = {
    {dv_easy, 100},
    {dv_medium, 1000},
    {dv_hard, 1000000}
};

string toTitle(string s) {
    const int length = s.length();
    char* charArray = new char[length + 1];
    strcpy(charArray, s.c_str());
    for (int i = 0; i < length; i++) {
        if (i == 0) {
            charArray[i] = toupper(charArray[i]);
        }
        else {
            charArray[i] = tolower(charArray[i]);
        }
    }
    string returnStr(charArray);
    return returnStr;

}

string toLower(string s) { // terrible function naming - tolower is a stdlib function
    const int length = s.length();
    char* charArray = new char[length + 1];
    strcpy(charArray, s.c_str());
    for (int i = 0; i < length; i++) {
        charArray[i] = tolower(charArray[i]);
    }
    string returnStr(charArray);
    return returnStr;
}

void help() {
    cout << "\n\t\t========== COMMANDS BOARD =========";
    cout << "\nPlay  - Play a round of dice";
    cout << "\nRules - Read the rules of the game";
    cout << "\nHelp  - Display this help message";
    cout << "\nQuit  - Cut the game short and leave\n";
}

void rules() {
    // system("cls");
    cout << "\n\t\t========== GAME RULES =========";
    cout << "\n1 - Place a bet on what number between 2 and 12 you think will appear";
    cout << "\n2 - Two dice will be rolled, and the numbers will be added together";
    cout << "\n3 - Whoever's number is closest to the total wins the pot. If more than one person wins, the pot is split evenly";
    cout << "\n4 - If you run out of money, you will be asked to leave\n";
}

int main() {
    srand(time(NULL));
    const int numOfPlayers = 3;

    string names[11] = {"Howard", "Rodney", "Ethel", "Diane", "Craig", "Albert", "Brenda", "Paula", "Jeremy", "Thomas", "Katherine"};
    
    // Create the player character
    string username;
    system("cls");
    cout << "\t\t========== WELCOME TO POT LUCK CASINO =========";
    cout << "\nEnter your name: ";
    cin >> username;
    username = toTitle(username);
    cout << "\nWelcome, " << username << "!";

    cout << "\nChoose a game setting: ";
    cout << "\nQuick - Start with $100. Win or lose, the game is over fast";
    cout << "\n\nLong - Start with $1000. This difficulty setting going to take a while. You can win bigger and lose bigger, but unless you go all in, you're in it for a long while";
    cout << "\n\nCEO - Start with $100000. Need to kill four hours at the airport? This is the difficulty for you. Everyone is rich and looking to get richer.";
    string difficultyChoice;
    difficultyValue dv;
    do {
        cout << "\n\nPick a difficulty level: ";
        cin >> difficultyChoice;
		difficultyChoice = toLower(difficultyChoice);
        dv = s_difficultyMappings[difficultyChoice];
    } while (dv == dv_undefined);

    int startingBalance = s_balanceMappings[dv];

    Player mainPlayer(username, startingBalance);
    Player* players[numOfPlayers + 1];
    players[0] = &mainPlayer;
    int playerName;

    for (int i = 1; i <= numOfPlayers; i++) {
        playerName = rand() % 11;
        players[i] = new Player(names[playerName], startingBalance);
    }

    help();
    rules();

    int remainingPlayers = numOfPlayers;
    while (1) {
        for (int i = 0; i <= remainingPlayers;) {
            if (players[i]->balance <= 0)
            {
                if (i == 0) {
					cout << "\n\t\t========== GAME OVER =========";
					cout << "\nYou have lost all your money and been asked to leave the casino";
					cout << "\nPress return to quit...";
                    _getch();
					system("cls");
					return 0;
                }
                cout << players[i]->name << " has run out of money and is being escorted from the premises\n";
                for (int j = i; j <= numOfPlayers; j++) {
                    players[j] = players[j + 1];
                }

                remainingPlayers--;
            }
            else {
                i++;
            }
        }

        if (remainingPlayers == 1) {
			cout << "\n\t\t========== YOU WIN =========";
            int diceRoll = rand() % 1000000 + 1;
            if (diceRoll == 6) {
                cout << "\nYou have out-gambled the four old people who frequent this casino and taken their life savings. "; 
				this_thread::sleep_for(chrono::seconds(2));
                cout << "\nI hope you feel good about yourself...";
				this_thread::sleep_for(chrono::seconds(5));
            }
            else {
                cout << "\nCongratulations, you win! Come back some other time and play again";
            }
            cout << "\nPress return to quit...";
			_getch();
            system("cls");
            return 0;
        }
        else {
			cout << "\n\t\t========== CASINO FLOOR =========\n";
			for (int i = 0; i <= remainingPlayers; i++) {
                cout << players[i]->name << " - $" << players[i]->balance << "\n";
			}
        }
        
        string action;
        cout << "\n>_ ";
        cin >> action;
        action = toLower(action);

        switch (s_actionMappings[action]) {
        case av_play: {
            int numChoice;
            int pot = 0;
            do {
				cout << "Pick a whole number between 2 and 12 ";
                cin.clear();
                cin.ignore(256, '\n');
            } while (!(cin >> numChoice || cin.get() != '\n') || !(numChoice >= 2 && numChoice <= 12));
            mainPlayer.currentBet = numChoice;

            cout << "You have $" << mainPlayer.balance << " to bet\n";
            int gamble;
            do {
				cout << "How much money do you want to bet $";
                cin.clear();
                cin.ignore(256, '\n');
            } while (!(cin >> gamble || cin.get() != '\n') || !(gamble > 0 && gamble <= mainPlayer.balance));

            mainPlayer.currentGamble = gamble;

            pot += gamble;
            cout << "\nYou have put $" << gamble << " on the number " << numChoice << " being rolled...\n";

            for (int i = 1; i <= remainingPlayers; i++) {
                players[i]->currentBet = rand() % 12 + 2;
                players[i]->currentGamble = rand() % players[i]->balance + 1;
                cout << players[i]->name <<  " bet $" << players[i]->currentGamble << " on the number " << players[i]->currentBet << "\n";
                pot += players[i]->currentGamble;
            }

            cout << "\nThere is a total of $" << pot << " in the pot\n";

            cout << "Rolling die...\n";

            int sleepSeconds = rand() % 4 + 1;
            this_thread::sleep_for(chrono::seconds(sleepSeconds));
            int diceOne = rand() % 6 + 1;
            cout << diceOne;

            this_thread::sleep_for(chrono::seconds(2));

            cout << " and ";
            sleepSeconds = rand() % 4 + 1;
            this_thread::sleep_for(chrono::seconds(sleepSeconds));

            int diceTwo = rand() % 6 + 1;
            cout << diceTwo << "... ";
            int diceTotal = diceOne + diceTwo;
            cout << "for a total of " << diceTotal << "!\n";

            int smallestDelta = 10000;
            list<Player*> winners;
            list<Player*> losers;
            for (int i = 0; i <= remainingPlayers; i++) {
                int currentDelta = abs(players[i]->currentBet - diceTotal);
                if (currentDelta < smallestDelta) { // if two players make a winning bet, whoever is last in the list will win
                    winners.clear();
                    smallestDelta = currentDelta;
                    winners.push_back(players[i]);
                }
                else if (currentDelta == smallestDelta)
                {
                    winners.push_back(players[i]);
                }
            }

            for (int i = 0; i <= remainingPlayers; i++) {
                if (find(winners.begin(), winners.end(), players[i]) == winners.end())
                    players[i]->balance -= players[i]->currentGamble;
            }

            int potSplit = winners.size();
            for (std::list<Player*>::const_iterator li = winners.begin(); li != winners.end(); li++) {
                int winnings = int(pot / potSplit);
                cout << (*li)->name << " wins $" << winnings << "\n";
                (*li)->balance += winnings;
            }

            break;
        }

        case av_help: {
            help();
            break;
        }

        case av_rules: {
            rules();
            break;
        }

        case av_quit:{ 
            string certain;
            cout << "Are you sure you want to quit? (y or n) ";
            cin >> certain;
            certain = toLower(certain);
            if (certain == "y") {
                return 0;
            }
            else {
                cout << "\nCancelling shutdown...\n";
				break;
            }
        }

        default: {
            cout << "\nInvalid command";
            break;
        }
        }
    }
	return 0;
}
