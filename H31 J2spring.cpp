//J2 春休み課題
//J1714 小山裕

//使用素材
//ぴぽや倉庫 https://pipoya.net/sozai/
//びたちー素材館 http://www.vita-chi.net/sozai1.htm
//魔王魂 https://maoudamashii.jokersounds.com/


#include "Header.h"
#include "DXLib.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetGraphMode(640, 480, 16);					// 画面モードのセット
	SetMainWindowText("HEROES");			//タイトルバーの変更
	ChangeWindowMode(winMode);					// ウィンドウモードで起動
	if (DxLib_Init() == -1) { return -1; }      // ＤＸライブラリ初期化処理
	InitGrp();									// 画像データのロード
	InitSE();									// 効果音データのロード
	PlayMusic(-1);								
	
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0 && exitFlag == 0) {
		Input();			// 入力の感知
		ClearDrawScreen();	// 画面をクリアする
		switch (scene) {
		case _TITLE:		Title();	break;
		case _SELECT:		Select();	break;
		case _BATTLE:	OneBattle();	break;
		}
	}
	DxLib_End();			// ＤＸライブラリ使用の終了処理
	return 0;				// ソフトの終了
}

//画像初期化処理
void InitGrp()
{
	//hosoku_color = GetColor(0, 0, 0);
	MessageFontColor = GetColor(255, 255, 255);
	title_font = CreateFontToHandle(NULL, 64, -1, DX_FONTTYPE_ANTIALIASING_EDGE);
	select_font[_HEAD] = CreateFontToHandle(NULL, 64, -1, DX_FONTTYPE_ANTIALIASING_EDGE);
	select_font[_CHOICES] = (select_font[_CURSOR] = CreateFontToHandle(NULL, 32, -1, DX_FONTTYPE_ANTIALIASING_EDGE));
	message_font = CreateFontToHandle(NULL, 20, -1, DX_FONTTYPE_ANTIALIASING_EDGE);
	BackGround[_TITLE] = LoadGraph("Data/Graphic/BackGround/title_bg.jpg");
	BackGround[_SELECT] = LoadGraph("Data/Graphic/BackGround/select_bg.jpg");
	grp_Grass = LoadGraph("Data/Graphic/Field/grass.bmp");
	grp_Tuta  = LoadGraph("Data/Graphic/Field/tuta.png");

	//自軍画像
	grp_Chara[_FRONT][PUTARO] = LoadGraph("Data/Graphic/MyArmy/pu-taro.png");
	grp_Chara[_FRONT][SOLDIER_01] = grp_Chara[_FRONT][SOLDIER_02] = LoadGraph("Data/Graphic/MyArmy/fri_soldier.png");
	grp_Chara[_FRONT][FENCER] = LoadGraph("Data/Graphic/MyArmy/fri_fencer.png");
	grp_Chara[_FRONT][WITCH] = LoadGraph("Data/Graphic/MyArmy/fri_witch.png");
	grp_Chara[_FRONT][WARRIOR] = LoadGraph("Data/Graphic/MyArmy/fri_warrior.png");
	grp_Chara[_FRONT][HEROINE] = LoadGraph("Data/Graphic/MyArmy/heroine.png");

	//敵軍画像
	grp_Enemy[KYU_01] = grp_Enemy[KYU_02] = LoadGraph("Data/Graphic/Enemy/kyu.png");
	grp_Enemy[GHOST_01] = grp_Enemy[GHOST_02] = LoadGraph("Data/Graphic/Enemy/ghost.png");
	grp_Enemy[E_SOLDIER_01] = grp_Enemy[E_SOLDIER_02] = grp_Enemy[E_SOLDIER_03] = grp_Enemy[E_SOLDIER_04] = LoadGraph("Data/Graphic/Enemy/ene_soldier.png");
	grp_Enemy[E_WITCH_01] = grp_Enemy[E_WITCH_02] = LoadGraph("Data/Graphic/Enemy/ene_witch.png");
	grp_Enemy[SATAN] = LoadGraph("Data/Graphic/Enemy/Satan.png");

	//サイコロとウインドウ
	Dices[0] = LoadGraph("Data/Graphic/Window&Icon/Dice_one.png");
	Dices[1] = LoadGraph("Data/Graphic/Window&Icon/Dice_two.png");
	Dices[2] = LoadGraph("Data/Graphic/Window&Icon/Dice_three.png");
	Dices[3] = LoadGraph("Data/Graphic/Window&Icon/Dice_four.png");
	Dices[4] = LoadGraph("Data/Graphic/Window&Icon/Dice_five.png");
	Dices[5] = LoadGraph("Data/Graphic/Window&Icon/Dice_six.png");
	grp_Window = LoadGraph("Data/Graphic/Window&Icon/Window.png");
		
}

//効果音初期化
void InitSE()
{
	se.walking = LoadSoundMem("Data/SE/walk.mp3");
	se.kettei = LoadSoundMem("Data/SE/kettei.mp3");
	se.drum = LoadSoundMem("Data/SE/sunea.mp3");
}

void PlayMusic(int Judge) {

	switch (scene) {
	case _TITLE:	PlayMusic("Data/Sound/theme.mp3", DX_PLAYTYPE_LOOP);	break;
	case _SELECT:
	case _BATTLE:	
		if(Judge == 1)	PlayMusic("Data/Sound/field.mp3", DX_PLAYTYPE_BACK);
		else if(Judge == 0)	PlayMusic("Data/Sound/lose.mp3", DX_PLAYTYPE_BACK);
		else PlayMusic("Data/Sound/field.mp3", DX_PLAYTYPE_LOOP);
		break;
	}
}

// フルスクリーンの切り替え -------------------------------------------------------------------- //
void FullScreen(void)
{
	if (winMode == 0) winMode = 1;
	else winMode = 0;
	ChangeWindowMode(winMode);
	InitGrp();
}

//キーボードの入力状態の更新 ---------------------------------------------------- //
void Input(void)
{
	//int padInput = GetJoypadInputState(DX_INPUT_PAD1);
	char keyBuff[256];
	GetHitKeyStateAll(keyBuff);
	// ←キー
	if ( keyBuff[KEY_INPUT_LEFT]) { Key[KEY_INPUT_LEFT] ++; }
	else { Key[KEY_INPUT_LEFT] = 0; }
	// ↑キー
	if ( keyBuff[KEY_INPUT_UP]) { Key[KEY_INPUT_UP] ++; }
	else { Key[KEY_INPUT_UP] = 0; }
	// →キー
	if ( keyBuff[KEY_INPUT_RIGHT]) { Key[KEY_INPUT_RIGHT] ++; }
	else { Key[KEY_INPUT_RIGHT] = 0; }
	// ↓キー
	if ( keyBuff[KEY_INPUT_DOWN]) { Key[KEY_INPUT_DOWN] ++; }
	else { Key[KEY_INPUT_DOWN] = 0; }
	// Zキー
	if ( keyBuff[KEY_INPUT_Z]) { Key[KEY_INPUT_Z] ++; }
	else { Key[KEY_INPUT_Z] = 0; }
	// Xキー
	if ( keyBuff[KEY_INPUT_BACK]) { Key[KEY_INPUT_X] ++; }
	else { Key[KEY_INPUT_X] = 0; }
	// Cキー
	if ( keyBuff[KEY_INPUT_C]) { Key[KEY_INPUT_C] ++; }
	else { Key[KEY_INPUT_C] = 0; }
	// spaceキー
	if ( keyBuff[KEY_INPUT_SPACE]) { Key[KEY_INPUT_SPACE] ++; }
	else { Key[KEY_INPUT_SPACE] = 0; }
	// LShiftキー
	if ( keyBuff[KEY_INPUT_LSHIFT]) { Key[KEY_INPUT_LSHIFT] ++; }
	else { Key[KEY_INPUT_LSHIFT] = 0; }
	// Enterキー
	if ( keyBuff[KEY_INPUT_RETURN]) { Key[KEY_INPUT_RETURN] ++; }
	else { Key[KEY_INPUT_RETURN] = 0; }
	
}

