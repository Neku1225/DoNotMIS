#include "define.h"

void Boss_obj::BossShotMain(int stage) {
	switch (Control.GetLevel()) {
	case 'E':
		BossShotE(stage);
		break;
	case 'N':
		BossShotN(stage);
		break;
	case 'H':
		BossShotH(stage);
		break;
	}
}

void Boss_obj::BossShotE(int stage) {
	int k, t;
	switch (stage) {
	case 1://一面のボスの弾幕
		switch (boss.type) {
		case 0://第1形態
			t = boss_shot.counter % 140;
			double angle;
			if (t < 60 && t % 10 == 0) {
				angle = BossAtan2();
				for (int i = 0; i < 30; i++) {
					if ((k = SerchBossShot()) != -1) {
						boss_shot.bullet[k].color = 0;
						boss_shot.bullet[k].x = boss.x + adj_boss_bul_x[stage - 1];//座標
						boss_shot.bullet[k].y = boss.y + adj_boss_bul_y[stage - 1];
						boss_shot.bullet[k].type = 8;
						boss_shot.bullet[k].angle = angle + M_PI * 2 / 30 * i;
						boss_shot.bullet[k].flag = 1;
						boss_shot.bullet[k].counter = 0;
						boss_shot.bullet[k].speed = 3;
						Enemy.se_flag[0] = 1;
					}
				}
			}
			if (t % 90 == 0) {
				angle = BossAtan2();
				for (int j = 0; j < 30; j++) {
					if ((k = SerchBossShot()) != -1) {
						boss_shot.bullet[k].color = 5;
						boss_shot.bullet[k].x = boss.x + adj_boss_bul_x[stage - 1];//座標
						boss_shot.bullet[k].y = boss.y + adj_boss_bul_y[stage - 1];
						boss_shot.bullet[k].type = 8;
						boss_shot.bullet[k].angle = angle + M_PI * 2 / 30 * j;
						boss_shot.bullet[k].flag = 1;
						boss_shot.bullet[k].counter = 0;
						boss_shot.bullet[k].speed = 3;
						Enemy.se_flag[0] = 1;
					}
				}
			}
			for (int i = 0; i < BOSS_BULLET_MAX; i++) {
				if (boss_shot.bullet[i].flag>0) {

				}
			}
			break;
		case 1://第2形態
			t = boss_shot.counter % 150;
			if (t < 30 && t % 10 == 0) {
				angle = BossAtan2();
				for (int i = 0; i < 30; i++) {
					if ((k = SerchBossShot()) != -1) {
						boss_shot.bullet[k].color = 0;
						boss_shot.bullet[k].x = boss.x + adj_boss_bul_x[stage - 1];//座標
						boss_shot.bullet[k].y = boss.y + adj_boss_bul_y[stage - 1];
						boss_shot.bullet[k].type = 6;
						boss_shot.bullet[k].angle = angle + M_PI * 2 / 21 * i;
						boss_shot.bullet[k].flag = 1;
						boss_shot.bullet[k].counter = 0;
						boss_shot.bullet[k].speed = 3;
						Enemy.se_flag[0] = 1;
					}
				}
			}
			if (30 <= t && t < 60 && t % 10 == 0) {
				angle = BossAtan2();
				for (int i = 0; i < 30; i++) {
					if ((k = SerchBossShot()) != -1) {
						boss_shot.bullet[k].color = 1;
						boss_shot.bullet[k].x = boss.x + adj_boss_bul_x[stage - 1];//座標
						boss_shot.bullet[k].y = boss.y + adj_boss_bul_y[stage - 1];
						boss_shot.bullet[k].type = 6;
						boss_shot.bullet[k].angle = angle + M_PI * 2 / 19 * i;
						boss_shot.bullet[k].flag = 1;
						boss_shot.bullet[k].counter = 0;
						boss_shot.bullet[k].speed = 3;
						Enemy.se_flag[0] = 1;
					}
				}
			}
			if (60 <= t && t < 90 && t % 10 == 0) {
				angle = BossAtan2();
				for (int i = 0; i < 30; i++) {
					if ((k = SerchBossShot()) != -1) {
						boss_shot.bullet[k].color = 2;
						boss_shot.bullet[k].x = boss.x + adj_boss_bul_x[stage - 1];//座標
						boss_shot.bullet[k].y = boss.y + adj_boss_bul_y[stage - 1];
						boss_shot.bullet[k].type = 6;
						boss_shot.bullet[k].angle = angle + M_PI * 2 / 17 * i;
						boss_shot.bullet[k].flag = 1;
						boss_shot.bullet[k].counter = 0;
						boss_shot.bullet[k].speed = 3;
						Enemy.se_flag[0] = 1;
					}
				}
			}
			if (90 <= t && t < 120 && t % 10 == 0) {
				angle = BossAtan2();
				for (int i = 0; i < 30; i++) {
					if ((k = SerchBossShot()) != -1) {
						boss_shot.bullet[k].color = t % 3;
						boss_shot.bullet[k].x = boss.x + adj_boss_bul_x[stage - 1];//座標
						boss_shot.bullet[k].y = boss.y + adj_boss_bul_y[stage - 1];
						boss_shot.bullet[k].type = 6;
						boss_shot.bullet[k].angle = angle + M_PI * 2 / 15 * i;
						boss_shot.bullet[k].flag = 1;
						boss_shot.bullet[k].counter = 0;
						boss_shot.bullet[k].speed = 3;
						Enemy.se_flag[0] = 1;
					}
				}
			}
			for (int i = 0; i < BOSS_BULLET_MAX; i++) {
				if (boss_shot.bullet[i].flag>0) {

				}
			}
			break;

		case 2://最終形態
			t = boss_shot.counter % 120;
			if (t < 96 && t % 12 == 0) {
				angle = BossAtan2();
				for (int i = 0; i < 30; i++) {
					if ((k = SerchBossShot()) != -1) {
						boss_shot.bullet[k].color = (t / 5) % 5;
						boss_shot.bullet[k].x = boss.x + adj_boss_bul_x[stage - 1];//座標
						boss_shot.bullet[k].y = boss.y + adj_boss_bul_y[stage - 1];
						boss_shot.bullet[k].type = 1;
						boss_shot.bullet[k].angle = angle + M_PI * 3 / 30 * i;
						boss_shot.bullet[k].flag = 1;
						boss_shot.bullet[k].counter = 0;
						boss_shot.bullet[k].speed = (t / 5) % 3 + 3;
						Enemy.se_flag[0] = 1;
					}
				}
			}
			break;
		case 3:
			Control.SetStage(s2_loading);
			break;
		}
		break;

	case 2://二面のボスの弾幕
		switch (boss.type) {
		case 0:
		{
			t = boss_shot.counter % 1000;
			double	angle = M_PI;
			for (int i = 0; i < 1; i++) {
				if (t % 12 == 0) {
					if ((k = SerchBossShot()) != -1) {
						boss_shot.bullet[k].color = 1;
						boss_shot.bullet[k].x = boss.x + adj_boss_bul_x[stage - 1];//座標
						boss_shot.bullet[k].y = boss.y + adj_boss_bul_y[stage - 1];
						boss_shot.bullet[k].type = 1;
						boss_shot.bullet[k].angle = -(angle + M_PI *(30 * (t % 11 + 1) + Enemy.Rang(18)) / 180);
						boss_shot.bullet[k].flag = 1;
						boss_shot.bullet[k].counter = 0;
						boss_shot.bullet[k].speed = 4 + t % 4;
						Enemy.se_flag[0] = 1;
					}
				}
			}

			for (int i = 0; i < BOSS_BULLET_MAX; i++) {

				if (t % 49 == 0)
					boss_shot.bullet[i].speed = 0;
				if (t % 99 == 0)
					boss_shot.bullet[i].speed = 4 + t % 4;
			}

			int tt = boss_shot.counter % 120;
			if (tt < 20 && tt % 10 == 0) {
				angle = BossAtan2();
				for (int j = 0; j < 30; j++) {
					if ((k = SerchBossShot()) != -1) {
						boss_shot.bullet[k].color = 0;
						boss_shot.bullet[k].x = boss.x + adj_boss_bul_x[stage - 1];//座標
						boss_shot.bullet[k].y = boss.y + adj_boss_bul_y[stage - 1];
						boss_shot.bullet[k].type = 2;
						boss_shot.bullet[k].angle = angle + M_PI * 3 / 30 * j;
						boss_shot.bullet[k].flag = 1;
						boss_shot.bullet[k].counter = 0;
						boss_shot.bullet[k].speed = 5;
						Enemy.se_flag[0] = 1;
					}
				}
			}
			break;
		}
		case 1:
		{
			t = boss_shot.counter % 120;
			double	angle = -M_PI / 4;
			if (t == 0) {
				boss.atk_flag = 1;
			}
			else if (t == 60) {
				boss.atk_flag = 0;
			}
			if (t <= 20 && t % 10 == 0) {
				for (int i = 0; i < 40; i++) {
					if ((k = SerchBossShot()) != -1) {
						boss_shot.bullet[k].color = 0;
						boss_shot.bullet[k].x = boss.x;//座標
						boss_shot.bullet[k].y = boss.y;
						boss_shot.bullet[k].type = 8;
						boss_shot.bullet[k].angle = angle + (t / 5 + 3 * (i + 1)) % 60 * M_PI / 40;
						boss_shot.bullet[k].flag = 1;
						boss_shot.bullet[k].speed = 5;
						boss_shot.bullet[k].counter = 0;
						Enemy.se_flag[0] = 1;
					}
				}
			}
			break;
		}
			
		case 2:
		{
			t = boss_shot.counter % 300;
			double	angle = M_PI;
			for (int i = 0; i < 3; i++) {
				if (t == 30) {
					if ((k = SerchBossShot()) != -1) {
						boss_shot.bullet[k].color = 0;
						boss_shot.bullet[k].x = boss.x + adj_boss_bul_x[stage - 1];//座標
						boss_shot.bullet[k].y = boss.y + adj_boss_bul_y[stage - 1];
						boss_shot.bullet[k].type = 1;
						boss_shot.bullet[k].angle = -(angle + M_PI *(50 + 40 * i) / 180);
						boss_shot.bullet[k].flag = 2;
						boss_shot.bullet[k].counter = 0;
						boss_shot.bullet[k].speed = 4;
						Enemy.se_flag[0] = 1;
					}
				}
			}

			for (int i = 0; i < BOSS_BULLET_MAX; i++) {
				if (boss_shot.bullet[i].flag == 1) {
					if (boss_shot.bullet[i].counter == 10) {
						boss_shot.bullet[i].speed = 0;
					}
					else if (boss_shot.bullet[i].counter == 70) {
						boss_shot.bullet[i].speed = 4;
					}
				}
				if (boss_shot.bullet[i].flag == 2) {
					if (boss_shot.bullet[i].counter == 30) {
						boss_shot.bullet[i].speed = 0;
						boss_shot.bullet[i].flag = 0;

						for (int j = 0; j < 20; j++) {
							if ((k = SerchBossShot()) != -1) {
								boss_shot.bullet[k].color = 0;
								boss_shot.bullet[k].x = boss_shot.bullet[i].x;//座標
								boss_shot.bullet[k].y = boss_shot.bullet[i].y;
								boss_shot.bullet[k].type = 8;
								boss_shot.bullet[k].angle = angle + M_PI * 2 / 20 * j;
								boss_shot.bullet[k].flag = 1;
								boss_shot.bullet[k].counter = 0;
								boss_shot.bullet[k].speed = 3;
								Enemy.se_flag[0] = 1;
							}
						}
					}
				}
			}
			break;
		}

		case 3:
			Control.SetStage(s3_loading);
			break;
		}
		break;

	case 3://三面のボスの弾幕
		switch (boss.type) {
		case 2:
			t = boss_shot.counter % 121;
			double angle;
			if (t == 60) {
				angle = BossAtan2() + t;
				for (int i = 0; i < 1; i++) {
					for (int j = 0; j < 60; j++) {
						if ((k = SerchBossShot()) != -1) {
							boss_shot.bullet[k].color = 0;
							boss_shot.bullet[k].x = boss.x + adj_boss_bul_x[stage - 1];//座標
							boss_shot.bullet[k].y = boss.y + adj_boss_bul_y[stage - 1];
							boss_shot.bullet[k].type = 7;
							boss_shot.bullet[k].angle = boss_shot.counter + M_PI * 2 / 30 * j;
							boss_shot.bullet[k].flag = 1;
							boss_shot.bullet[k].counter = 0;
							boss_shot.bullet[k].speed = 3;
							boss_shot.bullet[k].state = 0;
							Enemy.se_flag[0] = 1;
						}
					}
				}
			}
			if (t == 90) {
				angle = BossAtan2();
				for (int i = 0; i < 1; i++) {
					for (int j = 0; j < 60; j++) {
						if ((k = SerchBossShot()) != -1) {
							boss_shot.bullet[k].color = 4;
							boss_shot.bullet[k].x = boss.x + adj_boss_bul_x[stage - 1];//座標
							boss_shot.bullet[k].y = boss.y + adj_boss_bul_y[stage - 1];
							boss_shot.bullet[k].type = 7;
							boss_shot.bullet[k].angle = angle + boss_shot.counter + M_PI * 2 / 30 * j;
							boss_shot.bullet[k].flag = 2;
							boss_shot.bullet[k].counter = 0;
							boss_shot.bullet[k].speed = 1.5;
							boss_shot.bullet[k].state = 0;
							Enemy.se_flag[0] = 1;
						}
					}
				}
			}
			if (t == 120) {
				angle = BossAtan2();
				for (int i = 0; i < 1; i++) {
					for (int j = 0; j < 60; j++) {
						if ((k = SerchBossShot()) != -1) {
							boss_shot.bullet[k].color = 0;
							boss_shot.bullet[k].x = boss.x + adj_boss_bul_x[stage - 1];//座標
							boss_shot.bullet[k].y = boss.y + adj_boss_bul_y[stage - 1];
							boss_shot.bullet[k].type = 7;
							boss_shot.bullet[k].angle = boss_shot.counter + M_PI * 2 / 30 * j;
							boss_shot.bullet[k].flag = 1;
							boss_shot.bullet[k].counter = 0;
							boss_shot.bullet[k].speed = 3;
							boss_shot.bullet[k].state = 1;
							Enemy.se_flag[0] = 1;
						}
					}
				}
			}
			for (int i = 0; i < BOSS_BULLET_MAX; i++) {
				if (boss_shot.bullet[i].flag == 1) {
					int state = boss_shot.bullet[i].state;
					int cnt = boss_shot.bullet[i].counter;
					if (30 < cnt && cnt < 120) {	//30～120カウントなら
						boss_shot.bullet[i].speed -= 1.2 / 60.0;	//60カウントかけて1.2減らす
						boss_shot.bullet[i].angle += (M_PI / 3) / 90 * (state ? -1 : 1);	//60カウントかけて90°傾ける
					}
				}
			}
			break;
		case 1: {
			t = boss_shot.counter % 481;
			int t2 = boss_shot.counter, cnum;
			double x, y, xlen = FIELD_MAX_X / 8;
			int dnumy = FIELD_MAX_Y / xlen;
			double ylen = FIELD_MAX_Y / dnumy;
			if (t == 60) {
				x = 0, y = 0, angle = 0, cnum = 0;
				for (int i = 0; i < 4; i++) {	//画面左上端から　右→下→左→上　の４方向移動させる
					int to = i % 2 ? dnumy : 8;
					for (int j = 0; j <= to; j++) {
						for (int s = 0; s < 4; s++) {
							if ((k = SerchBossShot()) != -1) {
								boss_shot.bullet[k].x = x;//座標
								boss_shot.bullet[k].y = y;
								boss_shot.bullet[k].type = 1;//弾の種類
								boss_shot.bullet[k].flag = 1;
								boss_shot.bullet[k].counter = 0;
								boss_shot.bullet[k].color = 0;//弾の色
								boss_shot.bullet[k].angle = angle + M_PI / 2;//角度
								boss_shot.bullet[k].speed = 0.8;//スピード
								boss_shot.bullet[k].state = 0;//ステータス
								Enemy.se_flag[0] = 1;
								cnum++;
							}
						}
						x += cos(angle) * xlen;
						y += sin(angle) * ylen;
					}
					angle += M_PI / 2;
				}
			}
			if (t == 300) {
				x = 0, y = 0, angle = 0, cnum = 0;
				for (int i = 0; i < 4; i++) {	//画面左上端から　右→下→左→上　の４方向移動させる
					int to = i % 2 ? dnumy : 8;
					for (int j = 0; j <= to; j++) {
						for (int s = 0; s < 4; s++) {
							if ((k = SerchBossShot()) != -1) {
								boss_shot.bullet[k].x = x + 25;//座標
								boss_shot.bullet[k].y = y - 25;
								boss_shot.bullet[k].type = 1;//弾の種類
								boss_shot.bullet[k].flag = 1;
								boss_shot.bullet[k].counter = 0;
								boss_shot.bullet[k].color = 1;//弾の色
								boss_shot.bullet[k].angle = angle + M_PI / 2;//角度
								boss_shot.bullet[k].speed = 0.8;//スピード
								boss_shot.bullet[k].state = 0;//ステータス
								Enemy.se_flag[0] = 1;
								cnum++;
							}
						}
						x += cos(angle) * xlen;
						y += sin(angle) * ylen;
					}
					angle += M_PI / 2;
				}
			}
			for (int i = 0; i < BOSS_BULLET_MAX; i++) {

			}
			break;
		}
		case 0: {
			t = boss_shot.counter % 311;
			int num, t2 = boss_shot.counter;
			if (t2 == 0) num = 0;
			if (t == 60) {
				angle = BossAtan2();
				for (int i = 0; i < 2; i++) {
					for (t = 0; t < 3; t++) {
						for (int j = 0; j < 3; j++) {
							for (int s = 0; s < 30; s++) {
								if ((k = SerchBossShot()) != -1) {
									boss_shot.bullet[k].color = i;//弾の色
									boss_shot.bullet[k].x = boss.x + adj_boss_bul_x[stage - 1];//座標
									boss_shot.bullet[k].y = boss.y + adj_boss_bul_y[stage - 1];
									boss_shot.bullet[k].type = 2;//弾の種類
									boss_shot.bullet[k].angle = angle + M_PI * 2 / 30 * s + M_PI * 2 / 30 * i;//角度
									boss_shot.bullet[k].flag = 1;
									boss_shot.bullet[k].counter = 0;
									boss_shot.bullet[k].speed = 1.8 - 0.2 * j + 0.1 * i;//スピード
									boss_shot.bullet[k].effect = 0;
									boss_shot.bullet[k].state = t;
								}
								Enemy.se_flag[0] = 1;
							}
						}
					}
				}
			}
			if (t == 210) {
				angle = BossAtan2();
				for (int i = 0; i < 2; i++) {
					for (t = 0; t < 3; t++) {
						for (int j = 0; j < 3; j++) {
							for (int s = 0; s < 30; s++) {
								if ((k = SerchBossShot()) != -1) {
									boss_shot.bullet[k].color = i + 1;//弾の色
									boss_shot.bullet[k].x = boss.x + adj_boss_bul_x[stage - 1];//座標
									boss_shot.bullet[k].y = boss.y + adj_boss_bul_y[stage - 1];
									boss_shot.bullet[k].type = 2;//弾の種類
									boss_shot.bullet[k].angle = angle + M_PI * 2 / 30 * s + M_PI * 2 / 30 * i;//角度
									boss_shot.bullet[k].flag = 1;
									boss_shot.bullet[k].counter = 0;
									boss_shot.bullet[k].speed = 1.8 - 0.2 * j + 0.1 * i;//スピード
									boss_shot.bullet[k].effect = 0;
									boss_shot.bullet[k].state = t;
								}
								Enemy.se_flag[0] = 1;
							}
						}
					}
				}
			}
			for (int i = 0; i < BOSS_BULLET_MAX; i++) {
				if (boss_shot.bullet[i].flag > 0) {
					int cnt = boss_shot.bullet[i].counter;
					int state = boss_shot.bullet[i].state;
					if (state % 10 == 0) {
						if (cnt > 90 && cnt <= 100)
							boss_shot.bullet[i].speed -= boss_shot.bullet[i].speed / 220;
					}
					if (state % 10 == 1) {
						if (cnt > 50)
							boss_shot.bullet[i].speed += boss_shot.bullet[i].speed / 45;
					}
					if (state % 10 == 2) {
						if (cnt > 65)
							boss_shot.bullet[i].speed += boss_shot.bullet[i].speed / 90;
					}
					if (10 <= state && state <= 12) {
						if (cnt > 15 && cnt <= 80)
							boss_shot.bullet[i].angle += boss_shot.bullet[i].base_angle[0];
					}
				}
			}
			break;
		}
		case 3:
			Control.SetStage(s4_loading);
			break;
		}
		break;

	case 4://四面のボスの弾幕
		switch (boss.type) {
		case 2: {
			int i, j, k, n, t = boss_shot.counter % 200,
				t2 = boss_shot.counter;
			static int tm;
			double angle;
			//周期の最初にtmをセット
			if (t == 0)
				tm = 190 + Enemy.Rang(30);
			angle = M_PI * 1.5 + M_PI / 5 * sin(M_PI * 2 / tm * t2);
			//4カウントに1回上に8way弾を撃つ
			if (t2 % 20 == 0) {
				for (n = 0; n<8; n++) {
					if ((k = SerchBossShot()) != -1) {
						boss_shot.bullet[k].flag = 1;
						boss_shot.bullet[k].state = 0;
						boss_shot.bullet[k].counter = 0;
						boss_shot.bullet[k].type = 7;
						boss_shot.bullet[k].color = 7;
						boss_shot.bullet[k].angle = 0;
						boss_shot.bullet[k].effect = 0;
						boss_shot.bullet[k].x = boss.x;
						boss_shot.bullet[k].y = boss.y;
						boss_shot.bullet[k].vx = cos(angle - M_PI / 8 * 4 + M_PI / 8 * n + M_PI / 16) * 3;
						boss_shot.bullet[k].vy = sin(angle - M_PI / 8 * 4 + M_PI / 8 * n + M_PI / 16) * 3;
						boss_shot.bullet[k].till = 300;
					}
				}
				Enemy.se_flag[0] = 1;
			}
			if (t2 % 3 == 0) {
				angle = -M_PI * 1.5 + M_PI / 5 * sin(M_PI * 2 / tm);
				for (n = 0; n < 8; n++) {
					if ((k = SerchBossShot()) != -1) {
						boss_shot.bullet[k].flag = 1;
						boss_shot.bullet[k].state = 1;
						boss_shot.bullet[k].counter = 0;
						boss_shot.bullet[k].type = 1;
						boss_shot.bullet[k].color = 1;
						boss_shot.bullet[k].angle = 0;
						boss_shot.bullet[k].effect = 0;
						boss_shot.bullet[k].x = boss.x;
						boss_shot.bullet[k].y = boss.y;
						boss_shot.bullet[k].vx = cos(angle - M_PI / 8 * 4 + M_PI / 8 * n + M_PI / 16) * 3;
						boss_shot.bullet[k].vy = sin(angle - M_PI / 8 * 4 + M_PI / 8 * n + M_PI / 16) * 3;
						boss_shot.bullet[k].till = 300;
					}
				}
				Enemy.se_flag[0] = 1;
			}
			for (i = 0; i<BOSS_BULLET_MAX; i++) {
				if (boss_shot.bullet[i].flag>0) {
					if (boss_shot.bullet[i].state == 0) {
						if (boss_shot.bullet[i].counter<150)
							boss_shot.bullet[i].vy += 0.03;
						boss_shot.bullet[i].x += boss_shot.bullet[i].vx;
						boss_shot.bullet[i].y += boss_shot.bullet[i].vy;
					}
					if (boss_shot.bullet[i].state == 1) {
						if (boss_shot.bullet[i].counter<160)
							boss_shot.bullet[i].vy += 0.03;
						boss_shot.bullet[i].x += boss_shot.bullet[i].vx;
						boss_shot.bullet[i].y += boss_shot.bullet[i].vy;
						boss_shot.bullet[i].angle = atan2(boss_shot.bullet[i].vy, boss_shot.bullet[i].vx);
					}
				}
			}
		}
			break;
		case 0: {
			int i, j, k, n, num, t2 = boss_shot.counter % 540;
			double angle;
			//周期の最初にtmをセット
			if (t2 == 0) num = 0;
			angle = -M_PI / sin(M_PI / t2);
			if (0 < t2 && t2 < 180 && t2 % 2 == 0) {
				for (n = 0; n < 1; n++) {
					if ((k = SerchBossShot()) != -1) {
						boss_shot.bullet[k].flag = 1;
						boss_shot.bullet[k].state = 0;
						boss_shot.bullet[k].counter = 0;
						boss_shot.bullet[k].type = 7;
						boss_shot.bullet[k].color = 8;
						boss_shot.bullet[k].angle = 0;
						boss_shot.bullet[k].effect = 0;
						boss_shot.bullet[k].x = boss.x;
						boss_shot.bullet[k].y = boss.y;
						boss_shot.bullet[k].vx = cos(-angle - M_PI / 8 * 4 + M_PI / 8 * n + M_PI / 16) * 3 / 2;
						boss_shot.bullet[k].vy = sin(-angle - M_PI / 8 * 4 + M_PI / 8 * n + M_PI / 16) * 3 / 2;
					}
				}
				Enemy.se_flag[0] = 1;
			}
			if (180 < t2 && t2 < 450 && t2 % 2 == 0) {
				for (n = 0; n < 1; n++) {
					if ((k = SerchBossShot()) != -1) {
						boss_shot.bullet[k].flag = 1;
						boss_shot.bullet[k].state = 0;
						boss_shot.bullet[k].counter = 0;
						boss_shot.bullet[k].type = 1;
						boss_shot.bullet[k].color = 1;
						boss_shot.bullet[k].angle = 0;
						boss_shot.bullet[k].effect = 0;
						boss_shot.bullet[k].x = boss.x;
						boss_shot.bullet[k].y = boss.y;
						boss_shot.bullet[k].vx = cos(angle - M_PI / 8 * 4 + M_PI / 8 * n + M_PI / 16) * 3 / 2;
						boss_shot.bullet[k].vy = sin(angle - M_PI / 8 * 4 + M_PI / 8 * n + M_PI / 16) * 3 / 2;
					}
				}
				Enemy.se_flag[0] = 1;
			}
			if (450 < t2 && t2 < 540 && t2 % 2 == 0) {
				for (n = 0; n < 1; n++) {
					if ((k = SerchBossShot()) != -1) {
						boss_shot.bullet[k].flag = 1;
						boss_shot.bullet[k].state = 0;
						boss_shot.bullet[k].counter = 0;
						boss_shot.bullet[k].type = 7;
						boss_shot.bullet[k].color = 8;
						boss_shot.bullet[k].angle = 0;
						boss_shot.bullet[k].effect = 0;
						boss_shot.bullet[k].x = boss.x;
						boss_shot.bullet[k].y = boss.y;
						boss_shot.bullet[k].vx = cos(-angle - M_PI / 8 * 4 + M_PI / 8 * n + M_PI / 16) * 3 / 2;
						boss_shot.bullet[k].vy = sin(-angle - M_PI / 8 * 4 + M_PI / 8 * n + M_PI / 16) * 3 / 2;
					}
				}
				Enemy.se_flag[0] = 1;
			}
			for (i = 0; i < BOSS_BULLET_MAX; i++) {
				if (boss_shot.bullet[i].flag>0) {
					if (boss_shot.bullet[i].state == 0) {
						if (boss_shot.bullet[i].counter < 150)
							boss_shot.bullet[i].vy += 0.0005;
						boss_shot.bullet[i].x += boss_shot.bullet[i].vx;
						boss_shot.bullet[i].y += boss_shot.bullet[i].vy;
					}
					if (boss_shot.bullet[i].state == 1) {
						if (boss_shot.bullet[i].counter < 160)
							boss_shot.bullet[i].vy += 0.0005;
						boss_shot.bullet[i].x += boss_shot.bullet[i].vx;
						boss_shot.bullet[i].y += boss_shot.bullet[i].vy;
						boss_shot.bullet[i].angle = atan2(boss_shot.bullet[i].vy, boss_shot.bullet[i].vx);
					}
				}
			}
			if (t2 == 540) num = (++num);
			break;
		}
		case 1: {
			t = boss_shot.counter % 600;
			int t2 = boss_shot.counter;
			double angle;
			static int tcnt, cnt, cnum;
			if (t == 0) {
				boss_shot.base_angle[0] = BossAtan2();
				cnt = 0;
				tcnt = 2;
			}
			if (t < 540 && t % 3) {
				angle = BossAtan2();
				if (tcnt - 2 == cnt || tcnt - 1 == cnt) {
					if (tcnt - 1 == cnt) {
						boss_shot.base_angle[1] = boss_shot.base_angle[0] + M_PI * 2 / 20 * cnt * (cnum ? -1 : 1) - M_PI * 2 / 120 * 3;
						tcnt += 18;
					}
				}
				else {
					for (int i = 0; i < 18; i++) {
						if ((k = SerchBossShot()) != -1) {
							boss_shot.bullet[k].color = cnum ? 1 : 5;
							boss_shot.bullet[k].x = boss.x;
							boss_shot.bullet[k].y = boss.y;
							boss_shot.bullet[k].type = 8;
							boss_shot.bullet[k].angle = boss_shot.base_angle[0] + M_PI * 10 / 20 * cnt * (cnum ? -1 : 1) + M_PI * 10 / 60 * i * (cnum ? -1 : 1);
							boss_shot.bullet[k].flag = 1;
							boss_shot.bullet[k].counter = 0;
							boss_shot.bullet[k].speed = 2;
							Enemy.se_flag[0] = 1;
						}
					}
				}
				cnt++;
			}
			if (40 < t && t < 540 && t % 30 == 0) {
				for (int i = 0; i < 2; i++) {
					angle = boss_shot.base_angle[1] - M_PI * 2 / 36 * 4;
					for (int j = 0; j < 5; j++) {
						if ((k = SerchBossShot()) != -1) {
							boss_shot.bullet[k].color = cnum ? 5 : 1;
							boss_shot.bullet[k].x = boss.x;
							boss_shot.bullet[k].y = boss.y;
							boss_shot.bullet[k].type = 7;
							boss_shot.bullet[k].angle = angle;
							boss_shot.bullet[k].flag = 1;
							boss_shot.bullet[k].counter = 0;
							boss_shot.bullet[k].speed = 4 - 1.6 / 3 * i;
							Enemy.se_flag[0] = 1;
						}
						angle -= M_PI * 10 / 36;
					}
				}
			}
			for (int i = 0; i < BOSS_BULLET_MAX; i++) {
				if (boss_shot.bullet[i].flag>0) {

				}
			}
			if (t == 599) cnum = (++cnum) % 2;
			break;
		}
		case 3:
			Control.SetStage(s5_loading);
			break;
		}
		break;

	case 5://最終面のボスの弾幕
		switch (boss.type) {
		case 0: {
			t = (boss_shot.counter - 90) % 250;
			int bul_count = 0;
			//本命(自機を包囲する弾幕)
			if (t == 30) {
				bul_count = 0;
				for (int i = 0; i < 4; i++) {
					if ((k = SerchBossShot()) != -1) {
						boss_shot.bullet[k].color = 1;
						if (i < 2) {
							boss_shot.bullet[k].x = Player.GetX() + 100;//座標
						}
						else {
							boss_shot.bullet[k].x = Player.GetX() - 100;
						}
						if (i % 2 == 0) {
							boss_shot.bullet[k].y = Player.GetY() + 100;//座標
						}
						else {
							boss_shot.bullet[k].y = Player.GetY() - 100;
						}
						boss_shot.bullet[k].vx = 0;
						boss_shot.bullet[k].vy = 0;
						boss_shot.bullet[k].type = 7;
						boss_shot.bullet[k].angle = 0;
						boss_shot.bullet[k].flag = 3;
						boss_shot.bullet[k].counter = 0;
						boss_shot.bullet[k].speed = 0;
						boss_shot.bullet[k].till = 15;
						Enemy.se_flag[0] = 1;
					}
				}
			}
			else if (t == 40) {
				for (int i = 0; i < BOSS_BULLET_MAX; i++) {
					if (boss_shot.bullet[i].flag == 3) {
						boss_shot.bullet[i].flag = 0;
							for (int l = 0; l < 20; l++) {
								if ((k = SerchBossShot()) != -1) {
									boss_shot.bullet[k].vx = 0;
									boss_shot.bullet[k].vy = 0;
									boss_shot.bullet[k].color = 1;
									boss_shot.bullet[k].x = boss_shot.bullet[i].x;//座標
									boss_shot.bullet[k].y = boss_shot.bullet[i].y;
									boss_shot.bullet[k].type = 7;
									boss_shot.bullet[k].angle = M_PI*l / 9;
									boss_shot.bullet[k].flag = 2;
									boss_shot.bullet[k].counter = 0;
									boss_shot.bullet[k].speed = 3 ;
									boss_shot.bullet[k].till = 160;
									Enemy.se_flag[0] = 1;
								}
							}
						}
					}
				}
			else if (t == 60) {
				for (int i = 0; i < BOSS_BULLET_MAX; i++) {
					if (boss_shot.bullet[i].flag == 2) {
						boss_shot.bullet[i].speed = 0;
						boss_shot.bullet[i].angle = 0;
					}
				}
			}
			else if (t == 80) {
				for (int i = 0; i < BOSS_BULLET_MAX; i++) {
					if (boss_shot.bullet[i].flag == 2) {
						bul_count++;
						MoveBossShot(Player.GetX(), Player.GetY(), 120 - 10 * bul_count % 2, i);
					}
				}
				bul_count = 0;
			}
			break;
		}
		case 1: {
			t = boss_shot.counter % 300;
			int t2 = boss_shot.counter, cnum;
			double x, y, xlen = FIELD_MAX_X / 8;
			int dnumy = FIELD_MAX_Y / xlen;
			double ylen = FIELD_MAX_Y / dnumy;
			static int num;
			if (t2 == 0) num = 0;
			double angle;
			if (t == 0) {
				x = 0, y = 0, angle = 0, cnum = 0;
				for (int i = 0; i < 4; i++) {
					int to = i % 2 ? dnumy : 8;
					for (int j = 0; j <= to; j++) {
						for (int s = 0; s < 20; s++) {
							if ((k = SerchBossShot()) != -1) {
								boss_shot.bullet[k].x = x;
								boss_shot.bullet[k].y = y;
								boss_shot.bullet[k].type = 2;
								boss_shot.bullet[k].flag = 1;
								boss_shot.bullet[k].counter = 0;
								boss_shot.bullet[k].color = 0;
								boss_shot.bullet[k].angle = angle + M_PI / 2;
								boss_shot.bullet[k].speed = 1.2 + 0.05 * s;
								boss_shot.bullet[k].state = 0;
								Enemy.se_flag[0] = 1;
								cnum++;
							}
						}
						x += cos(angle) * xlen;
						y += sin(angle) * ylen;
					}
					angle += M_PI / 2;
				}
				for (int i = 0; i < 4; i++) {
					int to = i % 2 ? dnumy : 8;
					for (int j = 0; j <= to; j++) {
						for (int s = 0; s < 0; s++) {
							if ((k = SerchBossShot()) != -1) {
								boss_shot.bullet[k].x = x;
								boss_shot.bullet[k].y = y;
								boss_shot.bullet[k].type = 2;
								boss_shot.bullet[k].flag = 1;
								boss_shot.bullet[k].counter = 0;
								boss_shot.bullet[k].color = 3;
								boss_shot.bullet[k].angle = angle + M_PI / 3;
								boss_shot.bullet[k].speed = 1;
								boss_shot.bullet[k].state = 1;
								Enemy.se_flag[0] = 1;
								cnum++;
							}
						}
						x += cos(angle) * xlen;
						y += sin(angle) * ylen;
					}
					angle += M_PI / 2;
				}
			}
			for (int i = 0; i < BOSS_BULLET_MAX; i++) {
				if (boss_shot.bullet[i].flag>0) {
					int state = boss_shot.bullet[i].state;
					int cnt = boss_shot.bullet[i].counter;
					switch (boss_shot.bullet[i].state) {
					case 2:
						boss_shot.bullet[i].angle += boss_shot.bullet[i].base_angle[0];
						break;
					default:
						break;
					}

				}
			}
			if (t == 400) num = (++num) % 2;


			int tt = boss_shot.counter % 250;
			double angleB;
			if (tt < 30 && tt % 10 == 0) {
				angleB = BossAtan2();
				for (int i = 0; i < 30; i++) {
					if ((k = SerchBossShot()) != -1) {
						boss_shot.bullet[k].color = 2;
						boss_shot.bullet[k].x = boss.x + adj_boss_bul_x[stage - 1];//座標
						boss_shot.bullet[k].y = boss.y + adj_boss_bul_y[stage - 1];
						boss_shot.bullet[k].type = 9;
						boss_shot.bullet[k].angle = angleB + M_PI * 2 / 30 * i;
						boss_shot.bullet[k].flag = 1;
						boss_shot.bullet[k].counter = 0;
						boss_shot.bullet[k].speed = 2;
						Enemy.se_flag[0] = 1;
					}
				}
			}
			break;

		}
			
		case 2: {
			t = boss_shot.counter % 400;
			int x;
			if (t % 6 == 0 || t % 6 == 1 || t % 6 == 2)  x = -1;
			if (t % 6 == 3 || t % 6 == 4 || t % 6 == 5)  x = 1;

			double	angle = M_PI;
			for (int i = 0; i < 1; i++) {
				if (t < 80 && t % 2 == 0) {
					if ((k = SerchBossShotA()) != -1) {
						boss_shot.bullet[k].color = 0;
						boss_shot.bullet[k].x = boss.x + adj_boss_bul_x[stage - 1];//座標
						boss_shot.bullet[k].y = boss.y + adj_boss_bul_y[stage - 1];
						boss_shot.bullet[k].type = 5;
						boss_shot.bullet[k].angle = x*(angle + M_PI *(30 * (t % 4 + 2) + Enemy.Rang(36)) / 180);
						boss_shot.bullet[k].flag = 1;
						boss_shot.bullet[k].counter = 0;
						boss_shot.bullet[k].speed = 2 + t % 4;
						Enemy.se_flag[0] = 1;
					}
				}
			}
			for (int i = 0; i < 1; i++) {
				if (t < 80 && t % 2 == 1) {
					if ((k = SerchBossShotB()) != -1) {
						boss_shot.bullet[k].color = 1;
						boss_shot.bullet[k].x = boss.x + adj_boss_bul_x[stage - 1];//座標
						boss_shot.bullet[k].y = boss.y + adj_boss_bul_y[stage - 1];
						boss_shot.bullet[k].type = 5;
						boss_shot.bullet[k].angle = -x*(angle + M_PI *(30 * (t % 4 + 2) + Enemy.Rang(36)) / 180);
						boss_shot.bullet[k].flag = 1;
						boss_shot.bullet[k].counter = 0;
						boss_shot.bullet[k].speed = 2 + t % 4;
						Enemy.se_flag[0] = 1;
					}
				}
			}
			for (int i = 0; i < 1; i++) {
				if (t < 80 && t % 2 == 0) {
					if ((k = SerchBossShotC()) != -1) {
						boss_shot.bullet[k].color = 2;
						boss_shot.bullet[k].x = boss.x + adj_boss_bul_x[stage - 1];//座標
						boss_shot.bullet[k].y = boss.y + adj_boss_bul_y[stage - 1];
						boss_shot.bullet[k].type = 5;
						boss_shot.bullet[k].angle = x*(angle + M_PI *(30 * (t % 4 + 1) + Enemy.Rang(36)) / 180);
						boss_shot.bullet[k].flag = 1;
						boss_shot.bullet[k].counter = 0;
						boss_shot.bullet[k].speed = 3 + t % 4;
						Enemy.se_flag[0] = 1;
					}
				}
			}
			for (int i = 0; i < 1; i++) {
				if (t < 80 && t % 2 == 1) {
					if ((k = SerchBossShotD()) != -1) {
						boss_shot.bullet[k].color = 3;
						boss_shot.bullet[k].x = boss.x + adj_boss_bul_x[stage - 1];//座標
						boss_shot.bullet[k].y = boss.y + adj_boss_bul_y[stage - 1];
						boss_shot.bullet[k].type = 5;
						boss_shot.bullet[k].angle = -x*(angle + M_PI *(30 * (t % 4 + 1) + Enemy.Rang(36)) / 180);
						boss_shot.bullet[k].flag = 1;
						boss_shot.bullet[k].counter = 0;
						boss_shot.bullet[k].speed = 3 + t % 4;
						Enemy.se_flag[0] = 1;
					}
				}
			}
			for (int i = 0; i < 2400; i++) {

				if (t == 100)
					boss_shot.bullet[i].speed = 0;

			}

			for (int i = 0; i < 600; i++) {

				if (t == 150)
					boss_shot.bullet[i].speed = 6;

			}
			for (int i = 600; i < 1200; i++) {

				if (t == 200)
					boss_shot.bullet[i].speed = 6;

			}
			for (int i = 1200; i < 1800; i++) {

				if (t == 250)
					boss_shot.bullet[i].speed = 6;

			}
			for (int i = 1800; i < 2400; i++) {

				if (t == 300)
					boss_shot.bullet[i].speed = 6;

			}


			/*int num, t2 = boss_shot.counter;
			if (t2 == 0) num = 0;
			if (t % 200 == 0) {
				angle = BossAtan2();
				for (int i = 0; i < 2; i++) {
					for (t = 0; t < 3; t++) {
						for (int j = 0; j < 3; j++) {
							for (int s = 0; s < 1; s++) {
								if ((k = SerchBossShotE()) != -1) {
									boss_shot.bullet[k].color = i;//弾の色
									boss_shot.bullet[k].x = boss.x + adj_boss_bul_x[stage - 1];//座標
									boss_shot.bullet[k].y = boss.y + adj_boss_bul_y[stage - 1];
									boss_shot.bullet[k].type = 2;//弾の種類
									boss_shot.bullet[k].angle = angle + M_PI * 3 / 30 * s + M_PI * 2 / 60 * i;//角度
									boss_shot.bullet[k].flag = 1;
									boss_shot.bullet[k].counter = 0;
									boss_shot.bullet[k].speed = 1.8 - 0.2 * j + 0.1 * i;//スピード
									boss_shot.bullet[k].effect = 0;
									boss_shot.bullet[k].state = t;
								}
								Enemy.se_flag[0] = 1;
							}
						}
					}
				}
			}

			for (int i = 0; i < BOSS_BULLET_MAX; i++) {
				if (boss_shot.bullet[i].flag > 0) {
					int cnt = boss_shot.bullet[i].counter;
					int state = boss_shot.bullet[i].state;
					if (state % 10 == 0) {
						if (cnt > 90 && cnt <= 100)
							boss_shot.bullet[i].speed -= boss_shot.bullet[i].speed / 110;
					}
					if (state % 10 == 1) {
						if (cnt > 50)
							boss_shot.bullet[i].speed += boss_shot.bullet[i].speed / 45;
					}
					if (state % 10 == 2) {
						if (cnt > 65)
							boss_shot.bullet[i].speed += boss_shot.bullet[i].speed / 90;
					}
					if (10 <= state && state <= 12) {
						if (cnt > 15 && cnt <= 80)
							boss_shot.bullet[i].angle += boss_shot.bullet[i].base_angle[0];
					}
				}
			}*/
			break;
		}
		case 3:{
			t = boss_shot.counter % 600;
			int t2 = boss_shot.counter;
			double angle;
			static int tcnt, cnt, cnum;
			if (t == 0) {
				boss_shot.base_angle[0] = BossAtan2();
				cnt = 0;
				tcnt = 2;
			}
			if (0 < t && t < 720 && t % 30) {
				angle = BossAtan2();
				if (tcnt - 2 == cnt || tcnt - 1 == cnt) {
					if (tcnt - 1 == cnt) {
						boss_shot.base_angle[1] = boss_shot.base_angle[0] + M_PI * 2 / 20 * cnt * (cnum ? -1 : 1) - M_PI * 2 / 120 * 3; //レーザーの角度
						tcnt += 18;
					}
				}
				else {
					for (int i = 0; i < 10; i++) {
						if ((k = SerchBossShot()) != -1) {
							boss_shot.bullet[k].color = cnum ? 0 : 2;
							boss_shot.bullet[k].x = boss.dx + adj_boss_bul_x[stage - 1];//座標
							boss_shot.bullet[k].y = boss.dy + adj_boss_bul_y[stage - 1];
							boss_shot.bullet[k].type = 8;
							boss_shot.bullet[k].angle = boss_shot.base_angle[0] + M_PI * 10 / 20 * cnt * (cnum ? -1 : 1) + M_PI * 10 /30 * i * (cnum ? -1 : 1);
							boss_shot.bullet[k].flag = 1;
							boss_shot.bullet[k].counter = 0;
							boss_shot.bullet[k].speed = 2;
							Enemy.se_flag[0] = 1;
						}
					}
				}
				cnt++;
			}
			for (int i = 0; i < BOSS_BULLET_MAX; i++) {
				if (boss_shot.bullet[i].flag>0) {
					int state = boss_shot.bullet[i].state;
					int cnt = boss_shot.bullet[i].counter;
					if (30 < cnt) {	//30～なら
						boss_shot.bullet[i].speed -= 0.5 / 80.0;	//80カウントかけて0.5ずつ減らす
					}
				}
			}
			if (t == 599) cnum = (++cnum) % 2;
			break;
		}
		case 4:{
			int i, j, k, n, t = (boss_shot.counter-120) % 420,
				t2 = boss_shot.counter;
			static int tm;
			double angle;
			//周期の最初にtmをセット
			if (boss_shot.counter == 0) {
				warp_flag = 1;
				boss.wx = BOSS_POS_X + adj_boss_x[stage - 1];//ボスの初期座標
				boss.wy = BOSS_POS_Y + adj_boss_y[stage - 1];//ボスの初期座標
			}else if (boss_shot.counter == 120) {
				boss.atk_flag = 1;
				boss.plus_range = 35;
			}
			if (boss.hp < boss.set_hp[4] * 1 / 3) {
				if (t >= 0 && (t - 170) % 60 == 0) {
					int div = ((t - 170) % 70 == 0) ? -1 : 1;
					angle = BossAtan2();//自機とボスとの成す角
					for (int i = 0; i < 2; i++) {//速度の違う2つの弾がある
						for (t = 0; t < 1; t++) {//1箇所から1つにわかれる
							for (int s = 0; s < 30; s++) {//1周30個
								if ((k = SerchBossShot()) != -1) {
									boss_shot.bullet[k].color = i + 4;//弾の色
									boss_shot.bullet[k].x = boss.x + adj_boss_bul_x[stage - 1];//座標
									boss_shot.bullet[k].y = boss.y + adj_boss_bul_y[stage - 1] + 30;
									boss_shot.bullet[k].type = 4;//弾の種類
									boss_shot.bullet[k].angle = angle + M_PI * 6 / 30 * s;//角度
									boss_shot.bullet[k].flag = 1;
									boss_shot.bullet[k].counter = 0;
									boss_shot.bullet[k].speed = 2 - 0.2 * i;//スピード
									boss_shot.bullet[k].effect = 0;
									boss_shot.bullet[k].state = 0;
									boss_shot.bullet[k].base_angle[0] = M_PI / 300 * div;
								}
							}
						}
						Enemy.se_flag[0] = 1;
					}
				}
				if (t >= 0 && t % 42 == 0) {
					angle = BossAtan2();
					for (int i = 0; i < 2; i++) {
						for (int j = 0; j < 60; j++) {
							if ((k = SerchBossShot()) != -1) {
								boss_shot.bullet[k].color = 0;
								boss_shot.bullet[k].x = boss.x + adj_boss_bul_x[stage - 1];//座標
								boss_shot.bullet[k].y = boss.y + adj_boss_bul_y[stage - 1] + 30;
								boss_shot.bullet[k].type = 7;
								boss_shot.bullet[k].angle = angle + t2 * 5 + M_PI * 2 / 30 * j;
								boss_shot.bullet[k].flag = 1;
								boss_shot.bullet[k].counter = 0;
								boss_shot.bullet[k].speed = 1;
								boss_shot.bullet[k].state = 0;
								Enemy.se_flag[0] = 1;
							}
						}
					}
				}
			}
			if (boss.set_hp[4] * 1 / 3 <= boss.hp && boss.hp < boss.set_hp[4] * 2 / 3) {
				if (t >= 0 && (t - 170) % 60 == 0) {
					int div = ((t - 170) % 70 == 0) ? -1 : 1;
					angle = BossAtan2();//自機とボスとの成す角
					for (int i = 0; i < 1; i++) {//速度の違う2つの弾がある
						for (t = 0; t < 1; t++) {//1箇所から1つにわかれる
							for (int s = 0; s < 30; s++) {//1周30個
								if ((k = SerchBossShot()) != -1) {
									boss_shot.bullet[k].color = i + 4;//弾の色
									boss_shot.bullet[k].x = boss.x + adj_boss_bul_x[stage - 1];//座標
									boss_shot.bullet[k].y = boss.y + adj_boss_bul_y[stage - 1] + 30;
									boss_shot.bullet[k].type = 4;//弾の種類
									boss_shot.bullet[k].angle = angle + M_PI * 6 / 30 * s;//角度
									boss_shot.bullet[k].flag = 1;
									boss_shot.bullet[k].counter = 0;
									boss_shot.bullet[k].speed = 2 - 0.2 * i;//スピード
									boss_shot.bullet[k].effect = 0;
									boss_shot.bullet[k].state = 0;
									boss_shot.bullet[k].base_angle[0] = M_PI / 300 * div;
								}
							}
						}
						Enemy.se_flag[0] = 1;
					}
				}
				if (t >= 0 && t % 42 == 0) {
					angle = BossAtan2();
					for (int i = 0; i < 2; i++) {
						for (int j = 0; j < 60; j++) {
							if ((k = SerchBossShot()) != -1) {
								boss_shot.bullet[k].color = 0;
								boss_shot.bullet[k].x = boss.x + adj_boss_bul_x[stage - 1];//座標
								boss_shot.bullet[k].y = boss.y + adj_boss_bul_y[stage - 1] + 30;
								boss_shot.bullet[k].type = 7;
								boss_shot.bullet[k].angle = angle + t2 * 5 + M_PI * 2 / 30 * j;
								boss_shot.bullet[k].flag = 1;
								boss_shot.bullet[k].counter = 0;
								boss_shot.bullet[k].speed = 1;
								boss_shot.bullet[k].state = 0;
								Enemy.se_flag[0] = 1;
							}
						}
					}
				}
			}
			if (boss.set_hp[4] * 2 / 3 < boss.hp) {
				if (t >= 0 && t % 42 == 0) {
					angle = BossAtan2();
					for (int i = 0; i < 2; i++) {
						for (int j = 0; j < 60; j++) {
							if ((k = SerchBossShot()) != -1) {
								boss_shot.bullet[k].color = 0;
								boss_shot.bullet[k].x = boss.x + adj_boss_bul_x[stage - 1];//座標
								boss_shot.bullet[k].y = boss.y + adj_boss_bul_y[stage - 1] + 30;
								boss_shot.bullet[k].type = 7;
								boss_shot.bullet[k].angle = angle + t2 * 5 + M_PI * 2 / 30 * j;
								boss_shot.bullet[k].flag = 1;
								boss_shot.bullet[k].counter = 0;
								boss_shot.bullet[k].speed = 1;
								boss_shot.bullet[k].state = 0;
								Enemy.se_flag[0] = 1;
							}
						}
					}
				}

			}
			break;
		}
		break;
	}
	}
}


