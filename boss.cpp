#include "define.h"

void Boss_obj::Erosion() {//�Z�H�x�̏㏸
	if (Control.erosion < EROSION_MAX * 99 / 100) {
		Control.erosion += EROSION_MAX / 20 / 3600;
	}
}

int Boss_obj::SerchBossShot() {//�󂫔ԍ���Ԃ�
	for (int i = 0; i<BOSS_BULLET_MAX; i++) {
		if (boss_shot.bullet[i].flag == 0)
			return i;
	}
	return -1;
}

int Boss_obj::SerchBossShotA() {//�󂫔ԍ���Ԃ�(�ǉ�)
	for (int i = 0; i<600; i++) {
		if (boss_shot.bullet[i].flag == 0)
			return i;
	}
	return -1;
}

int Boss_obj::SerchBossShotB() {//�󂫔ԍ���Ԃ�(�ǉ�)
	for (int i = 600; i<1200; i++) {
		if (boss_shot.bullet[i].flag == 0)
			return i;
	}
	return -1;
}

int Boss_obj::SerchBossShotC() {//�󂫔ԍ���Ԃ�(�ǉ�)
	for (int i = 1200; i<1800; i++) {
		if (boss_shot.bullet[i].flag == 0)
			return i;
	}
	return -1;
}

int Boss_obj::SerchBossShotD() {//�󂫔ԍ���Ԃ�(�ǉ�)
	for (int i = 1800; i<2400; i++) {
		if (boss_shot.bullet[i].flag == 0)
			return i;
	}
	return -1;
}

int Boss_obj::SerchBossShotE() {//�󂫔ԍ���Ԃ�(�ǉ�)
	for (int i = 2400; i<3000; i++) {
		if (boss_shot.bullet[i].flag == 0)
			return i;
	}
	return -1;
}


double Boss_obj::BossAtan2() {//���@�ƓG�Ƃ̐����p�x
	return atan2(Player.GetY() - boss.y, Player.GetX() - boss.x);
}

//�����I�v�Z��������o�^������(�w�莞��t�Œ�ʒu�ɖ߂�)
void Boss_obj::InputPhy(double x, double y, int t) {
	double ymax_x, ymax_y;
	if (t == 0) {
		t = 1;
	}
	boss.phy.flag = 1;//�o�^�I��
	boss.phy.counter = 0;//�J�E���^������
	boss.phy.set_t = t;//�ړ��ɂ����鎞�Ԃ��Z�b�g
	ymax_x = boss.x - x;//�ړ���������������
	boss.phy.v0x = 2 * ymax_x / t;//���������̏����x
	boss.phy.ax = 2 * ymax_x / (t*t);//���������̉����x
	boss.phy.prex = boss.x;//����x���W
	ymax_y = boss.y - y;//�ړ���������������
	boss.phy.v0y = 2 * ymax_y / t;//���������̏����x
	boss.phy.ay = 2 * ymax_y / (t*t);//���������̉����x
	boss.phy.prey = boss.y;//����y���W
}

//�����I�L�����N�^�ړ��v�Z
void Boss_obj::CalcPhy() {
	double t = boss.phy.counter;
	boss.x = boss.phy.prex - ((boss.phy.v0x*t) - 0.5*boss.phy.ax*t*t);//���݂���ׂ�x���W�v�Z
	boss.y = boss.phy.prey - ((boss.phy.v0y*t) - 0.5*boss.phy.ay*t*t);//���݂���ׂ�y���W�v�Z
	boss.phy.counter++;
	if (boss.phy.counter >= boss.phy.set_t)//�ړ��ɂ����鎞�ԕ��ɂȂ�����
		boss.phy.flag = 0;//�I�t
}

