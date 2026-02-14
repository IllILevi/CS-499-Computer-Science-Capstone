//============================================================================
// Name        : CS300_Project_Two.cpp
// Author      : Levi Bajuscik
// Version     : 1.0
// Description : Course sorting algorithms
//============================================================================

#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>
#include<algorithm>
#include<limits>
#include<time.h>
#include<chrono>

using namespace std;
using namespace std::chrono;

struct course {
	string courseId;
	string courseName;
	vector<string> prerequisites;
};

void loadCourses(const string& filename, vector<course>& courses) {

	// Opens specified file
	ifstream file(filename);

	// Checks if file is opened successfully, if not, prints error message
	if (!file.is_open()) {
		cout << "Error opening file: " << filename << endl;
		return;
	}

	string line;
	// Read the file line by line
	while (getline(file, line)) {

		// Create a course object
		course c;
		// parse through file
		stringstream ss(line);
		getline(ss, c.courseId, ',');
		getline(ss, c.courseName, ',');

		string prereq;
		while (getline(ss, prereq, ',')) {

			// If prerequisite is not empty, add it to the end of the prerequisites vector
			if (!prereq.empty()) {
				c.prerequisites.push_back(prereq);
			}
		}
		// Add the course object to the courses vector
		courses.push_back(c);
	}
	cout << "\nData loaded successfully.\n" << endl;
	// Close the file
	file.close();
}

//sort()
//FilesTest.csv avg time: 31ms
//DummyData.txt avg time: 5,996.9ms
void sortCourses(vector<course>& courses) {
	sort(courses.begin(), courses.end(), [](const course& a, const course& b) {
		return a.courseId < b.courseId;
		});
}

// Define the < operator for the course struct
bool operator<(const course& a, const course& b) {
	return a.courseId < b.courseId;
}

// Creates two subarrays of courses and merges them back together
void merge(vector<course>& courses, int left, int mid, int right) {
	
	int n1 = mid - left + 1;
	int n2 = right - mid;

	// Create temp vectors
	vector<course> L(n1), R(n2);

	// Copy data to temp vectors L[] and R[]
	for (int i = 0; i < n1; i++) {
		L[i] = courses[left + i];
	}
	for (int j = 0; j < n2; j++) {
		R[j] = courses[mid + 1 + j];
	}

	int i = 0, j = 0;
	int k = left;

	// Merge the temp vectors back into courses
	while (i < n1 && j < n2) {
		if (L[i] < R[j]) {
			courses[k] = L[i];
			i++;
		}
		else {
			courses[k] = R[j];
			j++;
		}
		k++;
	}

	// Copy the remaining elements of L[], if there are any
	while (i < n1) {
		courses[k] = L[i];
		i++;
		k++;
	}

	// Copy the remaining elements of R[], if there are any
	while (j < n2) {
		courses[k] = R[j];
		j++;
		k++;
	}
}

// MergeSort
// FileTest.csv avg time: 142.4ms
// DummyData.txt avg time: 19,246.4ms
// Space complexity: O(n)
void mergeSort(vector<course>& courses, int left, int right) {
	if (left >= right) {
		return;
	}

	int mid = left + (right - left) / 2;
	mergeSort(courses, left, mid);
	mergeSort(courses, mid + 1, right);
	merge(courses, left, mid, right);
}

int partition(vector<course>& courses, int begin, int end) {

	// Initialize low and high indices
	int low = begin;
	int high = end;

	// choose the middle element as the pivot
	int middlePoint = (low + high) / 2;
	string pivot = courses.at(middlePoint).courseId;

	bool done = false;
	while (!done) {

		// Move low index right until we find an element greater than the pivot
		while (courses.at(low).courseId < pivot) {
			++low;
		}

		// Move the high index left until we find an element less than the pivot
		while (pivot < courses.at(high).courseId) {
			--high;
		}

		// If low and high have crossed each other, then partition is done
		if (low >= high) {
			done = true;
		}
		else {

			// Swap the elements at low and high indices
			swap(courses.at(low), courses.at(high));

			// Move indices towards each other
			++low;
			--high;
		}
	}
	// Reurn the final position of the pivot element
	return high;
}

// QuickSort
// FileTest.csv avg time: 27ms
// DummyData.txt avg time: 3,054.3ms
// Space complexity: O(log n)
void quickSort(vector<course>& courses, int begin, int end) {
	int mid = 0;

	// If the segment has one or fewer elements, it's already sorted
	if (begin >= end) {
		return;
	}

	// Partition the vector and get the pivot position
	mid = partition(courses, begin, end);

	// Recursively sort the left half (elements before the pivot) 
	quickSort(courses, begin, mid);

	// Recursively sort the right half (elements after the pivot)
	quickSort(courses, mid + 1, end);
}

// InsertionSort
// FilesTest.csv avg time: 56ms
// DummyData.txt avg time: 28,579.2ms
// space complexity: O(1)
void insertionSort(vector<course>& courses) {
	// start from the second element (index 1)
	for (int i = 1; i < courses.size(); i++) {
		course key = courses.at(i);
		int j = i - 1;

		// move elements greater than key one position ahead
		while (j >= 0 && courses.at(j).courseId > key.courseId) {
			courses.at(j + 1) = courses.at(j);
			j--;
		}
		courses.at(j + 1) = key;
	}
}