void Title(void)
{
	int x = 215, y = 100, key_x = x - 130, key_y = y + 200;
	int title_color = GetColor(100, 70, 200);
	//int title_font = CreateFontToHandle(NULL, 64, -1, DX_FONTTYPE_ANTIALIASING_EDGE);
	DrawGraph(0, 0, BackGround[_TITLE], FALSE);
	DrawStringToHandle(x + 3, y + 3, "HEROES", title_color, title_font);
	DrawStringToHandle(x, y, "HEROES", title_color, title_font);

	DrawStringToHandle(key_x + 3, key_y + 3, "Press Any Key!", title_color, title_font);
	DrawStringToHandle(key_x, key_y, "Press Any Key!", title_color, title_font);
	if (CheckHitKeyAll()) { scene = _SELECT;	battleFlag = 1;	Sleep(WAIT_TIME); }
}

void Select(void)
{
	int x = 100, y = 80;
	int choices_x = 250, choices_y[2] = { 200, 300 };
	int cursor_x = choices_x - 50;
	static int cursor_y = choices_y[0];
	unsigned int select_color[] = {
		GetColor(255, 255, 0),
		GetColor(100, 100, 100),
		GetColor(255, 255, 255)
	};
	battleFlag = 1;
	DrawGraph(0, 0, BackGround[_SELECT], FALSE);
	DrawStringToHandle(x + 3, y + 3, "BATTLE SELECT",select_color[_HEAD], select_font[_HEAD]);
	DrawStringToHandle(x, y, "BATTLE SELECT", select_color[_HEAD], select_font[_HEAD]);
	DrawStringToHandle(choices_x, choices_y[0], "BATTLE 1", select_color[_CHOICES], select_font[_CHOICES]);
	DrawStringToHandle(choices_x, choices_y[1], "BATTLE 2(未作成)", select_color[_CHOICES], select_font[_CHOICES]);
	DrawStringToHandle(cursor_x, cursor_y, "->", select_color[_CURSOR], select_font[_CURSOR]);
	DrawString(20, 400, "※↑↓キーでカーソル移動、Enterキーで決定、スペースキーでタイトルに戻る", GetColor(255,255, 255));
	if (Key[KEY_INPUT_UP])		cursor_y = choices_y[0];
	if (Key[KEY_INPUT_DOWN])	cursor_y = choices_y[1];
	if (Key[KEY_INPUT_SPACE]) {scene = _TITLE;	Sleep(WAIT_TIME);}
	if (cursor_y == choices_y[0] && Key[KEY_INPUT_RETURN]) { scene = _BATTLE; Sleep(WAIT_TIME); }
	}

//敵軍、自軍の各種初期化
void Init_MyArmy(void)
{
	//自軍の位置 前衛は兵士二人に剣士、戦士 後衛はプータローに王女、魔法使い
	const int MyArmy_Zenei = (GRASS_SIZE_Y - CHARACTER_SIZE_Y * 2 - 16);
	const int MyArmy_Kouei = (MyArmy_Zenei + CHARACTER_SIZE_Y);

	//自軍の位置 最前衛はキュー 前衛はゴースト 中衛は兵士 後衛は魔法使いとサタン
	const int Enemy_Kouei = 16;
	const int Enemy_Chuei = Enemy_Kouei + CHARACTER_SIZE_Y;
	const int Enemy_Zenei = Enemy_Chuei + CHARACTER_SIZE_Y;
	const int Enemy_SaiZenei = Enemy_Zenei + CHARACTER_SIZE_Y;

	//描画する際に左側にいてほしいものから初期化
	//自軍
	MyArmy[FENCER] = { CHARACTER_SIZE_X * 3 + 8, MyArmy_Zenei , 150, 150, 60,  _FRONT , 0,"剣士"};
	MyArmy[PUTARO] = { MyArmy[FENCER].x + CHARACTER_SIZE_X, MyArmy_Kouei, 80, 80, 10, _FRONT , 0,"プータロー"};
	MyArmy[SOLDIER_01] = { MyArmy[PUTARO].x + CHARACTER_SIZE_X, MyArmy_Zenei, 120, 120, 30, _FRONT , 0,"兵士No.1" };
	MyArmy[HEROINE] = { MyArmy[SOLDIER_01].x + CHARACTER_SIZE_X, MyArmy_Kouei, 170, 170, 80, _FRONT , 0,"王女"};
	MyArmy[SOLDIER_02] = { MyArmy[HEROINE].x + +CHARACTER_SIZE_X, MyArmy_Zenei, 120, 120, 30, _FRONT , 0,"兵士No.2" };
	MyArmy[WITCH] = { MyArmy[SOLDIER_02].x + CHARACTER_SIZE_X, MyArmy_Kouei, 120, 120, 80, _FRONT , 0,"魔法使い"};
	MyArmy[WARRIOR] = { MyArmy[WITCH].x + CHARACTER_SIZE_X, MyArmy_Zenei, 200, 200, 100, _FRONT , 0,"戦士"};

	//敵軍
	Enemy[GHOST_01] = { 8, Enemy_Zenei, 50, 50, 35,"ゴースト" };
	Enemy[E_SOLDIER_01] = { Enemy[GHOST_01].x + CHARACTER_SIZE_X, Enemy_Chuei, 100, 100, 40,"敵兵士" };
	Enemy[E_WITCH_01] = { Enemy[E_SOLDIER_01].x + CHARACTER_SIZE_X, Enemy_Kouei, 80, 80, 70,"極悪魔導士" };
	Enemy[E_SOLDIER_02] = { Enemy[E_WITCH_01].x + CHARACTER_SIZE_X, Enemy_Chuei, 100, 100, 40,"敵兵士" };
	Enemy[KYU_01] = { Enemy[E_SOLDIER_02].x + CHARACTER_SIZE_X, Enemy_SaiZenei, 30, 30, 15,"キュー" };
	Enemy[SATAN] = { Enemy[KYU_01].x + CHARACTER_SIZE_X, Enemy_Kouei, 300, 300, 100,"サタン" };
	Enemy[KYU_02] = { Enemy[SATAN].x + (CHARACTER_SIZE_X * 3), Enemy_SaiZenei, 30, 30, 15,"キュー" };
	Enemy[E_SOLDIER_03] = { Enemy[KYU_02].x + CHARACTER_SIZE_X, Enemy_Chuei, 100, 100, 40,"敵兵士" };
	Enemy[E_WITCH_02] = { Enemy[E_SOLDIER_03].x + CHARACTER_SIZE_X, Enemy_Kouei, 80, 80, 70,"極悪魔導士" };
	Enemy[E_SOLDIER_04] = { Enemy[E_WITCH_02].x + CHARACTER_SIZE_X, Enemy_Chuei, 100, 100, 40,"敵兵士" };
	Enemy[GHOST_02] = { Enemy[E_SOLDIER_04].x + CHARACTER_SIZE_X, Enemy_Zenei, 50, 50, 35, "ゴースト" };
}

