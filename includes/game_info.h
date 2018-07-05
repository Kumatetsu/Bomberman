#ifndef _GAME_INFO_H_
#define _GAME_INFO_H_

#include <stdlib.h>
#include "player.h"
#include "player_info.h"
#include "client.h"
#include "server.h"

typedef struct 	s_map_destroyable
{
  int		y_pos;                  /* La position y de l'element */
  int		x_pos;                  /* La position x de l'element */
  int		bomb;
  int		bomb_owner;
  int		dying;
  int		start_explode;
  int		wall_destroyable;
  int		exist;
}		t_map_destroyable;

typedef struct		s_game_info
{
  int			checksum;               /* Un checksum simple */
  int			tick_time;
  int     nb_client;
  int 			game_status;
  int			id_client;
  t_player_info		players[4];
  t_map_destroyable	map_destroyable[14][15];
} 			t_game_info;

t_game_info	*get_game_info();
void		set_game_info(t_game_info *new_game_info);

enum MAP_GRID {
	FREE_SLOT = 0,
	WALL = 1,
	FIRE = 2,
};

int**			get_array_map();
void			add_destructible_elements(t_game_info *game_info, int** map_pointer);
void			add_bomb_elements(t_game_info *game_info, int** map_pointer);
void			destroy_bomb(t_game_info *game_info,
				     int** map_pointer,
				     t_map_destroyable bomb_to_destroy);
t_map_destroyable	get_element_at_pos(t_game_info *game_info, int x, int y);
void			trigger_bomb(t_game_info *game_info, int** map_pointer, t_map_destroyable bomb);
void			handle_requests(t_game_info *game_info, t_player_request *player_request);
int			check_collision(int** map, t_player_request *player_request);
void			move_player(t_game_info *game_info, t_player_request *player_request, int **map_pointer);
void			create_game_info(t_srv **srv);
long			random_at_most(long max);
void			specify_player_info(int i, t_game_info *game_info);
void			process_requests(t_srv **server);
void			add_request_to_server(t_srv **srv, t_player_request *player_request);
void			place_bomb(t_game_info *game_info, t_player_request *player_request);
int 			apply_explosion(t_map_destroyable element, t_map_destroyable bomb, t_game_info *game_info,
							   int **map_pointer);
void    		apply_bomb_to_position(t_map_destroyable bomb, int **map_pointer, t_game_info *game_info, int i);
void			add_request_to_server(t_srv **srv, t_player_request *player_request);

#endif
