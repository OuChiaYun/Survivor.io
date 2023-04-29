# Leistungsstarkes Game Framework


目前的新開發方式

CGamestage_all.h
| 負責統一include 所有關卡class的標頭檔


CGamestage1
| 普通關卡，非boss的關卡

CGamestageBoss1
| 負責boss1關卡內容，以此類推

CGamestageSelect
| 選擇介面

使用方式 : 

void CGameStateRun::OnMove()							// 移動遊戲元素
{
	b2.OnMove();
	/*
	if (select_stage.show == 1) {
		select_stage.OnMove();
	}else if (energy_bar.get_energy() == 25) {
		b1.OnMove();
	}
	else {
		t1.OnMove();
	}
	*/

}

基本上，mygamerun 是一個最主要的gameloop，然後我們會呼叫想要顯示的class的對應功能的function，ex OnMove()，這邊呼叫b2.OnMove()代表說會出現的是b2(也就是boss2)裡面我們會想呈的OnMove內容，類似於我們進一個關卡時會先設置一個 if (state == 2) 然後只移動boss2 和一寫主角等等的物件，但這邊我們把它包進了class，故只要再需要第二關時直接呼叫b2.OnMove()就行，以此類推




會需要同步數據的物件 : 

會先在mygame.h裡宣告，然後在void set_share_obj_data(CMovingBitmap &tmp_background, CMovingBitmap &tmp_character,
			CMovingBitmap &tmp_opera, CMovingBitmap &tmp_blood_bar, CMovingBitmap &tmp_energy_bar, vector <CMovingBitmap> &tmp_dart, vector<CMovingBitmap> &tmp_bullet);
裡將需要被同步資料的obj 傳入

在class里設置指標，指向mygame裡宣告的物件，有增加的話要記的修改set_share_obj_data裡的內容

ex.

set_share_obj_data(){
	p_background = &tmp_background;
	p_character = &tmp_character;
	p_opera = &tmp_opera;
	p_blood_bar = &tmp_blood_bar;
	p_energy_bar = &tmp_energy_bar;
	p_dart = &tmp_dart;
	p_bullet = &tmp_bullet;
/////取得mygame裡的物件記憶體位址

	background = tmp_background;
	character = tmp_character;
	opera = tmp_opera;
	blood_bar = tmp_blood_bar;
	energy_bar = tmp_energy_bar;
	dart = tmp_dart;
	bullet = tmp_bullet;
}

/////賦值


然後我們會有get_data() 和 share_data() ，負責將個別class數據與mygame的物件同步，故當可能對資料做變動時，先呼叫get_data將mygame資料放入個別關卡物件，處理完資料再呼叫share_data() 將更新後的資料放入 mygame的物件


get_data() {

	background = *p_background;
	character = *p_character;
	opera = *p_opera;
	blood_bar = *p_blood_bar;
	energy_bar = *p_energy_bar;
	dart = *p_dart;
	bullet = *p_bullet;   => *p_xxxxx 裡面儲存的是 mygame 裡的物件內容，將這些物件內容放入關卡
}

share_data() {

	*p_background = background;
	*p_character = character;
	*p_opera = opera;
	*p_blood_bar = blood_bar;
	*p_energy_bar = energy_bar;
	*p_dart = dart;
	*p_bullet = bullet;  => *p_xxxxx 裡面儲存的是 mygame 裡的物件，將關卡物件內容放入mygame 物件的記憶體位置

};
	

	gat_data();


	background_move();
	boss2_move();

	dart_all(200);
	bullet_move(bullet);
	born_bullet(bullet, { "Resources/bullet.bmp" }, { 255, 255, 255 });
	bullet_erase(bullet);


	share_data();

=> 基本上會以這樣的形式出現