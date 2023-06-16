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

void CGamestageBoss3::OnBeginState() {
	run = 1;
	timmer = 0;
	boss3.set_hp(5000);
	boss3.SetTopLeft(420, 500);
	boss3.set_center((boss3.GetLeft() + boss3.GetWidth() / 2), (boss3.GetTop() + boss3.GetHeight() / 2));
	boss3.set_timer(1500);
	boss3.ax = 0;
	boss3.ay = 0;

	for (int i = 0; i < 8; i++) {
		boss3_bullet[i].SetTopLeft(boss3.get_center_x() - 20, boss3.get_center_y() - 20);
		boss3_bullet[i].SetAnimation(5, false);
	}

	vector<int> x = { 5, 10, -2 };
	vector<int> y = { 3,  -2,   8 };

	int a = boss3.boss3_hit_x.size();
	int b = boss3.boss3_hit_y.size();

	for (int i = 0; i < 3; i++) {

		boss3_rocket[i].SetTopLeft(boss3.GetLeft() + boss3.GetWidth() / 2, boss3.GetTop());
		boss3.set_hit_x(x[i], i);
		boss3.set_hit_y(y[i], i);
	}
};

void CGamestageBoss3::OnInit() {

	boss3.LoadBitmapByString({ "Resources/boss3/f0.bmp", "Resources/boss3/f1.bmp", "Resources/boss3/f2.bmp", "Resources/boss3/f3.bmp" }, RGB(255, 255, 255));
	boss3.SetAnimation(150, false);
	boss3.set_hp(5000);
	boss3.set_hp_max(5000);
	boss3.SetTopLeft(420, 500);
	boss3.set_center((boss3.GetLeft() + boss3.GetWidth() / 2), (boss3.GetTop() + boss3.GetHeight() / 2));
	boss3.set_timer(1500);
	boss3.ax = 0;
	boss3.ay = 0;

	blood_bar_boss3.LoadBitmapByString({ "Resources/health_ui/boss1/health_ui_0.bmp", "Resources/health_ui/boss1/health_ui_1.bmp",
										 "Resources/health_ui/boss1/health_ui_2.bmp", "Resources/health_ui/boss1/health_ui_3.bmp",
										 "Resources/health_ui/boss1/health_ui_4.bmp" }, RGB(255, 255, 255));
	blood_bar_boss3.SetFrameIndexOfBitmap(blood_bar_boss3.GetFrameSizeOfBitmap() - 1);

	blood_boss3.LoadBitmapByString({ "Resources/ignore.bmp", "Resources/blood/bloodfx001_01.bmp",
								 "Resources/blood/bloodfx001_02.bmp", "Resources/blood/bloodfx001_03.bmp",
								 "Resources/blood/bloodfx001_04.bmp", "Resources/blood/bloodfx001_05.bmp",
								 "Resources/ignore.bmp" }, RGB(255, 255, 255));

	vector<string> boss3_bullet_bmp = { "Resources/boss3/boss3_bullet/00.bmp", "Resources/boss3/boss3_bullet/10.bmp" , "Resources/boss3/boss3_bullet/20.bmp" , "Resources/boss3/boss3_bullet/30.bmp" , "Resources/boss3/boss3_bullet/40.bmp" ,
		"Resources/boss3/boss3_bullet/50.bmp" , "Resources/boss3/boss3_bullet/60.bmp " , "Resources/boss3/boss3_bullet/70.bmp", "Resources/boss3/boss3_bullet/80.bmp", "Resources/boss3/boss3_bullet/90.bmp" };

	for (int i = 0; i < 8; i++) {
		boss3_bullet.push_back(CMovingBitmap());
		boss3_bullet[i].LoadBitmapByString(boss3_bullet_bmp, RGB(255, 255, 255));
		boss3_bullet[i].SetTopLeft(boss3.get_center_x() - 20, boss3.get_center_y() - 20);
		boss3_bullet[i].SetAnimation(5, false);
	}



	boss3_range.LoadBitmapByString({ "Resources/boss2/boss2_range.bmp" }, RGB(255, 255, 255));
	boss3_range.SetTopLeft(0, 0);
	boss3.SetTopLeft(boss3_range.GetLeft() + 243, boss3_range.GetTop() + 130);


	blood.LoadBitmapByString({ "Resources/ignore.bmp", "Resources/blood/bloodfx001_01.bmp",
					"Resources/blood/bloodfx001_02.bmp", "Resources/blood/bloodfx001_03.bmp",
					"Resources/blood/bloodfx001_04.bmp", "Resources/blood/bloodfx001_05.bmp",
					"Resources/ignore.bmp" }, RGB(255, 255, 255));
	blood.SetTopLeft(character.GetLeft() + character.GetWidth(), character.GetTop());

	blood_boss3.LoadBitmapByString({ "Resources/ignore.bmp", "Resources/blood/bloodfx001_01.bmp",
								 "Resources/blood/bloodfx001_02.bmp", "Resources/blood/bloodfx001_03.bmp",
								 "Resources/blood/bloodfx001_04.bmp", "Resources/blood/bloodfx001_05.bmp",
								 "Resources/ignore.bmp" }, RGB(255, 255, 255));

	vector<int> x = { 5, 10, -2 };
	vector<int> y = { 3,  -2,   8 };

	int a = boss3.boss3_hit_x.size();
	int b = boss3.boss3_hit_y.size();

	vector<string> ball_name = { "Resources/boss3/orange_ball.bmp", "Resources/boss3/purple_ball.bmp" , "Resources/boss3/brown_ball.bmp" };
	for (int i = 0; i < 3; i++) {
		boss3_rocket.push_back(CMovingBitmap());
		boss3_rocket[i].LoadBitmapByString({ ball_name[i] }, RGB(200, 191, 231));
		boss3_rocket[i].SetTopLeft(boss3.GetLeft() + boss3.GetWidth() / 2, boss3.GetTop());
		boss3.set_hit_x(x[i], i);
		boss3.set_hit_y(y[i], i);
	}

	jump.LoadBitmapByString({ "Resources/UI/jump.bmp" , "Resources/UI/jump_2.bmp" }, RGB(255, 255, 255));
	jump.SetTopLeft(770, 15);
}

