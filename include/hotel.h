#ifndef HOTEL_H_
#define HOTEL_H_
#include "itinerary.h"
#include "cosmosants.h"
#include "naebaprince.h"

class HotelRoom
{
private:
    string hotelName;
    double pricePerNight;

public:
    explicit HotelRoom(string name, double price);
    string toString() const;

    double getPricePerNight() const;

    const string &getHotelName() const;
};

class HotelRequest
{
private:
    string fromDate, toDate, city;
    int guests;

public:
    explicit HotelRequest(string &fromDate, string &toDate, string &city, int guests);

    int getTotalNights() const;

    int getGuests() const;

    const string &getCity() const;

    const string &getFromDate() const;

    const string &getToDate() const;
};

class HotelReservation : public Reservation
{
private:
    HotelRequest request;
    HotelRoom room;

public:
    explicit HotelReservation(const HotelRequest &request, const HotelRoom &room);

    virtual double totalCost() const override;

    virtual string toString() const override;

    const HotelRequest &getRequest() const;

    const HotelRoom &getRoom() const;
};

class IHotelManager
{
public:
    virtual string getName() const = 0;

    virtual vector<HotelRoom> searchRooms(HotelRequest req) = 0;

    virtual bool bookRoom(const HotelReservation &reservation) const = 0;
};

class NaebaPrinceManager : public IHotelManager
{
public:
    virtual string getName() const override;

    virtual vector<HotelRoom> searchRooms(HotelRequest req) override;

    virtual bool bookRoom(const HotelReservation &reservation) const override;
};

class CosmoSantsManager : public IHotelManager
{
public:
    virtual string getName() const override;

    virtual vector<HotelRoom> searchRooms(HotelRequest req) override;

    virtual bool bookRoom(const HotelReservation &reservation) const override;
};

class HotelManagerFactory
{
public:
    static vector<IHotelManager *> getManagers();

    static IHotelManager *getManager(const string &name);
};

#endif /** HOTEL_H_ **/