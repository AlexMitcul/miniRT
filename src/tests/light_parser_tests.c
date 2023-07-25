/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_parser_tests.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 09:08:03 by amitcul           #+#    #+#             */
/*   Updated: 2023/07/25 12:38:06 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static bool ambient_light_compare(t_ambient_light *a, t_ambient_light *b)
{
	if (a == NULL && b == NULL)
		return (true);
	if (a == NULL || b == NULL)
		return (false);
	if (a->lighting == b->lighting &&
		a->color->r == b->color->r &&
		a->color->g == b->color->g &&
		a->color->b == b->color->b)
		return (true);
	return (false);
}

#define test_parse_ambient_light_COUNT 16
void test_parse_ambient_light(void)
{
	char *data[test_parse_ambient_light_COUNT] = {
			"A 0.0 255,255,255",			// true,
			"A 1.0 255,255,255",			// true,
			"A 0.2 0,0,0",				// true,
			"A 0.2 255,255,255",			// true,
			"  A   0.2  255,255,255   ",	// true,

			"A 0.2 -255,255,255",		// false,
			"A 0.2 255,-255,255",		// false,
			"A 0.2 255,255,-255",		// false,
			"A 0.2 500,255,255",		// false,
			"A 0.2 255,500,255",		// false,
			"A 0.2 255,255,500",		// false,
			"A 0,2 255,255,255",		// false,
			"A -0.2 255,255,255",	// false,
			"A 0. 255,255,255",		// false,
			"A -0. 255,255,255",		// false,
			"A 1.001 255,255,255",	// false
	};
	t_ambient_light lights[5] = {
			{new_color(255, 255, 255), 0.0f},
			{new_color(255, 255, 255), 1.0f},
			{new_color(0, 0, 0), 0.2f},
			{new_color(255, 255, 255), 0.2f},
			{new_color(255, 255, 255), 0.2f},
	};

	size_t test_index;
	char **splitted;
	t_scene *scene;

	printf("\033[36m \n\ttest_is_valid_file_extension \n\033[0m");
	test_index = 0;
	while (test_index < sizeof(data) / sizeof(char *))
	{
		scene = new_scene();
		splitted = ft_split(data[test_index], ' ');
		parse_ambient_light(scene, splitted);
		if (test_index < 5)
			validate(ambient_light_compare(scene->ambient_light, &lights[test_index]), test_index);
		else
			validate(ambient_light_compare(scene->ambient_light, NULL), test_index);
		test_index++;
		free_scene(scene);
	}
	printf("\n");
}

static bool light_compare(t_light *a, t_light *b)
{
    if (a == NULL && b == NULL)
        return (true);
    if (a == NULL || b == NULL)
        return (false);
    if (a->brightness == b->brightness &&
        vector_compare(a->origin, b->origin) &&
        color_compare(a->color, b->color))
        return (true);
    return (false);
}

// L -40.0,50.0,0.0 0.6 10,0,255
#define test_parse_light_COUNT 12
void test_parse_light(void)
{
    char *data[test_parse_light_COUNT] = {
            "L -40.0,50.0,0.0 0.6 10,0,255",
            "L -40.0,50.0,500.0 0.2 255,255,255",

            /* float range error */
            "L -40.0,50.0,0.0 -0.1 10,0,255",
            "L -40.0,50.0,0.0 1.1 10,0,255",

            /* color errors */
            "L -40.0,50.0,0.0 0.6 300,0,255",
            "L -40.0,50.0,0.0 0.6 10,-10,255",
            "L -40.0,50.0,0.0 0.6 10,0,   255",
            "L -40.0,50.0,0.0 0.6 10 ,  0,255",

            /* vector error */
            "L -40 .0,50.0,0.0 0.6 10,0,255",
            "L -40.0,  50.0,0.0 0.6 10,0,255",
            "L -40.0,50.0,  0.0 0.6 10,0,255",
            "L -40.0,50.0,0.0- 0.6 10,0,255",
    };
    t_light lights[2] = {
            {
                new_vector(-40, 50, 0),
                0.6f,
                new_color(10, 0, 255)
            },
            {
                    new_vector(-40, 50, 500),
                    0.2f,
                    new_color(255, 255, 255)
            },
    };

    size_t test_index;
    char **splitted;
    t_scene *scene;

    printf("\033[36m \n\ttest_parse_light \n\033[0m");
    test_index = 0;
    while (test_index < sizeof(data) / sizeof(char *))
    {
        scene = new_scene();
        splitted = ft_split(data[test_index], ' ');
        parse_light(scene, splitted);
        if (test_index < 2)
            validate(light_compare(scene->light, &lights[test_index]), test_index);
        else
            validate(light_compare(scene->light, NULL), test_index);
        test_index++;
        free_scene(scene);
    }
    printf("\n");
}
