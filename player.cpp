#include "define.h"

void Player_obj::Initialize() {
	for (int i = 0; i < P_SHOT_MAX; i++) {
		shot[i].flag = false;
		shot[i].atk = 0;
		shot[i].counter = 0;
		shot[i].type = 0;
		shot[i].x = 0;
		shot[i].y = 0;
		shot[i].angle = 0;
		shot[i].speed = 0;
	}


	memset(&bom, 0, sizeof(bom_t));
	x = (FIELD_MAX_X + FIELD_X*2) / 2;
	y = FIELD_MAX_Y - 100;
	move = 1.0;
	n = 0;
	l = 0;
	shot_mode = normal_shot;
	laser_width = 80;
	cool_flag = false;
	d_time = 0;

	if (charge  < 50) {
		shot_sx[0] = 0;
		shot_sy[0] = -60;
	}

	if (Control.GetState() == s1_loading) {
		energy_max = 6000;
		player_num = DEFAULT_P_NUM;
		charge = 0;
		flag = 0;
		inv_count = 0;
	}
	energy = energy_max;
}

void Player_obj::StartIni() {
	recover_ene = 4;
	LoadDivGraph("material/img/player/player.png", 12, 4, 3, 77, 77, gh);
	LoadDivGraph("material/img/player/player break.png", 4, 4, 1, 77, 77, gh2);
	shot_image[0] = LoadGraph("material/img/player/p_bullet.png");
	shot_image[1] = LoadGraph("material/img/player/homing.png");
}

void Player_obj::Draw() {
	if (Control.GetMode() == game_play) {
		d_time++;
		if (d_time % 10 == 0) {
			k++;
			k %= 4;
		}
		if (flag == 1 && count % 5 == 0) {
			l++;
			l %= 4;
		}
	}
	//���@�{�̂̕`��
	if (flag == 1) {
		DrawRotaGraphF(x, y, 0.7f, 0.0f, gh2[l], TRUE);
	}else if (inv_count % 2 == 0 || Control.GetMode() != game_play) {
		DrawRotaGraphF(x, y, 0.7f, 0.0f, gh[4 * n + k], TRUE);
	}
	if (Control.GetMode() == game_play && Control.GetState() < s1_talk_f ) {
	//�����蔻��̕`��
	if (Controller.g_Get(Config.g_slow) > 0 || Controller.k_Get(Config.k_slow) > 0) {
		DrawCircle(x, y, P_RANGE, GetColor(255, 0, 0));
	}
		//���@�̕��e�̕`��
		for (int i = 0; i < P_SHOT_MAX; i++) {
			if (shot[i].flag == true) {
				DrawRotaGraphF(shot[i].x, shot[i].y, 1.0f, shot[i].angle+M_PI/2, shot_image[shot[i].type], TRUE);
			}
		}
	}
}

