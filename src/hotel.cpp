#include "hotel.h"

/**
 *
 * HotelRoom
 *
 */
HotelRoom::HotelRoom(string name, double price)
    : hotelName(name), pricePerNight(price){};

string HotelRoom::toString() const
{
    ostringstream oss;
    oss << "Hotel: " << hotelName << '\n';
    oss << "Price per night: " << pricePerNight;
    return oss.str();
}

double HotelRoom::getPricePerNight() const { return pricePerNight; }

const string &HotelRoom::getHotelName() const { return hotelName; }

/**
 *
 * HotelRequest
 *
 */
HotelRequest::HotelRequest(string &fromDate, string &toDate, string &city, int guests)
    : fromDate(fromDate), toDate(toDate), city(city), guests(guests){};

int HotelRequest::getTotalNights() const
{
    // Dummy
    return 3;
}

int HotelRequest::getGuests() const { return guests; }

const string &HotelRequest::getCity() const { return city; }

const string &HotelRequest::getFromDate() const { return fromDate; }

const string &HotelRequest::getToDate() const { return toDate; }

/**
 *
 * HotelReservation
 *
 */
HotelReservation::HotelReservation(const HotelRequest &request, const HotelRoom &room)
    : request(request), room(room) {}

double HotelReservation::totalCost() const
{
    return room.getPricePerNight() * request.getTotalNights();
}

string HotelReservation::toString() const
{
    ostringstream oss;
    oss << "Hotel reservation: " << room.getHotelName() << ": " << request.getCity() << '\n';
    oss << "\t" << request.getFromDate() << " to " << request.getToDate() << " : " << request.getTotalNights() << '\n';
    oss << "\t"
        << "For " << request.getGuests() << " people. \n";
    oss << "\tTotal Cost: " << totalCost() << '\n';

    return oss.str();
}

const HotelRequest &HotelReservation::getRequest() const { return request; }

const HotelRoom &HotelReservation::getRoom() const { return room; }

/**
 *
 * NaebaPrinceManager
 *
 */
string NaebaPrinceManager::getName() const
{
    return "Naeba Prince";
}

vector<HotelRoom> NaebaPrinceManager::searchRooms(HotelRequest req)
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

bool NaebaPrinceManager::bookRoom(const HotelReservation &reservation) const
{
    return true;
}

/**
 *
 * CosmoSantsManager
 *
 */
string CosmoSantsManager::getName() const
{
    return "Cosmo Sants";
}

vector<HotelRoom> CosmoSantsManager::searchRooms(HotelRequest req)
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

bool CosmoSantsManager::bookRoom(const HotelReservation &reservation) const
{
    return true;
}

/**
 *
 * HotelManagerFactory
 *
 */
vector<IHotelManager *> HotelManagerFactory::getManagers()
{
    return vector<IHotelManager *>{new NaebaPrinceManager(), new CosmoSantsManager()};
}

IHotelManager *HotelManagerFactory::getManager(const string &name)
{
    for (IHotelManager *m : HotelManagerFactory::getManagers())
    {
        if (m->getName() == name)
            return m;
    }
    return nullptr;
}