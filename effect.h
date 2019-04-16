#pragma once

class Effect_c{
private:
	int bom_image[5];
	int	SearchEffect();
	int SearchDelEffect();
	int img_del_effect[5];
	int boss_del_effect[10];
	void EnterBom();
	void BomCalc();
	void DnCalc();
	double bom_x, bom_y;

	//エフェクト
	typedef struct {
		int flag, counter, color, type, img, effect, bright;
		double x, y, r, angle, speed, m_angle;
	}effect_t;

	//消滅エフェクト
	typedef struct {
		int flag, counter,color;
		double x, y;
	}del_effect_t;


	

	//ドン！と揺れる画面の情報
	typedef struct {
		int flag, counter, time, size;
		int x, y;
	}dn_t;

	effect_t effect[EFFECT_MAX];//エフェクト
	del_effect_t del_effect[DEL_EFFECT_MAX];//消滅エフェクト
	dn_t dn;                 //ドンと揺れる
	
public:
	void DrawEffect();
	void EnterDelEffect(int i);
	void EnterBossDelEffect(int);
	void CalcEffect();
	void CalcDelEffect();
	void Draw(int type);
	void Loop();
	void Initialize();
	void StartIni();
	void EnterDyingBomEffect();
	int GetdnX();
	int GetdnY();

	//画面の明るさ情報
	typedef struct {
		unsigned char bright;
	}bright_set_t;

	bright_set_t bright_set; //描画の輝度

};

extern Effect_c Effect;