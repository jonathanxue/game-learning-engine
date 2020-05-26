#pragma once
#include <stdio.h>

class ButtonCallbacks {
public:
	static void test1() {
		printf("Test 1 fired\n");
	}

	static void test2() {
		printf("Test 2 fired\n");
	}
};