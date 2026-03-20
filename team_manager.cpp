#include "team_manager.h"

Team* Team::manager = nullptr;

Team* Team::get_singleton() {
	if (!manager) manager = new Team();

	return manager;
}

Team::Team() {}

Team::~Team() {
	for (int i = 0; i < 4; i++) {
		delete teamList.at(i);
	}
}

const int Team::get_pos(const char* name) const noexcept {
	for (int i = 0; i < teamList.size(); i++) {
		if (teamList.at(i)->teamName == name) return i;
	}

	return -1;
}