/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_parser_tests.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 11:47:46 by amitcul           #+#    #+#             */
/*   Updated: 2023/07/25 12:38:30 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minirt.h"

static bool sphere_compare(t_sphere *a, t_sphere *b)
{
    if (a == NULL && b == NULL)
        return (true);
    if (a == NULL || b == NULL)
        return (false);
    if (a->radius  == b->radius &&
        vector_compare(a->center, b->center) &&
        color_compare(a->color, b->color))
        return (true);
    return (false);
}

#define test_parse_sphere_COUNT 7
void test_parse_sphere(void)
{
    char *data[test_parse_sphere_COUNT] = {
            "sp 0.0,0.0,20.6 12.6 10,0,255",
            "sp 0,0,20 12 10,0,255",
            "sp 0,0.0,0.0 12 10,0,255",

            /* float range error */
            "sp 0.0,0.0,20.6 0.0 10,0,255",
            "sp 0.0,0.0,20.6 0 10,0,255",
            "sp 0.0,0.0,20.6 -2 10,0,255",
            "sp 0.0,0.0,20.6 -2.0 10,0,255",
    };
    t_sphere spheres[3] = {
            {
                    new_vector(0, 0, 20.6),
                    12.6f / 2,
                    new_color(10, 0, 255),
                    NULL
            },
            {
                    new_vector(0, 0, 20),
                    12.0f / 2,
                    new_color(10, 0, 255),
                    NULL
            },
            {
                    new_vector(0, 0, 0),
                    12.0f / 2,
                    new_color(10, 0, 255),
                    NULL
            },
    };

    size_t test_index;
    char **splitted;
    t_scene *scene;

    printf("\033[36m \n\ttest_parse_sphere \n\033[0m");
    test_index = 0;
    while (test_index < sizeof(data) / sizeof(char *))
    {
        scene = new_scene();
        splitted = ft_split(data[test_index], ' ');
        parse_sphere(scene, splitted);
        if (test_index < 3)
            validate(sphere_compare(scene->spheres, &spheres[test_index]), test_index);
        else
            validate(sphere_compare(scene->spheres, NULL), test_index);
        test_index++;
        free_scene(scene);
    }
    printf("\n");
}
