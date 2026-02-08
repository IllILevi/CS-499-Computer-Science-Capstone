#include "Dog.h"
#include "TrainingStatus.h"
#include "Validation.h"
#include <utility>

// Constructor: initializes Dog with all required attributes
Dog::Dog(std::string name, std::string breed, std::string gender, std::string age, std::string weight, std::string acquisitionDate,
	std::string acquisitionCountry, std::string inServiceCountry, TrainingStatus ts, bool reserved)
	: RescueAnimal(std::move(name), std::move(gender), std::move(age), std::move(weight), std::move(acquisitionDate),
		std::move(acquisitionCountry), std::move(inServiceCountry), ts, reserved),
	breed_(std::move(breed)) 
{
	// Enforces invariants
	requireNonEmpty(name_, "Name");
	requireNonEmpty(breed_, "Breed");
	requireNonEmpty(gender_, "Gender");
	
	requirePositive(age_, "Age");
	requirePositive(weight_, "Weight");

	requireNonEmpty(acquisitionCountry_, "Acquisition country");
	requireNonEmpty(inServiceCountry_, "In service country");
}

// Prints dog information in formatted string
void Dog::print(std::ostream& os) const {
	os << "Dog | Name: " << name_
		<< " | Breed: " << breed_  //THESE SHOULD NOT BE MEMBER VARIABLES THEY SHOULD BE THE GETTERS
		<< " | Status: " << toString(trainingStatus_)
		<< " | AcquisitionCountry: " << acquisitionCountry_
		<< " | Reserved: " << (reserved_ ? "Yes" : "No");
};