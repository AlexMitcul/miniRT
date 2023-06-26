/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tests.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.c>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 11:01:38 by amitcul           #+#    #+#             */
/*   Updated: 2023/06/26 11:02:04 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

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

void test_parser(void)
{
    test_is_valid_file_extension();
    test_is_valid_line_items_count();
    test_parse_ambient_light();
    test_parse_light();
    test_parse_sphere();
    test_parse_plane();
}