//�{�X�̒e�����v�Z����
void Boss_obj::BossShotCalc() {
	int i;
	for (i = 0; i<BOSS_BULLET_MAX; i++) {
		if (boss_shot.bullet[i].flag>0) {
			if (boss_shot.bullet[i].speed == 0 && boss_shot.bullet[i].angle == 0) {
				boss_shot.bullet[i].x += boss_shot.bullet[i].vx;
				boss_shot.bullet[i].y += boss_shot.bullet[i].vy;
			}
			else {
				boss_shot.bullet[i].x += cos(boss_shot.bullet[i].angle)*boss_shot.bullet[i].speed;
				boss_shot.bullet[i].y += sin(boss_shot.bullet[i].angle)*boss_shot.bullet[i].speed;
			}
			boss_shot.bullet[i].counter++;
			if (boss_shot.bullet[i].counter>boss_shot.bullet[i].till) {
				if (boss_shot.bullet[i].x<-50 || boss_shot.bullet[i].x>FIELD_MAX_X + 50 ||
					boss_shot.bullet[i].y<-50 || boss_shot.bullet[i].y>FIELD_MAX_Y + 50)
					boss_shot.bullet[i].flag = 0;
			}
		}
	}
	boss_shot.counter++;
}
//�e�����Z�b�g
void Boss_obj::EnterBossShot() {
	memset(&boss_shot, 0, sizeof(boss_shot_t));//�e��񏉊���
	boss_shot.flag = 1;
	boss.w_time = 0;//�ҋ@����0
	boss.state = 2;//�e������Ԃ�
	boss.hp = boss.set_hp[boss.type];//HP�ݒ�
	boss.hp_max = boss.set_hp[boss.type];
}

//�{�X���Z�b�g
void Boss_obj::EnterBoss(int num, int stage) {
	if (num == 0) {//�{�X��J�n���̎���
		Enemy.Initialize();//�G���ƎG���̕������e������
		boss.x = BOSS_POS_X + adj_boss_x[stage - 1];//�{�X�̏������W
		boss.y = BOSS_POS_Y + adj_boss_y[stage - 1];
		boss.dx = boss.x;
		boss.dy = boss.y;
		boss.type = -1;//�e���̎��
	}
	warp_count = 0;
	warp_flag = 0;
	boss.flag = 1;
	boss.state = 1;//�ҋ@����Ԃ�
	boss.counter = 0;
	boss.graph_flag = 0;//�`��t���O��߂�
	boss.atk_flag = 0;
	boss.wx = boss.x;
	boss.wy = boss.y;
	boss.type++;
	n = 0;
	k = 0;
	if (boss.type == boss_form_num[stage - 1] ) {//�{�X���j��
		boss.flag = 0;
		Effect.EnterBossDelEffect(stage);
		Enemy.se_flag[3] = 1;
	}
	boss.w_time = 0;//�ҋ@���Ԃ�������
	if (num == 1) {
		Control.AddScore(10000 * (0.75 + 0.25*stage)*(1 + 0.2*boss.type) / 10 * 10);
	}
	for (int i = 0; i < 2; i++) {
		boss.graph_num[i] = boss_graph_num[stage - 1][i];
	}
	memset(&boss_shot, 0, sizeof(boss_shot_t));//�{�X�̒e������������
	if (stage != 3 && stage != 5) {
		InputPhy(BOSS_POS_X + adj_boss_x[stage - 1], BOSS_POS_Y + adj_boss_y[stage - 1], 60);//60�J�E���g�����Ė߂�
	}
}
//�{�X�̑ҋ@����
void Boss_obj::WaitAction() {
	boss.w_time++;
	if (boss.w_time > 140) {//140�J�E���g�ҋ@������e���Z�b�g
		EnterBossShot();
	}
}

//���X�{�X�̃��[�v�֌W
void Boss_obj::BossWarp() {
	warp_count++;
	if (warp_count == 1) {
		//���[�v�̏����̃��[�V�����ɓ���
		n = 1;
		k = 0;
	}else if (warp_count == 59) {
		//���ۂɍ��W�ړ��A���[�v�I����̃��[�V�����ɓ���
		boss.dx = boss.wx;
		boss.dy = boss.wy;
		boss.x = boss.wx;
		boss.y = boss.wy;
		n = 2;
		k = 0;
	}else if(warp_count==109){
		//�ʏ�ɖ߂�
		n = 0;
		k = 0;
		warp_flag = 0;
		warp_count = 0;
	}
}

