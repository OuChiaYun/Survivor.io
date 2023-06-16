#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Game/CGamestage_all.h"
#include "../Library/gamecore.h"
#include "mygame.h"

using namespace game_framework;

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的結束狀態(Game Over)
/////////////////////////////////////////////////////////////////////////////

CGameStateOver::CGameStateOver(CGame *g): CGameState(g)
{
}

void CGameStateOver::OnMove()
{
	//GotoGameState(GAME_STATE_INIT);
}

void CGameStateOver::OnBeginState()
{
	
}

void CGameStateOver::OnLButtonDown(UINT nFlags, CPoint point) {

	if (again.GetFrameSizeOfBitmap() == 2) {

		if (isSelect(nFlags, point, again)) {
			GotoGameState(GAME_STATE_INIT);
		}

	}
};
void CGameStateOver::OnMouseMove(UINT nFlags, CPoint point) {

	if (again.GetFrameSizeOfBitmap() == 2) {

		if (isSelect(TRUE, point, again)) {
			again.SetFrameIndexOfBitmap(1);
		}
		else {
			again.SetFrameIndexOfBitmap(0);
		}

	}
	
}

void CGameStateOver::OnInit()
{
	//
	// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
	//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
	//
	ShowInitProgress(66, "Initialize...");	// 接個前一個狀態的進度，此處進度視為66%
	//
	// 開始載入資料
	//
	Sleep(1000);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
	//
	// 最終進度為100%
	//
	ShowInitProgress(100, "OK!");

	Sleep(1000);

	victory.LoadBitmapByString({ "Resources/UI/victory.bmp" }, RGB(255, 255, 255));
	victory.SetTopLeft(110, 290);
	die.LoadBitmapByString({ "Resources/UI/died.bmp" }, RGB(255, 255, 255));//255,247,248
	die.SetTopLeft(100, 300);

	again.LoadBitmapByString({ "Resources/UI/again.bmp","Resources/UI/again2.bmp" }, RGB(255, 255, 255));
	again.SetTopLeft(400, 100);
	again.SetFrameIndexOfBitmap(0);
}

void CGameStateOver::OnShow()
{
	again.ShowBitmap();


	if (get_victory_value() == 1) {
		victory.ShowBitmap();	
	}
	if (get_victory_value() == 0) {
		die.ShowBitmap();
	}

	CDC *pdc = CDDraw::GetBackCDC();

	CTextDraw::ChangeFontLog(pdc, 70, "Modern No. 20", RGB(158, 45, 118), 60);
	CTextDraw::Print(pdc, 350, 490, "TIME");

	CTextDraw::ChangeFontLog(pdc, 40, "Modern No. 20", RGB(255, 255, 255), 60);
	CTextDraw::Print(pdc, 385, 590,"[ "+get_show_time()+" ]");

	CTextDraw::ChangeFontLog(pdc, 32, "Modern No. 20", RGB(158, 45, 118), 60);
	CTextDraw::Print(pdc, 310, 690, "KILL MONSTER ");

	CTextDraw::ChangeFontLog(pdc, 40, "Modern No. 20", RGB(255, 255, 255), 60);
	CTextDraw::Print(pdc, 310, 740,"[ "+ get_dead_number()+" ]");

	CTextDraw::ChangeFontLog(pdc, 30, "Modern No. 20", RGB(158, 45, 118), 60);
	CTextDraw::Print(pdc, 340, 850, "USE WEAPON ");

	CTextDraw::ChangeFontLog(pdc, 35, "Modern No. 20", RGB(255, 255, 255), 60);
	CTextDraw::Print(pdc, 310, 900,"[ "+ get_weapon_name()+" ]");


	CDDraw::ReleaseBackCDC();
}


/////////

bool CGameStateOver::isSelect(UINT nFlags, CPoint point, CMovingBitmap &item) {

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