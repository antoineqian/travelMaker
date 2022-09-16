#ifndef RESERVATION_H_
#define RESERVATION_H_
#include <string>
#include <memory>
#include <vector>
#include <sstream>
using std::ostringstream;
using std::shared_ptr;
using std::string;
using std::vector;

class Reservation
{
public:
    virtual double totalCost() const = 0;

    virtual string toString() const = 0;

    virtual ~Reservation()
    {
    }
};

class Itinerary : public Reservation
{
private:
    vector<shared_ptr<Reservation>> reservations;

public:
    void add(const shared_ptr<Reservation> &reservation)
    {
        reservations.push_back(reservation);
    }

    void clear()
    {
        reservations.clear();
    }

    virtual double totalCost() const override
    {
        double cost = 0;

        for (const shared_ptr<Reservation> reservation : reservations)
            cost += reservation->totalCost();

        return cost;
    }

    const vector<shared_ptr<Reservation>> &getReservations() const
    {
        return reservations;
    }

    virtual string toString() const override
    {
        ostringstream oss;

        oss << "Your itinerary consists of " << reservations.size() << " reservations\n";

        for (const shared_ptr<Reservation> reservation : reservations)
            oss << reservation->toString() << '\n';

        oss << "The total cost is " << totalCost() << '\n';
        return oss.str();
    }
};

#endif /** RESERVATION_H_ **/