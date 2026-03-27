#ifndef MSG_H
#define MSG_H

#define CONNECT 0
#define SET_TEAM 1
#define UPDATE 2
#define MY_TURN 3
#define DISCONNECT 4

struct Message {
	char type;
	unsigned int setID;
	bool disconnect;
};

#endif