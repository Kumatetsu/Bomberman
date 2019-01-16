#ifndef _COLLISION_H_
#define _COLLISION_H_

int	has_collision_with_wall(const SDL_Rect zone);
int	has_collision_with_destructible(const SDL_Rect zone);
int	has_collision_with_player(const SDL_Rect zone, int num_player);

#endif /* !_COLLISION_H_ */
