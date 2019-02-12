#ifndef _NOTIFY_CLIENT_H_
#define _NOTIFY_CLIENT_H_

#include "player_info.h"

void notify_actual_players(t_srv **server, int id_player);

void notify_move_up(t_srv **server, int id_player);

void notify_move_down(t_srv **server, int id_player);

void notify_move_left(t_srv **server, int id_player);

void notify_move_right(t_srv **server, int id_player);

void notify_put_bomb(t_srv **server, int id_player);

#endif
