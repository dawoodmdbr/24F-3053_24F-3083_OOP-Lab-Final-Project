#include "Stronghold.h"
#include <random>
#include <iostream>

Bank::Bank() : loanAmount(0.0), interestRate(5.0), treasuryBalance(5000.0), fraudDetected(false) {}

Bank::Bank(double loan, double interest, double balance) : 
    loanAmount(loan), 
    interestRate(interest), 
    treasuryBalance(balance),
    fraudDetected(false) {}

void Bank::setLoanAmount(double a) {
    loanAmount = a;
}

void Bank::issueLoan(double amount) {
    if (amount <= 0 || amount > treasuryBalance) {
        return;
    }
    loanAmount += amount;
    treasuryBalance -= amount;
    if (amount > treasuryBalance * 0.5) {
        corruptionLevel += 0.1;
        if (corruptionLevel > 1.0) {
            corruptionLevel = 1.0;
        }
    }
}

void Bank::repayLoan(double amount) {
    if (amount <= 0) {
        return;
    }
    double repayment = (amount > loanAmount) ? loanAmount : amount;
    loanAmount -= repayment;
    treasuryBalance += repayment;
    if (repayment >= loanAmount * 0.2) {
        corruptionLevel -= 0.05;
        if (corruptionLevel < 0.0) {
            corruptionLevel = 0.0;
        }
    }
}

void Bank::detectFraud() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 99);
    
    double detectionThreshold = 1000.0 - (corruptionLevel * 400);
    if (treasuryBalance < detectionThreshold) {
        fraudDetected = true;
        corruptionLevel *= 0.6;
    }
    if (dis(gen) < (10 + (corruptionLevel * 15))) {
        fraudDetected = true;
    }
}

void Bank::update(Kingdom& kingdom) {
    if (fraudDetected) {
        treasuryBalance -= 1000.0;
        fraudDetected = false;
    }
    applyInterest();
    auditTreasury();
    if (corruptionLevel > 0.5) {
        treasuryBalance -= 500.0;
    }
}

void Bank::auditTreasury() {
    detectFraud();
}

void Bank::applyInterest() {
    loanAmount += loanAmount * (interestRate / 100.0);
}