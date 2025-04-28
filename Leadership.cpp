#include "Stronghold.h"
Leadership::Leadership(const string& name) {
	leaderName = name;
	leadershipStyle = 0; // autocratic=0,democratic=1
	popularity = 50.0; 
}
void Leadership::update(Kingdom& kingdom) {
	if (leadershipStyle == 0) { 
		popularity -= 0.1; //decreases popularity of leader in autocratic systems
	}
	else { 
		popularity += 0.1; //increases popularity of leader in democratic systems
	}
	if (popularity < 0) {
		popularity = 0;
	}
	if (popularity > 100) {
		popularity = 100;
	}
}
void Leadership::holdElection(Kingdom& kingdom) {
	if (leadershipStyle == 1) { 
		if (popularity < 50) {
			changeLeader("New Elected Leader", 1); 
		}
	}
}
void Leadership::initiateCoup(Kingdom& kingdom) {
	if (leadershipStyle == 0) { 
		changeLeader("New Coup Leader", 0);
	}
}
void Leadership::changeLeader(const string& newName, int style) {
	leaderName = newName;
	leadershipStyle = style;//autocratic or democratic
	popularity = 50.0;
}
void Leadership::affectPopularity(double amount) {
	popularity += amount;
	if (popularity < 0) {
		popularity = 0;
	}
	if (popularity > 100) {
		popularity = 100;
	}
}
string Leadership::getLeaderName() const {
	return leaderName;
}
int Leadership::getLeadershipStyle() const {
	return leadershipStyle;
}
double Leadership::getPopularity() const {
	return popularity;
}


