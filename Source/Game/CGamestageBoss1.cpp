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

void CGamestageBoss1::OnBeginState() {};

void CGamestageBoss1::OnInit() {


	boss1.LoadBitmapByString({ "Resources/boss1/big_demon_idle_anim_f0.bmp", "Resources/boss1/big_demon_idle_anim_f1.bmp",
						   "Resources/boss1/big_demon_idle_anim_f1.bmp" ,  "Resources/boss1/big_demon_idle_anim_f3.bmp" }, RGB(255, 255, 255));

	boss1.SetAnimation(150, false);
	boss1.set_hp(5000);

	boss1_range.LoadBitmapByString({ "Resources/boss1/boss1_range.bmp" }, RGB(255, 255, 255));
	boss1_range.SetTopLeft(200,65 + 125 + 10);
	boss1.SetTopLeft(boss1_range.GetLeft() + 243, boss1_range.GetTop() + 130);

	
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
		boss1_bullet[i].LoadBitmapByString({ "Resources/Rock.bmp" }, RGB(255, 255, 255));
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


}

void CGamestageBoss1::OnKeyDown(UINT, UINT, UINT) {};

void CGamestageBoss1::OnKeyUp(UINT, UINT, UINT) {};

void CGamestageBoss1::OnLButtonDown(UINT nFlags, CPoint point) {};

void CGamestageBoss1::OnLButtonUp(UINT nFlags, CPoint point) {};


void CGamestageBoss1::OnMouseMove(UINT nFlags, CPoint point) {
	get_data();
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
	share_data();

};


void CGamestageBoss1::OnRButtonDown(UINT nFlags, CPoint point) {};

void CGamestageBoss1::OnRButtonUp(UINT nFlags, CPoint point) {};

void CGamestageBoss1::OnMove() {
	get_data();

	blood_bar_progress(blood_bar, character);
	bullet_move(bullet);
	born_bullet(bullet, { "Resources/bullet.bmp" }, { 255, 255, 255 });
	bullet_erase(bullet);
	

	boss1_bullet_move();
	boss1_background();

	dart_all(100);

	blood.SetTopLeft(character.GetLeft() + character.GetWidth(), character.GetTop());
	boss1_character_attack();

	blood_bar_progress(blood_bar_boss1, boss1);
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
	blood_bar.ShowBitmap();
	energy_bar.ShowBitmap();
	character.ShowBitmap();
	opera.ShowBitmap();

	show_text();
	share_data();


};


void CGamestageBoss1::show_text() {

	CDC *pdc = CDDraw::GetBackCDC();

	CTextDraw::ChangeFontLog(pdc, 25, "Modern No. 20", RGB(255, 255, 255), 80);
	CTextDraw::Print(pdc, 305, 10, to_string(character.get_hp()));

	CTextDraw::ChangeFontLog(pdc, 25, "Modern No. 20", RGB(255, 255, 255), 80);
	CTextDraw::Print(pdc, 305, energy_bar.GetTop() + 20 + 25, to_string(energy_bar.get_energy()) + "/ 25");

	CTextDraw::ChangeFontLog(pdc, 15, "Modern No. 20", RGB(255, 255, 255), 80);
	CTextDraw::Print(pdc, blood_bar_boss1.GetLeft() + 30, blood_bar_boss1.GetTop() + 10 + 20, to_string(boss1.get_hp()));

	CDDraw::ReleaseBackCDC();

}

