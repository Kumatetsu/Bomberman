#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <pthread.h>
#include "server.h"
#include "thread.h"

//Init de la structure serve servant de store des datas.
t_server 	*create_server(int *ticker) {
  t_server	*s;
  pthread_t	ticker_thread;

  s = NULL;
  if ((s = malloc(sizeof (*s))) == NULL)
      return NULL;

  if (pthread_create(&ticker_thread, NULL, threaded_ticker, ticker)) == -1)
  {
    printf("Ticker thread failed");
    return;
  }

  return s;
}
