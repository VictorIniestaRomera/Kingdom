#ifndef MSG_H
#define MSG_H

#define CONNECT 0
#define DISCONNECT 2


struct Message {
	char type;
	unsigned int id;

	bool disconnect;

	const char* team;
};

#endif