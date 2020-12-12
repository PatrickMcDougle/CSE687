#pragma once

#ifndef __TEST_DLL_FUNCTION_H__
#define __TEST_DLL_FUNCTION_H__

namespace test {
	/// <summary>
	/// This class will hold something to test.
	/// The main use at this time is for the class to hold a function pointer
	/// to a function that needs to be tested.
	/// </summary>
	/// <typeparam name="F">Is a template value for the class.  The class will execute this type.</typeparam>
	template<typename F>
	class TestDllFunction
	{
	private:
		// a pointer to the function or item to test.
		F test_function_ptr_;

	public:

		/// <summary>
		/// The default constructor.
		/// </summary>
		TestDllFunction() {};

		/// <summary>
		/// This method will set the function or item to be run later.
		/// </summary>
		/// <param name="test_function">a pointer to the function that needs to be tested/run.</param>
		void SetFunction(F test_function) {
			test_function_ptr_ = test_function;
		};

		/// <summary>
		/// The default destructor.
		/// </summary>
		~TestDllFunction() {};

		/// <summary>
		/// This method is called when the tester is ready to get a value from the test.
		/// </summary>
		/// <returns>Returns true if the test passes or false if the test fails.</returns>
		bool TestFunction() {
			return test_function_ptr_();
		}
	};
}

#endif // !__TEST_DLL_FUNCTION_H__