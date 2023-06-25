/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.c>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 15:36:02 by amitcul           #+#    #+#             */
/*   Updated: 2023/06/23 15:36:02 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef VECTOR_H
#define VECTOR_H

typedef enum s_vector_type
{
	NORMAL,
	NORMALIZED
}	t_vector_type;

typedef struct  s_vector
{
    float   x;
    float   y;
    float   z;
} t_vector;

t_vector    *new_vector(float, float, float);
t_vector	*new_vector_from_strings(const char *str);
t_vector 	*parse_vector(const char *str);
bool 		is_vector(const char *data, t_vector_type type);
void		free_vector(t_vector *vector);

t_vector    *vec_substract(t_vector *, t_vector *);
float       vec_length(t_vector *);
void        vec_normalize(t_vector *);
float       vec_product(t_vector *, t_vector *);

bool is_valid_vector_string(const char *str);

#endif