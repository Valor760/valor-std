#include "../src/string/string.h"

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
	const std::string fmt = "%s:%d - expected[%s], but received[%s]\n";
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


int main() {
	test_string_replace();

	return 0;
}