void Player_obj::Calc() {
	if (flag == 1) {//��炢�{����t���Ȃ�
		Effect.bright_set.bright = 80;//�Â�
		if (count > 10) {//0.33�b��炢�{�����󂯕t����
			flag = 2;    //1:��炢�{����t���@2:����ŕ����オ�蒆
			count = 0;
			Effect.bright_set.bright = 255;
		}
	} 
	if (count == 0 && flag == 2) {//���񂾏u�ԂȂ�
		x = (FIELD_MAX_X + FIELD_X * 2) / 2;//���W�Z�b�g
		y = FIELD_MAX_Y - 100;
		energy_max = 6000;
		energy = energy_max;
		charge = 0;
		player_num--;
		death_count++;
		Control.erosion += EROSION_MAX / 100;
		l = 0;
		Enemy.se_flag[4] = 1;
		if (Control.GetScore() >= 10000) {
			Control.AddScore(-10000);
		}
		else {
			Control.AddScore(-1 * Control.GetScore());
		}
		inv_count++;//���G��Ԃ�
	}else if (flag == 2) {//���|�b�v����̖��G��ԂȂ�
		inv_count++;
			if (inv_count > 120) {//2�b�o�߂�
				inv_count = 0;
				flag = 0;//�ʏ��Ԃɖ߂�
			}
		}else if (flag == 3) {//�V�[���h���Ȃ�
			if ((Controller.k_Get(Config.k_change) == 0 && Controller.g_Get(Config.g_change) == 0) 
				|| cool_flag == true ) {//�V�[���h�𒣂�̂���߂�(��߂�������)
				inv_count = 0;
				shield_range = 0;
				flag = 0;//�ʏ��Ԃɖ߂�
			}
		}else if (inv_count > 0) {//�{�����Ȃ��
		inv_count++;

		//�{�����̎��@�̎��͂̒e�̖���������
		for (int s = 0; s < SHOT_MAX; s++) {//�G�V���b�g����
			if (Enemy.GetShotFlag(s) > 0) {//���̃V���b�g���o�^����Ă�����
				for (int t = 0; t < SHOT_BULLET_MAX; t++) {//�e����
					if (Enemy.GetBulletFlag(s, t) == 1) {//�e���o�^����Ă�����
						if (Judge.JudgeES(s, t, 200) == 1) {
							Enemy.SetBulletFlag(s, t, 0);//�e���I�t
						}
					}
				}
			}
		}
		for (int t = 0; t < BOSS_BULLET_MAX; t++) {//�e����
			if (Boss.GetBulletFlag(t) >0) {//�e���o�^����Ă�����
				if (Judge.JudgeBS(t, 200) == 1 && Boss.GetBulletFlag(t) != 10) {
					Boss.SetBulletFlag(t, 0);//�e���I�t
				}
			}
		}
		//�L����
		if (inv_count > 150) {//2.5�b�ȏソ������
			inv_count = 0;//�߂�
		}
	}

	if (Controller.k_Get(Config.k_left) > 0 || Controller.g_Get(Config.g_left) > 0 || Controller.k_Get(Config.k_right) > 0 || Controller.g_Get(Config.g_right) > 0) {
		if (Controller.k_Get(Config.k_up) > 0 || Controller.g_Get(Config.g_up) > 0 || Controller.k_Get(Config.k_down) > 0 || Controller.g_Get(Config.g_down) > 0) {
			//�΂߂̎��ړ��W����1.0�ɐݒ�
			move = 1.0;
		}
	}
	else {
		//�΂߂���Ȃ���΃��[�g2�ɐݒ�
		move = sqrt(2.0);
	}
	if (flag == 1) {
		n = 0;
	}
	else {

		if ((Controller.k_Get(Config.k_down) > 0 || Controller.g_Get(Config.g_down) > 0) && y + 4 * move < FIELD_MAX_Y + FIELD_Y - 10) {
			if (flag == 3) {
				y += 4.0 * move / 4;
			}
			else if (Controller.k_Get(Config.k_slow) > 0 || Controller.g_Get(Config.g_slow) > 0) {
				y += 4.0 * move / 3;
			}
			else {
				y += 4.0 * move;
			}
		}
		if ((Controller.k_Get(Config.k_up) > 0 || Controller.g_Get(Config.g_up) > 0) && y - 4 * move > FIELD_Y + 10) {
			if (flag == 3) {
				y -= 4.0 * move / 4;
			}
			else if (Controller.k_Get(Config.k_slow) > 0 || Controller.g_Get(Config.g_slow) > 0) {
				y -= 4.0 * move / 3;
			}
			else {
				y -= 4.0 * move;
			}
		}

		if ((Controller.k_Get(Config.k_right) > 0 || Controller.g_Get(Config.g_right) > 0) && x + 4 * move < FIELD_MAX_X + FIELD_X - 10) {
			if (flag == 3) {
				x += 4.0 * move / 4;
			}
			else if (Controller.k_Get(Config.k_slow) > 0 || Controller.g_Get(Config.g_slow) > 0) {
				x += 4.0 * move / 3;
			}
			else {
				x += 4.0 * move;
			}
			n = 1;
		}
		if ((Controller.k_Get(Config.k_left) > 0 || Controller.g_Get(Config.g_left) > 0) && x - 4 * move > FIELD_X + 10) {
			if (flag == 3) {
				x -= 4.0 * move / 4;
			}
			else if (Controller.k_Get(Config.k_slow) > 0 || Controller.g_Get(Config.g_slow) > 0) {
				x -= 4.0 * move / 3;
			}
			else {
				x -= 4.0 * move;
			}
			n = 2;
		}
		else if(Controller.k_Get(Config.k_right) == 0 && Controller.g_Get(Config.g_right) == 0){
			n = 0;
		}
	}
	count++;
}

