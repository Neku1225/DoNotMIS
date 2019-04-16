#include "define.h"

//�����蔻��
//�V���b�g�̍��W:1  ������𔻒肷�镨��:2
int Judge_c::OutJudge(double x1, double y1, double x2, double y2,
	double range1, double range2, double speed1, double angle1) {
	int j;
	double x = x1 - x2;//�V���b�g�ƕ��̂̋���
	double y = y1 - y2;
	//���̂̓����蔻��ƃV���b�g�̓����蔻��̍��v�͈�
	double r = range1 + range2;
	//���Ԃ��v�Z����K�v�������
	if (speed1>r) {
		//�P�t���[���O�ɂ����ʒu���i�[����
		double pre_x = x1 + cos(angle1 + M_PI)*speed1;
		double pre_y = y1 + sin(angle1 + M_PI)*speed1;
		double px, py;
		for (j = 0; j<speed1 / r; j++) {//�i�񂾕��������蔻�蕪���[�v
			px = pre_x - x2;
			py = pre_y - y2;
			if (px*px + py*py<r*r)
				return 1;
			pre_x += cos(angle1)*r;
			pre_y += sin(angle1)*r;
		}
	}
	if (x*x + y*y < r*r) {//�����蔻����Ȃ�
		return 1;//������
	}
	return 0;
}

//�G�Ǝ��@�V���b�g�������������ǂ����𔻒肷��
bool Judge_c::JudgePS(int s, int t) {
	if (Player.GetShotCounter(s)>0) {//�V���b�g�̋O�����P�x�ł��v�Z����Ă�����
		if (OutJudge(Player.GetShotX(s), Player.GetShotY(s), Enemy.GetX(t), Enemy.GetY(t),
			Player.GetShotRange(Player.GetShotType(s)), Enemy.GetRange(Enemy.GetType(t)),
			Player.GetShotSpeed(s), Player.GetShotAngle(s))==1) {
			return true;
		}
	}
	return false;
}

//�{�X�Ǝ��@�V���b�g�������������ǂ����𔻒肷��
bool Judge_c::JudgePSBoss(int stage,int s) {
	if (Player.GetShotCounter(s)>0) {//�V���b�g�̋O�����P�x�ł��v�Z����Ă�����
		if (OutJudge(Player.GetShotX(s), Player.GetShotY(s), Boss.GetX(), Boss.GetY(),
			Player.GetShotRange(Player.GetShotType(s)), Boss.GetRange(stage)+Boss.GetPlusRange(), 
			Player.GetShotSpeed(s), Player.GetShotAngle(s))==1) {
			return true;
		}
	}
	return false;
}

//���@�ƓG�V���b�g�������������ǂ����𔻒肷��
bool Judge_c::JudgeES(int s, int t,int plus_range) {
	if (Enemy.GetBulletCount(s, t)>0) {//�V���b�g�̋O�����P�x�ł��v�Z����Ă�����
		if (OutJudge(
			Enemy.GetBulletX(s, t), Enemy.GetBulletY(s, t), Player.GetX(), Player.GetY(),
			Enemy.GetBulletRange(Enemy.GetBulletType(s, t)), P_RANGE+Player.GetShiledRange()+plus_range,
			Enemy.GetBulletSpeed(s, t), Enemy.GetBulletAngle(s, t)
			)==1) {
			return true;
		}
	}
	return false;
}

//���@�ƃ{�X�V���b�g�������������ǂ����𔻒肷��
bool Judge_c::JudgeBS(int s,int plus_range) {
	if (Boss.GetBulletCount(s)>0) {//�V���b�g�̋O�����P�x�ł��v�Z����Ă�����
		if (OutJudge(
			Boss.GetBulletX(s), Boss.GetBulletY(s), Player.GetX(), Player.GetY(),
			Boss.GetBulletRange(Boss.GetBulletType(s)), P_RANGE + Player.GetShiledRange()+plus_range,
			Boss.GetBulletSpeed(s), Boss.GetBulletAngle(s)
			)) {
			return true;
		}
	}
	return false;
}

