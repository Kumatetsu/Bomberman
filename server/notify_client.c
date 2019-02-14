#include <stdio.h>
#include <unistd.h>
#include "sdl.h"
#include "player_info.h"
#include "client_request.h"
#include "server.h"
#include "server_request.h"
#include "moving.h"
#include "bomb.h"

void			notify_actual_players(t_srv **server, int id_player)
{
  printf("sever: in notify actual players\n");
  t_response_players	players_pool;

  players_pool.id = PLAYERS;
  for (id_player = 0; id_player < 4; id_player++)
    {
      players_pool.players[id_player] = (*server)->players[id_player];
    }
  for (id_player = 0; id_player < 4; id_player++)
    {
      if ((*server)->players[id_player].fd == -1) {
	continue;
      }
#ifdef _WIN32
      int nbrBytes = 0;
      if ((nbrBytes = send((*server)->players[id_player].fd, (void*)&players_pool, sizeof(players_pool), 0)) < 0) {
	  printf("error %d sending from notify_actual_players to client num %d \n", WSAGetLastError(), id_player);
	} else {
	  printf("send to client num %d from notify_actual_players : %d bytes \n ", id_player, nbrBytes);
	}
#else
      write((*server)->players[id_player].fd, &players_pool, sizeof(players_pool));
#endif
    }
}

void			notify_move_up(t_srv **server, int id_player)
{
  t_response_up_pos	players_pool;
  int			i;
  
  printf("in move up player\n");
  move_player(server, MOVE_UP, id_player);
  players_pool.id = MOVE_U;
  players_pool.player_id = id_player;
  players_pool.x = (*server)->players[id_player].x;
  players_pool.y = (*server)->players[id_player].y;
  players_pool.direction = (*server)->players[id_player].direction_sprite;
  players_pool.action = (*server)->players[id_player].action_sprite;
  for (i = 0; i < 4; i++)
    {
      if ((*server)->players[i].fd == -1) {
	continue;
      }
#ifdef _WIN32
      int nbrBytes = 0;
      if ((nbrBytes = send((*server)->players[i].fd, (void*)&players_pool, sizeof(players_pool), 0)) < 0) {
	  printf("error %d sending from notify_move_up to client num %d \n", WSAGetLastError(), i);
	} else {
	  printf("send to client num %d from notify_move_up : %d bytes \n ", i, nbrBytes);
	}
#else
      write((*server)->players[i].fd, &players_pool, sizeof(players_pool));
#endif
    }
}

void			notify_move_down(t_srv **server, int id_player)
{
  t_response_up_pos	players_pool;
  int			i;
  
  printf("in move down player\n");
  move_player(server, MOVE_DOWN, id_player);
  players_pool.id = MOVE_D;
  players_pool.player_id = id_player;
  players_pool.x = (*server)->players[id_player].x;
  players_pool.y = (*server)->players[id_player].y;
  players_pool.direction = (*server)->players[id_player].direction_sprite;
  players_pool.action = (*server)->players[id_player].action_sprite;
  for (i = 0; i < 4; i++)
    {
      if ((*server)->players[i].fd == -1) {
	continue;
      }
#ifdef _WIN32
      int nbrBytes = 0;
      if ((nbrBytes = send((*server)->players[i].fd, (void*)&players_pool, sizeof(players_pool), 0)) < 0) {
	  printf("error %d sending from notify_move_down to client num %d \n", WSAGetLastError(), i);
	} else {
	  printf("send to client num %d from notify_move_down : %d bytes \n ", i, nbrBytes);
	}
#else
      write((*server)->players[i].fd, &players_pool, sizeof(players_pool));
#endif
    }
}

void			notify_move_left(t_srv **server, int id_player)
{
  t_response_up_pos	players_pool;
  int			i;
  
  printf("in move left player\n");
  move_player(server, MOVE_LEFT, id_player);
  players_pool.id = MOVE_L;
  players_pool.player_id = id_player;
  players_pool.x = (*server)->players[id_player].x;
  players_pool.y = (*server)->players[id_player].y;
  players_pool.direction = (*server)->players[id_player].direction_sprite;
  players_pool.action = (*server)->players[id_player].action_sprite;
  for (i = 0; i < 4; i++)
    {
      if ((*server)->players[i].fd == -1) {
	continue;
      }
#ifdef _WIN32
      int nbrBytes = 0;
      if ((nbrBytes = send((*server)->players[i].fd, (void*)&players_pool, sizeof(players_pool), 0)) < 0) {
	  printf("error %d sending from notify_move_left to client num %d \n", WSAGetLastError(), i);
	} else {
	  printf("send to client num %d from notify_move_left : %d bytes \n ", i, nbrBytes);
	}
#else
      write((*server)->players[i].fd, &players_pool, sizeof(players_pool));
#endif
    }
}

void			notify_move_right(t_srv **server, int id_player)
{
  t_response_up_pos	players_pool;
  int			i;
  
  printf("in move right player\n");
  move_player(server, MOVE_RIGHT, id_player);
  players_pool.id = MOVE_R;
  players_pool.player_id = id_player;
  players_pool.x = (*server)->players[id_player].x;
  players_pool.y = (*server)->players[id_player].y;
  players_pool.direction = (*server)->players[id_player].direction_sprite;
  players_pool.action = (*server)->players[id_player].action_sprite;
  for (i = 0; i < 4; i++)
    {
      if ((*server)->players[i].fd == -1) {
	continue;
      }
#ifdef _WIN32
      int nbrBytes = 0;
      if ((nbrBytes = send((*server)->players[i].fd, (void*)&players_pool, sizeof(players_pool), 0)) < 0) {
	  printf("error %d sending from notify_move_right to client num %d \n", WSAGetLastError(), i);
	} else {
	  printf("send to client num %d from notify_move_right : %d bytes \n ", i, nbrBytes);
	}
#else
      write((*server)->players[i].fd, &players_pool, sizeof(players_pool));
#endif
    }
}

void			notify_put_bomb(t_srv **server, int id_player)
{
  t_response_bomb	players_pool;
  t_map_destroyable	*bomb;
  int			index[1];
  int			i;
  
  printf("server put_bomb for player: %d\n", id_player);
  if ((bomb = place_bomb(server, id_player, index)) == NULL) {
    return;
  }
  players_pool.id = BOMB;
  players_pool.bomb = (*bomb);
  players_pool.index = index[0];
  for (i = 0; i < 4; i++)
    {
      if ((*server)->players[i].fd == -1) {
	continue;
      }
#ifdef _WIN32
      int nbrBytes = 0;
      if ((nbrBytes = send((*server)->players[i].fd, (void*)&players_pool, sizeof(players_pool), 0)) < 0) {
	  printf("error %d sending from notify_put_bomb to client num %d \n", WSAGetLastError(), i);
	} else {
	  printf("send to client num %d from notify_put_bomb : %d bytes \n ", i, nbrBytes);
	}
#else
      write((*server)->players[i].fd, &players_pool, sizeof(players_pool));
#endif
    }
}
