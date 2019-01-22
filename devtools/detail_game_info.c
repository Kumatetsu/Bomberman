#include <stdio.h>
#include "enum.h"
#include "constant.h"
#include "sdl.h"
#include "player_info.h"
#include "map.h"
#include "client_request.h"
#include "server.h"
#include "game_info.h"
#include "game_info_serialization.h"

void			detail_game_info()
{
  int			i;
  t_game_info		*gi;
  char			details[72];
  char			players_detail[500];
  char			map_detail[23960];
  t_player_info		p;
  t_map_destroyable	m;
  char			total_detail[72 + 500 + 23960];

  gi = get_game_info();
  snprintf(details, sizeof details, "\nchecksum: %d\ntick_time: %d\nnb_client: %d\ngame_status: %d\nid_client: %d", gi->checksum, gi->tick_time, gi->nb_client, gi->game_status, gi->id_client);
  for (i = 0; i < 4; i++)
    {
      p = gi->players[i];
      if (p.connected)
        printf("PLAYER CONNECTED:\nnum_player: %d\nx: %d\ny: %d\n", i, p.x, p.y);
      snprintf(players_detail, sizeof players_detail, "\nPlayers:\nconnected: %d\nalive: %d\ndying: %d\nx: %d\ny: %d\ncurrent_dir: %d\nbomb_left: %d\nfd: %d\nnum_player: %d", p.connected, p.alive, p.dying, p.x, p.y, p.current_dir, p.bomb_left, p.fd, p.num_player);
    }
  for (i = 0; i < INLINE_MATRIX; i++)
    {
      m = gi->map_destroyable[i];
      if (m.exist == 1)
	{
	  snprintf(map_detail, sizeof map_detail, "\nMap detail for [%d]:\ny: %d\nx: %d\nbomb: %d\nbomb_owner: %d\nstart_explode:%d\nwall_destroyable: %d\nexist: %d\n", i, m.y, m.x, m.bomb, m.bomb_owner, m.start_explode, m.wall_destroyable, m.exist);
	}
    }
  snprintf(total_detail, sizeof total_detail, "\nGAME INFO:\n%s\nPLAYERS:\n%s\nMAP:\n%s\n", details, players_detail, map_detail);
  printf(total_detail);
  printf("\nopen file\n");
  FILE	*f = fopen("game_info.txt", "w");
  if (f == NULL)
    {
      printf("\nOpen file failed\n");
      return;
    }
  printf("\nfile successfully opened\n");
  //  printf("\nserialized game_info: %s\n", gi);
  fprintf(f, total_detail);

  printf("\nwritten in file done\n");
  fclose(f);
  printf("\nfile closed\n");
}