bool Judge_c::JudgePL(int t) {
	if (Enemy.GetY(t) >= -20 && Enemy.GetX(t) - Enemy.GetRange(t) <= Player.GetX() + Player.GetLaserWidth() / 2
		&& Enemy.GetX(t) + Enemy.GetRange(t) >= Player.GetX() - Player.GetLaserWidth() / 2) {
		return true;
	}
	return false;
}

bool Judge_c::JudgePLBoss(int stage) {
	if (Boss.GetY() >= -20 && Boss.GetX() - Boss.GetRange(stage) <= Player.GetX() + Player.GetLaserWidth() / 2
		&& Boss.GetX() + Boss.GetRange(stage) >= Player.GetX() - Player.GetLaserWidth() / 2) {
		return true;
	}
	return false;
}



//�G�����ʂ��ǂ����̌���
void  Judge_c::EnemyDeathJudge(int t) {
	Enemy.se_flag[8] = 1;//�G�ɓ���������
	if (Enemy.GetHp(t) < 0) {//�G��HP���O�����ɂȂ�����
		Enemy.SetFlag(t, false);//�G�����ł�����
		Enemy.se_flag[2] = 1;//�G�̃s�`���艹
		Effect.EnterDelEffect(t);
		Control.AddScore(Enemy.GetHpMax(t) *(0.75 + Control.GetState() / 4) / 10 * 10);
		for (int i = 0; i < SHOT_MAX; i++) {//�G������
			if (Enemy.GetShotFlag(i) != 0) {//�o�^����Ă���e���f�[�^�������
				if (t == Enemy.GetShotNum(i)) {//���̓G���o�^�����e���������
					Enemy.SetShotFlag(i, 2);//����ȏ�e���𑱂��Ȃ��t���O�𗧂Ă�
					break;
				}
			}
		}
	}
}

//���@�V���b�g�ƓG�Ƃ̏���
void Judge_c::JudgeHitPS(int stage) {
	for (int s = 0; s < SHOT_MAX; s++) {//���@�V���b�g����
		if (Player.GetShotFlag(s) == true) {
			for (int t = 0; t < ENEMY_MAX; t++) {//�G����
				if (Enemy.GetFlag(t) == true) {
					if (JudgePS(s, t) == true) {//���@�V���b�g�ƓG���������Ă����
						Player.SetShotFlag(s, false);//���̎��@�V���b�g������
						Enemy.MinusHp(t, Player.GetShotAtk(s));//�e�̎��p���[��HP�����炷
						break;
					}
				}
			}
			//�{�X���o�����Ă��āA�`�悵�Ȃ��t���O���I�t�ŁA�V���b�g���Ȃ�
			if (Boss.GetFlag() == 1 && Boss.GetGraphFlag() == 0 ) {
				if (JudgePSBoss(stage, s) == true) {
					Player.SetShotFlag(s, false);//���̎��@�V���b�g������
					Boss.MinusHp(Player.GetShotAtk(s));
				}
			}
		}
	}

	/*
	//���[�U�[�������Ă���Ƃ�
	if (Player.GetCoolFlag() == false) {
		if (Player.GetShotMode() == laser && (Controller.k_Get(Config.k_shot) > 0 || Controller.g_Get(Config.g_shot) > 0)) {
			for (int t = 0; t < ENEMY_MAX; t++) {//�G����
				if (Enemy.GetFlag(t) == true) {
					if (JudgePL(t) == true) {
						Enemy.MinusHp(t, 20);
					}
				}
			}
			if (Boss.GetFlag() == 1 && Boss.GetGraphFlag() == 0) {
				if (JudgePLBoss(stage) == true ) {
					Boss.MinusHp(30);
				}
			}
		}
	}
	*/
}

