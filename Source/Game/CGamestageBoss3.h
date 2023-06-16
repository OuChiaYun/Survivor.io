
#include "stdafx.h"

#ifndef CGBOSS3_H
#define CGBOSS3_H

namespace game_framework {

	class CGamestageBoss3 {

	public:
		CGamestageBoss3() {};
		~CGamestageBoss3() {};

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

		void lightning_move(vector<CMovingBitmap> &item);
		void bricks_move(vector<CMovingBitmap> &item, int h, int k, int c, int x_move, int i);
		void bricks_erase(vector<CMovingBitmap> &item);


		bool isSelect(UINT nFlags, CPoint point, CMovingBitmap &item);

		///////////////////boss3////////////////

		void boss3_move();
		void boss3_bullet_move();
		void boss3_rocket_move();
		int isVector();
		//////////////////sharing///////////////

		void set_share_obj_data(CMovingBitmap &tmp_background, CMovingBitmap &tmp_character, CMovingBitmap &tmp_opera, CMovingBitmap &tmp_blood_bar, CMovingBitmap &tmp_energy_bar,
			vector <CMovingBitmap> &tmp_dart, vector<CMovingBitmap> &tmp_bullet, vector<CMovingBitmap> &tmp_bricks, vector<CMovingBitmap> &tmp_lightning);
		//set data's pointer & data obj
		void move_share_obj_data(CMovingBitmap &tmp_background, CMovingBitmap &tmp_character,
			CMovingBitmap &tmp_opera, CMovingBitmap &tmp_blood_bar, CMovingBitmap &tmp_energy_bar, vector <CMovingBitmap> &tmp_dart, vector<CMovingBitmap> &tmp_bullet, vector<CMovingBitmap> &tmp_bricks);
		//move data = run
		void get_data(); // move now data to run with pointer
		void share_data(); // move now data to run with pointer

		int run = 1;

	private:

		CMovingBitmap *p_background;
		CMovingBitmap *p_character;
		CMovingBitmap *p_opera;
		CMovingBitmap *p_blood_bar;
		CMovingBitmap *p_energy_bar;
		vector <CMovingBitmap> *p_dart;
		vector<CMovingBitmap> *p_bullet;
		vector<CMovingBitmap> *p_bricks;
		vector<CMovingBitmap> *p_lightning;

		CMovingBitmap background;
		CMovingBitmap character;
		CMovingBitmap opera;
		CMovingBitmap blood_bar;
		CMovingBitmap energy_bar;
		vector <CMovingBitmap> dart;
		vector<CMovingBitmap> bullet;
		vector<CMovingBitmap> bricks;
		vector<CMovingBitmap> lightning;

		//share

		CMovingBitmap boss3_range;
		CMovingBitmap boss3;
		vector<CMovingBitmap> boss3_bullet;
		vector<CMovingBitmap> boss3_rocket;
		CMovingBitmap blood;
		CMovingBitmap blood_bar_boss3;
		CMovingBitmap blood_boss3;

		CMovingBitmap jump;

		double PI = 3.14159265358979323846;
		double theta[8] = { 0.0, PI / 4, PI / 2, 3 * PI / 4, PI, 5 * PI / 4, 3 * PI / 2, 7 * PI / 4 };

		int h[4] = { -30, -60, 30, 60 };
		int k[4] = { -70, -100, -70, -100 };
		int c[4] = { 40, 60, 40, 60 };
		int x_move[4] = { -5, -5, 5, 5 };

		int timmer = 0;
	};

};

#endif;
#pragma once