void Player_obj::ChangeShotMode(){
	if (Controller.k_Get(Config.k_change) == 1 || Controller.g_Get(Config.g_change) == 1) {
		shot_mode++;
		shot_mode %= mode_num;
	}
	}

void Player_obj::Loop() {
	Calc();
	ShotMain();
}

//���@�V���b�g�̓o�^�\�ԍ���Ԃ�
int Player_obj::SearchShot() {
	for (int i = 0; i<P_SHOT_MAX; i++) {
		if (shot[i].flag == false)
			return i;
	}
	return -1;
}

//�ʏ�V���b�g�o�^
void Player_obj::PlayerShot() {
	int k;
	for (int i = 0; i < num_option; i++) {
		/*if (i >= 2 && Control.g_count / 3 % 3 != 0) {
			break;
		}*/
		if ((k = SearchShot()) != -1) {
			shot[k].flag = true;
			shot[k].counter = 0;
			if (i < 2) {
				shot[k].speed = 20;
				shot[k].angle = -M_PI / 2;
				shot[k].type = 0;
			}
			else if (i == 2) {
				shot[k].speed = 30;
				shot[k].angle = -M_PI * 7 / 12;
				shot[k].type = 1;
			}
			else {
				shot[k].speed = 30;
				shot[k].angle = -M_PI * 5 / 12;
				shot[k].type = 1;
			}
			
			shot[k].x = x + shot_sx[i];
			shot[k].y = y + shot_sy[i];
			if (Control.GetLevel() == 'E') {
				shot[k].atk = 15.0 * (1 + 0.25*num_option) / num_option;
				if (i > 2) {
					shot[k].atk = shot[k].atk * 1.0 / 2;
				}
			}
			else {
				if (cool_flag == false) {
					shot[k].atk = 15.0 * (0.5 + energy / 12000.0)* (1.0 + 0.40*num_option) / num_option;
				}
				else {
					shot[k].atk = 15.0 * 0.3* (1.0 + 0.40*num_option) / num_option;
				}
				if (i > 2) {
					shot[k].atk = shot[k].atk * 1.0 / 3;
				}
			}
			
		}
	}
	Enemy.se_flag[1] = 1;//���ˉ��I��
}

//�ᑬ�ʏ�V���b�g�o�^
void Player_obj::SlowPlayerShot() {
	int k;
	for (int i = 0; i < num_option; i++) {
		if ((k = SearchShot()) != -1) {
			shot[k].flag = true;
			shot[k].counter = 0;
			shot[k].angle = -M_PI / 2;
			shot[k].speed = 20;
			shot[k].x = x + shot_sx[i] / 2;//�ᑬ���Ȃ�ʒu�𒆐S����
			shot[k].y = y + shot_sy[i] / 2;
			if (Control.GetLevel() == 'E') {
				shot[k].atk = 15 * (1 + 0.25*num_option) / num_option;
			}
			else {
				shot[k].atk = 15 * (0.5 + energy / 12000.0)* (1 + 0.25*num_option) / num_option;
			}
			shot[k].type = 0;
		}
	}
	Enemy.se_flag[1] = 1;
}

void Player_obj::Shield() {
	if (Controller.k_Get(Config.k_change) == 1 || Controller.g_Get(Config.g_change) == 1) {
		Enemy.se_flag[5] = 1;
	}
	flag = 3;
	inv_count = 2;
	shield_range = 40;
	DrawCircle(x, y, shield_range, GetColor(255, 255, 255), 0, 2);
	energy -= 40 + recover_ene;
}