//メインゲーム
void OneBattle(void)
{
	if (battleFlag) {
		Init_MyArmy();						//キャラステータスの初期化
		battleFlag = 0;
		BattleTurn = PUTARO;
		PlayMusic(-1);
	}
	MyArmy_Turn = BattleTurn % CHARA_NUM;
	if (MyArmy[MyArmy_Turn].hp == 0)	TurnEnd();
	Draw();														//背景、敵、自軍などを描く
	if(Phase == MOVE_01 || Phase == MOVE_02)	MoveMyArmy();	//味方を動かす
	if (Phase == ATTACK) Attack();								//戦闘
	if (E_num == 0)			GameSet(1);							//敵を全滅させたら勝利
	else if (MyArmy[HEROINE].hp == 0)	GameSet(0);				//王女が死んだら敗北
}

//描画
void Draw(void)
{
	DrawField();		//背景、補助線を描く
	DrawArmy();			//敵、自軍を描く
	DrawWindow();		//ウィンドウを描く
	DrawDiceIcon();		//サイコロを描く
	DrawMessage();		//文を書く
	DrawCursor();		//カーソルを描く&動かす
	//DrawEffect();		//エフェクトを描く
}

void DrawField(void)
{
	int i, x = 8, y = 16;
	int LineColor = GetColor(100, 100, 100);
	int RedColor = GetColor(255, 0, 0);
	int BlueColor = GetColor(0, 145, 197);
	int YellowColor = GetColor(255, 230, 21);

	//背景描画
	DrawExtendGraph(0, 0, GRASS_SIZE_X, GRASS_SIZE_Y, grp_Grass, TRUE);			//背景描画
	//敵の攻撃範囲の描画
	for (i = 0; i < ENEMY_NUM; i++) {
		if (Enemy[i].hp != 0) {
			switch (i) {
			case SATAN:
				DrawBox(Enemy[i].x, Enemy[i].y + CHARACTER_SIZE_Y  * 2, Enemy[i].x + CHARACTER_SIZE_X, Enemy[i].y + CHARACTER_SIZE_Y * 3, RedColor, TRUE);
				DrawBox(Enemy[i].x + CHARACTER_SIZE_X, Enemy[i].y + CHARACTER_SIZE_Y * 2, Enemy[i].x + CHARACTER_SIZE_X * 2, Enemy[i].y + CHARACTER_SIZE_Y * 3, RedColor, TRUE);
				DrawBox(Enemy[i].x + CHARACTER_SIZE_X * 2, Enemy[i].y + CHARACTER_SIZE_Y * 2, Enemy[i].x + CHARACTER_SIZE_X * 3, Enemy[i].y + CHARACTER_SIZE_Y * 3, RedColor, TRUE);
				break;
			case E_WITCH_01:
				DrawBox(Enemy[i].x, Enemy[i].y + CHARACTER_SIZE_Y, Enemy[i].x + CHARACTER_SIZE_X, Enemy[i].y + CHARACTER_SIZE_Y * 2, RedColor, TRUE);
				DrawBox(Enemy[i].x, Enemy[i].y + CHARACTER_SIZE_Y * 2, Enemy[i].x + CHARACTER_SIZE_X, Enemy[i].y + CHARACTER_SIZE_Y * 3, RedColor, TRUE);
				break;
			case E_WITCH_02:
				DrawBox(Enemy[i].x, Enemy[i].y + CHARACTER_SIZE_Y, Enemy[i].x + CHARACTER_SIZE_X, Enemy[i].y + CHARACTER_SIZE_Y * 2, RedColor, TRUE);
				DrawBox(Enemy[i].x, Enemy[i].y + CHARACTER_SIZE_Y * 2, Enemy[i].x + CHARACTER_SIZE_X, Enemy[i].y + CHARACTER_SIZE_Y * 3, RedColor, TRUE);
				break;
			default:
				DrawBox(Enemy[i].x, Enemy[i].y + CHARACTER_SIZE_Y, Enemy[i].x + CHARACTER_SIZE_X, Enemy[i].y + CHARACTER_SIZE_Y * 2, RedColor, TRUE);
				break;
			}
		}
	}
	DrawGraph(x, y, grp_Tuta, TRUE);	//ツタゾーンの描画
	//自軍の攻撃範囲描画
	if (MyArmy[MyArmy_Turn].hp != 0) {
		DrawBox(MyArmy[MyArmy_Turn].x, MyArmy[MyArmy_Turn].y, MyArmy[MyArmy_Turn].x + CHARACTER_SIZE_X, MyArmy[MyArmy_Turn].y + CHARACTER_SIZE_Y, BlueColor, TRUE);
		if (Phase == MOVE_02) {
			if(massY - 1 >= 0)	DrawBox(MyArmy[MyArmy_Turn].x, MyArmy[MyArmy_Turn].y - CHARACTER_SIZE_Y, MyArmy[MyArmy_Turn].x + CHARACTER_SIZE_X, MyArmy[MyArmy_Turn].y, YellowColor, TRUE);
			if(MyArmy_Turn == WITCH && massY - 2 >= 0)	DrawBox(MyArmy[MyArmy_Turn].x, MyArmy[MyArmy_Turn].y - CHARACTER_SIZE_Y * 2, MyArmy[MyArmy_Turn].x + CHARACTER_SIZE_X, MyArmy[MyArmy_Turn].y - CHARACTER_SIZE_Y, YellowColor, TRUE);
		}
	}
	
	for (i = 0; i < GRASS_SIZE_X / CHARACTER_SIZE_X + 1; i++) {					//縦線を引く
		DrawLine(x, y, x, GRASS_SIZE_Y - y, LineColor);
		x += CHARACTER_SIZE_X;
	}
	x = 8;
	for (i = 0; i < GRASS_SIZE_Y / CHARACTER_SIZE_Y + 1; i++) {					//横線を引く
		DrawLine(x, y, GRASS_SIZE_X - x, y, LineColor);
		y += CHARACTER_SIZE_Y;
	}
}

