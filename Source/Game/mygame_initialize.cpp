#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"

using namespace game_framework;
/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲開頭畫面物件
/////////////////////////////////////////////////////////////////////////////

CGameStateInit::CGameStateInit(CGame *g) : CGameState(g)
{
}

void CGameStateInit::OnInit()
{
	logo.LoadBitmapByString({ "Resources/health_ui/health_ui_0.bmp" }, RGB(255, 255, 255));
	logo.SetTopLeft(510, 0);

	select1.LoadBitmapByString({ "Resources/UI/select_bg.bmp" }, RGB(255, 255, 255));
	select1.SetTopLeft(100, 390);

	select2.LoadBitmapByString({ "Resources/UI/select_bg.bmp" }, RGB(255, 255, 255));
	select2.SetTopLeft(select1.GetLeft() + select1.GetWidth() + 50, 390);

	check_blank1.LoadBitmapByString({ "Resources/UI/check_blank.bmp" }, RGB(255, 255, 255));
	check_blank1.SetTopLeft(100+20, 400);

	check_blank2.LoadBitmapByString({ "Resources/UI/check_blank.bmp" }, RGB(255, 255, 255));
	check_blank2.SetTopLeft(select1.GetLeft() + select1.GetWidth() + 50 + 20, 400);

	check1.LoadBitmapByString({ "Resources/ignore.bmp", "Resources/UI/check.bmp" }, RGB(255, 255, 255));
	check1.SetTopLeft(100 + 20, 400);

	check2.LoadBitmapByString({ "Resources/ignore.bmp", "Resources/UI/check.bmp" }, RGB(255, 255, 255));
	check2.SetTopLeft(select1.GetLeft() + select1.GetWidth() + 50 + 20, 400);

	select_scene1.LoadBitmapByString({ "Resources/background/Purple Nebula/init_Purple_Nebula_08.bmp" });
	select_scene1.SetTopLeft(select1.GetLeft() + 100, 450);

	select_scene2.LoadBitmapByString({ "Resources/background/Blue Nebula/init_Blue_Nebula_08.bmp" });
	select_scene2.SetTopLeft(select_scene1.GetLeft() + select_scene1.GetWidth() + 250+15, 450);

	play_bg.LoadBitmapByString({ "Resources/UI/play_bg.bmp" }, RGB(255, 255, 255));
	play_bg.SetTopLeft(350, 780);

	play.LoadBitmapByString({ "Resources/UI/play.bmp" }, RGB(255, 255, 255));
	play.SetTopLeft(375, 790);
	//
	// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
	//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
	//
	ShowInitProgress(0, "Start Initialize...");	// 一開始的loading進度為0%
	//
	// 開始載入資料
	//
	//Sleep(1000);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
	//
	// 此OnInit動作會接到CGameStaterRun::OnInit()，所以進度還沒到100%
	//
}

void CGameStateInit::OnBeginState()
{
}

void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{

}

void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (nFlags == TRUE) {
		if (select1.GetLeft() <= point.x && point.x <= select1.GetLeft() + select1.GetWidth()
			&& select1.GetTop() <= point.y && point.y <= select1.GetTop() + 300) {
			check1.SetFrameIndexOfBitmap(1);
			check2.SetFrameIndexOfBitmap(0);
			set_init_background_value(0);
		}
		else if (select2.GetLeft() <= point.x && point.x <= select2.GetLeft() + select2.GetWidth()
			&& select2.GetTop() <= point.y && point.y <= select2.GetTop() + 300) {
			check2.SetFrameIndexOfBitmap(1);
			check1.SetFrameIndexOfBitmap(0);
			set_init_background_value(1);
		}

		if (play_bg.GetLeft() <= point.x && point.x <= play_bg.GetLeft() + play_bg.GetWidth()
			&& play_bg.GetTop() <= point.y && point.y <= play_bg.GetTop() + 130) {
			GotoGameState(GAME_STATE_RUN);
		}
	}
}

void CGameStateInit::OnShow()
{
	CDC *pdc = CDDraw::GetBackCDC();

	CTextDraw::ChangeFontLog(pdc, 105, "Modern No. 20", RGB(255, 255, 255), 1000);
	CTextDraw::Print(pdc, 165, 130, "Survivor.io");

	CTextDraw::ChangeFontLog(pdc, 25, "Ink Free", RGB(255, 255, 255), 400);
	CTextDraw::Print(pdc, 320, 300, "Made By - Turtle & Sunny");

	CTextDraw::ChangeFontLog(pdc, 25, "Ink Free", RGB(255, 255, 255), 200);
	CTextDraw::Print(pdc, 185, 730, "Please select the scene which do you like");

	CDDraw::ReleaseBackCDC();

	select1.ShowBitmap();
	select2.ShowBitmap();
	check_blank1.ShowBitmap();
	check_blank2.ShowBitmap();
	check1.ShowBitmap();
	check2.ShowBitmap();
	select_scene1.ShowBitmap();
	select_scene2.ShowBitmap();
	play_bg.ShowBitmap();
	play.ShowBitmap();
	
}
