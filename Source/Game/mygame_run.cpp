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
#define BLOOD_ADD 3


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
	not_dead = 0;
	character.set_hp(5000);
	character.SetTopLeft(461, 252);
	character.set_center(470, 270);


	vector<CMovingBitmap>().swap(dart);		
	energy_bar.set_energy(0);
	energy_bar.SetFrameIndexOfBitmap(0);
	blood_bar.SetFrameIndexOfBitmap(blood_bar.GetFrameSizeOfBitmap()-1);
//	vector<CMovingBitmap>().swap(bullet);
	vector<CMovingBitmap>().swap(bricks);
	vector<CMovingBitmap>().swap(lightning);

	for (int i = 0; i < 3; i++) {
		weapon_list[i] = 0; 
	}

	boss_level = 0;
	level = 0;
	current_t = 0;
	pre_boss_t = 0;
	current_stage = 0;
	suspend_start = 0;
	suspend_end = 0;

	t0.OnBeginState();
	t1.OnBeginState();
	t2.OnBeginState();
	b1.OnBeginState();
	b2.OnBeginState();
	b3.OnBeginState();

	select_stage.OnBeginState();
	a = clock();
	b = clock();

	t0.run = 1;
	
}

void CGameStateRun::OnMove()							// 移動遊戲元素
{
	if (suspend == 0) {
		b = clock();
		current_t = (int)(b - a - (suspend_end - suspend_start)) / CLOCKS_PER_SEC;


		if (current_t - pre_boss_t > 30) {
			t0.run = 0;
			t1.run = 0;
			t2.run = 0;

			if (boss_level == 0) {
				b1.OnMove();
				if (b1.run == 0) {
					boss_level++;
					t1.run = 1;
					energy_bar.set_energy(0);
					energy_bar.SetFrameIndexOfBitmap(0);
					character.SetTopLeft(461, 252);
					character.set_center(470, 270);
					pre_boss_t = (int)(b - a) / CLOCKS_PER_SEC;
					CAudio::Instance()->Stop(AUDIO_GameBoss);
					CAudio::Instance()->Play(AUDIO_GameStage, true);
				}
			}


			else if (boss_level == 1) {
				b2.OnMove();
				if (b2.run == 0) {
					boss_level++;
					t2.run = 1;
					energy_bar.set_energy(0);
					energy_bar.SetFrameIndexOfBitmap(0);
					character.SetTopLeft(461, 252);
					character.set_center(470, 270);
					pre_boss_t = (int)(b - a) / CLOCKS_PER_SEC;
					CAudio::Instance()->Stop(AUDIO_GameBoss);
					CAudio::Instance()->Play(AUDIO_GameStage, true);
				}
			}
			else if (boss_level == 2) {
				b3.OnMove();
				if (b3.run == 0) {
					set_victory_value(1);
					set_over_data();
					CAudio::Instance()->Stop(AUDIO_GameStage);
					CAudio::Instance()->Play(AUDIO_MenuSelect, true);
					GotoGameState(GAME_STATE_OVER);
				}
			}

		}

		else {
			if (select_stage.show == 1) {
				select_stage.OnMove();
			}
			else if (t0.run == 1)
			{
				t0.OnMove(); //stage1
			}

			else if (t1.run == 1)
			{
				t1.OnMove(); //stage1
			}
			else if (t2.run == 1)
			{
				t2.OnMove(); //stage1
			}
		}
	}
	else {
		suspend_end = clock();
	}

	if (character.get_hp() <= 0 && not_dead == 0) {
		set_victory_value(0);
		set_over_data();
		CAudio::Instance()->Stop(AUDIO_GameStage);
		CAudio::Instance()->Play(AUDIO_MenuSelect, true);
		GotoGameState(GAME_STATE_OVER);
	}
	
}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{

	background.LoadBitmapByString({ "Resources/background/Purple Nebula/Purple_Nebula_03.bmp", "Resources/background/Blue Nebula/Blue_Nebula_02.bmp" });
	background.SetTopLeft(-1500, -1500);

	character.LoadBitmapByString(
		{ 
		"Resources/character/d1.bmp","Resources/character/d2.bmp","Resources/character/d3.bmp","Resources/character/d4.bmp","Resources/character/d5.bmp","Resources/character/d6.bmp",
		"Resources/character/w1.bmp","Resources/character/w2.bmp","Resources/character/w3.bmp","Resources/character/w4.bmp","Resources/character/w5.bmp","Resources/character/w6.bmp","Resources/character/w7.bmp","Resources/character/w8.bmp" ,
		"Resources/character/k1.bmp","Resources/character/k2.bmp","Resources/character/k3.bmp","Resources/character/k4.bmp","Resources/character/k5.bmp","Resources/character/k6.bmp","Resources/character/k7.bmp","Resources/character/k8.bmp" ,
		}, RGB(255, 255, 255));//RGB(20, 191, 231)
	character.set_limit_start_end(0, 5);

	character.SetAnimation(100, false);
	character.SetTopLeft(461, 252);
	character.set_center(470, 270);
	character.set_hp(5000);
	character.set_hp_max(5000);

	opera.LoadBitmapByString({ "Resources/operator.bmp" }, RGB(105, 106, 106));
	opera.SetTopLeft(437, 682);
	opera.set_center(437 + 54, 682 + 54);//491 , 736

	blood_bar.LoadBitmapByString({ "Resources/health_ui/health_ui_4.bmp", "Resources/health_ui/health_ui_3.bmp",
							   "Resources/health_ui/health_ui_2.bmp", "Resources/health_ui/health_ui_1.bmp",
							   "Resources/health_ui/health_ui_0.bmp" }, RGB(255, 255, 255));
	blood_bar.SetFrameIndexOfBitmap(blood_bar.GetFrameSizeOfBitmap() - 1);

	blood_bar.SetTopLeft(10, 15);

	energy_bar.LoadBitmapByString({ "Resources/energy_bar/00.bmp" }, RGB(255, 255, 255));
	energy_bar.LoadBitmapByString({ "Resources/energy_bar/1.bmp", "Resources/energy_bar/2.bmp", "Resources/energy_bar/3.bmp", "Resources/energy_bar/4.bmp", "Resources/energy_bar/5.bmp" }, RGB(255, 255, 255));
	energy_bar.SetTopLeft(18, 105);
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


	suspend_logo.LoadBitmapByString({ "Resources/UI/suspend.bmp","Resources/UI/suspend_2.bmp","Resources/UI/suspend_3.bmp" }, RGB(255, 255, 255));
	suspend_logo.SetTopLeft(1065-suspend_logo.GetWidth()-30,10);
	suspend_logo.SetFrameIndexOfBitmap(0);

	not_dead_logo.LoadBitmapByString({ "Resources/UI/not_dead.bmp","Resources/UI/not_dead_2.bmp","Resources/UI/not_dead_3.bmp" }, RGB(255, 255, 255));
	not_dead_logo.SetTopLeft(1065 - suspend_logo.GetWidth() - not_dead_logo.GetWidth()-30, 10);
	not_dead_logo.SetFrameIndexOfBitmap(0);

	lightning.size();

	t0.set_share_obj_data(background, character, opera, blood_bar, energy_bar, dart, bullet, bricks, lightning);
	t0.OnInit();

	t1.set_share_obj_data(background, character, opera, blood_bar, energy_bar, dart, bullet, bricks,lightning);
	t1.OnInit();

	t2.set_share_obj_data(background, character, opera, blood_bar, energy_bar, dart, bullet, bricks, lightning);
	t2.OnInit();

	select_stage.OnInit();

	b1.set_share_obj_data(background, character, opera, blood_bar, energy_bar, dart, bullet, bricks, lightning);
	b1.OnInit();

	b2.set_share_obj_data(background, character, opera, blood_bar, energy_bar, dart, bullet, bricks, lightning);
	b2.OnInit();

	b3.set_share_obj_data(background, character, opera, blood_bar, energy_bar, dart, bullet, bricks, lightning);
	b3.OnInit();

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
	if (isSelect(nFlags, point, not_dead_logo)) {

		not_dead = !not_dead;

		if (not_dead == 1) {
			not_dead_logo.SetFrameIndexOfBitmap(1);
		}
		else {
			not_dead_logo.SetFrameIndexOfBitmap(0);
		}

	}

	if (isSelect(nFlags, point, suspend_logo)) {
		suspend = !suspend;

		if (suspend == 1) {
			suspend_logo.SetFrameIndexOfBitmap(1);
			suspend_start = clock();

		}
		else {
			suspend_logo.SetFrameIndexOfBitmap(0);
		}

	}

	if (select_stage.show == 1 && suspend == 0 && current_t - pre_boss_t < 30){
		select_stage.OnLButtonDown(nFlags, point);
		if (select_stage.show == 2) {

			if (current_stage == 0) {
				select_temp(t0);
			}
			else if (current_stage == 1) {
				select_temp(t1);
			}

			else if(current_stage == 2) {
				select_temp(t2);
			}

		}
	}

	if (current_t - pre_boss_t > 30) {
		if (boss_level == 0) {
			b1.OnLButtonDown(nFlags, point);
		}
		else if (boss_level == 1) {
			b2.OnLButtonDown(nFlags, point);
		}
		else if (boss_level == 2) {
			b3.OnLButtonDown(nFlags, point);
		}
	}
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
	if (isSelect(true, point, not_dead_logo)) {

		not_dead_logo.SetFrameIndexOfBitmap(2);
	}
	else if(!isSelect(true, point, not_dead_logo) && not_dead == 1){
		not_dead_logo.SetFrameIndexOfBitmap(1);
	}
	else {
		not_dead_logo.SetFrameIndexOfBitmap(0);
	}

	if (isSelect(true, point, suspend_logo)) {
		
		suspend_logo.SetFrameIndexOfBitmap(2);
	}
	else if (!isSelect(true, point, suspend_logo) && suspend == 1) {
		suspend_logo.SetFrameIndexOfBitmap(1);
	}
	else if(suspend == 0){
		suspend_logo.SetFrameIndexOfBitmap(0);

		if (current_t - pre_boss_t > 30) {
			if (boss_level == 0) {
				b1.OnMouseMove(nFlags, point);
			}

			else if (boss_level == 1) {
				b2.OnMouseMove(nFlags, point);
			}
			
			else if (boss_level == 2) {
				b3.OnMouseMove(nFlags, point);
			}


		}
		else {
			if (select_stage.show == 1 && current_t - pre_boss_t < 30) {
				t1.OnMouseMove(false, point);
				select_stage.OnMouseMove(nFlags, point);
			}
			else {
				t1.OnMouseMove(nFlags, point);
			}
		}
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

	if (current_t - pre_boss_t > 30) {
		if (boss_level == 0) {
			b1.OnShow();
		}
		else if (boss_level == 1) {
			b2.OnShow();
		}
		else if (boss_level == 2) {
			b3.OnShow();
		}
	}
	else {

		if (boss_level == 0) {
			t0.OnShow();
			current_stage = 0;
			select_stage.show = t0.select;
		}
		else if (boss_level == 1 && b1.run == 0) {
			t1.OnShow();
			current_stage = 1;
			select_stage.show = t1.select;
		}
		else if (boss_level == 2 && b2.run == 0) {
			t2.OnShow();
			current_stage = 2;
			select_stage.show = t2.select;
		}

		if (select_stage.show == 1) {
			
			select_stage.OnShow();
		}
	}

	for (int i = 0; i < 3; i++) {
		if(weapon_list[i] != 0){
		weapon_logo[i].ShowBitmap();
		}
	}
	dead_logo.ShowBitmap();
	timer_express.ShowBitmap();
	suspend_logo.ShowBitmap();
	not_dead_logo.ShowBitmap();
	show_text();
}

void CGameStateRun::show_text() {

	CDC *pdc = CDDraw::GetBackCDC();
	b = clock();

	int t = (int)(b - a - (suspend_end - suspend_start) ) / CLOCKS_PER_SEC;

	if ((30 - (current_t - pre_boss_t) <= 5) && ( 30 - (current_t - pre_boss_t )>= 0)) {
		CTextDraw::ChangeFontLog(pdc, 35, "monogram", RGB(255, 255, 255), 80);
		CTextDraw::Print(pdc, 330, 900, "Boss In! " + to_string(30 - (current_t - pre_boss_t)) + "s left.");
	}

	CTextDraw::ChangeFontLog(pdc, 40, "monogram", RGB(255, 174, 201), 80);
	CTextDraw::Print(pdc, 823, 925, to_string((t / 600)) + to_string((t / 60) % 10) + " : " + to_string((t / 10) % 6) + to_string(t % 10));

	CTextDraw::ChangeFontLog(pdc, 40, "monogram", RGB(255, 255, 255), 60);
	CTextDraw::Print(pdc, 120, 950,to_string(t0.get_dead_monster() + t1.get_dead_monster() + t2.get_dead_monster()));

	CTextDraw::ChangeFontLog(pdc, 25, "monogram", RGB(255, 255, 255), 80);
	CTextDraw::Print(pdc, 305, blood_bar.GetTop() + 2, to_string(character.get_hp()));

	CTextDraw::ChangeFontLog(pdc, 25, "monogram", RGB(255, 255, 255), 80);
	CTextDraw::Print(pdc, 305, energy_bar.GetTop() +2, to_string(energy_bar.get_energy()) + "/ 25");

	CDDraw::ReleaseBackCDC();

}

void CGameStateRun::show_baclground_selected() {
	
	background.SetFrameIndexOfBitmap(get_init_background_value());
}

void CGameStateRun::set_over_data() {
	b = clock();
	int t = (int)(b - a - (suspend_end - suspend_start)) / CLOCKS_PER_SEC;
	string cout = "";
	for (int i = 0; i < 3; i++) {
		if (weapon_list[i] != 0) {
			cout += weapon_name[i] + " ";
		}
	}
	set_data(to_string((t / 600)) + to_string((t / 60) % 10) + " : " + to_string((t / 10) % 6) + to_string(t % 10),
		to_string(t0.get_dead_monster()+t1.get_dead_monster()+ t2.get_dead_monster()), cout);
}

bool CGameStateRun::isSelect(UINT nFlags, CPoint point, CMovingBitmap &item) {
	if (nFlags == TRUE) {
		if (item.GetLeft() <= point.x && point.x <= (item.GetLeft() + item.GetWidth())
			&& item.GetTop() <= point.y && point.y <= (item.GetTop() + item.GetHeight())) {

			return true;
		}
		else {
			return false;
		}
	}
	return false;
}

template<typename T>
void CGameStateRun::select_temp(T &t) {

	if (select_stage.weapon_selected == BRICKS) {
		t.bricks_born(bricks, { "Resources/weapon/cleaver.bmp" }, { 255, 255, 255 });
		t.get_data();
		weapon_list[select_stage.weapon_selected] += 1;
		select_stage.show = 0;
	}

	if (select_stage.weapon_selected == DART) {

		t.mygame_dart_born();
		t.share_data();
		weapon_list[select_stage.weapon_selected] += 1;
		select_stage.show = 0;
	}

	if (select_stage.weapon_selected == LIGHTNING) {

		t.lightning_born();
		t.share_data();
		weapon_list[select_stage.weapon_selected] += 1;
		select_stage.show = 0;
	}

	if (select_stage.weapon_selected == BLOOD_ADD) {
		t.share_data();
		character.set_hp(character.get_hp()+3500);
		t.get_data();
		select_stage.show = 0;
	}
	t.select = select_stage.show;

	energy_bar.set_energy(0);
	energy_bar.SetFrameIndexOfBitmap(0);
	select_stage.rand_option();

};

////////////////////////////////////////// CMovingBitmap class function  ////////////////////////////////////////////////////////////////////////////
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
				else {
					monster[i].set_hurted(1);
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
				//monster[i].set_hurted(1);
				if (monster[i].get_hp() <= 0) {
					monster_vanish.push_back(monster[i]);
					monster[i].set_hurted(0);
					monster_vanish[monster_vanish.size() - 1].SetAnimation(80, true);
					monster_vanish[monster_vanish.size() - 1].ShowBitmap();
					monster_vanish[monster_vanish.size() - 1].ToggleAnimation();
					monster_vanish[monster_vanish.size() - 1].SetFrameIndexOfBitmap(monster[i].set_end);
					monster.erase(monster.begin() + i);
				}
				else {
					monster[i].set_hurted(1);
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
