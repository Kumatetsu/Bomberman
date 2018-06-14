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
    if (accept_clients(&srv) == -1)
      return 0;

    // main_loop(&srv);

    return 0;
}
