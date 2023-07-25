/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_parser_tests.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 14:05:25 by amitcul           #+#    #+#             */
/*   Updated: 2023/07/25 12:37:29 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minirt.h"

static bool plane_compare(t_plane *a, t_plane *b)
{
    if (a == NULL && b == NULL)
        return (true);
    if (a == NULL || b == NULL)
        return (false);
    if (vector_compare(a->origin, b->origin) &&
        vector_compare(a->direction, b->direction) &&
        color_compare(a->color, b->color))
        return (true);
    return (false);
}

#define test_parse_plane_COUNT 6
void test_parse_plane(void)
{
    char *data[test_parse_plane_COUNT] = {
            "pl 0.0,0.0,-10.0 0.0,1.0,0.0 0,0,255",
            "pl 0.0,0.0,-10.0 0.0,-1.0,0.0 0,0,255",

            /* Invalid color */
            "pl 0.0,0.0,-10.0 0.0,1.0,0.0 0,0,-225",
            "pl 0.0,0.0,-10.0 0.0,1.0,0.0 3000,0,225",

            /* Invalid normaled vector */
            "pl 0.0,0.0,-10.0 0.0,1.1,0.0 0,0,225",
            "pl 0.0,0.0,-10.0 0.0,1.0,-1.1 0,0,225",
    };
    t_plane planes[2] = {
            {
                new_vector(0, 0, -10),
                new_vector(0, 1,0 ),
                new_color(0, 0, 255),
                NULL
             },
            {
                new_vector(0, 0, -10),
                new_vector(0, -1,0 ),
                new_color(0, 0, 255),
                NULL
            }
    };

    size_t test_index;
    char **splitted;
    t_scene *scene;

    printf("\033[36m \n\ttest_parse_plane \n\033[0m");
    test_index = 0;
    while (test_index < sizeof(data) / sizeof(char *))
    {
        scene = new_scene();
        splitted = ft_split(data[test_index], ' ');
        parse_plane(scene, splitted);
        if (test_index < 2)
            validate(plane_compare(scene->planes, &planes[test_index]), test_index);
        else
            validate(plane_compare(scene->planes, NULL), test_index);
        test_index++;
        free_scene(scene);
    }
    printf("\n");
}
