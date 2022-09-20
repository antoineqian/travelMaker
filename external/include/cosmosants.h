#include <vector>
using std::vector;

class CosmoSantsApartment
{
public:
    double nightlyPrice;
};

class CosmoSantsAPI
{
public:
    static vector<CosmoSantsApartment> findApartments(int persons);
};