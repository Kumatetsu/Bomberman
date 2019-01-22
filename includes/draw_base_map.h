#ifndef _DRAW_BASE_MAP_H_
#define _DRAW_BASE_MAP_H_

void	*draw_map_model(void *arg);
void	draw_explosion(void *arg, t_map_destroyable bomb_origin, int bomb_origin_index);
void	draw_destroyable_model(void *arg);
int	draw_timer(void *arg);
int	draw_pannel(void *arg);

#endif /* !_DRAW_BASE_MAP_H_ */
