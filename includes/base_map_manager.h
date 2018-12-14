/*
** base_map.h for Project-Master in /home/enach/CLionProjects/Bomberman
**
** Made by hochar_n
** Login   <hochar_n@etna-alternance.net>
**
** Started on  Thu Jul  5 21:38:24 2018 hochar_n
** Last update Thu Jul  5 21:38:25 2018 hochar_n
*/

#ifndef _BASE_MAP_MANAGER_H_
#define _BASE_MAP_MANAGER_H_

typedef enum	texture_type
  {
    bomb = 0,
    wall = 1,
    ground = 2,
    ground_shadowed = 3,
    pannel = 4,
    timer = 5,
  }		texture_type;

// pas ici...
typedef enum	bomb_texture_type
  {
    bomb_s = 0,
    bomb_m = 1,
    bomb_l = 2
  }		bomb_texture_type;

// in the picture, the size of the square is 16 for a wall block, so i use 48

static const int WINDOW_W = 1024;
static const int WINDOW_H = 768;
static const int PIXEL_SIZE = 48;
static const int I_BEGIN = ((1024 - (15 * 48)) / 2 ) / 48;
static const int J_BEGIN = (768 - (13 * 48)) / 48;

void *init_sprites_sheet(void *arg);

//game_map/white_bomber.c
void *white_bomber_sprite(void *arg);

//game_map/black_bomber.c
void *black_bomber_sprite(void *arg);

//game_map/red_bomber.c
void *red_bomber_sprite(void *arg);

//game_map/blue_bomber.c
void *blue_bomber_sprite(void *arg);

//game_map/bomb.c
void *bomb_sprite(void *arg);

SDL_Rect init_rect(int x, int y, int w, int z);
t_map init_t_map(SDL_Rect src, SDL_Rect dest, texture_type type);
void *draw_all(void *arg);
void *rebuild_map(void *arg);

//base_map/draw_players.c
void *draw_player_1(void *arg);
void *draw_player_2(void *arg);
void *draw_player_3(void *arg);
void *draw_player_4(void *arg);

#endif /* !_BASE_MAP_MANAGER_H_ */
