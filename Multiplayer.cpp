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
