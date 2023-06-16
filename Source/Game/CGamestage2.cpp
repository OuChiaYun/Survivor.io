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

void CGamestage2::OnBeginState() {
	run = 0;
	select = 0;
	magnet_once = 0;
	magnet_trigger = 0;
	magnet[0].SetFrameIndexOfBitmap(0);

	bomb_trigger = 0;
	bomb_timer = 0;
	bomb.SetFrameIndexOfBitmap(0);
	bomb.set_limit_start_end(0, 0);
	bomb.SetTopLeft(1000, 1000);

	dead_monster = 0;
	int min = -1450;
	int max = 1450;

	for (int i = int(monster.size()); i < 35; i++) {

		monster.push_back(monster_vanish[0]);
		monster[monster.size() - 1].SetFrameIndexOfBitmap(0);
		monster[monster.size() - 1].SetAnimation(50, false);
		monster[monster.size() - 1].set_hp(6);
		monster_reset(monster[monster.size() - 1]);
		monster_vanish.erase(monster_vanish.begin());
	}

	for (int i = 0; i<int(monster.size()); i++) {

		int x = rand() % (max - min + 1) + min;
		int y = rand() % (max - min + 1) + min;
		monster[i].SetTopLeft(x, y);
		monster[i].set_center(x + 45, y + 57);
	}

	for (int i = int(big_monster.size()); i < 6; i++) {

		big_monster.push_back(big_monster_vanish[0]);
		big_monster[big_monster.size() - 1].SetFrameIndexOfBitmap(0);
		big_monster[big_monster.size() - 1].SetAnimation(95, false);
		big_monster[big_monster.size() - 1].set_hp(40);
		big_monster[big_monster.size() - 1].set_limit_start_end(0, 3);
		big_monster_vanish.erase(big_monster_vanish.begin());
	}

	for (int i = 0; i<int(big_monster.size()); i++) {

		int x = rand() % (max - min + 1) + min;
		int y = rand() % (max - min + 1) + min;
		big_monster[i].SetTopLeft(x, y);
		big_monster[i].set_center(x + 45, y + 57);
	}

	for (int i = int(big_monster.size()); i < 6; i++) {

		big_monster.push_back(big_monster_vanish[0]);
		big_monster[big_monster.size() - 1].SetFrameIndexOfBitmap(0);
		big_monster[big_monster.size() - 1].SetAnimation(95, false);
		big_monster[big_monster.size() - 1].set_hp(40);
		big_monster[big_monster.size() - 1].set_limit_start_end(0, 3);
		big_monster_vanish.erase(big_monster_vanish.begin());
	}

	for (int i = 0; i<int(big_monster.size()); i++) {

		int x = rand() % (max - min + 1) + min;
		int y = rand() % (max - min + 1) + min;
		big_monster[i].SetTopLeft(x, y);
		big_monster[i].set_center(x + 45, y + 57);
	}

	for (int i = int(fast_monster.size()); i < 6; i++) {
		fast_monster.push_back(fast_monster_vanish[0]);
		fast_monster[fast_monster.size() - 1].SetFrameIndexOfBitmap(0);
		fast_monster[fast_monster.size() - 1].SetAnimation(95, false);
		fast_monster[fast_monster.size() - 1].set_hp(8);
		fast_monster[fast_monster.size() - 1].set_limit_start_end(0, 5);
		fast_monster[fast_monster.size() - 1].ay = 12;
		fast_monster[fast_monster.size() - 1].ax = 12;
		fast_monster[fast_monster.size() - 1].set_end = 11;
		fast_monster_vanish.erase(fast_monster_vanish.begin());
	}

	for (int i = 0; i<int(fast_monster.size()); i++) {

		int x = rand() % (max - min + 1) + min;
		int y = rand() % (max - min + 1) + min;
		fast_monster[i].SetTopLeft(x, y);
		fast_monster[i].set_center(x + 45, y + 57);
		fast_monster[i].set_center(x + 45, y + 57);
	}

	vector<CMovingBitmap>().swap(energy);
	max = 2000;
	for (int i = 0; i < 100; i++) {
		random_born_item(energy, { "Resources/gem/gem1.bmp", "Resources/gem/gem2.bmp",
								   "Resources/gem/gem3.bmp","Resources/gem/gem4.bmp","Resources/gem/gem5.bmp" }, { 200, 191, 231 });
		energy[i].SetAnimation(100, false);
	}
};

