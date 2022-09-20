#ifndef RESERVATION_H_
#define RESERVATION_H_
#include <string>
using std::string;

class Reservation
{
public:
    virtual double totalCost() const = 0;

    virtual string toString() const = 0;

    virtual ~Reservation()
    {
    }
};

#endif /** RESERVATION_H_ **/