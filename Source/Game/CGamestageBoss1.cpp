#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Game/CGamestage_all.h"
#include "../Library/gamecore.h"
#include "../Game/mygame.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <ctime>

using namespace game_framework;

void CGamestageBoss1::OnBeginState() {
	run = 1;
	boss1.set_hp(5000);
	blood_bar_boss1.SetFrameIndexOfBitmap(blood_bar_boss1.GetFrameSizeOfBitmap()-1);
	timmer = 0;

	int x[5] = { 5, 10, -2 };
	int y[5] = { 3,  -2,   8 };

	for (int i = 0; i < 3; i++) {
		boss1_bullet[i].SetTopLeft(boss1_range.GetLeft() + 270 + 10, boss1_range.GetTop() + 130);
		boss1.set_hit_x(x[i], i);
		boss1.set_hit_y(y[i], i);
	}

};

void CGamestageBoss1::OnInit() {


	boss1.LoadBitmapByString({ "Resources/boss1/big_demon_idle_anim_f0.bmp", "Resources/boss1/big_demon_idle_anim_f1.bmp",
						   "Resources/boss1/big_demon_idle_anim_f1.bmp" ,  "Resources/boss1/big_demon_idle_anim_f3.bmp" }, RGB(255, 255, 255));

	boss1.SetAnimation(150, false);
	boss1.set_hp(5000);
	boss1.set_hp_max(5000);

	boss1_range.LoadBitmapByString({ "Resources/boss1/boss1_range.bmp", "Resources/boss1/boss1_range_1.bmp", "Resources/boss1/boss1_range_2.bmp", "Resources/boss1/boss1_range_3.bmp" }, RGB(255, 255, 255));
	boss1_range.SetAnimation(300, false);
	boss1_range.SetTopLeft(120,65 + 125 + 10);
	boss1.SetTopLeft(boss1_range.GetLeft() + 365 - 60, boss1_range.GetTop() + 130);

	
	blood.LoadBitmapByString({ "Resources/ignore.bmp", "Resources/blood/bloodfx001_01.bmp",
					"Resources/blood/bloodfx001_02.bmp", "Resources/blood/bloodfx001_03.bmp",
					"Resources/blood/bloodfx001_04.bmp", "Resources/blood/bloodfx001_05.bmp",
					"Resources/ignore.bmp" }, RGB(255, 255, 255));
	blood.SetTopLeft(character.GetLeft() + character.GetWidth(), character.GetTop());
	

	vector<int> x = { 5, 10, -2 };
	vector<int> y = { 3,  -2,   8 };

	int a = boss1.boss1_hit_x.size();
	int b = boss1.boss1_hit_y.size();

	for (int i = 0; i < 3; i++) {
		boss1_bullet.push_back(CMovingBitmap());
		boss1_bullet[i].LoadBitmapByString({ "Resources/boss1/Rock.bmp" }, RGB(255, 255, 255));
		boss1_bullet[i].SetTopLeft(boss1_range.GetLeft() + 270 + 10, boss1_range.GetTop() + 130);
		boss1.set_hit_x(x[i], i);
		boss1.set_hit_y(y[i], i);
	}


	blood_bar_boss1.LoadBitmapByString({ "Resources/health_ui/boss1/health_ui_0.bmp", "Resources/health_ui/boss1/health_ui_1.bmp",
										 "Resources/health_ui/boss1/health_ui_2.bmp", "Resources/health_ui/boss1/health_ui_3.bmp",
										 "Resources/health_ui/boss1/health_ui_4.bmp" }, RGB(255, 255, 255));
	blood_bar_boss1.SetFrameIndexOfBitmap(blood_bar_boss1.GetFrameSizeOfBitmap() - 1);

	blood_boss1.LoadBitmapByString({ "Resources/ignore.bmp", "Resources/blood/bloodfx001_01.bmp",
								 "Resources/blood/bloodfx001_02.bmp", "Resources/blood/bloodfx001_03.bmp",
								 "Resources/blood/bloodfx001_04.bmp", "Resources/blood/bloodfx001_05.bmp",
								 "Resources/ignore.bmp" }, RGB(255, 255, 255));
	jump.LoadBitmapByString({ "Resources/UI/jump.bmp" , "Resources/UI/jump_2.bmp" }, RGB(255, 255, 255));
	jump.SetTopLeft(770, 15);

}

