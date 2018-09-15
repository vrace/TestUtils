#include "TestUtils.h"

int main()
{
	TestSuite::GetInstance().Run();
	return 0;
}

TEST_CASE(sample1, {
	TEST_PRINT << "Hello from sample1" << std::endl;
});

TEST_CASE(sample2, {
	ASSERT_THAT(1, IS(2));
});
