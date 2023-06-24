



#include "../../includes/minirt.h"

void validate(bool status, size_t test_index)
{
	if (status == true)
		printf("\033[32m Test %zu - OK \n\033[0m", test_index);
	else
		printf("\033[31m Test %zu - KO \n\033[0m", test_index);
}

#define test_is_valid_file_extension_COUNT 6
void test_is_valid_file_extension(void)
{
	char *filenames[test_is_valid_file_extension_COUNT] = {
			"valid.rt",
			"file.rt.rt",
			".rt",
			"file",
			"as.r",
			".r",
	};
	bool results[test_is_valid_file_extension_COUNT] = {
			true,
			true,
			false,
			false,
			false,
			false,
	};
	size_t test_index;
	bool result;

	printf("\033[36m \n\ttest_is_valid_file_extension \n\033[0m");
	test_index = 0;
	while (test_index < sizeof(filenames) / sizeof(char *))
	{
		result = is_valid_file_extension(filenames[test_index]);
		validate(result == results[test_index], test_index);
		test_index++;
	}
	printf("\n");
}


#define test_is_valid_line_items_count_COUNT 18
void test_is_valid_line_items_count(void)
{
	char *tests[test_is_valid_line_items_count_COUNT] = {
			"A 0.2 255,255,255",
			"A 255,255,255",
			"  A 0.2 0.2 255,255,255",

			"C -50.0,0,20 0,0,1 70",
			"C -50.0,0,20 0,0,1 ",
			"C -50.0,0,20 0,0,1 70 79",

			"L -40.0,50.0,0.0 0.6 10,0,255",
			"L -40.0,50.0,0.0 0.6",
			"L -40.0,50.0,0.0 0.6 0.6 10,0,255",

			"sp 0.0,0.0,20.6 12.6 10,0,25",
			"sp 0.0,0.0,20.6 12.6 ",
			"sp 0.0,0.0,20.6 12.6 12.6 10,0,25",

			"pl 0.0,0.0,-10.0 0.0,1.0,0.0 0,0,225",
			"pl 0.0,0.0,-10.0 0.0,1.0,0.0",
			"pl pl 0.0,0.0,-10.0 0.0,1.0,0.0  0,0,225",

			"cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255",
			"cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 ",
			"cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 21 10,0,255",
	};
	bool results[test_is_valid_line_items_count_COUNT] = {
			true, false, false
	};
	size_t test_index;
	char **splitted;
	bool result;

	printf("\033[36m \ttest_is_valid_line_items_count \n\033[0m");
	test_index = 0;
	while (test_index < sizeof(tests) / sizeof(char *))
	{
		splitted = ft_split(tests[test_index], ' ');
		result = is_valid_line_items_count(splitted);
		validate(result == results[test_index % 3], test_index);
		test_index++;
	}
	printf("\n");
}

#define test_parse_ambient_light_COUNT 18
void test_parse_ambient_light(void)
{
	char *data[test_parse_ambient_light_COUNT] = {
			"A 0.0 255,255,255",	// true,
			"A 1.0 255,255,255",	// true,
			"A 0.2 0,0,0",			// true,
			"A 0.2 255,255,255",	// true,
			"  A   0.2  255,255,255   ",	// true,

			"A 0.2 -255,255,255",	// false,
			"A 0.2 255,-255,255",	// false,
			"A 0.2 255,255,-255",	// false,
			"A 0.2 500,255,255",	// false,
			"A 0.2 255,500,255",	// false,
			"A 0.2 255,255,500",	// false,
			"A 0,2 255,255,255",	// false,
			"a 0.2 255,255,255",	// false,
			"A -0.2 255,255,255",	// false,
			"A 1.00000000000001 255,255,255", // false
	};
	bool results[test_parse_ambient_light_COUNT] = {
			true,
			true,
			true,
			true,
			true,
			false,
			false,
			false,
			false,
			false,
			false,
			false,
			false,
			false,
			false,
	};
	size_t test_index;
	bool result;
	char **splitted;
	t_scene *scene;

	printf("\033[36m \n\ttest_is_valid_file_extension \n\033[0m");
	test_index = 0;
	while (test_index < sizeof(data) / sizeof(char *))
	{
		scene = new_scene(0, 0);
		splitted = ft_split(data[test_index], ' ');
		result = parse_ambient_light(scene, splitted);
		validate(result == !results[test_index], test_index);
		test_index++;
		free_scene(scene);
	}
	printf("\n");
}


void test_parser(char *filename)
{
	(void)filename;
//	test_is_valid_file_extension();
//	test_is_valid_line_items_count();
	test_parse_ambient_light();
}