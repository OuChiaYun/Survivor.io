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

#define BRICKS 0
#define DART 1
#define LIGHTNING 2


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
	if (energy_bar.get_energy() == 25 && t1.run == 1) {
		boss_level++;
		t1.run = 0;
		CAudio::Instance()->Stop(AUDIO_GameStage);
		CAudio::Instance()->Play(AUDIO_GameBoss, true);

	}

	if (boss_level == 1 && b1.run == 1) {
		b1.OnMove();  //boss1
		if (b1.run == 0) { //stage2
			t1.run = 1;
			energy_bar.set_energy(0);
			energy_bar.SetFrameIndexOfBitmap(0);
			character.SetTopLeft(461, 252);
			character.set_center(470, 270);
			t1.select = 0;
			t1.open_stat2 = 1;
			CAudio::Instance()->Stop(AUDIO_GameBoss);
			CAudio::Instance()->Play(AUDIO_GameStage, true);
		}
	}
	else if(boss_level == 2 && b2.run == 1){
		b2.OnMove();  //boss2

		if (b2.isVector() == 1) {
			set_victory_value(1);
			set_over_data();
			GotoGameState(GAME_STATE_OVER);
		}

		if (b2.run == 0) {
			t1.run = 1;
			energy_bar.set_energy(0);
			energy_bar.SetFrameIndexOfBitmap(0);
			t1.select = 0;
			CAudio::Instance()->Stop(AUDIO_GameBoss);
			CAudio::Instance()->Play(AUDIO_GameStage, true);
		}
	}
	if (select_stage.show == 1) {
		select_stage.OnMove();
	}
	else if(t1.run == 1)
	{
		t1.OnMove(); //stage1
	}

	/*t1.run = 0;
	b1.run = 0;
	boss_level = 2;
	b2.run = 1;
	b2.OnMove();  //boss2*/
	
	if (character.get_hp() <= 0) {
		set_victory_value(0);
		set_over_data();
		GotoGameState(GAME_STATE_OVER);
	}
	
	
	
	

}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{

	background.LoadBitmapByString({ "Resources/background/Purple Nebula/Purple_Nebula_03.bmp", "Resources/background/Blue Nebula/Blue_Nebula_02.bmp" });
	background.SetTopLeft(-1500, -1500);

	character.LoadBitmapByString({ "Resources/character/char_04.bmp", "Resources/character/char_04_right.bmp" }, RGB(200, 191, 231));
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


	
	bullet.push_back(CMovingBitmap());
	bullet[0].LoadBitmapByString({ "Resources/weapon/bullet.bmp" }, RGB(255, 255, 255));
	bullet[0].SetTopLeft(character.GetLeft() + 10, character.GetTop());
	
	weapon_logo[0].LoadBitmapByString({ "Resources/weapon/cleaver_icon.bmp" }, RGB(255, 255, 255));
	weapon_logo[0].SetTopLeft(60, 180);
	weapon_logo[1].LoadBitmapByString({ "Resources/weapon/dart_icon.bmp" }, RGB(255, 255, 255));
	weapon_logo[1].SetTopLeft(100, 180);
	weapon_logo[2].LoadBitmapByString({ "Resources/weapon/lightning_icon.bmp" }, RGB(255, 255, 255));
	weapon_logo[2].SetTopLeft(147, 182);

	dead_logo.LoadBitmapByString({ "Resources/UI/skull.bmp" }, RGB(255, 255, 255));
	dead_logo.SetTopLeft(15, 930);

	/*
	CMovingBitmap background;
	CMovingBitmap character;
	CMovingBitmap opera;
	CMovingBitmap blood_bar;
	CMovingBitmap energy_bar;
	vector <CMovingBitmap> dart;
	vector<CMovingBitmap> bullet;
	*/
	lightning.size();

	t1.set_share_obj_data(background, character, opera, blood_bar, energy_bar, dart, bullet, bricks,lightning);
	t1.OnInit();

	select_stage.OnInit();

	b1.set_share_obj_data(background, character, opera, blood_bar, energy_bar, dart, bullet, bricks, lightning);
	b1.OnInit();

	b2.set_share_obj_data(background, character, opera, blood_bar, energy_bar, dart, bullet, bricks, lightning);
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
			

			if (select_stage.weapon_selected == BRICKS) {
				//t1.get_data();
				t1.bricks_born(bricks, { "Resources/weapon/cleaver.bmp" }, { 255, 255, 255 });
				t1.get_data();
				weapon_list[select_stage.weapon_selected] += 1;
			}

			if (select_stage.weapon_selected == DART) {
				
				t1.mygame_dart_born();
				t1.share_data();
				weapon_list[select_stage.weapon_selected] += 1;
			}
			
			if (select_stage.weapon_selected == LIGHTNING) {

				t1.lightning_born();
				t1.share_data();
				weapon_list[select_stage.weapon_selected] += 1;
			}
			
		}
	}
	
	
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{

	
	if (select_stage.show == 1) {
		t1.OnMouseMove(false, point);
		select_stage.OnMouseMove(nFlags, point);
	}
	else if (energy_bar.get_energy() == 25) {
		b2.OnMouseMove(nFlags, point);
	}
	else {
		t1.OnMouseMove(nFlags, point);
	}
	
}


