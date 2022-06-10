/* file: minunit.h c.f https://jera.com/techinfo/jtns/jtn002 */

#include <stdio.h>

#define mu_assert(message, test)   \
	do {                             \
		if (!(test))                   \
			return message;              \
		printf("\tTRUE: %s\n", #test); \
	} while (0)

#define mu_run_test(test)        \
	do {                           \
		printf("TEST: %s\n", #test); \
		char* message = test();      \
		tests_run++;                 \
		if (message)                 \
			return message;            \
	} while (0)

extern int tests_run;