void CGamestageBoss1::OnKeyDown(UINT, UINT, UINT) {};

void CGamestageBoss1::OnKeyUp(UINT, UINT, UINT) {};

void CGamestageBoss1::OnLButtonDown(UINT nFlags, CPoint point) {
	if (isSelect(nFlags, point, jump)) {
		boss1.set_hp(-1);
		run = 0;
	}
};

void CGamestageBoss1::OnLButtonUp(UINT nFlags, CPoint point) {};


void CGamestageBoss1::OnMouseMove(UINT nFlags, CPoint point) {

	get_data();
	if (isSelect(true, point, jump)) {

		jump.SetFrameIndexOfBitmap(1);
	}else{
		jump.SetFrameIndexOfBitmap(0);
	}

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

	if (opera.center_x < 491) {

		character.set_limit_start_end(14, 21);
	}
	else if (opera.center_x > 491) {

		character.set_limit_start_end(6, 13);
	}
	else {
		character.set_limit_start_end(0, 5);
	}
	if (character.GetFrameIndexOfBitmap() >= character.limit_frame_end || character.GetFrameIndexOfBitmap() <= character.limit_frame_start) {
		character.SetFrameIndexOfBitmap(character.limit_frame_start);
	}
	share_data();

};


void CGamestageBoss1::OnRButtonDown(UINT nFlags, CPoint point) {};

void CGamestageBoss1::OnRButtonUp(UINT nFlags, CPoint point) {};

void CGamestageBoss1::OnMove() {
	get_data();
	timmer+=1;


	blood_bar_progress(blood_bar, character);

	bullet_erase(bullet);
	bullet_move(bullet);

	dart_all(100);



	for (int i = 0; i < (int)bricks.size(); i++) {
		int j = bricks[i].ram_n;
		bricks_move(bricks, bricks[i].stdx + h[j], bricks[i].stdy + k[j], c[j], x_move[j], i);
		bricks_erase(bricks);
	}

	blood.SetTopLeft(character.GetLeft() + character.GetWidth(), character.GetTop());
	boss1_background();

	lightning_move(lightning);


	if(timmer > 200){


		boss1_bullet_move();
		boss1_character_attack();
		blood_bar_progress(blood_bar_boss1, boss1);
		if (boss1.get_hp() <= 0) {
			run = 0;
		}
	}
	share_data();
};

void CGamestageBoss1::OnShow() {
	get_data();
	background.ShowBitmap();
	boss1.ShowBitmap();
	blood.ShowBitmap();
	boss1_range.ShowBitmap();
	blood_bar_boss1.ShowBitmap();
	blood_bar_boss1.SetTopLeft(boss1.GetLeft(), boss1.GetTop() + 112 + 10);
	blood_boss1.ShowBitmap();
	blood_boss1.SetTopLeft(boss1.GetLeft() + boss1.GetWidth() / 2, boss1.GetTop());

	for (int i = 0; i < (int)boss1_bullet.size(); i++) {
		boss1_bullet[i].ShowBitmap();
	}

	for (int i = 0; i < (int)dart.size(); i++) {
		dart[i].ShowBitmap();
	}

	for (int i = 0; i < (int)bullet.size(); i++) {
		bullet[i].ShowBitmap();
	}

	for (int j = 0; j < (int)bricks.size(); j++) {
		bricks[j].ShowBitmap();
	}
	for (int i = 0; i < (int)lightning.size(); i++) {
		lightning[i].ShowBitmap();
	}
	blood_bar.ShowBitmap();
	energy_bar.ShowBitmap();
	if (character.GetFrameIndexOfBitmap() >= character.limit_frame_end) {
		character.SetFrameIndexOfBitmap(character.limit_frame_start);
	}
	character.ShowBitmap();
	opera.ShowBitmap();

	jump.ShowBitmap();

	show_text();
	share_data();

};


