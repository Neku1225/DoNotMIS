#include "define.h"

//�G�t�F�N�g�̓o�^�󂫔ԍ���T��
int Effect_c::SearchEffect() {
	for (int i = 0; i<EFFECT_MAX; i++) {
		if (effect[i].flag == 0)
			return i;
	}
	return -1;
}

//�G�t�F�N�g���v�Z����
void Effect_c::CalcEffect() {
	for (int i = 0; i<EFFECT_MAX; i++) {
		if (effect[i].flag>0) {//�G�t�F�N�g���o�^����Ă�����
			switch (effect[i].type) {//�G�t�F�N�g�̎�ނɂ���ĕ���
			case 0://0�Ԃ̏���
				effect[i].counter++;
				effect[i].r += 0.03;//�G�t�F�N�g�̑傫����i�X�傫������
				if (effect[i].counter > 10) {//10�J�E���g�ȏ�ɂȂ�����
					effect[i].bright -= 25;//���邳�����Ȃ�����
				}
				if (effect[i].counter > 20) {//20�J�E���g�ȏ�ɂȂ�����
					effect[i].flag = 0;//����
				}
				break;
			case 1:
				effect[i].r += 0.06;
				effect[i].counter++;
				if (effect[i].counter > 80) {
					effect[i].bright -= 20;
				}else if (effect[i].counter > 20 && effect[i].bright<115) {//10�J�E���g�ȏ�ɂȂ�����
					effect[i].bright += 10;
				}
				
				if (effect[i].counter >= 130) {
					effect[i].flag = 0;
				}
				/*
				//�{���̃G�t�F�N�g
				   //���W�v�Z
				effect[i].x += cos(effect[i].m_angle)*effect[i].speed;
				effect[i].y += sin(effect[i].m_angle)*effect[i].speed;
				//�X�s�[�h�v�Z
				if (effect[i].counter < 60) {
					effect[i].speed -= (0.2 + effect[i].counter*effect[i].counter / 3000.0);
				}
				if (effect[i].counter == 60) {
					effect[i].speed = 0;
					Enemy.se_flag[15] = 1;
					dn.flag = 1;
					dn.counter = 0;
					dn.size = 11;
					dn.time = 20;
				}
				//���邳�Ƒ傫���v�Z
				effect[i].r += 0.015;
				if (effect[i].counter < 51) {
					effect[i].bright += 5;
				}
				if (effect[i].counter >= 60) {
					effect[i].r += 0.04;
					effect[i].bright -= 255 / 30.0;
				}
				//�J�E���g�A�b�v�Ə����v�Z
				effect[i].counter++;
				if (effect[i].counter >= 90) {
					effect[i].flag = 0;
				}
				*/
				break;
			case 2://�{���G�t�F�N�g�i�L�����j
				   //���W�v�Z
				effect[i].x += cos(effect[i].m_angle)*effect[i].speed;
				effect[i].y += sin(effect[i].m_angle)*effect[i].speed;
				//���邳�v�Z
				if (effect[i].counter < 51) {
					effect[i].bright += 4;
				}
				if (effect[i].counter > 130 - 51) {
					effect[i].bright -= 4;
				}
				//�J�E���g�A�b�v�Ə����v�Z
				effect[i].counter++;
				if (effect[i].counter >= 130) {
					effect[i].flag = 0;
				}
				break;
			case 3://�{���̃G�t�F�N�g�i���C���j
				   //���W�v�Z
				effect[i].x += cos(effect[i].m_angle)*effect[i].speed;
				effect[i].y += sin(effect[i].m_angle)*effect[i].speed;
				//���邳�v�Z
				if (effect[i].counter < 51) {
					effect[i].bright += 2;
				}
				if (effect[i].counter > 130 - 51) {
					effect[i].bright -= 2;
				}
				//�J�E���g�A�b�v�Ə����v�Z
				effect[i].counter++;
				if (effect[i].counter >= 130) {
					effect[i].flag = 0;
				}
				break;
			case 4://��炢�{���G�t�F�N�g
				   //���邳�v�Z
				if (effect[i].counter >= 6) {
					effect[i].bright -= 255 / 6;
				}
				effect[i].r += 0.12;
				effect[i].counter++;
				if (effect[i].counter >= 12 || Player.GetFlag() != 1) {
					effect[i].flag = 0;
				}
				break;
			case 5:
				effect[i].counter++;
				if (effect[i].counter > 10) {//10�J�E���g�ȏ�ɂȂ�����
					effect[i].bright -= 25;//���邳�����Ȃ�����
				}
				if (effect[i].counter > 20) {//20�J�E���g�ȏ�ɂȂ�����
					effect[i].flag = 0;//����
				}
				break;
			case 6:
				effect[i].counter++;
				if (effect[i].counter > 10) {//10�J�E���g�ȏ�ɂȂ�����
					effect[i].bright -= 25;//���邳�����Ȃ�����
				}
				if (effect[i].counter > 20) {//20�J�E���g�ȏ�ɂȂ�����
					effect[i].flag = 0;//����
				}
				break;
			default:
				printfDx("effect�ݒ�G���[\n");
				break;
			}
		}
	}
}