void DrawArmy(void)
{
	int i = 0;

	//キャラのグラフィックが前向き固定(本当は4方位分入れたかった)
	const int Satan_size_x = CHARACTER_SIZE_X * 3, Satan_size_y = CHARACTER_SIZE_Y * 2;
	for (i = 0; i < CHARA_NUM; i++) {	//自軍の描画
		if (MyArmy[i].hp != 0) DrawExtendGraph(MyArmy[i].x, MyArmy[i].y, MyArmy[i].x + CHARACTER_SIZE_X, MyArmy[i].y + CHARACTER_SIZE_Y, grp_Chara[_FRONT][i], TRUE);
	}
	for (i = 0; i < ENEMY_NUM; i++) {	//敵の描画
		if (Enemy[i].hp != 0) {
			if (i == SATAN)	DrawExtendGraph(Enemy[i].x, Enemy[i].y, Enemy[i].x + Satan_size_x, Enemy[i].y + Satan_size_y, grp_Enemy[i], TRUE);
			else            DrawExtendGraph(Enemy[i].x, Enemy[i].y, Enemy[i].x + CHARACTER_SIZE_X, Enemy[i].y + CHARACTER_SIZE_Y, grp_Enemy[i], TRUE);
		}
	}
}

void DrawWindow(void)
{
	switch (Phase)
	{
	case MENU:		DrawExtendGraph(0, 0, WINDOW_SIZE_X, WINDOW_SIZE_Y, grp_Window, TRUE);	break;
	case MOVE_01:
		if(Putaro_skill == 2)	DrawExtendGraph(0, 0, WINDOW_SIZE_X, WINDOW_SIZE_Y + 30, grp_Window, TRUE);
		else         DrawExtendGraph(0, 0, WINDOW_SIZE_X, WINDOW_SIZE_Y, grp_Window, TRUE);	break;
		break;
	case MOVE_02:	break;
	case MOVE_03:	DrawExtendGraph(0, 0, WINDOW_SIZE_X, WINDOW_SIZE_Y, grp_Window, TRUE);	break;
	case CARD:		DrawExtendGraph(0, 0, WINDOW_SIZE_X, WINDOW_SIZE_Y, grp_Window, TRUE);	break;
	}
}

void DrawDiceIcon(void)
{
	const int Icon_Size_Big = 60;
	if (Phase == MENU) {
		switch (MyArmy_Turn) {
		case PUTARO:
			DrawExtendGraph(462, 46, 462 + ICON_SIZE, 46 + ICON_SIZE, Dices[5], TRUE);
			break;
		case SOLDIER_01:
			DrawExtendGraph(462, 46, 462 + ICON_SIZE, 46 + ICON_SIZE, Dices[0], TRUE);
			DrawExtendGraph(482, 46, 482 + ICON_SIZE, 46 + ICON_SIZE, Dices[1], TRUE);
			break;
		case SOLDIER_02:
			DrawExtendGraph(462, 46, 462 + ICON_SIZE, 46 + ICON_SIZE, Dices[0], TRUE);
			DrawExtendGraph(482, 46, 482 + ICON_SIZE, 46 + ICON_SIZE, Dices[1], TRUE);
			break;
		case FENCER:
			DrawExtendGraph(462, 46, 462 + ICON_SIZE, 46 + ICON_SIZE, Dices[3], TRUE);
			DrawExtendGraph(482, 46, 482 + ICON_SIZE, 46 + ICON_SIZE, Dices[4], TRUE);
			DrawExtendGraph(502, 46, 502 + ICON_SIZE, 46 + ICON_SIZE, Dices[5], TRUE);
			break;
		case WITCH:
			DrawExtendGraph(462, 46, 462 + ICON_SIZE, 46 + ICON_SIZE, Dices[2], TRUE);
			DrawExtendGraph(482, 46, 482 + ICON_SIZE, 46 + ICON_SIZE, Dices[3], TRUE);
			DrawExtendGraph(502, 46, 502 + ICON_SIZE, 46 + ICON_SIZE, Dices[4], TRUE);

			break;
		case WARRIOR:
			DrawExtendGraph(462, 46, 462 + ICON_SIZE, 46 + ICON_SIZE, Dices[1], TRUE);
			DrawExtendGraph(482, 46, 482 + ICON_SIZE, 46 + ICON_SIZE, Dices[2], TRUE);
			DrawExtendGraph(502, 46, 502 + ICON_SIZE, 46 + ICON_SIZE, Dices[3], TRUE);

			break;
		case HEROINE:
			DrawExtendGraph(462, 46, 462 + ICON_SIZE, 46 + ICON_SIZE, Dices[0], TRUE);
			DrawExtendGraph(482, 46, 482 + ICON_SIZE, 46 + ICON_SIZE, Dices[1], TRUE);
			DrawExtendGraph(502, 46, 502 + ICON_SIZE, 46 + ICON_SIZE, Dices[2], TRUE);
			DrawExtendGraph(522, 46, 522 + ICON_SIZE, 46 + ICON_SIZE, Dices[3], TRUE);
			DrawExtendGraph(542, 46, 542 + ICON_SIZE, 46 + ICON_SIZE, Dices[4], TRUE);
			DrawExtendGraph(562, 46, 562 + ICON_SIZE, 46 + ICON_SIZE, Dices[5], TRUE);
			break;
		}
	}
	//歩数決定時のでかいサイコロの描画
	if (Phase == MOVE_01 && Putaro_skill == 0){
		DrawExtendGraph(60, 20, 60 + Icon_Size_Big, 20 + Icon_Size_Big, Dices[(walk - 1) % 6], TRUE);
	}
}

void DrawMessage(void)
{
	int y = 45;
	switch (Phase) {
	case MENU:
		DrawFormatStringToHandle( 35, 20, MessageFontColor, message_font, "次の行動 は %s です。　　%dターン目", MyArmy[MyArmy_Turn].name, BattleTurn + 1);
		DrawFormatStringToHandle( 35, 45, MessageFontColor, message_font, "HP:%d / %d　攻撃力:%d", MyArmy[MyArmy_Turn].hp, MyArmy[MyArmy_Turn].hpMax, MyArmy[MyArmy_Turn].atk);
		DrawStringToHandle(35, 45, "　　　　　　　　　　　　　　出せる目:", MessageFontColor, message_font);
		DrawStringToHandle(70, 70, "　移動　　タイトルへ戻る　", MessageFontColor, message_font);
		break;
	case MOVE_01:
		if (Putaro_skill == 1) {
			//Sleep(500);
			DrawStringToHandle(35, 20, "　　プータローが移動する代わりにほかのキャラの", MessageFontColor, message_font);
			DrawStringToHandle(35, 45, "　　移動数を増やしますか?", MessageFontColor, message_font);
			DrawStringToHandle(35, 70, "　　　はい　　いいえ", MessageFontColor, message_font);
		}
		else if (Putaro_skill == 2)
		{
			DrawStringToHandle(35, 20, "誰の移動数を増やしますか?", MessageFontColor, message_font);
			DrawStringToHandle(100, 45, "　兵士1　　　兵士2", MessageFontColor, message_font);
			DrawStringToHandle(100, 70, "　剣士 　　　戦士　", MessageFontColor, message_font);
			DrawStringToHandle(100, 95, "　魔法使い　 王女    ※スペースキーで決定", MessageFontColor, message_font);
		}
		else{
			if (walkFlag) {
				Sleep(250);
				DrawStringToHandle(70, 70, "　　　が出ました。", MessageFontColor, message_font);
				if (WaitKey() && Check_onTuta()) { //ツタゾーンにいて動けないなら即終了
					Phase = MOVE_02; 
					walkFlag = 0; 
				}
			}
		}
		break;
	case MOVE_02:
		DrawFormatStringToHandle(35, 20, MessageFontColor, message_font, "残り  %d歩", walk);
		break;
	case MOVE_03:
		DrawStringToHandle(35, 20, "ここに止まります", MessageFontColor, message_font);
		WaitKey();
		Sleep(250);
		Phase = ATTACK;
		break;
	}
}

