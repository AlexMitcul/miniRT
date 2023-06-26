//
// Created by Alexandru Mitcul on 26/06/2023.
//

#ifndef MINIRT_CYLINDER_H
#define MINIRT_CYLINDER_H

# include "minirt.h"

typedef struct s_cylinder
{
    t_vector *center;
    t_vector *axis;
    float radius;
    float height;
    t_color *color;
    struct s_cylinder *next;
}   t_cylinder;

t_cylinder *cylinder(t_vector *center, t_vector *axis,
                     float radius, float height, t_color *color);
void    cylinder_add_to_scene(t_scene *scene, t_cylinder *cylinder);

#endif //MINIRT_CYLINDER_H
