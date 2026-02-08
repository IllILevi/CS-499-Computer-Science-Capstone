#include <string>
#include <utility>

#include "RescueAnimal.h"
#include "TrainingStatus.h"

RescueAnimal::RescueAnimal(std::string name, std::string gender, std::string age, std::string weight, std::string acquisitionDate,
	std::string acquisitionCountry, std::string inServiceCountry, TrainingStatus ts, bool reserved)
	: name_(move(name)),
	gender_(move(gender)),
	age_(move(age)),
	weight_(move(weight)),
	acquisitionDate_(move(acquisitionDate)),
	acquisitionCountry_(move(acquisitionCountry)),
	inServiceCountry_(move(inServiceCountry)),
	trainingStatus_(ts),
	reserved_(reserved) {}

void RescueAnimal::print(std::ostream& os) const {
	os << "Name: " << name_
		<< "| status: " << toString(trainingStatus_)
		<< "| Acquisition Country: " << acquisitionCountry_
		<< "| Reserved: " << (reserved_ ? "Yes" : "No");
}

std::ostream& operator<<(std::ostream& os, RescueAnimal  const& a) {
	a.print(os);
	return os;
}