#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Game/CGamestage_all.h"
#include "../Library/gamecore.h"
#include "mygame.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <ctime>

#define DART 1


using namespace game_framework;

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
/////////////////////////////////////////////////////////////////////////////

CGameStateRun::CGameStateRun(CGame *g) : CGameState(g)
{
}

CGameStateRun::~CGameStateRun()
{
}

void CGameStateRun::OnBeginState()
{
}

void CGameStateRun::OnMove()							// 移動遊戲元素
{
	//t1.OnMove();
	b2.OnMove();
	
	/*
	if (select_stage.show == 1) {
		select_stage.OnMove();
	}else if (energy_bar.get_energy() == 25) {
		b1.OnMove();
	}
	else {
		t1.OnMove();
	}
	*/
	
	

}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{

	background.LoadBitmapByString({ "Resources/background/Purple Nebula/Purple_Nebula_03.bmp", "Resources/background/Blue Nebula/Blue_Nebula_02.bmp" });
	background.SetTopLeft(-1500, -1500);

	character.LoadBitmapByString({ "Resources/character/char_04.bmp" }, RGB(200, 191, 231));
	character.SetTopLeft(461, 252);
	character.set_center(470, 270);
	character.set_hp(5000);

	opera.LoadBitmapByString({ "Resources/operator.bmp" }, RGB(105, 106, 106));
	opera.SetTopLeft(437, 682);
	opera.set_center(437 + 54, 682 + 54);//491 , 736

	blood_bar.LoadBitmapByString({ "Resources/health_ui/health_ui_0.bmp", "Resources/health_ui/health_ui_1.bmp",
							   "Resources/health_ui/health_ui_2.bmp", "Resources/health_ui/health_ui_3.bmp",
							   "Resources/health_ui/health_ui_4.bmp" }, RGB(255, 255, 255));
	blood_bar.SetFrameIndexOfBitmap(blood_bar.GetFrameSizeOfBitmap() - 1);

	energy_bar.LoadBitmapByString({ "Resources/energy_bar/00.bmp" }, RGB(255, 255, 255));
	energy_bar.LoadBitmapByString({ "Resources/energy_bar/1.bmp", "Resources/energy_bar/2.bmp", "Resources/energy_bar/3.bmp", "Resources/energy_bar/4.bmp", "Resources/energy_bar/5.bmp" }, RGB(200, 191, 231));
	energy_bar.SetTopLeft(0, 65);
	energy_bar.set_energy(0);

	for (int i = 0; i < 2; i++) { //max 9
		dart.push_back(CMovingBitmap());
		dart[i].LoadBitmapByString({
		"Resources/weapon/hot_wheels/00.bmp",
		"Resources/weapon/hot_wheels/01.bmp",
		"Resources/weapon/hot_wheels/02.bmp",
		"Resources/weapon/hot_wheels/03.bmp",
		"Resources/weapon/hot_wheels/04.bmp",
		"Resources/weapon/hot_wheels/05.bmp",
		"Resources/weapon/hot_wheels/06.bmp",
		"Resources/weapon/hot_wheels/07.bmp" }, RGB(255, 255, 255));
		dart[i].SetTopLeft(character.GetLeft() + 30, character.GetTop() - 10);
		dart[i].set_timer((int)(i + 1)*(360 / 2));
		dart[i].SetAnimation(100, false);
	}
	bullet.push_back(CMovingBitmap());
	bullet[0].LoadBitmapByString({ "Resources/bullet.bmp" }, RGB(255, 255, 255));
	bullet[0].SetTopLeft(character.GetLeft() + 10, character.GetTop());

	/*
	CMovingBitmap background;
	CMovingBitmap character;
	CMovingBitmap opera;
	CMovingBitmap blood_bar;
	CMovingBitmap energy_bar;
	vector <CMovingBitmap> dart;
	vector<CMovingBitmap> bullet;
	*/

	t1.set_share_obj_data(background, character, opera, blood_bar, energy_bar, dart, bullet);
	t1.OnInit();

	select_stage.OnInit();

	b1.set_share_obj_data(background, character, opera, blood_bar, energy_bar, dart, bullet);
	b1.OnInit();

	b2.set_share_obj_data(background, character, opera, blood_bar, energy_bar, dart, bullet);
	b2.OnInit();

	timer_express.LoadBitmapByString({ "Resources/t1.bmp" }, RGB(255, 255, 255));
	timer_express.SetTopLeft(1065 - timer_express.GetWidth() - 70, 1065 - timer_express.GetHeight() - 60);

	a = clock();


}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
	
	if (select_stage.show == 1) {
		select_stage.OnLButtonDown(nFlags, point);
		if (select_stage.show == 2) {
			t1.select = select_stage.show;
			weapon_list[select_stage.weapon_selected] += 1;
			if (select_stage.weapon_selected == DART) {
				t1.mygame_dart_born();
				t1.share_data();
			}

		}
	}
	
	
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
	//t1.OnMouseMove(nFlags, point);
	b2.OnMouseMove(nFlags, point);

	/*
	if (select_stage.show == 1) {
		t1.OnMouseMove(false, point);
	}

	else if (energy_bar.get_energy() == 25) {
		b1.OnMouseMove(nFlags, point);
	}
	else {
		t1.OnMouseMove(nFlags, point);
	}
	*/
	
	
}