void DrawCursor(void)
{
	const int choice_first = 70, choice_second = 165;
	static int x = choice_first;
	static int SoCC_x = 100, SoCC_y = 45;		//SoCCはSkill or Card Choicesの略
	int pre_x, pre_y;

	switch (Phase) {
	case MENU:
		DrawStringToHandle(x, 70, "⇒", MessageFontColor, message_font);
		if (Key[KEY_INPUT_RIGHT])	x = choice_second;
		if (Key[KEY_INPUT_LEFT])	x = choice_first;
		if (x == choice_first && Key[KEY_INPUT_RETURN]) {
			Phase = MOVE_01;
			PlaySoundMem(se.kettei, DX_PLAYTYPE_BACK);
			Sleep(250);
		}
		if (x == choice_second && Key[KEY_INPUT_RETURN]) { scene = _TITLE;	PlayMusic(-1); Sleep(WAIT_TIME); }
		break;
	case MOVE_01:
		//プータローのみスキルの使用を迫る
		if (Putaro_skill == 1) {
			DrawStringToHandle(x, 70, "⇒", MessageFontColor, message_font);
			if (Key[KEY_INPUT_RIGHT])	x = choice_second;
			if (Key[KEY_INPUT_LEFT])	x = choice_first;
			if (x == choice_first && Key[KEY_INPUT_RETURN]){
				Putaro_skill = 2;
				PlaySoundMem(se.kettei, DX_PLAYTYPE_BACK);
				Sleep(250); }
			if (x == choice_second && Key[KEY_INPUT_RETURN]) {
				Phase = MOVE_02;
				PlaySoundMem(se.kettei, DX_PLAYTYPE_BACK);
				Sleep(250);
			}
		}
		//使う対象を選ぶ
		if (Putaro_skill == 2) {
			pre_x = SoCC_x, pre_y = SoCC_y;
			DrawStringToHandle(SoCC_x, SoCC_y, "⇒", MessageFontColor, message_font);
			if (Key[KEY_INPUT_RIGHT])	SoCC_x += 130;
			if (Key[KEY_INPUT_LEFT])	SoCC_x -= 130;
			if (Key[KEY_INPUT_UP]) { SoCC_y -= 25; Sleep(250); }
			if (Key[KEY_INPUT_DOWN]) { SoCC_y += 25; Sleep(250); }
			if (SoCC_x < 100 || SoCC_x > 230)	SoCC_x = pre_x;
			if (SoCC_y < 45 || SoCC_y > 95)		SoCC_y = pre_y;
			if (Key[KEY_INPUT_SPACE]) {
				switch (SoCC_y) {
				case 45:
					if (SoCC_x == 100) { MyArmy[SOLDIER_01].Pskill = 1;		PlaySoundMem(se.kettei, DX_PLAYTYPE_BACK); }
					else if (SoCC_x == 230){	MyArmy[SOLDIER_02].Pskill = 1;	PlaySoundMem(se.kettei, DX_PLAYTYPE_BACK); }
					break;
				case 70:
					if (SoCC_x == 100)	{MyArmy[FENCER].Pskill = 1;			PlaySoundMem(se.kettei, DX_PLAYTYPE_BACK); }
					else if (SoCC_x == 230){MyArmy[WARRIOR].Pskill = 1;		PlaySoundMem(se.kettei, DX_PLAYTYPE_BACK); }
					break;
				case 95:
					if (SoCC_x == 100)	{MyArmy[WITCH].Pskill = 1;	PlaySoundMem(se.kettei, DX_PLAYTYPE_BACK); }
					else if (SoCC_x == 230)	{MyArmy[HEROINE].Pskill = 1;	PlaySoundMem(se.kettei, DX_PLAYTYPE_BACK); }
					break;
				}
				TurnEnd();
			}
		}
		break;
	case MOVE_02:	break;
	case MOVE_03:	break;
	}
}

void MoveMyArmy(void)
{
	//各キャラの動ける歩数を決定
	if (Phase == MOVE_01 && walkFlag == 0) {
		switch (MyArmy_Turn) {
		case PUTARO:					walk = 6;
			if (Putaro_skill != 2) Putaro_skill = 1;		break;
		case SOLDIER_01:				walk = GetRand(1) + 1;						break;
		case SOLDIER_02:				walk = GetRand(1) + 1;						break;
		case FENCER:					walk = GetRand(2) + 4;						break;
		case WITCH:						walk = GetRand(2) + 3;						break;
		case WARRIOR:					walk = GetRand(2) + 2;						break;
		case HEROINE:					walk = GetRand(5) + 1;						break;
		}
		//プータローのスキルが使われているなら+6歩
		if (MyArmy[MyArmy_Turn].Pskill) { walk += 6;	MyArmy[MyArmy_Turn].Pskill = 0; }
		walkFlag = 1;
	}

	//以前いた場所を保存
	pre_x = MyArmy[MyArmy_Turn].x;
	pre_y = MyArmy[MyArmy_Turn].y;
	pre_massX = pre_x / CHARACTER_SIZE_X;
	pre_massY = pre_y / CHARACTER_SIZE_Y;
	
	//移動
	if (Phase == MOVE_02 && walk != 0) {
		if (Key[KEY_INPUT_RIGHT]) // → キー を押したか
		{
			MyArmy[MyArmy_Turn].x += CHARACTER_SIZE_X;	
			field[pre_massY][pre_massX] = EMPTY;
			walk--;	
			MyArmy[MyArmy_Turn].dire = _RIGHT;
			PlaySoundMem(se.walking, DX_PLAYTYPE_BACK);
			Sleep(250);
		}
		if (Key[KEY_INPUT_LEFT]) // ← キー を押したか
		{
			MyArmy[MyArmy_Turn].x -= CHARACTER_SIZE_X;
			field[pre_massY][pre_massX] = EMPTY;
			MyArmy[MyArmy_Turn].dire = _LEFT;
			walk--;	
			PlaySoundMem(se.walking, DX_PLAYTYPE_BACK);
			Sleep(250);
		}
		if (Key[KEY_INPUT_UP]) // ↑ キー を押したか
		{
			MyArmy[MyArmy_Turn].y -= CHARACTER_SIZE_Y;
			field[pre_massY][pre_massX] = EMPTY;
			walk--;
			MyArmy[MyArmy_Turn].dire = _BACK;
			PlaySoundMem(se.walking, DX_PLAYTYPE_BACK);
			Sleep(250);
		}
		if (Key[KEY_INPUT_DOWN]) // ↓ キー を押したか
		{
			MyArmy[MyArmy_Turn].y += CHARACTER_SIZE_Y;	
			field[pre_massY][pre_massX] = EMPTY;
			walk--;
			MyArmy[MyArmy_Turn].dire = _FRONT;
			PlaySoundMem(se.walking, DX_PLAYTYPE_BACK);
			Sleep(250);
		}
		//フィールドから出ないようにする
		if (MyArmy[MyArmy_Turn].x < 8 || MyArmy[MyArmy_Turn].x > 584
			|| MyArmy[MyArmy_Turn].y < 16 || MyArmy[MyArmy_Turn].y > 400) {
			MyArmy[MyArmy_Turn].x = pre_x, MyArmy[MyArmy_Turn].y = pre_y;
			field[pre_massY][pre_massX] = MYARMY;
			walk++;
		}
		massX = MyArmy[MyArmy_Turn].x / CHARACTER_SIZE_X;
		massY = MyArmy[MyArmy_Turn].y / CHARACTER_SIZE_Y;

		//敵、味方とのぶつかりを調べる
		Check_canGo();
		}

		if (walk == 0 && Phase == MOVE_02) {
			field[massY][massX] = MYARMY;
			field[pre_massY][pre_massX] = EMPTY;
			Phase = MOVE_03;
		}
	}


