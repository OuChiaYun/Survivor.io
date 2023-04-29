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

void CGamestageBoss2::OnBeginState() {};

void CGamestageBoss2::OnInit() {

	boss2.LoadBitmapByString({ "Resources/boss2.bmp" }, RGB(255, 255, 255));
	boss2.SetTopLeft(110, 322);
	boss2.set_timer(1500);
	boss2.ax = 0;
	boss2.ay = 0;

}

void CGamestageBoss2::OnKeyDown(UINT, UINT, UINT) {};

void CGamestageBoss2::OnKeyUp(UINT, UINT, UINT) {};

void CGamestageBoss2::OnLButtonDown(UINT nFlags, CPoint point) {};

void CGamestageBoss2::OnLButtonUp(UINT nFlags, CPoint point) {};

void CGamestageBoss2::OnMouseMove(UINT nFlags, CPoint point) {
	gat_data();

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


void CGamestageBoss2::OnRButtonDown(UINT nFlags, CPoint point) {};

void CGamestageBoss2::OnRButtonUp(UINT nFlags, CPoint point) {};

void CGamestageBoss2::OnMove() {
	gat_data();


	background_move();
	boss2_move();

	dart_all(200);
	bullet_move(bullet);
	born_bullet(bullet, { "Resources/bullet.bmp" }, { 255, 255, 255 });
	bullet_erase(bullet);


	share_data();
};

void CGamestageBoss2::OnShow() {
	gat_data();
	background.ShowBitmap();

	boss2.ShowBitmap();


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

void CGamestageBoss2::show_text() {

	CDC *pdc = CDDraw::GetBackCDC();

	CTextDraw::ChangeFontLog(pdc, 25, "Modern No. 20", RGB(255, 255, 255), 80);
	CTextDraw::Print(pdc, 305, 10, to_string(character.get_hp()));

	CTextDraw::ChangeFontLog(pdc, 25, "Modern No. 20", RGB(255, 255, 255), 80);
	CTextDraw::Print(pdc, 305, energy_bar.GetTop() + 20 + 25, to_string(energy_bar.get_energy()) + "/ 25");

	CDDraw::ReleaseBackCDC();

}


void CGamestageBoss2::background_move() {
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

void CGamestageBoss2::bullet_move(vector<CMovingBitmap> &item) {
	for (int i = 0; i < (int)item.size(); i++) {
		item[i].SetTopLeft(character.GetLeft() + 10, item[i].GetTop() - 10);
		//item[i].dart_hit_monster(item, monster, monster_vanish);
	}
}

void CGamestageBoss2::born_bullet(vector<CMovingBitmap> &item, vector<string> str, vector<int>rgb) {
	int tail = item.size();
	if (item[tail - 1].GetTop() < 0) {
		item.push_back(CMovingBitmap());
		item[tail].LoadBitmapByString(str, RGB(rgb[0], rgb[1], rgb[2]));
		item[tail].SetTopLeft(character.GetLeft() + 10, character.GetTop());
	}
}

void CGamestageBoss2::bullet_erase(vector<CMovingBitmap> &item) {
	if (item[0].GetTop() < 0) {
		item.erase(item.begin());
	}
}

void CGamestageBoss2::dart_all(int setR) {
	for (int i = 0; i < (int)dart.size(); i++) {
		dart[i].add_timer(1);
		dart_move(dart[i], (dart[i].timer % 360) * 5, setR);
		if (dart[i].get_timer() > 360) {
			dart[i].set_timer(0);
		}
	}
}

void CGamestageBoss2::dart_move(CMovingBitmap &item, int i, int setR) {
	int r = setR;;
	int px = character.get_center_x() + (int)(r *cos(i * 3.14 / 180));
	int py = character.get_center_y() + (int)(r *sin(i * 3.14 / 180));
	item.SetTopLeft(px, py);
}

void CGamestageBoss2::blood_bar_progress(CMovingBitmap &blood_bar, CMovingBitmap &item_blood) {
	if (blood_bar.GetFrameIndexOfBitmap() > 0 && item_blood.get_hp() < (1000 * blood_bar.GetFrameIndexOfBitmap())) {
		blood_bar.SetFrameIndexOfBitmap(blood_bar.GetFrameIndexOfBitmap() - 1);
	}
}


///////////////////////////////////////////////////////

void CGamestageBoss2::boss2_move() {
	boss2.add_timer(1);
	if (boss2.get_timer() < 200) {
		boss2.SetTopLeft(boss2.GetLeft() + boss2.ax, boss2.GetTop() + boss2.ay);
	}
	else {
		boss2.set_timer(0);
		int x = rand() % 20 - 10;
		int y = rand() % 20 - 10;
		boss2.ax = x;
		boss2.ay = y;
	}

	if (boss2.GetLeft() < -300) {
		int x = rand() % 13;
		boss2.ax = x;
		boss2.SetTopLeft(boss2.GetLeft() + boss2.ax, boss2.GetTop() + boss2.ay);
	}
	else if (boss2.GetLeft() + boss2.GetWidth() > 1300) {
		int x = 0 - rand() % 13;
		boss2.ax = x;
		boss2.SetTopLeft(boss2.GetLeft() + boss2.ax, boss2.GetTop() + boss2.ay);
	}

	if (boss2.GetTop() < -300) {
		int y = rand() % 13;
		boss2.ay = y;
		boss2.SetTopLeft(boss2.GetLeft() + boss2.ax, boss2.GetTop() + boss2.ay);
	}
	else if (boss2.GetTop() + boss2.GetHeight() > 1300) {
		int y = 0 - rand() % 13;
		boss2.ay = y;
		boss2.SetTopLeft(boss2.GetLeft() + boss2.ax, boss2.GetTop() + boss2.ay);
	}
}




/////////////////////////////update data/////////////////

void CGamestageBoss2::set_share_obj_data(CMovingBitmap &tmp_background, CMovingBitmap &tmp_character,
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

void CGamestageBoss2::move_share_obj_data(CMovingBitmap &tmp_background, CMovingBitmap &tmp_character,
	CMovingBitmap &tmp_opera, CMovingBitmap &tmp_blood_bar, CMovingBitmap &tmp_energy_bar, vector <CMovingBitmap> &tmp_dart, vector<CMovingBitmap> &tmp_bullet) {

	tmp_background = background;
	tmp_character = character;
	tmp_opera = opera;
	tmp_blood_bar = blood_bar;
	tmp_energy_bar = energy_bar;
	tmp_dart = dart;
	tmp_bullet = bullet;
};

void CGamestageBoss2::gat_data() {

	background = *p_background;
	character = *p_character;
	opera = *p_opera;
	blood_bar = *p_blood_bar;
	energy_bar = *p_energy_bar;
	dart = *p_dart;
	bullet = *p_bullet;

};


void CGamestageBoss2::share_data() {

	*p_background = background;
	*p_character = character;
	*p_opera = opera;
	*p_blood_bar = blood_bar;
	*p_energy_bar = energy_bar;
	*p_dart = dart;
	*p_bullet = bullet;

};