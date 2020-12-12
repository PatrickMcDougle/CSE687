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

	// DLL stuff.
	HINSTANCE hDLL = nullptr;
	funcListOfFunctions list_of_functions = nullptr;
	funcNumberOfTests number_of_tests = nullptr;

	DllClient dll_client;

	dll_client.LoadDll(dll_directory_location);

	BlockingQueue<ITest*> blocking_queue_of_test_drivers;

	for (DllDataStructure* data_struct : dll_client.GetDataList())
	{
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

	AddressIp4 address_mother;

	address_mother.set(127, 0, 0, 1, 51000);

	vector<IAddressIp*> children_addresses;

	int child_port = 52010;
	for (int i = 0; i < number_of_children_threads; ++i) {
		IAddressIp* address_child = new AddressIp4();

		address_child->set(127, 0, 0, 1, child_port);

		children_addresses.push_back(address_child);

		child_port += 10;
	}

	MotherController mother(
		&address_mother,
		children_addresses,
		blocking_queue_of_test_drivers,
		"Mother");
	mother.setup(logger);

	//mother.run(); // when threads don't work, we can just call the run method.

	std::thread mother_thread(&MotherController::run, std::ref(mother));

	// wait here until the mother_thread is done processing information.
	mother_thread.join(); // must join with thread.

	delete logger;
	logger = nullptr;

	out_stream << "\n\n|| ####< Testing DLL - DONE >#### ||\n";
}