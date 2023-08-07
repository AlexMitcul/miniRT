
#include "../includes/minirt.h"

void	close_app(t_scene *scene)
{
  if (!scene)
	return ;
  free_scene(scene);
  exit(0);
}

t_vector *get_selected_origin(t_scene *scene)
{
  if (scene->selected_type == CAMERA)
	return (scene->camera->origin);
  else if (scene->selected_type == LIGHT)
	return (scene->light->origin);
  else if (scene->selected_type == SPHERE)
	return (scene->selected->sphere->center);
  else if (scene->selected_type == PLANE)
	return (scene->selected->plane->origin);
  else if (scene->selected_type == CYLINDER)
	return (scene->selected->cylinder->center);
  return (scene->camera->origin);
}

void move_object(t_vector *vector, int keycode)
{
  if (keycode == PLUS)
	update(vector, Z, -0.1);
  else if (keycode == MINUS)
	update(vector, Z, 0.1);
  else if (keycode == RIGHT)
	update(vector, X, 0.1);
  else if (keycode == LEFT)
	update(vector, X, -0.1);
  else if (keycode == UP)
	update(vector, Y, -0.1);
  else if (keycode == DOWN)
	update(vector, Y, 0.1);
}

void	move_camera(t_scene *scene, int keycode)
{
  if (keycode == PLUS)
	update(scene->camera->origin, Z, -0.1);
//	scene->camera->origin->z -= 0.1;
  else if (keycode == MINUS)
	update(scene->camera->origin, Z, 0.1);
//  scene->camera->origin->z += 0.1;
  else if (keycode == RIGHT)
	update(scene->camera->origin, X, 0.1);
//	scene->camera->origin->x += 0.1;
  else if (keycode == LEFT)
	update(scene->camera->origin, X, -0.1);
//	scene->camera->origin->x -= 0.1;
  else if (keycode == UP)
	update(scene->camera->origin, Y, -0.1);
//	scene->camera->origin->y -= 0.1;
  else if (keycode == DOWN)
	update(scene->camera->origin, Y, 0.1);
//	scene->camera->origin->y += 0.1;
  // printf("camera origin: %f %f %f\n", scene->camera->origin->x, scene->camera->origin->y, scene->camera->origin->z);
  // new_image(scene);
//  render(scene);
}

void	update_selected_type(t_scene *scene, int direction)
{
  if (scene->is_menu_open)
  {
	scene->selected_type += direction;
	if (scene->selected_type < 0)
	  scene->selected_type = 4;
	else if (scene->selected_type > 4)
	  scene->selected_type = 0;
  }
//  render(scene);
}

void	update_selected_element(t_scene *scene, int direction)
{
  if (scene->selected_type == SPHERE && direction < 0 && scene->selected->sphere->prev)
	scene->selected->sphere = scene->selected->sphere->prev;
  else if (scene->selected_type == SPHERE && direction > 0 && scene->selected->sphere->next)
	scene->selected->sphere = scene->selected->sphere->next;
  else if (scene->selected_type == PLANE && direction < 0 && scene->selected->plane->prev)
	scene->selected->plane = scene->selected->plane->prev;
  else if (scene->selected_type == PLANE && direction > 0 && scene->selected->plane->next)
	scene->selected->plane = scene->selected->plane->next;
  else if (scene->selected_type == CYLINDER && direction < 0 && scene->selected->cylinder->prev)
	scene->selected->cylinder = scene->selected->cylinder->prev;
  else if (scene->selected_type == CYLINDER && direction > 0 && scene->selected->cylinder->next)
	scene->selected->cylinder = scene->selected->cylinder->next;
//  render(scene);
}

int	close_win_with_cross(void *data)
{
  close_app((t_scene *)data);
  return (0);
}

int	close_win(int keycode, t_scene *scene)
{
  if (scene->is_busy)
	return (0);
  printf("keycode: %d\n", keycode);
  if (keycode == ESC)
	close_app(scene);
  if (keycode == ZERO)
  {
	scene->is_menu_open = !scene->is_menu_open;
	// new_image(scene);
	render(scene);
  }
  else if (keycode == UP_ARROW)
	update_selected_type(scene, -1);
  else if (keycode == DOWN_ARROW)
	update_selected_type(scene, 1);
  else if (keycode == RIGHT_ARROW)
	update_selected_element(scene, 1);
  else if (keycode == LEFT_ARROW)
	update_selected_element(scene, -1);
  else
	move_object(get_selected_origin(scene), keycode);
//	move_camera(scene, keycode);
  printf("selected type: %d\n", scene->selected_type);
  render(scene);
  return (0);
}
