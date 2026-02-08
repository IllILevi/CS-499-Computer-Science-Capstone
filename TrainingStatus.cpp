#include "TrainingStatus.h" 
#include <algorithm>
#include <stdexcept>

std::string toString(TrainingStatus s) {
	switch (s) {
	case TrainingStatus::PhaseI: return "Phase I";
	case TrainingStatus::PhaseII: return "Phase II";
	case TrainingStatus::PhaseIII: return "Phase III";
	case TrainingStatus::PhaseIV: return "Phase IV";
	case TrainingStatus::PhaseV: return "Phase V";
	case TrainingStatus::InService: return "In service";
	default: return "Intake";

	}
}

TrainingStatus parseTrainingStatus(const std::string& input) {
	std::string str = input;

	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
	str.erase(std::remove_if(str.begin(), str.end(), ::isspace), str.end());

	if (str == "intake") return TrainingStatus::Intake;
	if (str == "phasei") return TrainingStatus::PhaseI;
	if (str == "phaseii") return TrainingStatus::PhaseII;
	if (str == "phaseiii") return TrainingStatus::PhaseIII;
	if (str == "phaseiv") return TrainingStatus::PhaseIV;
	if (str == "phasev") return TrainingStatus::PhaseV;
	if (str == "inservice") return TrainingStatus::InService;

	throw std::invalid_argument("Invalid tranining status: " + input);
}

