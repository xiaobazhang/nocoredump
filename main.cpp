#include <iostream>
#include "srv/catch_exceptions.h"

using namespace std;

int test_test() {
	int a = 10 / 0;
	return 0;
}

bool ABCDEF() {
	test_test();
}
void CoreDump()
{
	for (int i = 0; i < 2; i++) {
		Try("first1")
			ABCDEF();
		EndTry
		CatchExceptions
			cout << "catch the crash first1!!!" << endl;
		EndCatch
	}
}

int main() {
	CoreDump();
	return 0;
}