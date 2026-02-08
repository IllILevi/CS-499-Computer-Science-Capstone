#include "Monkey.h"
#include "TrainingStatus.h"
#include "Validation.h"
#include <utility>

// Constructor: initializes Monkey with all required attributes
Monkey::Monkey(std::string name, std::string species, std::string gender, std::string tailLength, std::string height, std::string bodyLength,
	std::string age, std::string weight, std::string acquisitionDate, std::string acquisitionCountry, std::string inServiceCountry,
	TrainingStatus ts, bool reserved)
	: RescueAnimal(std::move(name), std::move(gender), std::move(age), std::move(weight), std::move(acquisitionDate),
		std::move(acquisitionCountry), std::move(inServiceCountry), ts, reserved),
	species_(std::move(species)),
	tailLength_(std::move(tailLength)),
	height_(std::move(height)),
	bodyLength_(std::move(bodyLength))
{
	// Enforces invariants
	requireNonEmpty(name_, "Name");
	requireNonEmpty(species_, "Species");
	requireNonEmpty(gender_, "Gender");

	requirePositive(tailLength_, "Tail length");
	requirePositive(height_, "Height");
	requirePositive(bodyLength_, "Body length");
	requirePositive(age_, "Age");
	requirePositive(weight_, "Weight");

	requireNonEmpty(acquisitionCountry_, "Acquisition country");
	requireNonEmpty(inServiceCountry_, "In service country");
}

// Prints monkey information in formatted string
void Monkey::print(std::ostream& os) const {
	os << "Monkey | Name: " << name_
		<< " | species: " << species_    // THESE SHOULD NOT BE MEMBER VARIABLES THEY SHOULD BE THE GETTERS
		<< " | Height: " << height_
		<< " | Tail length: " << tailLength_
		<< " | Body length: " << bodyLength_
		<< " | Status: " << toString(trainingStatus_)
		<< " | AcquisitionCountry: " << acquisitionCountry_
		<< " | Reserved: " << (reserved_ ? "Yes" : "No");
};