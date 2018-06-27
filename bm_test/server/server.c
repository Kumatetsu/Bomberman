#include <stdio.h>
#include "socket.h"
#include "server.h"

int main()
{
    int   s;
    t_srv *srv;

    if ((srv = create_struct_srv()) == NULL)
      return 0;

    if ((s = create_server_socket()) == -1)
      return 0;

    srv->fd = s;

    //n'attend qu'un client pour qu'on puisse tester tranquillement
    //on doit init le server avant d'écouter les connections
    // if (accept_clients(&srv) == -1)
    //   return 0;

    while(main_loop(&srv));
    return 0;
}
