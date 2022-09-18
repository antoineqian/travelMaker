#ifndef HOTEL_H_
#define HOTEL_H_

#include <vector>
#include <string>
#include "reservation.h"
using std::ostringstream;
using std::string;
using std::vector;

class NaebaPrinceRoom
{
public:
    double pricePerNight;
};

class NaebaPrinceAPI
{
public:
    static vector<NaebaPrinceRoom> getAvailableRooms(int beds)
    {
        vector<NaebaPrinceRoom> rooms;

        rooms.push_back({50});
        rooms.push_back({60});
        rooms.push_back({130});

        return rooms;
    }
};

class CosmoSantsApartment
{
public:
    double nightlyPrice;
};

class CosmoSantsAPI
{
public:
    static vector<CosmoSantsApartment> findApartments(int persons)
    {
        vector<CosmoSantsApartment> apts;

        apts.push_back({55});
        apts.push_back({65});
        apts.push_back({135});

        return apts;
    }
};

////////
class HotelRoom
{
private:
    string hotelName;
    double pricePerNight;

public:
    explicit HotelRoom(string name, double price) : hotelName(name), pricePerNight(price){};
    string toString() const
    {
        ostringstream oss;
        oss << "Hotel: " << hotelName << '\n';
        oss << "Price per night: " << pricePerNight;
        return oss.str();
    }

    double getPricePerNight() const { return pricePerNight; }

    const string &getHotelName() const { return hotelName; }
};

class HotelRequest
{
private:
    string fromDate;
    string toDate;
    string city;
    int guests;

public:
    explicit HotelRequest(string &fromDate, string &toDate, string &city, int guests) : fromDate(fromDate), toDate(toDate), city(city), guests(guests){};

    int getTotalNights() const
    {
        // Dummy
        return 3;
    }

    int getGuests() const { return guests; }

    const string &getCity() const { return city; }

    const string &getFromDate() const { return fromDate; }

    const string &getToDate() const { return toDate; }
};

class HotelReservation : public Reservation
{
private:
    HotelRequest request;
    HotelRoom room;

public:
    explicit HotelReservation(const HotelRequest &request, const HotelRoom &room) : request(request), room(room)
    {
    }

    virtual double totalCost() const override
    {
        return room.getPricePerNight() * request.getTotalNights();
    }

    virtual string toString() const override
    {
        ostringstream oss;
        oss << "Hotel reservation: " << room.getHotelName() << ": " << request.getCity() << '\n';
        oss << "\t" << request.getFromDate() << " to " << request.getToDate() << " : " << request.getTotalNights() << '\n';
        oss << "\t"
            << "For " << request.getGuests() << " people. \n";
        oss << "\tTotal Cost:" << totalCost() << '\n';

        return oss.str();
    }

    const HotelRequest &getRequest() const { return request; }

    const HotelRoom &getRoom() const { return room; }
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
    virtual string getName() const override
    {
        return "Naeba Prince";
    }

    virtual vector<HotelRoom> searchRooms(HotelRequest req) override
    {
        vector<NaebaPrinceRoom> results = NaebaPrinceAPI::getAvailableRooms(req.getGuests());
        vector<HotelRoom> rooms;

        for (auto &result : results)
        {
            HotelRoom room(getName(), result.pricePerNight);
            rooms.push_back(room);
        }
        return rooms;
    }

    virtual bool bookRoom(const HotelReservation &reservation) const override
    {
        return true;
    }
};

class CosmoSantsManager : public IHotelManager
{
public:
    virtual string getName() const override
    {
        return "Cosmo Sants";
    }

    virtual vector<HotelRoom> searchRooms(HotelRequest req) override
    {
        vector<CosmoSantsApartment> results = CosmoSantsAPI::findApartments(req.getGuests());
        vector<HotelRoom> rooms;

        for (auto &result : results)
        {
            HotelRoom room(getName(), result.nightlyPrice);
            rooms.push_back(room);
        }
        return rooms;
    }
    virtual bool bookRoom(const HotelReservation &reservation) const override
    {
        return true;
    }
};

class HotelManagerFactory
{
public:
    static vector<IHotelManager *> getManagers()
    {
        return vector<IHotelManager *>{new NaebaPrinceManager(), new CosmoSantsManager()};
    }

    static IHotelManager *getManager(const string &name)
    {
        for (IHotelManager *m : HotelManagerFactory::getManagers())
        {
            if (m->getName() == name)
                return m;
        }
        return nullptr;
    }
};

#endif /** HOTEL_H_ **/