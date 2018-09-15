#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <string>
#include <vector>
#include <iostream>

class TestCase
{
public:
	virtual ~TestCase() {}
	virtual std::string GetName() const = 0;
	virtual void Run() = 0;
};

class TestSuite
{
public:
	static TestSuite& GetInstance();
	void Add(TestCase &testCase);
	void Run();

private:
	std::vector<TestCase*> testCases_;
};

template <class T>
class TestCaseLoader
{
public:
	TestCaseLoader()
	{
		TestSuite::GetInstance().Add(testCase_);
	}

private:
	T testCase_;
};

template <class T>
class MatcherIs
{
public:
	MatcherIs(const T &expect)
		: expect_(expect) {}

	template <class U>
	bool Match(const U &actual) const
	{
		return expect_ == actual;
	}

	const T& Expect() const
	{
		return expect_;
	}

private:
	const T &expect_;
};

template <class T>
MatcherIs<T> IS(const T &expect)
{
	return MatcherIs<T>(expect);
}

#define TEST_CASE(name, impl) \
class test_case_##name : public TestCase \
{ \
public: \
std::string GetName() const { return #name; } \
void Run() impl \
}; \
TestCaseLoader<test_case_##name> load_test_case_##name;

#define TEST_PRINT \
std::cout << "> "

#define ASSERT_THAT(actual, matcher) \
if (!matcher.Match(actual)) \
{ \
TEST_PRINT << "ASSERTION FAILED!" << std::endl; \
TEST_PRINT << "EXPECT: " << matcher.Expect() << std::endl; \
TEST_PRINT << "ACTUAL: " << actual << std::endl; \
exit(-1); \
}

#endif