void CGamestageBoss3::OnKeyDown(UINT, UINT, UINT) {};

void CGamestageBoss3::OnKeyUp(UINT, UINT, UINT) {};

void CGamestageBoss3::OnLButtonDown(UINT nFlags, CPoint point) {
	if (isSelect(nFlags, point, jump)) {
		boss3.set_hp(-1);
		run = 0;
	}
};

void CGamestageBoss3::OnLButtonUp(UINT nFlags, CPoint point) {};

void CGamestageBoss3::OnMouseMove(UINT nFlags, CPoint point) {
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


void CGamestageBoss3::OnRButtonDown(UINT nFlags, CPoint point) {};

void CGamestageBoss3::OnRButtonUp(UINT nFlags, CPoint point) {};

void CGamestageBoss3::OnMove() {
	get_data();
	timmer++;


	if (timmer > 150) {


		boss3_move();
		boss3_rocket_move();

		if (timmer % 2 == 0) {
			boss3_bullet_move();
		}

		if (timmer > 10000) {
			timmer = 151;
		}
		isVector();
	}
	else {
		boss3.SetTopLeft(420, 500);

	}

	for (int i = 0; i < (int)bricks.size(); i++) {
		int j = bricks[i].ram_n;
		bricks_move(bricks, bricks[i].stdx + h[j], bricks[i].stdy + k[j], c[j], x_move[j], i);
		bricks_erase(bricks);
	}

	blood.SetTopLeft(character.GetLeft() + character.GetWidth(), character.GetTop());
	blood_bar_progress(blood_bar_boss3, boss3);

	lightning_move(lightning);

	background_move();
	dart_all(200);
	bullet_move(bullet);
	bullet_erase(bullet);


	share_data();
};

void CGamestageBoss3::OnShow() {
	get_data();
	background.ShowBitmap();

	boss3.ShowBitmap();
	blood_boss3.ShowBitmap();
	blood_boss3.SetTopLeft(boss3.GetLeft() + boss3.GetWidth() / 2, boss3.GetTop());

	for (int i = 0; i < (int)dart.size(); i++) {
		dart[i].ShowBitmap();
	}

	for (int i = 0; i < (int)bullet.size(); i++) {
		bullet[i].ShowBitmap();
	}

	for (int i = 0; i < (int)boss3_bullet.size(); i++) {
		boss3_bullet[i].ShowBitmap();
	}

	for (int i = 0; i < (int)boss3_rocket.size(); i++) {
		boss3_rocket[i].ShowBitmap();
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

	blood_bar_boss3.ShowBitmap();
	blood_bar_boss3.SetTopLeft(boss3.GetLeft() + 40, boss3.GetTop() + 160 + 10);

	opera.ShowBitmap();
	boss3_range.ShowBitmap();

	blood_bar.ShowBitmap();
	energy_bar.ShowBitmap();

	jump.ShowBitmap();

	show_text();

	share_data();


};

void CGamestageBoss3::show_text() {

	CDC *pdc = CDDraw::GetBackCDC();

	CTextDraw::ChangeFontLog(pdc, 15, "monogram", RGB(255, 255, 255), 80);
	CTextDraw::Print(pdc, blood_bar_boss3.GetLeft() + 30, blood_bar_boss3.GetTop() + 10 + 20, to_string(boss3.get_hp()));

	if (timmer < 100) {
		CTextDraw::ChangeFontLog(pdc, 65, "monogram", RGB(255, 255, 255), 80);
		CTextDraw::Print(pdc, 290, 200, "Boss3 Assault!!");
	}

	CDDraw::ReleaseBackCDC();

}


void CGamestageBoss3::background_move() {
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

	if (character.GetLeft() < boss3_range.GetLeft()) { //left
		character.SetTopLeft(boss3_range.GetLeft(), character.GetTop());
	}
	if (character.GetTop() < boss3_range.GetTop()) { //top
		character.SetTopLeft(character.GetLeft(), boss3_range.GetTop());
	}
	if (character.GetLeft() + character.GetWidth() > (boss3_range.GetLeft() + boss3_range.GetWidth())) { //right
		character.SetTopLeft(boss3_range.GetLeft() + boss3_range.GetWidth() - character.GetWidth(), character.GetTop());
	}
	if ((character.GetTop() + character.GetHeight()) > (boss3_range.GetTop() + boss3_range.GetHeight())) { //bottom
		character.SetTopLeft(character.GetLeft(), boss3_range.GetTop() + boss3_range.GetHeight() - character.GetHeight());
	}

	character.set_center((character.GetLeft() + 10), (character.GetTop() + 10));
}

void CGamestageBoss3::bullet_move(vector<CMovingBitmap> &item) {
	for (int i = 0; i < (int)item.size(); i++) {
		item[i].SetTopLeft(item[i].GetLeft(), item[i].GetTop() - 20);
		if (character.IsOverlap(item[i], boss3) && timmer > 150) {
			boss3.add_sub_hp(-15);
			blood_boss3.SetAnimation(50, false);
			blood_boss3.ShowBitmap();
			CAudio::Instance()->Play(AUDIO_Attack, false);
		}
		else {
			blood_boss3.SetAnimation(50, true);
		}
	}
}

void CGamestageBoss3::born_bullet(vector<CMovingBitmap> &item, vector<string> str, vector<int>rgb) {
	int tail = item.size();
	if (item[tail - 1].GetTop() < 0) {
		item.push_back(CMovingBitmap());
		item[tail].LoadBitmapByString(str, RGB(rgb[0], rgb[1], rgb[2]));
		item[tail].SetTopLeft(character.GetLeft() + 10, character.GetTop());
	}
}

void CGamestageBoss3::bullet_erase(vector<CMovingBitmap> &item) {
	if (item[0].GetTop() < 0) {
		//item.erase(item.begin());
		item[0].SetTopLeft(character.GetLeft() + 10, character.GetTop());
	}
}

void CGamestageBoss3::dart_all(int setR) {
	for (int i = 0; i < (int)dart.size(); i++) {
		dart[i].add_timer(1);
		dart_move(dart[i], (dart[i].timer % 360) * 5, setR);
		if (dart[i].get_timer() > 360) {
			dart[i].set_timer(0);
			blood_boss3.SetAnimation(50, true);
		}
		if (character.IsOverlap(dart[i], boss3) && timmer > 150) {
			boss3.add_sub_hp(-5);
			CAudio::Instance()->Play(AUDIO_Attack, false);
			blood_boss3.SetAnimation(50, false);
			blood_boss3.ShowBitmap();
		}
	}
}

void CGamestageBoss3::dart_move(CMovingBitmap &item, int i, int setR) {
	int r = setR;;
	int px = character.get_center_x() + (int)(r *cos(i * 3.14 / 180));
	int py = character.get_center_y() + (int)(r *sin(i * 3.14 / 180));
	item.SetTopLeft(px, py);
}

void CGamestageBoss3::blood_bar_progress(CMovingBitmap &blood_bar, CMovingBitmap &item_blood) {
	if (item_blood.get_hp() >= item_blood.get_hp_max()) {
		blood_bar.SetFrameIndexOfBitmap(blood_bar.GetFrameSizeOfBitmap() - 1);
	}
	else if (item_blood.get_hp() > 0) {
		blood_bar.SetFrameIndexOfBitmap(((item_blood.get_hp()) / (item_blood.get_hp_max() / 5)));
	}
}


void CGamestageBoss3::lightning_move(vector<CMovingBitmap> &item) {


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
		if (character.IsOverlap(lightning[i], boss3) && timmer > 150) {
			boss3.add_sub_hp(-5);
			blood_boss3.SetAnimation(50, false);
			blood_boss3.ShowBitmap();
			CAudio::Instance()->Play(AUDIO_Attack, false);
		}
		else {
			blood_boss3.SetAnimation(50, true);
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


void CGamestageBoss3::bricks_move(vector<CMovingBitmap> &item, int h, int k, int c, int x_move, int i) {
	int x = item[i].GetLeft() + x_move;
	int y = (x - h) * (x - h) / (4 * c) + k;
	item[i].SetTopLeft(x, y);
	if (character.IsOverlap(item[i], boss3) && timmer > 150) {
		boss3.add_sub_hp(-10);
		blood_boss3.SetAnimation(50, false);
		blood_boss3.ShowBitmap();
		CAudio::Instance()->Play(AUDIO_Attack, false);
	}
	else {
		blood_boss3.SetAnimation(50, true);
	}

}


void CGamestageBoss3::bricks_erase(vector<CMovingBitmap> &item) {

	for (int i = 0; i < (int)item.size(); i++) {
		if (item[i].GetTop() + 70 > 1065) {
			item[i].SetTopLeft(character.GetLeft() + 10, character.GetTop());
			item[i].stdx = character.GetLeft();
			bricks[i].stdy = character.GetTop();
			item[i].ram_n = (rand() + timmer) % 4;
		}
	}

}


bool CGamestageBoss3::isSelect(UINT nFlags, CPoint point, CMovingBitmap &item) {
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

void CGamestageBoss3::boss3_move() {
	boss3.add_timer(1);
	if (boss3.get_timer() < 300) {
		boss3.SetTopLeft(boss3.GetLeft() + boss3.ax, boss3.GetTop() + boss3.ay);
	}
	else {
		boss3.set_timer(0);
		int x = rand() % 20 - 10;
		int y = rand() % 20 - 10;
		boss3.ax = x;
		boss3.ay = y;
	}

	if (boss3.GetLeft() < 0) {
		int x = rand() % 13;
		boss3.ax = x;
		boss3.SetTopLeft(boss3.GetLeft() + boss3.ax, boss3.GetTop() + boss3.ay);
	}
	else if (boss3.GetLeft() + boss3.GetWidth() > 1065) {
		int x = 0 - rand() % 13;
		boss3.ax = x;
		boss3.SetTopLeft(boss3.GetLeft() + boss3.ax, boss3.GetTop() + boss3.ay);
	}

	if (boss3.GetTop() < 0) {
		int y = rand() % 13;
		boss3.ay = y;
		boss3.SetTopLeft(boss3.GetLeft() + boss3.ax, boss3.GetTop() + boss3.ay);
	}
	else if (boss3.GetTop() + boss3.GetHeight() > 1065) {
		int y = 0 - rand() % 13;
		boss3.ay = y;
		boss3.SetTopLeft(boss3.GetLeft() + boss3.ax, boss3.GetTop() + boss3.ay);
	}

	boss3.set_center((boss3.GetLeft() + boss3.GetWidth() / 2), (boss3.GetTop() + boss3.GetHeight() / 2));
}

void CGamestageBoss3::boss3_bullet_move() {

	double v = 1.0;
	int flag = 0;
	for (int i = 0; i < (int)boss3_bullet.size(); i++) {
		int x0 = boss3_bullet[i].GetLeft();
		int y0 = boss3_bullet[i].GetTop();
		int d = 10;
		int t = 1;
		double x = x0 + d * cos(theta[i]) + v * t*cos(theta[i]);
		double y = y0 + d * sin(theta[i]) + v * t*sin(theta[i]); //chage to calculate one time in class initing ,neverthless it will waste too much runing time
		boss3_bullet[i].SetTopLeft((int)(x), (int)(y));

		if (boss3.IsOverlap(boss3_bullet[i], character)) {
			character.add_sub_hp(-15);
			blood.SetAnimation(50, false);
			blood.ShowBitmap();
			CAudio::Instance()->Play(AUDIO_Attack, false);
		}
		else {
			blood.SetAnimation(50, true);
		}

		if (boss3_bullet[i].GetTop() < 0) { //up
			flag++;
		}
		else if (boss3_bullet[i].GetLeft() > 4000) { //right
			flag++;
		}
		else if (boss3_bullet[i].GetTop() > 4000) { //down
			flag++;
		}
		else if (boss3_bullet[i].GetLeft() < 0) { //left
			flag++;
		}
	}


	if (flag == boss3_bullet.size()) {

		for (int i = 0; i < 8; i++) {

			boss3_bullet[i].SetTopLeft(boss3.get_center_x(), boss3.get_center_y());

		}
	}

}


void CGamestageBoss3::boss3_rocket_move() {
	for (int i = 0; i < (int)boss3_rocket.size(); i++) {
		int x = boss3.get_hit_x(i);
		int y = boss3.get_hit_y(i);
		boss3_rocket[i].SetTopLeft(boss3_rocket[i].GetLeft() + x, boss3_rocket[i].GetTop() + y);
		if (boss3_rocket[i].GetLeft() < boss3_range.GetLeft()) {
			boss3.set_hit_x(abs(x), i);
		}
		else if (boss3_rocket[i].GetLeft() + boss3_rocket[i].GetWidth() > boss3_range.GetLeft() + boss3_range.GetWidth()) {
			boss3.set_hit_x(-abs(x), i);
		}
		else if (boss3_rocket[i].GetTop() < boss3_range.GetTop()) {
			boss3.set_hit_y(abs(y), i);
		}
		else if (boss3_rocket[i].GetTop() + 50 > boss3_range.GetTop() + 1040) {
			boss3.set_hit_y(-abs(y), i);
		}

		if (boss3.IsOverlap(boss3_rocket[i], character)) {
			character.add_sub_hp(-15);
			blood.SetAnimation(50, false);
			blood.ShowBitmap();
		}
		else {
			blood.SetAnimation(50, true);
		}
	}
}

int CGamestageBoss3::isVector() {
	if (boss3.get_hp() <= 0) {
		run = 0;
		return 1;
	}
	else {
		return 0;
	}
}

/////////////////////////////update data/////////////////

void CGamestageBoss3::set_share_obj_data(CMovingBitmap &tmp_background, CMovingBitmap &tmp_character, CMovingBitmap &tmp_opera, CMovingBitmap &tmp_blood_bar, CMovingBitmap &tmp_energy_bar,
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

void CGamestageBoss3::move_share_obj_data(CMovingBitmap &tmp_background, CMovingBitmap &tmp_character,
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


void CGamestageBoss3::get_data() {

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

void CGamestageBoss3::share_data() {

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