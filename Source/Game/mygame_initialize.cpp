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
// ?o??class???C?????C???}?Y?e??????
/////////////////////////////////////////////////////////////////////////////

CGameStateInit::CGameStateInit(CGame *g) : CGameState(g)
{

}

void CGameStateInit::OnInit()
{
	//
	// ?????h??AOnInit???J???????n???h????C????K???C?????H
	//     ???????@??A?C???|?X?{?uLoading ...?v?A???Loading???i??C
	//
	ShowInitProgress(0, "Start Initialize...");	// ?@?}?l??loading?i???0%
	Sleep(200);

	load_background();

	ShowInitProgress(66, "Initialize...");
	Sleep(200);
	//
	// ??OnInit??@?|????CGameStaterRun::OnInit()?A??H?i????S??100%
	//
}

void CGameStateInit::OnBeginState()
{

}

void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	GotoGameState(GAME_STATE_RUN);		// ??????GAME_STATE_RUN
}

void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
{
}

void CGameStateInit::OnShow()
{
	background.ShowBitmap();
	draw_text();
}

void CGameStateInit::load_background() {
	background.LoadBitmapByString({ "resources/initialize_background.bmp" });
	background.SetTopLeft(0, 0);
}

void CGameStateInit::draw_text() {
	CDC *pDC = CDDraw::GetBackCDC();
	CFont* fp;

	/* Print title */
	CTextDraw::ChangeFontLog(pDC, fp, 26, "微軟正黑體", RGB(255, 255, 255));
	CTextDraw::Print(pDC, 79, 228, "Game Framework Practice");

	/* Print info */
	CTextDraw::ChangeFontLog(pDC, fp, 20, "微軟正黑體", RGB(255, 255, 255));
	CTextDraw::Print(pDC, 182, 431, "Press any key to start");

	CDDraw::ReleaseBackCDC();
}