#include "user.h"

User::User(const string &username, const string &password)
{
    this->username = username;
    this->password = password;
};

string User::getUsername() const { return username; }

string User::getPassword() const { return password; }

const vector<Itinerary> User::getItineraries() { return itineraries; };

void User::addItinerary(const Itinerary &itinerary)
{
    itineraries.push_back(itinerary);
}