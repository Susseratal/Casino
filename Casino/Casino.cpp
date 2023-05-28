#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <time.h>
#include <stdlib.h>

using namespace std;

class Player {
public:
    string name;
    int balance;

    Player(string newName) {
        name = newName;
        balance = 1000;
    }
};

void rules()
{
    // system("cls");
    cout << "\n\t\t========== CASINO RULES =========";
    cout << "\n0 - You have $1000";
    cout << "\n1 - Rock up to a table and place a bet, the other players will place a bet too";
    cout << "\n2 - The dice will roll";
    cout << "\n3 - Winner gets the pot";
    cout << "\n4 - If you run out of money, you will be asked to leave";
    cout << "\n5 - At the end, a scoreboard will be displayed\n";
}

int main()
{
    /* Initialise the random seed */
    srand(time(NULL));
    const int maxPlayers = 11;

    string names[maxPlayers] = {"Howard", "Rodney", "Ethel", "Diane", "Craig", "Albert", "Brenda", "Paula", "Jeremy", "Thomas", "Katherine"};
    
    // Create the player character
    string username;
    system("cls");
    cout << "\n\t\t========== POT LUCK CASINO =========";
    cout << "\nPlease register at the front desk\n";
    cout << "Enter your name: ";
    cin >> username;
    cout << "\nWelcome, " << username << "!\n";
    Player mainPlayer(username);

    int numOfPlayers = rand() % 3 + 9;

    Player* players[maxPlayers];

    for (int i = 0; i < numOfPlayers; i++) {
        players[i] = new Player(names[i]);
    }

    rules();

    while (1) {
        if (mainPlayer.balance <= 0) {
			cout << "\n\t\t========== GAME OVER =========";
            cout << "\nYou have lost all your money and been asked to leave the casino";
            break;
        }

        cout << "\n\t\t========== CASINO FLOOR =========";
        cout << "\nName: " << mainPlayer.name;
        cout << "\nBalance: $" << mainPlayer.balance << "\n";

        // ok now prompt for stuff
        // maybe want play, rules or quit?
        // switch case probably i can't remember

        /*
        * Main game loop goes here
        * Game loop consists of starting a round
        * Player places a bet on a number
        *   - NPC's place a bet
        * Dice are rolled
        * Whoever gets closest to the number wins the pot. If there are joint winners, the pot is split
        * If a player runs out of money, they are asked to leave the establishment
        */
    }
    return 0;
}


/* 
* When you start a round of a game, the other casino goers are distributed to other tables, as well as joining the player's
* You make a bet, the wheel is spun and whoever wins the game gets the pot
*/