void Boss_obj::BossShotN(int stage) {
	int k, t;
	switch (stage) {
	case 1://一面のボスの弾幕
		switch (boss.type) {
		case 0://第1形態
			t = boss_shot.counter % 120;
			double angle;
			if (t < 60 && t % 10 == 0) {
				angle = BossAtan2();
				for (int i = 0; i < 30; i++) {
					if ((k = SerchBossShot()) != -1) {
						boss_shot.bullet[k].color = 0;
						boss_shot.bullet[k].x = boss.x + adj_boss_bul_x[stage - 1];//座標
						boss_shot.bullet[k].y = boss.y + adj_boss_bul_y[stage - 1];
						boss_shot.bullet[k].type = 8;
						boss_shot.bullet[k].angle = angle + M_PI * 2 / 30 * i;
						boss_shot.bullet[k].flag = 1;
						boss_shot.bullet[k].counter = 0;
						boss_shot.bullet[k].speed = 4;
						Enemy.se_flag[0] = 1;
					}
				}
			}
			if (t % 55 == 0) {
				angle = BossAtan2();
				for (int j = 0; j < 30; j++) {
					if ((k = SerchBossShot()) != -1) {
						boss_shot.bullet[k].color = 5;
						boss_shot.bullet[k].x = boss.x + adj_boss_bul_x[stage - 1];//座標
						boss_shot.bullet[k].y = boss.y + adj_boss_bul_y[stage - 1];
						boss_shot.bullet[k].type = 8;
						boss_shot.bullet[k].angle = angle + M_PI * 2 / 30 * j;
						boss_shot.bullet[k].flag = 1;
						boss_shot.bullet[k].counter = 0;
						boss_shot.bullet[k].speed = 3;
						Enemy.se_flag[0] = 1;
					}
				}
			}
			for (int i = 0; i < BOSS_BULLET_MAX; i++) {
				if (boss_shot.bullet[i].flag>0) {

				}
			}
			break;
		case 1://第2形態
			t = boss_shot.counter % 130;
			if (t < 30 && t % 10 == 0) {
				angle = BossAtan2();
				for (int i = 0; i < 30; i++) {
					if ((k = SerchBossShot()) != -1) {
						boss_shot.bullet[k].color = 0;
						boss_shot.bullet[k].x = boss.x + adj_boss_bul_x[stage - 1];//座標
						boss_shot.bullet[k].y = boss.y + adj_boss_bul_y[stage - 1];
						boss_shot.bullet[k].type = 6;
						boss_shot.bullet[k].angle = angle + M_PI * 2 / 21 * i;
						boss_shot.bullet[k].flag = 1;
						boss_shot.bullet[k].counter = 0;
						boss_shot.bullet[k].speed = 3;
						Enemy.se_flag[0] = 1;
					}
				}
			}
			if (30 <= t && t < 60 && t % 10 == 0) {
				angle = BossAtan2();
				for (int i = 0; i < 30; i++) {
					if ((k = SerchBossShot()) != -1) {
						boss_shot.bullet[k].color = 1;
						boss_shot.bullet[k].x = boss.x + adj_boss_bul_x[stage - 1];//座標
						boss_shot.bullet[k].y = boss.y + adj_boss_bul_y[stage - 1];
						boss_shot.bullet[k].type = 6;
						boss_shot.bullet[k].angle = angle + M_PI * 2 / 19 * i;
						boss_shot.bullet[k].flag = 1;
						boss_shot.bullet[k].counter = 0;
						boss_shot.bullet[k].speed = 3;
						Enemy.se_flag[0] = 1;
					}
				}
			}
			if (60 <= t && t < 90 && t % 10 == 0) {
				angle = BossAtan2();
				for (int i = 0; i < 30; i++) {
					if ((k = SerchBossShot()) != -1) {
						boss_shot.bullet[k].color = 2;
						boss_shot.bullet[k].x = boss.x + adj_boss_bul_x[stage - 1];//座標
						boss_shot.bullet[k].y = boss.y + adj_boss_bul_y[stage - 1];
						boss_shot.bullet[k].type = 6;
						boss_shot.bullet[k].angle = angle + M_PI * 2 / 17 * i;
						boss_shot.bullet[k].flag = 1;
						boss_shot.bullet[k].counter = 0;
						boss_shot.bullet[k].speed = 3;
						Enemy.se_flag[0] = 1;
					}
				}
			}
			if (90 <= t && t < 120 && t % 10 == 0) {
				angle = BossAtan2();
				for (int i = 0; i < 30; i++) {
					if ((k = SerchBossShot()) != -1) {
						boss_shot.bullet[k].color = t % 3;
						boss_shot.bullet[k].x = boss.x + adj_boss_bul_x[stage - 1];//座標
						boss_shot.bullet[k].y = boss.y + adj_boss_bul_y[stage - 1];
						boss_shot.bullet[k].type = 6;
						boss_shot.bullet[k].angle = angle + M_PI * 2 / 15 * i;
						boss_shot.bullet[k].flag = 1;
						boss_shot.bullet[k].counter = 0;
						boss_shot.bullet[k].speed = 3;
						Enemy.se_flag[0] = 1;
					}
				}
			}
			for (int i = 0; i < BOSS_BULLET_MAX; i++) {
				if (boss_shot.bullet[i].flag>0) {

				}
			}
			break;
		case 2://最終形態
			t = boss_shot.counter % 120;
			if (t < 96 && t % 12 == 0) {
				angle = BossAtan2();
				for (int i = 0; i < 30; i++) {
					if ((k = SerchBossShot()) != -1) {
						boss_shot.bullet[k].color = (t / 5) % 5;
						boss_shot.bullet[k].x = boss.x + adj_boss_bul_x[stage - 1];//座標
						boss_shot.bullet[k].y = boss.y + adj_boss_bul_y[stage - 1];
						boss_shot.bullet[k].type = 1;
						boss_shot.bullet[k].angle = angle + M_PI * 2 / 30 * i;
						boss_shot.bullet[k].flag = 1;
						boss_shot.bullet[k].counter = 0;
						boss_shot.bullet[k].speed = (t / 5) % 3 + 3;
						Enemy.se_flag[0] = 1;
					}
				}
			}
			for (int i = 0; i < BOSS_BULLET_MAX; i++) {
				if (boss_shot.bullet[i].flag>0) {

				}
			}
			break;
		case 3:
			Control.SetStage(s2_loading);
			break;
		}
		break;

	case 2://二面のボスの弾幕
		switch (boss.type) {
		case 0:
		{
			t = boss_shot.counter % 1000;
			double	angle = M_PI;
			for (int i = 0; i < 1; i++) {
				if (t % 8 == 0) {
					if ((k = SerchBossShot()) != -1) {
						boss_shot.bullet[k].color = 1;
						boss_shot.bullet[k].x = boss.x + adj_boss_bul_x[stage - 1];//座標
						boss_shot.bullet[k].y = boss.y + adj_boss_bul_y[stage - 1];
						boss_shot.bullet[k].type = 1;
						boss_shot.bullet[k].angle = -(angle + M_PI *(30 * (t % 7 + 1) + Enemy.Rang(18)) / 180);
						boss_shot.bullet[k].flag = 1;
						boss_shot.bullet[k].counter = 0;
						boss_shot.bullet[k].speed = 5 + t % 4;
						Enemy.se_flag[0] = 1;
					}
				}
			}

			for (int i = 0; i < BOSS_BULLET_MAX; i++) {

				if (t % 49 == 0)
					boss_shot.bullet[i].speed = 0;
				if (t % 99 == 0)
					boss_shot.bullet[i].speed = 5 + t % 4;
			}

			int tt = boss_shot.counter % 120;
			if (tt < 40 && tt % 10 == 0) {
				angle = BossAtan2();
				for (int j = 0; j < 30; j++) {
					if ((k = SerchBossShot()) != -1) {
						boss_shot.bullet[k].color = 0;
						boss_shot.bullet[k].x = boss.x + adj_boss_bul_x[stage - 1];//座標
						boss_shot.bullet[k].y = boss.y + adj_boss_bul_y[stage - 1];
						boss_shot.bullet[k].type = 2;
						boss_shot.bullet[k].angle = angle + M_PI * 3 / 30 * j;
						boss_shot.bullet[k].flag = 1;
						boss_shot.bullet[k].counter = 0;
						boss_shot.bullet[k].speed = 5;
						Enemy.se_flag[0] = 1;
					}
				}
			}
			break;
		}
		case 1: {
			t = boss_shot.counter % 90;
			double	angle = -M_PI / 4;
			if (t == 0) {
				boss.atk_flag = 1;
			}
			else if (t == 60) {
				boss.atk_flag = 0;
			}
			if (t < 40 && t % 10 == 0) {
				for (int i = 0; i < 30; i++) {
					if ((k = SerchBossShot()) != -1) {
						boss_shot.bullet[k].color = 0;
						boss_shot.bullet[k].x = boss.x;//座標
						boss_shot.bullet[k].y = boss.y;
						boss_shot.bullet[k].type = 8;
						boss_shot.bullet[k].angle = angle + (t / 5 + 3 * (i + 1)) % 90 * M_PI / 60;
						boss_shot.bullet[k].flag = 1;
						boss_shot.bullet[k].speed = 3;
						boss_shot.bullet[k].counter = 0;
						Enemy.se_flag[0] = 1;
					}
				}
			}
			break;
		}
		case 2:
		{
			t = boss_shot.counter % 300;
			double	angle = M_PI;
			for (int i = 0; i < 5; i++) {
				if (t == 30) {
					if ((k = SerchBossShot()) != -1) {
						boss_shot.bullet[k].color = 0;
						boss_shot.bullet[k].x = boss.x + adj_boss_bul_x[stage - 1];//座標
						boss_shot.bullet[k].y = boss.y + adj_boss_bul_y[stage - 1];
						boss_shot.bullet[k].type = 1;
						boss_shot.bullet[k].angle = -(angle + M_PI *(30 * (i + 1) + Enemy.Rang(15)) / 180);
						boss_shot.bullet[k].flag = 2;
						boss_shot.bullet[k].counter = 0;
						boss_shot.bullet[k].speed = 5;
						Enemy.se_flag[0] = 1;
					}
				}
			}

			for (int i = 0; i < BOSS_BULLET_MAX; i++) {
				if (boss_shot.bullet[i].flag == 1) {
					if (boss_shot.bullet[i].counter == 10) {
						boss_shot.bullet[i].speed = 0;
					}
					else if (boss_shot.bullet[i].counter == 70) {
						boss_shot.bullet[i].speed = 1 + GetRand(3);
					}
				}
				if (boss_shot.bullet[i].flag == 2) {
					if (boss_shot.bullet[i].counter == 30) {
						boss_shot.bullet[i].speed = 0;
						boss_shot.bullet[i].flag = 0;

						for (int j = 0; j < 30; j++) {
							if ((k = SerchBossShot()) != -1) {
								boss_shot.bullet[k].color = 0;
								boss_shot.bullet[k].x = boss_shot.bullet[i].x;//座標
								boss_shot.bullet[k].y = boss_shot.bullet[i].y;
								boss_shot.bullet[k].type = 8;
								boss_shot.bullet[k].angle = angle + M_PI * 2 / 25 * j;
								boss_shot.bullet[k].flag = 1;
								boss_shot.bullet[k].counter = 0;
								boss_shot.bullet[k].speed = 3;
								Enemy.se_flag[0] = 1;
							}
						}
					}
				}
			}
			break;
		}
		case 3:
			Control.SetStage(s3_loading);
			break;
		}
		break;

	case 3://三面のボスの弾幕
		switch (boss.type) {
		case 2:
			t = boss_shot.counter % 121;
			double angle;
			if (t == 60) {
				angle = BossAtan2() + t;
				for (int i = 0; i < 1; i++) {
					for (int j = 0; j < 60; j++) {
						if ((k = SerchBossShot()) != -1) {
							boss_shot.bullet[k].color = 0;
							boss_shot.bullet[k].x = boss.x + adj_boss_bul_x[stage - 1];//座標
							boss_shot.bullet[k].y = boss.y + adj_boss_bul_y[stage - 1];
							boss_shot.bullet[k].type = 7;
							boss_shot.bullet[k].angle = boss_shot.counter + M_PI * 2 / 40 * j;
							boss_shot.bullet[k].flag = 1;
							boss_shot.bullet[k].counter = 0;
							boss_shot.bullet[k].speed = 3;
							boss_shot.bullet[k].state = 0;
							Enemy.se_flag[0] = 1;
						}
					}
				}
			}
			if (t == 90) {
				angle = BossAtan2();
				for (int i = 0; i < 1; i++) {
					for (int j = 0; j < 60; j++) {
						if ((k = SerchBossShot()) != -1) {
							boss_shot.bullet[k].color = 4;
							boss_shot.bullet[k].x = boss.x + adj_boss_bul_x[stage - 1];//座標
							boss_shot.bullet[k].y = boss.y + adj_boss_bul_y[stage - 1];
							boss_shot.bullet[k].type = 7;
							boss_shot.bullet[k].angle = angle + boss_shot.counter + M_PI * 2 / 40 * j;
							boss_shot.bullet[k].flag = 2;
							boss_shot.bullet[k].counter = 0;
							boss_shot.bullet[k].speed = 1.5;
							boss_shot.bullet[k].state = 0;
							Enemy.se_flag[0] = 1;
						}
					}
				}
			}
			if (t == 120) {
				angle = BossAtan2();
				for (int i = 0; i < 1; i++) {
					for (int j = 0; j < 60; j++) {
						if ((k = SerchBossShot()) != -1) {
							boss_shot.bullet[k].color = 0;
							boss_shot.bullet[k].x = boss.x + adj_boss_bul_x[stage - 1];//座標
							boss_shot.bullet[k].y = boss.y + adj_boss_bul_y[stage - 1];
							boss_shot.bullet[k].type = 7;
							boss_shot.bullet[k].angle = boss_shot.counter + M_PI * 2 / 40 * j;
							boss_shot.bullet[k].flag = 1;
							boss_shot.bullet[k].counter = 0;
							boss_shot.bullet[k].speed = 3;
							boss_shot.bullet[k].state = 1;
							Enemy.se_flag[0] = 1;
						}
					}
				}
			}
			for (int i = 0; i < BOSS_BULLET_MAX; i++) {
				if (boss_shot.bullet[i].flag == 1) {
					int state = boss_shot.bullet[i].state;
					int cnt = boss_shot.bullet[i].counter;
					if (30 < cnt && cnt < 120) {	//30～120カウントなら
						boss_shot.bullet[i].speed -= 1.2 / 60.0;	//60カウントかけて1.2減らす
						boss_shot.bullet[i].angle += (M_PI / 3) / 90 * (state ? -1 : 1);	//60カウントかけて90°傾ける
					}
				}
			}
			break;
		case 1: {
			t = boss_shot.counter % 241;
			int t2 = boss_shot.counter, cnum;
			double x, y, xlen = FIELD_MAX_X / 8;
			int dnumy = FIELD_MAX_Y / xlen;
			double ylen = FIELD_MAX_Y / dnumy;
			if (t == 60) {
				x = 0, y = 0, angle = 0, cnum = 0;
				for (int i = 0; i < 4; i++) {	//画面左上端から　右→下→左→上　の４方向移動させる
					int to = i % 2 ? dnumy : 8;
					for (int j = 0; j <= to; j++) {
						for (int s = 0; s < 4; s++) {
							if ((k = SerchBossShot()) != -1) {
								boss_shot.bullet[k].x = x;//座標
								boss_shot.bullet[k].y = y;
								boss_shot.bullet[k].type = 1;//弾の種類
								boss_shot.bullet[k].flag = 1;
								boss_shot.bullet[k].counter = 0;
								boss_shot.bullet[k].color = 0;//弾の色
								boss_shot.bullet[k].angle = angle + M_PI / 2;//角度
								boss_shot.bullet[k].speed = 0.8;//スピード
								boss_shot.bullet[k].state = 0;//ステータス
								Enemy.se_flag[0] = 1;
								cnum++;
							}
						}
						x += cos(angle) * xlen;
						y += sin(angle) * ylen;
					}
					angle += M_PI / 2;
				}
			}
			if (t == 180) {
				x = 0, y = 0, angle = 0, cnum = 0;
				for (int i = 0; i < 4; i++) {	//画面左上端から　右→下→左→上　の４方向移動させる
					int to = i % 2 ? dnumy : 8;
					for (int j = 0; j <= to; j++) {
						for (int s = 0; s < 4; s++) {
							if ((k = SerchBossShot()) != -1) {
								boss_shot.bullet[k].x = x + 25;//座標
								boss_shot.bullet[k].y = y - 25;
								boss_shot.bullet[k].type = 1;//弾の種類
								boss_shot.bullet[k].flag = 1;
								boss_shot.bullet[k].counter = 0;
								boss_shot.bullet[k].color = 1;//弾の色
								boss_shot.bullet[k].angle = angle + M_PI / 2;//角度
								boss_shot.bullet[k].speed = 0.8;//スピード
								boss_shot.bullet[k].state = 0;//ステータス
								Enemy.se_flag[0] = 1;
								cnum++;
							}
						}
						x += cos(angle) * xlen;
						y += sin(angle) * ylen;
					}
					angle += M_PI / 2;
				}
			}
			for (int i = 0; i < BOSS_BULLET_MAX; i++) {

			}
			break;
		}
		case 0: {
			t = boss_shot.counter % 311;
			int num, t2 = boss_shot.counter;
			if (t2 == 0) num = 0;
			if (t == 60) {
				angle = BossAtan2();
				for (int i = 0; i < 2; i++) {
					for (t = 0; t < 3; t++) {
						for (int j = 0; j < 3; j++) {
							for (int s = 0; s < 30; s++) {
								if ((k = SerchBossShot()) != -1) {
									boss_shot.bullet[k].color = i;//弾の色
									boss_shot.bullet[k].x = boss.x + adj_boss_bul_x[stage - 1];//座標
									boss_shot.bullet[k].y = boss.y + adj_boss_bul_y[stage - 1];
									boss_shot.bullet[k].type = 2;//弾の種類
									boss_shot.bullet[k].angle = angle + M_PI * 2 / 30 * s + M_PI * 2 / 45 * i;//角度
									boss_shot.bullet[k].flag = 1;
									boss_shot.bullet[k].counter = 0;
									boss_shot.bullet[k].speed = 1.8 - 0.2 * j + 0.1 * i;//スピード
									boss_shot.bullet[k].effect = 0;
									boss_shot.bullet[k].state = t;
								}
								Enemy.se_flag[0] = 1;
							}
						}
					}
				}
			}
			if (t == 210) {
				angle = BossAtan2();
				for (int i = 0; i < 2; i++) {
					for (t = 0; t < 3; t++) {
						for (int j = 0; j < 3; j++) {
							for (int s = 0; s < 30; s++) {
								if ((k = SerchBossShot()) != -1) {
									boss_shot.bullet[k].color = i + 1;//弾の色
									boss_shot.bullet[k].x = boss.x + adj_boss_bul_x[stage - 1];//座標
									boss_shot.bullet[k].y = boss.y + adj_boss_bul_y[stage - 1];
									boss_shot.bullet[k].type = 2;//弾の種類
									boss_shot.bullet[k].angle = angle + M_PI * 2 / 30 * s + M_PI * 2 / 30 * i;//角度
									boss_shot.bullet[k].flag = 1;
									boss_shot.bullet[k].counter = 0;
									boss_shot.bullet[k].speed = 1.8 - 0.2 * j + 0.1 * i;//スピード
									boss_shot.bullet[k].effect = 0;
									boss_shot.bullet[k].state = t;
								}
								Enemy.se_flag[0] = 1;
							}
						}
					}
				}
			}
			for (int i = 0; i < BOSS_BULLET_MAX; i++) {
				if (boss_shot.bullet[i].flag > 0) {
					int cnt = boss_shot.bullet[i].counter;
					int state = boss_shot.bullet[i].state;
					if (state % 10 == 0) {
						if (cnt > 90 && cnt <= 100)
							boss_shot.bullet[i].speed -= boss_shot.bullet[i].speed / 220;
					}
					if (state % 10 == 1) {
						if (cnt > 50)
							boss_shot.bullet[i].speed += boss_shot.bullet[i].speed / 45;
					}
					if (state % 10 == 2) {
						if (cnt > 65)
							boss_shot.bullet[i].speed += boss_shot.bullet[i].speed / 90;
					}
					if (10 <= state && state <= 12) {
						if (cnt > 15 && cnt <= 80)
							boss_shot.bullet[i].angle += boss_shot.bullet[i].base_angle[0];
					}
				}
			}
			break;
		}
		case 3:
			Control.SetStage(s4_loading);
			break;
		}
		break;

	case 4://四面のボスの弾幕
		switch (boss.type) {
		case 2: {
			int i, j, k, n, t = boss_shot.counter % 200,
				t2 = boss_shot.counter;
			static int tm;
			double angle;
			//周期の最初にtmをセット
			if (t == 0)
				tm = 190 + Enemy.Rang(30);
			angle = M_PI * 1.5 + M_PI / 5 * sin(M_PI * 2 / tm * t2);
			//4カウントに1回上に8way弾を撃つ
			if (t2 % 12 == 0) {
				for (n = 0; n<8; n++) {
					if ((k = SerchBossShot()) != -1) {
						boss_shot.bullet[k].flag = 1;
						boss_shot.bullet[k].state = 0;
						boss_shot.bullet[k].counter = 0;
						boss_shot.bullet[k].type = 7;
						boss_shot.bullet[k].color = 7;
						boss_shot.bullet[k].angle = 0;
						boss_shot.bullet[k].effect = 0;
						boss_shot.bullet[k].x = boss.x;
						boss_shot.bullet[k].y = boss.y;
						boss_shot.bullet[k].vx = cos(angle - M_PI / 8 * 4 + M_PI / 8 * n + M_PI / 16) * 3;
						boss_shot.bullet[k].vy = sin(angle - M_PI / 8 * 4 + M_PI / 8 * n + M_PI / 16) * 3;
						boss_shot.bullet[k].till = 300;
					}
				}
				Enemy.se_flag[0] = 1;
			}
			if (t2 % 3 == 0) {
				angle = -M_PI * 1.5 + M_PI / 5 * sin(M_PI * 2 / tm);
				for (n = 0; n < 8; n++) {
					if ((k = SerchBossShot()) != -1) {
						boss_shot.bullet[k].flag = 1;
						boss_shot.bullet[k].state = 1;
						boss_shot.bullet[k].counter = 0;
						boss_shot.bullet[k].type = 1;
						boss_shot.bullet[k].color = 1;
						boss_shot.bullet[k].angle = 0;
						boss_shot.bullet[k].effect = 0;
						boss_shot.bullet[k].x = boss.x;
						boss_shot.bullet[k].y = boss.y;
						boss_shot.bullet[k].vx = cos(angle - M_PI / 8 * 4 + M_PI / 8 * n + M_PI / 16) * 3;
						boss_shot.bullet[k].vy = sin(angle - M_PI / 8 * 4 + M_PI / 8 * n + M_PI / 16) * 3;
						boss_shot.bullet[k].till = 300;
					}
				}
				Enemy.se_flag[0] = 1;
			}
			for (i = 0; i<BOSS_BULLET_MAX; i++) {
				if (boss_shot.bullet[i].flag>0) {
					if (boss_shot.bullet[i].state == 0) {
						if (boss_shot.bullet[i].counter<150)
							boss_shot.bullet[i].vy += 0.03;
						boss_shot.bullet[i].x += boss_shot.bullet[i].vx;
						boss_shot.bullet[i].y += boss_shot.bullet[i].vy;
					}
					if (boss_shot.bullet[i].state == 1) {
						if (boss_shot.bullet[i].counter<160)
							boss_shot.bullet[i].vy += 0.03;
						boss_shot.bullet[i].x += boss_shot.bullet[i].vx;
						boss_shot.bullet[i].y += boss_shot.bullet[i].vy;
						boss_shot.bullet[i].angle = atan2(boss_shot.bullet[i].vy, boss_shot.bullet[i].vx);
					}
				}
			}
		}
			break;
		case 0: {
			int i, j, k, n, num, t2 = boss_shot.counter % 540;
			double angle;
			//周期の最初にtmをセット
			if (t2 == 0) num = 0;
			angle = -M_PI / sin(M_PI / t2);
			if (0 < t2 && t2 < 180 && t2 % 2 == 0) {
				for (n = 0; n<2; n++) {
					if ((k = SerchBossShot()) != -1) {
						boss_shot.bullet[k].flag = 1;
						boss_shot.bullet[k].state = 0;
						boss_shot.bullet[k].counter = 0;
						boss_shot.bullet[k].type = 7;
						boss_shot.bullet[k].color = 8;
						boss_shot.bullet[k].angle = 0;
						boss_shot.bullet[k].effect = 0;
						boss_shot.bullet[k].x = boss.x;
						boss_shot.bullet[k].y = boss.y;
						boss_shot.bullet[k].vx = cos(-angle - M_PI / 8 * 4 + M_PI / 8 * n + M_PI / 16) * 3 / 2;
						boss_shot.bullet[k].vy = sin(-angle - M_PI / 8 * 4 + M_PI / 8 * n + M_PI / 16) * 3 / 2;
					}
				}
				Enemy.se_flag[0] = 1;
			}
			if (180 < t2 && t2 < 450 && t2 % 2 == 0) {
				for (n = 0; n<2; n++) {
					if ((k = SerchBossShot()) != -1) {
						boss_shot.bullet[k].flag = 1;
						boss_shot.bullet[k].state = 0;
						boss_shot.bullet[k].counter = 0;
						boss_shot.bullet[k].type = 1;
						boss_shot.bullet[k].color = 1;
						boss_shot.bullet[k].angle = 0;
						boss_shot.bullet[k].effect = 0;
						boss_shot.bullet[k].x = boss.x;
						boss_shot.bullet[k].y = boss.y;
						boss_shot.bullet[k].vx = cos(angle - M_PI / 8 * 4 + M_PI / 8 * n + M_PI / 16) * 3 / 2;
						boss_shot.bullet[k].vy = sin(angle - M_PI / 8 * 4 + M_PI / 8 * n + M_PI / 16) * 3 / 2;
					}
				}
				Enemy.se_flag[0] = 1;
			}
			if (450 < t2 && t2 < 540 && t2 % 2 == 0) {
				for (n = 0; n<2; n++) {
					if ((k = SerchBossShot()) != -1) {
						boss_shot.bullet[k].flag = 1;
						boss_shot.bullet[k].state = 0;
						boss_shot.bullet[k].counter = 0;
						boss_shot.bullet[k].type = 7;
						boss_shot.bullet[k].color = 8;
						boss_shot.bullet[k].angle = 0;
						boss_shot.bullet[k].effect = 0;
						boss_shot.bullet[k].x = boss.x;
						boss_shot.bullet[k].y = boss.y;
						boss_shot.bullet[k].vx = cos(-angle - M_PI / 8 * 4 + M_PI / 8 * n + M_PI / 16) * 3 / 2;
						boss_shot.bullet[k].vy = sin(-angle - M_PI / 8 * 4 + M_PI / 8 * n + M_PI / 16) * 3 / 2;
					}
				}
				Enemy.se_flag[0] = 1;
			}
			for (i = 0; i<BOSS_BULLET_MAX; i++) {
				if (boss_shot.bullet[i].flag>0) {
					if (boss_shot.bullet[i].state == 0) {
						if (boss_shot.bullet[i].counter<150)
							boss_shot.bullet[i].vy += 0.0005;
						boss_shot.bullet[i].x += boss_shot.bullet[i].vx;
						boss_shot.bullet[i].y += boss_shot.bullet[i].vy;
					}
					if (boss_shot.bullet[i].state == 1) {
						if (boss_shot.bullet[i].counter<160)
							boss_shot.bullet[i].vy += 0.0005;
						boss_shot.bullet[i].x += boss_shot.bullet[i].vx;
						boss_shot.bullet[i].y += boss_shot.bullet[i].vy;
						boss_shot.bullet[i].angle = atan2(boss_shot.bullet[i].vy, boss_shot.bullet[i].vx);
					}
				}
			}
			if (t2 == 540) num = (++num);
		}
			break;
		case 1: {
			t = boss_shot.counter % 600;
			int t2 = boss_shot.counter;
			double angle;
			static int tcnt, cnt, cnum;
			if (t == 0) {
				boss_shot.base_angle[0] = BossAtan2();
				cnt = 0;
				tcnt = 2;
			}
			if (t < 540 && t % 3) {
				angle = BossAtan2();
				if (tcnt - 2 == cnt || tcnt - 1 == cnt) {
					if (tcnt - 1 == cnt) {
						boss_shot.base_angle[1] = boss_shot.base_angle[0] + M_PI * 2 / 20 * cnt * (cnum ? -1 : 1) - M_PI * 2 / 120 * 3;
						tcnt += 18;
					}
				}
				else {
					for (int i = 0; i < 18; i++) {
						if ((k = SerchBossShot()) != -1) {
							boss_shot.bullet[k].color = cnum ? 1 : 5;
							boss_shot.bullet[k].x = boss.x;
							boss_shot.bullet[k].y = boss.y;
							boss_shot.bullet[k].type = 8;
							boss_shot.bullet[k].angle = boss_shot.base_angle[0] + M_PI * 10 / 20 * cnt * (cnum ? -1 : 1) + M_PI * 10 / 80 * i * (cnum ? -1 : 1);
							boss_shot.bullet[k].flag = 1;
							boss_shot.bullet[k].counter = 0;
							boss_shot.bullet[k].speed = 2;
							Enemy.se_flag[0] = 1;
						}
					}
				}
				cnt++;
			}
			if (40 < t && t < 540 && t % 30 == 0) {
				for (int i = 0; i < 2; i++) {
					angle = boss_shot.base_angle[1] - M_PI * 2 / 36 * 4;
					for (int j = 0; j < 10; j++) {
						if ((k = SerchBossShot()) != -1) {
							boss_shot.bullet[k].color = cnum ? 5 : 1;
							boss_shot.bullet[k].x = boss.x;
							boss_shot.bullet[k].y = boss.y;
							boss_shot.bullet[k].type = 7;
							boss_shot.bullet[k].angle = angle;
							boss_shot.bullet[k].flag = 1;
							boss_shot.bullet[k].counter = 0;
							boss_shot.bullet[k].speed = 4 - 1.6 / 3 * i;
							Enemy.se_flag[0] = 1;
						}
						angle -= M_PI * 10 / 36;
					}
				}
			}
			for (int i = 0; i < BOSS_BULLET_MAX; i++) {
				if (boss_shot.bullet[i].flag>0) {

				}
			}
			if (t == 599) cnum = (++cnum) % 2;
			break;
		}
		case 3:
			Control.SetStage(s5_loading);
			break;
		}
		break;

	case 5://最終面のボスの弾幕
		switch (boss.type) {
		case 0:{
			t = (boss_shot.counter - 90) % 200;
			int bul_count = 0;
			//左右への移動を制限する為の弾幕
			if (boss_shot.counter == 60) {
				for (int i = 0; i < 2; i++) {
					if ((k = SerchBossShot()) != -1) {
						boss_shot.bullet[k].color = 1;
						boss_shot.bullet[k].x = boss.x + adj_boss_bul_x[stage - 1];//座標
						boss_shot.bullet[k].y = boss.y + adj_boss_bul_y[stage - 1];
						boss_shot.bullet[k].type = 1;
						boss_shot.bullet[k].angle = -M_PI*(1 + 5 * i) / 7;
						boss_shot.bullet[k].flag = 10;
						boss_shot.bullet[k].counter = 0;
						boss_shot.bullet[k].speed = 6;
						Enemy.se_flag[0] = 1;
					}
				}
			}
			else if (boss_shot.counter == 90) {
				for (int i = 0; i < BOSS_BULLET_MAX; i++) {
					if (boss_shot.bullet[i].flag == 10) {
						boss_shot.bullet[i].speed = 0;
					}
				}
			}
			else if (boss_shot.counter > 90 && boss_shot.counter % 10 == 0) {
				for (int i = 0; i < BOSS_BULLET_MAX; i++) {
					if (boss_shot.bullet[i].flag == 10) {
						for (int j = 0; j < 5; j++) {
							if ((k = SerchBossShot()) != -1) {
								boss_shot.bullet[k].color = 6;
								if (i == 1) {
									boss_shot.bullet[k].x = FIELD_X + FIELD_MAX_X - 13 * (j + 1);//座標
								}
								else {
									boss_shot.bullet[k].x = FIELD_X + 13 * (j + 1);//座標
								}
								boss_shot.bullet[k].y = boss_shot.bullet[i].y;
								boss_shot.bullet[k].type = 8;
								boss_shot.bullet[k].angle = M_PI / 2;
								boss_shot.bullet[k].flag = 9;
								boss_shot.bullet[k].counter = 0;
								boss_shot.bullet[k].speed = 6;
								Enemy.se_flag[0] = 1;
							}
						}
					}
				}
			}

			//本命(自機を包囲する弾幕)
			if (t == 30) {
				bul_count = 0;
				for (int i = 0; i < 4; i++) {
					if ((k = SerchBossShot()) != -1) {
						boss_shot.bullet[k].color = 1;
						if (i < 2) {
							boss_shot.bullet[k].x = Player.GetX() + 100;//座標
						}
						else {
							boss_shot.bullet[k].x = Player.GetX() - 100;
						}
						if (i % 2 == 0) {
							boss_shot.bullet[k].y = Player.GetY() + 100;//座標
						}
						else {
							boss_shot.bullet[k].y = Player.GetY() - 100;
						}
						boss_shot.bullet[k].vx = 0;
						boss_shot.bullet[k].vy = 0;
						boss_shot.bullet[k].type = 7;
						boss_shot.bullet[k].angle = 0;
						boss_shot.bullet[k].flag = 3;
						boss_shot.bullet[k].counter = 0;
						boss_shot.bullet[k].speed = 0;
						boss_shot.bullet[k].till = 15;
						Enemy.se_flag[0] = 1;
					}
				}
			}
			else if (t == 40) {
				for (int i = 0; i < BOSS_BULLET_MAX; i++) {
					if (boss_shot.bullet[i].flag == 3) {
						boss_shot.bullet[i].flag = 0;
						for (int j = 0; j < 2; j++) {
							for (int l = 0; l < 20; l++) {
								if ((k = SerchBossShot()) != -1) {
									boss_shot.bullet[k].vx = 0;
									boss_shot.bullet[k].vy = 0;
									boss_shot.bullet[k].color = 1;
									boss_shot.bullet[k].x = boss_shot.bullet[i].x;//座標
									boss_shot.bullet[k].y = boss_shot.bullet[i].y;
									boss_shot.bullet[k].type = 7;
									boss_shot.bullet[k].angle = M_PI*l / 9;
									boss_shot.bullet[k].flag = 2;
									boss_shot.bullet[k].counter = 0;
									boss_shot.bullet[k].speed = 3 + j;
									boss_shot.bullet[k].till = 160;
									Enemy.se_flag[0] = 1;
								}
							}
						}
					}
				}
			}
			else if (t == 60) {
				for (int i = 0; i < BOSS_BULLET_MAX; i++) {
					if (boss_shot.bullet[i].flag == 2) {
						boss_shot.bullet[i].speed = 0;
						boss_shot.bullet[i].angle = 0;
					}
				}
			}
			else if (t == 80) {
				for (int i = 0; i < BOSS_BULLET_MAX; i++) {
					if (boss_shot.bullet[i].flag == 2) {
						bul_count++;
						MoveBossShot(Player.GetX(), Player.GetY(), 120 - 10 * bul_count % 4, i);
					}
				}
				bul_count = 0;
			}

			break;
		}
		case 1: {
			t = boss_shot.counter % 300;
			int t2 = boss_shot.counter, cnum;
			double x, y, xlen = FIELD_MAX_X / 8;
			int dnumy = FIELD_MAX_Y / xlen;
			double ylen = FIELD_MAX_Y / dnumy;
			static int num;
			if (t2 == 0) num = 0;
			double angle;
			if (t == 0) {
				x = 0, y = 0, angle = 0, cnum = 0;
				for (int i = 0; i < 4; i++) {
					int to = i % 2 ? dnumy : 8;
					for (int j = 0; j <= to; j++) {
						for (int s = 0; s < 20; s++) {
							if ((k = SerchBossShot()) != -1) {
								boss_shot.bullet[k].x = x;
								boss_shot.bullet[k].y = y;
								boss_shot.bullet[k].type = 2;
								boss_shot.bullet[k].flag = 1;
								boss_shot.bullet[k].counter = 0;
								boss_shot.bullet[k].color = 0;
								boss_shot.bullet[k].angle = angle + M_PI / 2;
								boss_shot.bullet[k].speed = 1.2 + 0.05 * s;
								boss_shot.bullet[k].state = 0;
								Enemy.se_flag[0] = 1;
								cnum++;
							}
						}
						x += cos(angle) * xlen;
						y += sin(angle) * ylen;
					}
					angle += M_PI / 2;
				}
				for (int i = 0; i < 4; i++) {
					int to = i % 2 ? dnumy : 8;
					for (int j = 0; j <= to; j++) {
						for (int s = 0; s < 1; s++) {
							if ((k = SerchBossShot()) != -1) {
								boss_shot.bullet[k].x = x;
								boss_shot.bullet[k].y = y;
								boss_shot.bullet[k].type = 2;
								boss_shot.bullet[k].flag = 1;
								boss_shot.bullet[k].counter = 0;
								boss_shot.bullet[k].color = 3;
								boss_shot.bullet[k].angle = angle + M_PI / 3;
								boss_shot.bullet[k].speed = 1;
								boss_shot.bullet[k].state = 1;
								Enemy.se_flag[0] = 1;
								cnum++;
							}
						}
						x += cos(angle) * xlen;
						y += sin(angle) * ylen;
					}
					angle += M_PI / 2;
				}
			}
			for (int i = 0; i < BOSS_BULLET_MAX; i++) {
				if (boss_shot.bullet[i].flag>0) {
					int state = boss_shot.bullet[i].state;
					int cnt = boss_shot.bullet[i].counter;
					switch (boss_shot.bullet[i].state) {
					case 2:
						boss_shot.bullet[i].angle += boss_shot.bullet[i].base_angle[0];
						break;
					default:
						break;
					}

				}
			}
			if (t == 400) num = (++num) % 2;


			int tt = boss_shot.counter % 250;
			double angleB;
			if (tt < 30 && tt % 10 == 0) {
				angleB = BossAtan2();
				for (int i = 0; i < 30; i++) {
					if ((k = SerchBossShot()) != -1) {
						boss_shot.bullet[k].color = 2;
						boss_shot.bullet[k].x = boss.x + adj_boss_bul_x[stage - 1];//座標
						boss_shot.bullet[k].y = boss.y + adj_boss_bul_y[stage - 1];
						boss_shot.bullet[k].type = 9;
						boss_shot.bullet[k].angle = angleB + M_PI * 2 / 30 * i;
						boss_shot.bullet[k].flag = 1;
						boss_shot.bullet[k].counter = 0;
						boss_shot.bullet[k].speed = 2;
						Enemy.se_flag[0] = 1;
					}
				}
			}
			break;

		}
		case 2: {
			t = boss_shot.counter % 400;
			int x;
			if (t % 6 == 0 || t % 6 == 1 || t % 6 == 2)  x = -1;
			if (t % 6 == 3 || t % 6 == 4 || t % 6 == 5)  x = 1;

			double	angle = M_PI;
			for (int i = 0; i < 1; i++) {
				if (t < 100 && t % 2 == 0) {
					if ((k = SerchBossShotA()) != -1) {
						boss_shot.bullet[k].color = 0;
						boss_shot.bullet[k].x = boss.x + adj_boss_bul_x[stage - 1];//座標
						boss_shot.bullet[k].y = boss.y + adj_boss_bul_y[stage - 1];
						boss_shot.bullet[k].type = 5;
						boss_shot.bullet[k].angle = x*(angle + M_PI *(30 * (t % 4 + 2) + Enemy.Rang(36)) / 180);
						boss_shot.bullet[k].flag = 1;
						boss_shot.bullet[k].counter = 0;
						boss_shot.bullet[k].speed = 3 + t % 4;
						Enemy.se_flag[0] = 1;
					}
				}
			}
			for (int i = 0; i < 1; i++) {
				if (t < 100 && t % 2 == 1) {
					if ((k = SerchBossShotB()) != -1) {
						boss_shot.bullet[k].color = 1;
						boss_shot.bullet[k].x = boss.x + adj_boss_bul_x[stage - 1];//座標
						boss_shot.bullet[k].y = boss.y + adj_boss_bul_y[stage - 1];
						boss_shot.bullet[k].type = 5;
						boss_shot.bullet[k].angle = -x*(angle + M_PI *(30 * (t % 4 + 2) + Enemy.Rang(36)) / 180);
						boss_shot.bullet[k].flag = 1;
						boss_shot.bullet[k].counter = 0;
						boss_shot.bullet[k].speed = 3 + t % 4;
						Enemy.se_flag[0] = 1;
					}
				}
			}
			for (int i = 0; i < 1; i++) {
				if (t < 100 && t % 2 == 0) {
					if ((k = SerchBossShotC()) != -1) {
						boss_shot.bullet[k].color = 2;
						boss_shot.bullet[k].x = boss.x + adj_boss_bul_x[stage - 1];//座標
						boss_shot.bullet[k].y = boss.y + adj_boss_bul_y[stage - 1];
						boss_shot.bullet[k].type = 5;
						boss_shot.bullet[k].angle = x*(angle + M_PI *(30 * (t % 4 + 1) + Enemy.Rang(36)) / 180);
						boss_shot.bullet[k].flag = 1;
						boss_shot.bullet[k].counter = 0;
						boss_shot.bullet[k].speed = 4 + t % 4;
						Enemy.se_flag[0] = 1;
					}
				}
			}
			for (int i = 0; i < 1; i++) {
				if (t < 100 && t % 2 == 1) {
					if ((k = SerchBossShotD()) != -1) {
						boss_shot.bullet[k].color = 3;
						boss_shot.bullet[k].x = boss.x + adj_boss_bul_x[stage - 1];//座標
						boss_shot.bullet[k].y = boss.y + adj_boss_bul_y[stage - 1];
						boss_shot.bullet[k].type = 5;
						boss_shot.bullet[k].angle = -x*(angle + M_PI *(30 * (t % 4 + 1) + Enemy.Rang(36)) / 180);
						boss_shot.bullet[k].flag = 1;
						boss_shot.bullet[k].counter = 0;
						boss_shot.bullet[k].speed = 4 + t % 4;
						Enemy.se_flag[0] = 1;
					}
				}
			}
			for (int i = 0; i < 2400; i++) {

				if (t == 100)
					boss_shot.bullet[i].speed = 0;

			}

			for (int i = 0; i < 600; i++) {

				if (t == 150)
					boss_shot.bullet[i].speed = 6;

			}
			for (int i = 600; i < 1200; i++) {

				if (t == 200)
					boss_shot.bullet[i].speed = 6;

			}
			for (int i = 1200; i < 1800; i++) {

				if (t == 250)
					boss_shot.bullet[i].speed = 6;

			}
			for (int i = 1800; i < 2400; i++) {

				if (t == 300)
					boss_shot.bullet[i].speed = 6;

			}


			/*int num, t2 = boss_shot.counter;
			if (t2 == 0) num = 0;
			if (t % 200 == 0) {
				angle = BossAtan2();
				for (int i = 0; i < 2; i++) {
					for (t = 0; t < 3; t++) {
						for (int j = 0; j < 3; j++) {
							for (int s = 0; s < 10; s++) {
								if ((k = SerchBossShotE()) != -1) {
									boss_shot.bullet[k].color = i;//弾の色
									boss_shot.bullet[k].x = boss.x + adj_boss_bul_x[stage - 1];//座標
									boss_shot.bullet[k].y = boss.y + adj_boss_bul_y[stage - 1];
									boss_shot.bullet[k].type = 2;//弾の種類
									boss_shot.bullet[k].angle = angle + M_PI * 3 / 30 * s + M_PI * 2 / 60 * i;//角度
									boss_shot.bullet[k].flag = 1;
									boss_shot.bullet[k].counter = 0;
									boss_shot.bullet[k].speed = 1.8 - 0.2 * j + 0.1 * i;//スピード
									boss_shot.bullet[k].effect = 0;
									boss_shot.bullet[k].state = t;
								}
								Enemy.se_flag[0] = 1;
							}
						}
					}
				}
			}

			for (int i = 0; i < BOSS_BULLET_MAX; i++) {
				if (boss_shot.bullet[i].flag > 0) {
					int cnt = boss_shot.bullet[i].counter;
					int state = boss_shot.bullet[i].state;
					if (state % 10 == 0) {
						if (cnt > 90 && cnt <= 100)
							boss_shot.bullet[i].speed -= boss_shot.bullet[i].speed / 110;
					}
					if (state % 10 == 1) {
						if (cnt > 50)
							boss_shot.bullet[i].speed += boss_shot.bullet[i].speed / 45;
					}
					if (state % 10 == 2) {
						if (cnt > 65)
							boss_shot.bullet[i].speed += boss_shot.bullet[i].speed / 90;
					}
					if (10 <= state && state <= 12) {
						if (cnt > 15 && cnt <= 80)
							boss_shot.bullet[i].angle += boss_shot.bullet[i].base_angle[0];
					}
				}
			}*/
			break;
		}

		case 3: {
			t = boss_shot.counter % 1080;
			int t2 = boss_shot.counter;
			double angle;
			static int tcnt, cnt, cnum;
			if (t == 0) {
				boss_shot.base_angle[0] = BossAtan2();
				cnt = 0;
				tcnt = 2;
			}
			if (0 < t && t < 1140 && t % 30) {
				angle = BossAtan2();
				if (tcnt - 2 == cnt || tcnt - 1 == cnt) {
					if (tcnt - 1 == cnt) {
						boss_shot.base_angle[1] = boss_shot.base_angle[0] + M_PI * 2 / 20 * cnt * (cnum ? -1 : 1) - M_PI * 2 / 120 * 3; //レーザーの角度
						tcnt += 18;
					}
				}
				else {
					for (int i = 0; i < 10; i++) {
						if ((k = SerchBossShot()) != -1) {
							boss_shot.bullet[k].color = cnum ? 0 : 2;
							boss_shot.bullet[k].x = boss.dx + adj_boss_bul_x[stage - 1];//座標
							boss_shot.bullet[k].y = boss.dy + adj_boss_bul_y[stage - 1];
							boss_shot.bullet[k].type = 8;
							boss_shot.bullet[k].angle = boss_shot.base_angle[0] + M_PI * 10 / 20 * cnt * (cnum ? -1 : 1) + M_PI * 10 / 80 * i * (cnum ? -1 : 1);
							boss_shot.bullet[k].flag = 1;
							boss_shot.bullet[k].counter = 0;
							boss_shot.bullet[k].speed = 2;
							Enemy.se_flag[0] = 1;
						}
					}
				}
				cnt++;
			}
			if (t >= 0 && t % 180 == 0) {
				angle = BossAtan2();
				for (int i = 0; i < 2; i++) {
					for (int j = 0; j < 50; j++) {
						if ((k = SerchBossShot()) != -1) {
							boss_shot.bullet[k].color = 7;
							boss_shot.bullet[k].x = boss.x + adj_boss_bul_x[stage - 1];//座標
							boss_shot.bullet[k].y = boss.y + adj_boss_bul_y[stage - 1];
							boss_shot.bullet[k].type = 7;
							boss_shot.bullet[k].angle = angle + M_PI * 2 / 30 * j;
							boss_shot.bullet[k].flag = 2;
							boss_shot.bullet[k].counter = 0;
							boss_shot.bullet[k].speed = 1;
							boss_shot.bullet[k].state = 0;
							Enemy.se_flag[0] = 1;
						}
					}
				}
			}
			for (int i = 0; i < BOSS_BULLET_MAX; i++) {
				if (boss_shot.bullet[i].flag == 1) {
					int state = boss_shot.bullet[i].state;
					int cnt = boss_shot.bullet[i].counter;
					if (30 < cnt) {	//30～なら
						boss_shot.bullet[i].speed -= 0.5 / 80.0;	//80カウントかけて0.5ずつ減らす
					}
				}
			}
			if (t == 599) cnum = (++cnum) % 2;
			break;
		}
		case 4: {
			int i, j, k, n, t = (boss_shot.counter - 120) % 420,
				t2 = boss_shot.counter;
			static int tm;
			double angle;
			//周期の最初にtmをセット
			if (boss_shot.counter == 0) {
				warp_flag = 1;
				boss.wx = BOSS_POS_X + adj_boss_x[stage - 1];//ボスの初期座標
				boss.wy = BOSS_POS_Y + adj_boss_y[stage - 1];//ボスの初期座標
			}
			else if (boss_shot.counter == 120) {
				boss.atk_flag = 1;
				boss.plus_range = 30;
			}
			if (boss.hp < boss.set_hp[4] * 1 / 3) {
				if (t >= 0 && (t - 170) % 50 == 0) {
					int div = ((t - 170) % 70 == 0) ? -1 : 1;
					angle = BossAtan2();//自機とボスとの成す角
					for (int i = 0; i < 2; i++) {//速度の違う2つの弾がある
						for (t = 0; t < 1; t++) {//1箇所から1つにわかれる
							for (int s = 0; s < 30; s++) {//1周30個
								if ((k = SerchBossShot()) != -1) {
									boss_shot.bullet[k].color = i + 4;//弾の色
									boss_shot.bullet[k].x = boss.x + adj_boss_bul_x[stage - 1];//座標
									boss_shot.bullet[k].y = boss.y + adj_boss_bul_y[stage - 1] + 30;
									boss_shot.bullet[k].type = 4;//弾の種類
									boss_shot.bullet[k].angle = angle + M_PI * 4 / 30 * s;//角度
									boss_shot.bullet[k].flag = 1;
									boss_shot.bullet[k].counter = 0;
									boss_shot.bullet[k].speed = 2 - 0.2 * i;//スピード
									boss_shot.bullet[k].effect = 0;
									boss_shot.bullet[k].state = 0;
									boss_shot.bullet[k].base_angle[0] = M_PI / 300 * div;
								}
							}
						}
						Enemy.se_flag[0] = 1;
					}
				}
				if (t >= 0 && t % 30 == 0) {
					angle = BossAtan2();
					for (int i = 0; i < 2; i++) {
						for (int j = 0; j < 60; j++) {
							if ((k = SerchBossShot()) != -1) {
								boss_shot.bullet[k].color = 0;
								boss_shot.bullet[k].x = boss.x + adj_boss_bul_x[stage - 1];//座標
								boss_shot.bullet[k].y = boss.y + adj_boss_bul_y[stage - 1] + 30;
								boss_shot.bullet[k].type = 7;
								boss_shot.bullet[k].angle = angle + t2 * 5 + M_PI * 2 / 30 * j;
								boss_shot.bullet[k].flag = 1;
								boss_shot.bullet[k].counter = 0;
								boss_shot.bullet[k].speed = 1;
								boss_shot.bullet[k].state = 0;
								Enemy.se_flag[0] = 1;
							}
						}
					}
				}
			}
			if (boss.set_hp[4] * 1 / 3 <= boss.hp && boss.hp < boss.set_hp[4] * 2 / 3) {
				if (t >= 0 && (t - 170) % 50 == 0) {
					int div = ((t - 170) % 70 == 0) ? -1 : 1;
					angle = BossAtan2();//自機とボスとの成す角
					for (int i = 0; i < 1; i++) {//速度の違う2つの弾がある
						for (t = 0; t < 1; t++) {//1箇所から1つにわかれる
							for (int s = 0; s < 30; s++) {//1周30個
								if ((k = SerchBossShot()) != -1) {
									boss_shot.bullet[k].color = i + 4;//弾の色
									boss_shot.bullet[k].x = boss.x + adj_boss_bul_x[stage - 1];//座標
									boss_shot.bullet[k].y = boss.y + adj_boss_bul_y[stage - 1] + 30;
									boss_shot.bullet[k].type = 4;//弾の種類
									boss_shot.bullet[k].angle = angle + M_PI * 4 / 30 * s;//角度
									boss_shot.bullet[k].flag = 1;
									boss_shot.bullet[k].counter = 0;
									boss_shot.bullet[k].speed = 2 - 0.2 * i;//スピード
									boss_shot.bullet[k].effect = 0;
									boss_shot.bullet[k].state = 0;
									boss_shot.bullet[k].base_angle[0] = M_PI / 300 * div;
								}
							}
						}
						Enemy.se_flag[0] = 1;
					}
				}
				if (t >= 0 && t % 30 == 0) {
					angle = BossAtan2();
					for (int i = 0; i < 2; i++) {
						for (int j = 0; j < 60; j++) {
							if ((k = SerchBossShot()) != -1) {
								boss_shot.bullet[k].color = 0;
								boss_shot.bullet[k].x = boss.x + adj_boss_bul_x[stage - 1];//座標
								boss_shot.bullet[k].y = boss.y + adj_boss_bul_y[stage - 1] + 30;
								boss_shot.bullet[k].type = 7;
								boss_shot.bullet[k].angle = angle + t2 * 5 + M_PI * 2 / 30 * j;
								boss_shot.bullet[k].flag = 1;
								boss_shot.bullet[k].counter = 0;
								boss_shot.bullet[k].speed = 1;
								boss_shot.bullet[k].state = 0;
								Enemy.se_flag[0] = 1;
							}
						}
					}
				}
			}
			if (boss.set_hp[4] * 2 / 3 < boss.hp) {
				if (t >= 0 && t % 30 == 0) {
					angle = BossAtan2();
					for (int i = 0; i < 2; i++) {
						for (int j = 0; j < 60; j++) {
							if ((k = SerchBossShot()) != -1) {
								boss_shot.bullet[k].color = 0;
								boss_shot.bullet[k].x = boss.x + adj_boss_bul_x[stage - 1];//座標
								boss_shot.bullet[k].y = boss.y + adj_boss_bul_y[stage - 1] + 30;
								boss_shot.bullet[k].type = 7;
								boss_shot.bullet[k].angle = angle + t2 * 5 + M_PI * 2 / 30 * j;
								boss_shot.bullet[k].flag = 1;
								boss_shot.bullet[k].counter = 0;
								boss_shot.bullet[k].speed = 1;
								boss_shot.bullet[k].state = 0;
								Enemy.se_flag[0] = 1;
							}
						}
					}
				}

			}
			break;
		}
		break;
	}	
	}	
}	

