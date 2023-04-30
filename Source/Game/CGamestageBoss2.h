#pragma once

#include "stdafx.h"

#ifndef CGBOSS2_H
#define CGBOSS2_H

namespace game_framework {

	class CGamestageBoss2 {

	public:
		CGamestageBoss2() {};
		~CGamestageBoss2() {};

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

		void background_move();
		void bullet_move(vector<CMovingBitmap> &item);
		void bullet_erase(vector<CMovingBitmap> &item);
		void born_bullet(vector<CMovingBitmap> &item, vector<string> str, vector<int>rgb);
		void dart_all(int);
		void dart_move(CMovingBitmap &item, int i, int setR);
		void blood_bar_progress(CMovingBitmap &blood_bar, CMovingBitmap &item_blood);
		void show_text();

		///////////////////boss2////////////////

		void boss2_move();
		void boss2_bullet_move();
		//////////////////sharing///////////////
		void set_share_obj_data(CMovingBitmap &tmp_background, CMovingBitmap &tmp_character,
			CMovingBitmap &tmp_opera, CMovingBitmap &tmp_blood_bar, CMovingBitmap &tmp_energy_bar, vector <CMovingBitmap> &tmp_dart, vector<CMovingBitmap> &tmp_bullet);
		//set data's pointer & data obj
		void move_share_obj_data(CMovingBitmap &tmp_background, CMovingBitmap &tmp_character,
			CMovingBitmap &tmp_opera, CMovingBitmap &tmp_blood_bar, CMovingBitmap &tmp_energy_bar, vector <CMovingBitmap> &tmp_dart, vector<CMovingBitmap> &tmp_bullet);
		//move data = run
		void gat_data(); // move now data to run with pointer
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

		CMovingBitmap boss2_range;
		CMovingBitmap boss2;
		vector<CMovingBitmap> boss2_bullet;
		CMovingBitmap blood;

		double PI = 3.14159265358979323846;
		double theta[8] = { 0.0, PI / 4, PI / 2, 3 * PI / 4, PI, 5 * PI / 4, 3 * PI / 2, 7 * PI / 4 };

		int timmer = 0;
	};

};

#endif;
#pragma once