void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnShow()
{

	show_baclground_selected();
	select_stage.show = t1.select;
	


	if (boss_level == 1 && b1.run == 1) {
		b1.OnShow();
	}
	else if (boss_level == 2 &&b2.run == 1) {
		b2.OnShow();
	}

	if (select_stage.show == 1) {
		t1.OnShow();
		select_stage.OnShow();
	}
	else if (t1.run == 1)
	{
		t1.OnShow();
	}


	for (int i = 0; i < 3; i++) {
		if(weapon_list[i] != 0){
		weapon_logo[i].ShowBitmap();
		}
	}
	dead_logo.ShowBitmap();
	timer_express.ShowBitmap();
	show_text();

}

void CGameStateRun::show_text() {

	CDC *pdc = CDDraw::GetBackCDC();
	b = clock();

	int t = (int)(b - a) / CLOCKS_PER_SEC;
	CTextDraw::ChangeFontLog(pdc, 40, "Modern No. 20", RGB(255, 174, 201), 80);
	CTextDraw::Print(pdc, 825, 925, to_string((t / 600)) + to_string((t / 60) % 10) + " : " + to_string((t / 10) % 6) + to_string(t % 10));

	CTextDraw::ChangeFontLog(pdc, 40, "Modern No. 20", RGB(255, 255, 255), 60);
	CTextDraw::Print(pdc, 120, 950,to_string(t1.get_dead_monster()));


	CDDraw::ReleaseBackCDC();

}

void CGameStateRun::show_baclground_selected() {
	
	background.SetFrameIndexOfBitmap(get_init_background_value());
}


void CGameStateRun::set_over_data() {
	b = clock();
	int t = (int)(b - a) / CLOCKS_PER_SEC;
	string cout = "";
	for (int i = 0; i < 3; i++) {
		if (weapon_list[i] != 0) {
			cout += weapon_name[i] + " ";
		}
	}
	set_data(to_string((t / 600)) + to_string((t / 60) % 10) + " : " + to_string((t / 10) % 6) + to_string(t % 10),
		to_string(t1.get_dead_monster()), cout);
}
//////////////////////////////////////////////////////////////////////////////////////////////
void CMovingBitmap::dart_hit_monster(vector<CMovingBitmap> &dart, vector<CMovingBitmap> &monster, vector<CMovingBitmap> &monster_vanish) {

	for (int i = 0; i < (int)monster.size(); i++) {

		for (int j = 0; j < (int)dart.size(); j++) {
			if ((i < (int)monster.size()) && IsOverlap(dart[j], monster[i])) {

				monster[i].add_sub_hp(-1);
				CAudio::Instance()->Play(AUDIO_Attack, false);
				if (monster[i].get_hp() <= 0) {
					monster_vanish.push_back(monster[i]);
					monster_vanish[monster_vanish.size() - 1].SetAnimation(80, true);
					monster_vanish[monster_vanish.size() - 1].ShowBitmap();
					monster_vanish[monster_vanish.size() - 1].ToggleAnimation();
					monster_vanish[monster_vanish.size() - 1].SetFrameIndexOfBitmap(monster[i].set_end);
					monster.erase(monster.begin() + i);

				}

			}
		}
	}
}


void CMovingBitmap::dart_hit_monster(CMovingBitmap &dart, vector<CMovingBitmap> &monster, vector<CMovingBitmap> &monster_vanish) {

	for (int i = 0; i < (int)monster.size(); i++) {

			if ((i < (int)monster.size()) && IsOverlap(dart, monster[i])) {

				monster[i].add_sub_hp(-1);
				CAudio::Instance()->Play(AUDIO_Attack, false);
				if (monster[i].get_hp() <= 0) {
					monster_vanish.push_back(monster[i]);
					monster_vanish[monster_vanish.size() - 1].SetAnimation(80, true);
					monster_vanish[monster_vanish.size() - 1].ShowBitmap();
					monster_vanish[monster_vanish.size() - 1].ToggleAnimation();
					monster_vanish[monster_vanish.size() - 1].SetFrameIndexOfBitmap(monster[i].set_end);
					monster.erase(monster.begin() + i);
					

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
