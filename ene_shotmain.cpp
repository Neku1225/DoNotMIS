#include "define.h"

void Enemy_obj::EnterShot(int i) {
	int j;
	for (j = 0; j<SHOT_MAX; j++) {//�t���O�̂����Ė���enemy��T��
		if (shot[j].flag == 0) {//���g�p�̒e���f�[�^�������
			memset(&shot[j], 0, sizeof(shot_t));//���������ēo�^
			shot[j].flag = 1;//�t���O�����Ă�
			shot[j].type = enemy[i].bl_type;//�e�̎��
			shot[j].num = i;//num=�ǂ̓G���甭�˂��ꂽ���̂��B
			shot[j].counter = 0;
			return;
		}
	}
}
//n�Ԗڂ̃V���b�g��o�^�����G�Ǝ��@�Ƃ̊p�x��Ԃ�
double Enemy_obj::Shotatan2(int n) {
	return atan2(Player.GetY() - enemy[shot[n].num].y, Player.GetX() - enemy[shot[n].num].x);
}

//�󂢂Ă���e��T��
int Enemy_obj::ShotSearch(int n) {
	int i;
	for (i = 0; i<SHOT_BULLET_MAX; i++) {
		if (shot[n].bullet[i].flag == 0) {
			return i;
		}
	}
	return -1;
}

void Enemy_obj::ShotMain() {
	int i;
	for (i = 0; i<SHOT_MAX; i++) {//�e���f�[�^�v�Z
								  //�t���O�������Ă��āA�ݒ肵����ނ��Ԉ���Ă��Ȃ����
		if (shot[i].flag != 0 && 0 <= shot[i].type && shot[i].type < SHOT_TYPE_MAX) {
			switch (Control.GetLevel()) {
			case 'E':
				ShotEasy(i);
				break;
			case 'N':
				ShotNormal(i);
				break;
			case 'H':
				ShotHard(i);
				break;
			}
			ShotCalc(i);//i�Ԗڂ̒e�����v�Z
			shot[i].counter++;
		}
	}
}

void Enemy_obj::ShotCalc(int n) {
	int i, max = 0;
	if (enemy[shot[n].num].flag != 1)//�G���|���ꂽ��
		shot[n].flag = 2;//����ȏ�V���b�g��o�^���Ȃ��t���O�ɕς���
	for (i = 0; i<SHOT_BULLET_MAX; i++) {//n�Ԗڂ̒e���f�[�^�̒e���v�Z
		if (shot[n].bullet[i].flag>0) {//���̒e���o�^����Ă�����
			shot[n].bullet[i].x += cos(shot[n].bullet[i].angle)*shot[n].bullet[i].speed;
			shot[n].bullet[i].y += sin(shot[n].bullet[i].angle)*shot[n].bullet[i].speed;
			shot[n].bullet[i].counter++;
			if (shot[n].bullet[i].x<-50 || shot[n].bullet[i].x>FIELD_MAX_X + 50 ||
				shot[n].bullet[i].y<-50 || shot[n].bullet[i].y>FIELD_MAX_Y + 50) {//��ʂ���O�ꂽ��
				if (shot[n].bullet[i].till < shot[n].bullet[i].counter) {//�Œ�����Ȃ����Ԃ�蒷�����
					shot[n].bullet[i].flag = 0;//����
				}
			}
		}
	}
	//���ݕ\�����̒e����ł����邩�ǂ������ׂ�
	for (i = 0; i < SHOT_BULLET_MAX; i++) {
		if (shot[n].bullet[i].flag > 0) {
			return;
		}
	}
	if (enemy[shot[n].num].flag != 1) {
		shot[n].flag = 0;//�I��
		enemy[shot[n].num].flag = 0;
	}
}

void Enemy_obj::DrawBullet() {
	int i, j;
	SetDrawMode(DX_DRAWMODE_BILINEAR);//���`�⊮�`��
	for (i = 0; i<SHOT_MAX; i++) {//�G�̒e���������[�v
		if (shot[i].flag>0) {//�e���f�[�^���I���Ȃ�
			for (j = 0; j<SHOT_BULLET_MAX; j++) {//���̒e�������e�̍ő吔�����[�v
				if (shot[i].bullet[j].flag != 0) {//�e�f�[�^���I���Ȃ�
					if (shot[i].bullet[j].effect == 1) {
						SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
					}

					DrawRotaGraphF(shot[i].bullet[j].x, shot[i].bullet[j].y, 1.0,
						shot[i].bullet[j].angle + M_PI / 2, bul_image[shot[i].bullet[j].type][shot[i].bullet[j].color], TRUE);

					if (shot[i].bullet[j].effect == 1) {
						SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
					}
				}
			}
		}
	}
	SetDrawMode(DX_DRAWMODE_NEAREST);//�`��`����߂�
}

//�n���ꂽ�����\���̂ɓ����֐�
void Enemy_obj::InputBulletInfo(bullet_info_t *b_info, int size_x, int size_y, int color_num, double range) {
	b_info->size_x = size_x;  b_info->size_y = size_y;
	b_info->col_num = color_num; b_info->range = range;
}

