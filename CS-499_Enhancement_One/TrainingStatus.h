#pragma once
#include <string>

// Training progression stages for animals
enum class TrainingStatus {
	Intake, PhaseI, PhaseII, PhaseIII, PhaseIV, PhaseV, InService
};

// function to return string value of enum
std::string toString(TrainingStatus str);

// Normalizes training status to a valid enum
TrainingStatus parseTrainingStatus(const std::string& input);
