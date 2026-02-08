#pragma once
#include "RescueAnimal.h"
#include <string>

// Monkey class inherits from RescueAnimal, adds monkey-specific functionality
class Monkey : public RescueAnimal {
private:
	// Monkey exclusive information
	std::string tailLength_;
	std::string height_;
	std::string bodyLength_;
	std::string species_;

public:
	// Constructor with default training status and reservation
	Monkey(std::string name, std::string species, std::string gender, std::string tailLength, std::string height, std::string bodyLength,
		std::string age, std::string weight, std::string acquisitionDate, std::string acquisitionCountry, std::string inServiceCountry,
		TrainingStatus ts = TrainingStatus::Intake, bool reserved = false);
	
	// Getter functions for private variables
	const std::string& tailLength() const noexcept { return tailLength_; }
	const std::string& height() const noexcept { return height_; }
	const std::string& bodyLength() const noexcept { return bodyLength_; }
	const std::string& species() const noexcept { return species_; }

	// Override print function for monkey-specific output
	void print(std::ostream& os) const override;
};
