#ifndef USER_H_
#define USER_H_
#include "itinerary.h"
#include "utils.h"
class User
{
public:
    User(const User &) = delete;
    void operator=(const User &) = delete;
    explicit User(const string &username, const string &password);

    string getUsername() const;

    string getPassword() const;

    const vector<Itinerary> getItineraries();

    void addItinerary(const Itinerary &itinerary);

private:
    vector<Itinerary> itineraries;
    string username;
    string password;
};

#endif /** USER_H_ **/