void CGamestageBoss1::show_text() {

	CDC *pdc = CDDraw::GetBackCDC();

	CTextDraw::ChangeFontLog(pdc, 15, "monogram", RGB(255, 255, 255), 80);
	CTextDraw::Print(pdc, blood_bar_boss1.GetLeft() + 30, blood_bar_boss1.GetTop() + 10 + 20, to_string(boss1.get_hp()));

	if (timmer < 100) {
		CTextDraw::ChangeFontLog(pdc, 40, "monogram", RGB(255, 255, 255), 80);
		CTextDraw::Print(pdc, 325, 500, "Boss1 Assault!!");
	}

	CDDraw::ReleaseBackCDC();

}

void CGamestageBoss1::boss1_bullet_move() {
	for (int i = 0; i < (int)boss1_bullet.size(); i++) {
		int x = boss1.get_hit_x(i);
		int y = boss1.get_hit_y(i);
		boss1_bullet[i].SetTopLeft(boss1_bullet[i].GetLeft() + x, boss1_bullet[i].GetTop() + y);
		if (boss1_bullet[i].GetLeft() < boss1_range.GetLeft() + 30) {
			boss1.set_hit_x(abs(x), i);
		}
		else if (boss1_bullet[i].GetLeft() + boss1_bullet[i].GetWidth() > boss1_range.GetLeft() + boss1_range.GetWidth() - 30) {
			boss1.set_hit_x(-abs(x), i);
		}
		else if (boss1_bullet[i].GetTop() < boss1_range.GetTop() + 30) {
			boss1.set_hit_y(abs(y), i);
		}
		else if (boss1_bullet[i].GetTop() + 26 > boss1_range.GetTop() + 630 - 30) {
			boss1.set_hit_y(-abs(y), i);
		}

		
		if (boss1.IsOverlap(boss1_bullet[i],character)) {
			character.add_sub_hp(-15);
			blood.SetAnimation(50, false);
			blood.ShowBitmap();
		}
		else {
			blood.SetAnimation(50, true);
		}
		
	}
}


void CGamestageBoss1::boss1_background() {

	int ax = 0;
	int ay = 0;

	if (opera.center_x < 491) {
		ax = -3;
	}
	else if (opera.center_x > 491) {
		ax = 3;
	}

	if (opera.center_y < 736) {
		ay = -3;
	}
	else if (opera.center_y > 736) {
		ay = 3;
	}

	character.SetTopLeft(character.GetLeft() + ax, character.GetTop() + ay);

	if (character.GetLeft() < boss1_range.GetLeft()) { //left
		character.SetTopLeft(boss1_range.GetLeft(), character.GetTop());
	}
	if (character.GetTop() < boss1_range.GetTop()) { //top
		character.SetTopLeft(character.GetLeft(), boss1_range.GetTop());
	}
	if (character.GetLeft() + character.GetWidth() > boss1_range.GetLeft() + boss1_range.GetWidth()) { //right
		character.SetTopLeft(boss1_range.GetLeft() + boss1_range.GetWidth() - character.GetWidth(), character.GetTop());
	}
	if (character.GetTop() + 130 > boss1_range.GetTop() + 630) { //bottom
		character.SetTopLeft(character.GetLeft(), boss1_range.GetTop() + 630 - 130);
	}

	character.set_center((character.GetLeft() + 10), (character.GetTop() + 10));
}

void CGamestageBoss1::boss1_character_attack() {
	for (int i = 0; i<int(bullet.size()); i++) {
		if (boss1.IsOverlap(bullet[i], boss1)) {
			boss1.add_sub_hp(-15);
			CAudio::Instance()->Play(AUDIO_Attack, false);
			blood_boss1.SetAnimation(50, false);
			blood_boss1.ShowBitmap();
		}
		else {
			blood_boss1.SetAnimation(50, true);
		}
	}

	for (int i = 0; i<int(dart.size()); i++) {
		if (boss1.IsOverlap(dart[i], boss1)) {
			boss1.add_sub_hp(-10);
			blood_boss1.SetAnimation(50, false);
			blood_boss1.ShowBitmap();
			CAudio::Instance()->Play(AUDIO_Attack, false);
		}
		else {
			blood_boss1.SetAnimation(50, true);
		}
	}
}


