#include <algorithm>
#include <iostream>
#include <memory>
#include <unordered_set>
#include <vector>

#include "Dog.h"
#include "Monkey.h"
#include "TrainingStatus.h"

// if on macOS or Linux, maps _stricmp to strcasecmp
#if defined(__APPLE__) || defined(__linux__)
#define _stricmp strcasecmp
#endif

using std::cout;
using std::cin;
using std::string;

// pointer to RescueAnimal object
using AnimalPtr = std::unique_ptr<RescueAnimal>;
static std::vector <AnimalPtr> animals;

// Testing data
static void dummyData() {
	animals.push_back(std::make_unique<Dog>("Spot", "German Shepherd", "male", "1", "25.6", "05-12-2019", "United States", "United States", TrainingStatus::Intake, false));
	animals.push_back(std::make_unique<Dog>("Rex", "Great Dane", "male", "3", "35.2", "02-03-2020", "United States", "United States", TrainingStatus::PhaseI, false));
	animals.push_back(std::make_unique<Dog>("Bella", "Chihuahua", "female", "4", "25.6", "12-12-2019", "Canada", "Canada", TrainingStatus::InService, true));
	animals.push_back(std::make_unique<Monkey>("Spike", "Capuchin", "male", "1", "25.6", "15", "6", "19", "05-12-2019", "United States", "United States", TrainingStatus::Intake, false));
	animals.push_back(std::make_unique<Monkey>("Pam", "Macaque", "female", "15", "6", "19", "1", "25.6", "05-12-2019", "Canada", "Canada", TrainingStatus::InService, false));
	animals.push_back(std::make_unique<Monkey>("Harry", "Capuchin", "male", "1", "25.6", "15", "6", "19", "05-12-2019", "United States", "United States", TrainingStatus::Intake, false));
}

// prints out menu options
static void displayMenu() {
	cout << "\n\n\t\tRescue Animal System Menu\n" 
		 << "[1] Intake a new dog\n" 
		 << "[2] Intake a new monkey\n" 
		 << "[3] Reserve an animal\n" 
		 << "[4] Print a list of all dogs\n" 
		 << "[5] Print a list of all monkeys\n" 
		 << "[6] Print a list of all animals that are not reserved\n" 
		 << "[q] Quit application\n" 
		 << "Enter a menu selection: ";
}

// Prompts user for input, takes in user input
static string readLine(const string& prompt = "") {
	if (!prompt.empty()) {
		cout << prompt;
	}
	string s;
	std::getline(cin, s);
	return s;
}

// Checks duplicate by name, prompts user for dog info, adds new dog to animals vector
static void intakeNewDog() {
	string name = readLine("What is the dog's name?");

	// Check duplicate by name 
	auto it = std::find_if(animals.begin(), animals.end(), [&](const AnimalPtr& a) {
		return _stricmp(a->name().c_str(), name.c_str()) == 0 && dynamic_cast<Dog const*>(a.get());
		});

	// Duplicate found
	if (it != animals.end()) {
		cout << "\nThis dog is already in our system.\n";
		return;
	}

	string breed = readLine("What is the dog's breed? "); 
	string gender = readLine("What is the dog's gender? "); 
	string age = readLine("What is the dog's age? "); 
	string weight = readLine("What is the dog's weight? "); 
	string acquisitionDate = readLine("What is the dog's acquisition date? "); 
	string acquisitionCountry = readLine("What is the dog's acquisition country? "); 
	string trainingStatusStr = readLine("What is the dog's training status (Intake/PhaseI/InService)? "); 
	string inServiceCountry = readLine("What is the dog's service country? ");

	// Throws invalid_argument exception if training status is not valid
	TrainingStatus ts;
	try {
		ts = parseTrainingStatus(trainingStatusStr);
	}
	catch (const std::invalid_argument& e) {
		std::cout << e.what() << "\nPlease try again.\n";
		return;
	}

	// Adds dog to animals vector
	animals.push_back(std::make_unique<Dog>(name, breed, gender, age, weight, acquisitionDate, acquisitionCountry, inServiceCountry, ts, false));
	cout << "Dog added to system.\n";
}

