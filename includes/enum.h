#ifndef _ENUM_H_
#define _ENUM_H_

typedef enum texture_type
{
  bomb = 0,
  wall = 1,
  ground = 2,
  ground_shadowed = 3,
  pannel = 4,
  timer = 5,
  fire = 6,
} texture_type;

typedef enum bomb_texture_type
{
  bomb_s = 0,
  bomb_m = 1,
  bomb_l = 2
} bomb_texture_type;

enum bomber_sprite_dir
{
  bomber_d = 0,
  bomber_l = 1,
  bomber_r = 2,
  bomber_u = 3,
  die = 4
};

enum bomber_sprite_action
{
  not_move = 0,
  move_r = 1,
  transit_move = 2,
  move_l = 3
};

enum MAP_GRID
{
  FREE_SLOT = 0,
  WALL = 1,
  FIRE = 2,
  FREE_SLOT_SHADOW = 3
};

enum CLIENT_REQUEST_STATUS
{
  BAD_SEND,
  SUCCESS_SEND,
  BAD_RECEIVE,
  SUCCESS_RECEIVE,
  BAD_FREE,
  SUCCESS_FREE,
};

enum COMMAND_REQUEST
{
  NOT_MOVE = 0,
  START_GAME = 1,
  PLACE_BOMB = 2,
  MOVE_UP = 3,
  MOVE_DOWN = 4,
  MOVE_LEFT = 5,
  MOVE_RIGHT = 6,
  GIVE_PLAYERS = 7
};

enum Directions
{
  BOMBER_D = 0,
  BOMBER_L = 1,
  BOMBER_R = 2,
  BOMBER_U = 3,
};

enum Response_type
{
  BOMB,
  MOVE,
  PLAYERS
};

typedef enum Server_status
{
  RUNNING,
  WAITING
} t_server_status;

#endif /* !_ENUM_H_ */