//�{�X�̈ړ��Ɋ֌W����֐�
void Boss_obj::MoveBoss(int stage) {
	int t = boss_shot.counter % 540, num;
	if (t == 0) num = 0;
	if (warp_flag == 1) {
		BossWarp();
	}
	if (stage != 1 && stage != 3) {
		switch (stage) {
		case 4:
			switch (boss.type) {
			case 0:
				if (t == 0) {
					n = 1;
				}
				if (0 < t && t < 90) {
					n = 0;
					boss.dx = boss.x;
					boss.x--;
					boss.dy = boss.y;
					boss.y++;
				}
				if (180 < t && t < 360) {
					n = 2;
					boss.dx = boss.x;
					boss.x++;
					boss.dy = boss.y;
				}
				if (450 < t && t < 540) {
					n = 0;
					boss.dx = boss.x;
					boss.x--;
					boss.dy = boss.y;
					boss.y--;
				}
				break;
			case 1:
				if (t == 0) {
					n = 1;
					boss.dx = boss.x;
					boss.x = BOSS_POS_X + adj_boss_x[stage - 1];
					boss.dy = boss.y;
					boss.y = BOSS_POS_Y + adj_boss_y[stage - 1];
				}
				if (0 < t && t < 90) {
					n = 0;
					boss.dx = boss.x;
					boss.x--;
					boss.dy = boss.y + sin(M_PI * 2 / 130 * (Control.g_count % 130)) * 10;
				}
				if (180 < t && t < 360) {
					n = 2;
					boss.dx = boss.x;
					boss.x++;
					boss.dy = boss.y + sin(M_PI * 2 / 130 * (Control.g_count % 130)) * 10;
				}
				if (450 < t && t < 540) {
					n = 0;
					boss.dx = boss.x;
					boss.x--;
					boss.dy = boss.y + sin(M_PI * 2 / 130 * (Control.g_count % 130)) * 10;
				}
				break;
			case 2:
				if (t == 0) {
					n = 1;
					boss.dx = boss.x;
					boss.x = BOSS_POS_X + adj_boss_x[stage - 1];
					boss.dy = boss.y;
					boss.y = BOSS_POS_Y + adj_boss_y[stage - 1];
				}
				if (0 < t && t < 60) {
					n = 2;
					boss.dx = boss.x;
					boss.x++;
					boss.dy = boss.y + sin(M_PI * 2 / 130 * (Control.g_count % 130)) * 10;
					boss.y++;
				}
				if (120 < t && t < 180) {
					n = 0;
					boss.dx = boss.x;
					boss.x--;
					boss.dy = boss.y + sin(M_PI * 2 / 130 * (Control.g_count % 130)) * 10;
					boss.y++;
				}
				if (240 < t && t < 300) {
					n = 0;
					boss.dx = boss.x;
					boss.x--;
					boss.dy = boss.y + sin(M_PI * 2 / 130 * (Control.g_count % 130)) * 10;
					boss.y--;
				}
				if (360 < t && t < 420) {
					n = 2;
					boss.dx = boss.x;
					boss.x++;
					boss.dy = boss.y + sin(M_PI * 2 / 130 * (Control.g_count % 130)) * 10;
					boss.y--;
				}
				break;
			case 3:
				break;
			}
		case 5:
			switch (boss.type) {
			case 0:
				break;
			case 1:
				break;
			case 2:
				break;
			case 3:
				t = boss_shot.counter % 1080;
				if (t == 60) {
					warp_flag = 1;
					boss.wx = 100;
					boss.wy = 120;
				}
				if (t == 240) {
					warp_flag = 1;
					boss.wx = 350;
					boss.wy = 220;
				}
				if (t == 420) {
					warp_flag = 1;
					boss.wx = 300;
					boss.wy = 100;
				}
				if (t == 600) {
					warp_flag = 1;
					boss.wx = 100;
					boss.wy = 200;
				}
				if (t == 780) {
					warp_flag = 1;
					boss.wx = 150;
					boss.wy = 150;
				}
				if (t == 960) {
					warp_flag = 1;
					boss.wx = 270;
					boss.wy = 170;
				}
				break;
			case 4:
				break;
			}
			break;
		}
	}
}

