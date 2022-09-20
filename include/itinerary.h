#ifndef ITINERARY_H_
#define ITINERARY_H_
#include "reservation.h"
#include <memory>
#include <vector>
#include <sstream>
using std::ostringstream;
using std::shared_ptr;
using std::vector;

class Itinerary : public Reservation
{
private:
    vector<shared_ptr<Reservation>> reservations;

public:
    void add(const shared_ptr<Reservation> &reservation);

    void clear();

    virtual double totalCost() const override;

    const vector<shared_ptr<Reservation>> &getReservations() const;

    virtual string toString() const override;
};

#endif /** ITINERARY_H_ **/