void Enemy_obj::ShotEasy(int n) {
	int k;
	switch (shot[n].type) {
	case 0:
		//1�������A���@�Ɍ������Ē����ړ�
		if (shot[n].counter == 0) {
			if (shot[n].flag != 2 && (k = ShotSearch(n)) != -1) {
				shot[n].bullet[k].type = enemy[shot[n].num].bl_type2;
				shot[n].bullet[k].angle = Shotatan2(n);
				shot[n].bullet[k].flag = 1;
				shot[n].bullet[k].x = enemy[shot[n].num].x;
				shot[n].bullet[k].y = enemy[shot[n].num].y;
				shot[n].bullet[k].color = enemy[shot[n].num].color;
				shot[n].bullet[k].counter = 0;
				shot[n].bullet[k].speed = 3;
				Enemy.se_flag[0] = 1;
			}
		}
		break;
	case 1:
		//100�J�E���g����10���A���@�Ɍ������Ē�������(��Ɏ��@�_��)
		if (shot[n].counter >= 0 && shot[n].counter < 100 && shot[n].counter % 20 == 0) {//100�J�E���g��10�J�E���g��1��
			if (shot[n].flag != 2 && (k = ShotSearch(n)) != -1) {//�G�����āA�e���o�^�\�Ȃ�
				shot[n].bullet[k].type = enemy[shot[n].num].bl_type2;//�e�o�^
				shot[n].bullet[k].angle = Shotatan2(n);//�p�x
				shot[n].bullet[k].flag = 1;//�t���O
				shot[n].bullet[k].x = enemy[shot[n].num].x;//���W
				shot[n].bullet[k].y = enemy[shot[n].num].y;
				shot[n].bullet[k].color = enemy[shot[n].num].color;//�F
				shot[n].bullet[k].counter = 0;//�J�E���^
				shot[n].bullet[k].speed = 3;//�X�s�[�h
				se_flag[0] = 1;
			}
		}
		break;
	case 2:
		//100�J�E���g����10���A���@�Ɍ������Ē�������(�p�x�L��)
		if (shot[n].counter >= 0 && shot[n].counter < 100 && shot[n].counter % 10 == 0) {
			if (shot[n].counter == 0) {
				shot[n].base_angle[0] = Shotatan2(n);
			}
			if (shot[n].flag != 2 && (k = ShotSearch(n)) != -1) {
				shot[n].bullet[k].type = enemy[shot[n].num].bl_type2;
				shot[n].bullet[k].angle = shot[n].base_angle[0];
				shot[n].bullet[k].flag = 1;
				shot[n].bullet[k].x = enemy[shot[n].num].x;
				shot[n].bullet[k].y = enemy[shot[n].num].y;
				shot[n].bullet[k].color = enemy[shot[n].num].color;
				shot[n].bullet[k].counter = 0;
				shot[n].bullet[k].speed = 3;
				se_flag[0] = 1;
			}
		}
		break;
	case 3:
		//100�J�E���g����10���A���@�Ɍ������ăX�s�[�h�ω���������
		if (shot[n].counter >= 0 && shot[n].counter < 100 && shot[n].counter % 10 == 0) {
			if (shot[n].flag != 2 && (k = ShotSearch(n)) != -1) {
				shot[n].bullet[k].type = enemy[shot[n].num].bl_type2;
				shot[n].bullet[k].angle = Shotatan2(n);
				shot[n].bullet[k].flag = 1;
				shot[n].bullet[k].x = enemy[shot[n].num].x;
				shot[n].bullet[k].y = enemy[shot[n].num].y;
				shot[n].bullet[k].color = enemy[shot[n].num].color;
				shot[n].bullet[k].counter = 0;
				shot[n].bullet[k].speed = 1 + 5.0 / 100 * shot[n].counter;
				se_flag[0] = 1;
			}
		}
		break;
	case 4:
		//0.5�b��1�񂸂~�`����
		if (shot[n].counter >= 0 && shot[n].counter < 120 && shot[n].counter % 20 == 0) {
			double angle = Shotatan2(n);
			for (int i = 0; i < 20; i++) {
				if (shot[n].flag != 2 && (k = ShotSearch(n)) != -1) {
					shot[n].bullet[k].type = enemy[shot[n].num].bl_type2;
					shot[n].bullet[k].angle = angle + M_PI / 10 * i;
					shot[n].bullet[k].flag = 1;
					shot[n].bullet[k].x = enemy[shot[n].num].x;
					shot[n].bullet[k].y = enemy[shot[n].num].y;
					shot[n].bullet[k].color = enemy[shot[n].num].color;
					shot[n].bullet[k].counter = 0;
					shot[n].bullet[k].speed = 4;
				}
				se_flag[0] = 1;
			}
		}
		break;
	case 5:
		//�΂�܂��V���b�g
		if (shot[n].counter >= 0 && shot[n].counter < 120 && shot[n].counter % 2 == 0) {
			if (shot[n].flag != 2 && (k = ShotSearch(n)) != -1) {
				shot[n].bullet[k].type = enemy[shot[n].num].bl_type2;
				shot[n].bullet[k].angle = Shotatan2(n) + Rang(M_PI / 4);
				shot[n].bullet[k].flag = 1;
				shot[n].bullet[k].x = enemy[shot[n].num].x;
				shot[n].bullet[k].y = enemy[shot[n].num].y;
				shot[n].bullet[k].color = enemy[shot[n].num].color;
				shot[n].bullet[k].counter = 0;
				shot[n].bullet[k].speed = 3 + Rang(1.5);
				se_flag[0] = 1;
			}
		}
		break;
	case 6:
		//�΂�܂��V���b�g(����)
		if (shot[n].counter >= 0 && shot[n].counter < 120 && shot[n].counter % 2 == 0) {
			if (shot[n].flag != 2 && (k = ShotSearch(n)) != -1) {
				shot[n].bullet[k].type = enemy[shot[n].num].bl_type2;
				shot[n].bullet[k].angle = Shotatan2(n) + Rang(M_PI / 4);
				shot[n].bullet[k].flag = 1;
				shot[n].bullet[k].x = enemy[shot[n].num].x;
				shot[n].bullet[k].y = enemy[shot[n].num].y;
				shot[n].bullet[k].color = enemy[shot[n].num].color;
				shot[n].bullet[k].counter = 0;
				shot[n].bullet[k].speed = 10 + Rang(2);
				se_flag[0] = 1;
			}
		}
		for (int i = 0; i<SHOT_BULLET_MAX; i++) {//�S�e�����[�v
			if (shot[n].bullet[i].speed>1.5)//���x��1.5���傫�����̂������
				shot[n].bullet[i].speed -= 0.04;//����
		}
		break;
	case 7:
		if (shot[n].counter >= 0 && shot[n].counter < 200 && shot[n].counter % 25 == 0) {
			if (shot[n].counter == 0) {
				shot[n].base_angle[0] = M_PI / 2;//�^����
			}
			if (shot[n].flag != 2 && (k = ShotSearch(n)) != -1) {
				shot[n].bullet[k].type = enemy[shot[n].num].bl_type2;
				shot[n].bullet[k].angle = shot[n].base_angle[0];
				shot[n].bullet[k].flag = 1;
				shot[n].bullet[k].x = enemy[shot[n].num].x;
				shot[n].bullet[k].y = enemy[shot[n].num].y;
				shot[n].bullet[k].color = enemy[shot[n].num].color;
				shot[n].bullet[k].counter = 0;
				shot[n].bullet[k].speed = 2;
				se_flag[0] = 1;
			}
		}
		break;
	case 8:
		if (shot[n].counter >= 0 && shot[n].counter < 200 && shot[n].counter % 80 == 0) {
			if (shot[n].counter == 0) {
				shot[n].base_angle[0] = M_PI / 2;//�^����
			}
			if (shot[n].flag != 2 && (k = ShotSearch(n)) != -1) {
				shot[n].bullet[k].type = enemy[shot[n].num].bl_type2;
				shot[n].bullet[k].angle = shot[n].base_angle[0];
				shot[n].bullet[k].flag = 1;
				shot[n].bullet[k].x = enemy[shot[n].num].x;
				shot[n].bullet[k].y = enemy[shot[n].num].y;
				shot[n].bullet[k].color = enemy[shot[n].num].color;
				shot[n].bullet[k].counter = 0;
				shot[n].bullet[k].speed = 2;
				se_flag[0] = 1;
			}
		}
		break;
	case 9:
		if (shot[n].counter >= 0 && shot[n].counter < 300 && shot[n].counter % 25 == 0) {
			if (shot[n].counter == 0) {
				shot[n].base_angle[0] = M_PI / 4;//�E�΂�45�x
			}
			if (shot[n].flag != 2 && (k = ShotSearch(n)) != -1) {
				shot[n].bullet[k].type = enemy[shot[n].num].bl_type2;
				shot[n].bullet[k].angle = shot[n].base_angle[0];
				shot[n].bullet[k].flag = 1;
				shot[n].bullet[k].x = enemy[shot[n].num].x;
				shot[n].bullet[k].y = enemy[shot[n].num].y;
				shot[n].bullet[k].color = enemy[shot[n].num].color;
				shot[n].bullet[k].counter = 0;
				shot[n].bullet[k].speed = 1;
				se_flag[0] = 1;
			}
		}
		break;
	case 10:
		if (shot[n].counter >= 0 && shot[n].counter < 300 && shot[n].counter % 25 == 0) {
			if (shot[n].counter == 0) {
				shot[n].base_angle[0] = (M_PI / 4) * 3;//���΂�45�x
			}
			if (shot[n].flag != 2 && (k = ShotSearch(n)) != -1) {
				shot[n].bullet[k].type = enemy[shot[n].num].bl_type2;
				shot[n].bullet[k].angle = shot[n].base_angle[0];
				shot[n].bullet[k].flag = 1;
				shot[n].bullet[k].x = enemy[shot[n].num].x;
				shot[n].bullet[k].y = enemy[shot[n].num].y;
				shot[n].bullet[k].color = enemy[shot[n].num].color;
				shot[n].bullet[k].counter = 0;
				shot[n].bullet[k].speed = 1;
				se_flag[0] = 1;
			}
		}
		break;
	case 11:
		//�΂�܂��V���b�g(�Ȉ�)
		if (shot[n].counter >= 0 && shot[n].counter < 200 && shot[n].counter % 18 == 0) {
			if (shot[n].flag != 2 && (k = ShotSearch(n)) != -1) {
				shot[n].bullet[k].type = enemy[shot[n].num].bl_type2;
				shot[n].bullet[k].angle = Shotatan2(n) + Rang(M_PI / 4);
				shot[n].bullet[k].flag = 1;
				shot[n].bullet[k].x = enemy[shot[n].num].x;
				shot[n].bullet[k].y = enemy[shot[n].num].y;
				shot[n].bullet[k].color = enemy[shot[n].num].color;
				shot[n].bullet[k].counter = 0;
				shot[n].bullet[k].speed = 2;
				se_flag[0] = 1;
			}
		}
		break;
	case 12:
		//100�J�E���g����10���A���@�Ɍ������Ē�������(�p�x�L��) 3way
		if (shot[n].counter >= 0 && shot[n].counter < 100 && shot[n].counter % 10 == 0) {
			if (shot[n].counter == 0) {
				shot[n].base_angle[0] = Shotatan2(n);
			}
			for (int i = 0; i < 3; i++) {
				if (shot[n].flag != 2 && (k = ShotSearch(n)) != -1) {
					shot[n].bullet[k].type = enemy[shot[n].num].bl_type2;
					shot[n].bullet[k].angle = shot[n].base_angle[0] + (i - 1) * 0.25;
					shot[n].bullet[k].flag = 1;
					shot[n].bullet[k].x = enemy[shot[n].num].x;
					shot[n].bullet[k].y = enemy[shot[n].num].y;
					shot[n].bullet[k].color = enemy[shot[n].num].color;
					shot[n].bullet[k].counter = 0;
					shot[n].bullet[k].speed = 3;
					se_flag[0] = 1;
				}
			}
		}
		break;
	case 13:
		//100�J�E���g����10���A���@�Ɍ������Ē�������(��Ɏ��@�_��) 3way
		for (int i = 0; i < 3; i++) {
			if (shot[n].counter >= 0 && shot[n].counter < 100 && shot[n].counter % 20 == 0) {//100�J�E���g��10�J�E���g��1��
				if (shot[n].flag != 2 && (k = ShotSearch(n)) != -1) {//�G�����āA�e���o�^�\�Ȃ�
					shot[n].bullet[k].type = enemy[shot[n].num].bl_type2;//�e�o�^
					shot[n].bullet[k].angle = Shotatan2(n) + (i - 1) * 0.25;//�p�x
					shot[n].bullet[k].flag = 1;//�t���O
					shot[n].bullet[k].x = enemy[shot[n].num].x;//���W
					shot[n].bullet[k].y = enemy[shot[n].num].y;
					shot[n].bullet[k].color = enemy[shot[n].num].color;//�F
					shot[n].bullet[k].counter = 0;//�J�E���^
					shot[n].bullet[k].speed = 3;//�X�s�[�h
					se_flag[0] = 1;
				}
			}
		}
		break;
	case 14:
		//�\��
		if (shot[n].counter >= 0 && shot[n].counter % 50 == 0) {
			double angle = Shotatan2(n);
			for (int i = 0; i < 20; i++) {
				if (shot[n].flag != 2 && (k = ShotSearch(n)) != -1) {
					shot[n].bullet[k].type = enemy[shot[n].num].bl_type2;
					shot[n].bullet[k].angle = M_PI / 2 * i;
					shot[n].bullet[k].flag = 1;
					shot[n].bullet[k].x = enemy[shot[n].num].x;
					shot[n].bullet[k].y = enemy[shot[n].num].y;
					shot[n].bullet[k].color = enemy[shot[n].num].color;
					shot[n].bullet[k].counter = 0;
					shot[n].bullet[k].speed = 2;
				}
				se_flag[0] = 1;
			}
		}
		break;
	}
}

