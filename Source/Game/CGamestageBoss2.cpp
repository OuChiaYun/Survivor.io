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

void CGamestageBoss2::OnBeginState() {
	run = 1;
	timmer = 0;
	boss2.set_hp(5000);
	boss2.set_hp_max(5000);
	boss2.SetTopLeft(420, 500);
	boss2.set_center((boss2.GetLeft() + boss2.GetWidth() / 2), (boss2.GetTop() + boss2.GetHeight() / 2));
	boss2.set_timer(1500);
	boss2.ax = 0;
	boss2.ay = 0;

	for (int i = 0; i < 8; i++) {
		boss2_bullet[i].SetTopLeft(boss2.get_center_x() - 20, boss2.get_center_y() - 20);
		boss2_bullet[i].SetAnimation(5, false);
	}

};

void CGamestageBoss2::OnInit() {

	boss2.LoadBitmapByString({ "Resources/boss2/boss2_f0.bmp", "Resources/boss2/boss2_f1.bmp", "Resources/boss2/boss2_f2.bmp", "Resources/boss2/boss2_f3.bmp" }, RGB(255, 255, 255));
	boss2.SetAnimation(150, false);
	boss2.set_hp(5000);
	boss2.set_hp_max(5000);
	boss2.SetTopLeft(420, 500);
	boss2.set_center((boss2.GetLeft() + boss2.GetWidth() / 2), (boss2.GetTop() + boss2.GetHeight() / 2));
	boss2.set_timer(1500);
	boss2.ax = 0;
	boss2.ay = 0;

	blood_bar_boss2.LoadBitmapByString({ "Resources/health_ui/boss1/health_ui_0.bmp", "Resources/health_ui/boss1/health_ui_1.bmp",
										 "Resources/health_ui/boss1/health_ui_2.bmp", "Resources/health_ui/boss1/health_ui_3.bmp",
										 "Resources/health_ui/boss1/health_ui_4.bmp" }, RGB(255, 255, 255));
	blood_bar_boss2.SetFrameIndexOfBitmap(blood_bar_boss2.GetFrameSizeOfBitmap() - 1);

	blood_boss2.LoadBitmapByString({ "Resources/ignore.bmp", "Resources/blood/bloodfx001_01.bmp",
								 "Resources/blood/bloodfx001_02.bmp", "Resources/blood/bloodfx001_03.bmp",
								 "Resources/blood/bloodfx001_04.bmp", "Resources/blood/bloodfx001_05.bmp",
								 "Resources/ignore.bmp" }, RGB(255, 255, 255));

	vector<string> boss2_bullet_bmp = { "Resources/boss2/boss2_b1.bmp ","Resources/boss2/boss2_b2.bmp " ,"Resources/boss2/boss2_b3.bmp" ,"Resources/boss2/boss2_b4.bmp" ,"Resources/boss2/boss2_b5.bmp" ,"Resources/boss2/boss2_b6.bmp " ,"Resources/boss2/boss2_b7.bmp " ,"Resources/boss2/boss2_b8.bmp " };

	for (int i = 0; i < 8; i++) {
		boss2_bullet.push_back(CMovingBitmap());
		boss2_bullet[i].LoadBitmapByString(boss2_bullet_bmp, RGB(140, 133, 90));
		boss2_bullet[i].SetTopLeft(boss2.get_center_x() - 20, boss2.get_center_y() - 20);
		boss2_bullet[i].SetAnimation(5, false);
	}

	boss2_range.LoadBitmapByString({ "Resources/boss2/boss2_range.bmp" }, RGB(255, 255, 255));
	boss2_range.SetTopLeft(0, 0);
	boss2.SetTopLeft(boss2_range.GetLeft() + 243, boss2_range.GetTop() + 130);

	blood.LoadBitmapByString({ "Resources/ignore.bmp", "Resources/blood/bloodfx001_01.bmp",
					"Resources/blood/bloodfx001_02.bmp", "Resources/blood/bloodfx001_03.bmp",
					"Resources/blood/bloodfx001_04.bmp", "Resources/blood/bloodfx001_05.bmp",
					"Resources/ignore.bmp" }, RGB(255, 255, 255));
	blood.SetTopLeft(character.GetLeft() + character.GetWidth(), character.GetTop());

	blood_boss2.LoadBitmapByString({ "Resources/ignore.bmp", "Resources/blood/bloodfx001_01.bmp",
								 "Resources/blood/bloodfx001_02.bmp", "Resources/blood/bloodfx001_03.bmp",
								 "Resources/blood/bloodfx001_04.bmp", "Resources/blood/bloodfx001_05.bmp",
								 "Resources/ignore.bmp" }, RGB(255, 255, 255));

	jump.LoadBitmapByString({ "Resources/UI/jump.bmp" , "Resources/UI/jump_2.bmp" }, RGB(255, 255, 255));
	jump.SetTopLeft(770, 15);
}

