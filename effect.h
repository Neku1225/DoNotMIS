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

	//�G�t�F�N�g
	typedef struct {
		int flag, counter, color, type, img, effect, bright;
		double x, y, r, angle, speed, m_angle;
	}effect_t;

	//���ŃG�t�F�N�g
	typedef struct {
		int flag, counter,color;
		double x, y;
	}del_effect_t;


	

	//�h���I�Ɨh����ʂ̏��
	typedef struct {
		int flag, counter, time, size;
		int x, y;
	}dn_t;

	effect_t effect[EFFECT_MAX];//�G�t�F�N�g
	del_effect_t del_effect[DEL_EFFECT_MAX];//���ŃG�t�F�N�g
	dn_t dn;                 //�h���Ɨh���
	
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

	//��ʂ̖��邳���
	typedef struct {
		unsigned char bright;
	}bright_set_t;

	bright_set_t bright_set; //�`��̋P�x

};

extern Effect_c Effect;