void Player_obj::Laser() {
	//���[�U�[���ɓ������e�̖���������
	for (int s = 0; s < SHOT_MAX; s++) {//�G�V���b�g����
		if (Enemy.GetShotFlag(s) > 0) {//���̃V���b�g���o�^����Ă�����
			for (int t = 0; t < SHOT_BULLET_MAX; t++) {//�e����
				if (Enemy.GetBulletX(s, t) >= x - laser_width / 2 && Enemy.GetBulletX(s, t) <= x + laser_width / 2) {
					Enemy.SetBulletFlag(s, t, 0);//���[�U�̒��ɓ������e������
				}
			}
		}
	}
	for (int t = 0; t < BOSS_BULLET_MAX; t++) {//�e����
		if (Boss.GetBulletFlag(t) == 1) {//�e���o�^����Ă�����
			if (Boss.GetBulletX(t) >= x - laser_width / 2 && Boss.GetBulletX(t) <= x + laser_width / 2) {
				Boss.SetBulletFlag(t, 0);//�e���I�t
			}
		}
	}

	//���[�U�[�̕`��
		DrawBox(x - laser_width / 2, y - 77 / 2, x + laser_width / 2, -20, GetColor(255, 255, 255), 1);
	energy -= 30 + recover_ene;
}

//�V���b�g�o�^��
void Player_obj::EnterShot() {
	if (flag != 1) {
		if ((Controller.k_Get(Config.k_change) > 0 || Controller.g_Get(Config.g_change) > 0) && cool_flag == false) {
			Shield();
		}
		else if (Controller.k_Get(Config.k_shot) > 0 || Controller.g_Get(Config.g_shot) > 0) {
			shot_counter++;
			if (shot_counter % 3 == 0) {//3�J�E���g��1��
				if ((Controller.k_Get(Config.k_slow) > 0 || Controller.g_Get(Config.g_slow) > 0)) {//�ᑬ�ړ����Ȃ�
					SlowPlayerShot();
				}
				else {
					PlayerShot();
				}
			}
		}
		else {
			shot_counter = 0;
		}
	}
}

//��ԋ߂��G��T���Ċp�x���Z�b�g����
void Player_obj::CalcHoming(int k) {
	int i, d, num = -1, min = -1;
	double x, y;
	if (Boss.GetBossFlag() == 0) {//�{�X�����Ȃ���
		for (i = 0; i<ENEMY_MAX; i++) {//�G�̑�����
			if (Enemy.GetFlag(i) == 1) {
			if(	Enemy.GetEneBulType(i)!=8){
				x = (Enemy.GetX(i) - shot[k].x);
				y = (Enemy.GetY(i) - shot[k].y);
				d = (int)(x*x + y*y);//�V���b�g�ƓG�̋���
				if (d < min || min == -1) {//�v�Z���ʂ��ŏ��l���܂��i�[���Ă��Ȃ��Ȃ�
					num = i;//�ԍ��L�^
					min = d;//�����L�^
				}
				}
			}
		}
	}
	//�߂��G������������A���邢�̓{�X�����āAHP������Ƃ��͊p�x���Z�b�g
	if (num != -1 || (Boss.GetBossFlag() == 1 && Boss.GetBossHp()>0)) {
		if (Boss.GetBossFlag() == 0) {
			x = Enemy.GetX(num) - shot[k].x;
			y = Enemy.GetY(num) - shot[k].y;
		}
		else {
			x = Boss.GetX() - shot[k].x;
			y = Boss.GetY() - shot[k].y;
		}
		shot[k].angle = atan2(y, x);
	}
}

