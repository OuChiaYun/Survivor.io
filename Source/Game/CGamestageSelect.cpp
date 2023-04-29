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

void CGamestageSelect::OnBeginState() {};

void CGamestageSelect::OnInit() {

	select_bar.LoadBitmapByString({ "Resources/select_bar/select_bg.bmp","Resources/select_bar/select_bg_ignore.bmp" }, RGB(255, 255, 255));
	select_bar.SetTopLeft(533 - select_bar.GetWidth() / 2, 200);
	select_bar.SetFrameIndexOfBitmap(0);


	select_pic_bg[0].LoadBitmapByString({ "Resources/select_bar/select_bg_pic_2.bmp" }, RGB(255, 255, 255));
	select_pic_bg[0].SetTopLeft((select_bar.GetLeft() + 40 + ((select_bar.GetWidth() - 80) / 6) * 1) - (select_pic_bg[0].GetWidth() / 2), select_bar.GetTop() + 50);

	select_pic_bg[1].LoadBitmapByString({ "Resources/select_bar/select_bg_pic_2.bmp" }, RGB(255, 255, 255));
	select_pic_bg[1].SetTopLeft((select_bar.GetLeft() + 40 + ((select_bar.GetWidth() - 80) / 6) * 3) - (select_pic_bg[0].GetWidth() / 2), select_bar.GetTop() + 50);

	select_pic_bg[2].LoadBitmapByString({ "Resources/select_bar/select_bg_pic_2.bmp" }, RGB(255, 255, 255));
	select_pic_bg[2].SetTopLeft((select_bar.GetLeft() + 40 + ((select_bar.GetWidth() - 80) / 6) * 5) - (select_pic_bg[0].GetWidth() / 2), select_bar.GetTop() + 50);

	select_pic.LoadBitmapByString({ "Resources/weapon/hot_wheels/00.bmp",
	"Resources/weapon/hot_wheels/01.bmp",
	"Resources/weapon/hot_wheels/02.bmp",
	"Resources/weapon/hot_wheels/03.bmp",
	"Resources/weapon/hot_wheels/04.bmp",
	"Resources/weapon/hot_wheels/05.bmp",
	"Resources/weapon/hot_wheels/06.bmp",
	"Resources/weapon/hot_wheels/07.bmp" }, RGB(255, 255, 255));
	
		//	select_pic.SetTopLeft( (select_pic_bg.GetLeft() + select_pic_bg.GetWidth() ) / 2 + (select_pic.GetWidth()), select_pic_bg.GetTop()+30);
		
	select_pic.SetAnimation(100,false);

	select_start.LoadBitmapByString({ "Resources/select_bar/s1.bmp","Resources/select_bar/s2.bmp","Resources/select_bar/s3.bmp" ,"Resources/select_bar/s4.bmp" ,"Resources/select_bar/s5.bmp" }, RGB(255, 255, 255));
	select_start.SetAnimation(200, false);
	select_start.SetTopLeft((select_bar.GetLeft() + 40 + ((select_bar.GetWidth() - 80) / 6) * 3) - (select_start.GetWidth() / 2), select_bar.GetTop() + 450);

	selected.LoadBitmapByString({ "Resources/select_bar/selected2.bmp", "Resources/select_bar/selected_ignore.bmp" }, RGB(255, 255, 255));
	selected.SetTopLeft(select_pic_bg[1].GetLeft() + 2, select_pic_bg[1].GetTop());

}

void CGamestageSelect::OnKeyDown(UINT, UINT, UINT) {};

void CGamestageSelect::OnKeyUp(UINT, UINT, UINT) {};

void CGamestageSelect::OnLButtonDown(UINT nFlags, CPoint point) {

	if (isSelect(nFlags, point, select_pic_bg[0])) {
		selected.SetTopLeft(select_pic_bg[0].GetLeft() + 2, select_pic_bg[0].GetTop());
		weapon_selected = 0;

	}
	if (isSelect(nFlags, point, select_pic_bg[1])) {
		selected.SetTopLeft(select_pic_bg[1].GetLeft() + 2, select_pic_bg[1].GetTop());
		weapon_selected = 1;

	}
	if (isSelect(nFlags, point, select_pic_bg[2])) {
		selected.SetTopLeft(select_pic_bg[2].GetLeft() + 2, select_pic_bg[2].GetTop());
		weapon_selected = 2;

	}
	if (isSelect(nFlags, point, select_start)) {
		show = 2;
	};
};

void CGamestageSelect::OnLButtonUp(UINT nFlags, CPoint point) {};

void CGamestageSelect::OnMouseMove(UINT nFlags, CPoint point) {

};

void CGamestageSelect::OnRButtonDown(UINT nFlags, CPoint point) {};

void CGamestageSelect::OnRButtonUp(UINT nFlags, CPoint point) {};

void CGamestageSelect::OnMove() {

};

void CGamestageSelect::OnShow() {
	select_bar.ShowBitmap();
	select_pic_bg[0].ShowBitmap();
	select_pic_bg[1].ShowBitmap();
	select_pic_bg[2].ShowBitmap();
	select_pic.SetTopLeft((select_pic_bg[1].GetLeft() + select_pic_bg[1].GetWidth() / 2 - select_pic.GetWidth() / 2), select_pic_bg[1].GetTop() + 40);
	select_pic.ShowBitmap();
	select_start.ShowBitmap();
	selected.ShowBitmap();
};



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