void CGamestage2::OnInit() {


	for (int i = 0; i < 100; i++) {
		random_born_item(energy, { "Resources/gem/gem1.bmp", "Resources/gem/gem2.bmp",
								   "Resources/gem/gem3.bmp","Resources/gem/gem4.bmp","Resources/gem/gem5.bmp" }, { 200, 191, 231 });
		energy[i].SetAnimation(100, false);
	}

	for (int i = 0; i < 35; i++) {
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
		monster[i].set_end = 30;
	}

	for (int i = 0; i < 6; i++) {
		random_born_big_monster(big_monster, { "Resources/monster/big_m0.bmp","Resources/monster/big_m1.bmp" ,"Resources/monster/big_m2.bmp" ,"Resources/monster/big_m3.bmp",
											"Resources/monster/big_m4.bmp","Resources/monster/big_m5.bmp" ,"Resources/monster/big_m6.bmp" ,"Resources/monster/big_m7.bmp" },
			big_monster_vanish, { "Resources/monster/big_e0.bmp","Resources/monster/big_e1.bmp","Resources/monster/big_e2.bmp" ,"Resources/monster/big_e3.bmp",
								  "Resources/monster/big_e4.bmp","Resources/monster/big_e5.bmp","Resources/monster/big_e6.bmp" ,"Resources/monster/big_e7.bmp",
								  "Resources/monster/big_e8.bmp","Resources/monster/big_e9.bmp","Resources/monster/m17.bmp" }, { 255,255,255 }, { 255, 255, 255 });  //255
		big_monster[i].SetAnimation(100, false);
		big_monster[i].set_hp(40);
		big_monster[i].set_end = 8;

		big_monster_blood.push_back(CMovingBitmap());
		big_monster_blood[i].LoadBitmapByString({ "Resources/ignore.bmp", "Resources/blood/B001.bmp",
			"Resources/blood/B002.bmp", "Resources/blood/B003.bmp","Resources/blood/B004.bmp", "Resources/blood/B005.bmp",
			"Resources/blood/B006.bmp", "Resources/blood/B007.bmp","Resources/blood/B008.bmp", "Resources/blood/B009.bmp",
			"Resources/ignore.bmp" }, RGB(255, 255, 255));
		big_monster_blood[i].SetTopLeft(big_monster[i].GetLeft() + big_monster[i].GetWidth(), big_monster[i].GetTop() + 20);
		big_monster_blood[i].SetAnimation(60, true);
	}

	for (int i = 0; i < 6; i++) {
		random_born_big_monster(fast_monster, {
			"Resources/fast_monster/b1.bmp","Resources/fast_monster/b2.bmp" ,"Resources/fast_monster/b3.bmp" ,"Resources/fast_monster/b4.bmp" ,"Resources/fast_monster/b5.bmp" ,"Resources/fast_monster/b6.bmp",
			"Resources/fast_monster/c1.bmp","Resources/fast_monster/c2.bmp" ,"Resources/fast_monster/c3.bmp" ,"Resources/fast_monster/c4.bmp" ,"Resources/fast_monster/c5.bmp" ,"Resources/fast_monster/c6.bmp" },
			fast_monster_vanish, { "Resources/fast_monster/k1.bmp","Resources/fast_monster/k2.bmp","Resources/fast_monster/k3.bmp" ,"Resources/fast_monster/k4.bmp",
								 "Resources/fast_monster/k5.bmp","Resources/fast_monster/k6.bmp","Resources/fast_monster/k7.bmp" ,"Resources/fast_monster/k8.bmp",
								 "Resources/fast_monster/k9.bmp","Resources/fast_monster/k10.bmp","Resources/fast_monster/k11.bmp" ,"Resources/fast_monster/k12.bmp",
								 "Resources/fast_monster/k13.bmp","Resources/fast_monster/k14.bmp","Resources/monster/m17.bmp" }, { 255,255,255 }, { 255, 255, 255 });  //255
		fast_monster[i].set_limit_start_end(0, 5);
		fast_monster[i].set_hp(10);
		fast_monster[i].set_end = 11;
		fast_monster[i].SetFrameIndexOfBitmap(0);
		fast_monster[i].SetAnimation(100, false);
		fast_monster[i].ay = 12;
		fast_monster[i].ax = 12;
	}

	blood.LoadBitmapByString({ "Resources/ignore.bmp", "Resources/blood/bloodfx001_01.bmp",
							"Resources/blood/bloodfx001_02.bmp", "Resources/blood/bloodfx001_03.bmp",
							"Resources/blood/bloodfx001_04.bmp", "Resources/blood/bloodfx001_05.bmp",
							"Resources/ignore.bmp" }, RGB(255, 255, 255));
	blood.SetTopLeft(character.GetLeft() + character.GetWidth(), character.GetTop());

	magnet.push_back(CMovingBitmap());
	magnet[0].LoadBitmapByString({ "Resources/props/magnet.bmp" , "Resources/ignore.bmp" }, RGB(255, 255, 255));
	magnet[0].SetTopLeft(character.GetLeft() - 300, character.GetTop() - 300);

	bomb.LoadBitmapByString({ "Resources/weapon/bomb.bmp" }, RGB(255, 255, 255));
	bomb.LoadBitmapByString({ "Resources/weapon/flamethrower_1_1.bmp", "Resources/weapon/flamethrower_1_2.bmp", "Resources/weapon/flamethrower_1_3.bmp",
		"Resources/weapon/flamethrower_1_4.bmp" }, RGB(255, 255, 255));
	bomb.LoadBitmapByString({ "Resources/ignore.bmp" }, RGB(255, 255, 255));

	bomb.SetFrameIndexOfBitmap(0);
	bomb.SetTopLeft(1000, 1000);
	bomb.set_limit_start_end(0, 0);
	bomb.SetAnimation(100, false);

}

