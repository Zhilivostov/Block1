//#include "pch.h"
#include <gtest/gtest.h>
#include "mystring.h"

//class MemoryLeakDetector {
//public:
//	MemoryLeakDetector() {
//		_CrtMemCheckpoint(&memState_);
//	}
//
//	~MemoryLeakDetector() {
//		_CrtMemState stateNow, stateDiff;
//		_CrtMemCheckpoint(&stateNow);
//		int diffResult = _CrtMemDifference(&stateDiff, &memState_, &stateNow);
//		if (diffResult)
//			reportFailure(stateDiff.lSizes[1]);
//	}
//private:
//	void reportFailure(unsigned int unfreedBytes) {
//		FAIL() << "Memory leak of " << unfreedBytes << " byte(s) detected.";
//	}
//	_CrtMemState memState_;
//};

TEST(Replace, test)
{
	String str1("Hello");
	String str2(" World");
	str1.replace(1, 3, 3, 'H');
	str1.replace(str1.size(), 0, str2);
	str1.replace(5, 6, str2);
	str1.replace(4, 3, str2);
	str1.erase(1, 3);
}

TEST(Constructors, All) {
	//MemoryLeakDetector mem;
	String str1;
	String str2("Hello");
	String str3("Hello", 3);
	String str4(5, 'p');
	String str5(str2);
	String str6(str2, 1, 3);
	str1 = str2;
	EXPECT_EQ(str1.countRef(), 3);
	EXPECT_EQ(str2.countRef(), 3);
	str1 = "Hello";
	EXPECT_EQ(str1.compare(str2), 0);
	EXPECT_EQ(str1.countRef(), 1);
	EXPECT_EQ(str2.countRef(), 2);
}

//TEST(Constructors, All) {
//	//MemoryLeakDetector mem;
//	String str1;
//	String str2("Hello");
//	String str3("Hello", 3);
//	String str4(5, 'p');
//	String str5(str2);   //возможно проблема в этом конструкторе!!!  сам конструктор вроде рабочий, но если к str5 использовать +=, то ошибка!!
//	String str6(str2, 1, 3);
//	str1 = str2;
//	str1 = "Hello";
//	EXPECT_EQ(str1.compare(str2), 0);
//	EXPECT_EQ(str2.size(), 5);
//	str1 += str3;
//	str5 += "Hello";
//	str4 += str5;
//	str5 += "kjk";
//	//str4 += "gf";
//	//str6 += str4;
//	//EXPECT_EQ(*(str1.data()), *("Hello"));
//}

TEST(Methods, Return_elements) {
	//MemoryLeakDetector mem;
	String str2("Hello");
	String str3(str2);
	EXPECT_EQ(str2.capacity(), 11);
	EXPECT_EQ(str2.size(), 5);
	EXPECT_EQ(str2.countRef(), 2);
}

TEST(Methods, At) {
	//MemoryLeakDetector mem;
	String str2("Hello");
	EXPECT_EQ(str2.at(0), 'H');
	EXPECT_EQ(str2[3], 'l');
	EXPECT_ANY_THROW(str2[7]);
}

TEST(Methods, Front_back) {
	//MemoryLeakDetector mem;
	String str1;
	String str2("Hello");
	String str3("Hello", 3);
	String str4(5, 'p');
	String str5(str2);
	String str6(str2, 1, 3);
	str1 = str2;
	EXPECT_EQ(str2.back(), 'o');
	EXPECT_EQ(str3.front(), 'H');
}

TEST(Methods, Operators) {
	//MemoryLeakDetector mem;
	const char* aaa = "Hello";
	String str1;
	String str2("Hello");
	String str3("Hello", 3);
	String str4(5, 'p');
	String str5(str2);
	String str6(str2, 1, 3);
	const char* strnull = nullptr;
	str1 = str2;
	str4 += str3;

	//str2 += str6.data();
	//str5 += str6.data();
	//std::cout << str3.data() << str5.data();
	EXPECT_EQ(*(str2.data()), *(aaa));
	EXPECT_EQ(*(str3.data()), *("Helppppp"));
	EXPECT_EQ(*(str5.data()), *("Helloell"));
	EXPECT_ANY_THROW(str1+=strnull);
}

TEST(Methods, Inserts) {
	//MemoryLeakDetector mem;
	const char* aaa = "aaa";
	String str2("Hello");
	String str3("Hello", 3);
	str2.insert(3, str3);
	str3.insert(2, aaa);
	EXPECT_ANY_THROW(str2.insert(9, str3));
	EXPECT_EQ(*(str2.data()), *("HeHelllo"));
	EXPECT_EQ(*(str3.data()), *("Haaael"));
}

TEST(Methods, Erase_clear) {
	//MemoryLeakDetector mem;
	String str2("Hello");
	str2.erase(3);
	EXPECT_EQ(*(str2.data()), *("Hel"));
	str2.clear();
	EXPECT_TRUE(str2.empty());
}

TEST(Methods, Replaces) {
	//MemoryLeakDetector mem;
	String str2("Hello");
	String str1("he");
	const char* aaa = "aaa";
	str2.replace(3,2, aaa);
	EXPECT_EQ(*(str2.data()), *("Helaa"));
	str2.replace(3, 2, str1);
	EXPECT_EQ(*(str2.data()), *("Helhe"));
	str2.replace(3, 2, 2, 'a');
	EXPECT_EQ(*(str2.data()), *("Helaa"));

}

TEST(Methods, Swap) {
	//MemoryLeakDetector mem;
	String str2("Hello");
	String str3("olleH");
	str2.swap(str3);
	EXPECT_EQ(*(str2.data()), *("olleH"));
}

TEST(Methods, Finds) {
	//MemoryLeakDetector mem;
	String str2("Hello");
	String str4("Hel");
	EXPECT_EQ(str2.find(str4, 0), 0);
	EXPECT_EQ(str2.find('e', 0), 1);
	EXPECT_EQ(str2.find("Hel", 0), 0);
}

TEST(Methods, Substr) {
	//MemoryLeakDetector mem;
	String str2("Hello");
	str2.substr(1, 3);
	EXPECT_EQ(*(str2.data()), 'H');
	String str3("olleH");
	EXPECT_NO_THROW(str3.substr(3, 7));
}



