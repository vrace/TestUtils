#include "TestUtils.h"

TestSuite& TestSuite::GetInstance()
{
	static TestSuite instance;
	return instance;
}

void TestSuite::Add(TestCase &testCase)
{
	testCases_.push_back(&testCase);
}

void TestSuite::Run()
{
	for (std::vector<TestCase*>::iterator it = testCases_.begin(); it != testCases_.end(); ++it)
	{
		TestCase *testCase = *it;
		std::cout << "TEST CASE: " << testCase->GetName() << std::endl;
		testCase->Run();
	}

	std::cout << "ALL TEST CASE(S) PASSED." << std::endl;
}
