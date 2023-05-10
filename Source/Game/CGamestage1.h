
#include "stdafx.h"

#ifndef CG_H
#define CG_H

namespace game_framework {

	class CGamestage1 {
	public:
		CGamestage1() {};
		~CGamestage1() {};	
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
		void blood_bar_progress(CMovingBitmap &blood_bar, CMovingBitmap &item_blood);
		void random_born_item(vector<CMovingBitmap>&item, vector<string> str, vector<int>rgb);
		void item_move(CMovingBitmap &item);
		void dart_all(int);
		void dart_move(CMovingBitmap &item, int i, int setR);
		void mygame_dart_born();
		void random_born_monster(vector<CMovingBitmap>&monster, vector<string> str_monster, vector<CMovingBitmap>&monster_vanish, vector<string> str_monster_vanish, vector<int>rgb_monster, vector<int>rgb_monster_vanish);
		void monster_all();
		void monster_pop(int less_than_n);
		bool isLeft(CMovingBitmap &character, CMovingBitmap &item);
		bool isDown(CMovingBitmap &character, CMovingBitmap &item);
		void monster_move(CMovingBitmap &monster);
		void bullet_move(vector<CMovingBitmap> &item);
		void bullet_erase(vector<CMovingBitmap> &item);
		void born_bullet(vector<CMovingBitmap> &item, vector<string> str, vector<int>rgb);

		void lightning_move(vector<CMovingBitmap> &item);
		void lightning_born();
		void bricks_move(vector<CMovingBitmap> &item, int h, int k, int c, int x_move,int i);
		void bricks_erase(vector<CMovingBitmap> &item);
		void bricks_born(vector<CMovingBitmap> &item, vector<string> str, vector<int>rgb);
		void monster_reset(CMovingBitmap &item);
		void magnet_animation();

		void show_text();
		void show_img();


		/////////////////////////////update data/////////////////
		void set_share_obj_data(CMovingBitmap &tmp_background, CMovingBitmap &tmp_character,CMovingBitmap &tmp_opera, CMovingBitmap &tmp_blood_bar, CMovingBitmap &tmp_energy_bar, 
			vector <CMovingBitmap> &tmp_dart, vector<CMovingBitmap> &tmp_bullet, vector<CMovingBitmap> &tmp_bricks, vector<CMovingBitmap> &tmp_lightning);



		void move_share_obj_data(CMovingBitmap &tmp_background, CMovingBitmap &tmp_character,CMovingBitmap &tmp_opera, CMovingBitmap &tmp_blood_bar, CMovingBitmap &tmp_energy_bar, 
			vector <CMovingBitmap> &tmp_dart, vector<CMovingBitmap> &tmp_bullet, vector<CMovingBitmap> &tmp_bricks, vector<CMovingBitmap> &tmp_lightning);
		//move data = run

		void get_data(); // move now data to run with pointer

		void share_data();
		//move data to point to run
		int select = 0;

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

		////////////////////////
		vector<CMovingBitmap> magnet;
//share

		vector<CMovingBitmap> monster;
		vector<CMovingBitmap> monster_vanish;
		CMovingBitmap blood;
		vector<CMovingBitmap> big_monster;
		vector<CMovingBitmap> big_monster_vanish;
		vector <CMovingBitmap> energy;
		int axay[4][2] = { {-2,2},{2,2},{-2,-2},{2,-2} };
		int item_stdax;
		int item_stday;

		//CMovingBitmap timer_express;
		//clock_t a, b;

		int timer = 0;
		int magnet_timer = 0;
		int magnet_trigger = 0;
		int magnet_once = 0;

	};

};

#endif;
