/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 10:59:19 by amitcul           #+#    #+#             */
/*   Updated: 2023/07/17 10:59:51 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

void	test(void);

void	validate(bool status, size_t test_index);

void	test_color(void);
void	test_parser(void);

/*
 *  Light
 */
void	test_parse_ambient_light(void);
void	test_parse_light(void);

/*
 *  Figures
 */
void	test_parse_sphere(void);
void	test_parse_plane(void);

#endif //MINIRT_TEST_H
