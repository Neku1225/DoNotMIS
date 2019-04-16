#include "define.h"

void Enemy_obj::EnterShot(int i) {
	int j;
	for (j = 0; j<SHOT_MAX; j++) {//フラグのたって無いenemyを探す
		if (shot[j].flag == 0) {//未使用の弾幕データがあれば
			memset(&shot[j], 0, sizeof(shot_t));//初期化して登録
			shot[j].flag = 1;//フラグをたてる
			shot[j].type = enemy[i].bl_type;//弾の種類
			shot[j].num = i;//num=どの敵から発射されたものか。
			shot[j].counter = 0;
			return;
		}
	}
}
//n番目のショットを登録した敵と自機との角度を返す
double Enemy_obj::Shotatan2(int n) {
	return atan2(Player.GetY() - enemy[shot[n].num].y, Player.GetX() - enemy[shot[n].num].x);
}

//空いている弾を探す
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
	for (i = 0; i<SHOT_MAX; i++) {//弾幕データ計算
								  //フラグが立っていて、設定した種類が間違っていなければ
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
			ShotCalc(i);//i番目の弾幕を計算
			shot[i].counter++;
		}
	}
}

void Enemy_obj::ShotCalc(int n) {
	int i, max = 0;
	if (enemy[shot[n].num].flag != 1)//敵が倒されたら
		shot[n].flag = 2;//それ以上ショットを登録しないフラグに変える
	for (i = 0; i<SHOT_BULLET_MAX; i++) {//n番目の弾幕データの弾を計算
		if (shot[n].bullet[i].flag>0) {//その弾が登録されていたら
			shot[n].bullet[i].x += cos(shot[n].bullet[i].angle)*shot[n].bullet[i].speed;
			shot[n].bullet[i].y += sin(shot[n].bullet[i].angle)*shot[n].bullet[i].speed;
			shot[n].bullet[i].counter++;
			if (shot[n].bullet[i].x<-50 || shot[n].bullet[i].x>FIELD_MAX_X + 50 ||
				shot[n].bullet[i].y<-50 || shot[n].bullet[i].y>FIELD_MAX_Y + 50) {//画面から外れたら
				if (shot[n].bullet[i].till < shot[n].bullet[i].counter) {//最低消えない時間より長ければ
					shot[n].bullet[i].flag = 0;//消す
				}
			}
		}
	}
	//現在表示中の弾が一つでもあるかどうか調べる
	for (i = 0; i < SHOT_BULLET_MAX; i++) {
		if (shot[n].bullet[i].flag > 0) {
			return;
		}
	}
	if (enemy[shot[n].num].flag != 1) {
		shot[n].flag = 0;//終了
		enemy[shot[n].num].flag = 0;
	}
}

