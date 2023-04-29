#pragma once

#include "stdafx.h"

#ifndef CGBOSS1_H
#define CGBOSS1_H

namespace game_framework {

	class CGamestageBoss1{

	public:
		CGamestageBoss1() {};
		~CGamestageBoss1() {};
	
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

		void boss1_bullet_move();
		void boss1_background();
		void boss1_character_attack();
		void bullet_move(vector<CMovingBitmap> &item);
		void bullet_erase(vector<CMovingBitmap> &item);
		void born_bullet(vector<CMovingBitmap> &item, vector<string> str, vector<int>rgb);
		void dart_all(int);
		void dart_move(CMovingBitmap &item, int i, int setR);
		void blood_bar_progress(CMovingBitmap &blood_bar, CMovingBitmap &item_blood);
		void show_text();


		void set_share_obj_data(CMovingBitmap &tmp_background, CMovingBitmap &tmp_character,
			CMovingBitmap &tmp_opera, CMovingBitmap &tmp_blood_bar, CMovingBitmap &tmp_energy_bar, vector <CMovingBitmap> &tmp_dart, vector<CMovingBitmap> &tmp_bullet);
		//set data's pointer & data obj
		void move_share_obj_data(CMovingBitmap &tmp_background, CMovingBitmap &tmp_character,
			CMovingBitmap &tmp_opera, CMovingBitmap &tmp_blood_bar, CMovingBitmap &tmp_energy_bar, vector <CMovingBitmap> &tmp_dart, vector<CMovingBitmap> &tmp_bullet);
		//move data = run
		void get_data(); // move now data to run with pointer
		void share_data(); // move now data to run with pointer

	

	private:

		CMovingBitmap *p_background;
		CMovingBitmap *p_character;
		CMovingBitmap *p_opera;
		CMovingBitmap *p_blood_bar;
		CMovingBitmap *p_energy_bar;
		vector <CMovingBitmap> *p_dart;
		vector<CMovingBitmap> *p_bullet;

		CMovingBitmap character;
		CMovingBitmap background;
		CMovingBitmap opera;
		CMovingBitmap blood_bar;
		CMovingBitmap energy_bar;
		vector <CMovingBitmap> dart;
		vector<CMovingBitmap> bullet;
		//share

		CMovingBitmap boss1;
		CMovingBitmap boss1_range;
		CMovingBitmap blood;
		vector<CMovingBitmap> boss1_bullet;
		CMovingBitmap blood_bar_boss1;
		CMovingBitmap blood_boss1;
	};

};

#endif;
#pragma once