void CGamestage2::OnKeyDown(UINT, UINT, UINT) {};

void CGamestage2::OnKeyUp(UINT, UINT, UINT) {};

void CGamestage2::OnLButtonDown(UINT nFlags, CPoint point) {};

void CGamestage2::OnLButtonUp(UINT nFlags, CPoint point) {};

void CGamestage2::OnMouseMove(UINT nFlags, CPoint point) {
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

void CGamestage2::OnRButtonDown(UINT nFlags, CPoint point) {};

void CGamestage2::OnRButtonUp(UINT nFlags, CPoint point) {};

void CGamestage2::OnMove() {
	get_data();
	timer += 1;

	background_move();

	blood.SetTopLeft(character.GetLeft() + character.GetWidth(), character.GetTop());
	blood_bar_progress(blood_bar, character);


	if (energy_bar.GetFrameIndexOfBitmap() == energy_bar.GetFrameSizeOfBitmap() - 1) {
		select = 1;	
	}
	dart_all(200);


	for (int i = 0; i < (int)(energy.size()); i++) {
		if (!energy[i].IsOverlap(character, energy[i]))
			item_move(energy[i]);
	}
	character.item_hit_energy(character, energy, energy_bar);
	if ((int)energy.size() < 10) {
		for (int i = 0; i < 100; i++) {
			random_born_item(energy, { "Resources/gem/gem1.bmp", "Resources/gem/gem2.bmp",
								   "Resources/gem/gem3.bmp","Resources/gem/gem4.bmp","Resources/gem/gem5.bmp" }, { 200, 191, 231 });

			energy[i].SetAnimation(100, false);
		}
	}

	item_move(magnet[0]);
	if (character.IsOverlap(character, magnet[0])) {
		magnet_trigger = 1;
		magnet[0].SetFrameIndexOfBitmap(1);
	}

	if (magnet_trigger == 1 && magnet_once == 0) {

		magnet_timer += 1;
		if (magnet_timer % 3 == 0) {
			magnet_animation();
		}
		if (magnet_timer > 100) {
			magnet_trigger = 0;
			magnet_timer = 0;
			magnet_once = 1;
		}
	}

	item_move(bomb);

	if (character.IsOverlap(character, bomb) && bomb.GetFrameIndexOfBitmap() == 0) {
		bomb_trigger = 1;
		bomb.set_limit_start_end(1, 4);
	}

	if (bomb_trigger == 1 && bomb_once == 0) {

		bomb_timer += 1;
		bomb.dart_hit_monster(bomb, monster, monster_vanish);
		bomb.dart_hit_monster(bomb, big_monster, big_monster_vanish);
		bomb.dart_hit_monster(bomb, fast_monster, fast_monster_vanish);

		if (bomb_timer > 110) {
			bomb_trigger = 0;
			bomb_timer = 0;
			bomb.SetFrameIndexOfBitmap(0);
			bomb.set_limit_start_end(0, 0);
			bomb.SetTopLeft(rand() % 1000 - 1000, rand() % 1000 - 1000);
		}
	}

	monster_all();

	bullet_move(bullet);
	bullet_erase(bullet);

	for (int i = 0; i < (int)bricks.size(); i++) {
		int j = bricks[i].ram_n;
		bricks_move(bricks[i], character.GetLeft() + h[j], character.GetTop() + k[j], c[j], x_move[j]);
		bricks_erase(bricks[i]);

		int k = monster.size();
		character.dart_hit_monster(bricks[i], monster, monster_vanish);
		character.dart_hit_monster(bricks[i], big_monster, big_monster_vanish);
		character.dart_hit_monster(bricks[i], fast_monster, fast_monster_vanish);
		dead_monster += k - monster.size();
	}


	lightning_move(lightning);

	for (int i = 0; i < (int)(lightning.size()); i++) {
		int ax = lightning[i].GetLeft();
		int ay = lightning[i].GetTop();
		item_move(lightning[i]);

		lightning[i].stdx += lightning[i].GetLeft() - ax;
		lightning[i].stdy += lightning[i].GetTop() - ay;

	}

	share_data();
};

void CGamestage2::OnShow() {
	get_data();
	show_img();
	show_text();
	share_data();
};

void CGamestage2::show_img() {

	background.ShowBitmap();

	if (character.GetFrameIndexOfBitmap() >= character.limit_frame_end) {
		character.SetFrameIndexOfBitmap(character.limit_frame_start);
	}
	character.ShowBitmap();
	for (int i = 0; i < (int)energy.size(); i++) {
		energy[i].ShowBitmap();
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
	}

	for (int i = 0; i < (int)(big_monster.size()); i++) {
		if (big_monster[i].GetFrameIndexOfBitmap() >= big_monster[i].limit_frame_end) {
			big_monster[i].SetFrameIndexOfBitmap(big_monster[i].limit_frame_start);
		}
		if (big_monster[i].IsOverlap(background, big_monster[i])) {
			big_monster[i].ShowBitmap();

		}
		big_monster_blood[i].SetTopLeft(big_monster[i].GetLeft(), big_monster[i].GetTop() + 50);
		if (big_monster[i].ishurted() == 1 && big_monster_blood[i].IsAnimationDone() && !big_monster_blood[i].IsAnimation()) {
			big_monster_blood[i].ToggleAnimation();
			big_monster[i].set_hurted(0);
		}


	}

	for (int i = 0; i < (int)big_monster_blood.size(); i++) {


		big_monster_blood[i].ShowBitmap();
	}

	for (int i = 0; i < (int)(fast_monster.size()); i++) {
		if (fast_monster[i].GetFrameIndexOfBitmap() >= fast_monster[i].limit_frame_end) {
			fast_monster[i].SetFrameIndexOfBitmap(fast_monster[i].limit_frame_start);
		}
		if (fast_monster[i].IsOverlap(background, fast_monster[i])) {
			fast_monster[i].ShowBitmap();
		}

	}


	for (int i = 0; i < (int)(big_monster_vanish.size()); i++) {
		big_monster_vanish[i].ShowBitmap();
	}

	for (int i = 0; i < (int)(fast_monster_vanish.size()); i++) {
		fast_monster_vanish[i].ShowBitmap();
	}


	for (int i = 0; i < (int)bullet.size(); i++) {
		bullet[i].ShowBitmap();
	}

	for (int j = 0; j < (int)bricks.size(); j++) {
		bricks[j].ShowBitmap();
	}

	for (int i = 0; i < (int)dart.size(); i++) {
		dart[i].ShowBitmap();
	}

	for (int i = 0; i < (int)lightning.size(); i++) {
		lightning[i].ShowBitmap();
	}

	magnet[0].ShowBitmap();
	if (bomb.GetFrameIndexOfBitmap() >= bomb.limit_frame_end) {
		bomb.SetFrameIndexOfBitmap(bomb.limit_frame_start);
	}

	bomb.ShowBitmap();
	blood.ShowBitmap();
	blood_bar.ShowBitmap();
	opera.ShowBitmap();
	energy_bar.ShowBitmap();

}

void CGamestage2::show_text() {

}

void CGamestage2::background_move() {
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

void CGamestage2::blood_bar_progress(CMovingBitmap &blood_bar, CMovingBitmap &item_blood) {

	if (item_blood.get_hp() >= item_blood.get_hp_max()) {
		blood_bar.SetFrameIndexOfBitmap(blood_bar.GetFrameSizeOfBitmap() - 1);
	}
	else if (item_blood.get_hp() > 0) {
		blood_bar.SetFrameIndexOfBitmap(((item_blood.get_hp()) / (item_blood.get_hp_max() / 5)));
	}
}

void CGamestage2::random_born_item(vector<CMovingBitmap>&item, vector<string> str, vector<int>rgb) {
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

void CGamestage2::item_move(CMovingBitmap &item) {
	double rate = 0.15;
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

void CGamestage2::mygame_dart_born() {

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

void CGamestage2::dart_all(int setR) {
	for (int i = 0; i < (int)dart.size(); i++) {
		dart[i].add_timer(1);
		dart_move(dart[i], (dart[i].timer % 360) * 5, setR);
		if (dart[i].get_timer() > 360) {
			dart[i].set_timer(0);
		}
		int k = monster.size();
		character.dart_hit_monster(dart[i], monster, monster_vanish);
		character.dart_hit_monster(dart[i], big_monster, big_monster_vanish);
		character.dart_hit_monster(dart[i], fast_monster, fast_monster_vanish);
		dead_monster += k - monster.size();
	}
}

void CGamestage2::dart_move(CMovingBitmap &item, int i, int setR) {
	int r = setR;;
	int px = character.get_center_x() + (int)(r *cos(i * 3.14 / 180));
	int py = character.get_center_y() + (int)(r *sin(i * 3.14 / 180));
	item.SetTopLeft(px, py);
}

void CGamestage2::random_born_monster(vector<CMovingBitmap>&monster, vector<string> str_monster, vector<CMovingBitmap>&monster_vanish, vector<string> str_monster_vanish, vector<int>rgb_monster, vector<int>rgb_monster_vanish) {

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


void CGamestage2::random_born_big_monster(vector<CMovingBitmap>&monster, vector<string> str_monster, vector<CMovingBitmap>&monster_vanish, vector<string> str_monster_vanish, vector<int>rgb_monster, vector<int>rgb_monster_vanish) {

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
	monster[tail].set_limit_start_end(0, 3);
}
void CGamestage2::monster_all() {

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

	for (int i = 0; i < (int)(big_monster.size()); i++) {
		item_move(big_monster[i]);

		if (!monster[i].IsOverlap(character, big_monster[i])) {
			big_monster_move(big_monster[i]);
			blood.SetAnimation(50, true);
		}
		else {
			character.add_sub_hp(-5);
			blood.SetAnimation(50, false);
			blood.ShowBitmap();
		}
	}

	for (int i = 0; i < (int)(fast_monster.size()); i++) {
		item_move(fast_monster[i]);

		if (!fast_monster[i].IsOverlap(character, fast_monster[i])) {
			big_monster_move(fast_monster[i]);
			blood.SetAnimation(50, true);
		}
		else {
			character.add_sub_hp(-5);
			blood.SetAnimation(50, false);
			blood.ShowBitmap();
		}

		if (isLeft(character, fast_monster[i])) {
			fast_monster[i].set_limit_start_end(6, 11);

		}
		else {
			fast_monster[i].set_limit_start_end(0, 5);

		}
	}

	if (int(monster.size()) < 30 && monster_vanish.size() != 0) {

		monster.push_back(monster_vanish[0]);
		monster[monster.size() - 1].SetFrameIndexOfBitmap(0);
		monster[monster.size() - 1].SetAnimation(50, false);
		monster[monster.size() - 1].set_hp(6);
		monster_reset(monster[monster.size() - 1]);
		monster_vanish.erase(monster_vanish.begin());
	}

	if (int(big_monster_vanish.size() > 2)) {

		big_monster.push_back(big_monster_vanish[0]);
		big_monster[big_monster.size() - 1].SetFrameIndexOfBitmap(0);
		big_monster[big_monster.size() - 1].SetAnimation(95, false);
		big_monster[big_monster.size() - 1].set_hp(40);
		big_monster[big_monster.size() - 1].set_limit_start_end(0, 3);
		int min = -1450;
		int max = 1450;
		int tail = big_monster.size() - 1;
		int x = rand() % (max - min + 1) + min;
		int y = rand() % (max - min + 1) + min;
		big_monster[tail].SetTopLeft(x, y);
		big_monster[tail].set_center(x + 45, y + 57);
		big_monster_vanish.erase(big_monster_vanish.begin());
	}
	
	if (int(fast_monster_vanish.size() > 2)) {

		fast_monster.push_back(fast_monster_vanish[0]);
		fast_monster[fast_monster.size() - 1].SetFrameIndexOfBitmap(0);
		fast_monster[fast_monster.size() - 1].SetAnimation(95, false);
		fast_monster[fast_monster.size() - 1].set_hp(10);
		fast_monster[fast_monster.size() - 1].set_limit_start_end(0, 5);
		int min = -1450;
		int max = 1450;
		int tail = fast_monster.size() - 1;
		int x = rand() % (max - min + 1) + min;
		int y = rand() % (max - min + 1) + min;
		fast_monster[tail].SetTopLeft(x, y);
		fast_monster[tail].set_center(x + 45, y + 57);
		fast_monster_vanish.erase(fast_monster_vanish.begin());			
	}

	if (timer == 10000) {
		timer = 0;
	}
}

bool CGamestage2::isLeft(CMovingBitmap &character, CMovingBitmap &item) {
	if (item.GetLeft() < character.GetLeft()) {
		return false;
	}
	else {
		return true;
	}
};

bool CGamestage2::isDown(CMovingBitmap &character, CMovingBitmap &item) {
	if (item.GetTop() - 200 < character.GetTop()) {
		return false;
	}
	else {
		return true;
	}
};

void CGamestage2::monster_move(CMovingBitmap &monster) {

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

void CGamestage2::big_monster_move(CMovingBitmap &monster) {

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


	monster.SetTopLeft(monster.GetLeft() + (int)(np_x*_x*0.5*(1+monster.ax/10.0)), monster.GetTop() + (int)(np_y*_y*0.5*((1 + monster.ay/10.0) ) ) );

	if (isLeft(character, monster)) {
		monster.set_limit_start_end(4, 7);

	}
	else {
		monster.set_limit_start_end(0, 3);
	}
};


void CGamestage2::bullet_move(vector<CMovingBitmap> &item) {
	for (int i = 0; i < (int)item.size(); i++) {
		item[i].SetTopLeft(character.GetLeft() + 10, item[i].GetTop() - 10);
		int k = monster.size();
		character.dart_hit_monster(item[i], monster, monster_vanish);
		character.dart_hit_monster(item[i], big_monster, big_monster_vanish);
		character.dart_hit_monster(item[i], fast_monster, fast_monster_vanish);
		dead_monster += k - monster.size();
	}
}


void CGamestage2::bullet_erase(vector<CMovingBitmap> &item) {

	for (int i = 0; i < (int)item.size(); i++) {
		if (item[i].GetTop() < 0) {
			bullet[i].SetTopLeft(character.GetLeft() + 10, character.GetTop());
		}
	}
}

void CGamestage2::bricks_move(CMovingBitmap &item, int h, int k, int c, int x_move) {
	int x = item.GetLeft() + x_move;
	int y = (x - h) * (x - h) / (4 * c) + k;
	item.SetTopLeft(x, y);


}

void CGamestage2::bricks_born(vector<CMovingBitmap> &item, vector<string> str, vector<int>rgb) {
	int tail = item.size();
	item.push_back(CMovingBitmap());
	item[tail].LoadBitmapByString(str, RGB(rgb[0], rgb[1], rgb[2]));
	item[tail].SetTopLeft(character.GetLeft() + 10, character.GetTop());
	item[tail].ram_n = rand() % 4;
}

void CGamestage2::born_bullet(vector<CMovingBitmap> &item, vector<string> str, vector<int>rgb) {
	int tail = item.size();
	if (item[tail - 1].GetTop() < 0) {
		item.push_back(CMovingBitmap());
		item[tail].LoadBitmapByString(str, RGB(rgb[0], rgb[1], rgb[2]));
		item[tail].SetTopLeft(character.GetLeft() + 10, character.GetTop());
	}
}


void CGamestage2::bricks_erase(CMovingBitmap &item) {
	if (item.GetTop() + 70 > 1065) {
		//item.erase(item.begin());
		item.ram_n = (rand() + timer) % 4;
		item.SetTopLeft(character.GetLeft() + 10, character.GetTop());
	}
}

void CGamestage2::monster_pop(int less_than_n) {

	for (int i = 0; i < (int)monster.size(); i++) {
		if ((int)monster.size() > less_than_n) {
			monster.erase(monster.begin() + i);
		}
		else {
			break;
		}
	}
}

void CGamestage2::big_monster_born() {
	int i = big_monster.size();
	random_born_big_monster(big_monster, { "Resources/monster/big_m0.bmp","Resources/monster/big_m1.bmp" ,"Resources/monster/big_m2.bmp" ,"Resources/monster/big_m3.bmp",
										"Resources/monster/big_m4.bmp","Resources/monster/big_m5.bmp" ,"Resources/monster/big_m6.bmp" ,"Resources/monster/big_m7.bmp" },
		big_monster_vanish, { "Resources/monster/big_e0.bmp","Resources/monster/big_e1.bmp" ,"Resources/monster/big_e2.bmp" ,"Resources/monster/big_e3.bmp",
							  "Resources/monster/big_e4.bmp","Resources/monster/big_e5.bmp" ,"Resources/monster/big_e6.bmp" ,"Resources/monster/big_e7.bmp",
							  "Resources/monster/big_e8.bmp","Resources/monster/big_e9.bmp","Resources/monster/m17.bmp" }, { 255,255,255 }, { 255, 255, 255 });  //255
	big_monster[i].SetAnimation(125, false);
	big_monster[i].set_hp(40);
}

void CGamestage2::show_baclground_selected(int s) {

	if (s == 0) {
		background.SetFrameIndexOfBitmap(0);

	}
	else if (s == 1) {
		background.SetFrameIndexOfBitmap(1);

	}

}

void CGamestage2::lightning_move(vector<CMovingBitmap> &item) {


	int flag = 0;
	int f[100] = { 0,0,0,0, 0,0,0,0 };
	for (int i = 0; i < (int)item.size(); i++) {

		if ((lightning[i].GetLeft() <= (lightning[i].stdx - 300)) || (lightning[i].GetLeft() + 105 >= (lightning[i].stdx + 300))) {
			lightning[i].ax *= -1;
		}
		if (lightning[i].GetTop() < (lightning[i].stdy - 700) || lightning[i].GetTop() > (lightning[i].stdy + 700)) {
			flag++;
			f[i] = 1;
		}

		lightning[i].SetTopLeft(lightning[i].GetLeft() + lightning[i].ax, lightning[i].GetTop() + lightning[i].ay);
		int k = monster.size();
		character.dart_hit_monster(item[i], monster, monster_vanish);
		character.dart_hit_monster(item[i], big_monster, big_monster_vanish);
		character.dart_hit_monster(item[i], fast_monster, fast_monster_vanish);
		dead_monster += k - monster.size();
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




void CGamestage2::monster_reset(CMovingBitmap &item) {


	int min = -1450;
	int max = 1450;
	int x = rand() % (max - min + 1) + min;
	int y = rand() % (max - min + 1) + min;
	item.SetTopLeft(x, y);
	item.set_center(x + 45, y + 57);

	item.SetFrameIndexOfBitmap(item.limit_frame_start);

	if (isLeft(character, item)) {
		item.set_limit_start_end(10, 19);
		item.SetFrameIndexOfBitmap(item.limit_frame_start);
	}
	else {
		item.set_limit_start_end(0, 9);
		item.SetFrameIndexOfBitmap(item.limit_frame_start);

	}

	if (isDown(character, item) && (item.GetLeft() > 365 && item.GetLeft() < 580)) {
		item.set_limit_start_end(20, 29);
		item.SetFrameIndexOfBitmap(item.limit_frame_start);
	}
	else {
		item.SetFrameIndexOfBitmap(item.limit_frame_start);
	}


};


void CGamestage2::lightning_born() {

	int axay[5][4] = { {-5,2},{5,2},{-5,-2},{5,-2} };
	int a = (int)lightning.size();

	for (int i = a; i < a + 4; i++) {
		lightning.push_back(CMovingBitmap());
		lightning[i].LoadBitmapByString({ "Resources/lightning/g1.bmp","Resources/lightning/g2.bmp","Resources/lightning/g3.bmp","Resources/lightning/g4.bmp",
										  "Resources/lightning/g5.bmp" ,"Resources/lightning/g6.bmp" ,"Resources/lightning/g7.bmp" ,"Resources/lightning/g8.bmp",
										  "Resources/lightning/g9.bmp", "Resources/lightning/g10.bmp", "Resources/lightning/g11.bmp", "Resources/lightning/g12.bmp",
										  "Resources/lightning/g13.bmp" ,"Resources/lightning/g14.bmp" ,"Resources/lightning/g15.bmp" ,"Resources/lightning/g16.bmp",
										  "Resources/lightning/g17.bmp" ,"Resources/lightning/g18.bmp" ,"Resources/lightning/g19.bmp", "Resources/lightning/g20.bmp" }, RGB(255, 255, 255));
		lightning[i].SetTopLeft(character.GetLeft() + character.GetWidth() / 2 - lightning[i].GetWidth() / 2, character.GetTop());
		lightning[i].SetAnimation(30, false);
		lightning[i].stdx = character.GetLeft() + (character.GetWidth() / 2);
		lightning[i].stdy = character.GetTop();
		lightning[i].ax = axay[i % 4][0];
		lightning[i].ay = axay[i % 4][1];
	}

};


void CGamestage2::magnet_animation() {
	int x1 = character.GetLeft();
	int y1 = character.GetTop();
	for (int i = 0; i < (int)(energy.size()); i++) {
		if (abs(energy[i].GetLeft() - character.GetLeft()) < 500 && abs(energy[i].GetTop() - character.GetTop()) < 500) {
			int x2 = energy[i].GetLeft();
			int y2 = energy[i].GetTop();
			int m = 0;
			if (x2 - x1 != 0) {
				m = (y2 - y1) / (x2 - x1);
			}
			int b = y1 - m * x1;
			int x = x2;
			if (x > x1) {
				x -= 40;
			}
			else {
				x += 40;
			}
			int y = m * x + b;
			energy[i].SetTopLeft(x, y);
		}
	}
}
int CGamestage2::get_dead_monster() {
	return dead_monster;
}

/////////////////////////////update data/////////////////


void CGamestage2::set_share_obj_data(CMovingBitmap &tmp_background, CMovingBitmap &tmp_character, CMovingBitmap &tmp_opera, CMovingBitmap &tmp_blood_bar, CMovingBitmap &tmp_energy_bar,
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

void CGamestage2::move_share_obj_data(CMovingBitmap &tmp_background, CMovingBitmap &tmp_character, CMovingBitmap &tmp_opera, CMovingBitmap &tmp_blood_bar,
	CMovingBitmap &tmp_energy_bar, vector <CMovingBitmap> &tmp_dart, vector<CMovingBitmap> &tmp_bullet, vector<CMovingBitmap> &tmp_bricks, vector<CMovingBitmap> &tmp_lightning) {

	tmp_background = background;
	tmp_character = character;
	tmp_opera = opera;
	tmp_blood_bar = blood_bar;
	tmp_energy_bar = energy_bar;
	tmp_dart = dart;
	tmp_bullet = bullet;
	tmp_bricks = bricks;
	tmp_lightning = lightning;
};

void CGamestage2::get_data() {

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

void CGamestage2::share_data() {

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