void CGamestageBoss2::OnKeyDown(UINT, UINT, UINT) {};

void CGamestageBoss2::OnKeyUp(UINT, UINT, UINT) {};

void CGamestageBoss2::OnLButtonDown(UINT nFlags, CPoint point) {
	if (isSelect(nFlags, point, jump)) {
		boss2.set_hp(-1);
		run = 0;
	}
};

void CGamestageBoss2::OnLButtonUp(UINT nFlags, CPoint point) {};

void CGamestageBoss2::OnMouseMove(UINT nFlags, CPoint point) {
	get_data();

	if (isSelect(true, point, jump)) {

		jump.SetFrameIndexOfBitmap(1);
	}
	else {
		jump.SetFrameIndexOfBitmap(0);
	}
	if (isSelect(true, point, jump)) {

		jump.SetFrameIndexOfBitmap(1);
	}
	else {
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
	share_data();

};


void CGamestageBoss2::OnRButtonDown(UINT nFlags, CPoint point) {};

void CGamestageBoss2::OnRButtonUp(UINT nFlags, CPoint point) {};

void CGamestageBoss2::OnMove() {
	get_data();
	timmer++;


	if (timmer > 150) {
		

		boss2_move();

		if (timmer % 2 == 0) {
			boss2_bullet_move();
		}

		if (timmer > 10000) {
			timmer = 151;
		}
	}
	else {
		boss2.SetTopLeft(420, 500);

	}


	for (int i = 0; i < (int)bricks.size(); i++) {
		int j = bricks[i].ram_n;
		bricks_move(bricks, bricks[i].stdx + h[j], bricks[i].stdy + k[j], c[j], x_move[j], i);
		bricks_erase(bricks);
	}

	blood.SetTopLeft(character.GetLeft() + character.GetWidth(), character.GetTop());
	blood_bar_progress(blood_bar_boss2, boss2);

	lightning_move(lightning);

	background_move();
	dart_all(200);
	bullet_move(bullet);
	//born_bullet(bullet, { "Resources/weapon/bullet.bmp" }, { 255, 255, 255 });
	bullet_erase(bullet);

	if (boss2.get_hp() <= 0) {
		run = 0;
	}


	share_data();
};

void CGamestageBoss2::OnShow() {
	get_data();
	background.ShowBitmap();

	boss2.ShowBitmap();
	blood_boss2.ShowBitmap();
	blood_boss2.SetTopLeft(boss2.GetLeft() + boss2.GetWidth() / 2, boss2.GetTop());

	for (int i = 0; i < (int)dart.size(); i++) {
		dart[i].ShowBitmap();
	}

	for (int i = 0; i < (int)bullet.size(); i++) {
		bullet[i].ShowBitmap();
	}

	for (int i = 0; i < (int)boss2_bullet.size(); i++) {
		boss2_bullet[i].ShowBitmap();

	}

	for (int j = 0; j < (int)bricks.size(); j++) {
		bricks[j].ShowBitmap();
	}
	for (int i = 0; i < (int)lightning.size(); i++) {
		lightning[i].ShowBitmap();
	}

	if (character.GetFrameIndexOfBitmap() >= character.limit_frame_end) {
		character.SetFrameIndexOfBitmap(character.limit_frame_start);
	}
	character.ShowBitmap();

	blood.SetTopLeft((character.GetLeft() + character.GetWidth() / 2), character.GetTop());
	blood.ShowBitmap();

	blood_bar_boss2.ShowBitmap();
	blood_bar_boss2.SetTopLeft(boss2.GetLeft() + 40, boss2.GetTop() + 160 + 10);

	opera.ShowBitmap();
	boss2_range.ShowBitmap();

	blood_bar.ShowBitmap();
	energy_bar.ShowBitmap();


	jump.ShowBitmap();
	show_text();
	share_data();


};

void CGamestageBoss2::show_text() {

	CDC *pdc = CDDraw::GetBackCDC();

	CTextDraw::ChangeFontLog(pdc, 15, "monogram", RGB(255, 255, 255), 80);
	CTextDraw::Print(pdc, blood_bar_boss2.GetLeft() + 30, blood_bar_boss2.GetTop() + 10 + 20, to_string(boss2.get_hp()));

	if (timmer < 100) {
		CTextDraw::ChangeFontLog(pdc, 60, "monogram", RGB(255, 255, 255), 80);
		CTextDraw::Print(pdc, 300, 210, "Boss2 Assault!!");
	}

	CDDraw::ReleaseBackCDC();
}


void CGamestageBoss2::background_move() {
	int ax = 0;
	int ay = 0;

	if (opera.center_x < 491) {
		ax = -5;
	}
	else if (opera.center_x > 491) {
		ax = 5;
	}

	if (opera.center_y < 736) {
		ay = -5;
	}
	else if (opera.center_y > 736) {
		ay = 5;
	}

	character.SetTopLeft(character.GetLeft() + ax, character.GetTop() + ay);

	if (character.GetLeft() < boss2_range.GetLeft()) { //left
		character.SetTopLeft(boss2_range.GetLeft(), character.GetTop());
	}
	if (character.GetTop() < boss2_range.GetTop()) { //top
		character.SetTopLeft(character.GetLeft(), boss2_range.GetTop());
	}
	if (character.GetLeft() + character.GetWidth() > (boss2_range.GetLeft() + boss2_range.GetWidth())) { //right
		character.SetTopLeft(boss2_range.GetLeft() + boss2_range.GetWidth() - character.GetWidth(), character.GetTop());
	}
	if ((character.GetTop() + character.GetHeight()) > (boss2_range.GetTop() + boss2_range.GetHeight())) { //bottom
		character.SetTopLeft(character.GetLeft(), boss2_range.GetTop() + boss2_range.GetHeight() - character.GetHeight());
	}

	character.set_center((character.GetLeft() + 10), (character.GetTop() + 10));
}

void CGamestageBoss2::bullet_move(vector<CMovingBitmap> &item) {
	for (int i = 0; i < (int)item.size(); i++) {
		item[i].SetTopLeft(item[i].GetLeft(), item[i].GetTop() - 20);
		if (character.IsOverlap(item[i], boss2) && timmer>150) {
			boss2.add_sub_hp(-15);
			blood_boss2.SetAnimation(50, false);
			blood_boss2.ShowBitmap();
			CAudio::Instance()->Play(AUDIO_Attack, false);
		}
		else {
			blood_boss2.SetAnimation(50, true);
		}
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
		//item.erase(item.begin());
		item[0].SetTopLeft(character.GetLeft() + 10, character.GetTop());
	}
}

void CGamestageBoss2::dart_all(int setR) {
	for (int i = 0; i < (int)dart.size(); i++) {
		dart[i].add_timer(1);
		dart_move(dart[i], (dart[i].timer % 360) * 5, setR);
		if (dart[i].get_timer() > 360) {
			dart[i].set_timer(0);
			blood_boss2.SetAnimation(50, true);
		}
		if (character.IsOverlap(dart[i], boss2)&&timmer > 150) {
			boss2.add_sub_hp(-5);
			CAudio::Instance()->Play(AUDIO_Attack, false);
			blood_boss2.SetAnimation(50, false);
			blood_boss2.ShowBitmap();
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
	if (item_blood.get_hp() >= item_blood.get_hp_max()) {
		blood_bar.SetFrameIndexOfBitmap(blood_bar.GetFrameSizeOfBitmap() - 1);
	}
	else if (item_blood.get_hp() > 0) {
		blood_bar.SetFrameIndexOfBitmap(((item_blood.get_hp()) / (item_blood.get_hp_max() / 5)));
	}
}


void CGamestageBoss2::lightning_move(vector<CMovingBitmap> &item) {


	int flag = 0;
	int f[100] = { 0,0,0,0, 0,0,0,0 };
	for (int i = 0; i < (int)item.size(); i++) {

		if ((lightning[i].GetLeft() <= (lightning[i].stdx - 300)) || (lightning[i].GetLeft() + 105 >= (lightning[i].stdx + 300))) {
			lightning[i].ax *= -1;
		}
		if (lightning[i].GetTop() < (lightning[i].stdy - 1065) || lightning[i].GetTop() > (lightning[i].stdy + 1065)) {
			flag++;
			f[i] = 1;
		}

		lightning[i].SetTopLeft(lightning[i].GetLeft() + lightning[i].ax, lightning[i].GetTop() + lightning[i].ay);
		if (character.IsOverlap(lightning[i], boss2)&& timmer > 150) {
			boss2.add_sub_hp(-5);
			blood_boss2.SetAnimation(50, false);
			blood_boss2.ShowBitmap();
			CAudio::Instance()->Play(AUDIO_Attack, false);
		}
		else {
			blood_boss2.SetAnimation(50, true);
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


void CGamestageBoss2::bricks_move(vector<CMovingBitmap> &item, int h, int k, int c, int x_move, int i) {
	int x = item[i].GetLeft() + x_move;
	int y = (x - h) * (x - h) / (4 * c) + k;
	item[i].SetTopLeft(x, y);
	if (character.IsOverlap(item[i], boss2)&& timmer > 150) {
		boss2.add_sub_hp(-10);
		blood_boss2.SetAnimation(50, false);
		blood_boss2.ShowBitmap();
		CAudio::Instance()->Play(AUDIO_Attack, false);
	}
	else {
		blood_boss2.SetAnimation(50, true);
	}

}


void CGamestageBoss2::bricks_erase(vector<CMovingBitmap> &item) {

	for (int i = 0; i < (int)item.size(); i++) {
		if (item[i].GetTop() + 70 > 1065) {
			item[i].SetTopLeft(character.GetLeft() + 10, character.GetTop());
			item[i].stdx = character.GetLeft();
			bricks[i].stdy = character.GetTop();
			item[i].ram_n = (rand() + timmer) % 4;
		}
	}

}

bool CGamestageBoss2::isSelect(UINT nFlags, CPoint point, CMovingBitmap &item) {
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

///////////////////////////////////////////////////////

void CGamestageBoss2::boss2_move() {
	boss2.add_timer(1);
	if (boss2.get_timer() < 300) {
		boss2.SetTopLeft(boss2.GetLeft() + boss2.ax, boss2.GetTop() + boss2.ay);
	}
	else {
		boss2.set_timer(0);
		int x = rand() % 20 - 10;
		int y = rand() % 20 - 10;
		boss2.ax = x;
		boss2.ay = y;
	}

	if (boss2.GetLeft() < 0) {
		int x = rand() % 13;
		boss2.ax = x;
		boss2.SetTopLeft(boss2.GetLeft() + boss2.ax, boss2.GetTop() + boss2.ay);
	}
	else if (boss2.GetLeft() + boss2.GetWidth() > 1065) {
		int x = 0 - rand() % 13;
		boss2.ax = x;
		boss2.SetTopLeft(boss2.GetLeft() + boss2.ax, boss2.GetTop() + boss2.ay);
	}

	if (boss2.GetTop() < 0) {
		int y = rand() % 13;
		boss2.ay = y;
		boss2.SetTopLeft(boss2.GetLeft() + boss2.ax, boss2.GetTop() + boss2.ay);
	}
	else if (boss2.GetTop() + boss2.GetHeight() > 1065) {
		int y = 0 - rand() % 13;
		boss2.ay = y;
		boss2.SetTopLeft(boss2.GetLeft() + boss2.ax, boss2.GetTop() + boss2.ay);
	}

	boss2.set_center((boss2.GetLeft() + boss2.GetWidth() / 2), (boss2.GetTop() + boss2.GetHeight() / 2));
}

void CGamestageBoss2::boss2_bullet_move() {

	double v = 1.0;
	int flag = 0;
	for (int i = 0; i < (int)boss2_bullet.size(); i++) {
		int x0 = boss2_bullet[i].GetLeft();
		int y0 = boss2_bullet[i].GetTop();
		int d = 10;
		int t = 1;
		double x = x0 + d * cos(theta[i]) + v * t*cos(theta[i]);
		double y = y0 + d * sin(theta[i]) + v * t*sin(theta[i]); //chage to calculate one time in class initing ,neverthless it will waste too much runing time
		boss2_bullet[i].SetTopLeft((int)(x), (int)(y));

		if (boss2.IsOverlap(boss2_bullet[i], character)) {
			character.add_sub_hp(-15);
			blood.SetAnimation(50, false);
			blood.ShowBitmap();
			CAudio::Instance()->Play(AUDIO_Attack, false);
		}
		else {
			blood.SetAnimation(50, true);
		}

		if (boss2_bullet[i].GetTop() < 0) { //up
			flag++;
		}
		else if (boss2_bullet[i].GetLeft() > 1065) { //right
			flag++;
		}
		else if (boss2_bullet[i].GetTop() > 1065) { //down
			flag++;
		}
		else if (boss2_bullet[i].GetLeft() < 0) { //left
			flag++;
		}
	}

	if (flag == boss2_bullet.size()) {

		for (int i = 0; i < 8; i++) {
			boss2_bullet[i].SetTopLeft(boss2.get_center_x(), boss2.get_center_y());
		}
	}
}

int CGamestageBoss2::isVector() {
	if (boss2.get_hp() <= 0) {
		return 1;
	}
	else {
		return 0;
	}
}


/////////////////////////////update data/////////////////

void CGamestageBoss2::set_share_obj_data(CMovingBitmap &tmp_background, CMovingBitmap &tmp_character, CMovingBitmap &tmp_opera, CMovingBitmap &tmp_blood_bar, CMovingBitmap &tmp_energy_bar,
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

void CGamestageBoss2::move_share_obj_data(CMovingBitmap &tmp_background, CMovingBitmap &tmp_character,
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


void CGamestageBoss2::get_data() {

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


void CGamestageBoss2::share_data() {

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