/* file: minunit.h */
/* Source: http://www.jera.com/techinfo/jtns/jtn002.html */
/* Modified by Miguel Rodrigues dos Santos - 2015 */
#define mu_assert(message, test) do { tests_run++; if (!(test)) return message; \
									else tests_passed++; } while (0)
#define mu_run_test(test) do { char *message = test(); \
							if (message) return message; } while (0)
extern int tests_run;
extern int tests_passed;