//�{�X�̍s������
void Boss_obj::BossMain(int stage) {
	if (boss.type == boss_form_num[stage - 1] && boss.flag == 0 ) {
		boss.w_time++;
		if (boss.w_time == 2 && stage==5) {
			Control.HighScore();
			Control.whiteout_counter = 1;
		}
		if (boss.w_time == 120) {
			if (stage != 5) {
				Control.SetStage(Control.GetState() + 10);//�{�X���j��̃V�i���I�ɔ��
			}
		}
	}
	if (Control.g_count == boss.appear_count && boss.flag == 0) {//�J�n���ԂȂ�
		EnterBoss(0, stage);//�{�X��J�n
	}
	if (boss.flag == 0) {//�{�X���o�^����Ė�����Ζ߂�
		return;
	}
	MoveBoss(stage);
	if (boss.phy.flag == 1) {//�������Z�ړ��I���Ȃ�
		CalcPhy();//�����v�Z��
	}
	if (boss.state == 2 && boss.hp <= 0) {//�e�����ɑ̗͂������Ȃ�����
			EnterBoss(1, stage);//���̒e����o�^
	}
	if (boss.state == 1) {//�ҋ@���Ȃ�
		WaitAction();
	}
	if (boss.state == 2) {//�e�����Ȃ�
		BossShotMain(stage);//�e���֐���
		BossShotCalc();//�e���v�Z
	}
	boss.counter++;
	if (boss.counter % 10== 0) {
		k++;
		k %= boss.graph_num[boss.atk_flag];
	}
}

void Boss_obj::Loop(int stage){
	BossMain(stage);
	DrawBoss();
	DrawBullet();
	Erosion();
}


int Boss_obj::GetBossFlag() {
	return boss.flag;
}

void Boss_obj::Initialize(int stage){
	memset(&boss, 0, sizeof(boss_t));
	memset(&boss_shot, 0, sizeof(boss_shot_t));//�e��񏉊���

	if (stage != 5) {
		boss.appear_count = 60 * (60 + 1);//1�b�̓X�e�[�W���n�܂�܂ł̎���
	}
	else {
		boss.appear_count = 60;//�ŏI�ʂ͂����{�X 
	}
	for (int i = 0; i < BOSS_IMG_MAX; i++) {
		DeleteGraph(boss_image[0][i]);
		DeleteGraph(boss_image[1][i]);
	}

	switch (stage) {
	case 1:
		exrate = 1;
		LoadDivGraph("material/img/enemy/south boss.png", 4, 4, 1, 128, 128, boss_image[0]);
		LoadDivGraph("material/img/enemy/south boss attack.png", 6, 6, 1, 128, 128, boss_image[1]);//�U�����[�V����
		for (int i = 0; i < 3; i++) {
			boss.set_hp[i] = 8000;
			boss.back_type[i] = 1;
		}
		break;

	case 2:
		exrate = 2;
		LoadDivGraph("material/img/enemy/east boss.png", 12, 4, 3, 64, 64, boss_image[0]);
		LoadDivGraph("material/img/enemy/east boss attack.png", 18, 6, 3, 64, 64, boss_image[1]);//�U�����[�V����
		for (int i = 0; i < 3; i++) {
			boss.set_hp[i] = 10000;
			boss.back_type[i] = 1;
		}
		break;

	case 3:
		exrate = 1;
		LoadDivGraph("material/img/enemy/west boss.png", 12, 6, 2, 128, 128, boss_image[0]);
		for (int i = 0; i < 3; i++) {
			boss.set_hp[i] = 12000;
			boss.back_type[i] = 1;
		}
		break;

	case 4:
		exrate = 1;
		LoadDivGraph("material/img/enemy/north boss.png", 12, 4, 3, 128, 128, boss_image[0]);
		for (int i = 0; i < 3; i++) {
			boss.set_hp[i] = 14000;
			boss.back_type[i] = 1;
		}
		break;

	case 5:
		exrate = 1;
		LoadDivGraph("material/img/enemy/last boss.png", 18, 6, 3, 128, 128, boss_image[0]);
		LoadDivGraph("material/img/enemy/last boss lastmotion.png", 4, 4, 1, 192, 192, boss_image[1]);
		for (int i = 0; i < 5; i++) {
			if (i == 4) {
				boss.set_hp[i] = 32000;
			}
			else {
				boss.set_hp[i] = 16000;
			}
			boss.back_type[i] = 1;	
		}	
			break;
	}
}

