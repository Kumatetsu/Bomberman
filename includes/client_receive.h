#ifndef _CLIENT_RECEIVE_H_
#define _CLIENT_RECEIVE_H_

void	*listen_server(void *s);
int	get_message(SOCKET s, t_game_info **client_game_info);

#endif /* !_CLIENT_RECEIVE_H_ */
