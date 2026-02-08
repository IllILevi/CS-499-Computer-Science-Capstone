#pragma once
#include <string>
#include <algorithm>
#include <stdexcept>

// Determines if animal info has postitive numbers
inline bool isPositive(const std::string& s) {
	bool hasDigit = false;

	for (char c : s) {
		if (std::isdigit(static_cast<unsigned char>(c))) {
			hasDigit = true;
		}
		else if (c != '.' && c != '-') {
			return false;
		}
	}
}

// if a field is empty, throw invalid_argument exception
inline void requireNonEmpty(const std::string& val, const std::string& fieldName) {
	if (val.empty()) {
		throw std::invalid_argument(fieldName + " cannot be empty.");
	}
}

// if a field is under 0, throw invalid_argument exception
inline void requirePositive(const std::string& val, const std::string& fieldName) {
	if (!isPositive(val)) {
		throw std::invalid_argument(fieldName + " must be positive.");
	}
}