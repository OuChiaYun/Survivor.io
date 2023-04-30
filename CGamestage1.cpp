#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Game/CGamestage_all.h"
#include "../Library/gamecore.h"
#include "Source/Game/mygame.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <ctime>

using namespace game_framework;

void CGamestage1::OnBeginState() {};

void CGamestage1::OnInit() {


	for (int i = 0; i < 100; i++) {
		random_born_item(energy, { "Resources/gem/gem1.bmp", "Resources/gem/gem2.bmp",
								   "Resources/gem/gem3.bmp","Resources/gem/gem4.bmp","Resources/gem/gem5.bmp" }, { 200, 191, 231 });
		energy[i].SetAnimation(100, false);
	}



	for (int i = 0; i < 30; i++) {
		int arr[] = { 1,2,3 };
		random_born_monster(monster, {
			"Resources/monster/m1.bmp","Resources/monster/m2.bmp","Resources/monster/m3.bmp","Resources/monster/m4.bmp","Resources/monster/m5.bmp",
			"Resources/monster/m6.bmp","Resources/monster/m7.bmp","Resources/monster/m8.bmp","Resources/monster/m9.bmp","Resources/monster/m10.bmp",
			"Resources/monster/e1.bmp","Resources/monster/e2.bmp","Resources/monster/e3.bmp","Resources/monster/e4.bmp","Resources/monster/e5.bmp",
			"Resources/monster/e6.bmp","Resources/monster/e7.bmp","Resources/monster/e8.bmp","Resources/monster/e9.bmp","Resources/monster/e10.bmp",
			"Resources/monster/d1.bmp","Resources/monster/d2.bmp","Resources/monster/d3.bmp","Resources/monster/d4.bmp","Resources/monster/d5.bmp",
			"Resources/monster/d6.bmp","Resources/monster/d7.bmp","Resources/monster/d8.bmp","Resources/monster/d9.bmp","Resources/monster/d10.bmp" },
			monster_vanish, { "Resources/monster/m11.bmp", "Resources/monster/m12.bmp", "Resources/monster/m13.bmp", "Resources/monster/m14.bmp", "Resources/monster/m15.bmp",
			"Resources/monster/m16.bmp", "Resources/monster/m17.bmp" }, { 255,255,255 }, { 200, 191, 231 });  //255
		monster[i].SetAnimation(50, false);
		monster[i].set_hp(6);
		/*
		monster_vanish.push_back(CMovingBitmap());
		monster_vanish[i].SetTopLeft(5000, 5000);
		monster_vanish[i].
		*/

	}

	blood.LoadBitmapByString({ "Resources/ignore.bmp", "Resources/blood/bloodfx001_01.bmp",
							"Resources/blood/bloodfx001_02.bmp", "Resources/blood/bloodfx001_03.bmp",
							"Resources/blood/bloodfx001_04.bmp", "Resources/blood/bloodfx001_05.bmp",
							"Resources/ignore.bmp" }, RGB(255, 255, 255));
	blood.SetTopLeft(character.GetLeft() + character.GetWidth(), character.GetTop());
	int axay[5][4] = { {-5,2},{5,2},{-5,-2},{5,-2} };
	for (int i = 0; i < 4; i++) {
		lightning.push_back(CMovingBitmap());
		lightning[i].LoadBitmapByString({ "Resources/lightning/g1.bmp","Resources/lightning/g2.bmp","Resources/lightning/g3.bmp","Resources/lightning/g4.bmp",
										  "Resources/lightning/g5.bmp" ,"Resources/lightning/g6.bmp" ,"Resources/lightning/g7.bmp" ,"Resources/lightning/g8.bmp",
										  "Resources/lightning/g9.bmp", "Resources/lightning/g10.bmp", "Resources/lightning/g11.bmp", "Resources/lightning/g12.bmp",
										  "Resources/lightning/g13.bmp" ,"Resources/lightning/g14.bmp" ,"Resources/lightning/g15.bmp" ,"Resources/lightning/g16.bmp",
										  "Resources/lightning/g17.bmp" ,"Resources/lightning/g18.bmp" ,"Resources/lightning/g19.bmp", "Resources/lightning/g20.bmp"}, RGB(255, 255, 255));
		lightning[i].SetTopLeft(character.GetLeft() + character.GetWidth() / 2 - lightning[i].GetWidth()/2, character.GetTop());
		lightning[i].SetAnimation(30, false);
		lightning[i].stdx = character.GetLeft() + (character.GetWidth() / 2);
		lightning[i].stdy = character.GetTop();
		lightning[i].ax = axay[i][0];
		lightning[i].ay = axay[i][1];
	}
}

