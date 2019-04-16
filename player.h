#pragma once

class Player_obj {
private:
	int d_time;
	double x, y;     //座標
	float move;     //速度
	int n, k,l;  //自機の画像の切り替え関係
	int gh[12];
	int gh2[6];
	int player_num;
	void Calc();
	int recover_ene;//1カウントでどれだけエネルギーが回復するか
	bool cool_flag; //エネルギー切れで技が使えない状態かどうか示す
	int energy;
	int energy_max;
	int rest_player;
	int charge;
	int count;
	int inv_count;
	int flag;
	int shield_range;
	int laser_width;
	int shot_counter;
	int shot_image[P_SHOT_TYPE];        //自機ショット用画像
	int shot_sx[4] = { 0, 10,-30, 30 };//ショットの開始位置を自機からどの程度ずらすか
	int shot_sy[4] = { -30,-30,-10,-10 };
	int num_option;
	int chrge;
	void EnterShot();
	void ShotCalc();
	void ShotMain();
	int SearchShot();
	void PlayerShot();
	void SlowPlayerShot();
	void ChangeShotMode();
	void Shield();
	void Laser();
	void CalcHoming(int k);
	//自機ショットの当たり判定範囲
	int shot_range[PSHOT_RANGE_MAX] = { 6, 6, 6, 6, 6};

	struct shot_t {
		bool flag;//フラグ
		int atk, counter, type;//攻撃力、カウンタ、種類
		double x, y, angle, speed;//座標、角度、スピード
	};
	
	//ボムの情報
	typedef struct {
		int flag, counter, type;
		double x, y;
	}bom_t;


	shot_t shot[P_SHOT_MAX];
	bom_t bom;               //ボム


public:
	int death_count;
	void SetShotSpeed(int,double);
	void Draw();
	int shot_mode;
	void Loop();
	void StartIni();
	void Initialize();
	double GetX();
	double GetY();
	bool GetShotFlag(int);
	int GetShotAtk(int);
	int GetShotCounter(int);
	int GetShotType(int);
	double GetShotX(int);
	double GetShotY(int);
	double GetShotSpeed(int);
	double GetShotAngle(int);
	void SetShotFlag(int, bool);
	int GetShotRange(int);
	void SetCount(int);
	int GetFlag();
	void SetFlag(int);
	int GetInvCount();
	void SetInvCount(int);
	int GetBomFlag();
	int GetBomType();
	int GetBomCounter();
	double GetBomX();
	double GetBomY();
	void SetBomFlag(int);
	void SetBomType(int);
	void SetBomCounter(int);
	int GetCount();
	int GetShotMode();
	int GetShiledRange();
	int GetLaserWidth();
	int GetEnergy();
	int GetEnergyMax();
	void SetEnergy(int);
	void SetEnergyMax(int);
	bool GetCoolFlag();
	int GetCharge();
	int GetPlayerNum();
	void SetPlayerNum(int);
};

typedef enum {
	normal_shot,
	shield,
	mode_num,
	laser,
}shot_mode;

extern Player_obj Player;