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
	//background_move(background2);

	for (int i = 0; i < 100; i++) {
		item_move(energy[i]);
	}
	//item_move(goal);
	
}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{
	background.LoadBitmapByString({"Resources/background.bmp"});
	background.SetTopLeft(0, 0);
	background2.LoadBitmapByString({ "Resources/background.bmp" });
	background2.SetTopLeft(0, 4000);

	character.LoadBitmapByString({ "Resources/witch.bmp" },RGB(255,255,255));
	character.SetTopLeft(481, 252);

	opera.LoadBitmapByString({ "Resources/operator.bmp" }, RGB(105, 106, 106));
	opera.SetTopLeft(437, 682);
	opera.set_center(437 + 54, 682 + 54);//491 , 736

	goal.LoadBitmapByString({ "Resources/goal.bmp" }, RGB(255, 255, 255));
	goal.SetTopLeft(107, 82);


	srand((unsigned)time(NULL));
	/* 指定亂數範圍 */
	int min = 0;
	int max = 1100;
	for (int i = 0; i < 100; i++) {
		energy[i].LoadBitmapByString({ "Resources/energy.bmp", "Resources/energy_ignore.bmp" }, RGB(255, 255, 255));
		/* 產生 [min , max] 的整數亂數 */
		int x = rand() % (max - min + 1) + min;
		int y = rand() % (max - min + 1) + min;
		energy[i].SetTopLeft(x, y);
	}
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_UP) {
		character.SetTopLeft(character.GetLeft(), character.GetTop() - 15);
		//character.Height;
	}

	if (nChar == VK_DOWN) {
		character.SetTopLeft(character.GetLeft(), character.GetTop() + 15);
		//character.Height;
	}

	if (nChar == VK_RIGHT) {
		character.SetTopLeft(character.GetLeft() + 15, character.GetTop());
		//character.Height;
	}

	if (nChar == VK_LEFT) {
		character.SetTopLeft(character.GetLeft() - 15, character.GetTop());
		//character.Height;
	}
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
				opera.set_center(opera.get_center_x()-6, opera.get_center_y());
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
				opera.set_center(opera.get_center_x(), opera.get_center_y()-6);
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
	show_img();
	show_text();
}

void CGameStateRun::show_img() {
	background.ShowBitmap();
	character.ShowBitmap();
	opera.ShowBitmap();
	goal.ShowBitmap();
	for (int i = 0; i < 100; i++) {
		energy[i].ShowBitmap();
	}
}

void CGameStateRun::show_text() {
	
}

void CGameStateRun::background_move() {

	//if (item == background) {
	
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
			if ((opera.GetTop() ) > 682) { //turn right
				background.SetTopLeft(background.GetLeft() - int((opera.GetLeft() - 437)*0.2), background.GetTop() - int((opera.GetTop() - 682)*0.2));
			}
			else {
				background.SetTopLeft(background.GetLeft() - int((opera.GetLeft() - 437)*0.2), background.GetTop() );

			}
		}
		else if (background.GetTop()+background.GetHeight() < character.GetTop()+character.GetHeight()) { //character->item
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
		if ((opera.GetLeft() - 437) > 0) { //turn right
			item.SetTopLeft(item.GetLeft() - int((opera.GetLeft() - 437)*0.2), item.GetTop() - int((opera.GetTop() - 682)*0.2));
		}
		else {
			item.SetTopLeft(item.GetLeft(), item.GetTop() - int((opera.GetTop() - 682)*0.2));
		}
	}
	else if (background.GetLeft() + background.GetWidth() <= character.GetLeft() + character.GetWidth()) { //item->character
		if ((opera.GetLeft() - 437) < 0) { //turn left
			item.SetTopLeft(item.GetLeft() - int((opera.GetLeft() - 437)*0.2), item.GetTop() - int((opera.GetTop() - 682)*0.2));
		}
		else {
			item.SetTopLeft(item.GetLeft(), item.GetTop() - int((opera.GetTop() - 682)*0.2));
		}
	}

	else if (background.GetTop() >= character.GetTop()) { //character->item
		if (opera.GetTop()  > 682) { //turn right
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
		//goal.SetTopLeft(goal.GetLeft() - int((opera.GetLeft() - 437)*0.2), goal.GetTop() - int((opera.GetTop() - 682)*0.2));

	}

	if (451 <= x && x <= 511 && 222 <= y && y <= 282) {
		item.SetFrameIndexOfBitmap(1);
	}

}
