//J2プログラミング2　春休み課題
//J1714　小山裕
//※本当はexternをつけるべきだとは思いますが省略しています

#define WAIT_TIME			500
#define GRASS_SIZE_X		640 
#define GRASS_SIZE_Y		480
#define MASS_X_NUM			13
#define MASS_Y_NUM			7
#define EMPTY				0
#define MYARMY				1
#define ENEMY				2
#define CHARACTER_SIZE_X	48
#define CHARACTER_SIZE_Y	64
#define WINDOW_SIZE_X		GRASS_SIZE_X
#define WINDOW_SIZE_Y		110		
#define SCREENMODE_NUM		3
#define CHARA_NUM			7
#define ENEMY_NUM			11
#define WALK_X				CHARACTER_SIZE_X
#define WALK_Y				CHARACTER_SIZE_Y
#define DIRECTION			4
#define STRN				100
#define ICON_SIZE			20

enum eScreenMode { _TITLE, _SELECT, _BATTLE };				// 画面モード
int scene = _TITLE;		
enum eSelect { _HEAD, _CHOICES, _CURSOR };					// セレクト画面用
enum eChara_Class { PUTARO, SOLDIER_01, SOLDIER_02, FENCER, WITCH, WARRIOR, HEROINE};			//自軍キャラ
enum eEnemy_Class{ KYU_01, KYU_02, GHOST_01, GHOST_02, E_SOLDIER_01, E_SOLDIER_02,				//敵軍キャラ
					E_SOLDIER_03, E_SOLDIER_04,E_WITCH_01, E_WITCH_02, SATAN};
struct Chara_Status { int x, y, hp, hpMax, atk,  dire, Pskill;		char name[11]; };			//自軍キャラクターのステータス
struct Enemy_Status { int x, y, hp, hpMax, atk;						char name[11]; };			//敵軍キャラクターのステータス
struct Chara_Status MyArmy[CHARA_NUM];
struct Enemy_Status Enemy[ENEMY_NUM];
int Key[256];									// キー（入力の識別をする）
int BackGround[SCREENMODE_NUM];					//タイトル、セレクト画面での背景
int grp_Grass, grp_Tuta;						//メインゲームでの背景など
struct seData { int walking, kettei, drum; };	//	効果音データ
struct seData se;
int title_font;									//タイトル画面のフォント
int select_font[3];								//セレクト画面のフォント
int hosoku_color;								//補足のフォント
int message_font;								//メインゲームのメッセージのフォント
int MessageFontColor;							//メインゲームのメッセージの色
int exitFlag = 0;
int winMode = 1;								//ウィンドウモード(全画面にもできるように考えてた)

int grp_Chara[DIRECTION][CHARA_NUM];			//自軍の画像データ
int grp_Enemy[ENEMY_NUM];						//敵軍の画像データ
int grp_Window;									//メッセージウィンドウの画像データ
int Dices[6];									//サイコロの画像データ
enum eDirection { _FRONT, _BACK, _RIGHT, _LEFT};//向き
int battleFlag;									//ゲームが開始されたかどうかのフラグ
enum ePhase { MENU, MOVE_01, MOVE_02, MOVE_03, CARD, ATTACK,TURN_END};
												//ゲームの段階(移動中やバトル中など)
int field[MASS_Y_NUM][MASS_X_NUM] =				//ゲームマップじょうの情報
{												//0は何もなし、1は味方、2は敵
		{0,0,2,0,0,2,2,2,0,0,2,0,0},
		{0,2,0,2,0,2,2,2,0,2,0,2,0},
		{2,0,0,0,0,0,0,0,0,0,0,0,2},
		{0,0,0,0,2,0,0,0,2,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,1,0,1,0,1,0,1,0,0,0},
		{0,0,0,0,1,0,1,0,1,0,0,0,0}
};
int BattleTurn;							//ターン数
int MyArmy_Turn;						//誰のターンかの判別
int Phase = MENU;						//段階の判別

int walk, walkFlag = 0;					//歩数と歩行を行うかどうかのフラグ
int Putaro_skill = 0;					//プータローの特殊能力のフラグ
int pre_x, pre_y;						//前にいた座標を保存
int massX, massY;						//マス目状での位置
int pre_massX, pre_massY;				//前にどこのマス目にいたか保存
int E_num = ENEMY_NUM;					//敵の数

void InitGrp();								// 画像データのロード
void InitSE();								// 効果音データのロード
void PlayMusic(int);
void FullScreen();
void Input();
void Title();
void Select();
void Init_MyArmy();
void Draw();
void DrawArmy();
void DrawField();
void DrawWindow();
void DrawMessage();
void DrawDiceIcon();
void DrawCursor();
void MoveMyArmy();
void Attack();
int  Check_onTuta();
void TurnEnd();
void Check_canGo();
void GameSet(int);
void OneBattle();