void CGamestage1::OnKeyDown(UINT, UINT, UINT) {};

void CGamestage1::OnKeyUp(UINT, UINT, UINT) {};

void CGamestage1::OnLButtonDown(UINT nFlags, CPoint point) {};

void CGamestage1::OnLButtonUp(UINT nFlags, CPoint point) {};

void CGamestage1::OnMouseMove(UINT nFlags, CPoint point) {
	get_data();
	if (nFlags == FALSE) {
		opera.SetTopLeft(437, 682);
		opera.set_center(491, 736);

	}
	else  {

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
	share_data();
};

void CGamestage1::OnRButtonDown(UINT nFlags, CPoint point) {};

void CGamestage1::OnRButtonUp(UINT nFlags, CPoint point) {};

void CGamestage1::OnMove() {
	get_data();
	timer += 1;

	background_move();

	blood.SetTopLeft(character.GetLeft() + character.GetWidth(), character.GetTop());
	blood_bar_progress(blood_bar, character);

	if (energy_bar.GetFrameIndexOfBitmap() > 2) {
		//select_bar.ShowBitmap();
		if (select != 2) {
			select = 1;
		}
		dart_all(200);
	}

	for (int i = 0; i < (int)(energy.size()); i++) {
		if (!energy[i].IsOverlap(character, energy[i]))
			item_move(energy[i]);
	}
	character.item_hit_energy(character, energy, energy_bar);
	monster_all();

	bullet_move(bullet);
	born_bullet(bullet, { "Resources/bullet.bmp" }, { 255, 255, 255 });
	bullet_erase(bullet);

	character.dart_hit_monster(dart, monster, monster_vanish);

	lightning_move(lightning);

	for (int i = 0; i < (int)(lightning.size()); i++) {
		int ax = lightning[i].GetLeft();
		int ay = lightning[i].GetTop();
		item_move(lightning[i]);

		lightning[i].stdx += lightning[i].GetLeft()-ax;
		lightning[i].stdy += lightning[i].GetTop()-ay;

	}
	share_data();
};

void CGamestage1::OnShow() {
	get_data();
	show_img();
	show_text();
	share_data();
};

void CGamestage1::show_img() {

	//show_baclground_selected();
	background.ShowBitmap();
	character.ShowBitmap();


	for (int i = 0; i < (int)energy.size(); i++) {
		energy[i].ShowBitmap();
	}
	if (energy_bar.GetFrameIndexOfBitmap() > 2) {

		for (int i = 0; i < (int)dart.size(); i++) {
			dart[i].ShowBitmap();
		}
	}
	for (int i = 0; i < (int)(monster.size()); i++) {
		if (monster[i].GetFrameIndexOfBitmap() >= monster[i].limit_frame_end) {
			monster[i].SetFrameIndexOfBitmap(monster[i].limit_frame_start);
		}
		if (monster[i].IsOverlap(background, monster[i])) {
			monster[i].ShowBitmap();
		}
	}

	for (int i = 0; i < (int)monster_vanish.size(); i++) {
		monster_vanish[i].ShowBitmap();
		if (monster_vanish[i].IsAnimationDone()) {
			monster_vanish.erase(monster_vanish.begin() + i);
		}
	}

	for (int i = 0; i < (int)bullet.size(); i++) {
		bullet[i].ShowBitmap();
	}

	for (int i = 0; i < (int)lightning.size(); i++) {
		lightning[i].ShowBitmap();
	}

	blood.ShowBitmap();
	blood_bar.ShowBitmap();
	opera.ShowBitmap();
	energy_bar.ShowBitmap();
	//timer_express.ShowBitmap();
}

void CGamestage1::show_text() {

	CDC *pdc = CDDraw::GetBackCDC();

	CTextDraw::ChangeFontLog(pdc, 25, "Modern No. 20", RGB(255, 255, 255), 80);
	CTextDraw::Print(pdc, 305, 10, to_string(character.get_hp()));

	CTextDraw::ChangeFontLog(pdc, 25, "Modern No. 20", RGB(255, 255, 255), 80);
	CTextDraw::Print(pdc, 305, energy_bar.GetTop() + 20 + 25, to_string(energy_bar.get_energy()) + "/ 25");

	CDDraw::ReleaseBackCDC();

}

void CGamestage1::background_move() {
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
	else if (opera.center_x > 491) {
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

			background.SetTopLeft(background.GetLeft() + ax, background.GetTop() + ay);
		}
		else {
			background.SetTopLeft(background.GetLeft(), background.GetTop() + ay);
		}

	}
	else if (background.GetLeft() + background.GetWidth() < 1045) { //item->character
		if (ax > 0) { //turn left
			background.SetTopLeft(background.GetLeft() + ax, background.GetTop() + ay);
		}
		else {
			background.SetTopLeft(background.GetLeft(), background.GetTop() + ay);
		}
	}
	else if (background.GetTop() > 0) { //character->item
		if ((opera.GetTop()) > 682) { //turn right
			background.SetTopLeft(background.GetLeft() + ax, background.GetTop() + ay);
		}
		else {
			background.SetTopLeft(background.GetLeft() + ax, background.GetTop());

		}
	}
	else if (background.GetTop() + background.GetHeight() < 1045) { //character->item
		if ((opera.GetTop()) < 682) {
			background.SetTopLeft(background.GetLeft() + ax, background.GetTop() + ay);
		}
		else {
			background.SetTopLeft(background.GetLeft() + ax, background.GetTop());
		}
	}
	else {
		background.SetTopLeft(background.GetLeft() + ax, background.GetTop() + ay);

	}
}

