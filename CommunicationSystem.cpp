#include"Stronghold.h"
#include <iostream>

CommunicationSystem::CommunicationSystem(){
    fileName = "chat_log.txt";
    logCount = 0;
}
void CommunicationSystem::sendMessage(const string& sender, const string& receiver, const string& message){
    string formatted = sender + " to " + receiver + ": " + message;

    if(logCount < 100){
        inMemLog[logCount] = formatted;
        logCount++;
    } else {
        cout << "In-memory log is full. Cannot send more messages." << endl;
    }

    ofstream file(fileName, ios::app);
    if(file.is_open()){
        file << formatted << endl;
        file.close();
    } else {
        cout << "Error opening file for writing." << endl;
    }   
}

void CommunicationSystem::showInMemChat() const{
    cout << "In-Memory Chat Log:" << endl;
    for(int i = 0; i < logCount; i++){
        cout << inMemLog[i] << endl;
    }
}

void CommunicationSystem::showFileChat() const{
    cout << "File Chat Log:" << endl;
    ifstream file(fileName);
    if(file.is_open()){
        string line;
        while(getline(file, line)){
            cout << line << endl;
        }
        file.close();
    } else {
        cout << "Error opening file for reading." << endl;
    }
}