void CGamestageBoss1::bullet_move(vector<CMovingBitmap> &item) {
	for (int i = 0; i < (int)item.size(); i++) {
		item[i].SetTopLeft(character.GetLeft() + 20, item[i].GetTop() - 20);
	}
}

void CGamestageBoss1::born_bullet(vector<CMovingBitmap> &item, vector<string> str, vector<int>rgb) {
	    int tail = item.size();
		item.push_back(CMovingBitmap());
		item[tail].LoadBitmapByString(str, RGB(rgb[0], rgb[1], rgb[2]));
		item[tail].SetTopLeft(character.GetLeft() + 10, character.GetTop());
	
}

void CGamestageBoss1::bullet_erase(vector<CMovingBitmap> &item) {
	for (int i = 0; i < (int)item.size(); i++) {
		if (item[i].GetTop() < 0) {
			bullet[i].SetTopLeft(character.GetLeft() + 10, character.GetTop());
		}
	}
}

void CGamestageBoss1::dart_all(int setR) {
	for (int i = 0; i < (int)dart.size(); i++) {
		dart[i].add_timer(1);
		dart_move(dart[i], (dart[i].timer % 360) * 5, setR);
		if (dart[i].get_timer() > 360) {
			dart[i].set_timer(0);
		}
	}
}

void CGamestageBoss1::dart_move(CMovingBitmap &item, int i, int setR) {
	int r = setR;;
	int px = character.get_center_x() + (int)(r *cos(i * 3.14 / 180));
	int py = character.get_center_y() + (int)(r *sin(i * 3.14 / 180));
	item.SetTopLeft(px, py);
}

void CGamestageBoss1::blood_bar_progress(CMovingBitmap &blood_bar, CMovingBitmap &item_blood) {
	if (item_blood.get_hp() >= item_blood.get_hp_max()) {
		blood_bar.SetFrameIndexOfBitmap(blood_bar.GetFrameSizeOfBitmap() - 1);
	}
	else if (item_blood.get_hp() > 0) {
		blood_bar.SetFrameIndexOfBitmap(((item_blood.get_hp()) / (item_blood.get_hp_max() / 5)));
	}
}

void CGamestageBoss1::lightning_move(vector<CMovingBitmap> &item) {


	int flag = 0;
	int f[100] = { 0,0,0,0, 0,0,0,0 };
	for (int i = 0; i < (int)item.size(); i++) {

		if ((lightning[i].GetLeft() <= (lightning[i].stdx - 300)) || (lightning[i].GetLeft() +105 >= (lightning[i].stdx + 300))) {
			lightning[i].ax *= -1;
		}
		if (lightning[i].GetTop() < (lightning[i].stdy - 365) || lightning[i].GetTop() > (lightning[i].stdy + 365)) {
			flag++;
			f[i] = 1;
		}

		lightning[i].SetTopLeft(lightning[i].GetLeft() + lightning[i].ax, lightning[i].GetTop() + lightning[i].ay);
		if (character.IsOverlap(lightning[i], boss1)) {
			boss1.add_sub_hp(-5);
			CAudio::Instance()->Play(AUDIO_Attack, false);
			blood_boss1.SetAnimation(50, false);
			blood_boss1.ShowBitmap();
		}
		else {
			blood_boss1.SetAnimation(50, true);
		}
	}

	int axay[5][4] = { {-5,2},{5,2},{-5,-2},{5,-2} };
	if (flag % 4 == 0 && flag != 0) {
		for (int i = 0; i < (int)lightning.size(); i++) {
			if (f[i] == 1) {
				lightning[i].SetTopLeft(character.GetLeft() + character.GetWidth() / 2 - lightning[i].GetWidth() / 2, character.GetTop());
				lightning[i].stdx = character.GetLeft() + (character.GetWidth() / 2);
				lightning[i].stdy = character.GetTop();
				lightning[i].ax = axay[i % 4][0];
				lightning[i].ay = axay[i % 4][1];
			}
		}
	}
};

