#include "../src/string/string.h"
#include "../src/fstream/fstream.h"

#include <iostream>
#include <assert.h>
#include <stdarg.h>

#define ASSERT(expr, fmt, ...)\
			if(!(expr)) {									\
				fprintf(stderr, fmt __VA_OPT__(,) __VA_ARGS__);	\
				assert(false);\
			}

#define _FUNLINE_ __FUNCTION__,__LINE__

// FIXME: Make better unit tests
void test_string_replace() {
	const vlr::string fmt = "%s:%d - expected[%s], but received[%s]\n";
	vlr::string expected, changed;

	// Test #1
	expected = "Some ttqweqwe sssstringgg";
	changed = "Some qweqweqwe sssstringgg";
	ASSERT(expected == changed.replace("qwe", "tt"), fmt.c_str(), _FUNLINE_, expected.c_str(), changed.c_str());

	// Test #2
	expected = "Some qweqweqwe sssstringgg";
	changed = "Some qweqweqwe sssstringgg";
	ASSERT(expected == changed.replace("mmm", "tt"), fmt.c_str(), _FUNLINE_, expected.c_str(), changed.c_str());

	// Test #3
	expected = "Some ttt sssstringgg";
	changed = "Some qweqweqwe sssstringgg";
	ASSERT(expected == changed.replace("qwe", "t", 20), fmt.c_str(), _FUNLINE_, expected.c_str(), changed.c_str());

	// Test #4
	expected = "Handsome qweqweqwe sssstringgg";
	changed = "Some qweqweqwe sssstringgg";
	ASSERT(expected == changed.replace("S", "Hands"), fmt.c_str(), _FUNLINE_, expected.c_str(), changed.c_str());

	// Test #5
	expected = "Some qweqweqwe mmmstringgg";
	changed = "Some qweqweqwe sssstringgg";
	ASSERT(expected == changed.replace("s", "m", 3), fmt.c_str(), _FUNLINE_, expected.c_str(), changed.c_str());
}

void test_string_to_lower() {
	const vlr::string fmt = "%s:%d - expected[%s], but received[%s]\n";
	vlr::string expected, changed;

	// Test #1
	expected = "";
	changed = "";
	ASSERT(expected == changed.to_lower(), fmt.c_str(), _FUNLINE_, expected.c_str(), changed.c_str());

	// Test #2
	expected = "some string";
	changed = "SOME STRING";
	ASSERT(expected == changed.to_lower(), fmt.c_str(), _FUNLINE_, expected.c_str(), changed.c_str());

	// Test #3
	expected = "some str1 w1th num63r5";
	changed = "SOME STR1 W1TH NUM63R5";
	ASSERT(expected == changed.to_lower(), fmt.c_str(), _FUNLINE_, expected.c_str(), changed.c_str());

	// Test #4
	expected = "some str1 w num63r5 and !!!";
	changed = "SomE STr1 w NuM63R5 aNd !!!";
	ASSERT(expected == changed.to_lower(), fmt.c_str(), _FUNLINE_, expected.c_str(), changed.c_str());
}

void test_string_contains() {
	const vlr::string fmt = "%s:%d - expected[%s], but received[%s]\n";
	vlr::string expected, changed;

	// Test #1
	expected = "";
	changed = "";
	ASSERT(changed.contains(expected), fmt.c_str(), _FUNLINE_, expected.c_str(), changed.c_str());

	// Test #2
	expected = "ooo";
	changed = "Some Looong String";
	ASSERT(changed.contains(expected), fmt.c_str(), _FUNLINE_, expected.c_str(), changed.c_str());

	// Test #3
	expected = "Short";
	changed = "Some Looong String";
	ASSERT(!changed.contains(expected), fmt.c_str(), _FUNLINE_, expected.c_str(), changed.c_str());

	// Test #4
	expected = "sOMe";
	changed = "Some Looong String";
	ASSERT(!changed.contains(expected), fmt.c_str(), _FUNLINE_, expected.c_str(), changed.c_str());

	// Test #4
	changed = "Some Looong String";
	ASSERT(changed.contains('r'), fmt.c_str(), _FUNLINE_, expected.c_str(), changed.c_str());
}


int main() {
	try {
		test_string_replace();
		test_string_to_lower();
	} catch(std::exception e) {
		std::cout << "ERROR: Test Failed:\n" << e.what() << "\n";
		return 1;
	}

	// vlr::fstream qwe("qwe.txt");

	std::cout << "Test executed successfully!\n";
	return 0;
}