void Enemy_obj::ShotNormal(int n) {
	int k;
	switch (shot[n].type) {
	case 0:
		//1�������A���@�Ɍ������Ē����ړ�
		if (shot[n].counter == 0) {
			if (shot[n].flag != 2 && (k = ShotSearch(n)) != -1) {
				shot[n].bullet[k].type = enemy[shot[n].num].bl_type2;
				shot[n].bullet[k].angle = Shotatan2(n);
				shot[n].bullet[k].flag = 1;
				shot[n].bullet[k].x = enemy[shot[n].num].x;
				shot[n].bullet[k].y = enemy[shot[n].num].y;
				shot[n].bullet[k].color = enemy[shot[n].num].color;
				shot[n].bullet[k].counter = 0;
				shot[n].bullet[k].speed = 3;
				Enemy.se_flag[0] = 1;
			}
		}
		break;
	case 1:
		//100�J�E���g����10���A���@�Ɍ������Ē�������(��Ɏ��@�_��)
		if (shot[n].counter >= 0 && shot[n].counter < 100 && shot[n].counter % 15 == 0) {//100�J�E���g��10�J�E���g��1��
			if (shot[n].flag != 2 && (k = ShotSearch(n)) != -1) {//�G�����āA�e���o�^�\�Ȃ�
				shot[n].bullet[k].type = enemy[shot[n].num].bl_type2;//�e�o�^
				shot[n].bullet[k].angle = Shotatan2(n);//�p�x
				shot[n].bullet[k].flag = 1;//�t���O
				shot[n].bullet[k].x = enemy[shot[n].num].x;//���W
				shot[n].bullet[k].y = enemy[shot[n].num].y;
				shot[n].bullet[k].color = enemy[shot[n].num].color;//�F
				shot[n].bullet[k].counter = 0;//�J�E���^
				shot[n].bullet[k].speed = 3;//�X�s�[�h
				se_flag[0] = 1;
			}
		}
		break;
	case 2:
		//100�J�E���g����10���A���@�Ɍ������Ē�������(�p�x�L��)
		if (shot[n].counter >= 0 && shot[n].counter < 100 && shot[n].counter % 10 == 0) {
			if (shot[n].counter == 0) {
				shot[n].base_angle[0] = Shotatan2(n);
			}
			if (shot[n].flag != 2 && (k = ShotSearch(n)) != -1) {
				shot[n].bullet[k].type = enemy[shot[n].num].bl_type2;
				shot[n].bullet[k].angle = shot[n].base_angle[0];
				shot[n].bullet[k].flag = 1;
				shot[n].bullet[k].x = enemy[shot[n].num].x;
				shot[n].bullet[k].y = enemy[shot[n].num].y;
				shot[n].bullet[k].color = enemy[shot[n].num].color;
				shot[n].bullet[k].counter = 0;
				shot[n].bullet[k].speed = 3;
				se_flag[0] = 1;
			}
		}
		break;
	case 3:
		//100�J�E���g����10���A���@�Ɍ������ăX�s�[�h�ω���������
		if (shot[n].counter >= 0 && shot[n].counter < 100 && shot[n].counter % 10 == 0) {
			if (shot[n].flag != 2 && (k = ShotSearch(n)) != -1) {
				shot[n].bullet[k].type = enemy[shot[n].num].bl_type2;
				shot[n].bullet[k].angle = Shotatan2(n);
				shot[n].bullet[k].flag = 1;
				shot[n].bullet[k].x = enemy[shot[n].num].x;
				shot[n].bullet[k].y = enemy[shot[n].num].y;
				shot[n].bullet[k].color = enemy[shot[n].num].color;
				shot[n].bullet[k].counter = 0;
				shot[n].bullet[k].speed = 1 + 5.0 / 100 * shot[n].counter;
				se_flag[0] = 1;
			}
		}
		break;
	case 4:
		//0.5�b��1�񂸂~�`����
		if (shot[n].counter >= 0 && shot[n].counter < 120 && shot[n].counter % 20 == 0) {
			double angle = Shotatan2(n);
			for (int i = 0; i < 20; i++) {
				if (shot[n].flag != 2 && (k = ShotSearch(n)) != -1) {
					shot[n].bullet[k].type = enemy[shot[n].num].bl_type2;
					shot[n].bullet[k].angle = angle + M_PI / 10 * i;
					shot[n].bullet[k].flag = 1;
					shot[n].bullet[k].x = enemy[shot[n].num].x;
					shot[n].bullet[k].y = enemy[shot[n].num].y;
					shot[n].bullet[k].color = enemy[shot[n].num].color;
					shot[n].bullet[k].counter = 0;
					shot[n].bullet[k].speed = 4;
				}
				se_flag[0] = 1;
			}
		}
		break;
	case 5:
		//�΂�܂��V���b�g
		if (shot[n].counter >= 0 && shot[n].counter < 120 && shot[n].counter % 2 == 0) {
			if (shot[n].flag != 2 && (k = ShotSearch(n)) != -1) {
				shot[n].bullet[k].type = enemy[shot[n].num].bl_type2;
				shot[n].bullet[k].angle = Shotatan2(n) + Rang(M_PI / 4);
				shot[n].bullet[k].flag = 1;
				shot[n].bullet[k].x = enemy[shot[n].num].x;
				shot[n].bullet[k].y = enemy[shot[n].num].y;
				shot[n].bullet[k].color = enemy[shot[n].num].color;
				shot[n].bullet[k].counter = 0;
				shot[n].bullet[k].speed = 3 + Rang(1.5);
				se_flag[0] = 1;
			}
		}
		break;
	case 6:
		//�΂�܂��V���b�g(����)
		if (shot[n].counter >= 0 && shot[n].counter < 120 && shot[n].counter % 2 == 0) {
			if (shot[n].flag != 2 && (k = ShotSearch(n)) != -1) {
				shot[n].bullet[k].type = enemy[shot[n].num].bl_type2;
				shot[n].bullet[k].angle = Shotatan2(n) + Rang(M_PI / 4);
				shot[n].bullet[k].flag = 1;
				shot[n].bullet[k].x = enemy[shot[n].num].x;
				shot[n].bullet[k].y = enemy[shot[n].num].y;
				shot[n].bullet[k].color = enemy[shot[n].num].color;
				shot[n].bullet[k].counter = 0;
				shot[n].bullet[k].speed = 10 + Rang(2);
				se_flag[0] = 1;
			}
		}
		for (int i = 0; i<SHOT_BULLET_MAX; i++) {//�S�e�����[�v
			if (shot[n].bullet[i].speed>1.5)//���x��1.5���傫�����̂������
				shot[n].bullet[i].speed -= 0.04;//����
		}
		break;
	case 7:
		if (shot[n].counter >= 0 && shot[n].counter < 200 && shot[n].counter % 20 == 0) {
			if (shot[n].counter == 0) {
				shot[n].base_angle[0] = M_PI / 2;//�^����
			}
			if (shot[n].flag != 2 && (k = ShotSearch(n)) != -1) {
				shot[n].bullet[k].type = enemy[shot[n].num].bl_type2;
				shot[n].bullet[k].angle = shot[n].base_angle[0];
				shot[n].bullet[k].flag = 1;
				shot[n].bullet[k].x = enemy[shot[n].num].x;
				shot[n].bullet[k].y = enemy[shot[n].num].y;
				shot[n].bullet[k].color = enemy[shot[n].num].color;
				shot[n].bullet[k].counter = 0;
				shot[n].bullet[k].speed = 2;
				se_flag[0] = 1;
			}
		}
		break;
	case 8:
		if (shot[n].counter >= 0 && shot[n].counter < 200 && shot[n].counter % 60 == 0) {
			if (shot[n].counter == 0) {
				shot[n].base_angle[0] = M_PI / 2;//�^����
			}
			if (shot[n].flag != 2 && (k = ShotSearch(n)) != -1) {
				shot[n].bullet[k].type = enemy[shot[n].num].bl_type2;
				shot[n].bullet[k].angle = shot[n].base_angle[0];
				shot[n].bullet[k].flag = 1;
				shot[n].bullet[k].x = enemy[shot[n].num].x;
				shot[n].bullet[k].y = enemy[shot[n].num].y;
				shot[n].bullet[k].color = enemy[shot[n].num].color;
				shot[n].bullet[k].counter = 0;
				shot[n].bullet[k].speed = 2;
				se_flag[0] = 1;
			}
		}
		break;
	case 9:
		if (shot[n].counter >= 0 && shot[n].counter < 300 && shot[n].counter % 20 == 0) {
			if (shot[n].counter == 0) {
				shot[n].base_angle[0] = M_PI / 4;//�E�΂�45�x
			}
			if (shot[n].flag != 2 && (k = ShotSearch(n)) != -1) {
				shot[n].bullet[k].type = enemy[shot[n].num].bl_type2;
				shot[n].bullet[k].angle = shot[n].base_angle[0];
				shot[n].bullet[k].flag = 1;
				shot[n].bullet[k].x = enemy[shot[n].num].x;
				shot[n].bullet[k].y = enemy[shot[n].num].y;
				shot[n].bullet[k].color = enemy[shot[n].num].color;
				shot[n].bullet[k].counter = 0;
				shot[n].bullet[k].speed = 1;
				se_flag[0] = 1;
			}
		}
		break;
	case 10:
		if (shot[n].counter >= 0 && shot[n].counter < 300 && shot[n].counter % 20 == 0) {
			if (shot[n].counter == 0) {
				shot[n].base_angle[0] = (M_PI / 4) * 3;//���΂�45�x
			}
			if (shot[n].flag != 2 && (k = ShotSearch(n)) != -1) {
				shot[n].bullet[k].type = enemy[shot[n].num].bl_type2;
				shot[n].bullet[k].angle = shot[n].base_angle[0];
				shot[n].bullet[k].flag = 1;
				shot[n].bullet[k].x = enemy[shot[n].num].x;
				shot[n].bullet[k].y = enemy[shot[n].num].y;
				shot[n].bullet[k].color = enemy[shot[n].num].color;
				shot[n].bullet[k].counter = 0;
				shot[n].bullet[k].speed = 1;
				se_flag[0] = 1;
			}
		}
		break;
	case 11:
		//�΂�܂��V���b�g(�Ȉ�)
		if (shot[n].counter >= 0 && shot[n].counter < 200 && shot[n].counter % 12 == 0) {
			if (shot[n].flag != 2 && (k = ShotSearch(n)) != -1) {
				shot[n].bullet[k].type = enemy[shot[n].num].bl_type2;
				shot[n].bullet[k].angle = Shotatan2(n) + Rang(M_PI / 4);
				shot[n].bullet[k].flag = 1;
				shot[n].bullet[k].x = enemy[shot[n].num].x;
				shot[n].bullet[k].y = enemy[shot[n].num].y;
				shot[n].bullet[k].color = enemy[shot[n].num].color;
				shot[n].bullet[k].counter = 0;
				shot[n].bullet[k].speed = 2;
				se_flag[0] = 1;
			}
		}
		break;
	case 12:
		//100�J�E���g����10���A���@�Ɍ������Ē�������(�p�x�L��) 3way
		if (shot[n].counter >= 0 && shot[n].counter < 100 && shot[n].counter % 10 == 0) {
			if (shot[n].counter == 0) {
				shot[n].base_angle[0] = Shotatan2(n);
			}
			for (int i = 0; i < 4; i++) {
				if (shot[n].flag != 2 && (k = ShotSearch(n)) != -1) {
					shot[n].bullet[k].type = enemy[shot[n].num].bl_type2;
					shot[n].bullet[k].angle = shot[n].base_angle[0] + (i - 1) * 0.25;
					shot[n].bullet[k].flag = 1;
					shot[n].bullet[k].x = enemy[shot[n].num].x;
					shot[n].bullet[k].y = enemy[shot[n].num].y;
					shot[n].bullet[k].color = enemy[shot[n].num].color;
					shot[n].bullet[k].counter = 0;
					shot[n].bullet[k].speed = 3;
					se_flag[0] = 1;
				}
			}
		}
		break;
	case 13:
		//100�J�E���g����10���A���@�Ɍ������Ē�������(��Ɏ��@�_��) 3way
		for (int i = 0; i < 3; i++) {
			if (shot[n].counter >= 0 && shot[n].counter < 100 && shot[n].counter % 15 == 0) {//100�J�E���g��10�J�E���g��1��
				if (shot[n].flag != 2 && (k = ShotSearch(n)) != -1) {//�G�����āA�e���o�^�\�Ȃ�
					shot[n].bullet[k].type = enemy[shot[n].num].bl_type2;//�e�o�^
					shot[n].bullet[k].angle = Shotatan2(n) + (i - 1) * 0.25;//�p�x
					shot[n].bullet[k].flag = 1;//�t���O
					shot[n].bullet[k].x = enemy[shot[n].num].x;//���W
					shot[n].bullet[k].y = enemy[shot[n].num].y;
					shot[n].bullet[k].color = enemy[shot[n].num].color;//�F
					shot[n].bullet[k].counter = 0;//�J�E���^
					shot[n].bullet[k].speed = 3;//�X�s�[�h
					se_flag[0] = 1;
				}
			}
		}
		break;
	case 14:
		//�\��
		if (shot[n].counter >= 0 && shot[n].counter % 40 == 0) {
			double angle = Shotatan2(n);
			for (int i = 0; i < 20; i++) {
				if (shot[n].flag != 2 && (k = ShotSearch(n)) != -1) {
					shot[n].bullet[k].type = enemy[shot[n].num].bl_type2;
					shot[n].bullet[k].angle = M_PI / 2 * i;
					shot[n].bullet[k].flag = 1;
					shot[n].bullet[k].x = enemy[shot[n].num].x;
					shot[n].bullet[k].y = enemy[shot[n].num].y;
					shot[n].bullet[k].color = enemy[shot[n].num].color;
					shot[n].bullet[k].counter = 0;
					shot[n].bullet[k].speed = 2;
				}
				se_flag[0] = 1;
			}
		}
		break;
	}
}