void Boss_obj::StartIni() {
	font[0] = CreateFontToHandle("Microsoft Sans Serif", 20, -1, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
	//�e�摜�̃t�@�C����ǂݍ���
	LoadDivGraph("material/img/bullet/b0C.png", 5, 5, 1, 77, 77, bul_image[0]);
	LoadDivGraph("material/img/bullet/b1C.png", 6, 6, 1, 22, 22, bul_image[1]);
	LoadDivGraph("material/img/bullet/b2C.png", 10, 10, 1, 5, 120, bul_image[2]);
	LoadDivGraph("material/img/bullet/b3C.png", 5, 5, 1, 19, 34, bul_image[3]);
	LoadDivGraph("material/img/bullet/b4C.png", 10, 10, 1, 38, 38, bul_image[4]);
	LoadDivGraph("material/img/bullet/b5C.png", 4, 4, 1, 14, 16, bul_image[5]);
	LoadDivGraph("material/img/bullet/b6C.png", 3, 3, 1, 14, 18, bul_image[6]);
	LoadDivGraph("material/img/bullet/b7C.png", 9, 9, 1, 16, 16, bul_image[7]);
	LoadDivGraph("material/img/bullet/b8C.png", 10, 10, 1, 12, 18, bul_image[8]);
	LoadDivGraph("material/img/bullet/b9C.png", 3, 3, 1, 13, 19, bul_image[9]);

	//��F�e0��76x76�s�N�Z���ŁA5�F����A������͈�17�s�N�Z��
	InputBulletInfo(&bullet_info[0], 77, 77, 5, 17.0);
	InputBulletInfo(&bullet_info[1], 22, 22, 6, 4.0);
	InputBulletInfo(&bullet_info[2], 5, 120, 10, 2.5);
	InputBulletInfo(&bullet_info[3], 19, 34, 5, 2.0);
	InputBulletInfo(&bullet_info[4], 38, 38, 10, 2.0);
	InputBulletInfo(&bullet_info[5], 14, 16, 3, 3.5);
	InputBulletInfo(&bullet_info[6], 14, 18, 3, 2.0);
	InputBulletInfo(&bullet_info[7], 16, 16, 9, 2.5);
	InputBulletInfo(&bullet_info[8], 12, 18, 10, 1.5);
	InputBulletInfo(&bullet_info[9], 13, 19, 3, 2.0);

    hp_bar_image = LoadGraph("material/img/enemy/hp_boss.png");//�{�X��HP
}

void Boss_obj::DrawBoss() {
	if (boss.flag != 0) {
		DrawRotaGraphF(boss.dx + Effect.GetdnX(), boss.dy + Effect.GetdnY(), exrate*1.0f, 0.0f,
			boss_image[boss.atk_flag][n* boss.graph_num[boss.atk_flag] + k], TRUE);
			}
}

void Boss_obj::DrawHpBar() {
	if (boss.flag != 0) {
		/*if (boss.state != 2 && boss.type == 0) {
			rest_form_num = boss_form_num[(Control.GetState() + 1) / 2];
		}
		else {
			rest_form_num = boss_form_num[(Control.GetState() + 1) / 2] - boss.type - 1;
		}*/
		if (boss.state == 2 || boss.type != 0) {
			DrawFormatStringToHandle(FIELD_X + 15, FIELD_Y, GetColor(255, 255, 255), font[0], "%d", boss_form_num[(Control.GetState() + 1) / 2 - 1] - boss.type - 1);
		}
		if (boss.state == 2) {
			if (boss.hp_max == 0) { printfDx("graph_boss��0����\n"); return; }
			for (int i = 0; i < (FIELD_MAX_X-FIELD_X-20)*0.98*boss.hp / boss.hp_max; i++) {
				if (boss.back_type[boss.type] == 1) {
					DrawGraph(FIELD_X + 40 + i + Effect.GetdnX(), FIELD_Y + 4 + Effect.GetdnY(), hp_bar_image, FALSE);
				}
			}
		}
	}
}


//�e�ۂ̕`��
void Boss_obj::DrawBullet() {
	SetDrawMode(DX_DRAWMODE_BILINEAR);//���`�⊮�`��
	//�{�X
	if (boss_shot.flag > 0) {//�e���f�[�^���I���Ȃ�
		for (int j = 0; j<BOSS_BULLET_MAX; j++) {//���̒e�������e�̍ő吔�����[�v
			if (boss_shot.bullet[j].flag != 0) {//�e�f�[�^���I���Ȃ�
				if (boss_shot.bullet[j].effect == 1)
					SetDrawBlendMode(DX_BLENDMODE_ADD, 255);

				DrawRotaGraphF(
					boss_shot.bullet[j].x + Effect.GetdnX() , boss_shot.bullet[j].y + Effect.GetdnY() ,
					1.0, boss_shot.bullet[j].angle + M_PI / 2,
					bul_image[boss_shot.bullet[j].type][boss_shot.bullet[j].color], TRUE);

				if (boss_shot.bullet[j].effect == 1)
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}
		}
	}
	SetDrawMode(DX_DRAWMODE_NEAREST);//�`��`����߂�
}

void Boss_obj::MinusHp(int atk){
	boss.hp -= atk;
}

//�n���ꂽ�����\���̂ɓ����֐�
void Boss_obj::InputBulletInfo(bullet_info_t *b_info, int size_x, int size_y, int color_num, double range) {
	b_info->size_x = size_x;  b_info->size_y = size_y;
	b_info->col_num = color_num; b_info->range = range;
}

void Boss_obj::MoveBossShot(double setx, double sety, int t, int i) {
	boss_shot.bullet[i].vx = (setx - boss_shot.bullet[i].x) / t;
	boss_shot.bullet[i].vy = (sety - boss_shot.bullet[i].y) / t;
}

int Boss_obj::GetAppearCount() {
	return boss.appear_count;
}

int Boss_obj::GetFlag() {
	return boss.flag;
}

int Boss_obj::GetState() {
	return boss.state;
}

int Boss_obj::GetGraphFlag() {
	return boss.graph_flag;
}

int Boss_obj::GetBulletCount(int i) {
	return boss_shot.bullet[i].counter;
}

int Boss_obj::GetBulletX(int i) {
	return boss_shot.bullet[i].x;
}

int Boss_obj::GetBulletY(int i) {
	return boss_shot.bullet[i].y;
}

int Boss_obj::GetBulletSpeed(int i) {
	return boss_shot.bullet[i].speed;
}

int Boss_obj::GetBulletAngle(int i) {
	return boss_shot.bullet[i].angle;
}

int Boss_obj::GetBulletRange(int i) {
	return bullet_info[i].range;
}

int Boss_obj::GetBulletType(int i) {
	return boss_shot.bullet[i].type;
}

int Boss_obj::GetBulletFlag(int i) {
	return boss_shot.bullet[i].flag;
}

void Boss_obj::SetBulletFlag(int i, int setflag) {
	boss_shot.bullet[i].flag = setflag;
}

int Boss_obj::GetRange(int stage) {
	return boss_range[stage - 1];
}

int Boss_obj::GetX() {
	return boss.x;
}

int Boss_obj::GetY() {
	return boss.y;
}

int Boss_obj::GetShotFlag() {
	return boss_shot.flag;
}

int Boss_obj::GetBossHp() {
	return boss.hp;
}

int Boss_obj::GetBossHpMax() {
	return boss.hp_max;
}

int Boss_obj::GetBossBackType(int i) {
	return boss.back_type[i];
}

int Boss_obj::GetBossType() {
	return boss.type;
}

double Boss_obj::GetBossSpeed() {
	return boss.speed;
}

double Boss_obj::GetBossAngle() {
	return boss.angle;
}

int Boss_obj::GetPlusRange() {
	return boss.plus_range;
}

int Boss_obj::BossShotCounter() {
	return boss_shot.counter;
}