void Enemy_obj::DrawBullet() {
	int i, j;
	SetDrawMode(DX_DRAWMODE_BILINEAR);//線形補完描画
	for (i = 0; i<SHOT_MAX; i++) {//敵の弾幕数分ループ
		if (shot[i].flag>0) {//弾幕データがオンなら
			for (j = 0; j<SHOT_BULLET_MAX; j++) {//その弾幕が持つ弾の最大数分ループ
				if (shot[i].bullet[j].flag != 0) {//弾データがオンなら
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
	SetDrawMode(DX_DRAWMODE_NEAREST);//描画形式を戻す
}

//渡された情報を構造体に入れる関数
void Enemy_obj::InputBulletInfo(bullet_info_t *b_info, int size_x, int size_y, int color_num, double range) {
	b_info->size_x = size_x;  b_info->size_y = size_y;
	b_info->col_num = color_num; b_info->range = range;
}

void Enemy_obj::ShotEasy(int n) {
	int k;
	switch (shot[n].type) {
	case 0:
		//1発だけ、自機に向かって直線移動
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
		//100カウント中に10発、自機に向かって直線発射(常に自機狙い)
		if (shot[n].counter >= 0 && shot[n].counter < 100 && shot[n].counter % 20 == 0) {//100カウント中10カウントに1回
			if (shot[n].flag != 2 && (k = ShotSearch(n)) != -1) {//敵がいて、弾が登録可能なら
				shot[n].bullet[k].type = enemy[shot[n].num].bl_type2;//弾登録
				shot[n].bullet[k].angle = Shotatan2(n);//角度
				shot[n].bullet[k].flag = 1;//フラグ
				shot[n].bullet[k].x = enemy[shot[n].num].x;//座標
				shot[n].bullet[k].y = enemy[shot[n].num].y;
				shot[n].bullet[k].color = enemy[shot[n].num].color;//色
				shot[n].bullet[k].counter = 0;//カウンタ
				shot[n].bullet[k].speed = 3;//スピード
				se_flag[0] = 1;
			}
		}
		break;
	case 2:
		//100カウント中に10発、自機に向かって直線発射(角度記憶)
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
		//100カウント中に10発、自機に向かってスピード変化直線発射
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
		//0.5秒に1回ずつ円形発射
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
		//ばらまきショット
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
		//ばらまきショット(減速)
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
		for (int i = 0; i<SHOT_BULLET_MAX; i++) {//全弾分ループ
			if (shot[n].bullet[i].speed>1.5)//速度が1.5より大きいものがあれば
				shot[n].bullet[i].speed -= 0.04;//減速
		}
		break;
	case 7:
		if (shot[n].counter >= 0 && shot[n].counter < 200 && shot[n].counter % 25 == 0) {
			if (shot[n].counter == 0) {
				shot[n].base_angle[0] = M_PI / 2;//真下へ
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
				shot[n].base_angle[0] = M_PI / 2;//真下へ
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
				shot[n].base_angle[0] = M_PI / 4;//右斜め45度
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
				shot[n].base_angle[0] = (M_PI / 4) * 3;//左斜め45度
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
		//ばらまきショット(簡易)
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
		//100カウント中に10発、自機に向かって直線発射(角度記憶) 3way
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
		//100カウント中に10発、自機に向かって直線発射(常に自機狙い) 3way
		for (int i = 0; i < 3; i++) {
			if (shot[n].counter >= 0 && shot[n].counter < 100 && shot[n].counter % 20 == 0) {//100カウント中10カウントに1回
				if (shot[n].flag != 2 && (k = ShotSearch(n)) != -1) {//敵がいて、弾が登録可能なら
					shot[n].bullet[k].type = enemy[shot[n].num].bl_type2;//弾登録
					shot[n].bullet[k].angle = Shotatan2(n) + (i - 1) * 0.25;//角度
					shot[n].bullet[k].flag = 1;//フラグ
					shot[n].bullet[k].x = enemy[shot[n].num].x;//座標
					shot[n].bullet[k].y = enemy[shot[n].num].y;
					shot[n].bullet[k].color = enemy[shot[n].num].color;//色
					shot[n].bullet[k].counter = 0;//カウンタ
					shot[n].bullet[k].speed = 3;//スピード
					se_flag[0] = 1;
				}
			}
		}
		break;
	case 14:
		//十字
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
		//1発だけ、自機に向かって直線移動
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
		//100カウント中に10発、自機に向かって直線発射(常に自機狙い)
		if (shot[n].counter >= 0 && shot[n].counter < 100 && shot[n].counter % 15 == 0) {//100カウント中10カウントに1回
			if (shot[n].flag != 2 && (k = ShotSearch(n)) != -1) {//敵がいて、弾が登録可能なら
				shot[n].bullet[k].type = enemy[shot[n].num].bl_type2;//弾登録
				shot[n].bullet[k].angle = Shotatan2(n);//角度
				shot[n].bullet[k].flag = 1;//フラグ
				shot[n].bullet[k].x = enemy[shot[n].num].x;//座標
				shot[n].bullet[k].y = enemy[shot[n].num].y;
				shot[n].bullet[k].color = enemy[shot[n].num].color;//色
				shot[n].bullet[k].counter = 0;//カウンタ
				shot[n].bullet[k].speed = 3;//スピード
				se_flag[0] = 1;
			}
		}
		break;
	case 2:
		//100カウント中に10発、自機に向かって直線発射(角度記憶)
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
		//100カウント中に10発、自機に向かってスピード変化直線発射
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
		//0.5秒に1回ずつ円形発射
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
		//ばらまきショット
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
		//ばらまきショット(減速)
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
		for (int i = 0; i<SHOT_BULLET_MAX; i++) {//全弾分ループ
			if (shot[n].bullet[i].speed>1.5)//速度が1.5より大きいものがあれば
				shot[n].bullet[i].speed -= 0.04;//減速
		}
		break;
	case 7:
		if (shot[n].counter >= 0 && shot[n].counter < 200 && shot[n].counter % 20 == 0) {
			if (shot[n].counter == 0) {
				shot[n].base_angle[0] = M_PI / 2;//真下へ
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
				shot[n].base_angle[0] = M_PI / 2;//真下へ
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
				shot[n].base_angle[0] = M_PI / 4;//右斜め45度
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
				shot[n].base_angle[0] = (M_PI / 4) * 3;//左斜め45度
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
		//ばらまきショット(簡易)
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
		//100カウント中に10発、自機に向かって直線発射(角度記憶) 3way
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
		//100カウント中に10発、自機に向かって直線発射(常に自機狙い) 3way
		for (int i = 0; i < 3; i++) {
			if (shot[n].counter >= 0 && shot[n].counter < 100 && shot[n].counter % 15 == 0) {//100カウント中10カウントに1回
				if (shot[n].flag != 2 && (k = ShotSearch(n)) != -1) {//敵がいて、弾が登録可能なら
					shot[n].bullet[k].type = enemy[shot[n].num].bl_type2;//弾登録
					shot[n].bullet[k].angle = Shotatan2(n) + (i - 1) * 0.25;//角度
					shot[n].bullet[k].flag = 1;//フラグ
					shot[n].bullet[k].x = enemy[shot[n].num].x;//座標
					shot[n].bullet[k].y = enemy[shot[n].num].y;
					shot[n].bullet[k].color = enemy[shot[n].num].color;//色
					shot[n].bullet[k].counter = 0;//カウンタ
					shot[n].bullet[k].speed = 3;//スピード
					se_flag[0] = 1;
				}
			}
		}
		break;
	case 14:
		//十字
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
		//1発だけ、自機に向かって直線移動
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
		//100カウント中に10発、自機に向かって直線発射(常に自機狙い)
		if (shot[n].counter >= 0 && shot[n].counter < 100 && shot[n].counter % 10 == 0) {//100カウント中10カウントに1回
			if (shot[n].flag != 2 && (k = ShotSearch(n)) != -1) {//敵がいて、弾が登録可能なら
				shot[n].bullet[k].type = enemy[shot[n].num].bl_type2;//弾登録
				shot[n].bullet[k].angle = Shotatan2(n);//角度
				shot[n].bullet[k].flag = 1;//フラグ
				shot[n].bullet[k].x = enemy[shot[n].num].x;//座標
				shot[n].bullet[k].y = enemy[shot[n].num].y;
				shot[n].bullet[k].color = enemy[shot[n].num].color;//色
				shot[n].bullet[k].counter = 0;//カウンタ
				shot[n].bullet[k].speed = 3;//スピード
				se_flag[0] = 1;
			}
		}
		break;
	case 2:
		//100カウント中に10発、自機に向かって直線発射(角度記憶)
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
		//100カウント中に10発、自機に向かってスピード変化直線発射
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
		//0.5秒に1回ずつ円形発射
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
		//ばらまきショット
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
		//ばらまきショット(減速)
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
		for (int i = 0; i<SHOT_BULLET_MAX; i++) {//全弾分ループ
			if (shot[n].bullet[i].speed>1.5)//速度が1.5より大きいものがあれば
				shot[n].bullet[i].speed -= 0.04;//減速
		}
		break;
	case 7:
		if (shot[n].counter >= 0 && shot[n].counter < 200 && shot[n].counter % 15 == 0) {
			if (shot[n].counter == 0) {
				shot[n].base_angle[0] = M_PI / 2;//真下へ
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
				shot[n].base_angle[0] = M_PI / 2;//真下へ
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
				shot[n].base_angle[0] = M_PI / 4;//右斜め45度
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
				shot[n].base_angle[0] = (M_PI / 4) * 3;//左斜め45度
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
		//ばらまきショット(簡易)
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
		//100カウント中に10発、自機に向かって直線発射(角度記憶) 3way
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
		//100カウント中に10発、自機に向かって直線発射(常に自機狙い) 3way
		for (int i = 0; i < 5; i++) {
			if (shot[n].counter >= 0 && shot[n].counter < 100 && shot[n].counter % 10 == 0) {//100カウント中10カウントに1回
				if (shot[n].flag != 2 && (k = ShotSearch(n)) != -1) {//敵がいて、弾が登録可能なら
					shot[n].bullet[k].type = enemy[shot[n].num].bl_type2;//弾登録
					shot[n].bullet[k].angle = Shotatan2(n) + (i - 2) * 0.25;//角度
					shot[n].bullet[k].flag = 1;//フラグ
					shot[n].bullet[k].x = enemy[shot[n].num].x;//座標
					shot[n].bullet[k].y = enemy[shot[n].num].y;
					shot[n].bullet[k].color = enemy[shot[n].num].color;//色
					shot[n].bullet[k].counter = 0;//カウンタ
					shot[n].bullet[k].speed = 3;//スピード
					se_flag[0] = 1;
				}
			}
		}
		break;
	case 14:
		//十字
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
