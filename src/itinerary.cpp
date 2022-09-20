#include "itinerary.h"

void Itinerary::add(const shared_ptr<Reservation> &reservation)
{
    reservations.push_back(reservation);
}

void Itinerary::clear()
{
    reservations.clear();
}

double Itinerary::totalCost() const
{
    double cost = 0;

    for (const shared_ptr<Reservation> &reservation : reservations)
        cost += reservation->totalCost();

    return cost;
}

const vector<shared_ptr<Reservation>> &Itinerary::getReservations() const
{
    return reservations;
}

string Itinerary::toString() const
{
    ostringstream oss;

    oss << "Your itinerary consists of " << reservations.size() << " reservations\n";

    for (const shared_ptr<Reservation> &reservation : reservations)
        oss << reservation->toString() << '\n';

    oss << "The total cost is " << totalCost() << '\n';
    return oss.str();
}