int Check_onTuta(void)
{
	const int TutaZone = CHARACTER_SIZE_Y * 3 + 16;

	if (MyArmy[MyArmy_Turn].y < TutaZone && walk < 4) {
		DrawExtendGraph(0, 0, WINDOW_SIZE_X, WINDOW_SIZE_Y, grp_Window, TRUE);	//ごり押し
		DrawFormatStringToHandle(35, 20, MessageFontColor, message_font, "歩ける歩数(%d) < 4 なので", walk);
		DrawStringToHandle(35, 45, "ツタに足をとられて動けません", MessageFontColor, message_font);
		if (WaitKey())	TurnEnd();
		Sleep(250);
		return 0;
		
	}
	else return 1;
}

//色々初期化した上で、ターンを+1して次に回す
void TurnEnd(void)
{
	Putaro_skill = 0;
	walk = 0;
	walkFlag = 0;
	BattleTurn++;
	Phase = MENU;
}

void Check_canGo( void ) {
	//敵と重ならないようにする
	if (field[massY][massX] == ENEMY) {
		MyArmy[MyArmy_Turn].x = pre_x, MyArmy[MyArmy_Turn].y = pre_y;
		field[pre_massY][pre_massX] = MYARMY;
		walk++;
	}

	//進む先に味方がいたら
	if (field[massY][massX] == MYARMY && (massX != pre_massX || massY != pre_massY)) {
		switch (MyArmy[MyArmy_Turn].dire) {
		case _FRONT:
			if (massY + 1 <= 6 && field[massY + 1][massX] == EMPTY) {	//味方を挟んださらに上に何もなかったら
				for (int i = 0; i < CHARA_NUM; i++) {	//今ぶつかっているキャラは何かを探る
					if (i == MyArmy_Turn)	continue;
					if (MyArmy[i].x / CHARACTER_SIZE_X == massX
						&&  MyArmy[i].y / CHARACTER_SIZE_Y == massY) {
						MyArmy[i].y += CHARACTER_SIZE_Y;	//ぶつかったキャラの座標移動
						field[massY + 1][massX] = MYARMY;	
						field[pre_massY][pre_massX] = EMPTY;
					}
				}

			}
			else {//挟んだ先が敵や味方、範囲外なら元に戻す
				MyArmy[MyArmy_Turn].x = pre_x, MyArmy[MyArmy_Turn].y = pre_y;
				walk++;
			}
			break;

		case _BACK:
			if (massY - 1 >= 0 && field[massY - 1][massX] == EMPTY) {
				for (int i = 0; i < CHARA_NUM; i++) {
					if (i == MyArmy_Turn)	continue;
					if (MyArmy[i].x / CHARACTER_SIZE_X == massX
						&& MyArmy[i].y / CHARACTER_SIZE_Y == massY) {
						MyArmy[i].y -= CHARACTER_SIZE_Y;
						field[massY - 1][massX] = MYARMY;
						field[pre_massY][pre_massX] = EMPTY;
					}
				}

			}
			else {
				MyArmy[MyArmy_Turn].x = pre_x, MyArmy[MyArmy_Turn].y = pre_y;
				walk++;
			}
			break;

		case _RIGHT:
			if (massX + 1 <= 12 && field[massY][massX + 1] == EMPTY) {
				for (int i = 0; i < CHARA_NUM; i++) {
					if (i == MyArmy_Turn)	continue;
					if (MyArmy[i].x / CHARACTER_SIZE_X == massX
						&& MyArmy[i].y / CHARACTER_SIZE_Y == massY) {
						MyArmy[i].x += CHARACTER_SIZE_X;
						field[massY][massX + 1] = MYARMY;
						field[pre_massY][pre_massX] = EMPTY;
					}
				}

			}
			else {
				MyArmy[MyArmy_Turn].x = pre_x, MyArmy[MyArmy_Turn].y = pre_y;
				walk++;
			}
			break;

		case _LEFT:
			if (massX - 1 >= 0 && field[massY][massX - 1] == EMPTY) {
				for (int i = 0; i < CHARA_NUM; i++) {
					if (i == MyArmy_Turn)	continue;
					if ((MyArmy[i].x - 8) / CHARACTER_SIZE_X == massX
						&& (MyArmy[i].y - 8) / CHARACTER_SIZE_Y == massY) {
						MyArmy[i].x -= CHARACTER_SIZE_X;
						field[massY][massX - 1] = MYARMY;
						field[pre_massY][pre_massX] = EMPTY;
					}
				}

			}
			else {
				MyArmy[MyArmy_Turn].x = pre_x, MyArmy[MyArmy_Turn].y = pre_y;
				walk++;
			}
			break;
		}
	}
}