//�{����o�^
void  Effect_c::EnterBom() {
	int k;
	Player.SetBomFlag(1);
	Player.SetBomCounter(0);
	Player.SetBomType(0);
	Player.SetInvCount(1);//���G��
	Enemy.se_flag[14] = 1;//�{�����炷

	/*
	if ((k = SearchEffect()) != -1) {
		effect[k].flag = 1;
		effect[k].counter = 0;
		effect[k].type = 2;//�{���̃L�����E���̃G�t�F�N�g
		effect[k].bright = 0;
		effect[k].angle = 0;
		effect[k].m_angle = -M_PI / 2;
		effect[k].speed = 0.7;
		effect[k].r = 1;
		effect[k].effect = 2;
		effect[k].img = bom_image[2];
		effect[k].x = 260;
		effect[k].y = 300;
	}
	*/
}

//���ŃG�t�F�N�g�̓o�^�󂫔ԍ���T��
int Effect_c::SearchDelEffect() {
	for (int i = 0; i<100; i++) {
		if (del_effect[i].flag == 0)
			return i;
	}
	return -1;
}

//���ŃG�t�F�N�g��o�^����
void Effect_c::EnterDelEffect(int i) {
	int k = SearchDelEffect();
	if (k != -1) {
		del_effect[k].flag = 1;//�t���O�𗧂Ă�
		del_effect[k].counter = 0;
		del_effect[k].color = Enemy.GetBackColor(i);//�G�̔w�i�F�����ŐF�ɐݒ肷��
		del_effect[k].x = Enemy.GetX(i);//�G�̍��W�����ňʒu�ɃZ�b�g
		del_effect[k].y = Enemy.GetY(i);
	}
}

void Effect_c::EnterBossDelEffect(int stage) {
	int k = SearchDelEffect();
	if (k != -1) {
		if (stage == 5) {
			del_effect[k].flag = 3;//�t���O�𗧂Ă�
			del_effect[k].counter = 0;
			del_effect[k].x = Boss.GetX();//�G�̍��W�����ňʒu�ɃZ�b�g
			del_effect[k].y = Boss.GetY();
		}
	else{
			del_effect[k].flag = 2;//�t���O�𗧂Ă�
			del_effect[k].counter = 0;
			del_effect[k].x = Boss.GetX();//�G�̍��W�����ňʒu�ɃZ�b�g
			del_effect[k].y = Boss.GetY();
		}
			}
}

