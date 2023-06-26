//
// Created by amitcul on 6/25/23.
//

#ifndef MINIRT_TEST_H
#define MINIRT_TEST_H

void	test(void);

void validate(bool status, size_t test_index);

void test_color(void);
void test_parser(void);

/*
 *  Light
 */
void test_parse_ambient_light(void);
void test_parse_light(void);

/*
 *  Figures
 */
void test_parse_sphere(void);

#endif //MINIRT_TEST_H
