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
#include <cstdlib> 
#include <time.h>
#include <string>
#include <ctime>

#define BRICKS 0
#define DART 1
#define LIGHTNING 2
#define BLOOD_ADD 3

using namespace game_framework;

void CGamestageSelect::OnBeginState() {
	show = 0;
};

void CGamestageSelect::OnInit() {

	//srand(time(NULL));

	select_bar.LoadBitmapByString({ "Resources/select_bar/select_bg.bmp","Resources/select_bar/select_bg_ignore.bmp" }, RGB(255, 255, 255));
	select_bar.SetTopLeft(533 - select_bar.GetWidth() / 2, 200);
	select_bar.SetFrameIndexOfBitmap(0);


	select_pic_bg[0].LoadBitmapByString({ "Resources/select_bar/select_bg_pic_2.bmp" }, RGB(255, 255, 255));
	select_pic_bg[0].SetTopLeft((select_bar.GetLeft() + 40 + ((select_bar.GetWidth() - 80) / 6) * 1) - (select_pic_bg[0].GetWidth() / 2), select_bar.GetTop() + 50);

	select_pic_bg[1].LoadBitmapByString({ "Resources/select_bar/select_bg_pic_2.bmp" }, RGB(255, 255, 255));
	select_pic_bg[1].SetTopLeft((select_bar.GetLeft() + 40 + ((select_bar.GetWidth() - 80) / 6) * 3) - (select_pic_bg[0].GetWidth() / 2), select_bar.GetTop() + 50);

	select_pic_bg[2].LoadBitmapByString({ "Resources/select_bar/select_bg_pic_2.bmp" }, RGB(255, 255, 255));
	select_pic_bg[2].SetTopLeft((select_bar.GetLeft() + 40 + ((select_bar.GetWidth() - 80) / 6) * 5) - (select_pic_bg[0].GetWidth() / 2), select_bar.GetTop() + 50);

	select_pic[0].LoadBitmapByString({ "Resources/weapon/cleaver.bmp",

	"Resources/weapon/hot_wheels/00.bmp",
	"Resources/weapon/hot_wheels/01.bmp",
	"Resources/weapon/hot_wheels/02.bmp",
	"Resources/weapon/hot_wheels/03.bmp",
	"Resources/weapon/hot_wheels/04.bmp",
	"Resources/weapon/hot_wheels/05.bmp",
	"Resources/weapon/hot_wheels/06.bmp",
	"Resources/weapon/hot_wheels/07.bmp",

	"Resources/lightning/g1.bmp","Resources/lightning/g2.bmp","Resources/lightning/g3.bmp","Resources/lightning/g4.bmp",
	"Resources/lightning/g5.bmp" ,"Resources/lightning/g6.bmp" ,"Resources/lightning/g7.bmp" ,"Resources/lightning/g8.bmp",
	"Resources/lightning/g9.bmp", "Resources/lightning/g10.bmp", "Resources/lightning/g11.bmp", "Resources/lightning/g12.bmp",
	"Resources/lightning/g13.bmp" ,"Resources/lightning/g14.bmp" ,"Resources/lightning/g15.bmp" ,"Resources/lightning/g16.bmp",
	"Resources/lightning/g17.bmp" ,"Resources/lightning/g18.bmp" ,"Resources/lightning/g19.bmp", "Resources/lightning/g20.bmp",

	"Resources/select_bar/blood_add_water.bmp"
	}, RGB(255, 255, 255));

	select_pic[1].LoadBitmapByString({ "Resources/weapon/cleaver.bmp",

	"Resources/weapon/hot_wheels/00.bmp",
	"Resources/weapon/hot_wheels/01.bmp",
	"Resources/weapon/hot_wheels/02.bmp",
	"Resources/weapon/hot_wheels/03.bmp",
	"Resources/weapon/hot_wheels/04.bmp",
	"Resources/weapon/hot_wheels/05.bmp",
	"Resources/weapon/hot_wheels/06.bmp",
	"Resources/weapon/hot_wheels/07.bmp",

	"Resources/lightning/g1.bmp","Resources/lightning/g2.bmp","Resources/lightning/g3.bmp","Resources/lightning/g4.bmp",
	"Resources/lightning/g5.bmp" ,"Resources/lightning/g6.bmp" ,"Resources/lightning/g7.bmp" ,"Resources/lightning/g8.bmp",
	"Resources/lightning/g9.bmp", "Resources/lightning/g10.bmp", "Resources/lightning/g11.bmp", "Resources/lightning/g12.bmp",
	"Resources/lightning/g13.bmp" ,"Resources/lightning/g14.bmp" ,"Resources/lightning/g15.bmp" ,"Resources/lightning/g16.bmp",
	"Resources/lightning/g17.bmp" ,"Resources/lightning/g18.bmp" ,"Resources/lightning/g19.bmp", "Resources/lightning/g20.bmp",

	"Resources/select_bar/blood_add_water.bmp"
	}, RGB(255, 255, 255));

	select_pic[2].LoadBitmapByString({ "Resources/weapon/cleaver.bmp",

	"Resources/weapon/hot_wheels/00.bmp",
	"Resources/weapon/hot_wheels/01.bmp",
	"Resources/weapon/hot_wheels/02.bmp",
	"Resources/weapon/hot_wheels/03.bmp",
	"Resources/weapon/hot_wheels/04.bmp",
	"Resources/weapon/hot_wheels/05.bmp",
	"Resources/weapon/hot_wheels/06.bmp",
	"Resources/weapon/hot_wheels/07.bmp",

	"Resources/lightning/g1.bmp","Resources/lightning/g2.bmp","Resources/lightning/g3.bmp","Resources/lightning/g4.bmp",
	"Resources/lightning/g5.bmp" ,"Resources/lightning/g6.bmp" ,"Resources/lightning/g7.bmp" ,"Resources/lightning/g8.bmp",
	"Resources/lightning/g9.bmp", "Resources/lightning/g10.bmp", "Resources/lightning/g11.bmp", "Resources/lightning/g12.bmp",
	"Resources/lightning/g13.bmp" ,"Resources/lightning/g14.bmp" ,"Resources/lightning/g15.bmp" ,"Resources/lightning/g16.bmp",
	"Resources/lightning/g17.bmp" ,"Resources/lightning/g18.bmp" ,"Resources/lightning/g19.bmp", "Resources/lightning/g20.bmp",

	"Resources/select_bar/blood_add_water.bmp"
	}, RGB(255, 255, 255));


	select_start.LoadBitmapByString({ "Resources/select_bar/s1.bmp","Resources/select_bar/s2.bmp","Resources/select_bar/s3.bmp" ,"Resources/select_bar/s4.bmp" ,"Resources/select_bar/s5.bmp" ,"Resources/select_bar/s_s.bmp" }, RGB(255, 255, 255));

	select_start.SetTopLeft((select_bar.GetLeft() + 40 + ((select_bar.GetWidth() - 80) / 6) * 3) - (select_start.GetWidth() / 2), select_bar.GetTop() + 450);
	select_start.set_limit_start_end(0,4);
	
	selected.LoadBitmapByString({ "Resources/select_bar/selected2.bmp", "Resources/select_bar/selected_ignore.bmp" }, RGB(255, 255, 255));
	selected.SetTopLeft(select_pic_bg[0].GetLeft() + 2, select_pic_bg[0].GetTop());

	rand_option();

}

