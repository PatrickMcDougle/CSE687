#pragma once

#ifndef __TEST_DLL_FUNCTION_H__
#define __TEST_DLL_FUNCTION_H__

namespace test {
	template<typename F>
	class TestDllFunction
	{
	private:
		F test_function_ptr_;

	public:

		TestDllFunction() {};

		void SetFunction(F test_function) {
			test_function_ptr_ = test_function;
		};
		~TestDllFunction() {};

		bool TestFunction() {
			return test_function_ptr_();
		}
	};
}

#endif // !__TEST_DLL_FUNCTION_H__