#ifndef TEAM_MANAGER_H
#define TEAM_MANAGER_H

#include "team_exception.h"

#include "color_writings.h"

#include "core.h"
#include "point2.h"

struct TeamData {
	const char* teamColor;
	const char* teamName;
	util::Core<util::Point2*> teamMap;

	~TeamData() {
		delete teamColor;
		delete teamName;

		for (int i = 0; i < teamMap.size(); i++) {
			delete teamMap.at(i);
		}
	}
};

class Team {
	util::Core<TeamData*> teamList;	//This will be in the server

	static Team* manager;

	const int get_pos(const char* name) const noexcept;

public:
	Team();

	~Team();

	static Team* get_singleton();

	inline void add_team(const char* name) noexcept {
		if (teamList.size() != 4) {
			TeamData* add = new TeamData();

			add->teamName = name;

			switch (teamList.size()) {
			case 0:
				add->teamColor = ColorWritings::TEAM_1;

				break;

			case 1:
				add->teamColor = ColorWritings::TEAM_2;

				break;

			case 2:
				add->teamColor = ColorWritings::TEAM_3;

				break;

			case 3:
				add->teamColor = ColorWritings::TEAM_4;

				break;
			}

			teamList.push_back(add);
		}
		else LogWriter::log("Team limit reached!");
	}

	inline TeamData* get_data(const char* name) noexcept {
		try {
			int pos = get_pos(name);

			if (pos == -1) throw(new TeamException(1));

			return teamList.at(pos);
		}
		catch (const TeamException* e) {
			LogWriter::log(e->what());

			delete e;

			return nullptr;
		}
	}

	inline const char* get_color() const noexcept {
		return teamList.at(0)->teamColor;	//Change when server is done
	}

	inline const char* get_name() const noexcept {
		return teamList.at(0)->teamName;	//Change when server is done
	}
};

#endif