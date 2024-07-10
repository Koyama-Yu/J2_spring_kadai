//J2�v���O���~���O2�@�t�x�݉ۑ�
//J1714�@���R�T
//���{����extern������ׂ����Ƃ͎v���܂����ȗ����Ă��܂�

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

enum eScreenMode { _TITLE, _SELECT, _BATTLE };				// ��ʃ��[�h
int scene = _TITLE;		
enum eSelect { _HEAD, _CHOICES, _CURSOR };					// �Z���N�g��ʗp
enum eChara_Class { PUTARO, SOLDIER_01, SOLDIER_02, FENCER, WITCH, WARRIOR, HEROINE};			//���R�L����
enum eEnemy_Class{ KYU_01, KYU_02, GHOST_01, GHOST_02, E_SOLDIER_01, E_SOLDIER_02,				//�G�R�L����
					E_SOLDIER_03, E_SOLDIER_04,E_WITCH_01, E_WITCH_02, SATAN};
struct Chara_Status { int x, y, hp, hpMax, atk,  dire, Pskill;		char name[11]; };			//���R�L�����N�^�[�̃X�e�[�^�X
struct Enemy_Status { int x, y, hp, hpMax, atk;						char name[11]; };			//�G�R�L�����N�^�[�̃X�e�[�^�X
struct Chara_Status MyArmy[CHARA_NUM];
struct Enemy_Status Enemy[ENEMY_NUM];
int Key[256];									// �L�[�i���͂̎��ʂ�����j
int BackGround[SCREENMODE_NUM];					//�^�C�g���A�Z���N�g��ʂł̔w�i
int grp_Grass, grp_Tuta;						//���C���Q�[���ł̔w�i�Ȃ�
struct seData { int walking, kettei, drum; };	//	���ʉ��f�[�^
struct seData se;
int title_font;									//�^�C�g����ʂ̃t�H���g
int select_font[3];								//�Z���N�g��ʂ̃t�H���g
int hosoku_color;								//�⑫�̃t�H���g
int message_font;								//���C���Q�[���̃��b�Z�[�W�̃t�H���g
int MessageFontColor;							//���C���Q�[���̃��b�Z�[�W�̐F
int exitFlag = 0;
int winMode = 1;								//�E�B���h�E���[�h(�S��ʂɂ��ł���悤�ɍl���Ă�)

int grp_Chara[DIRECTION][CHARA_NUM];			//���R�̉摜�f�[�^
int grp_Enemy[ENEMY_NUM];						//�G�R�̉摜�f�[�^
int grp_Window;									//���b�Z�[�W�E�B���h�E�̉摜�f�[�^
int Dices[6];									//�T�C�R���̉摜�f�[�^
enum eDirection { _FRONT, _BACK, _RIGHT, _LEFT};//����
int battleFlag;									//�Q�[�����J�n���ꂽ���ǂ����̃t���O
enum ePhase { MENU, MOVE_01, MOVE_02, MOVE_03, CARD, ATTACK,TURN_END};
												//�Q�[���̒i�K(�ړ�����o�g�����Ȃ�)
int field[MASS_Y_NUM][MASS_X_NUM] =				//�Q�[���}�b�v���傤�̏��
{												//0�͉����Ȃ��A1�͖����A2�͓G
		{0,0,2,0,0,2,2,2,0,0,2,0,0},
		{0,2,0,2,0,2,2,2,0,2,0,2,0},
		{2,0,0,0,0,0,0,0,0,0,0,0,2},
		{0,0,0,0,2,0,0,0,2,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,1,0,1,0,1,0,1,0,0,0},
		{0,0,0,0,1,0,1,0,1,0,0,0,0}
};
int BattleTurn;							//�^�[����
int MyArmy_Turn;						//�N�̃^�[�����̔���
int Phase = MENU;						//�i�K�̔���

int walk, walkFlag = 0;					//�����ƕ��s���s�����ǂ����̃t���O
int Putaro_skill = 0;					//�v�[�^���[�̓���\�͂̃t���O
int pre_x, pre_y;						//�O�ɂ������W��ۑ�
int massX, massY;						//�}�X�ڏ�ł̈ʒu
int pre_massX, pre_massY;				//�O�ɂǂ��̃}�X�ڂɂ������ۑ�
int E_num = ENEMY_NUM;					//�G�̐�

void InitGrp();								// �摜�f�[�^�̃��[�h
void InitSE();								// ���ʉ��f�[�^�̃��[�h
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