void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnShow()
{
//	t1.OnShow();
	b2.OnShow();
/*
	t1.show_baclground_selected(get_init_background_value());
	select_stage.show = t1.select;
	
	if (energy_bar.get_energy() == 25) {
		b1.OnShow();
	}
	else {
		t1.OnShow();
	}

	if (select_stage.show == 1) {
		select_stage.OnShow();
	}

*/
	


	timer_express.ShowBitmap();
	show_text();

}

void CGameStateRun::show_text() {

	CDC *pdc = CDDraw::GetBackCDC();
	b = clock();

	int t = (int)(b - a) / CLOCKS_PER_SEC;
	CTextDraw::ChangeFontLog(pdc, 40, "Modern No. 20", RGB(255, 174, 201), 80);
	CTextDraw::Print(pdc, 825, 925, to_string((t / 600)) + to_string((t / 60) % 10) + " : " + to_string((t / 10) % 6) + to_string(t % 10));

	CDDraw::ReleaseBackCDC();

}

void CGameStateRun::show_baclground_selected() {
	
	t1.show_baclground_selected(get_init_background_value());

}

void CMovingBitmap::dart_hit_monster(vector<CMovingBitmap> &dart, vector<CMovingBitmap> &monster, vector<CMovingBitmap> &monster_vanish) {

	for (int i = 0; i < (int)monster.size(); i++) {

		for (int j = 0; j < (int)dart.size(); j++) {
			if ((i < (int)monster.size()) && IsOverlap(dart[j], monster[i])) {

				monster[i].add_sub_hp(-1);
				if (monster[i].get_hp() <= 0) {

					monster_vanish.push_back(monster[i]);
					monster_vanish[monster_vanish.size() - 1].SetAnimation(80, true);
					monster_vanish[monster_vanish.size() - 1].ShowBitmap();
					monster_vanish[monster_vanish.size() - 1].ToggleAnimation();
					monster_vanish[monster_vanish.size() - 1].SetFrameIndexOfBitmap(30);

					monster.erase(monster.begin() + i);

				}

			}
		}
	}
}

void CMovingBitmap::item_hit_energy(CMovingBitmap &character, vector<CMovingBitmap> &item, CMovingBitmap &energy_bar) {
	for (int i = 0; i < (int)item.size(); i++) {
		if (IsOverlap(character, item[i])) {
			item.erase(item.begin() + i);
			energy_bar.add_energy(1);
			if (energy_bar.get_energy() % 5 == 0 && energy_bar.GetFrameIndexOfBitmap() < 5) {
				energy_bar.SetFrameIndexOfBitmap(energy_bar.GetFrameIndexOfBitmap() + 1);
				if (energy_bar.GetFrameIndexOfBitmap() == 5) {
				}
			}
			break;
		}
	}
}

void CMovingBitmap::set_limit_start_end(int start, int end) {
	limit_frame_start = start;
	limit_frame_end = end;
};

void CMovingBitmap::item_hit(CMovingBitmap &character, vector<CMovingBitmap> &item) {
	for (int i = 0; i < (int)item.size(); i++) {
		if (IsOverlap(character, item[i])) {
			item.erase(item.begin() + i);
			break;
		}
	}
}
