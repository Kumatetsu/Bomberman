/*
** moving.c for Project-Master in /home/enach/CLionProjects/Bomberman/bm_test/server
**
** Made by hochar_n
** Login   hochar_n@etna-altenance.net
**
** Started on  Sun Jul  1 17:39:23 2018 hochar_n
** Last update Mon Jul  2 21:01:32 2018 hochar_n
*/

#include <stdio.h>
#include "my_put.h"
#include "enum.h"
#include "sdl.h"
#include "player_info.h"
#include "client_request.h"
#include "server.h"
#include "map.h"
#include "game_info.h"
#include "constant.h"
#include "collision.h"
#include "moving.h"

void	move_player(t_srv **srv, enum COMMAND_REQUEST command, int num_player)
{
  printf("server: in move_player\n");
  // x = width, y = height, sprite = visual to apply in the front
  int	new_x, new_y;
  int	sprite_direction;

  new_x = 0;
  new_y = 0;
  if ((*srv)->players[num_player].connected == 0) {
    return;
  }
  switch (command)
    {
    case MOVE_UP:
      new_y = (*srv)->players[num_player].y - 24;
      new_x = (*srv)->players[num_player].x;
      sprite_direction = bomber_u;
      break;

    case MOVE_DOWN:
      new_y = (*srv)->players[num_player].y + 24;
      new_x = (*srv)->players[num_player].x;
      sprite_direction = bomber_d;
      break;

    case MOVE_RIGHT:
      new_x = (*srv)->players[num_player].x + 24;
      new_y = (*srv)->players[num_player].y;
      sprite_direction = bomber_r;
      break;

    case MOVE_LEFT:
      new_x = (*srv)->players[num_player].x - 24;
      new_y = (*srv)->players[num_player].y;
      sprite_direction = bomber_l;
      break;

    default:
      command = NOT_MOVE;
      break;
    }

  if (check_collision(srv, new_x, new_y, num_player) == 0) {
    return;
  }

  if ((*srv)->players[num_player].alive) {
      (*srv)->players[num_player].x = new_x;
      (*srv)->players[num_player].y = new_y;
    }

  change_sprite(&(*srv)->players[num_player], sprite_direction, command);
  printf("server: updated_client_pos: x:%d y:%d\n", (*srv)->players[num_player].x, (*srv)->players[num_player].y);
}

void	change_sprite(t_player_info *player, int sprite_direction, int player_command)
{
  int	next_action_sprite;

  // Death management
  if (player->alive == 0) {
      player->action_sprite = 0;
      return;
    }

  // Well there are no many ways to don't move...
  if (player_command == not_move) {
      next_action_sprite = not_move;
      player->action_sprite = next_action_sprite;
      return;
    }

  switch (player->action_sprite)
    {
    case move_l:
      next_action_sprite = move_r;
      break;
    case move_r:
      next_action_sprite = move_l;
    default:
      next_action_sprite = move_l;
      break;
    }
  player->direction_sprite = sprite_direction;
  player->action_sprite = next_action_sprite;
  return;
}

int			check_collision(t_srv **srv,
					int requested_x,
					int requested_y,
					int num_player)
{
  const SDL_Rect	player = {requested_x, requested_y + 46, PIXEL_SIZE - 12, 21};

  if (has_collision_with_wall(player)) {
    return (0);
  }
  if (has_collision_with_destructible(srv, player)) {
    return (0);
  }
  if (has_collision_with_player(srv, player, num_player) >= 0) {
    return (0);
  }
  return (1);
}
