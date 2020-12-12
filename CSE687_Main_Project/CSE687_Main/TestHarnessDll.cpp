#include "TestHarnessDll.h"

TestHarnessDll::~TestHarnessDll()
{
}

void TestHarnessDll::Run()
{
	out_stream << "\n\n|| ####< Testing DLL - START >#### ||\n";
	out_stream << "Number of Hardware Threads:" << thread::hardware_concurrency() << "\n";

	// socket system will setup the sockets and tears them down when the
	// class is destroyed.
	SocketSystem socket_system_setup;

	DllClient dll_client;

	dll_client.LoadDll(dll_directory_location);

	// create a blocking queue to put all our tests into.
	BlockingQueue<ITest*> blocking_queue_of_test_drivers;

	// go through the dll(s) that were found and valid.
	for (DllDataStructure* data_struct : dll_client.GetDataList())
	{
		// go through all the functions and load them up for testing.
		for (size_t i = 0; i < data_struct->number_of_functions; i++)
		{
			LPCSTR function_name = data_struct->function_list_array[i].c_str();

			auto test_this = new TestDriver<TestDllFunction<funcTestbool>>();

			auto test_function = new TestDllFunction<funcTestbool>();

			test_function->SetFunction((funcTestbool)GetProcAddress(
				data_struct->dll_instance,
				function_name
			));

			test_this
				->loadClass(test_function)
				->loadMethod(&TestDllFunction<funcTestbool>::TestFunction)
				->methodName(data_struct->function_list_array[i])
				->loadLogger(logger)
				->loadMessage("Testing if method returns true.");

			blocking_queue_of_test_drivers.enqueue(test_this);
		}
	}

	out_stream << "Number of tests to run:" << blocking_queue_of_test_drivers.size() << "\n";

	// setup mother thread network infor.
	AddressIp4 address_mother;
	address_mother.set(127, 0, 0, 1, 51000);

	// setup children test threads.
	vector<IAddressIp*> children_addresses;

	int child_port = 52010;
	for (int i = 0; i < number_of_children_threads; ++i) {
		IAddressIp* address_child = new AddressIp4();

		address_child->set(127, 0, 0, 1, child_port);

		children_addresses.push_back(address_child);

		child_port += 10;
	}

	// setup mother code.
	MotherController mother(
		&address_mother,
		children_addresses,
		blocking_queue_of_test_drivers,
		"Mother");
	mother.setup(logger);

	// set mother on her own thread seperate from the main thread.
	thread mother_thread(&MotherController::run, std::ref(mother));

	// wait here until the mother_thread is done processing information.
	mother_thread.join(); // must join with thread.

	out_stream << "\n\n|| ####< Testing DLL - DONE >#### ||\n";
}