//���ŃG�t�F�N�g���v�Z�E�G�t�F�N�g��o�^����
void Effect_c::CalcDelEffect() {
	int k;
	for (int i = 0; i<DEL_EFFECT_MAX; i++) {
		if (del_effect[i].flag > 0) {
			if ((k = SearchEffect()) != -1) {//�󂫔ԍ�����
				switch (del_effect[i].flag) {
				case 1:
					if (del_effect[i].counter % 2 == 0) {// 1/30�b���Z�b�g

						memset(&effect[k], 0, sizeof(effect_t));//������
						effect[k].flag = 1;//�t���O�𗧂Ă�
						effect[k].bright = 255;//�P�x���ő�l��
						effect[k].angle = 0;
						effect[k].color = del_effect[i].counter / 12 % 5;
						effect[k].effect = 0;//1�͌��G�t�F�N�g�B���G�t�F�N�g�ɃZ�b�g����
						effect[k].img = img_del_effect[effect[k].color];//���ł���摜���Z�b�g
						effect[k].type = 0;//�G�t�F�N�g�̎�ނ�0��(�G���̏��ŃG�t�F�N�g��0�Ƃ���)
						effect[k].x = del_effect[i].x;//���W���Z�b�g
						effect[k].y = del_effect[i].y;
						effect[k].speed = 0;
					}
					if (del_effect[i].counter > 60) {
						del_effect[i].flag = 0;
					}
					break;
				case 2:
					if (del_effect[i].counter % 9 == 0) {

						memset(&effect[k], 0, sizeof(effect_t));//������
						effect[k].flag = 1;
						effect[k].bright = 255;//�P�x���ő�l��
						effect[k].angle = 0;
						effect[k].color = del_effect[i].counter / 9;
						effect[k].effect = 0;
						effect[k].img = boss_del_effect[effect[k].color];//���ł���摜���Z�b�g
						effect[k].type = 5;//�G�t�F�N�g�̎�ނ�0��(�G���̏��ŃG�t�F�N�g��0�Ƃ���)
						effect[k].x = del_effect[i].x;//���W���Z�b�g
						effect[k].y = del_effect[i].y;
						effect[k].speed = 0;
						effect[k].r = 1;
					}
					if (del_effect[i].counter > 72) {
						del_effect[i].flag = 0;
					}
					break;
				case 3:
					if (del_effect[i].counter % 9 == 0) {
						memset(&effect[k], 0, sizeof(effect_t));//������
						effect[k].flag = 1;//�t���O�𗧂Ă�
						effect[k].bright = 255;
						effect[k].angle = 0;
						effect[k].color = del_effect[i].counter / 9;
						effect[k].effect = 0;
						effect[k].img = boss_del_effect[effect[k].color];//���ł���摜���Z�b�g
						effect[k].type = 6;//�G�t�F�N�g�̎�ނ�0��(�G���̏��ŃG�t�F�N�g��0�Ƃ���)
						effect[k].x = del_effect[i].x;//���W���Z�b�g
						effect[k].y = del_effect[i].y;
						effect[k].speed = 0;
						effect[k].r = 2;
					}
					if (del_effect[i].counter > 72) {
						del_effect[i].flag = 0;
					}
					break;
				}
			}
			del_effect[i].counter++;
		}
	}
}

//�{���v�Z
void Effect_c::BomCalc() {
	int n, k, shot_angle[4] = { 0,M_PI,M_PI / 2,M_PI*1.5 };//4���G�t�F�N�g����Ԋp�x
	if ((Player.GetFlag() == 0 || Player.GetFlag() == 1) && Player.GetBomFlag() == 0) {//�{�����I�t�Ȃ�
		if (Player.GetCoolFlag() == false) {
			if ((Controller.k_Get(Config.k_bom) == 1 || Controller.g_Get(Config.g_bom) == 1) && Player.GetEnergy() > 1200) {//�G�l���M�[���\���ȏ�ԂŃ{���{�^���������ꂽ��
				Player.SetEnergyMax(Player.GetEnergyMax() - 1200);
				Player.SetEnergy(Player.GetEnergy() - 1200);
				EnterBom();
				if (Player.GetFlag() == 1) {
					Player.SetFlag(0);
				}
			}
		}
	}
	if (Player.GetBomFlag() == 1) {//�{�����o�^����Ă�����
		if (Player.GetBomCounter() % 10 == 0) {//1/6�b�ɂP��
			n = (Player.GetBomCounter() / 10);
			if (n<4 && (k = SearchEffect()) != -1) {
				if (n == 0) {
					bom_x = Player.GetX();
					bom_y = Player.GetY();
				}
			    effect[k].x = bom_x;//���W
			    effect[k].y = bom_y;
				effect[k].flag = 1;
				effect[k].counter = 0;
				effect[k].type = 1;//�G�t�F�N�g�ԍ��P�F�{���̃G�t�F�N�g
				effect[k].bright = 5;
				effect[k].angle = Enemy.Rang(M_PI);//�摜�̌����̓����_��
				effect[k].m_angle = shot_angle[n] - M_PI / 4;//��ԕ���
				effect[k].speed = 0;//�X�s�[�h
				effect[k].r = 0.5;//�傫��
				effect[k].effect = 2;//���u�����h
				effect[k].img = bom_image[0];//�摜		
			}
		}
		Player.SetBomCounter(Player.GetBomCounter()+1);
		if (Player.GetBomCounter() < 40) {
			bright_set.bright = 255 - Player.GetBomCounter() * 5;//��ʂ̖��邳�ݒ�(�Â�)
		}
		if (Player.GetBomCounter() > 90) {
			bright_set.bright = 255 - 40 * 5 + (Player.GetBomCounter() - 90) * 5;//��ʂ̖��邳�ݒ�(���邭)
		}
		if (Player.GetBomCounter()>130) {
			Player.SetBomFlag(0);
			bright_set.bright = 255;
		}
	}
}

