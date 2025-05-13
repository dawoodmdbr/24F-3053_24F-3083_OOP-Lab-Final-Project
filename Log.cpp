#include "Stronghold.h"
#include <fstream>
#include <ctime>

void Logger::logGameStart(bool isMultiplayer, const string& player1, const string& player2) {
    std::ofstream logFile("game_sessions.txt", ios::app);
    if (!logFile.is_open()) return;
    time_t now = time(0);
    char timeStr[26];
    ctime_s(timeStr, sizeof(timeStr), &now);

    logFile << "=== GAME START ===\n";
    logFile << "Time: " << timeStr;
    logFile << "Mode: " << (isMultiplayer ? "Multiplayer" : "Singleplayer") << "\n";

    if (isMultiplayer) {
        logFile << "Players: " << player1 << " vs " << player2 << "\n";
    }
    else {
        logFile << "Player: " << player1 << "\n";
    }
    logFile << "==================\n\n";
}
