#ifndef _REQUEST_SERIALIZATION_H_
#define _REQUEST_SERIALIZATION_H_

char			*request_serialization(t_player_request *client_request);
t_player_request	*request_deserialize(char *request_serialized);

#endif /* !_REQUEST_SERIALIZATION_H_ */
