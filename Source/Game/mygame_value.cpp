#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Game/CGamestage_all.h"
#include "../Library/gamecore.h"
#include "mygame.h"

using namespace game_framework;

CGameStateValueStorage::CGameStateValueStorage() {};
int CGameStateValueStorage::init_background_value = -1;
int CGameStateValueStorage::victory = -1;
string CGameStateValueStorage::show_time = "";
string CGameStateValueStorage::dead_number = "";
 string CGameStateValueStorage::weapon_name = "";

void CGameStateValueStorage::set_init_background_value(int n) {
	init_background_value = n;
}
int CGameStateValueStorage::get_init_background_value() {
	return init_background_value;
}

void CGameStateValueStorage::set_victory_value(int n) {
	victory = n;
}
int CGameStateValueStorage::get_victory_value() {
	return victory;
}

void CGameStateValueStorage::set_data(string tmp_t, string tmp_dead, string tmp_name) {
	show_time = tmp_t;
	dead_number = tmp_dead;
	weapon_name = tmp_name;
};

string CGameStateValueStorage::get_show_time() {
	return show_time;
};
string CGameStateValueStorage::get_dead_number() {
	return dead_number;
};
 string CGameStateValueStorage::get_weapon_name() {
	return weapon_name;
};