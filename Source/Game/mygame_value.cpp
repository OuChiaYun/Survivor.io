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

