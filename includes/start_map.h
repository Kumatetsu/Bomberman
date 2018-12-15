#ifndef _START_MAP_H_
#define _START_MAP_H_

// in the picture, the size of the square is 16 for a wall block, so i use 48
// c'est pas faux
void	*init_sprites_sheet(void *arg);
int	start_map(t_sdl *sdl, int socket, t_player_request *player_request);

#endif /* !_START_MAP_H_ */
