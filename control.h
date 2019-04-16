#pragma once

class Control_c{
private:
	bool story_load_flag;
	int state;//stateはゲーム本編のステージの状態を示す
	int mode;//modeはタイトルかポーズかゲームプレイ中かという大枠を示す
	int retry_com;
	int pause_com;
	char level;
	void Continue();
	void Pause();
	void DrawStopTime();
	void  Story(int);
	int mispic[6];//0:通常 1:ニコニコ 2:苦笑 3:困惑 4:驚き 5:決意
	int runapic[3];//0:通常 1: 2:
	int kernpic[2];//0:通常 1:嘲笑
	int out[2];
	int last_picture[1];
	int px[3];
	int rx[2];
	int font[4];
	int font_color;
	int highscore[3];
	int scoresave_flag;
	int score;
	int begin_score;//ステージ開始時のスコア
	int begin_erosion;//ステージ開始時のスコア
	int begin_playernum;
	int i = 0, j, ch_i = 0, counter = 0;
	int out_counter;
	int out_mode;
	char str1[100] = "", str2[100] = "", str3[100] = "", str4[100] = "", str5[100] = "", str6[100] = "";//通常は22文字、エンディングは??文字
	int face[50];
	int m_face;
	int r_face;
	int k_face;
	bool m_draw_flag;//描写するかしないか
	bool r_draw_flag;
	bool k_draw_flag;
	int m_talk_time;
	int r_talk_time;
	int k_talk_time;
	char ch[185][100];
	char name[50][7];
	int ch_max;
	int i_max;
public:
	int blackout_counter;
	int whiteout_counter;
	void Out();
	int level_num;
	int GetScore();
	void SetScore(int);
	int HighScore();
	int ReadHighScore();
	int GetHighScore(int);
	void AddScore(int);
	int g_count;//敵の出現や攻撃のタイミングを指定するのに使う
	void Loop(int);//毎ループごとに呼び出す
	void Initialize();//ステージが始まるたびに行う初期化(敵データとか自機の初期位置とか)
	void StartIni();//画像、音楽など一度でいいものの読み込み
	void LoadStage(int);//順次ステージごとに必要な要素のみの読み込みに変更
	void All();
	void ChangeStage();
	void SetLevel(char);
	void SetStage(int);
	void SetMode(int);
	void SetDifficulty();
	void DrawMaskData();
	char GetLevel();
	int erosion;
	int s_change;//ステージの変更が必要かどうか示すために使う変数(デバッグ用)
	int GetState();
	int GetMode();
	void SetPx(int, int, int);
	void SetRx(int, int);
};

typedef enum {
	s1_loading,  //s1_loadingはステージ1に必要なデータを読み込む状態
	stage1,
	s2_loading,
	stage2,
	s3_loading,
	stage3,
	s4_loading,
	stage4,
	s5_loading,
	stage5,
	s1_talk_f,
	s1_talk_l,
	s2_talk_f,
	s2_talk_l,
	s3_talk_f,
	s3_talk_l,
	s4_talk_f,
	s4_talk_l,
	s5_talk_f,
	s5_talk_l,
} state;

typedef enum{
	title,
	pause,
	retry,
	game_play,
	setting,
	gameover,
	staff_roll,
}mode;

typedef enum {
	playagain,
	rcom_title,
	rcom_num
}retry_com;

typedef enum {
	play,
	stage_retry,
	pcom_title,
	pcom_num
}pause_com;

extern Control_c Control;