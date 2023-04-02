#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


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
	timer += 1;
	background_move();
	

	for (int i = 0; i < (int)(energy.size()); i++) {
		if(!energy[i].IsOverlap(character, energy[i]))
			item_move(energy[i]);
	}
	
	//character.item_hit(character, energy);
	
	character.item_hit_energy(character, energy, energy_bar);

	int flag = 0;
	for (int i = 0;i< (int)(monster.size()); i++) {
		item_move(monster[i]);
		if (!monster[i].IsOverlap(character, monster[i])) {
			monster_move(monster[i]);
			blood.SetAnimation(50, true);

		}
		else {
			//hit_count += 1;
			flag++;
			character.add_sub_hp(-5);
			/*if (flag <= 3) {
				character.SetFrameIndexOfBitmap(flag);
			}*/
			if (blood_bar.GetFrameIndexOfBitmap()>0 && character.get_hp() %1000 == 0) {
				blood_bar.SetFrameIndexOfBitmap(blood_bar.GetFrameIndexOfBitmap() - 1);
			}
			blood.SetAnimation(50, false);
			blood.ShowBitmap();
		}
	}

	if (flag == 0) {
		character.SetFrameIndexOfBitmap(0);
	}

	if (timer > 10 && int(monster.size())<300) {
		random_born_monster(monster, {
			"Resources/monster/m1.bmp","Resources/monster/m2.bmp","Resources/monster/m3.bmp","Resources/monster/m4.bmp","Resources/monster/m5.bmp",
			"Resources/monster/m6.bmp","Resources/monster/m7.bmp","Resources/monster/m8.bmp","Resources/monster/m9.bmp","Resources/monster/m10.bmp",
			"Resources/monster/e1.bmp","Resources/monster/e2.bmp","Resources/monster/e3.bmp","Resources/monster/e4.bmp","Resources/monster/e5.bmp",
			"Resources/monster/e6.bmp","Resources/monster/e7.bmp","Resources/monster/e8.bmp","Resources/monster/e9.bmp","Resources/monster/e10.bmp",
			"Resources/monster/d1.bmp","Resources/monster/d2.bmp","Resources/monster/d3.bmp","Resources/monster/d4.bmp","Resources/monster/d5.bmp",
			"Resources/monster/d6.bmp","Resources/monster/d7.bmp","Resources/monster/d8.bmp","Resources/monster/d9.bmp","Resources/monster/d10.bmp" },
			monster_vanish, { "Resources/monster/m11.bmp", "Resources/monster/m12.bmp", "Resources/monster/m13.bmp", "Resources/monster/m14.bmp", "Resources/monster/m15.bmp",
			"Resources/monster/m16.bmp", "Resources/monster/m17.bmp" }, { 255,255,255 }, { 200, 191, 231 });
		monster[monster.size()-1].SetAnimation(50, false);
		monster[monster.size() - 1].set_hp(6);
		timer = 0;
		//monster_vanish[monster_vanish.size() - 1].SetAnimation(50, false);
	}

	character.dart_hit_monster(dart, monster, monster_vanish);



	for (int i = 0; i < (int)dart.size(); i++) {
		dart[i].add_timer(1);
		dart_move(dart[i], (dart[i].timer % 360) * 5);
		if (dart[i].get_timer() > 360) {
			dart[i].set_timer(0);
		}
	}
	boss2_move();
	item_move(boss2);

}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{
	background.LoadBitmapByString({ "Resources/background/Purple Nebula/Purple_Nebula_03.bmp", "Resources/background/Blue Nebula/Blue_Nebula_02.bmp" });
	background.SetTopLeft(-1500, -1500);
	background2.LoadBitmapByString({ "Resources/background/Purple Nebula/Purple_Nebula_03.bmp", "Resources/background/Blue Nebula/Blue_Nebula_02.bmp" });
	background2.SetTopLeft(0, 4000);

	/*character.LoadBitmapByString({ "Resources/character/skeleton-animation_00.bmp","Resources/character/skeleton-animation_01.bmp","Resources/character/skeleton-animation_02.bmp", "Resources/character/skeleton-animation_03.bmp"
		,"Resources/character/skeleton-animation_04.bmp" ,"Resources/character/skeleton-animation_05.bmp" ,"Resources/character/skeleton-animation_06.bmp" ,"Resources/character/skeleton-animation_07.bmp" ,"Resources/character/skeleton-animation_08.bmp" 
		,"Resources/character/skeleton-animation_09.bmp" ,"Resources/character/skeleton-animation_10.bmp" }, RGB(255, 255, 255));*/
	character.LoadBitmapByString({ "Resources/character/char_04_s.bmp" }, RGB(200, 191, 231));
	character.SetTopLeft(461, 252);
	character.set_center(470,270); //40 49
	//character.SetAnimation(50, false);
	character.set_hp(50000);
	

	goal.LoadBitmapByString({ "Resources/goal.bmp" }, RGB(255, 255, 255));
	goal.SetTopLeft(100, 82);

	blood_bar.LoadBitmapByString({ "Resources/health_ui/health_ui_0.bmp", "Resources/health_ui/health_ui_1.bmp", "Resources/health_ui/health_ui_2.bmp", "Resources/health_ui/health_ui_3.bmp", "Resources/health_ui/health_ui_4.bmp" }, RGB(255, 255, 255));
	blood_bar.SetFrameIndexOfBitmap(blood_bar.GetFrameSizeOfBitmap() - 1);

	//energy_bar.LoadBitmapByString();

	boss2.LoadBitmapByString({ "Resources/boss2.bmp" }, RGB(255, 255, 255));
	boss2.SetTopLeft(100, 322);
	boss2.set_timer(1500);
	boss2.ax = 0;
	boss2.ay = 0;

	srand((unsigned)time(NULL));
	/* 指定亂數範圍 */

	for (int i = 0; i < 100; i++) {
		random_born_item(energy, { "Resources/gem/gem1.bmp", "Resources/gem/gem2.bmp","Resources/gem/gem3.bmp","Resources/gem/gem4.bmp","Resources/gem/gem5.bmp" }, { 200, 191, 231 });
		energy[i].SetAnimation(100, false);
	}
	for (int i = 0; i < 40; i++) {
		int arr[] = { 1,2,3 };
		random_born_monster(monster, {
			"Resources/monster/m1.bmp","Resources/monster/m2.bmp","Resources/monster/m3.bmp","Resources/monster/m4.bmp","Resources/monster/m5.bmp",
			"Resources/monster/m6.bmp","Resources/monster/m7.bmp","Resources/monster/m8.bmp","Resources/monster/m9.bmp","Resources/monster/m10.bmp",
			"Resources/monster/e1.bmp","Resources/monster/e2.bmp","Resources/monster/e3.bmp","Resources/monster/e4.bmp","Resources/monster/e5.bmp",
			"Resources/monster/e6.bmp","Resources/monster/e7.bmp","Resources/monster/e8.bmp","Resources/monster/e9.bmp","Resources/monster/e10.bmp",
			"Resources/monster/d1.bmp","Resources/monster/d2.bmp","Resources/monster/d3.bmp","Resources/monster/d4.bmp","Resources/monster/d5.bmp",
			"Resources/monster/d6.bmp","Resources/monster/d7.bmp","Resources/monster/d8.bmp","Resources/monster/d9.bmp","Resources/monster/d10.bmp" },
			monster_vanish, { "Resources/monster/m11.bmp", "Resources/monster/m12.bmp", "Resources/monster/m13.bmp", "Resources/monster/m14.bmp", "Resources/monster/m15.bmp",
			"Resources/monster/m16.bmp", "Resources/monster/m17.bmp" }, { 255,255,255 }, { 200, 191, 231 });
		monster[i].SetAnimation(50, false);
		monster[i].set_hp(6);
		//monster_vanish[i].SetAnimation(50, false);
	}

	opera.LoadBitmapByString({ "Resources/operator.bmp" }, RGB(105, 106, 106));
	opera.SetTopLeft(437, 682);
	opera.set_center(437 + 54, 682 + 54);//491 , 736

	
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
		dart[i].SetTopLeft(0, 0);
		dart[i].set_timer((int)(i+1)*(360/2));
		dart[i].SetAnimation(100, false);
	}
	blood.LoadBitmapByString({ "Resources/ignore.bmp", "Resources/blood/bloodfx001_01.bmp", "Resources/blood/bloodfx001_02.bmp", "Resources/blood/bloodfx001_03.bmp", "Resources/blood/bloodfx001_04.bmp", "Resources/blood/bloodfx001_05.bmp", "Resources/ignore.bmp" }, RGB(255, 255, 255));
	blood.SetTopLeft(520, 252);

	energy_bar.LoadBitmapByString({ "Resources/energy_bar/0.bmp", "Resources/energy_bar/1.bmp", "Resources/energy_bar/2.bmp", "Resources/energy_bar/3.bmp", "Resources/energy_bar/4.bmp", "Resources/energy_bar/5.bmp" }, RGB(200, 191, 231));
	energy_bar.SetTopLeft(0, 65);
	energy_bar.set_energy(0);
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{

}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{

}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
	// 處理滑鼠的動作
	if (nFlags == FALSE) {
		opera.SetTopLeft(437, 682);
		opera.set_center(491, 736);
	}
	else {

		if (point.x < 491) {
			if (opera.get_center_x() > 451) {
				opera.SetTopLeft((opera.GetLeft() - 6), opera.GetTop());
				opera.set_center(opera.get_center_x() - 6, opera.get_center_y());
			}
		}
		if (point.x > 491) {
			if (opera.get_center_x() < 541) {
				opera.SetTopLeft((opera.GetLeft() + 6), opera.GetTop());
				opera.set_center(opera.get_center_x() + 6, opera.get_center_y());
			}
		}

		if ((point.y < 736)) {
			if (opera.get_center_y() > 686) {
				
				opera.SetTopLeft(opera.GetLeft(), (opera.GetTop() - 6));
				opera.set_center(opera.get_center_x(), opera.get_center_y() - 6);
			}
		}
		if ((point.y) > 736) {
			if (opera.get_center_y() < 786) {
				opera.SetTopLeft(opera.GetLeft(), (opera.GetTop() + 6));
				opera.set_center(opera.get_center_x(), opera.get_center_y() + 6);
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
	show_text();
	show_img();
}

void CGameStateRun::show_img() {
	show_baclground_selected();
	background.ShowBitmap();
	character.ShowBitmap();
	//goal.ShowBitmap();
	boss2.ShowBitmap();
	for (int i = 0; i < (int)energy.size(); i++) {
		energy[i].ShowBitmap();
	}

	for (int i = 0;i< (int)(monster.size()); i++) {
		if (monster[i].GetFrameIndexOfBitmap() == monster[i].limit_frame_end) {
			monster[i].SetFrameIndexOfBitmap(monster[i].limit_frame_start);
		}
		if (monster[i].IsOverlap(background, monster[i])) {
			monster[i].ShowBitmap();
			monster_vanish[i].ShowBitmap();
		}
	}

	blood_bar.ShowBitmap();
	
	for (int i = 0; i < (int)dart.size(); i++) {
		dart[i].ShowBitmap();
	}

	blood.ShowBitmap();
	energy_bar.ShowBitmap();



	opera.ShowBitmap();

}

void CGameStateRun::show_text() {

}

void CGameStateRun::show_baclground_selected() {
	if (get_init_background_value() == 0) {
		background.SetFrameIndexOfBitmap(0);
		background2.SetFrameIndexOfBitmap(0);
	}
	else if (get_init_background_value() == 1) {
		background.SetFrameIndexOfBitmap(1);
		background2.SetFrameIndexOfBitmap(1);
	}
	//background.SetTopLeft(0, 0);
//	background2.SetTopLeft(0, 4000);

}

void CGameStateRun::background_move() {

	double rate = 0.1;

	int ch_x = character.GetLeft();
	int ch_y = character.GetTop();
	int opera_x = opera.GetLeft();
	int opera_y = opera.GetTop();
	int background_x = background.GetLeft();
	int background_y = background.GetTop();

	int ax = 0;
	int ay = 0;

	if (opera.center_x < 491) {
		ax = 1;
	}
	else if(opera.center_x > 491) {
		ax = -1;
	}

	if (opera.center_y < 736) {
		ay = 1;
	}
	else if (opera.center_y > 736) {
		ay = -1;
	}
	
	if (background_x > 0) { //character->item
		if (ax < 0) { //turn right

			background.SetTopLeft(background.GetLeft() + ax, background.GetTop()+ay);
			
		}
		else {
			background.SetTopLeft(background.GetLeft(), background.GetTop()+ay);

		}

	}
	else if (background.GetLeft() + background.GetWidth() < 1045) { //item->character
		if (ax> 0) { //turn left
			background.SetTopLeft(background.GetLeft() +ax, background.GetTop() +ay);

		}
		else {
			background.SetTopLeft(background.GetLeft(), background.GetTop() +ay);

		}
	}
	else if (background.GetTop() > 0) { //character->item
		if ((opera.GetTop()) > 682) { //turn right
			background.SetTopLeft(background.GetLeft() +ax, background.GetTop()+ay);
		}
		else {
			background.SetTopLeft(background.GetLeft() +ax, background.GetTop());

		}
	}
	else if (background.GetTop() + background.GetHeight() < 1045) { //character->item
		if ((opera.GetTop()) < 682) {
			background.SetTopLeft(background.GetLeft() +ax ,background.GetTop() +ay);
		}
		else {
			background.SetTopLeft(background.GetLeft() +ax, background.GetTop());

		}
	}
	else {
		background.SetTopLeft(background.GetLeft() + ax, background.GetTop() +ay);

	}



}

void CGameStateRun::item_move(CMovingBitmap &item) {
	double rate = 0.12;
	int x = item.GetLeft() - int((opera.GetLeft() - 437)*rate);
	int y = item.GetTop() - int((opera.GetTop() - 682)*rate);

	int std_x = background.GetLeft();
	int std_w = background.GetWidth();


	if (background.GetLeft() >= character.GetLeft()) { //character->item
		if (opera.GetLeft() > 437) { //turn right
			item.SetTopLeft(item.GetLeft() - int((opera.GetLeft() - 437)*rate), item.GetTop() - int((opera.GetTop() - 682)*rate));
		}
		else {
			item.SetTopLeft(item.GetLeft(), item.GetTop() - int((opera.GetTop() - 682)*rate));
		}
	}
	else if (background.GetLeft() + background.GetWidth() <= character.GetLeft() + character.GetWidth()) { //item->character
		if ((opera.GetLeft()) < 437) { //turn left
			item.SetTopLeft(item.GetLeft() - int((opera.GetLeft() - 437)*rate), item.GetTop() - int((opera.GetTop() - 682)*rate));
		}
		else {
			item.SetTopLeft(item.GetLeft(), item.GetTop() - int((opera.GetTop() - 682)*rate));
		}
	}

	else if (background.GetTop() >= character.GetTop()) { //character->item
		if (opera.GetTop() > 682) { //turn right
			item.SetTopLeft(item.GetLeft() - int((opera.GetLeft() - 437)*rate), item.GetTop() - int((opera.GetTop() - 682)*rate));
		}
		else {
			item.SetTopLeft(item.GetLeft() - int((opera.GetLeft() - 437)*rate), item.GetTop());
		}
	}
	else if (background.GetTop() + background.GetHeight() <= character.GetTop() + character.GetHeight()) { //item->character
		if ((opera.GetLeft()) > 682) { //turn left
			item.SetTopLeft(item.GetLeft() - int((opera.GetLeft() - 437)*rate), item.GetTop() - int((opera.GetTop() - 682)*rate));
		}
		else {
			item.SetTopLeft(item.GetLeft() - int((opera.GetLeft() - 437)*rate), item.GetTop());
		}
	}
	else {

		item.SetTopLeft(item.GetLeft() - int((opera.GetLeft() - 437)*rate), item.GetTop() - int((opera.GetTop() - 682)*rate));

	}
}

void CMovingBitmap::item_hit(CMovingBitmap &character, vector<CMovingBitmap> &item) {
	for (int i = 0; i < (int)item.size(); i++) {
		if (IsOverlap(character, item[i])) {
			item.erase(item.begin() + i);
			break;
		}
	}
}

void CMovingBitmap::dart_hit_monster(vector<CMovingBitmap> &dart, vector<CMovingBitmap> &monster, vector<CMovingBitmap> &monster_vanish) {

	for (int i = 0; i < (int)monster.size(); i++) {

		for (int j = 0; j < (int)dart.size(); j++) {
			if (IsOverlap(dart[j], monster[i])) {

				monster[i].add_sub_hp(-1);
				if (monster[i].get_hp() <= 0) {
					monster_vanish[i].SetTopLeft(monster[i].GetLeft(), monster[i].GetTop());
					monster.erase(monster.begin() + i);

					monster_vanish[i].SetAnimation(80, true);
					monster_vanish[i].ShowBitmap();
					monster_vanish[i].ToggleAnimation();
					if (monster_vanish[i].IsAnimationDone())
						monster_vanish.erase(monster_vanish.begin() + i);
					break;
				}
				
			}
		}
	}
}


void CGameStateRun::monster_move(CMovingBitmap &monster) {

	int x = abs(monster.GetLeft() - character.GetLeft());
	int y = abs(monster.GetTop() - character.GetTop());
	double std_a = 2.2;
	double a = pow((x*x + y * y), 0.5);
	int _x = (int)(x / (a / std_a));
	int _y = (int)(y / (a / std_a));

	int np_x = 1;
	int np_y = 1;

	if (monster.GetLeft() < character.GetLeft()) {
		np_x = 1;
	}
	else if (monster.GetLeft() > character.GetLeft()) {
		np_x = -1;
	}

	if (monster.GetTop() < character.GetTop()) {
		np_y = 1;
	}
	else if (monster.GetTop() > character.GetTop()) {
		np_y = -1;
	}


	monster.SetTopLeft(monster.GetLeft() + (int)(np_x*_x), monster.GetTop() + (int)(np_y*_y));


	if (isLeft(character, monster)) {
		monster.set_limit_start_end(10, 19);
	}
	else {
		monster.set_limit_start_end(0, 9);

	}
	if (isDown(character, monster) && (monster.GetLeft() > 365 && monster.GetLeft() < 580)) {
		monster.set_limit_start_end(20, 29);
	}

};

void CGameStateRun::random_born_item(vector<CMovingBitmap> &item, vector<string> str, vector<int>rgb) {

	int min = -1450;
	int max = 1450;
	int tail = item.size();

	item.push_back(CMovingBitmap());
	item[tail].LoadBitmapByString(str, RGB(rgb[0], rgb[1], rgb[2]));
	/* 產生 [min , max] 的整數亂數 */
	int x = rand() % (max - min + 1) + min;
	int y = rand() % (max - min + 1) + min;
	item[tail].SetTopLeft(x, y);
	item[tail].set_center(x + 45, y + 57);
}

void CGameStateRun::random_born_monster(vector<CMovingBitmap>&monster, vector<string> str_monster, vector<CMovingBitmap>&monster_vanish, vector<string> str_monster_vanish, vector<int>rgb_monster, vector<int>rgb_monster_vanish) {

	int min = -1450;
	int max = 1450;
	int tail = monster.size();

	monster.push_back(CMovingBitmap());
	monster[tail].LoadBitmapByString(str_monster, RGB(rgb_monster[0], rgb_monster[1], rgb_monster[2]));
	

	monster_vanish.push_back(CMovingBitmap());
	monster_vanish[tail].LoadBitmapByString(str_monster_vanish, RGB(rgb_monster_vanish[0], rgb_monster_vanish[1], rgb_monster_vanish[2]));
	/* 產生 [min , max] 的整數亂數 */
	int x = rand() % (max - min + 1) + min;
	int y = rand() % (max - min + 1) + min;
	monster[tail].SetTopLeft(x, y);
	monster[tail].set_center(x + 45, y + 57);
	monster_vanish[tail].SetTopLeft(x, y);
	monster_vanish[tail].set_center(x + 45, y + 57);
	monster_vanish[tail].SetFrameIndexOfBitmap(6);

	monster[tail].SetFrameIndexOfBitmap(monster[tail].limit_frame_start);

	if (isLeft(character, monster[tail])) {
		monster[tail].set_limit_start_end(10, 19);
		monster[tail].SetFrameIndexOfBitmap(monster[tail].limit_frame_start);
	}
	else {
		monster[tail].set_limit_start_end(0,9);
		monster[tail].SetFrameIndexOfBitmap(monster[tail].limit_frame_start);

	}

	if (isDown(character, monster[tail]) && (monster[tail].GetLeft()>365 && monster[tail].GetLeft() < 580)) {
		monster[tail].set_limit_start_end(20, 29);
		monster[tail].SetFrameIndexOfBitmap(monster[tail].limit_frame_start);
	}
	else {
		monster[tail].SetFrameIndexOfBitmap(monster[tail].limit_frame_start);
	}
}

void CGameStateRun::dart_move(CMovingBitmap &item,int i) {
	int r = 200;
		int px = character.get_center_x() + (int)(r *cos(i * 3.14 / 180));
		int py = character.get_center_y() + (int)(r *sin(i * 3.14 / 180));
		item.SetTopLeft(px,py);
}

bool CGameStateRun::isLeft(CMovingBitmap &character, CMovingBitmap &item) {
	if (item.GetLeft() < character.GetLeft()) {
		return false;
	}
	else{
		return true;
	}
};

bool CGameStateRun::isDown(CMovingBitmap &character, CMovingBitmap &item) {
	if (item.GetTop()-200 < character.GetTop()) {
		return false;
	}
	else {
		return true;
	}
};

void CMovingBitmap::set_limit_start_end(int start, int end) {
	limit_frame_start = start;
	limit_frame_end = end;
};


void CGameStateRun::boss2_move() {
	boss2.add_timer(1);
	if (boss2.get_timer() < 200) {
		boss2.SetTopLeft(boss2.GetLeft()+boss2.ax,boss2.GetTop()+boss2.ay);
	}
	else{
		boss2.set_timer(0);
		int x = rand() % 20-10;
		int y = rand() % 20-10;
		boss2.ax = x;
		boss2.ay = y;
		//boss2.SetTopLeft(boss2.GetLeft() + boss2.ax, boss2.GetTop() + boss2.ay);
	}

	if (boss2.GetLeft() < -300) {
		int x = rand() % 13;
		boss2.ax = x;
		boss2.SetTopLeft(boss2.GetLeft() + boss2.ax, boss2.GetTop() + boss2.ay);
	}
	else if (boss2.GetLeft()+boss2.GetWidth() > 1300) {
		int x = 0 -rand() % 13;
		boss2.ax = x;
		boss2.SetTopLeft(boss2.GetLeft() + boss2.ax, boss2.GetTop() + boss2.ay);
	}

	if (boss2.GetTop() < -300) {
		int y = rand() % 13;
		boss2.ay = y;
		boss2.SetTopLeft(boss2.GetLeft() + boss2.ax, boss2.GetTop() + boss2.ay);
	}
	else if (boss2.GetTop()+boss2.GetHeight() > 1300) {
		int y = 0 - rand() % 13;
		boss2.ay = y;
		boss2.SetTopLeft(boss2.GetLeft() + boss2.ax, boss2.GetTop() + boss2.ay);
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
					//go to next phase
				}
			}
			break;
		}
	}
}