void CGamestageBoss1::bricks_move(vector<CMovingBitmap> &item, int h, int k, int c, int x_move, int i) {
	int x = item[i].GetLeft() + x_move;
	int y = (x - h) * (x - h) / (4 * c) + k;
	item[i].SetTopLeft(x, y);
	if (character.IsOverlap(item[i], boss1)) {
		boss1.add_sub_hp(-20);
		CAudio::Instance()->Play(AUDIO_Attack, false);
		blood_boss1.SetAnimation(50, false);
		blood_boss1.ShowBitmap();
	}
	else {
		blood_boss1.SetAnimation(50, true);
	}
}


void CGamestageBoss1::bricks_erase(vector<CMovingBitmap> &item) {

	for (int i = 0; i < (int)item.size(); i++) {
		if (item[i].GetTop() + 70 > 1065) {
			item[i].SetTopLeft(character.GetLeft() + 10, character.GetTop());
			item[i].stdx = character.GetLeft();
			bricks[i].stdy = character.GetTop();
			item[i].ram_n = (rand() + timmer) % 4;
		}
	}
}

bool CGamestageBoss1::isSelect(UINT nFlags, CPoint point, CMovingBitmap &item) {
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
};

/////////////////////////////update data/////////////////

void CGamestageBoss1::set_share_obj_data(CMovingBitmap &tmp_background, CMovingBitmap &tmp_character, CMovingBitmap &tmp_opera, CMovingBitmap &tmp_blood_bar, CMovingBitmap &tmp_energy_bar,
	vector <CMovingBitmap> &tmp_dart, vector<CMovingBitmap> &tmp_bullet, vector<CMovingBitmap> &tmp_bricks, vector<CMovingBitmap> &tmp_lightning) {
	p_background = &tmp_background;
	p_character = &tmp_character;
	p_opera = &tmp_opera;
	p_blood_bar = &tmp_blood_bar;
	p_energy_bar = &tmp_energy_bar;
	p_dart = &tmp_dart;
	p_bullet = &tmp_bullet;
	p_bricks = &tmp_bricks;
	p_lightning = &tmp_lightning;


	background = tmp_background;
	character = tmp_character;
	opera = tmp_opera;
	blood_bar = tmp_blood_bar;
	energy_bar = tmp_energy_bar;
	dart = tmp_dart;
	bullet = tmp_bullet;
	bricks = tmp_bricks;
	lightning = tmp_lightning;
}

void CGamestageBoss1::move_share_obj_data(CMovingBitmap &tmp_background, CMovingBitmap &tmp_character,
	CMovingBitmap &tmp_opera, CMovingBitmap &tmp_blood_bar, CMovingBitmap &tmp_energy_bar, vector <CMovingBitmap> &tmp_dart, vector<CMovingBitmap> &tmp_bullet, vector<CMovingBitmap> &tmp_bricks) {

	tmp_background = background;
	tmp_character = character;
	tmp_opera = opera;
	tmp_blood_bar = blood_bar;
	tmp_energy_bar = energy_bar;
	tmp_dart = dart;
	tmp_bullet = bullet;
	tmp_bricks = bricks;
};

void CGamestageBoss1::get_data() {

	background = *p_background;
	character = *p_character;
	opera = *p_opera;
	blood_bar = *p_blood_bar;
	energy_bar = *p_energy_bar;
	dart = *p_dart;
	bullet = *p_bullet;
	bricks = *p_bricks;
	lightning = *p_lightning;
};

void CGamestageBoss1::share_data() {

	*p_background = background;
	*p_character = character;
	*p_opera = opera;
	*p_blood_bar = blood_bar;
	*p_energy_bar = energy_bar;
	*p_dart = dart;
	*p_bullet = bullet;
	*p_bricks = bricks;
	*p_lightning = lightning;
};