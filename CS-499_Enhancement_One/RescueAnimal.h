#pragma once
#include <string>
#include <iostream>
#include <ostream>

#include "TrainingStatus.h"

class RescueAnimal {
protected:
	std::string name_;
	std::string gender_;
	std::string age_;
	std::string weight_;
	std::string acquisitionDate_;
	std::string acquisitionCountry_;
	std::string inServiceCountry_;
	TrainingStatus trainingStatus_;
	bool reserved_ = false;

public:
	RescueAnimal(std::string name, std::string gender, std::string age, std::string weight, std::string acquisitionDate,
		std::string acquisitionCountry, std::string inServiceCountry, TrainingStatus ts = TrainingStatus::Intake, bool reserved = false);

	// Virtual Destructor
	virtual ~RescueAnimal() = default;

	// Getters
	const std::string& name() const noexcept { return name_; }
	const std::string& gender() const noexcept { return gender_; }
	const std::string& age() const noexcept { return age_; }
	const std::string& weight() const noexcept { return weight_; }
	const std::string& acquisitionDate() const noexcept { return acquisitionDate_; }
	const std::string& acquisitionCountry() const noexcept { return acquisitionCountry_; }
	const std::string& inServiceCountry() const noexcept { return inServiceCountry_; }
	TrainingStatus trainingStatus() const noexcept { return trainingStatus_; }
	bool reserved() const noexcept { return reserved_; }

	// Setters
	void setReserved(bool res) noexcept { reserved_ = res; }
	//void setTrainingStatus(TrainingStatus ts) noexcept { trainingStatus_ = ts; }

	virtual void print(std::ostream& os) const;

	friend std::ostream& operator<<(std::ostream& os, RescueAnimal  const& a);
};
