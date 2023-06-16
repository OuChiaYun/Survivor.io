#pragma once

#include "stdafx.h"

#ifndef CGSELECT_H
#define CGSELECT_H

namespace game_framework {

	class CGamestageSelect {

	public:
		CGamestageSelect() {};
		~CGamestageSelect() {};
		
		void OnBeginState();
		void OnInit();
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
		void OnLButtonDown(UINT nFlags, CPoint point);
		void OnLButtonUp(UINT nFlags, CPoint point);
		void OnMouseMove(UINT nFlags, CPoint point);
		void OnRButtonDown(UINT nFlags, CPoint point);
		void OnRButtonUp(UINT nFlags, CPoint point);
		void OnMove();
		void OnShow();
		void show_text();

		bool isSelect(UINT nFlags, CPoint point, CMovingBitmap & item);
		void rand_option();
		//int weapon_list[3] = { 0,0,0 };

		int show = 0;
		int weapon_selected = 0;
		


	private:
		CMovingBitmap select_bar;
		CMovingBitmap select_pic_bg[3];
		CMovingBitmap select_pic[3];
		CMovingBitmap select_start;
		CMovingBitmap selected;

		int rand_list[5] ;
		//int weapon_selected = 0;





	};

};

#endif;