// Checks duplicate by name, prompts user for monkey info, adds new monkey to animals vector
static void intakeNewMonkey() {
	string name = readLine("What is the monkey's name?");

	// Check duplicate by name
	auto it = std::find_if(animals.begin(), animals.end(), [&](const AnimalPtr& a) {
		return _stricmp(a->name().c_str(), name.c_str()) == 0 && dynamic_cast<Monkey const*>(a.get());
		});

	// Duplicate found
	if (it != animals.end()) {
		cout << "\nThis monkey is already in our system.\n";
		return;
	}

	string species = readLine("What is the monkey's species? ");
	string gender = readLine("What is the monkey's gender? ");
	string age = readLine("What is the monkey's age? ");
	string weight = readLine("What is the monkey's weight? ");
	string height = readLine("What is the monkey's height? ");
	string tailLength = readLine("What is the monkey's tail length? ");
	string bodyLength = readLine("What is the monkey's body length? ");
	string acquisitionDate = readLine("What is the monkey's acquisition date? ");
	string acquisitionCountry = readLine("What is the monkey's acquisition country? ");
	string trainingStatusStr = readLine("What is the monkey's training status (Intake/PhaseI/InService)? ");
	string inServiceCountry = readLine("What is the monkey's service country? ");

	// Throws invalid_argument exception if training status is not valid
	TrainingStatus ts;
	try {
		ts = parseTrainingStatus(trainingStatusStr);
	}
	catch (const std::invalid_argument& e) {
		std::cout << e.what() << "\nPlease try again.\n";
		return;
	}

	// Adds Monkey to the animals vector
	animals.push_back(std::make_unique<Monkey>(name, species, gender, tailLength, height, bodyLength, age, weight, acquisitionDate, acquisitionCountry, inServiceCountry, ts, false));
	cout << "Monkey added to system.\n";
}

// Loops through animals vector to find an animal that matches what the user needs
static void reserveAnimal() {
	string animalType = readLine("What type of animal do you need (\"dog\" or \"monkey\") ? ");
	string country = readLine("What country do you need the animal?");

	for (auto& a : animals) {
		bool matchType = (animalType == "dog" && dynamic_cast<Dog*>(a.get())) ||
						 (animalType == "monkey" && dynamic_cast<Monkey*>(a.get()));

		// If the animal type does not match, skip to next animal
		if (!matchType) continue; 

		// If animal is not reserved, inService, and inServiceCountry matches what user needs
		if (Dog* d = dynamic_cast<Dog*>(a.get())) {
			if (!d->reserved() && d->trainingStatus() == TrainingStatus::InService && d->inServiceCountry() == country) {
				d->setReserved(true);
				cout << "Dog has beed reserved.\n";
				return;
			}
		}
		else if (Monkey* m = dynamic_cast<Monkey*>(a.get())) {
			if (!m->reserved() && m->trainingStatus() == TrainingStatus::InService && m->inServiceCountry() == country) {
				m->setReserved(true);
				cout << "Monkey has been reserved.\n";
				return;
			}
		}
	}
	cout << "No animal was availble in that country.\n";
}

// Prints either all dogs, all monkeys, or all available animals
static void printAnimals(const string& userInput) {
	if (userInput == "4") {
		cout << "\n All dogs:\n";
		for (auto const& a : animals) {
			if (dynamic_cast<Dog const*>(a.get())) {
				cout << *a << '\n';
			}
		}
	}
	if (userInput == "5") {
		cout << "\n All monkeys:\n";
		for (auto const& a : animals) {
			if (dynamic_cast<Monkey const*>(a.get())) {
				cout << *a << '\n';
			}
		}
	}
	if (userInput == "6") {
		cout << "All available animals:\n";
		for (auto const& a : animals) {
			if (!a->reserved() && a->trainingStatus() == TrainingStatus::InService) {
				cout << *a << '\n';
			}
		}
	}
}

int main() {
	dummyData();
	
	string userInput;

	// Set of valid user inputs
	const std::unordered_set<string> validInputs = { "1", "2", "3", "4", "5", "6", "q", "Q" };

	while (true) {
		displayMenu();
		std::getline(cin, userInput);

		if (!validInputs.count(userInput)) {
			cout << "Invalid input! Please try again.\n";
			continue;
		}

		if (userInput == "q" || userInput == "Q") {
			break;
		}
		if (userInput == "1") {
			intakeNewDog();
		}
		else if (userInput == "2") {
			intakeNewMonkey();
		}
		else if (userInput == "3") {
			reserveAnimal();
		}
		else {
			printAnimals(userInput);
		}
	}
	cout << "Quitting application, goodbye!\n";
	return 0;
}


