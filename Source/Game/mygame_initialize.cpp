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
	//
	// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
	//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
	//
	ShowInitProgress(0, "Start Initialize...");	// 一開始的loading進度為0%
	//
	// 開始載入資料
	//
	Sleep(1000);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
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
		if (select_scene1.GetLeft() <= point.x && point.x <= select_scene1.GetLeft() + select_scene1.GetWidth()
			&& select_scene1.GetTop() <= point.y && point.y <= select_scene1.GetTop() + 300) {
			selected1.SetFrameIndexOfBitmap(1);
			Sleep(1000);
		}
		else {
			selected1.SetFrameIndexOfBitmap(0);
		}
	}
	background_select = 1;
	GotoGameState(GAME_STATE_RUN);		// 切換至GAME_STATE_RUN
}

void CGameStateInit::OnShow()
{
	logo.LoadBitmapByString({  "Resources/health_ui/health_ui_0.bmp" }, RGB(255, 255, 255));
	logo.SetTopLeft(510, 0);
	logo.ShowBitmap();
	
	select_scene1.LoadBitmapByString({ "Resources/select_background.bmp" });
	select_scene1.SetTopLeft(10, 300);
	select_scene1.ShowBitmap();

	select_scene2.LoadBitmapByString({ "Resources/select_Hills.bmp" });
	select_scene2.SetTopLeft(350, 300);
	select_scene2.ShowBitmap();

	selected1.LoadBitmapByString({ "Resources/ignore.bmp", "Resources/selected.bmp" }, RGB(255, 255, 255));
	selected1.SetTopLeft(10, 300);
	selected1.ShowBitmap();

	selected2.LoadBitmapByString({ "Resources/ignore.bmp", "Resources/selected.bmp" }, RGB(255, 255, 255));
	selected2.SetTopLeft(350, 300);
	selected2.ShowBitmap();
}
