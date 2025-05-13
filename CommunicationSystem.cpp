#include "Stronghold.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

CommunicationSystem::CommunicationSystem(){
    fileName = "";
    logCount=0;
}

CommunicationSystem::CommunicationSystem(const string& file) {
    fileName = file;
    logCount = 0;
}


void CommunicationSystem::sendMessage(const string& sender, const string& receiver, const string& message) {
    string logEntry = sender + " to " + receiver + ": " + message;

    
    if (logCount < 100) {
        inMemLog[logCount++] = logEntry;
    } else {
        cout << "In-memory log is full, cannot store more messages.\n";
    }

    
    ofstream outFile(fileName, ios::app); 
    if (outFile.is_open()) {
        outFile << logEntry << endl;
        outFile.close();
    } else {
        cout << "Error opening file to save message.\n";
    }
}


void CommunicationSystem::showInMemChat() const {
    cout << "\n=== In-Memory Chat ===\n";
    if (logCount == 0) {
        cout << "No messages in memory.\n";
    } else {
        for (int i = 0; i < logCount; ++i) {
            cout << inMemLog[i] << endl;
        }
    }
}


void CommunicationSystem::showFileChat() const {
    cout << "\n=== File Chat History ===\n";
    ifstream inFile(fileName);
    if (inFile.is_open()) {
        string line;
        while (getline(inFile, line)) {
            cout << line << endl;
        }
        inFile.close();
    } else {
        cout << "Error opening file to read chat history.\n";
    }
}