void Attack(void)
{
	int i;

	//攻撃範囲内に敵がいるか探り、バトル(ただし、敵か味方のどちらにも魔法使いがいないとき)
	if (massY - 1 >= 0 && field[massY - 1][massX] == ENEMY) {
		for (i = 0; i < ENEMY_NUM; i++) {
			if (MyArmy[MyArmy_Turn].y == Enemy[i].y + CHARACTER_SIZE_Y && MyArmy[MyArmy_Turn].x == Enemy[i].x) break;
		}
		//もしバトルするのがサタンだったら
	 if (i - 1 == SATAN) {
		 //体力を減らす(0を下回らないように)
		MyArmy[MyArmy_Turn].hp -= Enemy[SATAN].atk;
		Enemy[SATAN].hp -= MyArmy[MyArmy_Turn].atk;
		if (MyArmy[MyArmy_Turn].hp < 0)	MyArmy[MyArmy_Turn].hp = 0;
		if (Enemy[SATAN].hp < 0)	Enemy[SATAN].hp = 0;

		DrawExtendGraph(0, 0, WINDOW_SIZE_X, WINDOW_SIZE_Y + 30, grp_Window, TRUE);
		DrawFormatStringToHandle(35, 20, MessageFontColor, message_font, " %s と %s のバトル!!", MyArmy[MyArmy_Turn].name, Enemy[SATAN].name);
		PlaySoundMem(se.drum, DX_PLAYTYPE_BACK);
		WaitTimer(500);
		DrawFormatStringToHandle(35, 45, MessageFontColor, message_font, " %sの攻撃! %s に %d のダメージ!", MyArmy[MyArmy_Turn].name, Enemy[SATAN].name, MyArmy[MyArmy_Turn].atk);
		PlaySoundMem(se.drum, DX_PLAYTYPE_BACK);
		WaitTimer(500);
		DrawFormatStringToHandle(35, 70, MessageFontColor, message_font, " %sの攻撃! %s に %d のダメージ!", Enemy[SATAN].name, MyArmy[MyArmy_Turn].name, Enemy[SATAN].atk);
		PlaySoundMem(se.drum, DX_PLAYTYPE_BACK);
		WaitTimer(500);
		DrawFormatStringToHandle(35, 95, MessageFontColor, message_font, " 残りHP %s : %d, %s : %d", MyArmy[MyArmy_Turn].name, MyArmy[MyArmy_Turn].hp, Enemy[SATAN].name, Enemy[SATAN].hp);
		PlaySoundMem(se.drum, DX_PLAYTYPE_BACK);
		if (MyArmy[MyArmy_Turn].hp == 0)	field[massY][massX] = EMPTY;
		if (Enemy[SATAN].hp == 0) {
			//サタンがいたところをEMPTYに
			for (i = 5; i < 8; i++) {
				field[0][i] = EMPTY;
				field[1][i] = EMPTY;
			}
			E_num--;
		}
		if (WaitKey()) { TurnEnd();	WaitTimer(500); }	//何か押したらターンエンド
	}
	 else {//それ以外(バトル対象がサタン出ないとき)
		 MyArmy[MyArmy_Turn].hp -= Enemy[i].atk;
		 Enemy[i].hp -= MyArmy[MyArmy_Turn].atk;
		 if (MyArmy[MyArmy_Turn].hp < 0)	MyArmy[MyArmy_Turn].hp = 0;
		 if (Enemy[i].hp < 0)	Enemy[i].hp = 0;

		 DrawExtendGraph(0, 0, WINDOW_SIZE_X, WINDOW_SIZE_Y + 30, grp_Window, TRUE);
		 DrawFormatStringToHandle(35, 20, MessageFontColor, message_font, " %s と %s のバトル!!", MyArmy[MyArmy_Turn].name, Enemy[i].name);
		 PlaySoundMem(se.drum, DX_PLAYTYPE_BACK);
		 WaitTimer(500);
		 DrawFormatStringToHandle(35, 45, MessageFontColor, message_font, " %sの攻撃! %s に %d のダメージ!", MyArmy[MyArmy_Turn].name, Enemy[i].name, MyArmy[MyArmy_Turn].atk);
		 PlaySoundMem(se.drum, DX_PLAYTYPE_BACK);
		 WaitTimer(500);
		 DrawFormatStringToHandle(35, 70, MessageFontColor, message_font, " %sの攻撃! %s に %d のダメージ!", Enemy[i].name, MyArmy[MyArmy_Turn].name, Enemy[i].atk);
		 PlaySoundMem(se.drum, DX_PLAYTYPE_BACK);
		 WaitTimer(500);
		 DrawFormatStringToHandle(35, 95, MessageFontColor, message_font, " 残りHP %s : %d, %s : %d", MyArmy[MyArmy_Turn].name, MyArmy[MyArmy_Turn].hp, Enemy[i].name, Enemy[i].hp);
		 PlaySoundMem(se.drum, DX_PLAYTYPE_BACK);
		 if (MyArmy[MyArmy_Turn].hp == 0)	field[massY][massX] = EMPTY;
		 if (Enemy[i].hp == 0) { field[massY - 1][massX] = EMPTY;	E_num--; }
		 if (WaitKey()) { TurnEnd();	WaitTimer(500); }
	 }
	}
	else if (massY - 2 >= 0 && field[massY - 2][massX] == ENEMY){//バトルに魔法使いが関わるとき
		for (i = 0; i < ENEMY_NUM; i++) {
			if (MyArmy[MyArmy_Turn].y == Enemy[i].y + CHARACTER_SIZE_Y * 2 && MyArmy[MyArmy_Turn].x == Enemy[i].x) break;
			}
		//魔法使い同士の戦いならお互いにダメージ
		if (MyArmy_Turn == WITCH && (i == E_WITCH_01 || i == E_WITCH_02)) {
			MyArmy[MyArmy_Turn].hp -= Enemy[i].atk;
			Enemy[i].hp -= MyArmy[MyArmy_Turn].atk;
			if (MyArmy[MyArmy_Turn].hp < 0)	MyArmy[MyArmy_Turn].hp = 0;
			if (Enemy[i].hp < 0)	Enemy[i].hp = 0;

			DrawExtendGraph(0, 0, WINDOW_SIZE_X, WINDOW_SIZE_Y + 30, grp_Window, TRUE);
			DrawFormatStringToHandle(35, 20, MessageFontColor, message_font, " %s と %s のバトル!!", MyArmy[MyArmy_Turn].name, Enemy[i].name);
			PlaySoundMem(se.drum, DX_PLAYTYPE_BACK);
			WaitTimer(500);
			DrawFormatStringToHandle(35, 45, MessageFontColor, message_font, " %sの攻撃! %s に %d のダメージ!", MyArmy[MyArmy_Turn].name, Enemy[i].name, MyArmy[MyArmy_Turn].atk);
			PlaySoundMem(se.drum, DX_PLAYTYPE_BACK);
			WaitTimer(500);
			DrawFormatStringToHandle(35, 70, MessageFontColor, message_font, " %sの攻撃! %s に %d のダメージ!", Enemy[i].name, MyArmy[MyArmy_Turn].name, Enemy[i].atk);
			PlaySoundMem(se.drum, DX_PLAYTYPE_BACK);
			WaitTimer(500);
			DrawFormatStringToHandle(35, 95, MessageFontColor, message_font, " 残りHP %s : %d, %s : %d", MyArmy[MyArmy_Turn].name, MyArmy[MyArmy_Turn].hp, Enemy[i].name, Enemy[i].hp);
			PlaySoundMem(se.drum, DX_PLAYTYPE_BACK);
			if (MyArmy[MyArmy_Turn].hp == 0)	field[massY][massX] = EMPTY;
			if (Enemy[i].hp == 0) { field[massY - 2][massX] = EMPTY;	E_num--; }
			if (WaitKey()) { TurnEnd();	WaitTimer(500); }
		}
		//魔法使いとサタンのバトルでもお互いにダメージ
		else if (MyArmy_Turn == WITCH && i - 1 == SATAN) {
			MyArmy[MyArmy_Turn].hp -= Enemy[SATAN].atk;
			Enemy[SATAN].hp -= MyArmy[MyArmy_Turn].atk;
			if (MyArmy[MyArmy_Turn].hp < 0)	MyArmy[MyArmy_Turn].hp = 0;
			if (Enemy[SATAN].hp < 0)	Enemy[SATAN].hp = 0;

			DrawExtendGraph(0, 0, WINDOW_SIZE_X, WINDOW_SIZE_Y + 30, grp_Window, TRUE);
			DrawFormatStringToHandle(35, 20, MessageFontColor, message_font, " %s と %s のバトル!!", MyArmy[MyArmy_Turn].name, Enemy[SATAN].name);
			PlaySoundMem(se.drum, DX_PLAYTYPE_BACK);
			WaitTimer(500);
			DrawFormatStringToHandle(35, 45, MessageFontColor, message_font, " %sの攻撃! %s に %d のダメージ!", MyArmy[MyArmy_Turn].name, Enemy[SATAN].name, MyArmy[MyArmy_Turn].atk);
			PlaySoundMem(se.drum, DX_PLAYTYPE_BACK);
			WaitTimer(500);
			DrawFormatStringToHandle(35, 70, MessageFontColor, message_font, " %sの攻撃! %s に %d のダメージ!", Enemy[SATAN].name, MyArmy[MyArmy_Turn].name, Enemy[SATAN].atk);
			PlaySoundMem(se.drum, DX_PLAYTYPE_BACK);
			WaitTimer(500);
			DrawFormatStringToHandle(35, 95, MessageFontColor, message_font, " 残りHP %s : %d, %s : %d", MyArmy[MyArmy_Turn].name, MyArmy[MyArmy_Turn].hp, Enemy[SATAN].name, Enemy[SATAN].hp);
			PlaySoundMem(se.drum, DX_PLAYTYPE_BACK);
			if (MyArmy[MyArmy_Turn].hp == 0)	field[massY][massX] = EMPTY;
			if (Enemy[SATAN].hp == 0) {
				for (i = 5; i < 8; i++) {
					field[0][i] = EMPTY;
					field[1][i] = EMPTY;
				}
				E_num--;
			}
			if (WaitKey()) { TurnEnd();	WaitTimer(500); }
		}
		//味方のほうのみが魔法使いなら一方的にダメージを与える
		else if (MyArmy_Turn == WITCH) {
			Enemy[i].hp -= MyArmy[MyArmy_Turn].atk;
			if (Enemy[i].hp < 0)	Enemy[i].hp = 0;
			DrawExtendGraph(0, 0, WINDOW_SIZE_X, WINDOW_SIZE_Y + 30, grp_Window, TRUE);
			DrawFormatStringToHandle(35, 45, MessageFontColor, message_font, " %sの攻撃! %s に %d のダメージ!", MyArmy[MyArmy_Turn].name, Enemy[i].name, MyArmy[MyArmy_Turn].atk);
			PlaySoundMem(se.drum, DX_PLAYTYPE_BACK);
			WaitTimer(500);
			DrawFormatStringToHandle(35, 95, MessageFontColor, message_font, " 残りHP %s : %d, %s : %d", MyArmy[MyArmy_Turn].name, MyArmy[MyArmy_Turn].hp, Enemy[i].name, Enemy[i].hp);
			PlaySoundMem(se.drum, DX_PLAYTYPE_BACK);
			if (MyArmy[MyArmy_Turn].hp == 0)	field[massY][massX] = EMPTY;
			if (Enemy[i].hp == 0) {field[massY - 2][massX] = EMPTY;	E_num--;}
			if (WaitKey()) { TurnEnd();	WaitTimer(500); }
		}
		//敵の方のみが魔法使いなら一方的にダメージを受ける
		else if (i == E_WITCH_01 || i == E_WITCH_02) {
			MyArmy[MyArmy_Turn].hp -= Enemy[i].atk;
			if (MyArmy[MyArmy_Turn].hp < 0)	MyArmy[MyArmy_Turn].hp = 0;
			DrawExtendGraph(0, 0, WINDOW_SIZE_X, WINDOW_SIZE_Y + 30, grp_Window, TRUE);
			DrawFormatStringToHandle(35, 45, MessageFontColor, message_font, " %sの攻撃! %s に %d のダメージ!", Enemy[i].name, MyArmy[MyArmy_Turn].name, Enemy[i].atk);
			PlaySoundMem(se.drum, DX_PLAYTYPE_BACK);
			WaitTimer(500);
			DrawFormatStringToHandle(35, 95, MessageFontColor, message_font, " 残りHP %s : %d, %s : %d", MyArmy[MyArmy_Turn].name, MyArmy[MyArmy_Turn].hp, Enemy[i].name, Enemy[i].hp);
			PlaySoundMem(se.drum, DX_PLAYTYPE_BACK);
			if (MyArmy[MyArmy_Turn].hp == 0)	field[massY][massX] = EMPTY;
			if (Enemy[i].hp == 0) { field[massY - 2][massX] = EMPTY;	E_num--; }
			if (WaitKey()) { TurnEnd();	WaitTimer(500); }
		}
		else
			TurnEnd();
	}
	else
		TurnEnd();	
}

