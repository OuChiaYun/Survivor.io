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

	select_pic[0].LoadBitmapByString({"Resources/weapon/cleaver.bmp"}, RGB(255, 255, 255));


	select_pic[1].LoadBitmapByString({ "Resources/weapon/hot_wheels/00.bmp",
	"Resources/weapon/hot_wheels/01.bmp",
	"Resources/weapon/hot_wheels/02.bmp",
	"Resources/weapon/hot_wheels/03.bmp",
	"Resources/weapon/hot_wheels/04.bmp",
	"Resources/weapon/hot_wheels/05.bmp",
	"Resources/weapon/hot_wheels/06.bmp",
	"Resources/weapon/hot_wheels/07.bmp" }, RGB(255, 255, 255));

	select_pic[2].LoadBitmapByString({ "Resources/lightning/g1.bmp","Resources/lightning/g2.bmp","Resources/lightning/g3.bmp","Resources/lightning/g4.bmp",
	"Resources/lightning/g5.bmp" ,"Resources/lightning/g6.bmp" ,"Resources/lightning/g7.bmp" ,"Resources/lightning/g8.bmp",
	"Resources/lightning/g9.bmp", "Resources/lightning/g10.bmp", "Resources/lightning/g11.bmp", "Resources/lightning/g12.bmp",
	"Resources/lightning/g13.bmp" ,"Resources/lightning/g14.bmp" ,"Resources/lightning/g15.bmp" ,"Resources/lightning/g16.bmp",
	"Resources/lightning/g17.bmp" ,"Resources/lightning/g18.bmp" ,"Resources/lightning/g19.bmp", "Resources/lightning/g20.bmp" }, RGB(255, 255, 255));
	
		
	select_pic[1].SetAnimation(100,false);
	select_pic[2].SetAnimation(100, false);

	select_start.LoadBitmapByString({ "Resources/select_bar/s1.bmp","Resources/select_bar/s2.bmp","Resources/select_bar/s3.bmp" ,"Resources/select_bar/s4.bmp" ,"Resources/select_bar/s5.bmp" }, RGB(255, 255, 255));
	select_start.SetAnimation(200, false);
	select_start.SetTopLeft((select_bar.GetLeft() + 40 + ((select_bar.GetWidth() - 80) / 6) * 3) - (select_start.GetWidth() / 2), select_bar.GetTop() + 450);

	selected.LoadBitmapByString({ "Resources/select_bar/selected2.bmp", "Resources/select_bar/selected_ignore.bmp" }, RGB(255, 255, 255));
	selected.SetTopLeft(select_pic_bg[0].GetLeft() + 2, select_pic_bg[0].GetTop());

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
	
	for (int i = 0; i < 3; i++) {
		select_pic_bg[i].ShowBitmap();
		select_pic[i].SetTopLeft((select_pic_bg[i].GetLeft() + select_pic_bg[i].GetWidth() / 2 - select_pic[i].GetWidth() / 2), select_pic_bg[i].GetTop() + 40);
		select_pic[i].ShowBitmap();
	}
	select_start.ShowBitmap();
	selected.ShowBitmap();
	show_text();
};

void CGamestageSelect::show_text() {
	CDC *pdc = CDDraw::GetBackCDC();

	CTextDraw::ChangeFontLog(pdc, 25, "Modern No. 20", RGB(255, 255, 255), 80);
	CTextDraw::Print(pdc, select_pic_bg[0].GetLeft() + 75, select_pic[0].GetTop() + 85, "Brick");
	CTextDraw::ChangeFontLog(pdc, 12, "Modern No. 20", RGB(255, 255, 255), 80);
	CTextDraw::Print(pdc, select_pic_bg[0].GetLeft() + 65, select_pic[0].GetTop() + 140, "Throws 1 brick");

	CTextDraw::ChangeFontLog(pdc, 25, "Modern No. 20", RGB(255, 255, 255), 80);
	CTextDraw::Print(pdc, select_pic_bg[1].GetLeft() + 45, select_pic[1].GetTop() + 85, "Guardian");
	CTextDraw::ChangeFontLog(pdc, 12, "Modern No. 20", RGB(255, 255, 255), 80);
	CTextDraw::Print(pdc, select_pic_bg[1].GetLeft() + 32, select_pic[1].GetTop() + 140, "Summoons 1 tops that");
	CTextDraw::ChangeFontLog(pdc, 12, "Modern No. 20", RGB(255, 255, 255), 80);
	CTextDraw::Print(pdc, select_pic_bg[1].GetLeft() + 32, select_pic[1].GetTop() + 165, "circle you Stops bullets");

	CTextDraw::ChangeFontLog(pdc, 25, "Modern No. 20", RGB(255, 255, 255), 80);
	CTextDraw::Print(pdc, select_pic_bg[2].GetLeft() + 35, select_pic[2].GetTop() + 85, "Lightning");
	CTextDraw::ChangeFontLog(pdc, 12, "Modern No. 20", RGB(255, 255, 255), 80);
	CTextDraw::Print(pdc, select_pic_bg[2].GetLeft() + 33, select_pic[2].GetTop() + 140, "Lightning shower on");
	CTextDraw::ChangeFontLog(pdc, 12, "Modern No. 20", RGB(255, 255, 255), 80);
	CTextDraw::Print(pdc, select_pic_bg[2].GetLeft() + 40, select_pic[2].GetTop() + 165, "random target area");

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
