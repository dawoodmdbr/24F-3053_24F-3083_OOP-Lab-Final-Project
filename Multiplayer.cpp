#include "Stronghold.h"
#include <string>
#include <iostream>

using namespace std;

MultiplayerSystem::MultiplayerSystem()
    : isPlayer1Turn(true), currentTurn(1), player1Name("Player 1"), player2Name("Player 2") {}

void MultiplayerSystem::startGame() {
    cout << "=== MULTIPLAYER MODE ===" << endl;

    cout << "Player 1, enter your name: ";
    cin.ignore();
    getline(cin, player1Name);

    cout << "Player 2, enter your name: ";
    getline(cin, player2Name);
    player1 = Kingdom();
    player2 = Kingdom();
    Logger logger;
    logger.logGameStart(true, player1Name, player2Name);
    cout << endl << "Game started! " << player1Name << " goes first." << endl;
}

void MultiplayerSystem::switchTurn() {
    isPlayer1Turn = !isPlayer1Turn;
    if (isPlayer1Turn) {
        currentTurn++;
        cout << endl << "=== TURN " << currentTurn << " ===" << endl;
    }
}
void MultiplayerSystem::communicationMenu() {
    int choice;
    string message;
    string& currentPlayer = isPlayer1Turn ? player1Name : player2Name;
    string& opponentPlayer = isPlayer1Turn ? player2Name : player1Name;

    cout << "\n--- Communication Menu ---\n";
    cout << "1. Check last message\n";
    cout << "2. Send message \n";
    cout << "0. Back\n";
    cout << "Choice: ";
    cin >> choice;
    cin.ignore();

    switch (choice) {
    case 1:
        if (getCurrentPlayer().lastReceivedMessage.empty()) {
            cout << "No messages received.\n";
        }
        else {
            cout << "\n--- Inbox --- \n";
            cout << getCurrentPlayer().lastReceivedMessage << "\n";

            cout << "\nReply? (Y/N): ";
            char reply;
            cin >> reply;
            cin.ignore();

            if (toupper(reply) == 'Y') {
                cout << "Enter reply: ";
                getline(cin, message);
                getOpponentPlayer().lastReceivedMessage = message;
                cout << "Reply sent!\n";
            }
        }
        break;

    case 2:
        cout << "Enter message: ";
        getline(cin, message);
        getOpponentPlayer().lastReceivedMessage = message;
        cout << "Message sent.\n";
        break;

    case 0:
        return;

    default:
        cout << "Invalid choice.\n";
    }
}
void MultiplayerSystem::processCurrentTurn() {
    Kingdom& current = getCurrentPlayer();
    current.update();
    current.getTradeSystem().updateMarket();
    current.handleEvents();
}

Kingdom& MultiplayerSystem::getCurrentPlayer() {
    return isPlayer1Turn ? player1 : player2;
}

Kingdom& MultiplayerSystem::getOpponentPlayer() {
    return isPlayer1Turn ? player2 : player1;
}

string MultiplayerSystem::getCurrentPlayerName() const {
    return isPlayer1Turn ? player1Name : player2Name;
}

bool MultiplayerSystem::isCurrentPlayer1() const {
    return isPlayer1Turn;
}

int MultiplayerSystem::getCurrentTurn() const {
    return currentTurn;
}
