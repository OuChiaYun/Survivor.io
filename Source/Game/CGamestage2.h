#ifndef CG_H
#define CG_H

#include "stdafx.h"
#include "../Game/CGamestage1.h"

namespace game_framework {

	class CGamestage2 {
	public:
		CGamestage2() {};
		~CGamestage2() {};
		friend class CGamestage1;
	};
};
#endif