//�V���b�g�̌v�Z
void Player_obj::ShotCalc() {
	if (charge < 400) {
		shot_sx[0] = 0;
		shot_sy[0] = -60;
		num_option = 1;
	}
	else if (charge < 800) {
		shot_sx[0] = -20;
		shot_sx[1] = 20;
		shot_sy[0] = -30;
		shot_sy[1] = -30;
		num_option = 2;
	}
	else if (charge < 1200) {
		shot_sx[0] = -20;
		shot_sx[1] = 20;
		shot_sx[2] = -30;
		shot_sy[0] = -30;
		shot_sy[1] = -30;
		shot_sy[2] = 30;
		num_option = 3;
	}
	else {
		shot_sx[0] = -20;
		shot_sx[1] = 20;
		shot_sx[2] = -30;
		shot_sx[3] = 30;
		shot_sy[0] = -30;
		shot_sy[1] = -30;
		shot_sy[2] = 30;
		shot_sy[3] = 30;
		num_option = 4;
	}
	for (int i = 0; i<P_SHOT_MAX; i++) {
		if (shot[i].flag == true) {
			int dranx = shot[i].speed + 11 / 2, drany = shot[i].speed + 55 / 2;//11,55�͒e�̑傫��
			if (shot[i].type == 1) {
				CalcHoming(i);
			}
			shot[i].x += cos(shot[i].angle)*shot[i].speed;
			shot[i].y += sin(shot[i].angle)*shot[i].speed;
			shot[i].counter++;
			if (shot[i].x<-dranx || shot[i].x>FIELD_MAX_X + FIELD_X + dranx || shot[i].y<-drany || shot[i].y>FIELD_MAX_Y + FIELD_Y + drany) {//��ʂ���O�ꂽ��
				shot[i].flag = 0;
			}
		}
	}
	if (energy < 0) {
		energy = 0;
		cool_flag = true;
	}
	else if (energy < energy_max) {
		energy += recover_ene;
	}
	if (energy >= energy_max) {
		energy = energy_max;
		cool_flag = false;
		if (charge < 1200) {
			charge++;
		}
	}
}

//�L�����N�^�V���b�g�Ɋւ���֐�
void Player_obj::ShotMain() {
	ShotCalc();//�V���b�g�̋O���v�Z
	EnterShot();//�V���b�g�o�^
}

double Player_obj::GetX() {
	return x;
}

double Player_obj::GetY() {
	return y;
}

bool Player_obj::GetShotFlag(int i) {
	return shot[i].flag;
}

int Player_obj::GetShotAtk(int i) {
	return shot[i].atk;
}

int Player_obj::GetShotCounter(int i) {
	return shot[i].counter;
}

int Player_obj::GetShotType(int i) {
	return shot[i].type;
}

double Player_obj::GetShotX(int i) {
	return shot[i].x;
}

double Player_obj::GetShotY(int i) {
	return shot[i].y;
}

double Player_obj::GetShotSpeed(int i) {
	return shot[i].speed;
}

double Player_obj::GetShotAngle(int i) {
	return shot[i].angle;
}

int Player_obj::GetShotRange(int i) {
	return shot_range[i];
}

void Player_obj::SetShotFlag(int i, bool setflag) {
	shot[i].flag = setflag;
}

void Player_obj::SetCount(int setcount) {
	count = setcount;
}

int Player_obj::GetFlag() {
	return flag;
}

void Player_obj::SetFlag(int setflag) {
	flag = setflag;
}

int Player_obj::GetInvCount() {
	return inv_count;
}

void Player_obj::SetInvCount(int setinv_count) {
	inv_count = setinv_count;
}

int Player_obj::GetBomFlag() {
	return bom.flag;
}

void Player_obj::SetBomFlag(int setflag) {
	bom.flag = setflag;
}

int Player_obj::GetBomType() {
	return bom.type;
}

void Player_obj::SetBomType(int settype) {
	bom.type = settype;
}

int Player_obj::GetBomCounter() {
	return bom.counter;
}

void Player_obj::SetBomCounter(int setcounter) {
	bom.counter = setcounter;
}

double Player_obj::GetBomX() {
	return bom.x;
}

double Player_obj::GetBomY() {
	return bom.y;
}

int Player_obj::GetCount() {
	return count;
}

int Player_obj::GetShotMode() {
	return shot_mode;
}

int Player_obj::GetShiledRange() {
	return shield_range;
}

int Player_obj::GetLaserWidth() {
	return laser_width;
}

int Player_obj::GetEnergy() {
	return energy;
}

int Player_obj::GetEnergyMax() {
	return energy_max;
}

void Player_obj::SetEnergy(int setenergy) {
	energy = setenergy;
}

void Player_obj::SetEnergyMax(int setene_max){
	energy_max = setene_max;
}


bool Player_obj::GetCoolFlag() {
	return cool_flag;
}

int Player_obj::GetCharge() {
	return charge;
}

int Player_obj::GetPlayerNum() {
	return player_num;
}

void Player_obj::SetPlayerNum(int setplayer_num) {
	player_num = setplayer_num;
}

void Player_obj::SetShotSpeed(int s,double setspeed) {
	shot[s].speed = setspeed;
}