//�h�K�[���Ƃ����ʂ̏���
void Effect_c::DnCalc() {
	if (dn.flag == 1) {
		dn.x = (int)Enemy.Rang(dn.size);
		dn.y = (int)Enemy.Rang(dn.size);
		dn.counter++;
		if (dn.counter>dn.time) {//�w�肳�ꂽ���Ԃ����ƏI���
			dn.flag = 0;
			dn.x = 0;
			dn.y = 0;
		}
	}
}

void Effect_c::EnterDyingBomEffect() {
	int k;
	if (Player.GetFlag() == 1) {
		if (Player.GetCount() % 2 == 0) {
			if ((k = SearchEffect()) != -1) {
				effect[k].flag = 1;
				effect[k].counter = 0;
				effect[k].type = 4;//��炢�{���G�t�F�N�g
				effect[k].bright = 255;
				effect[k].angle = Enemy.Rang(M_PI);
				effect[k].speed = 0;
				effect[k].r = 0;
				effect[k].effect = 2;
				effect[k].img = img_del_effect[GetRand(4)];
				effect[k].x = Player.GetX();
				effect[k].y = Player.GetY();
			}
		}
	}
}

void Effect_c::Draw(int type) {
	for (int i = 0; i<EFFECT_MAX; i++) {
		if (effect[i].flag>0 && effect[i].type == type) {
			if (effect[i].effect == 1) {//�G�t�F�N�g�����G�t�F�N�g�Ȃ�
				SetDrawBlendMode(DX_BLENDMODE_ADD, effect[i].bright);
			}
				if (effect[i].effect == 2){//�G�t�F�N�g�����G�t�F�N�g�Ȃ�
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, effect[i].bright);
			}

			DrawRotaGraphF(effect[i].x+dn.x , effect[i].y+dn.y , effect[i].r, effect[i].angle, effect[i].img, TRUE);

			if (effect[i].effect == 1 || effect[i].effect == 2) {
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}
		}
	}
}

void Effect_c::DrawEffect() {
	Draw(0);//�G�����ʃG�t�F�N�g
	Draw(1);//�{���̃G�t�F�N�g
  //Draw(4);//��炢�{���̃G�t�F�N�g
	Draw(5);
	Draw(6);
}

void Effect_c::Loop() {
	DnCalc();//�����ʂ̏���
	CalcDelEffect();//���ŃG�t�F�N�g�̌v�Z
	CalcEffect();//�G�t�F�N�g�̌v�Z
	BomCalc();//�{���v�Z
	//EnterDyingBomEffect();

	DrawEffect();//�G�t�F�N�g���܂Ƃ߂ĕ`��
}

void Effect_c::Initialize() {
	memset(effect, 0, sizeof(effect_t)*EFFECT_MAX);
	memset(del_effect, 0, sizeof(del_effect_t)*DEL_EFFECT_MAX);
	memset(&bright_set, 0, sizeof(bright_set_t));
	memset(&dn, 0, sizeof(dn_t));

	bright_set.bright = 255;
}

void Effect_c::StartIni() {
	LoadDivGraph("material/img/effect/break.png", 5, 5, 1, 64, 64, img_del_effect);
	LoadDivGraph("material/img/effect/boss break.png", 8, 8, 1, 128, 128, boss_del_effect);
	bom_image[0] = LoadGraph("material/img/effect/bomb_effect.png");
	bom_image[1] = LoadGraph("material/img/effect/bom1.png");
	//bom_image[2] = LoadGraph("material/img/player/body.png");
}

int Effect_c::GetdnX() {
	return dn.x;
}

int Effect_c::GetdnY() {
	return dn.y;
}