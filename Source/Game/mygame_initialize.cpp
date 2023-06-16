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
// 這個class為遊戲的遊戲開頭畫面物件
/////////////////////////////////////////////////////////////////////////////

CGameStateInit::CGameStateInit(CGame *g) : CGameState(g)
{
}

void CGameStateInit::OnInit()
{

	character_logo.LoadBitmapByString({ "Resources/character/d1.bmp", "Resources/character/d2.bmp", "Resources/character/d3.bmp",
										"Resources/character/d4.bmp", "Resources/character/d5.bmp", "Resources/character/d6.bmp" }, RGB(255, 255, 255));
	character_logo.SetTopLeft(30, 880);
	character_logo.SetAnimation(100, false);

	comunicate_logo.LoadBitmapByString({ "Resources/character/comunicate.bmp","Resources/character/comunicate_2.bmp" }, RGB(255, 255, 255));
	comunicate_logo.SetTopLeft(80, 800);

	com_bg.LoadBitmapByString({ "Resources/UI/com_bg.bmp" },RGB(255,255,255));
	com_bg.SetTopLeft(70, 305);

	com_no.LoadBitmapByString({ "Resources/UI/no.bmp" ,"Resources/UI/no_2.bmp" }, RGB(255, 255, 255));
	com_no.SetTopLeft(860, 320);

	CAudio::Instance()->Load(AUDIO_MenuSelect, "Resources/Audio/Select.wav");
	CAudio::Instance()->Load(AUDIO_GameStage, "Resources/Audio/Goblins_Dance_(Battle).wav");
	CAudio::Instance()->Load(AUDIO_GameBoss, "Resources/Audio/battle.wav");
	CAudio::Instance()->Load(AUDIO_GameOver, "Resources/Audio/Goblins_Dance_(Battle).wav");
	CAudio::Instance()->Load(AUDIO_Attack, "Resources/Audio/bubbles.wav");

	CAudio::Instance()->Play(AUDIO_MenuSelect, true);

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
	play_bg.SetTopLeft(1065 / 2 - play_bg.GetWidth() / 2, 780);

	play.LoadBitmapByString({ "Resources/UI/play.bmp","Resources/UI/play_s.bmp" }, RGB(255, 255, 255));
	play.SetTopLeft((play_bg.GetLeft() + play_bg.GetWidth()/2) - play.GetWidth()/2+5, 790);
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

void CGameStateInit::OnMouseMove(UINT nFlags, CPoint point)
{
	
	if (play.GetFrameSizeOfBitmap() == 2 ) {

		if (isSelect(true, point, play) || isSelect(true, point, play_bg)) {
			play.SetFrameIndexOfBitmap(1);
		}
		else {
			play.SetFrameIndexOfBitmap(0);
		}
	}

	if (comunicate_logo.GetFrameSizeOfBitmap() == 2) {

		if (isSelect(true, point, comunicate_logo)) {
			comunicate_logo.SetFrameIndexOfBitmap(1);
		}
		else {
			comunicate_logo.SetFrameIndexOfBitmap(0);
		}
	}

	if (show_text == 1 && com_no.GetFrameSizeOfBitmap() == 2) {

		if (isSelect(true, point, com_no)) {
			com_no.SetFrameIndexOfBitmap(1);
		}
		else {
			com_no.SetFrameIndexOfBitmap(0);
		}
	}
}


void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (nFlags == TRUE && show_text == 0) {
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
			if (get_init_background_value() == 0 || get_init_background_value() ==1) {
				CAudio::Instance()->Stop(AUDIO_MenuSelect);
				CAudio::Instance()->Play(AUDIO_GameStage, true);
				GotoGameState(GAME_STATE_RUN);
			}
		}
	}

	if (comunicate_logo.GetFrameSizeOfBitmap() == 2) {

		if (isSelect(nFlags, point, comunicate_logo)) {
			show_text = 1;
		}

	}
	if (com_no.GetFrameSizeOfBitmap() == 2) {

		if (show_text == 1 && isSelect(nFlags, point, com_no)) {
			show_text = 0;
		}
	}
}

void CGameStateInit::OnShow()
{
	CDC *pdc = CDDraw::GetBackCDC();

	CTextDraw::ChangeFontLog(pdc, 145, "monogram", RGB(255, 255, 255), 1000);
	CTextDraw::Print(pdc, 95, 130, "Survivor.io");	//Vivaldi 

	CTextDraw::ChangeFontLog(pdc, 25, "monogram", RGB(255, 255, 255), 400);
	CTextDraw::Print(pdc, 360, 300, "Made By - Turtle & Sunny");

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
	comunicate_logo.ShowBitmap();
	character_logo.ShowBitmap();

	if (show_text == 1) {
		com_bg.ShowBitmap();
		com_no.ShowBitmap();
		CDC *pdc2 = CDDraw::GetBackCDC();

		CTextDraw::ChangeFontLog(pdc, 35, "monogram", RGB(255, 255, 255), 40);
		CTextDraw::Print(pdc2, 260, 330, "Welcome to the survivor.io !");

		CTextDraw::ChangeFontLog(pdc, 21, "monogram", RGB(255, 255, 255), 40);
		CTextDraw::Print(pdc2, 120, 420, "Select your preferred background and click 'Play' to start the game");

		CTextDraw::ChangeFontLog(pdc, 21, "monogram", RGB(255, 255, 255), 40);
		CTextDraw::Print(pdc2, 120, 460, "Control the character's movement by dragging the  bubble with  your");

		CTextDraw::ChangeFontLog(pdc, 21, "monogram", RGB(255, 255, 255), 40);
		CTextDraw::Print(pdc2, 120, 480, "mouse.");

		CTextDraw::ChangeFontLog(pdc, 21, "monogram", RGB(255, 255, 255), 40);
		CTextDraw::Print(pdc2, 120, 530, "Collect gems to fill up the progress bar ,choose the desired weapon");

		CTextDraw::ChangeFontLog(pdc, 21, "monogram", RGB(255, 255, 255), 40);
		CTextDraw::Print(pdc2, 120, 570, "Face BOSS challenges every 40 seconds");

		CTextDraw::ChangeFontLog(pdc, 21, "monogram", RGB(255, 255, 255), 40);
		CTextDraw::Print(pdc2, 120, 630, "If you want to activate the developer's special invincibility mode, ");

		CTextDraw::ChangeFontLog(pdc, 21, "monogram", RGB(255, 255, 255), 40);
		CTextDraw::Print(pdc2, 120, 650, "click on the computer icon in the top right corner.  A blue screen ");


		CTextDraw::ChangeFontLog(pdc, 21, "monogram", RGB(255, 255, 255), 40);
		CTextDraw::Print(pdc2, 120, 670, "indicates the mode is enabled ");

		CTextDraw::ChangeFontLog(pdc, 40, "monogram", RGB(255, 255, 255), 40);
		CTextDraw::Print(pdc2, 180, 800, "Enjoy your gameplay experience!");

		CDDraw::ReleaseBackCDC();
	}
	

}

bool CGameStateInit::isSelect(UINT nFlags, CPoint point, CMovingBitmap &item) {
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