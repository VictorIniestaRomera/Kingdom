#include <iostream>

#include "map_manager.h"

#include "first_player.h"
#include "second_player.h"
#include "third_player.h"
#include "fourth_player.h"

int main() {
    Map* m = new Map(40, 80);

    Player* firstPlayer = new FirstPlayer(m->get_map());
    Player* secondPlayer = new SecondPlayer(m->get_map());
    Player* thirdPlayer = new ThirdPlayer(m->get_map());
    Player* fourthPlayer = new FourthPlayer(m->get_map());

    m->draw_map();
}