void Boss_obj::BossShotH(int stage) {
	int k, t;
	switch (stage) {
	case 1://一面のボスの弾幕
		switch (boss.type) {
		case 0://第1形態
			t = boss_shot.counter % 120;
			double angle;
			if (t < 60 && t % 10 == 0) {
				angle = BossAtan2();
				for (int i = 0; i < 30; i++) {
					if ((k = SerchBossShot()) != -1) {
						boss_shot.bullet[k].color = 0;
						boss_shot.bullet[k].x = boss.x + adj_boss_bul_x[stage - 1];//座標
						boss_shot.bullet[k].y = boss.y + adj_boss_bul_y[stage - 1];
						boss_shot.bullet[k].type = 8;
						boss_shot.bullet[k].angle = angle + M_PI * 2 / 30 * i;
						boss_shot.bullet[k].flag = 1;
						boss_shot.bullet[k].counter = 0;
						boss_shot.bullet[k].speed = 5;
						Enemy.se_flag[0] = 1;
					}
				}
			}
			if (t % 55 == 0) {
				angle = BossAtan2();
				for (int j = 0; j < 30; j++) {
					if ((k = SerchBossShot()) != -1) {
						boss_shot.bullet[k].color = 5;
						boss_shot.bullet[k].x = boss.x + adj_boss_bul_x[stage - 1];//座標
						boss_shot.bullet[k].y = boss.y + adj_boss_bul_y[stage - 1];
						boss_shot.bullet[k].type = 8;
						boss_shot.bullet[k].angle = angle + M_PI * 2 / 30 * j;
						boss_shot.bullet[k].flag = 1;
						boss_shot.bullet[k].counter = 0;
						boss_shot.bullet[k].speed = 3;
						Enemy.se_flag[0] = 1;
					}
				}
			}
			for (int i = 0; i < BOSS_BULLET_MAX; i++) {
				if (boss_shot.bullet[i].flag>0) {

				}
			}
			break;
		case 1://第2形態
			t = boss_shot.counter % 130;
			if (t < 30 && t % 10 == 0) {
				angle = BossAtan2();
				for (int i = 0; i < 30; i++) {
					if ((k = SerchBossShot()) != -1) {
						boss_shot.bullet[k].color = 0;
						boss_shot.bullet[k].x = boss.x + adj_boss_bul_x[stage - 1];//座標
						boss_shot.bullet[k].y = boss.y + adj_boss_bul_y[stage - 1];
						boss_shot.bullet[k].type = 6;
						boss_shot.bullet[k].angle = angle + M_PI * 1.5 / 21 * i;
						boss_shot.bullet[k].flag = 1;
						boss_shot.bullet[k].counter = 0;
						boss_shot.bullet[k].speed = 3;
						Enemy.se_flag[0] = 1;
					}
				}
			}
			if (30 <= t && t < 60 && t % 10 == 0) {
				angle = BossAtan2();
				for (int i = 0; i < 30; i++) {
					if ((k = SerchBossShot()) != -1) {
						boss_shot.bullet[k].color = 1;
						boss_shot.bullet[k].x = boss.x + adj_boss_bul_x[stage - 1];//座標
						boss_shot.bullet[k].y = boss.y + adj_boss_bul_y[stage - 1];
						boss_shot.bullet[k].type = 6;
						boss_shot.bullet[k].angle = angle + M_PI * 1.5 / 19 * i;
						boss_shot.bullet[k].flag = 1;
						boss_shot.bullet[k].counter = 0;
						boss_shot.bullet[k].speed = 3;
						Enemy.se_flag[0] = 1;
					}
				}
			}
			if (60 <= t && t < 90 && t % 10 == 0) {
				angle = BossAtan2();
				for (int i = 0; i < 30; i++) {
					if ((k = SerchBossShot()) != -1) {
						boss_shot.bullet[k].color = 2;
						boss_shot.bullet[k].x = boss.x + adj_boss_bul_x[stage - 1];//座標
						boss_shot.bullet[k].y = boss.y + adj_boss_bul_y[stage - 1];
						boss_shot.bullet[k].type = 6;
						boss_shot.bullet[k].angle = angle + M_PI * 1.5 / 17 * i;
						boss_shot.bullet[k].flag = 1;
						boss_shot.bullet[k].counter = 0;
						boss_shot.bullet[k].speed = 3;
						Enemy.se_flag[0] = 1;
					}
				}
			}
			if (90 <= t && t < 120 && t % 10 == 0) {
				angle = BossAtan2();
				for (int i = 0; i < 30; i++) {
					if ((k = SerchBossShot()) != -1) {
						boss_shot.bullet[k].color = t%3;
						boss_shot.bullet[k].x = boss.x + adj_boss_bul_x[stage - 1];//座標
						boss_shot.bullet[k].y = boss.y + adj_boss_bul_y[stage - 1];
						boss_shot.bullet[k].type = 6;
						boss_shot.bullet[k].angle = angle + M_PI * 1.5 / 15 * i;
						boss_shot.bullet[k].flag = 1;
						boss_shot.bullet[k].counter = 0;
						boss_shot.bullet[k].speed = 3;
						Enemy.se_flag[0] = 1;
					}
				}
			}
			for (int i = 0; i < BOSS_BULLET_MAX; i++) {
				if (boss_shot.bullet[i].flag>0) {

				}
			}
			break;
		case 2://最終形態
			t = boss_shot.counter % 120;
			if (t < 96 && t % 8 == 0) {
				angle = BossAtan2();
				for (int i = 0; i < 30; i++) {
					if ((k = SerchBossShot()) != -1) {
						boss_shot.bullet[k].color = (t/5) % 5;
						boss_shot.bullet[k].x = boss.x + adj_boss_bul_x[stage - 1];//座標
						boss_shot.bullet[k].y = boss.y + adj_boss_bul_y[stage - 1];
						boss_shot.bullet[k].type = 1;
						boss_shot.bullet[k].angle = angle + M_PI * 2 / 30 * i;
						boss_shot.bullet[k].flag = 1;
						boss_shot.bullet[k].counter = 0;
						boss_shot.bullet[k].speed = (t/5) % 3 + 3;
						Enemy.se_flag[0] = 1;
					}
				}
			}
			for (int i = 0; i < BOSS_BULLET_MAX; i++) {
				if (boss_shot.bullet[i].flag>0) {

				}
			}
			break;
		case 3:
			Control.SetStage(s2_loading);
			break;
		}
		break;
	case 2://二面のボスの弾幕
		switch (boss.type) {
		case 0:
		{
			t = boss_shot.counter % 1000;
			double	angle = M_PI;
			for (int i = 0; i < 1; i++) {
				if (t % 5 == 0) {
					if ((k = SerchBossShot()) != -1) {
						boss_shot.bullet[k].color = 1;
						boss_shot.bullet[k].x = boss.x + adj_boss_bul_x[stage - 1];//座標
						boss_shot.bullet[k].y = boss.y + adj_boss_bul_y[stage - 1];
						boss_shot.bullet[k].type = 1;
						boss_shot.bullet[k].angle = -(angle + M_PI *(30 * ( t % 4 + 1) + Enemy.Rang(36)) / 180);
						boss_shot.bullet[k].flag = 1;
						boss_shot.bullet[k].counter = 0;
						boss_shot.bullet[k].speed = 5 + t % 4;
						Enemy.se_flag[0] = 1;
					}
				}
			}

			for (int i = 0; i < BOSS_BULLET_MAX; i++) {
				
					if (t % 49 == 0)
						boss_shot.bullet[i].speed = 0;
					if (t % 99 == 0)
						boss_shot.bullet[i].speed = 5 + t % 4;
			}
			
			int tt = boss_shot.counter % 120;
			if (tt < 60 && tt % 10 == 0) {
				angle = BossAtan2();
				for (int j = 0; j < 30; j++) {
					if ((k = SerchBossShot()) != -1) {
						boss_shot.bullet[k].color = 0;
						boss_shot.bullet[k].x = boss.x + adj_boss_bul_x[stage - 1];//座標
						boss_shot.bullet[k].y = boss.y + adj_boss_bul_y[stage - 1];
						boss_shot.bullet[k].type = 2;
						boss_shot.bullet[k].angle = angle + M_PI * 3 / 30 * j;
						boss_shot.bullet[k].flag = 1;
						boss_shot.bullet[k].counter = 0;
						boss_shot.bullet[k].speed = 5;
						Enemy.se_flag[0] = 1;
					}
				}
			}
			break;
		}
		case 1: {
			t = boss_shot.counter % 90;
			double	angle = -M_PI / 4;
			if (t == 0) {
				boss.atk_flag = 1;
			}
			else if (t == 60) {
				boss.atk_flag = 0;
			}
			if (t <= 40 && t % 10 == 0) {
				for (int i = 0; i < 40; i++) {
						if ((k = SerchBossShot()) != -1) {
						boss_shot.bullet[k].color = 0;
						boss_shot.bullet[k].x = boss.x;//座標
						boss_shot.bullet[k].y = boss.y;
						boss_shot.bullet[k].type = 8;
						boss_shot.bullet[k].angle = angle + (t / 5 + 3 * (i + 1)) % 120 * M_PI / 80;
						boss_shot.bullet[k].flag = 1;
						boss_shot.bullet[k].speed = 4;
						boss_shot.bullet[k].counter = 0;
						Enemy.se_flag[0] = 1;
					}
				}
			}
				break;
			}
		case 2:
		{
			t = boss_shot.counter % 150;
			double	angle = M_PI;
			for (int i = 0; i < 5; i++) {
				if (t == 30) {
					if ((k = SerchBossShot()) != -1) {
						boss_shot.bullet[k].color = 0;
						boss_shot.bullet[k].x = boss.x + adj_boss_bul_x[stage - 1];//座標
						boss_shot.bullet[k].y = boss.y + adj_boss_bul_y[stage - 1];
						boss_shot.bullet[k].type = 1;
						boss_shot.bullet[k].angle = -(angle + M_PI *(30 * (i + 1) + Enemy.Rang(18)) / 180);
						boss_shot.bullet[k].flag = 2;
						boss_shot.bullet[k].counter = 0;
						boss_shot.bullet[k].speed = 4;
						Enemy.se_flag[0] = 1;
					}
				}
			}

			for (int i = 0; i < BOSS_BULLET_MAX; i++) {
				if (boss_shot.bullet[i].flag == 1) {
					if (boss_shot.bullet[i].counter == 15) {
						boss_shot.bullet[i].speed = 0;
					}
					else if (boss_shot.bullet[i].counter == 65) {
						boss_shot.bullet[i].speed = 2 + GetRand(3);
					}
				}
				if (boss_shot.bullet[i].flag == 2) {
					if (boss_shot.bullet[i].counter == 30) {
						boss_shot.bullet[i].speed = 0;
						boss_shot.bullet[i].flag = 0;

						for (int j = 0; j < 60; j++) {
							if ((k = SerchBossShot()) != -1) {
								boss_shot.bullet[k].color = 0;
								boss_shot.bullet[k].x = boss_shot.bullet[i].x;//座標
								boss_shot.bullet[k].y = boss_shot.bullet[i].y;
								boss_shot.bullet[k].type = 8;
								boss_shot.bullet[k].angle = angle + M_PI * 2 / 30 * j;
								boss_shot.bullet[k].flag = 1;
								boss_shot.bullet[k].counter = 0;
								if (j < 30) {
									boss_shot.bullet[k].speed = 2;
								}
								else {
									boss_shot.bullet[k].speed = 4;
								}
								Enemy.se_flag[0] = 1;
							}
						}
					}
				}
			}
			break;
		}
		case 3:
			Control.SetStage(s3_loading);
			break;
		}
		break;

	case 3://三面のボスの弾幕 合間に軽い全方位
		switch (boss.type) {
		case 2: 
			t = boss_shot.counter % 121;
			double angle;
			if (t == 60) {
				angle = BossAtan2() + t;
				for (int i = 0; i < 1; i++) {
					for (int j = 0; j < 60; j++) {
						if ((k = SerchBossShot()) != -1) {
							boss_shot.bullet[k].color = 0;
							boss_shot.bullet[k].x = boss.x + adj_boss_bul_x[stage - 1];//座標
							boss_shot.bullet[k].y = boss.y + adj_boss_bul_y[stage - 1];
							boss_shot.bullet[k].type = 7;
							boss_shot.bullet[k].angle = boss_shot.counter + M_PI * 2 / 60 * j;
							boss_shot.bullet[k].flag = 1;
							boss_shot.bullet[k].counter = 0;
							boss_shot.bullet[k].speed = 3;
							boss_shot.bullet[k].state = 0;
							Enemy.se_flag[0] = 1;
						}
					}
				}
			}
			if (t == 90) {
				angle = BossAtan2();
				for (int i = 0; i < 1; i++) {
					for (int j = 0; j < 60; j++) {
						if ((k = SerchBossShot()) != -1) {
							boss_shot.bullet[k].color = 4;
							boss_shot.bullet[k].x = boss.x + adj_boss_bul_x[stage - 1];//座標
							boss_shot.bullet[k].y = boss.y + adj_boss_bul_y[stage - 1];
							boss_shot.bullet[k].type = 7;
							boss_shot.bullet[k].angle = angle + boss_shot.counter + M_PI * 2 / 60 * j;
							boss_shot.bullet[k].flag = 2;
							boss_shot.bullet[k].counter = 0;
							boss_shot.bullet[k].speed = 1.5;
							boss_shot.bullet[k].state = 0;
							Enemy.se_flag[0] = 1;
						}
					}
				}
			}
			if (t == 120) {
				angle = BossAtan2();
				for (int i = 0; i < 1; i++) {
					for (int j = 0; j < 60; j++) {
						if ((k = SerchBossShot()) != -1) {
							boss_shot.bullet[k].color = 0;
							boss_shot.bullet[k].x = boss.x + adj_boss_bul_x[stage - 1];//座標
							boss_shot.bullet[k].y = boss.y + adj_boss_bul_y[stage - 1];
							boss_shot.bullet[k].type = 7;
							boss_shot.bullet[k].angle = boss_shot.counter + M_PI * 2 / 60 * j;
							boss_shot.bullet[k].flag = 1;
							boss_shot.bullet[k].counter = 0;
							boss_shot.bullet[k].speed = 3;
							boss_shot.bullet[k].state = 1;
							Enemy.se_flag[0] = 1;
						}
					}
				}
			}
			for (int i = 0; i < BOSS_BULLET_MAX; i++) {
				if (boss_shot.bullet[i].flag == 1) {
					int state = boss_shot.bullet[i].state;
					int cnt = boss_shot.bullet[i].counter;
					if (30 < cnt && cnt < 120) {	//30～120カウントなら
						boss_shot.bullet[i].speed -= 1.2 / 60.0;	//60カウントかけて1.2減らす
						boss_shot.bullet[i].angle += (M_PI / 3) / 90 * (state ? -1 : 1);	//60カウントかけて90°傾ける
					}
				}
			}
			break;
		case 1: {
			t = boss_shot.counter % 361;
			int t2 = boss_shot.counter, cnum;
			double x, y, xlen = FIELD_MAX_X / 8;
			int dnumy = FIELD_MAX_Y / xlen;
			double ylen = FIELD_MAX_Y / dnumy;
			if (t == 60) {
				x = 0, y = 0, angle = 0, cnum = 0;
				for (int i = 0; i < 4; i++) {	//画面左上端から　右→下→左→上　の４方向移動させる
					int to = i % 2 ? dnumy : 8;
					for (int j = 0; j <= to; j++) {
						for (int s = 0; s < 4; s++) {
							if ((k = SerchBossShot()) != -1) {
								boss_shot.bullet[k].x = x;//座標
								boss_shot.bullet[k].y = y;
								boss_shot.bullet[k].type = 1;//弾の種類
								boss_shot.bullet[k].flag = 1;
								boss_shot.bullet[k].counter = 0;				
								boss_shot.bullet[k].color = 0;//弾の色
								boss_shot.bullet[k].angle = angle + M_PI / 2;//角度
								boss_shot.bullet[k].speed = 0.8;//スピード
								boss_shot.bullet[k].state = 0;//ステータス
								Enemy.se_flag[0] = 1;
								cnum++;
							}
						}
						x += cos(angle) * xlen;
						y += sin(angle) * ylen;
					}
					angle += M_PI / 2;
				}
			}
			if (t == 180) {
				x = 0, y = 0, angle = 0, cnum = 0;
				for (int i = 0; i < 4; i++) {	//画面左上端から　右→下→左→上　の４方向移動させる
					int to = i % 2 ? dnumy : 8;
					for (int j = 0; j <= to; j++) {
						for (int s = 0; s < 4; s++) {
							if ((k = SerchBossShot()) != -1) {
								boss_shot.bullet[k].x = x + 25;//座標
								boss_shot.bullet[k].y = y - 25;
 								boss_shot.bullet[k].type = 1;//弾の種類
								boss_shot.bullet[k].flag = 1;
								boss_shot.bullet[k].counter = 0;
								boss_shot.bullet[k].color = 1;//弾の色
								boss_shot.bullet[k].angle = angle + M_PI / 2;//角度
								boss_shot.bullet[k].speed = 0.8;//スピード
								boss_shot.bullet[k].state = 0;//ステータス
								Enemy.se_flag[0] = 1;
								cnum++;
							}
						}
						x += cos(angle) * xlen;
						y += sin(angle) * ylen;
					}
					angle += M_PI / 2;
				}
			}
			if (t == 300) {
				x = 0, y = 0, angle = 0, cnum = 0;
				for (int i = 0; i < 4; i++) {	//画面左上端から　右→下→左→上　の４方向移動させる
					int to = i % 2 ? dnumy : 8;
					for (int j = 0; j <= to; j++) {
						for (int s = 0; s < 4; s++) {
							if ((k = SerchBossShot()) != -1) {
								boss_shot.bullet[k].x = x + 10;//座標
								boss_shot.bullet[k].y = y - 10;
								boss_shot.bullet[k].type = 1;//弾の種類
								boss_shot.bullet[k].flag = 1;
								boss_shot.bullet[k].counter = 0;
								boss_shot.bullet[k].color = 2;//弾の色
								boss_shot.bullet[k].angle = angle + M_PI / 2;//角度
								boss_shot.bullet[k].speed = 0.8;//スピード
								boss_shot.bullet[k].state = 0;//ステータス
								Enemy.se_flag[0] = 1;
								cnum++;
							}
						}
						x += cos(angle) * xlen;
						y += sin(angle) * ylen;
					}
					angle += M_PI / 2;
				}
			}
			for (int i = 0; i < BOSS_BULLET_MAX; i++) {
				
			}
			break;
		}
		case 0: {
			t = boss_shot.counter % 311;
			int num, t2 = boss_shot.counter;
			if (t2 == 0) num = 0;
			if (t == 60) {
				angle = BossAtan2();
				for (int i = 0; i < 2; i++) {
					for (t = 0; t < 3; t++) {
						for (int j = 0; j < 3; j++) {
							for (int s = 0; s < 30; s++) {
								if ((k = SerchBossShot()) != -1) {
									boss_shot.bullet[k].color = i;//弾の色
									boss_shot.bullet[k].x = boss.x + adj_boss_bul_x[stage - 1];//座標
									boss_shot.bullet[k].y = boss.y + adj_boss_bul_y[stage - 1];
									boss_shot.bullet[k].type = 2;//弾の種類
									boss_shot.bullet[k].angle = angle + M_PI * 2 / 30 * s + M_PI * 2 / 60 * i;//角度
									boss_shot.bullet[k].flag = 1;
									boss_shot.bullet[k].counter = 0;
									boss_shot.bullet[k].speed = 1.8 - 0.2 * j + 0.1 * i;//スピード
									boss_shot.bullet[k].effect = 0;
									boss_shot.bullet[k].state = t;
								}
								Enemy.se_flag[0] = 1;
							}
						}
					}
				}
			}
			if (t == 210) {
				angle = BossAtan2();
				for (int i = 0; i < 2; i++) {
					for (t = 0; t < 3; t++) {
						for (int j = 0; j < 3; j++) {
							for (int s = 0; s < 30; s++) {
								if ((k = SerchBossShot()) != -1) {
									boss_shot.bullet[k].color = i + 1;//弾の色
									boss_shot.bullet[k].x = boss.x + adj_boss_bul_x[stage - 1];//座標
									boss_shot.bullet[k].y = boss.y + adj_boss_bul_y[stage - 1];
									boss_shot.bullet[k].type = 2;//弾の種類
									boss_shot.bullet[k].angle = angle + M_PI * 2 / 30 * s + M_PI * 2 / 60 * i;//角度
									boss_shot.bullet[k].flag = 1;
									boss_shot.bullet[k].counter = 0;
									boss_shot.bullet[k].speed = 1.8 - 0.2 * j + 0.1 * i;//スピード
									boss_shot.bullet[k].effect = 0;
									boss_shot.bullet[k].state = t;
								}
								Enemy.se_flag[0] = 1;
							}
						}
					}
				}
			}
			for (int i = 0; i < BOSS_BULLET_MAX; i++) {
				if (boss_shot.bullet[i].flag > 0) {
					int cnt = boss_shot.bullet[i].counter;
					int state = boss_shot.bullet[i].state;
					if (state % 10 == 0) {
						if (cnt > 90 && cnt <= 100)
							boss_shot.bullet[i].speed -= boss_shot.bullet[i].speed / 220;
					}
					if (state % 10 == 1) {
						if (cnt > 50)
							boss_shot.bullet[i].speed += boss_shot.bullet[i].speed / 45;
					}
					if (state % 10 == 2) {
						if (cnt > 65)
							boss_shot.bullet[i].speed += boss_shot.bullet[i].speed / 90;
					}
					if (10 <= state && state <= 12) {
						if (cnt > 15 && cnt <= 80)
							boss_shot.bullet[i].angle += boss_shot.bullet[i].base_angle[0];
					}
				}
			}
			break;
		}
		case 3:
			Control.SetStage(s4_loading);
			break;
		}
		break;

	case 4://四面のボスの弾幕
		switch (boss.type) {
		case 2: {
			int i, j, k, n, t = boss_shot.counter % 200, 
				t2 = boss_shot.counter;
			static int tm;
			double angle;
			//周期の最初にtmをセット
			if (t == 0)
				tm = 190 + Enemy.Rang(30);
			angle = M_PI * 1.5 + M_PI / 5 * sin(M_PI * 2  / tm * t2);
			//4カウントに1回上に8way弾を撃つ
			if (t2 % 4 == 0) {
				for (n = 0; n<8; n++) {
					if ((k = SerchBossShot()) != -1) {
						boss_shot.bullet[k].flag = 1;
						boss_shot.bullet[k].state = 0;
						boss_shot.bullet[k].counter = 0;
						boss_shot.bullet[k].type = 7;
						boss_shot.bullet[k].color = 7;
						boss_shot.bullet[k].angle = 0;
						boss_shot.bullet[k].effect = 0;
						boss_shot.bullet[k].x = boss.x;
						boss_shot.bullet[k].y = boss.y;
						boss_shot.bullet[k].vx = cos(angle - M_PI / 8 * 4 + M_PI / 8 * n + M_PI / 16) * 3;
						boss_shot.bullet[k].vy = sin(angle - M_PI / 8 * 4 + M_PI / 8 * n +M_PI / 16) * 3;
						boss_shot.bullet[k].till = 300;
					}
				}
				Enemy.se_flag[0] = 1;
			}
			if (t2 % 3 == 0) {
				angle = -M_PI * 1.5 + M_PI / 5 * sin(M_PI * 2 / tm);
				for (n = 0; n < 8; n++) {
					if ((k = SerchBossShot()) != -1) {
						boss_shot.bullet[k].flag = 1;
						boss_shot.bullet[k].state = 1;
						boss_shot.bullet[k].counter = 0;
						boss_shot.bullet[k].type = 1;
						boss_shot.bullet[k].color = 1;
						boss_shot.bullet[k].angle = 0;
						boss_shot.bullet[k].effect = 0;
						boss_shot.bullet[k].x = boss.x;
						boss_shot.bullet[k].y = boss.y;
						boss_shot.bullet[k].vx = cos(angle - M_PI / 8 * 4 + M_PI / 8 * n + M_PI / 16) * 3;
						boss_shot.bullet[k].vy = sin(angle - M_PI / 8 * 4 + M_PI / 8 * n + M_PI / 16) * 3;
						boss_shot.bullet[k].till = 300;
					}
				}
				Enemy.se_flag[0] = 1;
			}
			for (i = 0; i<BOSS_BULLET_MAX; i++) {
				if (boss_shot.bullet[i].flag>0) {
					if (boss_shot.bullet[i].state == 0) {
						if (boss_shot.bullet[i].counter<150)
							boss_shot.bullet[i].vy += 0.03;
						boss_shot.bullet[i].x += boss_shot.bullet[i].vx;
						boss_shot.bullet[i].y += boss_shot.bullet[i].vy;
					}
					if (boss_shot.bullet[i].state == 1) {
						if (boss_shot.bullet[i].counter<160)
							boss_shot.bullet[i].vy += 0.03;
						boss_shot.bullet[i].x += boss_shot.bullet[i].vx;
						boss_shot.bullet[i].y += boss_shot.bullet[i].vy;
						boss_shot.bullet[i].angle = atan2(boss_shot.bullet[i].vy, boss_shot.bullet[i].vx);
					}
				}
			}
		}
			break;
		case 0: {
			int i, j, k, n, num, t2 = boss_shot.counter % 540;
			double angle;
			//周期の最初にtmをセット
			if (t2 == 0) num = 0;
			angle = -M_PI / sin(M_PI / t2);
			if (0 < t2 && t2 < 180 && t2 % 2 == 0) {
				for (n = 0; n < 3; n++) {
					if ((k = SerchBossShot()) != -1) {
						boss_shot.bullet[k].flag = 1;
						boss_shot.bullet[k].state = 0;
						boss_shot.bullet[k].counter = 0;
						boss_shot.bullet[k].type = 7;
						boss_shot.bullet[k].color = 8;
						boss_shot.bullet[k].angle = 0;
						boss_shot.bullet[k].effect = 0;
						boss_shot.bullet[k].x = boss.x;
						boss_shot.bullet[k].y = boss.y;
						boss_shot.bullet[k].vx = cos(-angle - M_PI / 8 * 4 + M_PI / 8 * n + M_PI / 16) * 3 / 2;
						boss_shot.bullet[k].vy = sin(-angle - M_PI / 8 * 4 + M_PI / 8 * n + M_PI / 16) * 3 / 2;
					}
				}
				Enemy.se_flag[0] = 1;
			}
			if (180 < t2 && t2 < 450 && t2 % 2 == 0) {
				for (n = 0; n < 3; n++) {
					if ((k = SerchBossShot()) != -1) {
						boss_shot.bullet[k].flag = 1;
						boss_shot.bullet[k].state = 0;
						boss_shot.bullet[k].counter = 0;
						boss_shot.bullet[k].type = 1;
						boss_shot.bullet[k].color = 1;
						boss_shot.bullet[k].angle = 0;
						boss_shot.bullet[k].effect = 0;
						boss_shot.bullet[k].x = boss.x;
						boss_shot.bullet[k].y = boss.y;
						boss_shot.bullet[k].vx = cos(angle - M_PI / 8 * 4 + M_PI / 8 * n + M_PI / 16) * 3 / 2;
						boss_shot.bullet[k].vy = sin(angle - M_PI / 8 * 4 + M_PI / 8 * n + M_PI / 16) * 3 / 2;
					}
				}
				Enemy.se_flag[0] = 1;
			}
			if (450 < t2 && t2 < 540 && t2 % 2 == 0) {
				for (n = 0; n < 3; n++) {
					if ((k = SerchBossShot()) != -1) {
						boss_shot.bullet[k].flag = 1;
						boss_shot.bullet[k].state = 0;
						boss_shot.bullet[k].counter = 0;
						boss_shot.bullet[k].type = 7;
						boss_shot.bullet[k].color = 8;
						boss_shot.bullet[k].angle = 0;
						boss_shot.bullet[k].effect = 0;
						boss_shot.bullet[k].x = boss.x;
						boss_shot.bullet[k].y = boss.y;
						boss_shot.bullet[k].vx = cos(-angle - M_PI / 8 * 4 + M_PI / 8 * n + M_PI / 16) * 3 / 2;
						boss_shot.bullet[k].vy = sin(-angle - M_PI / 8 * 4 + M_PI / 8 * n + M_PI / 16) * 3 / 2;
					}
				}
				Enemy.se_flag[0] = 1;
			}
			for (i = 0; i < BOSS_BULLET_MAX; i++) {
				if (boss_shot.bullet[i].flag>0) {
					if (boss_shot.bullet[i].state == 0) {
						if (boss_shot.bullet[i].counter < 150)
							boss_shot.bullet[i].vy += 0.0005;
						boss_shot.bullet[i].x += boss_shot.bullet[i].vx;
						boss_shot.bullet[i].y += boss_shot.bullet[i].vy;
					}
					if (boss_shot.bullet[i].state == 1) {
						if (boss_shot.bullet[i].counter < 160)
							boss_shot.bullet[i].vy += 0.0005;
						boss_shot.bullet[i].x += boss_shot.bullet[i].vx;
						boss_shot.bullet[i].y += boss_shot.bullet[i].vy;
						boss_shot.bullet[i].angle = atan2(boss_shot.bullet[i].vy, boss_shot.bullet[i].vx);
					}
				}
			}
			if (t2 == 540) num = (++num);
			break;
		}
		case 1: {
			t = boss_shot.counter % 600;
			int t2 = boss_shot.counter;
			double angle;
			static int tcnt, cnt, cnum;
			if (t == 0) {
				boss_shot.base_angle[0] = BossAtan2();
				cnt = 0;
				tcnt = 2;
			}
			if (t < 540 && t % 30) {
				angle = BossAtan2();
				if (tcnt - 2 == cnt || tcnt - 1 == cnt) {
					if (tcnt - 1 == cnt) {
						boss_shot.base_angle[1] = boss_shot.base_angle[0] + M_PI * 2 / 20 * cnt * (cnum ? -1 : 1) - M_PI * 2 / 120 * 3; //レーザーの角度
						tcnt += 18;
					}
				}
				else {
					for (int i = 0; i < 18; i++) {
						if ((k = SerchBossShot()) != -1) {
							boss_shot.bullet[k].color = cnum ? 1 : 5;
							boss_shot.bullet[k].x = boss.x + adj_boss_bul_x[stage - 1];//座標
							boss_shot.bullet[k].y = boss.y + adj_boss_bul_y[stage - 1];
							boss_shot.bullet[k].type = 8;
							boss_shot.bullet[k].angle = boss_shot.base_angle[0] + M_PI * 10 / 20 * cnt * (cnum ? -1 : 1) + M_PI * 10 / 100 * i * (cnum ? -1 : 1);
							boss_shot.bullet[k].flag = 1;
							boss_shot.bullet[k].counter = 0;
							boss_shot.bullet[k].speed = 2;
							Enemy.se_flag[0] = 1;
						}
					}
				}
				cnt++;
			}
			if (40 < t && t < 540 && t % 30 == 0) {
				for (int i = 0; i < 2; i++) {
					angle = boss_shot.base_angle[1] - M_PI * 2 / 36 * 4;
					for (int j = 0; j < 15; j++) {
						if ((k = SerchBossShot()) != -1) {
							boss_shot.bullet[k].color = cnum ? 5 : 1;
							boss_shot.bullet[k].x = boss.x + adj_boss_bul_x[stage - 1];//座標
							boss_shot.bullet[k].y = boss.y + adj_boss_bul_y[stage - 1];
							boss_shot.bullet[k].type = 7;
							boss_shot.bullet[k].angle = angle;
							boss_shot.bullet[k].flag = 1;
							boss_shot.bullet[k].counter = 0;
							boss_shot.bullet[k].speed = 4 - 1.6 / 3 * i;
							Enemy.se_flag[0] = 1;
						}
						angle -= M_PI * 10 / 36;
					}
				}
			}
			for (int i = 0; i < BOSS_BULLET_MAX; i++) {
				if (boss_shot.bullet[i].flag>0) {

				}
			}
			if (t == 599) cnum = (++cnum) % 2;
			break;
		}
		case 3:
			Control.SetStage(s5_loading);
			break;
		}
		break;

	case 5://最終面のボスの弾幕
		switch (boss.type) {
		case 0: {
			t = (boss_shot.counter - 90) % 200;
			int bul_count = 0;
			//左右への移動を制限する為の弾幕
			if (boss_shot.counter == 60) {
				for (int i = 0; i < 2; i++) {
					if ((k = SerchBossShot()) != -1) {
						boss_shot.bullet[k].color = 1;
						boss_shot.bullet[k].x = boss.x + adj_boss_bul_x[stage - 1];//座標
						boss_shot.bullet[k].y = boss.y + adj_boss_bul_y[stage - 1];
						boss_shot.bullet[k].type = 1;
						boss_shot.bullet[k].angle = -M_PI*(1 + 4 * i) / 6;
						boss_shot.bullet[k].flag = 10;
						boss_shot.bullet[k].counter = 0;
						boss_shot.bullet[k].speed = 5;
						Enemy.se_flag[0] = 1;
					}
				}
			}
			else if (boss_shot.counter == 90) {
				for (int i = 0; i < BOSS_BULLET_MAX; i++) {
					if (boss_shot.bullet[i].flag == 10) {
						boss_shot.bullet[i].speed = 0;
					}
				}
			}
			else if (boss_shot.counter > 90 && boss_shot.counter % 10 == 0) {
				for (int i = 0; i < BOSS_BULLET_MAX; i++) {
					if (boss_shot.bullet[i].flag == 10) {
						for (int j = 0; j < 7; j++) {
							if ((k = SerchBossShot()) != -1) {
								boss_shot.bullet[k].color = 6;
								if (i == 1) {
									boss_shot.bullet[k].x = FIELD_X + FIELD_MAX_X - 13 * (j + 1);//座標
								}
								else {
									boss_shot.bullet[k].x = FIELD_X + 13 * (j + 1);//座標
								}
								boss_shot.bullet[k].y = boss_shot.bullet[i].y;
								boss_shot.bullet[k].type = 8;
								boss_shot.bullet[k].angle = M_PI / 2;
								boss_shot.bullet[k].flag = 9;
								boss_shot.bullet[k].counter = 0;
								boss_shot.bullet[k].speed = 6;
								Enemy.se_flag[0] = 1;
							}
						}
					}
				}
			}

			//本命(自機を包囲する弾幕)
			if (t == 30) {
				bul_count = 0;
				for (int i = 0; i < 4; i++) {
					if ((k = SerchBossShot()) != -1) {
						boss_shot.bullet[k].color = 1;
						if (i < 2) {
							boss_shot.bullet[k].x = Player.GetX() + 100;//座標
						}
						else {
							boss_shot.bullet[k].x = Player.GetX() - 100;
						}
						if (i % 2 == 0) {
							boss_shot.bullet[k].y = Player.GetY() + 100;//座標
						}
						else {
							boss_shot.bullet[k].y = Player.GetY() - 100;
						}
						boss_shot.bullet[k].vx = 0;
						boss_shot.bullet[k].vy = 0;
						boss_shot.bullet[k].type = 7;
						boss_shot.bullet[k].angle = 0;
						boss_shot.bullet[k].flag = 3;
						boss_shot.bullet[k].counter = 0;
						boss_shot.bullet[k].speed = 0;
						boss_shot.bullet[k].till = 15;
						Enemy.se_flag[0] = 1;
					}
				}
			}
			else if (t == 40) {
				for (int i = 0; i < BOSS_BULLET_MAX; i++) {
					if (boss_shot.bullet[i].flag == 3) {
						boss_shot.bullet[i].flag = 0;
						for (int j = 0; j < 2; j++) {
							for (int l = 0; l < 30; l++) {
								if ((k = SerchBossShot()) != -1) {
									boss_shot.bullet[k].vx = 0;
									boss_shot.bullet[k].vy = 0;
									boss_shot.bullet[k].color = 1;
									boss_shot.bullet[k].x = boss_shot.bullet[i].x;//座標
									boss_shot.bullet[k].y = boss_shot.bullet[i].y;
									boss_shot.bullet[k].type = 7;
									boss_shot.bullet[k].angle = M_PI*l / 15;
									boss_shot.bullet[k].flag = 2;
									boss_shot.bullet[k].counter = 0;
									boss_shot.bullet[k].speed = 3 + j;
									boss_shot.bullet[k].till = 160;
									Enemy.se_flag[0] = 1;
								}
							}
						}
					}
				}
			}
			else if (t == 60) {
				for (int i = 0; i < BOSS_BULLET_MAX; i++) {
					if (boss_shot.bullet[i].flag == 2) {
						boss_shot.bullet[i].speed = 0;
						boss_shot.bullet[i].angle = 0;
					}
				}
			}
			else if (t == 80) {
				for (int i = 0; i < BOSS_BULLET_MAX; i++) {
					if (boss_shot.bullet[i].flag == 2) {
						bul_count++;
						MoveBossShot(Player.GetX() + Enemy.Rang(2) * 10, Player.GetY() + Enemy.Rang(2) * 10, 120 - 10 * bul_count % 6, i);
					}
				}
				bul_count = 0;
			}

			break;
		}
		case 1: {
			t = boss_shot.counter % 300;
			int t2 = boss_shot.counter, cnum;
			double x, y, xlen = FIELD_MAX_X / 8;
			int dnumy = FIELD_MAX_Y / xlen;
			double ylen = FIELD_MAX_Y / dnumy;
			static int num;
			if (t2 == 0) num = 0;
			double angle;
			if (t == 0) {
				x = 0, y = 0, angle = 0, cnum = 0;
				for (int i = 0; i < 4; i++) {
					int to = i % 2 ? dnumy : 8;
					for (int j = 0; j <= to; j++) {
						for (int s = 0; s < 40; s++) {
							if ((k = SerchBossShot()) != -1) {
								boss_shot.bullet[k].x = x;
								boss_shot.bullet[k].y = y;
								boss_shot.bullet[k].type = 2;
								boss_shot.bullet[k].flag = 1;
								boss_shot.bullet[k].counter = 0;
								boss_shot.bullet[k].color = 0;
								boss_shot.bullet[k].angle = angle + M_PI / 2;
								boss_shot.bullet[k].speed = 1.2 + 0.05 * s;
								boss_shot.bullet[k].state = 0;
								Enemy.se_flag[0] = 1;
								cnum++;
							}
						}
						x += cos(angle) * xlen;
						y += sin(angle) * ylen;
					}
					angle += M_PI / 2;
				}
				for (int i = 0; i < 4; i++) {
					int to = i % 2 ? dnumy : 8;
					for (int j = 0; j <= to; j++) {
						for (int s = 0; s < 40; s++) {
							if ((k = SerchBossShot()) != -1) {
								boss_shot.bullet[k].x = x;
								boss_shot.bullet[k].y = y;
								boss_shot.bullet[k].type = 2;
								boss_shot.bullet[k].flag = 1;
								boss_shot.bullet[k].counter = 0;
								boss_shot.bullet[k].color = 3;
								boss_shot.bullet[k].angle = angle + M_PI / 3;
								boss_shot.bullet[k].speed = 1;
								boss_shot.bullet[k].state = 1;
								Enemy.se_flag[0] = 1;
								cnum++;
							}
						}
						x += cos(angle) * xlen;
						y += sin(angle) * ylen;
					}
					angle += M_PI / 2;
				}
			}
			for (int i = 0; i < BOSS_BULLET_MAX; i++) {
				if (boss_shot.bullet[i].flag>0) {
					int state = boss_shot.bullet[i].state;
					int cnt = boss_shot.bullet[i].counter;
					switch (boss_shot.bullet[i].state) {
					case 2:
						boss_shot.bullet[i].angle += boss_shot.bullet[i].base_angle[0];
						break;
					default:
						break;
					}

				}
			}
			if (t == 400) num = (++num) % 2;


			int tt = boss_shot.counter % 200;
			double angleB;
			if (tt < 60 && tt % 10 == 0) {
				angleB = BossAtan2();
				for (int i = 0; i < 30; i++) {
					if ((k = SerchBossShot()) != -1) {
						boss_shot.bullet[k].color = 2;
						boss_shot.bullet[k].x = boss.x + adj_boss_bul_x[stage - 1];//座標
						boss_shot.bullet[k].y = boss.y + adj_boss_bul_y[stage - 1];
						boss_shot.bullet[k].type = 9;
						boss_shot.bullet[k].angle = angleB + M_PI * 2 / 30 * i;
						boss_shot.bullet[k].flag = 1;
						boss_shot.bullet[k].counter = 0;
						boss_shot.bullet[k].speed = 2;
						Enemy.se_flag[0] = 1;
					}
				}
			}
			break;

		}
		case 2:
		{
			t = boss_shot.counter % 400;
			int x;
			if (t % 6 == 0 || t % 6 == 1 || t % 6 == 2)  x = -1;
			if (t % 6 == 3 || t % 6 == 4 || t % 6 == 5)  x = 1;

			double	angle = M_PI;
			for (int i = 0; i < 1; i++) {
				if (t < 100 && t % 2 == 0) {
					if ((k = SerchBossShotA()) != -1) {
						boss_shot.bullet[k].color = 0;
						boss_shot.bullet[k].x = boss.x + adj_boss_bul_x[stage - 1];//座標
						boss_shot.bullet[k].y = boss.y + adj_boss_bul_y[stage - 1];
						boss_shot.bullet[k].type = 5;
						boss_shot.bullet[k].angle = x*(angle + M_PI *(30 * (t % 4 + 2) + Enemy.Rang(36)) / 180);
						boss_shot.bullet[k].flag = 1;
						boss_shot.bullet[k].counter = 0;
						boss_shot.bullet[k].speed = 2 + t % 4;
						Enemy.se_flag[0] = 1;
					}
				}
			}
			for (int i = 0; i < 1; i++) {
				if (t < 100 && t % 2 == 1) {
					if ((k = SerchBossShotB()) != -1) {
						boss_shot.bullet[k].color = 1;
						boss_shot.bullet[k].x = boss.x + adj_boss_bul_x[stage - 1];//座標
						boss_shot.bullet[k].y = boss.y + adj_boss_bul_y[stage - 1];
						boss_shot.bullet[k].type = 5;
						boss_shot.bullet[k].angle = -x*(angle + M_PI *(30 * (t % 4 + 2) + Enemy.Rang(36)) / 180);
						boss_shot.bullet[k].flag = 1;
						boss_shot.bullet[k].counter = 0;
						boss_shot.bullet[k].speed = 2 + t % 4;
						Enemy.se_flag[0] = 1;
					}
				}
			}
			for (int i = 0; i < 1; i++) {
				if (t < 100 && t % 2 == 0) {
					if ((k = SerchBossShotC()) != -1) {
						boss_shot.bullet[k].color = 2;
						boss_shot.bullet[k].x = boss.x + adj_boss_bul_x[stage - 1];//座標
						boss_shot.bullet[k].y = boss.y + adj_boss_bul_y[stage - 1];
						boss_shot.bullet[k].type = 5;
						boss_shot.bullet[k].angle = x*(angle + M_PI *(30 * (t % 4 + 1) + Enemy.Rang(36)) / 180);
						boss_shot.bullet[k].flag = 1;
						boss_shot.bullet[k].counter = 0;
						boss_shot.bullet[k].speed = 3 + t % 4;
						Enemy.se_flag[0] = 1;
					}
				}
			}
			for (int i = 0; i < 1; i++) {
				if (t < 100 && t % 2 == 1) {
					if ((k = SerchBossShotD()) != -1) {
						boss_shot.bullet[k].color = 3;
						boss_shot.bullet[k].x = boss.x + adj_boss_bul_x[stage - 1];//座標
						boss_shot.bullet[k].y = boss.y + adj_boss_bul_y[stage - 1];
						boss_shot.bullet[k].type = 5;
						boss_shot.bullet[k].angle = -x*(angle + M_PI *(30 * (t % 4 + 1) + Enemy.Rang(36)) / 180);
						boss_shot.bullet[k].flag = 1;
						boss_shot.bullet[k].counter = 0;
						boss_shot.bullet[k].speed = 3 + t % 4;
						Enemy.se_flag[0] = 1;
					}
				}
			}
			for (int i = 0; i < 2400; i++) {

				if (t == 100)
					boss_shot.bullet[i].speed = 0;

			}

			for (int i = 0; i < 600; i++) {

				if (t == 150)
					boss_shot.bullet[i].speed = 6;

			}
			for (int i = 600; i < 1200; i++) {

				if (t == 200)
					boss_shot.bullet[i].speed = 6;

			}
			for (int i = 1200; i < 1800; i++) {

				if (t == 250)
					boss_shot.bullet[i].speed = 6;

			}
			for (int i = 1800; i < 2400; i++) {

				if (t == 300)
					boss_shot.bullet[i].speed = 6;

			}


			int num, t2 = boss_shot.counter;
			if (t2 == 0) num = 0;
			if (t % 200 == 0) {
				angle = BossAtan2();
				for (int i = 0; i < 2; i++) {
					for (t = 0; t < 3; t++) {
						for (int j = 0; j < 3; j++) {
							for (int s = 0; s < 50; s++) {
								if ((k = SerchBossShotE()) != -1) {
									boss_shot.bullet[k].color = i;//弾の色
									boss_shot.bullet[k].x = boss.x + adj_boss_bul_x[stage - 1];//座標
									boss_shot.bullet[k].y = boss.y + adj_boss_bul_y[stage - 1];
									boss_shot.bullet[k].type = 2;//弾の種類
									boss_shot.bullet[k].angle = angle + M_PI * 3 / 30 * s + M_PI * 2 / 60 * i;//角度
									boss_shot.bullet[k].flag = 1;
									boss_shot.bullet[k].counter = 0;
									boss_shot.bullet[k].speed = 1.8 - 0.2 * j + 0.1 * i;//スピード
									boss_shot.bullet[k].effect = 0;
									boss_shot.bullet[k].state = t;
								}
								Enemy.se_flag[0] = 1;
							}
						}
					}
				}
			}

			for (int i = 0; i < BOSS_BULLET_MAX; i++) {
				if (boss_shot.bullet[i].flag > 0) {
					int cnt = boss_shot.bullet[i].counter;
					int state = boss_shot.bullet[i].state;
					if (state % 10 == 0) {
						if (cnt > 90 && cnt <= 100)
							boss_shot.bullet[i].speed -= boss_shot.bullet[i].speed / 110;
					}
					if (state % 10 == 1) {
						if (cnt > 50)
							boss_shot.bullet[i].speed += boss_shot.bullet[i].speed / 45;
					}
					if (state % 10 == 2) {
						if (cnt > 65)
							boss_shot.bullet[i].speed += boss_shot.bullet[i].speed / 90;
					}
					if (10 <= state && state <= 12) {
						if (cnt > 15 && cnt <= 80)
							boss_shot.bullet[i].angle += boss_shot.bullet[i].base_angle[0];
					}
				}
			}


			break;
		}

		case 3: {
			t = boss_shot.counter % 600;
			int t2 = boss_shot.counter;
			double angle;
			static int tcnt, cnt, cnum;
			if (t == 0) {
				boss_shot.base_angle[0] = BossAtan2();
				cnt = 0;
				tcnt = 2;
			}
			if (0 < t && t < 720 && t % 30) {
				angle = BossAtan2();
				if (tcnt - 2 == cnt || tcnt - 1 == cnt) {
					if (tcnt - 1 == cnt) {
						boss_shot.base_angle[1] = boss_shot.base_angle[0] + M_PI * 2 / 20 * cnt * (cnum ? -1 : 1) - M_PI * 2 / 120 * 3; //レーザーの角度
						tcnt += 18;
					}
				}
				else {
					for (int i = 0; i < 10; i++) {
						if ((k = SerchBossShot()) != -1) {
							boss_shot.bullet[k].color = cnum ? 0 : 2;
							boss_shot.bullet[k].x = boss.dx + adj_boss_bul_x[stage - 1];//座標
							boss_shot.bullet[k].y = boss.dy + adj_boss_bul_y[stage - 1];
							boss_shot.bullet[k].type = 8;
							boss_shot.bullet[k].angle = boss_shot.base_angle[0] + M_PI * 10 / 20 * cnt * (cnum ? -1 : 1) + M_PI * 10 / 180 * i * (cnum ? -1 : 1);
							boss_shot.bullet[k].flag = 1;
							boss_shot.bullet[k].counter = 0;
							boss_shot.bullet[k].speed = 2;
							Enemy.se_flag[0] = 1;
						}
					}
				}
				cnt++;
			}
			for (int i = 0; i < BOSS_BULLET_MAX; i++) {
				if (boss_shot.bullet[i].flag>0) {
					int state = boss_shot.bullet[i].state;
					int cnt = boss_shot.bullet[i].counter;
					if (30 < cnt) {	//30～なら
						boss_shot.bullet[i].speed -= 0.5 / 80.0;	//80カウントかけて0.5ずつ減らす
					}
				}
			}
			if (t == 599) cnum = (++cnum) % 2;
			break;
		}
		case 4: {
			int i, j, k, n, t = (boss_shot.counter-120) % 420,
				t2 = boss_shot.counter;
			static int tm;
			double angle;
			//周期の最初にtmをセット
			if (boss_shot.counter == 0) {
				warp_flag = 1;
				boss.wx = BOSS_POS_X + adj_boss_x[stage - 1];//ボスの初期座標
				boss.wy = BOSS_POS_Y + adj_boss_y[stage - 1];//ボスの初期座標
			}
			else if (boss_shot.counter == 120) {
				boss.atk_flag = 1;
				boss.plus_range = 30;
			}
			if (boss.hp < boss.set_hp[4] * 1 / 3) {
				if (t >= 0 && (t - 170) % 35 == 0) {
					int div = ((t - 170) % 70 == 0) ? -1 : 1;
					angle = BossAtan2();//自機とボスとの成す角
					for (int i = 0; i < 2; i++) {//速度の違う2つの弾がある
						for (t = 0; t < 1; t++) {//1箇所から1つにわかれる
							for (int s = 0; s < 30; s++) {//1周30個
								if ((k = SerchBossShot()) != -1) {
									boss_shot.bullet[k].color = i + 4;//弾の色
									boss_shot.bullet[k].x = boss.x + adj_boss_bul_x[stage - 1];//座標
									boss_shot.bullet[k].y = boss.y + adj_boss_bul_y[stage - 1] + 30;
									boss_shot.bullet[k].type = 4;//弾の種類
									boss_shot.bullet[k].angle = angle + M_PI * 2 / 30 * s;//角度
									boss_shot.bullet[k].flag = 1;
									boss_shot.bullet[k].counter = 0;
									boss_shot.bullet[k].speed = 2 - 0.2 * i;//スピード
									boss_shot.bullet[k].effect = 0;
									boss_shot.bullet[k].state = 0;
									boss_shot.bullet[k].base_angle[0] = M_PI / 300 * div;
								}
							}
						}
						Enemy.se_flag[0] = 1;
					}
				}
				if (t >= 0 && t % 20 == 0) {
					angle = BossAtan2();
					for (int i = 0; i < 2; i++) {
						for (int j = 0; j < 60; j++) {
							if ((k = SerchBossShot()) != -1) {
								boss_shot.bullet[k].color = 0;
								boss_shot.bullet[k].x = boss.x + adj_boss_bul_x[stage - 1];//座標
								boss_shot.bullet[k].y = boss.y + adj_boss_bul_y[stage - 1] + 30;
								boss_shot.bullet[k].type = 7;
								boss_shot.bullet[k].angle = angle + t2 * 5 + M_PI * 2 / 30 * j;
								boss_shot.bullet[k].flag = 1;
								boss_shot.bullet[k].counter = 0;
								boss_shot.bullet[k].speed = 1;
								boss_shot.bullet[k].state = 0;
								Enemy.se_flag[0] = 1;
							}
						}
					}
				}
			}
			if (boss.set_hp[4] * 1 / 3 <= boss.hp && boss.hp < boss.set_hp[4] * 2 / 3) {
				if (t >= 0 && (t - 170) % 35 == 0) {
					int div = ((t - 170) % 70 == 0) ? -1 : 1;
					angle = BossAtan2();//自機とボスとの成す角
					for (int i = 0; i < 1; i++) {//速度の違う2つの弾がある
						for (t = 0; t < 1; t++) {//1箇所から1つにわかれる
							for (int s = 0; s < 30; s++) {//1周30個
								if ((k = SerchBossShot()) != -1) {
									boss_shot.bullet[k].color = i + 4;//弾の色
									boss_shot.bullet[k].x = boss.x + adj_boss_bul_x[stage - 1];//座標
									boss_shot.bullet[k].y = boss.y + adj_boss_bul_y[stage - 1] + 30;
									boss_shot.bullet[k].type = 4;//弾の種類
									boss_shot.bullet[k].angle = angle + M_PI * 2 / 30 * s;//角度
									boss_shot.bullet[k].flag = 1;
									boss_shot.bullet[k].counter = 0;
									boss_shot.bullet[k].speed = 2 - 0.2 * i;//スピード
									boss_shot.bullet[k].effect = 0;
									boss_shot.bullet[k].state = 0;
									boss_shot.bullet[k].base_angle[0] = M_PI / 300 * div;
								}
							}
						}
						Enemy.se_flag[0] = 1;
					}
				}
				if (t >= 0 && t % 20 == 0) {
					angle = BossAtan2();
					for (int i = 0; i < 2; i++) {
						for (int j = 0; j < 60; j++) {
							if ((k = SerchBossShot()) != -1) {
								boss_shot.bullet[k].color = 0;
								boss_shot.bullet[k].x = boss.x + adj_boss_bul_x[stage - 1];//座標
								boss_shot.bullet[k].y = boss.y + adj_boss_bul_y[stage - 1] + 30;
								boss_shot.bullet[k].type = 7;
								boss_shot.bullet[k].angle = angle + t2 * 5 + M_PI * 2 / 30 * j;
								boss_shot.bullet[k].flag = 1;
								boss_shot.bullet[k].counter = 0;
								boss_shot.bullet[k].speed = 1;
								boss_shot.bullet[k].state = 0;
								Enemy.se_flag[0] = 1;
							}
						}
					}
				}
			}
			if (boss.set_hp[4] * 2 / 3 < boss.hp) {
				if (t >= 0 && t % 20 == 0) {
					angle = BossAtan2();
					for (int i = 0; i < 2; i++) {
						for (int j = 0; j < 60; j++) {
							if ((k = SerchBossShot()) != -1) {
								boss_shot.bullet[k].color = 0;
								boss_shot.bullet[k].x = boss.x + adj_boss_bul_x[stage - 1];//座標
								boss_shot.bullet[k].y = boss.y + adj_boss_bul_y[stage - 1] + 30;
								boss_shot.bullet[k].type = 7;
								boss_shot.bullet[k].angle = angle + t2 * 5 + M_PI * 2 / 30 * j;
								boss_shot.bullet[k].flag = 1;
								boss_shot.bullet[k].counter = 0;
								boss_shot.bullet[k].speed = 1;
								boss_shot.bullet[k].state = 0;
								Enemy.se_flag[0] = 1;
							}
						}
					}
				}
				
			}
			break;
		}
		case 5:
			break;
		}
	}
}
