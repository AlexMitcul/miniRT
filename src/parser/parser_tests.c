



#include "../../includes/minirt.h"

void test_is_valid_file_extension(void)
{
	if (is_valid_file_extension(".rt") == false)
		printf("TEST 1: OK\n");
	else
		printf("TEST 1: KO\n");

	if (is_valid_file_extension("valid.rt") == true)
		printf("TEST 2: OK\n");
	else
		printf("TEST 2: KO\n");

	if (is_valid_file_extension("file") == false)
		printf("TEST 3: OK\n");
	else
		printf("TEST 3: KO\n");

	if (is_valid_file_extension("as.r") == false)
		printf("TEST 4: OK\n");
	else
		printf("TEST 4: KO\n");

	if (is_valid_file_extension(".r") == false)
		printf("TEST 5: OK\n");
	else
		printf("TEST 5: KO\n");

	if (is_valid_file_extension("as.rt.rt") == true)
		printf("TEST 6: OK\n");
	else
		printf("TEST 7: KO\n");
}
