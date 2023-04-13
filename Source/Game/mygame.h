/*
 * mygame.h: 本檔案儲遊戲本身的class的interface
 * Copyright (C) 2002-2008 Woei-Kae Chen <wkc@csie.ntut.edu.tw>
 *
 * This file is part of game, a free game development framework for windows.
 *
 * game is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * game is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *	 2004-03-02 V4.0
 *      1. Add CGameStateInit, CGameStateRun, and CGameStateOver to
 *         demonstrate the use of states.
 *   2005-09-13
 *      Rewrite the codes for CBall and CEraser.
 *   2005-09-20 V4.2Beta1.
 *   2005-09-29 V4.2Beta2.
 *   2006-02-08 V4.2
 *      1. Rename OnInitialUpdate() -> OnInit().
 *      2. Replace AUDIO_CANYON as AUDIO_NTUT.
 *      3. Add help bitmap to CGameStateRun.
 *   2006-09-09 V4.3
 *      1. Rename Move() and Show() as OnMove and OnShow() to emphasize that they are
 *         event driven.
 *   2008-02-15 V4.4
 *      1. Add namespace game_framework.
 *      2. Replace the demonstration of animation as a new bouncing ball.
 *      3. Use ShowInitProgress(percent) to display loading progress.
*/


namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// Constants
	/////////////////////////////////////////////////////////////////////////////

	enum AUDIO_ID {				// 定義各種音效的編號
		AUDIO_DING,				// 0
		AUDIO_LAKE,				// 1
		AUDIO_NTUT				// 2
	};

	class CGameStateValueStorage {
	public:
		CGameStateValueStorage();
		static void set_init_background_value(int);
		static int get_init_background_value();

		static void set_victory_value(int);
		static int get_victory_value();
	private:
		static int init_background_value;
		static int victory;
	};
	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲開頭畫面物件
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateInit : public CGameState, public CGameStateValueStorage {
	public:
		CGameStateInit(CGame *g);
		void OnInit();  								// 遊戲的初值及圖形設定
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnKeyUp(UINT, UINT, UINT); 				// 處理鍵盤Up的動作
		void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
	protected:
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		CMovingBitmap logo;								// csie的logo
		CMovingBitmap select1;
		CMovingBitmap select2;
		CMovingBitmap check_blank1;
		CMovingBitmap check_blank2;
		CMovingBitmap check1;
		CMovingBitmap check2;
		CMovingBitmap select_scene1;
		CMovingBitmap select_scene2;
		CMovingBitmap play;
		CMovingBitmap play_bg;
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateRun : public CGameState, public CGameStateValueStorage {
	public:
		CGameStateRun(CGame *g);
		~CGameStateRun();
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();  								// 遊戲的初值及圖形設定
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
		void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		void OnLButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作
		void OnMouseMove(UINT nFlags, CPoint point);	// 處理滑鼠的動作 
		void OnRButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		void OnRButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作
		bool isSelect(UINT nFlags, CPoint point,CMovingBitmap & item);

	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();		// 顯示這個狀態的遊戲畫面
	private:
		CMovingBitmap background;
		CMovingBitmap background2;
		CMovingBitmap character;
		CMovingBitmap opera;
		CMovingBitmap goal;
		CMovingBitmap blood_bar;
		CMovingBitmap blood_bar_boss1;
		CMovingBitmap energy_bar;
		CMovingBitmap boss2;
		CMovingBitmap blood;
		CMovingBitmap blood_boss1;
		CMovingBitmap select_bar;
		CMovingBitmap select_pic_bg[3];
		CMovingBitmap select_pic;
		CMovingBitmap select_start;
		CMovingBitmap selected;
		CMovingBitmap timer_express;


		//CMovingBitmap dart;
		vector <CMovingBitmap> dart;
		vector <CMovingBitmap> energy;
		vector<CMovingBitmap> monster;
		vector<CMovingBitmap> monster_vanish;
		vector<CMovingBitmap> hiden;

		void show_img();
		void show_text();
		
		void show_baclground_selected();

		void background_move();
		void item_move(CMovingBitmap &item);
		void monster_move(CMovingBitmap &monster);
		void dart_move(CMovingBitmap &item, int i, int setR);
		void boss2_move();

		bool isLeft(CMovingBitmap &character, CMovingBitmap &item);
		bool isDown(CMovingBitmap &character, CMovingBitmap &item);


		void random_born_item(vector<CMovingBitmap>&item,vector<string> str, vector<int>rgb);
		void random_born_monster(vector<CMovingBitmap>&monster, vector<string> str_monster, vector<CMovingBitmap>&monster_vanish, vector<string> str_monster_vanish, vector<int>rgb_monster, vector<int>rgb_monster_vanish);
		void monster_pop(int less_than_n);
		
		int hit_count = 0;
		int timer = 0;
		int stop = 0;
		int state = 0; // 1-> select
		int weapon_list[3] = { 0,0,0 };
		clock_t a, b;

		void monster_all();
		void dart_all(int);
		

		void blood_bar_progress(CMovingBitmap &blood_bar, CMovingBitmap &item_blood);

		vector<CMovingBitmap> bullet;
		void bullet_move(vector<CMovingBitmap> &item);
		void bullet_erase(vector<CMovingBitmap> &item);
		void born_bullet(vector<CMovingBitmap> &item, vector<string> str, vector<int>rgb);

		CMovingBitmap boss1;
		CMovingBitmap boss1_range;
		vector<CMovingBitmap> boss1_bullet;
		void boss1_background();
		void boss1_character_attack();
		void boss1_bullet_move();

		int level = 0;
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的結束狀態(Game Over)
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateOver : public CGameState, public CGameStateValueStorage {
	public:
		CGameStateOver(CGame *g);
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();
	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		int counter;	// 倒數之計數器

		CMovingBitmap victory;
		CMovingBitmap die;
	};

}