//ゲームが終わった時(王女が死ぬか敵を全滅させたとき)
void GameSet(int Judge) {
	int WinColor = GetColor(255, 241, 86), LoseColor = GetColor(0, 115, 176);
	int font = CreateFontToHandle(NULL, 45, -1, DX_FONTTYPE_ANTIALIASING_EDGE);

	DrawExtendGraph(0, 0, WINDOW_SIZE_X, WINDOW_SIZE_Y + 30, grp_Window, TRUE);
	DrawExtendGraph(0, 0, WINDOW_SIZE_X, WINDOW_SIZE_Y + 30, grp_Window, TRUE);
	DrawStringToHandle(35, 70, "あなたの", MessageFontColor, message_font);
	if (Judge == 1) {
		DrawStringToHandle(150, 45, "勝利!", WinColor, font);
		if(BattleTurn <= 50)	DrawStringToHandle(320, 90, "Aランク   Excellent!", MessageFontColor, message_font);
		else if (BattleTurn >= 51 && BattleTurn <= 80)	DrawStringToHandle(320, 90, "Bランク   Good!", MessageFontColor, message_font);
		else if (BattleTurn >= 81 )	DrawStringToHandle(320, 90, "Cランク   That's all?", MessageFontColor, message_font);
	}
	else if (Judge == 0)	DrawStringToHandle(150, 45, "負け...", LoseColor, font);
	PlayMusic(Judge);
	if (WaitKey())	scene = _TITLE;
}