void printCourses(const vector<course>& sortedCourses) {

	// Print the sorted courses
	for (const auto& c : sortedCourses) {
		cout << c.courseId << ", " << c.courseName << endl;
	}
	cout << endl;
}

void printCourseInfo(const vector<course>& courses, string courseId) {

	// Convert user input to uppercase for case-insensitive comparison
	for (char& c : courseId) {
		c = toupper(static_cast<unsigned char>(c));
	}

	// Track if course is found
	bool found = false;

	// Iterate through courses vector
	for (int i = 0; i < courses.size(); i++) {

		// Check if the current courseId matches the provided courseId
		if (courses.at(i).courseId == courseId) {
			found = true;

			// Print course information
			cout << courses.at(i).courseId << ", " << courses.at(i).courseName << endl;
			cout << "Prerequisites: ";

			// Iterate through the prerequisites vector for the current course
			// and print each prerequisite
			for (int j = 0; j < courses.at(i).prerequisites.size(); j++) {
				cout << courses.at(i).prerequisites.at(j);

				if (j != courses.at(i).prerequisites.size() - 1) {
					cout << ", ";
				}
			}
			cout << endl;

			// Exit outer loop since the course is found
			break;
		}
	}
	// If course isn't found, print error message
	if (!found) {
		cout << "Course not found: " << courseId << endl;
	}
}

int main() {

	// Print welcome message
	cout << "Welcome to the Course Planner!" << endl;

	// Initialize vector to store courses
	vector<course> courses;
	vector<course> sortedCourses;

	// Variable to store user's menu choice
	int option = 0;

	// Variables to store filename and courseId inputs
	string fileName;
	string courseId;

	clock_t ticks;

	// Main program loop
	do {

		// Display menu options
		cout << "1. Load Course Data." << endl
			<< "2. QuickSort Courses." << endl
			<< "3. C++ std::sort Courses." << endl
			<< "4. MergeSort Courses." << endl
			<< "5. InsertionSort Courses." << endl
			<< "6. Print Course Info." << endl
			<< "9. Exit\n" << endl
			<< "What would you like to do? ";

		// Get user input
		cin >> option;

		switch (option) {
		case 1:

			// Load courses from specified file
			cout << "Enter the filename: ";
			cin >> fileName;

			// Initalize timer
			ticks = clock();

			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			loadCourses(fileName, courses);

			// Calculate elapse time and display result
			ticks = clock() - ticks; // current clock ticks minus starting clock ticks
			cout << "time: " << ticks << " clock ticks" << endl;
			cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds \n" << endl;

			break;
		case 2: {
			sortedCourses = courses;

			auto start = high_resolution_clock::now();

			quickSort(sortedCourses, 0, sortedCourses.size() - 1);

			auto end = high_resolution_clock::now();
			auto duration = duration_cast<microseconds>(end - start);

			cout << "Time: " << duration.count() << " microseconds" << endl;
			cout << "Time: " << duration.count() / 1000000.0 << " seconds" << endl;

			// Print all courses in alphanumeric order
			cout << "Here is a sample schedule: \n" << endl;
			printCourses(sortedCourses);

			break;
		}
		case 3: {
			sortedCourses = courses;

			auto start = high_resolution_clock::now();

			sortCourses(sortedCourses);

			auto end = high_resolution_clock::now();
			auto duration = duration_cast<microseconds>(end - start);

			cout << "Time: " << duration.count() << " microseconds" << endl;
			cout << "Time: " << duration.count() / 1000000.0 << " seconds" << endl;

			// Print all courses in alphanumeric order
			cout << "Here is a sample schedule: \n" << endl;
			printCourses(sortedCourses);

			break;
		}
		case 4: {
			sortedCourses = courses;

			auto start = high_resolution_clock::now();

			mergeSort(sortedCourses, 0, sortedCourses.size() - 1);

			auto end = high_resolution_clock::now();
			auto duration = duration_cast<microseconds>(end - start);

			cout << "Time: " << duration.count() << " microseconds" << endl;
			cout << "Time: " << duration.count() / 1000000.0 << " seconds" << endl;

			// Print all courses in alphanumeric order
			cout << "Here is a sample schedule: \n" << endl;
			printCourses(sortedCourses);

			break;
		}
		case 5: {
			sortedCourses = courses;

			auto start = high_resolution_clock::now();

			insertionSort(sortedCourses);

			auto end = high_resolution_clock::now();
			auto duration = duration_cast<microseconds>(end - start);

			cout << "Time: " << duration.count() << " microseconds" << endl;
			cout << "Time: " << duration.count() / 1000000.0 << " seconds" << endl;

			// Print all courses in alphanumeric order
			cout << "Here is a sample schedule: \n" << endl;
			printCourses(sortedCourses);

			break;
		}
		case 6:
			// Print specified course information
			cout << "What course do you want to know about? ";
			cin >> courseId;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			printCourseInfo(courses, courseId);
			break;
		case 9:
			// Exit program
			cout << "Goodbye!" << endl;
			break;
		default:
			// Invalid option
			cout << option << " is not a valid option.\n" << endl;
		}
	} while (option != 9); // Continue loop until user inputs 9 (Exit)

	return 0;
}
