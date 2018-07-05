/*
** base_map.h for Project-Master in /home/enach/CLionProjects/Bomberman
** 
** Made by hochar_n
** Login   <hochar_n@etna-alternance.net>
** 
** Started on  Thu Jul  5 21:38:24 2018 hochar_n
** Last update Thu Jul  5 21:38:25 2018 hochar_n
*/

#ifndef _BASE_MAP_H_
#define _BASE_MAP_H_

typedef enum	texture_type
  {
    bomb = 0,
    wall = 1,
    ground = 2,
    ground_shadowed = 3,
    pannel = 4,
    timer = 5,
  }		texture_type;

typedef enum	bomb_texture_type
  {
    bomb_s = 0,
    bomb_m = 1,
    bomb_l = 2
  }		bomb_texture_type;

typedef struct	s_map
{
  SDL_Rect	src_rect;
  SDL_Rect	dest_rect;
  texture_type  texture_type;
}		t_map;

typedef struct	s_data
{
  SDL_Texture	*texture;
  SDL_Renderer	*renderer;
  SDL_Window	*window;
  t_map		array_map[14][15];
  t_player	players[4];
  SDL_Rect	destroyable[3][3];
}		t_data;

// in the picture, the size of the square is 16 for a wall block, so i use 48

static const int WINDOW_W = 1024;
static const int WINDOW_H = 768;
static const int PIXEL_SIZE = 48;
static const int I_BEGIN = ((1024 - (15 * 48)) / 2 ) / 48;
static const int J_BEGIN = (768 - (13 * 48)) / 48;


//start_map.c
int start_map(t_sdl *sdl, int socket, t_player_request *cr);
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

//base_map/init_tools.c
SDL_Rect init_rect(int x, int y, int w, int z);
t_map init_t_map(SDL_Rect src, SDL_Rect dest, texture_type type);


//base_map/base_map_manager.c
void *draw_all(void *arg);
void *rebuild_map(void *arg);

//base_map/draw_base_map.c
void *draw_map_model(void *arg);
void *draw_timer(void *arg);
void *draw_pannel(void *arg);

//base_map/draw_players.c
void *draw_player_1(void *arg);
void *draw_player_2(void *arg);
void *draw_player_3(void *arg);
void *draw_player_4(void *arg);

#endif