//�G�V���b�g�Ǝ��@�Ƃ̏���
void Judge_c::JudgeHitES(int stage) {
	for (int s = 0; s<SHOT_MAX; s++) {//�G�V���b�g����
		if (Enemy.GetShotFlag(s)>0) {//���̃V���b�g���o�^����Ă�����
			for (int t = 0; t<SHOT_BULLET_MAX; t++) {//�e����
				if (Enemy.GetBulletFlag(s, t) == 1) {//�e���o�^����Ă�����
					if (Player.GetFlag() == 2 && Player.GetCount() == 1) {//���G�ɂȂ����u��
							Enemy.SetBulletFlag(s, t, 0);//�e���I�t
					}else if (JudgeES(s, t,0) == true) {//���@�ɂ��̒e���ڐG���Ă�����
						Enemy.SetBulletFlag(s, t, 0);//�e���I�t
						if (Player.GetFlag() == 3) {
							Control.AddScore(100);
						}else if (Player.GetFlag() == 0 && Player.GetInvCount() == 0) {//�X�e�[�^�X���ʏ�ŁA���G����Ȃ�������
							Player.SetFlag(1);     //1:��炢�{����t���@2:��炢�{����t�I���A���S�m��
							Player.SetCount(0);
						}
					}
				}
			}
		}
	}
	//�{�X�̃V���b�g
	if (Boss.GetFlag() > 0) {//���̃V���b�g���o�^����Ă�����
		for (int t = 0; t < BOSS_BULLET_MAX; t++) {//�e����
			if (Boss.GetBulletFlag(t) > 0) {//�e���o�^����Ă�����
				if (Player.GetFlag() == 2 && Player.GetCount() == 1) {//���G�ɂȂ����u��
					if (Boss.GetBulletFlag(t) != 10) {
						Boss.SetBulletFlag(t, 0);//�e���I�t
					}
				}
				else if (JudgeBS(t, 0) == true && Boss.GetBulletFlag(t) != 10) {//���@�ɂ��̒e���ڐG���Ă�����
					Boss.SetBulletFlag(t, 0);//�e���I�t
					if (Player.GetFlag() == 3) {
						Control.AddScore(100);
					}else if (Player.GetFlag() == 0 && Player.GetInvCount() == 0) {
						Player.SetCount(0);
						Player.SetFlag(1);
					}
				}
			}
		}
	//�{�X�ƐڐG�����Ƃ�
		if (OutJudge(Boss.GetX(), Boss.GetY(), Player.GetX(), Player.GetY(), Boss.GetRange(stage), P_RANGE, Boss.GetBossSpeed(), Boss.GetBossAngle() == 1)){
			if (Player.GetFlag() == 0 && Player.GetInvCount() == 0) {//�X�e�[�^�X���ʏ�ŁA���G����Ȃ�������
				Player.SetFlag(1);     //1:��炢�{����t���@2:��炢�{����t�I���A���S�m��
				Player.SetCount(0);
			}
		}
	}
}

void Judge_c::JudgeHitPB(int stage) {
	double rate=1.0;
	if (Player.GetBomFlag() != 1) {
		return;
	}
	for (int s = 0; s<ENEMY_MAX; s++) {//�G����
		if (Enemy.GetFlag(s) == true) {//���̓G�������
			if (Enemy.GetX(s) > FIELD_X && Enemy.GetX(s) < FIELD_X + FIELD_MAX_X) {
				if (Enemy.GetY(s) > FIELD_Y && Enemy.GetY(s) < FIELD_Y + FIELD_MAX_Y) {
					Enemy.MinusHp(s, 20);//�_���[�W��^����
				}
			}
		}
	}
	//�{�X�����āA�`�悵�Ȃ��t���O���I�t�ŁA�V���b�g���Ȃ�
	if (Control.g_count % 2 == 0) {
		if (Boss.GetBossFlag() == 1 && Boss.GetGraphFlag() == 0 && Boss.GetState() == 2 ) {
			if (stage == 5) {
				if (Control.GetLevel() == 'H') {
					rate = 0;
				}
				else if (Boss.GetBossType() == 4 && Control.GetLevel() == 'E') {
					rate = 0.5;
				}
				else if (Boss.GetBossType() == 4 && Control.GetLevel() == 'N') {
					rate = 0;
				}
			}
			Boss.MinusHp(40*rate);//���킷
		}
	}
}

void Judge_c::JudgeTouch(int stage) {

}

void Judge_c::Loop(int stage) {
	JudgeHitPS(stage);
	JudgeHitPB(stage);
	JudgeHitES(stage);
}