void CGamestage1::blood_bar_progress(CMovingBitmap &blood_bar, CMovingBitmap &item_blood) {
	if (blood_bar.GetFrameIndexOfBitmap() > 0 && item_blood.get_hp() < (1000 * blood_bar.GetFrameIndexOfBitmap())) {
		blood_bar.SetFrameIndexOfBitmap(blood_bar.GetFrameIndexOfBitmap() - 1);
	}
}

void CGamestage1::random_born_item(vector<CMovingBitmap>&item, vector<string> str, vector<int>rgb) {
	int min = -1450;
	int max = 1450;
	int tail = item.size();

	item.push_back(CMovingBitmap());
	item[tail].LoadBitmapByString(str, RGB(rgb[0], rgb[1], rgb[2]));
	int x = rand() % (max - min + 1) + min;
	int y = rand() % (max - min + 1) + min;
	item[tail].SetTopLeft(x, y);
	item[tail].set_center(x + 45, y + 57);
};

void CGamestage1::item_move(CMovingBitmap &item) {
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

void CGamestage1::mygame_dart_born(){
	
	dart.push_back(CMovingBitmap());
	int i = dart.size() - 1;
	
	dart[i].LoadBitmapByString({
	"Resources/weapon/hot_wheels/00.bmp",
	"Resources/weapon/hot_wheels/01.bmp",
	"Resources/weapon/hot_wheels/02.bmp",
	"Resources/weapon/hot_wheels/03.bmp",
	"Resources/weapon/hot_wheels/04.bmp",
	"Resources/weapon/hot_wheels/05.bmp",
	"Resources/weapon/hot_wheels/06.bmp",
	"Resources/weapon/hot_wheels/07.bmp" }, RGB(255, 255, 255));
	
	for (int j = 0; j < (int)dart.size(); j++) {
		dart[j].SetTopLeft(character.GetLeft() + 30, character.GetTop() - 10);
		dart[j].set_timer((int)(j + 1)*(360 / dart.size()));
		dart[j].SetAnimation(100, false);
	}
}

void CGamestage1::dart_all(int setR) {
	for (int i = 0; i < (int)dart.size(); i++) {
		dart[i].add_timer(1);
		dart_move(dart[i], (dart[i].timer % 360) * 5, setR);
		if (dart[i].get_timer() > 360) {
			dart[i].set_timer(0);
		}
	}
}

void CGamestage1::dart_move(CMovingBitmap &item, int i, int setR) {
	int r = setR;;
	int px = character.get_center_x() + (int)(r *cos(i * 3.14 / 180));
	int py = character.get_center_y() + (int)(r *sin(i * 3.14 / 180));
	item.SetTopLeft(px, py);
}

void CGamestage1::random_born_monster(vector<CMovingBitmap>&monster, vector<string> str_monster, vector<CMovingBitmap>&monster_vanish, vector<string> str_monster_vanish, vector<int>rgb_monster, vector<int>rgb_monster_vanish) {

	int min = -1450;
	int max = 1450;
	int tail = monster.size();

	monster.push_back(CMovingBitmap());
	monster[tail].LoadBitmapByString(str_monster, RGB(rgb_monster[0], rgb_monster[1], rgb_monster[2]));
	monster[tail].LoadBitmapByString(str_monster_vanish, RGB(rgb_monster_vanish[0], rgb_monster_vanish[1], rgb_monster_vanish[2]));

	int x = rand() % (max - min + 1) + min;
	int y = rand() % (max - min + 1) + min;
	monster[tail].SetTopLeft(x, y);
	monster[tail].set_center(x + 45, y + 57);

	monster[tail].SetFrameIndexOfBitmap(monster[tail].limit_frame_start);

	if (isLeft(character, monster[tail])) {
		monster[tail].set_limit_start_end(10, 19);
		monster[tail].SetFrameIndexOfBitmap(monster[tail].limit_frame_start);
	}
	else {
		monster[tail].set_limit_start_end(0, 9);
		monster[tail].SetFrameIndexOfBitmap(monster[tail].limit_frame_start);

	}

	if (isDown(character, monster[tail]) && (monster[tail].GetLeft() > 365 && monster[tail].GetLeft() < 580)) {
		monster[tail].set_limit_start_end(20, 29);
		monster[tail].SetFrameIndexOfBitmap(monster[tail].limit_frame_start);
	}
	else {
		monster[tail].SetFrameIndexOfBitmap(monster[tail].limit_frame_start);
	}
}

void CGamestage1::monster_all() {
	for (int i = 0; i < (int)(monster.size()); i++) {
		item_move(monster[i]);
		if (!monster[i].IsOverlap(character, monster[i])) {
			monster_move(monster[i]);
			blood.SetAnimation(50, true);

		}
		else {
			character.add_sub_hp(-5);
			blood.SetAnimation(50, false);
			blood.ShowBitmap();
		}
	}

	if (timer % 10 == 0 && int(monster.size()) < 30) {
		random_born_monster(monster, {
			"Resources/monster/m1.bmp","Resources/monster/m2.bmp","Resources/monster/m3.bmp","Resources/monster/m4.bmp","Resources/monster/m5.bmp",
			"Resources/monster/m6.bmp","Resources/monster/m7.bmp","Resources/monster/m8.bmp","Resources/monster/m9.bmp","Resources/monster/m10.bmp",
			"Resources/monster/e1.bmp","Resources/monster/e2.bmp","Resources/monster/e3.bmp","Resources/monster/e4.bmp","Resources/monster/e5.bmp",
			"Resources/monster/e6.bmp","Resources/monster/e7.bmp","Resources/monster/e8.bmp","Resources/monster/e9.bmp","Resources/monster/e10.bmp",
			"Resources/monster/d1.bmp","Resources/monster/d2.bmp","Resources/monster/d3.bmp","Resources/monster/d4.bmp","Resources/monster/d5.bmp",
			"Resources/monster/d6.bmp","Resources/monster/d7.bmp","Resources/monster/d8.bmp","Resources/monster/d9.bmp","Resources/monster/d10.bmp" },
			monster_vanish, { "Resources/monster/m11.bmp", "Resources/monster/m12.bmp", "Resources/monster/m13.bmp", "Resources/monster/m14.bmp", "Resources/monster/m15.bmp",
			"Resources/monster/m16.bmp", "Resources/monster/m17.bmp" }, { 255,255,255 }, { 200, 191, 231 });
		monster[monster.size() - 1].SetFrameIndexOfBitmap(0);
		monster[monster.size() - 1].SetAnimation(50, false);
		monster[monster.size() - 1].set_hp(6);
	}

	if (timer == 10000) {
		timer = 0;
	}
}

bool CGamestage1::isLeft(CMovingBitmap &character, CMovingBitmap &item) {
	if (item.GetLeft() < character.GetLeft()) {
		return false;
	}
	else {
		return true;
	}
};

bool CGamestage1::isDown(CMovingBitmap &character, CMovingBitmap &item) {
	if (item.GetTop() - 200 < character.GetTop()) {
		return false;
	}
	else {
		return true;
	}
};

void CGamestage1::monster_move(CMovingBitmap &monster) {

	int x = abs(monster.GetLeft() - character.GetLeft());
	int y = abs(monster.GetTop() - character.GetTop());
	double std_a = 4;
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


	monster.SetTopLeft(monster.GetLeft() + (int)(np_x*_x*0.5), monster.GetTop() + (int)(np_y*_y*0.5));


	if (isLeft(character, monster)) {
		monster.set_limit_start_end(10, 19);

	}
	else {
		monster.set_limit_start_end(0, 9);


	}
	if (isDown(character, monster) && (monster.GetLeft() > 365 && monster.GetLeft() < 580)) {
		monster.set_limit_start_end(20, 28);
	}

};

void CGamestage1::bullet_move(vector<CMovingBitmap> &item) {
	for (int i = 0; i < (int)item.size(); i++) {
		item[i].SetTopLeft(character.GetLeft() + 10, item[i].GetTop() - 10);
		item[i].dart_hit_monster(item, monster, monster_vanish);
	}
}

void CGamestage1::born_bullet(vector<CMovingBitmap> &item, vector<string> str, vector<int>rgb) {
	int tail = item.size();
	if (item[tail - 1].GetTop() < 0) {
		item.push_back(CMovingBitmap());
		item[tail].LoadBitmapByString(str, RGB(rgb[0], rgb[1], rgb[2]));
		item[tail].SetTopLeft(character.GetLeft() + 10, character.GetTop());
	}
}

void CGamestage1::bullet_erase(vector<CMovingBitmap> &item) {
	if (item[0].GetTop() < 0) {
		item.erase(item.begin());
	}
}

void CGamestage1::monster_pop(int less_than_n) {

	for (int i = 0; i < (int)monster.size(); i++) {
		if ((int)monster.size() > less_than_n) {
			monster.erase(monster.begin() + i);
		}
		else {
			break;
		}
	}
}

void CGamestage1::show_baclground_selected(int s) {

	if (s == 0) {
		background.SetFrameIndexOfBitmap(0);

	}
	else if (s == 1) {
		background.SetFrameIndexOfBitmap(1);

	}

}

void CGamestage1::lightning_move(vector<CMovingBitmap> &item) {


	int flag = 0;
	for (int i = 0; i < (int) item.size(); i++) {

		if ((lightning[i].GetLeft() <= (lightning[i].stdx - 300)) || (lightning[i].GetLeft()+lightning[i].GetWidth() >= (lightning[i].stdx + 300))) {
			lightning[i].ax *= -1;
		}
		if (lightning[i].GetTop() < (lightning[i].stdy-1065)|| lightning[i].GetTop() > (lightning[i].stdy + 1065)) {
			flag++;
		}

		lightning[i].SetTopLeft(lightning[i].GetLeft() + lightning[i].ax, lightning[i].GetTop() +lightning[i].ay);
		
	}
	int axay[5][4] = { {-5,2},{5,2},{-5,-2},{5,-2} };
	if (flag == (int)lightning.size()) {
		for (int i = 0; i < (int)lightning.size(); i++) {
			lightning[i].SetTopLeft(character.GetLeft() + character.GetWidth() / 2 - lightning[i].GetWidth() / 2, character.GetTop());
			lightning[i].stdx = character.GetLeft() + (character.GetWidth() / 2);
			lightning[i].stdy = character.GetTop();
			lightning[i].ax = axay[i][0];
			lightning[i].ay = axay[i][1];
		}
	}

};


/////////////////////////////update data/////////////////



void CGamestage1::set_share_obj_data(CMovingBitmap &tmp_background, CMovingBitmap &tmp_character,
	CMovingBitmap &tmp_opera, CMovingBitmap &tmp_blood_bar, CMovingBitmap &tmp_energy_bar, vector <CMovingBitmap> &tmp_dart, vector<CMovingBitmap> &tmp_bullet) {

	p_background = &tmp_background;
	p_character = &tmp_character;
	p_opera = &tmp_opera;
	p_blood_bar = &tmp_blood_bar;
	p_energy_bar = &tmp_energy_bar;
	p_dart = &tmp_dart;
	p_bullet = &tmp_bullet;

	
	background = tmp_background;
	character = tmp_character;
	opera = tmp_opera;
	blood_bar = tmp_blood_bar;
	energy_bar = tmp_energy_bar;
	dart = tmp_dart;
	bullet = tmp_bullet;

}

void CGamestage1::move_share_obj_data(CMovingBitmap &tmp_background, CMovingBitmap &tmp_character,
	CMovingBitmap &tmp_opera, CMovingBitmap &tmp_blood_bar, CMovingBitmap &tmp_energy_bar, vector <CMovingBitmap> &tmp_dart, vector<CMovingBitmap> &tmp_bullet) {

	tmp_background = background;
	tmp_character = character;
	tmp_opera = opera;
	tmp_blood_bar = blood_bar;
	tmp_energy_bar = energy_bar;
	tmp_dart = dart;
	tmp_bullet = bullet;
};


void CGamestage1::get_data() {

	background = *p_background;
	character = *p_character;
	opera = *p_opera;
	blood_bar = *p_blood_bar;
	energy_bar = *p_energy_bar;
	dart = *p_dart;
	bullet = *p_bullet;

};


void CGamestage1::share_data() {

	*p_background = background;
	*p_character = character;
	*p_opera = opera;
	*p_blood_bar = blood_bar;
	*p_energy_bar = energy_bar;
	*p_dart = dart;
	*p_bullet = bullet;

};

