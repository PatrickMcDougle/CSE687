// Creators - Team #5: Patrick McDougle, Edgardo Navarro, William Scott
// Class: CSE 687 OOD
// School: Syracuse University
// Project Name: Test Harness
// Create Date: 2020-10-11
// Description: Contains the main function

#include <iostream>

#include "TestHarnessDll.h"

using std::ostream;
using std::cout;

/// <summary>
/// This is the main function that start the whole program.
/// There are no arguments at this time, but the system would support this if needed.
/// </summary>
/// <returns></returns>
int main()
{
	// Initialize out_stream
	ostream& out_stream = cout;

	// Alert User of Program Start
	out_stream << "|| ####< Start of Program >#### ||\n";

	// setup the logger
	LoggerFactory log_factory;
	ILogger* logger = log_factory.create(30, 50, 10);

	// get the number of threads that the hardware has.
	// then calculate a subset of that to generate children.
	int number_of_children = thread::hardware_concurrency() / 6;

	// if the value is too low, bump it up.
	if (number_of_children < 3) {
		number_of_children *= 3;
	}
	// if the value is 0 hard set it to 3 threads.
	if (number_of_children == 0) {
		number_of_children = 3;
	}

	out_stream << "Number of children:" << number_of_children << "\n";

	// setup the test harness.
	TestHarnessDll test_harness(logger, number_of_children);

	// run the test harness
	test_harness.Run();

	// clean up.
	delete logger;
	logger = nullptr;

	// Alert User of Program End
	out_stream << "\n\n|| ####< Done With Program >#### ||\n\n\n";
}