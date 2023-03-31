#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"

using namespace game_framework;

CGameStateValueStorage::CGameStateValueStorage() {};
int CGameStateValueStorage::init_background_value = -1;

void CGameStateValueStorage::set_init_background_value(int a) {
	init_background_value = a;
}
int CGameStateValueStorage::get_init_background_value() {
	return init_background_value;
}