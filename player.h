#pragma once

class Player_obj {
private:
	int d_time;
	double x, y;     //���W
	float move;     //���x
	int n, k,l;  //���@�̉摜�̐؂�ւ��֌W
	int gh[12];
	int gh2[6];
	int player_num;
	void Calc();
	int recover_ene;//1�J�E���g�łǂꂾ���G�l���M�[���񕜂��邩
	bool cool_flag; //�G�l���M�[�؂�ŋZ���g���Ȃ���Ԃ��ǂ�������
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
	int shot_image[P_SHOT_TYPE];        //���@�V���b�g�p�摜
	int shot_sx[4] = { 0, 10,-30, 30 };//�V���b�g�̊J�n�ʒu�����@����ǂ̒��x���炷��
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
	//���@�V���b�g�̓����蔻��͈�
	int shot_range[PSHOT_RANGE_MAX] = { 6, 6, 6, 6, 6};

	struct shot_t {
		bool flag;//�t���O
		int atk, counter, type;//�U���́A�J�E���^�A���
		double x, y, angle, speed;//���W�A�p�x�A�X�s�[�h
	};
	
	//�{���̏��
	typedef struct {
		int flag, counter, type;
		double x, y;
	}bom_t;


	shot_t shot[P_SHOT_MAX];
	bom_t bom;               //�{��


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