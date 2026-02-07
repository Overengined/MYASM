#include "unity.h"
#include "cleaner.h"

int verbose = 0;

void setUp(void) {}
void tearDown(void) {}

void test_AverageThreeBytes_should_AverageMidRangeValues(void)
{
TEST_ASSERT_EQUAL_STRING("this is a test",prepare("this   is a    test"));
TEST_ASSERT_EQUAL_STRING("testing the \n \n comments",prepare("testing the \n # removal of \n comments"));
TEST_ASSERT_EQUAL_STRING("testing both at \n \n why not ",prepare("testing    both at # once \n #   because \n why  not "));
}

int main(void) {
	UnityBegin("testcleaner.c");
	RUN_TEST(test_AverageThreeBytes_should_AverageMidRangeValues);
	return UnityEnd();
}