void Enemy_obj::ShotHard(int n) {
	int k;
	switch (shot[n].type) {
	case 0:
		//1�������A���@�Ɍ������Ē����ړ�
		if (shot[n].counter == 0) {
			if (shot[n].flag != 2 && (k = ShotSearch(n)) != -1) {
				shot[n].bullet[k].type = enemy[shot[n].num].bl_type2;
				shot[n].bullet[k].angle = Shotatan2(n);
				shot[n].bullet[k].flag = 1;
				shot[n].bullet[k].x = enemy[shot[n].num].x;
				shot[n].bullet[k].y = enemy[shot[n].num].y;
				shot[n].bullet[k].color = enemy[shot[n].num].color;
				shot[n].bullet[k].counter = 0;
				shot[n].bullet[k].speed = 3;
				Enemy.se_flag[0] = 1;
			}
		}
		break;
	case 1:
		//100�J�E���g����10���A���@�Ɍ������Ē�������(��Ɏ��@�_��)
		if (shot[n].counter >= 0 && shot[n].counter < 100 && shot[n].counter % 10 == 0) {//100�J�E���g��10�J�E���g��1��
			if (shot[n].flag != 2 && (k = ShotSearch(n)) != -1) {//�G�����āA�e���o�^�\�Ȃ�
				shot[n].bullet[k].type = enemy[shot[n].num].bl_type2;//�e�o�^
				shot[n].bullet[k].angle = Shotatan2(n);//�p�x
				shot[n].bullet[k].flag = 1;//�t���O
				shot[n].bullet[k].x = enemy[shot[n].num].x;//���W
				shot[n].bullet[k].y = enemy[shot[n].num].y;
				shot[n].bullet[k].color = enemy[shot[n].num].color;//�F
				shot[n].bullet[k].counter = 0;//�J�E���^
				shot[n].bullet[k].speed = 3;//�X�s�[�h
				se_flag[0] = 1;
			}
		}
		break;
	case 2:
		//100�J�E���g����10���A���@�Ɍ������Ē�������(�p�x�L��)
		if (shot[n].counter >= 0 && shot[n].counter < 100 && shot[n].counter % 10 == 0) {
			if (shot[n].counter == 0) {
				shot[n].base_angle[0] = Shotatan2(n);
			}
			if (shot[n].flag != 2 && (k = ShotSearch(n)) != -1) {
				shot[n].bullet[k].type = enemy[shot[n].num].bl_type2;
				shot[n].bullet[k].angle = shot[n].base_angle[0];
				shot[n].bullet[k].flag = 1;
				shot[n].bullet[k].x = enemy[shot[n].num].x;
				shot[n].bullet[k].y = enemy[shot[n].num].y;
				shot[n].bullet[k].color = enemy[shot[n].num].color;
				shot[n].bullet[k].counter = 0;
				shot[n].bullet[k].speed = 3;
				se_flag[0] = 1;
			}
		}
		break;
	case 3:
		//100�J�E���g����10���A���@�Ɍ������ăX�s�[�h�ω���������
		if (shot[n].counter >= 0 && shot[n].counter < 100 && shot[n].counter % 10 == 0) {
			if (shot[n].flag != 2 && (k = ShotSearch(n)) != -1) {
				shot[n].bullet[k].type = enemy[shot[n].num].bl_type2;
				shot[n].bullet[k].angle = Shotatan2(n);
				shot[n].bullet[k].flag = 1;
				shot[n].bullet[k].x = enemy[shot[n].num].x;
				shot[n].bullet[k].y = enemy[shot[n].num].y;
				shot[n].bullet[k].color = enemy[shot[n].num].color;
				shot[n].bullet[k].counter = 0;
				shot[n].bullet[k].speed = 1 + 5.0 / 100 * shot[n].counter;
				se_flag[0] = 1;
			}
		}
		break;
	case 4:
		//0.5�b��1�񂸂~�`����
		if (shot[n].counter >= 0 && shot[n].counter < 120 && shot[n].counter % 20 == 0) {
			double angle = Shotatan2(n);
			for (int i = 0; i < 20; i++) {
				if (shot[n].flag != 2 && (k = ShotSearch(n)) != -1) {
					shot[n].bullet[k].type = enemy[shot[n].num].bl_type2;
					shot[n].bullet[k].angle = angle + M_PI / 10 * i;
					shot[n].bullet[k].flag = 1;
					shot[n].bullet[k].x = enemy[shot[n].num].x;
					shot[n].bullet[k].y = enemy[shot[n].num].y;
					shot[n].bullet[k].color = enemy[shot[n].num].color;
					shot[n].bullet[k].counter = 0;
					shot[n].bullet[k].speed = 4;
				}
				se_flag[0] = 1;
			}
		}
		break;
	case 5:
		//�΂�܂��V���b�g
		if (shot[n].counter >= 0 && shot[n].counter < 120 && shot[n].counter % 2 == 0) {
			if (shot[n].flag != 2 && (k = ShotSearch(n)) != -1) {
				shot[n].bullet[k].type = enemy[shot[n].num].bl_type2;
				shot[n].bullet[k].angle = Shotatan2(n) + Rang(M_PI / 4);
				shot[n].bullet[k].flag = 1;
				shot[n].bullet[k].x = enemy[shot[n].num].x;
				shot[n].bullet[k].y = enemy[shot[n].num].y;
				shot[n].bullet[k].color = enemy[shot[n].num].color;
				shot[n].bullet[k].counter = 0;
				shot[n].bullet[k].speed = 3 + Rang(1.5);
				se_flag[0] = 1;
			}
		}
		break;
	case 6:
		//�΂�܂��V���b�g(����)
		if (shot[n].counter >= 0 && shot[n].counter < 120 && shot[n].counter % 2 == 0) {
			if (shot[n].flag != 2 && (k = ShotSearch(n)) != -1) {
				shot[n].bullet[k].type = enemy[shot[n].num].bl_type2;
				shot[n].bullet[k].angle = Shotatan2(n) + Rang(M_PI / 4);
				shot[n].bullet[k].flag = 1;
				shot[n].bullet[k].x = enemy[shot[n].num].x;
				shot[n].bullet[k].y = enemy[shot[n].num].y;
				shot[n].bullet[k].color = enemy[shot[n].num].color;
				shot[n].bullet[k].counter = 0;
				shot[n].bullet[k].speed = 10 + Rang(2);
				se_flag[0] = 1;
			}
		}
		for (int i = 0; i<SHOT_BULLET_MAX; i++) {//�S�e�����[�v
			if (shot[n].bullet[i].speed>1.5)//���x��1.5���傫�����̂������
				shot[n].bullet[i].speed -= 0.04;//����
		}
		break;
	case 7:
		if (shot[n].counter >= 0 && shot[n].counter < 200 && shot[n].counter % 15 == 0) {
			if (shot[n].counter == 0) {
				shot[n].base_angle[0] = M_PI / 2;//�^����
			}
			if (shot[n].flag != 2 && (k = ShotSearch(n)) != -1) {
				shot[n].bullet[k].type = enemy[shot[n].num].bl_type2;
				shot[n].bullet[k].angle = shot[n].base_angle[0];
				shot[n].bullet[k].flag = 1;
				shot[n].bullet[k].x = enemy[shot[n].num].x;
				shot[n].bullet[k].y = enemy[shot[n].num].y;
				shot[n].bullet[k].color = enemy[shot[n].num].color;
				shot[n].bullet[k].counter = 0;
				shot[n].bullet[k].speed = 2;
				se_flag[0] = 1;
			}
		}
		break;
	case 8:
		if (shot[n].counter >= 0 && shot[n].counter < 200 && shot[n].counter % 35 == 0) {
			if (shot[n].counter == 0) {
				shot[n].base_angle[0] = M_PI / 2;//�^����
			}
			if (shot[n].flag != 2 && (k = ShotSearch(n)) != -1) {
				shot[n].bullet[k].type = enemy[shot[n].num].bl_type2;
				shot[n].bullet[k].angle = shot[n].base_angle[0];
				shot[n].bullet[k].flag = 1;
				shot[n].bullet[k].x = enemy[shot[n].num].x;
				shot[n].bullet[k].y = enemy[shot[n].num].y;
				shot[n].bullet[k].color = enemy[shot[n].num].color;
				shot[n].bullet[k].counter = 0;
				shot[n].bullet[k].speed = 2;
				se_flag[0] = 1;
			}
		}
		break;
	case 9:
		if (shot[n].counter >= 0 && shot[n].counter < 300 && shot[n].counter % 15 == 0) {
			if (shot[n].counter == 0) {
				shot[n].base_angle[0] = M_PI / 4;//�E�΂�45�x
			}
			if (shot[n].flag != 2 && (k = ShotSearch(n)) != -1) {
				shot[n].bullet[k].type = enemy[shot[n].num].bl_type2;
				shot[n].bullet[k].angle = shot[n].base_angle[0];
				shot[n].bullet[k].flag = 1;
				shot[n].bullet[k].x = enemy[shot[n].num].x;
				shot[n].bullet[k].y = enemy[shot[n].num].y;
				shot[n].bullet[k].color = enemy[shot[n].num].color;
				shot[n].bullet[k].counter = 0;
				shot[n].bullet[k].speed = 1;
				se_flag[0] = 1;
			}
		}
		break;
	case 10:
		if (shot[n].counter >= 0 && shot[n].counter < 300 && shot[n].counter % 15 == 0) {
			if (shot[n].counter == 0) {
				shot[n].base_angle[0] = (M_PI / 4) * 3;//���΂�45�x
			}
			if (shot[n].flag != 2 && (k = ShotSearch(n)) != -1) {
				shot[n].bullet[k].type = enemy[shot[n].num].bl_type2;
				shot[n].bullet[k].angle = shot[n].base_angle[0];
				shot[n].bullet[k].flag = 1;
				shot[n].bullet[k].x = enemy[shot[n].num].x;
				shot[n].bullet[k].y = enemy[shot[n].num].y;
				shot[n].bullet[k].color = enemy[shot[n].num].color;
				shot[n].bullet[k].counter = 0;
				shot[n].bullet[k].speed = 1;
				se_flag[0] = 1;
			}
		}
		break;
	case 11:
		//�΂�܂��V���b�g(�Ȉ�)
		if (shot[n].counter >= 0 && shot[n].counter < 200 && shot[n].counter % 6 == 0) {
			if (shot[n].flag != 2 && (k = ShotSearch(n)) != -1) {
				shot[n].bullet[k].type = enemy[shot[n].num].bl_type2;
				shot[n].bullet[k].angle = Shotatan2(n) + Rang(M_PI / 4);
				shot[n].bullet[k].flag = 1;
				shot[n].bullet[k].x = enemy[shot[n].num].x;
				shot[n].bullet[k].y = enemy[shot[n].num].y;
				shot[n].bullet[k].color = enemy[shot[n].num].color;
				shot[n].bullet[k].counter = 0;
				shot[n].bullet[k].speed = 2;
				se_flag[0] = 1;
			}
		}
		break;
	case 12:
		//100�J�E���g����10���A���@�Ɍ������Ē�������(�p�x�L��) 3way
		if (shot[n].counter >= 0 && shot[n].counter < 100 && shot[n].counter % 10 == 0) {
			if (shot[n].counter == 0) {
				shot[n].base_angle[0] = Shotatan2(n);
			}
			for (int i = 0; i < 5; i++) {
				if (shot[n].flag != 2 && (k = ShotSearch(n)) != -1) {
					shot[n].bullet[k].type = enemy[shot[n].num].bl_type2;
					shot[n].bullet[k].angle = shot[n].base_angle[0] + (i - 2) * 0.25;
					shot[n].bullet[k].flag = 1;
					shot[n].bullet[k].x = enemy[shot[n].num].x;
					shot[n].bullet[k].y = enemy[shot[n].num].y;
					shot[n].bullet[k].color = enemy[shot[n].num].color;
					shot[n].bullet[k].counter = 0;
					shot[n].bullet[k].speed = 3;
					se_flag[0] = 1;
				}
			}
		}
		break;
	case 13:
		//100�J�E���g����10���A���@�Ɍ������Ē�������(��Ɏ��@�_��) 3way
		for (int i = 0; i < 5; i++) {
			if (shot[n].counter >= 0 && shot[n].counter < 100 && shot[n].counter % 10 == 0) {//100�J�E���g��10�J�E���g��1��
				if (shot[n].flag != 2 && (k = ShotSearch(n)) != -1) {//�G�����āA�e���o�^�\�Ȃ�
					shot[n].bullet[k].type = enemy[shot[n].num].bl_type2;//�e�o�^
					shot[n].bullet[k].angle = Shotatan2(n) + (i - 2) * 0.25;//�p�x
					shot[n].bullet[k].flag = 1;//�t���O
					shot[n].bullet[k].x = enemy[shot[n].num].x;//���W
					shot[n].bullet[k].y = enemy[shot[n].num].y;
					shot[n].bullet[k].color = enemy[shot[n].num].color;//�F
					shot[n].bullet[k].counter = 0;//�J�E���^
					shot[n].bullet[k].speed = 3;//�X�s�[�h
					se_flag[0] = 1;
				}
			}
		}
		break;
	case 14:
		//�\��
		if (shot[n].counter >= 0 && shot[n].counter % 30 == 0) {
			double angle = Shotatan2(n);
			for (int i = 0; i < 20; i++) {
				if (shot[n].flag != 2 && (k = ShotSearch(n)) != -1) {
					shot[n].bullet[k].type = enemy[shot[n].num].bl_type2;
					shot[n].bullet[k].angle = M_PI / 2 * i;
					shot[n].bullet[k].flag = 1;
					shot[n].bullet[k].x = enemy[shot[n].num].x;
					shot[n].bullet[k].y = enemy[shot[n].num].y;
					shot[n].bullet[k].color = enemy[shot[n].num].color;
					shot[n].bullet[k].counter = 0;
					shot[n].bullet[k].speed = 2;
				}
				se_flag[0] = 1;
			}
		}
		break;
	}
}
