#ifndef _REQUEST_HANDLING_H_
#define _REQUEST_HANDLING_H_

void	handle_requests(t_game_info *game_info, int num_player, t_player_request *player_request);
void	place_bomb(t_game_info *game_info, t_player_request *player_request);
void	add_request_to_server(t_srv **srv, t_player_request *player_request);

#endif /* !_REQUEST_HANDLING_H_ */
