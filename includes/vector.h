/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenses- <amenses-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 15:36:02 by amitcul           #+#    #+#             */
/*   Updated: 2023/08/06 19:18:12 by amenses-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

typedef enum s_vector_type
{
	NORMAL,
	NORMALIZED
}	t_vector_type;

typedef struct s_vector
{
	float	x;
	float	y;
	float	z;
}			t_vector;

t_vector	*new_vector(float x, float y, float z);
t_vector	*new_vector_from_strings(const char *str);
t_vector	*parse_vector(const char *str);
bool		is_vector(const char *data, t_vector_type type);
void		free_vector(t_vector *vector);

/* vector_operations.c */
t_vector	*vec_add(t_vector *a, t_vector *b);
t_vector	*vec_substract(t_vector *a, t_vector *b);
float		vec_length(t_vector *vector);
void		vec_normalize(t_vector *vector);
float		vec_product(t_vector *a, t_vector *b);

/* vector_operations_1.c */
t_vector 	*vec_dup(t_vector *v);
t_vector	*vec_multiply(float scalar, t_vector *v);
t_vector	*vec_cross_product(t_vector *a, t_vector *b);
t_vector	*vec_point(t_vector *origin, t_vector *directions, float t);

bool		is_valid_vector_string(const char *str);
bool		vector_compare(t_vector *a, t_vector *b);

#endif
