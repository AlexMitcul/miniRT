#include "../../includes/minirt.h"

static void print_result(bool status, size_t test_index)
{
	if (status == true)
		printf("\033[32m Test %zu - OK \n\033[0m", test_index);
	else
		printf("\033[31m Test %zu - KO \n\033[0m", test_index);
}

#define new_color_test_COUNT 9
void	new_color_test(void)
{
	int data[new_color_test_COUNT][3] = {
		{0, 0, 0},
		{128, 128, 128},
		{255, 255, 255},

		{-10, 0, 0},
		{0, -10, 0},
		{0, 0, -10},
		{300, 0, 0},
		{0, 300, 0},
		{0, 0, 300},
	};
	size_t test_index;
	t_color *color;

	printf("\033[36m \n\tnew_color_test \n\033[0m");

	test_index = 0;
	while (test_index < new_color_test_COUNT)
	{
		color = new_color(data[test_index][0],
						  data[test_index][1],
						  data[test_index][2]);
		if (test_index == 0 && color->r == 0 && color->g == 0 && color->b == 0)
			print_result(true, test_index);
		else if (test_index == 1 && color->r == 128 && color->g == 128 && color->b == 128)
			print_result(true, test_index);
		else if (test_index == 2 && color->r == 255 && color->g == 255 && color->b == 255)
			print_result(true, test_index);
		else if (test_index > 2 && color == NULL)
			print_result(true, test_index);
		else
			print_result(false, test_index);
		test_index++;
	}
	printf("\n");
}

#define new_color_from_string_COUNT 14
void	new_color_from_string_test(void)
{
	char *data[new_color_from_string_COUNT] = {
			"0,0,0",
			"128,128,128",
			"255,255,255",

			"300,255,255",
			"255,300,255",
			"255,255,300",

			"-255,255,255",
			"255,-255,255",
			"255,255,-255",

			",255,255,255",
			"255,255,25 5",
			"255,25  5,255",
			"255,  255,255",
			"255,255   ,255",
	};
	size_t test_index;
	t_color *color;

	printf("\033[36m \n\tnew_color_from_string_test \n\033[0m");

	test_index = 0;
	while (test_index < new_color_from_string_COUNT)
	{
		color = new_color_from_string(data[test_index]);
		if (test_index == 0 && color->r == 0 && color->g == 0 && color->b == 0)
			print_result(true, test_index);
		else if (test_index == 1 && color->r == 128 && color->g == 128 && color->b == 128)
			print_result(true, test_index);
		else if (test_index == 2 && color->r == 255 && color->g == 255 && color->b == 255)
			print_result(true, test_index);
		else if (test_index > 2 && color == NULL)
			print_result(true, test_index);
		else
			print_result(false, test_index);
		test_index++;
	}
	printf("\n");
}

void test_color(void)
{
//	new_color_test();
	new_color_from_string_test();
}


