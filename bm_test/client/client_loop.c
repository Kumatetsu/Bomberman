#include <stdio.h>
#include "client.h"

void	my_bzero(void *s1, int n)
{
  char	*c;

  c = (char *)s1;
  while (n > 0)
    {
      *c++ = 0;
      n--;
    }
}

int         send_input(int s, t_client_request* client_request)
{
  char*     request_string;

  request_string = get_request_string(client_request);
  if (my_strlen(request_string) > 0)
    {
      write(s, request_string, my_strlen(request_string));
      return SUCCESS_SEND;
    }
  else
    {
      write(1, "exit\n", 5);
      return BAD_SEND;
    }
}

int		get_msg(int s)
{
  char		buff[1024];
  int		r;

  my_bzero(buff, 1024);
  r = recv(s, buff, 1024, 0);
  if (r > 0)
    {
      buff[r] = '\0';
      write(1, buff, r);
      return (1);
    }
  else
    {
      write(1, "Connection closed\n", 18);
      return (0);
    }
}

int client_loop(int s)
{
    fd_set	fd_read;

    FD_ZERO(&fd_read);

    FD_SET(STDIN_FILENO, &fd_read);
    FD_SET(s, &fd_read);

    if (select((s + 1), &fd_read, NULL, NULL, NULL) == -1)
	    return 0;
    if (FD_ISSET(STDIN_FILENO, &fd_read))
	{
        printf("Send_input\n");
	    send_input(s);
	}
    if (FD_ISSET(s, &fd_read))
    {
        printf("get_msg\n");
	    get_msg(s);
    }
    return 1;
}
