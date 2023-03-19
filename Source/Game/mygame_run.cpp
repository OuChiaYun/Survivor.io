#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace game_framework;

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
/////////////////////////////////////////////////////////////////////////////

CGameStateRun::CGameStateRun(CGame *g) : CGameState(g)
{
}

CGameStateRun::~CGameStateRun()
{
}

void CGameStateRun::OnBeginState()
{
}

void CGameStateRun::OnMove()							// 移動遊戲元素
{

	//background.SetTopLeft(background.GetLeft() - int((opera.GetLeft()- 437)*0.2), background.GetTop() - int((opera.GetTop() - 682)*0.2));
	background_move();
	show_img();
	//background_move(background2);

	for (int i = 0; i < 100; i++) {
		item_move(energy[i]);
		character.item_hit(character,energy[i]);
	}
	for (int i = 0; i < 40; i++) {
		item_move(monster[i]);
		monster_move(monster[i]);
	}


}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{
	background.LoadBitmapByString({ "Resources/background.bmp" });
	background.SetTopLeft(-1500, -1500);
	background2.LoadBitmapByString({ "Resources/background.bmp" });
	background2.SetTopLeft(0, 4000);

	character.LoadBitmapByString({ "Resources/witch.bmp" }, RGB(255, 255, 255));
	character.SetTopLeft(461, 252);
	character.set_center(501,300); //40 49

	opera.LoadBitmapByString({ "Resources/operator.bmp" }, RGB(105, 106, 106));
	opera.SetTopLeft(437, 682);
	opera.set_center(437 + 54, 682 + 54);//491 , 736

	goal.LoadBitmapByString({ "Resources/goal.bmp" }, RGB(255, 255, 255));
	goal.SetTopLeft(107, 82);


	srand((unsigned)time(NULL));
	/* 指定亂數範圍 */
	int min = -1450;
	int max = 1450;
	for (int i = 0; i < 100; i++) {
		random_born_item(energy, { "Resources/energy.bmp", "Resources/energy_ignore.bmp" }, {255,255,255});

	}
	for (int i = 0; i < 40; i++) {
		int arr[] = { 1,2,3 };
		random_born_item(monster, { "Resources/monster.bmp", "Resources/energy_ignore.bmp" }, { 255,255,255 });

	}
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{

}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{

}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
	// 處理滑鼠的動作
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
				//opera.SetTopLeft((opera.GetLeft() + 6), opera.GetTop());
				opera.SetTopLeft((opera.GetLeft() + 6), opera.GetTop());
				opera.set_center(opera.get_center_x() + 6, opera.get_center_y());
			}
		}

		if ((point.y < 736)) {
			if (opera.get_center_y() > 686) {
				//opera.SetTopLeft(opera.GetLeft(), (opera.GetTop() - 6));
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

}


void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnShow()
{
	show_text();
	show_img();
}

void CGameStateRun::show_img() {
	background.ShowBitmap();
	character.ShowBitmap();
	opera.ShowBitmap();
	goal.ShowBitmap();
	for (int i = 0; i < 100; i++) {
		energy[i].ShowBitmap();
	}

	//if(monster.size()>0){
		for (int i = 0;i < 30; i++) {
			monster[i].ShowBitmap();
		}
	//}
}

void CGameStateRun::show_text() {

}

void CGameStateRun::background_move() {

	if (background.GetLeft() > character.GetLeft()) { //character->item
		if ((opera.GetLeft() - 437) > 0) { //turn right
			background.SetTopLeft(background.GetLeft() - int((opera.GetLeft() - 437)*0.2), background.GetTop() - int((opera.GetTop() - 682)*0.2));
		}
		else {
			background.SetTopLeft(background.GetLeft(), background.GetTop() - int((opera.GetTop() - 682)*0.2));

		}
	}
	else if (background.GetLeft() + background.GetWidth() < character.GetLeft() + character.GetWidth()) { //item->character
		if ((opera.GetLeft() - 437) < 0) { //turn left
			background.SetTopLeft(background.GetLeft() - int((opera.GetLeft() - 437)*0.2), background.GetTop() - int((opera.GetTop() - 682)*0.2));

		}
		else {
			background.SetTopLeft(background.GetLeft(), background.GetTop() - int((opera.GetTop() - 682)*0.2));

		}
	}
	else if (background.GetTop() > character.GetTop()) { //character->item
		if ((opera.GetTop()) > 682) { //turn right
			background.SetTopLeft(background.GetLeft() - int((opera.GetLeft() - 437)*0.2), background.GetTop() - int((opera.GetTop() - 682)*0.2));
		}
		else {
			background.SetTopLeft(background.GetLeft() - int((opera.GetLeft() - 437)*0.2), background.GetTop());

		}
	}
	else if (background.GetTop() + background.GetHeight() < character.GetTop() + character.GetHeight()) { //character->item
		if ((opera.GetTop()) < 682) { //turn right
			background.SetTopLeft(background.GetLeft() - int((opera.GetLeft() - 437)*0.2), background.GetTop() - int((opera.GetTop() - 682)*0.2));
		}
		else {
			background.SetTopLeft(background.GetLeft() - int((opera.GetLeft() - 437)*0.2), background.GetTop());

		}
	}
	else {
		background.SetTopLeft(background.GetLeft() - int((opera.GetLeft() - 437)*0.2), background.GetTop() - int((opera.GetTop() - 682)*0.2));

	}



}

void CGameStateRun::item_move(CMovingBitmap &item) {
	int x = item.GetLeft() - int((opera.GetLeft() - 437)*0.2);
	int y = item.GetTop() - int((opera.GetTop() - 682)*0.2);

	int std_x = background.GetLeft();
	int std_w = background.GetWidth();


	if (background.GetLeft() >= character.GetLeft()) { //character->item
		if (opera.GetLeft()  > 437) { //turn right
			item.SetTopLeft(item.GetLeft() - int((opera.GetLeft() - 437)*0.2), item.GetTop() - int((opera.GetTop() - 682)*0.2));
		}
		else {
			item.SetTopLeft(item.GetLeft(), item.GetTop() - int((opera.GetTop() - 682)*0.2));
		}
	}
	else if (background.GetLeft() + background.GetWidth() <= character.GetLeft() + character.GetWidth()) { //item->character
		if ((opera.GetLeft()) < 437) { //turn left
			item.SetTopLeft(item.GetLeft() - int((opera.GetLeft() - 437)*0.2), item.GetTop() - int((opera.GetTop() - 682)*0.2));
		}
		else {
			item.SetTopLeft(item.GetLeft(), item.GetTop() - int((opera.GetTop() - 682)*0.2));
		}
	}

	else if (background.GetTop() >= character.GetTop()) { //character->item
		if (opera.GetTop() > 682) { //turn right
			item.SetTopLeft(item.GetLeft() - int((opera.GetLeft() - 437)*0.2), item.GetTop() - int((opera.GetTop() - 682)*0.2));
		}
		else {
			item.SetTopLeft(item.GetLeft() - int((opera.GetLeft() - 437)*0.2), item.GetTop());
		}
	}
	else if (background.GetTop() + background.GetHeight() <= character.GetTop() + character.GetHeight()) { //item->character
		if ((opera.GetLeft()) > 682) { //turn left
			item.SetTopLeft(item.GetLeft() - int((opera.GetLeft() - 437)*0.2), item.GetTop() - int((opera.GetTop() - 682)*0.2));
		}
		else {
			item.SetTopLeft(item.GetLeft() - int((opera.GetLeft() - 437)*0.2), item.GetTop());
		}
	}
	else {

		item.SetTopLeft(item.GetLeft() - int((opera.GetLeft() - 437)*0.2), item.GetTop() - int((opera.GetTop() - 682)*0.2));

	}


}

void CMovingBitmap::item_hit(CMovingBitmap &character,CMovingBitmap &item) {
	if (IsOverlap(character, item)) {
		item.SetFrameIndexOfBitmap(1);
	}
}

void CGameStateRun::monster_move(CMovingBitmap &monster) {

	int ax = int((monster.GetLeft() - character.GetLeft())*0.01), ay = int((monster.GetTop() - character.GetTop())*0.01);

	if (monster.GetLeft() < character.GetLeft()) {
		ax = 1;
	}
	else if (monster.GetLeft() > character.GetLeft()) {
		ax = -1;
	}

	if (monster.GetTop() < character.GetTop()) {
		ay = 1;
	}
	else if (monster.GetTop() > character.GetTop()) {
		ay = -1;
	}

	
	monster.SetTopLeft(monster.GetLeft() + ax, monster.GetTop() + ay);
	monster.set_center(monster.GetLeft()+45,monster.GetTop()+57);
};

void CGameStateRun::random_born_item(vector<CMovingBitmap> &item, vector<string> str, vector<int>rgb) {

	int min = -1450;
	int max = 1450;
	int tail = item.size();

	item.push_back(CMovingBitmap());
	item[tail].LoadBitmapByString(str, RGB(rgb[0], rgb[1], rgb[2]));
	/* 產生 [min , max] 的整數亂數 */
	int x = rand() % (max - min + 1) + min;
	int y = rand() % (max - min + 1) + min;
	item[tail].SetTopLeft(x, y);
	item[tail].set_center(x + 45, y + 57);


}