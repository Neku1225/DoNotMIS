#pragma once

class Boss_obj {
private:
	int warp_flag;
	int warp_count;
	int boss_image[2][20];
	void MoveBossShot(double,double,int,int);
	int SerchBossShot();
	int font[1];
	int rest_form_num;
	int boss_form_num[5] = { 3,3,3,3,5 };
	void BossWarp();
	int SerchBossShotA();//追加
	int SerchBossShotB();//追加
	int SerchBossShotC();//追加
	int SerchBossShotD();//追加
	int SerchBossShotE();//追加
	void InputPhy(double,double,int);
	void BossShotCalc();
	void EnterBossShot();
	void EnterBoss(int num, int stage);
	void WaitAction();
	void BossMain(int stage);
	void BossShotE(int stage);
	void BossShotN(int stage);
	void BossShotH(int stage);
	void BossShotMain(int stage);
	void DrawBullet();
	void Erosion();
	int bul_image[BSHOT_TYPE_MAX][10];
	//	ボスの当たり判定範囲
	int boss_range[B_RANGE_MAX] = { 32, 32, 48, 32, 55};
	int hp_bar_image;
	void MoveBoss(int stage);
	void CalcPhy();
	int adj_boss_x[5] = { 0, 0, 0, 0, 0 };//南　東　西　北　最終
	int adj_boss_bul_x[5] = { 0, 0, 0, 0, 0 };
	int adj_boss_y[5] = { 0, 0, 0, 0, 0 };
	int adj_boss_bul_y[5] = { 0, 0, 40, 0, 0 };
	int boss_graph_num[5][2] = { {4,6}, {3,6}, {6,0}, {4,0}, {6,4} };//各モーションの一行の枚数
	int exrate;
	int n, k;//どの画像を描写するかに関係　※読み込んだ画像の(n+1)行目の画像を描画する、kは時間に応じて変化

	//弾に関する構造体
	struct bullet_t {
		//フラグ、種類、カウンタ、色、状態、少なくとも消さない時間、エフェクトの種類
		int  flag, type, counter, color, state, till, effect;
		//座標、角度、速度、ベースの角度、一時記憶スピード
		double x, y, vx, vy,angle, speed, base_angle[1], rem_speed[1];
	};

	//弾の情報
	struct bullet_info_t {
		int size_x, size_y, col_num;
		double range;
	};
	void InputBulletInfo(bullet_info_t *b_info, int size_x, int size_y, int col_num, double range);

	//ボスショットに関する構造体
	typedef struct {
		//フラグ、種類、カウンタ、どの敵から発射されたかの番号、色
		int flag, type, counter, num;
		//ベース角度、ベーススピード
		double base_angle[1], base_speed[1];
		bullet_t bullet[BOSS_BULLET_MAX];
	}boss_shot_t;

	//物理的計算に使う構造体
	typedef struct {
		int flag, counter, set_t;
		double ax, v0x, ay, v0y, vx, vy, prex, prey;
	}phy_t;

	//ボスの情報
	typedef struct {
		int flag,atk_flag, counter, type, w_time, state, graph_flag,graph_num[2];
		int hp, hp_max;
		int appear_count, set_hp[5], back_type[5], plus_range;
		double x, y, dx, dy, angle, speed, wx, wy;
		phy_t phy;
	}boss_t;

	boss_shot_t boss_shot;
	boss_t boss;
	bullet_info_t bullet_info[20];//弾情報
public:
	void DrawBoss();
	double BossAtan2();//自機と敵との成す角度を返す
	int GetBossFlag();
	void Loop(int stage);
	void Initialize(int stage);
	void StartIni();
	void MinusHp(int atk);
	double GetBossAngle();
	double GetBossSpeed();
	int GetAppearCount();
	int GetFlag();
	int GetState();
	int GetGraphFlag();
	int GetBulletCount(int i);
	int GetBulletX(int i);
	int GetBulletY(int i);
	int GetBulletSpeed(int i);
	int GetBulletAngle(int i);
	int GetBulletRange(int i);
	int GetBulletType(int i);
	int GetBulletFlag(int i);
	void SetBulletFlag(int i, int setflag);
	int GetRange(int stage);
	int GetX();
	int GetY();
	int BossShotCounter();
	int GetShotFlag();
	int GetBossHp();
	int GetBossHpMax();
	void DrawHpBar();
	int GetBossBackType(int i);
	int GetBossType();
	int GetPlusRange();
};

extern Boss_obj Boss;