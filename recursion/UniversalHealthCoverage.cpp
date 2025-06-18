#include "simpio.h"
#include <iostream>
#include "set.h"
#include "vector.h"

using namespace std;

bool canOfferUniversalCoverage(Set<string>& cities, Vector<Set<string> >& locations,
                               int numHospitals, Vector<Set<string> >& result);

int main() {
    Set<string> cities;
	cities += "A", "B", "C", "D", "E", "F";

	int numHospitals = getInteger("Enter number of hospitals: ");

	Vector<Set<string> > locations(numHospitals);
	Set<string> set;
	for (int i = 0; i < 4; i++){
		locations.add(set);
	}
	locations[0] += "A", "B", "C", "F";
	locations[1] += "A", "C", "D", "E";
	locations[2] += "B", "F";
	locations[3] += "C", "E", "F";

	Vector<Set<string> > result(numHospitals);


	if(canOfferUniversalCoverage(cities, locations, numHospitals, result)){
		cout << "it is possible" << endl;
	} else {
		cout << "it is not possible" << endl;
	}
	system("pause");
    return 0;
}
bool canOfferUniversalCoverage(Set<string>& cities,
                               Vector< Set<string> >& locations,
                               int numHospitals,
                               Vector< Set<string> >& result) {
    if (cities.isEmpty()) {
        return true;
    }
    if (numHospitals == 0 || locations.isEmpty()) {
        return false;
    }

    Set<string> res;
    for (int i = 0; i < numHospitals; i++) {
        res += result[i];
    }
    if (cities.isSubsetOf(res)) {
        return true; 
    }

    for (int i = 0; i < numHospitals; i++) {
        if (result[i].isEmpty()) { 
            for (int k = 0; k < locations.size(); k++) {
                result[i] = locations[k];
                if (canOfferUniversalCoverage(cities, locations, numHospitals, result)) {
                    return true;
                }
                result[i] = Set<string>();
            }
            break;
        }
	}
    return false;
}

