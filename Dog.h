#pragma once
#include "RescueAnimal.h"
#include <string>

// Dog class inherits from RescueAnimal, adds breed-specific functionality
class Dog : public RescueAnimal {
private:
	std::string breed_; // Dog's breed information

public:
	// Constructor with default training status and reservation
	Dog(std::string name, std::string breed, std::string gender, std::string age, std::string weight, std::string acquisitionDate,
		std::string acquisitionCountry, std::string inServiceCountry, TrainingStatus ts = TrainingStatus::Intake, bool reserved = false);

	// Getter for breed
	//const std::string& breed() const noexcept { return breed_; }

	// Override print function for dog-specific output
	void print(std::ostream& os) const override;
};
