#include <gtest/gtest.h>
#include <windows.h>
#include "test.h"

TEST(MyCJson, test1){
	EXPECT_EQ(true, TestObject());
	EXPECT_EQ(true, TestArray());
}

int main(int argc, char* argv[]){
	TestByFile("tests\\test1", "tests\\test1_result.txt");
	TestByFile("tests\\test2", "tests\\test2_result.txt");
	TestByFile("tests\\test3", "tests\\test3_result.txt");
	TestByFile("tests\\test4", "tests\\test4_result.txt");
	TestByFile("tests\\test5", "tests\\test5_result.txt");
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	system("pause");
	return 0;
}