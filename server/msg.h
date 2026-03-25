#ifndef MSG_H
#define MSG_H

#define SET_ID 0
#define DISCONNECT

struct Message {
	char type;
	int setID;
	bool disconnect;
};

#endif