void CGamestageSelect::OnKeyDown(UINT, UINT, UINT) {};

void CGamestageSelect::OnKeyUp(UINT, UINT, UINT) {};

void CGamestageSelect::OnLButtonDown(UINT nFlags, CPoint point) {

	
	if (isSelect(nFlags, point, select_pic_bg[0])) {
		selected.SetTopLeft(select_pic_bg[0].GetLeft() + 2, select_pic_bg[0].GetTop());
		weapon_selected = rand_list[0];

	}
	if (isSelect(nFlags, point, select_pic_bg[1])) {
		selected.SetTopLeft(select_pic_bg[1].GetLeft() + 2, select_pic_bg[1].GetTop());
		weapon_selected = rand_list[1];

	}
	if (isSelect(nFlags, point, select_pic_bg[2])) {
		selected.SetTopLeft(select_pic_bg[2].GetLeft() + 2, select_pic_bg[2].GetTop());
		weapon_selected = rand_list[2];
	}
	
	if (isSelect(nFlags, point, select_start)) {
		show = 2;
	};
	
};

void CGamestageSelect::OnLButtonUp(UINT nFlags, CPoint point) {};

void CGamestageSelect::OnMouseMove(UINT nFlags, CPoint point) {
	if (isSelect(TRUE, point, select_start)) {
		select_start.SetAnimation(200, true);
		select_start.SetFrameIndexOfBitmap(5);
		select_start.set_limit_start_end(0, 6);
		
	}
	else {
select_start.SetAnimation(200, false);
select_start.set_limit_start_end(0, 5);
	}
};

