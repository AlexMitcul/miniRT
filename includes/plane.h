//
// Created by Alexandru Mitcul on 26/06/2023.
//

#ifndef MINIRT_PLANE_H
#define MINIRT_PLANE_H

# include "minirt.h"

typedef struct s_plane
{
    t_vector *origin;
    t_vector *direction;
    t_color *color;
    struct s_plane *next;
}   t_plane;

t_plane *new_plane(t_vector *origin, t_vector *destination, t_color *color);
void    pland_add_to_scene(t_scene *scene, t_plane *plane);

#endif //MINIRT_PLANE_H
