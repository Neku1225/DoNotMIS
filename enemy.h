#ifndef ENEMY_H
#define ENEMY_H

class Enemy_obj {
private:
	struct enemy_t {
		//�t���O�A�J�E���^�A�ړ��p�^�[���A�����A�G�̎�ށAHP�ő�l�A���Ƃ��A�C�e���A�摜�A�w�i�F
		bool flag;
		int  counter, pattern, direction, type, hp, hp_max, item_n[6], img, back_color;
		//���W�A���xx�����A���xy�����A�X�s�[�h�A�p�x
		double x, y, vx, vy, speed, angle;
		//�e���J�n���ԁA�e���̎�ށA�e�̎�ށA�F�A��ԁA�ҋ@���ԁA��؎���
		int bl_time, bl_type, bl_type2, color, state, w_time, wait, death_count;
	};
	enemy_t enemy[ENEMY_MAX];


	struct order_t {
		int counter, pattern, type;
		double x, y, speed;
		int bl_time, bl_type, color, hp, bl_type2, wait, item_n[6];
	};
	order_t enemy_order[ENEMY_ORDER_MAX];


	//�e�Ɋւ���\����
	struct bullet_t {
		//�t���O�A��ށA�J�E���^�A�F�A��ԁA���Ȃ��Ƃ������Ȃ����ԁA�G�t�F�N�g�̎��
		int  flag, type, counter, color, state, till, effect;
		//���W�A�p�x�A���x�A�x�[�X�̊p�x�A�ꎞ�L���X�s�[�h
		double x, y, angle, speed, base_angle[1], rem_speed[1];
	};

	//�e�̏��
	struct bullet_info_t {
		int size_x, size_y, col_num;
		double range;
	};
	bullet_info_t bullet_info[10];//�e���


	//�e���f�[�^�Ɋւ���\����
	struct shot_t {
		//num=�ǂ̓G���甭�˂��ꂽ���̔ԍ�
		int flag, type, counter, num;
		//�x�[�X�p�x�A�x�[�X�X�s�[�h
		double base_angle[1], base_speed[1];
		bullet_t bullet[SHOT_BULLET_MAX];
	};
	shot_t shot[SHOT_MAX];//�e���f�[�^���

	int ene_image[3][12];
	int bul_image[SHOT_TYPE_MAX][10];
	//�G�̓����蔻��͈�
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
	int se_flag[SE_MAX];					//���Ȃ炷�t���O
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