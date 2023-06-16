
#include "stdafx.h"

#ifndef CG2_H
#define CG2_H

namespace game_framework {

	class CGamestage2 {
	public:
		CGamestage2() {};
		~CGamestage2() {};
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
		void show_baclground_selected(int s);

		void background_move();
		void blood_bar_progress(CMovingBitmap &blood_bar, CMovingBitmap &item_blood);//have some bug
		void random_born_item(vector<CMovingBitmap>&item, vector<string> str, vector<int>rgb);
		void item_move(CMovingBitmap &item);
		void dart_all(int);
		void dart_move(CMovingBitmap &item, int i, int setR);
		void mygame_dart_born();

		void random_born_monster(vector<CMovingBitmap>&monster, vector<string> str_monster, vector<CMovingBitmap>&monster_vanish, vector<string> str_monster_vanish, vector<int>rgb_monster, vector<int>rgb_monster_vanish);
		void random_born_big_monster(vector<CMovingBitmap>&monster, vector<string> str_monster, vector<CMovingBitmap>&monster_vanish, vector<string> str_monster_vanish, vector<int>rgb_monster, vector<int>rgb_monster_vanish);


		void monster_all();
		void monster_pop(int less_than_n);
		bool isLeft(CMovingBitmap &character, CMovingBitmap &item);
		bool isDown(CMovingBitmap &character, CMovingBitmap &item);
		void monster_move(CMovingBitmap &monster);
		void big_monster_move(CMovingBitmap &monster);
		void big_monster_born();

		void bullet_move(vector<CMovingBitmap> &item);
		void bullet_erase(vector<CMovingBitmap> &item);
		void born_bullet(vector<CMovingBitmap> &item, vector<string> str, vector<int>rgb);

		void lightning_move(vector<CMovingBitmap> &item);
		void lightning_born();
		void bricks_move(CMovingBitmap &item, int h, int k, int c, int x_move);
		void bricks_erase(CMovingBitmap &item);
		void bricks_born(vector<CMovingBitmap> &item, vector<string> str, vector<int>rgb);
		void monster_reset(CMovingBitmap &item);
		void magnet_animation();
		int get_dead_monster();

		void show_text();
		void show_img();


		/////////////////////////////update data/////////////////
		void set_share_obj_data(CMovingBitmap &tmp_background, CMovingBitmap &tmp_character, CMovingBitmap &tmp_opera, CMovingBitmap &tmp_blood_bar, CMovingBitmap &tmp_energy_bar,
			vector <CMovingBitmap> &tmp_dart, vector<CMovingBitmap> &tmp_bullet, vector<CMovingBitmap> &tmp_bricks, vector<CMovingBitmap> &tmp_lightning);



		void move_share_obj_data(CMovingBitmap &tmp_background, CMovingBitmap &tmp_character, CMovingBitmap &tmp_opera, CMovingBitmap &tmp_blood_bar, CMovingBitmap &tmp_energy_bar,
			vector <CMovingBitmap> &tmp_dart, vector<CMovingBitmap> &tmp_bullet, vector<CMovingBitmap> &tmp_bricks, vector<CMovingBitmap> &tmp_lightning);
		//move data = run

		void get_data(); // move now data to run with pointer

		void share_data();
		//move data to point to run
		int select = 0;

		int run = 1;

		//int open_stat2 = 0;


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

		////////////////////////
		vector<CMovingBitmap> magnet;
		CMovingBitmap bomb;

		//share
		vector<CMovingBitmap> monster;
		vector<CMovingBitmap> monster_vanish;
		CMovingBitmap blood;

		vector<CMovingBitmap> big_monster;
		vector<CMovingBitmap> big_monster_vanish;
		vector<CMovingBitmap> big_monster_blood;

		vector<CMovingBitmap> fast_monster;
		vector<CMovingBitmap> fast_monster_vanish;

		vector<CMovingBitmap> heart;

		vector <CMovingBitmap> energy;
		int axay[4][2] = { {-2,2},{2,2},{-2,-2},{2,-2} };
		int item_stdax;
		int item_stday;

		int timer = 0;
		int magnet_timer = 0;
		int magnet_trigger = 0;
		int magnet_once = 0;

		int bomb_timer = 0;
		int bomb_trigger = 0;
		int bomb_once = 0;

		int h[4] = { -30, -60, 30, 60 };
		int k[4] = { -70, -100, -70, -100 };
		int c[4] = { 40, 60, 40, 60 };
		int x_move[4] = { -5, -5, 5, 5 };

		int dead_monster = 0;
	};
};

#endif;