void CGamestageSelect::OnRButtonDown(UINT nFlags, CPoint point) {};

void CGamestageSelect::OnRButtonUp(UINT nFlags, CPoint point) {};

void CGamestageSelect::OnMove() {

};

void CGamestageSelect::OnShow() {
	//select_bar.ShowBitmap();

	for (int i = 0; i < 3; i++) {
		select_pic_bg[i].ShowBitmap();
		if (select_pic[i].GetFrameIndexOfBitmap() >= select_pic[i].limit_frame_end) {
			select_pic[i].SetFrameIndexOfBitmap(select_pic[i].limit_frame_start);
		}
		select_pic[i].SetTopLeft((select_pic_bg[i].GetLeft() + select_pic_bg[i].GetWidth() / 2 - select_pic[i].GetWidth() / 2), select_pic_bg[i].GetTop() + 40);
		select_pic[i].ShowBitmap();




	}
	if (select_start.GetFrameIndexOfBitmap() >= select_start.limit_frame_end) {
		select_start.SetFrameIndexOfBitmap(select_start.limit_frame_start);
	}
	select_start.ShowBitmap();

	selected.ShowBitmap();
	show_text();
};

void CGamestageSelect::show_text() {

	string text[5][100] = { {"Brick","Throws 1 brick"},
							{"Guardian","Summoons 1 tops","that circle you","Stops bullets"},
							{"Lightning","Lightning shower ","on random target ","area"},
							{"Heal elixir","Hp + 3500"} };


	CDC *pdc = CDDraw::GetBackCDC();

	for (int j = 0; j < 3; j++) {
		CTextDraw::ChangeFontLog(pdc, 25, "monogram", RGB(255, 255, 255), 80);
		CTextDraw::Print(pdc, select_pic_bg[j].GetLeft() + 40+ (10 - (text[rand_list[j]][0].length())/2)*5, select_pic[0].GetTop() + 110, text[rand_list[j]][0]);

		for (int i = 1; i < sizeof(text[j]) / sizeof(text[j][0]); i++) {
			CTextDraw::ChangeFontLog(pdc, 12, "monogram", RGB(255, 255, 255), 80);
			CTextDraw::Print(pdc, select_pic_bg[j].GetLeft() + 65 + 10, select_pic[j].GetTop() + 145 + 25 * i, text[rand_list[j]][i]);
		}
	}
	CDDraw::ReleaseBackCDC();
}


bool CGamestageSelect::isSelect(UINT nFlags, CPoint point, CMovingBitmap &item) {
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

void CGamestageSelect::rand_option() {

	for (int i = 0; i < 3; i++)
	{
		rand_list[i] = rand() % 4;

		for (int j = 0; j < i; j++)
		{
			if (rand_list[i] == rand_list[j])
			{
				i--;
				break;
			}
		}

	}

	for (int i = 0; i < 3; i++) {
		if (rand_list[i] == BRICKS) {
			select_pic[i].SetFrameIndexOfBitmap(0);
			select_pic[i].set_limit_start_end(0, 0);
			select_pic[i].SetAnimation(100, true);

		}
		if (rand_list[i] == DART) {
			select_pic[i].SetFrameIndexOfBitmap(1);
			select_pic[i].set_limit_start_end(1, 8);
			select_pic[i].SetAnimation(100, false);
		}
		if (rand_list[i] == LIGHTNING) {
			select_pic[i].SetFrameIndexOfBitmap(9);
			select_pic[i].set_limit_start_end(9, 28);
			select_pic[i].SetAnimation(100, false);
		}
		if (rand_list[i] == BLOOD_ADD) {
			select_pic[i].SetFrameIndexOfBitmap(29);
			select_pic[i].set_limit_start_end(29, 29);
			select_pic[i].SetAnimation(100, true);
		}

	}

	if (selected.GetLeft() == select_pic_bg[0].GetLeft() + 2 && selected.GetTop() == select_pic_bg[0].GetTop()) {
		weapon_selected = rand_list[0];
	}

	else if (selected.GetLeft() == select_pic_bg[1].GetLeft() + 2 && selected.GetTop() == select_pic_bg[1].GetTop()) {
		weapon_selected = rand_list[1];
	}

	else if (selected.GetLeft() == select_pic_bg[2].GetLeft() + 2 && selected.GetTop() == select_pic_bg[2].GetTop()) {
		weapon_selected = rand_list[2];
	}
};
