#ifndef ENEMY_H
#define ENEMY_H

class Enemy_obj {
private:
	struct enemy_t {
		//フラグ、カウンタ、移動パターン、向き、敵の種類、HP最大値、落とすアイテム、画像、背景色
		bool flag;
		int  counter, pattern, direction, type, hp, hp_max, item_n[6], img, back_color;
		//座標、速度x成分、速度y成分、スピード、角度
		double x, y, vx, vy, speed, angle;
		//弾幕開始時間、弾幕の種類、弾の種類、色、状態、待機時間、停滞時間
		int bl_time, bl_type, bl_type2, color, state, w_time, wait, death_count;
	};
	enemy_t enemy[ENEMY_MAX];


	struct order_t {
		int counter, pattern, type;
		double x, y, speed;
		int bl_time, bl_type, color, hp, bl_type2, wait, item_n[6];
	};
	order_t enemy_order[ENEMY_ORDER_MAX];


	//弾に関する構造体
	struct bullet_t {
		//フラグ、種類、カウンタ、色、状態、少なくとも消さない時間、エフェクトの種類
		int  flag, type, counter, color, state, till, effect;
		//座標、角度、速度、ベースの角度、一時記憶スピード
		double x, y, angle, speed, base_angle[1], rem_speed[1];
	};

	//弾の情報
	struct bullet_info_t {
		int size_x, size_y, col_num;
		double range;
	};
	bullet_info_t bullet_info[10];//弾情報


	//弾幕データに関する構造体
	struct shot_t {
		//num=どの敵から発射されたかの番号
		int flag, type, counter, num;
		//ベース角度、ベーススピード
		double base_angle[1], base_speed[1];
		bullet_t bullet[SHOT_BULLET_MAX];
	};
	shot_t shot[SHOT_MAX];//弾幕データ情報

	int ene_image[3][12];
	int bul_image[SHOT_TYPE_MAX][10];
	//敵の当たり判定範囲
	int enemy_range[ENEMY_RANGE_MAX] = { 30,30,30,30 };
	void DrawBullet();
	void EnemyEnter();
	int EnemyNumSearch();
	void EnterShot(int i);
	double Shotatan2(int n);
	int ShotSearch(int n);
	void ShotMain();
	void ShotEasy(int n);
	void ShotNormal(int n);
	void ShotHard(int n);
	void ShotCalc(int n);
	void EnemyAct();
	void Move(int i);
	void InputBulletInfo(bullet_info_t *b_info, int size_x, int size_y, int col_num, double range);
public:
	void DrawEnemy();
	void Initialize();
	void StartIni();
	void Load_story(char level,int stage);
	void Loop();
	double Rang(double ang);
	int se_flag[SE_MAX];					//音ならすフラグ
	int GetBackColor(int i);
	double GetX(int i);
	double GetY(int i);
	int GetRange(int i);
	int GetType(int i);
	bool GetFlag(int i);
	void SetFlag(int i, bool setflag);
	int GetHp(int i);
	int GetHpMax(int i);
	void MinusHp(int i, int minushp);
	int GetShotFlag(int i);
	void SetShotFlag(int i, int setflag);
	int GetShotNum(int i);
	int GetBulletCount(int i, int j);
	double GetBulletX(int i, int j);
	double GetBulletY(int i, int j);
	double GetBulletSpeed(int i, int j);
	double GetBulletAngle(int i, int j);
	int GetBulletType(int i, int j);
	int GetBulletFlag(int i, int j);
	void SetBulletFlag(int i, int j, int setflag);
	int GetBulletRange(int i);
	void LoadEneBul(int);
	int GetEneBulType(int);
};

extern Enemy_obj Enemy;

#endif //ENEMY_H