void CGamestageBoss1::boss1_bullet_move() {
	for (int i = 0; i < (int)boss1_bullet.size(); i++) {
		int x = boss1.get_hit_x(i);
		int y = boss1.get_hit_y(i);
		boss1_bullet[i].SetTopLeft(boss1_bullet[i].GetLeft() + x, boss1_bullet[i].GetTop() + y);
		if (boss1_bullet[i].GetLeft() < boss1_range.GetLeft()) {
			boss1.set_hit_x(abs(x), i);
		}
		else if (boss1_bullet[i].GetLeft() + boss1_bullet[i].GetWidth() > boss1_range.GetLeft() + boss1_range.GetWidth()) {
			boss1.set_hit_x(-abs(x), i);
		}
		else if (boss1_bullet[i].GetTop() < boss1_range.GetTop()) {
			boss1.set_hit_y(abs(y), i);
		}
		else if (boss1_bullet[i].GetTop() + 26 > boss1_range.GetTop() + 430) {
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
	if (character.GetTop() + 60 > boss1_range.GetTop() + 430) { //bottom
		character.SetTopLeft(character.GetLeft(), boss1_range.GetTop() + 430 - 60);
	}

	character.set_center((character.GetLeft() + 10), (character.GetTop() + 10));
}


void CGamestageBoss1::boss1_character_attack() {
	for (int i = 0; i<int(bullet.size()); i++) {
		if (boss1.IsOverlap(bullet[i], boss1)) {
			boss1.add_sub_hp(-5);
			blood_boss1.SetAnimation(50, false);
			blood_boss1.ShowBitmap();
		}
		else {
			blood_boss1.SetAnimation(50, true);
		}
	}

	for (int i = 0; i<int(dart.size()); i++) {
		if (boss1.IsOverlap(dart[i], boss1)) {
			boss1.add_sub_hp(-5);
			blood_boss1.SetAnimation(50, false);
			blood_boss1.ShowBitmap();
		}
		else {
			blood_boss1.SetAnimation(50, true);
		}
	}
}



void CGamestageBoss1::bullet_move(vector<CMovingBitmap> &item) {
	for (int i = 0; i < (int)item.size(); i++) {
		item[i].SetTopLeft(character.GetLeft() + 10, item[i].GetTop() - 10);
		//item[i].dart_hit_monster(item, monster, monster_vanish);
	}
}

void CGamestageBoss1::born_bullet(vector<CMovingBitmap> &item, vector<string> str, vector<int>rgb) {
	int tail = item.size();
	if (item[tail - 1].GetTop() < 0) {
		item.push_back(CMovingBitmap());
		item[tail].LoadBitmapByString(str, RGB(rgb[0], rgb[1], rgb[2]));
		item[tail].SetTopLeft(character.GetLeft() + 10, character.GetTop());
	}
}

void CGamestageBoss1::bullet_erase(vector<CMovingBitmap> &item) {
	if (item[0].GetTop() < 0) {
		item.erase(item.begin());
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
	if (blood_bar.GetFrameIndexOfBitmap() > 0 && item_blood.get_hp() < (1000 * blood_bar.GetFrameIndexOfBitmap())) {
		blood_bar.SetFrameIndexOfBitmap(blood_bar.GetFrameIndexOfBitmap() - 1);
	}
}


/////////////////////////////update data/////////////////

void CGamestageBoss1::set_share_obj_data(CMovingBitmap &tmp_background, CMovingBitmap &tmp_character,
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

void CGamestageBoss1::move_share_obj_data(CMovingBitmap &tmp_background, CMovingBitmap &tmp_character,
	CMovingBitmap &tmp_opera, CMovingBitmap &tmp_blood_bar, CMovingBitmap &tmp_energy_bar, vector <CMovingBitmap> &tmp_dart, vector<CMovingBitmap> &tmp_bullet) {

	tmp_background = background;
	tmp_character = character;
	tmp_opera = opera;
	tmp_blood_bar = blood_bar;
	tmp_energy_bar = energy_bar;
	tmp_dart = dart;
	tmp_bullet = bullet;
};


void CGamestageBoss1::get_data() {

	background = *p_background;
	character = *p_character;
	opera = *p_opera;
	blood_bar = *p_blood_bar;
	energy_bar = *p_energy_bar;
	dart = *p_dart;
	bullet = *p_bullet;

};


void CGamestageBoss1::share_data() {

	*p_background = background;
	*p_character = character;
	*p_opera = opera;
	*p_blood_bar = blood_bar;
	*p_energy_bar = energy_bar;
	*p_dart = dart;
	*p_bullet = bullet;

};