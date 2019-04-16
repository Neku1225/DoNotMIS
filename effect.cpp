#include "define.h"

//エフェクトの登録空き番号を探す
int Effect_c::SearchEffect() {
	for (int i = 0; i<EFFECT_MAX; i++) {
		if (effect[i].flag == 0)
			return i;
	}
	return -1;
}

//エフェクトを計算する
void Effect_c::CalcEffect() {
	for (int i = 0; i<EFFECT_MAX; i++) {
		if (effect[i].flag>0) {//エフェクトが登録されていたら
			switch (effect[i].type) {//エフェクトの種類によって分岐
			case 0://0番の処理
				effect[i].counter++;
				effect[i].r += 0.03;//エフェクトの大きさを段々大きくする
				if (effect[i].counter > 10) {//10カウント以上になったら
					effect[i].bright -= 25;//明るさを少なくする
				}
				if (effect[i].counter > 20) {//20カウント以上になったら
					effect[i].flag = 0;//消す
				}
				break;
			case 1:
				effect[i].r += 0.06;
				effect[i].counter++;
				if (effect[i].counter > 80) {
					effect[i].bright -= 20;
				}else if (effect[i].counter > 20 && effect[i].bright<115) {//10カウント以上になったら
					effect[i].bright += 10;
				}
				
				if (effect[i].counter >= 130) {
					effect[i].flag = 0;
				}
				/*
				//ボムのエフェクト
				   //座標計算
				effect[i].x += cos(effect[i].m_angle)*effect[i].speed;
				effect[i].y += sin(effect[i].m_angle)*effect[i].speed;
				//スピード計算
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
				//明るさと大きさ計算
				effect[i].r += 0.015;
				if (effect[i].counter < 51) {
					effect[i].bright += 5;
				}
				if (effect[i].counter >= 60) {
					effect[i].r += 0.04;
					effect[i].bright -= 255 / 30.0;
				}
				//カウントアップと消去計算
				effect[i].counter++;
				if (effect[i].counter >= 90) {
					effect[i].flag = 0;
				}
				*/
				break;
			case 2://ボムエフェクト（キャラ）
				   //座標計算
				effect[i].x += cos(effect[i].m_angle)*effect[i].speed;
				effect[i].y += sin(effect[i].m_angle)*effect[i].speed;
				//明るさ計算
				if (effect[i].counter < 51) {
					effect[i].bright += 4;
				}
				if (effect[i].counter > 130 - 51) {
					effect[i].bright -= 4;
				}
				//カウントアップと消去計算
				effect[i].counter++;
				if (effect[i].counter >= 130) {
					effect[i].flag = 0;
				}
				break;
			case 3://ボムのエフェクト（ライン）
				   //座標計算
				effect[i].x += cos(effect[i].m_angle)*effect[i].speed;
				effect[i].y += sin(effect[i].m_angle)*effect[i].speed;
				//明るさ計算
				if (effect[i].counter < 51) {
					effect[i].bright += 2;
				}
				if (effect[i].counter > 130 - 51) {
					effect[i].bright -= 2;
				}
				//カウントアップと消去計算
				effect[i].counter++;
				if (effect[i].counter >= 130) {
					effect[i].flag = 0;
				}
				break;
			case 4://喰らいボムエフェクト
				   //明るさ計算
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
				if (effect[i].counter > 10) {//10カウント以上になったら
					effect[i].bright -= 25;//明るさを少なくする
				}
				if (effect[i].counter > 20) {//20カウント以上になったら
					effect[i].flag = 0;//消す
				}
				break;
			case 6:
				effect[i].counter++;
				if (effect[i].counter > 10) {//10カウント以上になったら
					effect[i].bright -= 25;//明るさを少なくする
				}
				if (effect[i].counter > 20) {//20カウント以上になったら
					effect[i].flag = 0;//消す
				}
				break;
			default:
				printfDx("effect設定エラー\n");
				break;
			}
		}
	}
}

//ボムを登録
void  Effect_c::EnterBom() {
	int k;
	Player.SetBomFlag(1);
	Player.SetBomCounter(0);
	Player.SetBomType(0);
	Player.SetInvCount(1);//無敵に
	Enemy.se_flag[14] = 1;//ボム音鳴らす

	/*
	if ((k = SearchEffect()) != -1) {
		effect[k].flag = 1;
		effect[k].counter = 0;
		effect[k].type = 2;//ボムのキャラ・線のエフェクト
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

//消滅エフェクトの登録空き番号を探す
int Effect_c::SearchDelEffect() {
	for (int i = 0; i<100; i++) {
		if (del_effect[i].flag == 0)
			return i;
	}
	return -1;
}

//消滅エフェクトを登録する
void Effect_c::EnterDelEffect(int i) {
	int k = SearchDelEffect();
	if (k != -1) {
		del_effect[k].flag = 1;//フラグを立てる
		del_effect[k].counter = 0;
		del_effect[k].color = Enemy.GetBackColor(i);//敵の背景色を消滅色に設定する
		del_effect[k].x = Enemy.GetX(i);//敵の座標を消滅位置にセット
		del_effect[k].y = Enemy.GetY(i);
	}
}

void Effect_c::EnterBossDelEffect(int stage) {
	int k = SearchDelEffect();
	if (k != -1) {
		if (stage == 5) {
			del_effect[k].flag = 3;//フラグを立てる
			del_effect[k].counter = 0;
			del_effect[k].x = Boss.GetX();//敵の座標を消滅位置にセット
			del_effect[k].y = Boss.GetY();
		}
	else{
			del_effect[k].flag = 2;//フラグを立てる
			del_effect[k].counter = 0;
			del_effect[k].x = Boss.GetX();//敵の座標を消滅位置にセット
			del_effect[k].y = Boss.GetY();
		}
			}
}

//消滅エフェクトを計算・エフェクトを登録する
void Effect_c::CalcDelEffect() {
	int k;
	for (int i = 0; i<DEL_EFFECT_MAX; i++) {
		if (del_effect[i].flag > 0) {
			if ((k = SearchEffect()) != -1) {//空き番号検索
				switch (del_effect[i].flag) {
				case 1:
					if (del_effect[i].counter % 2 == 0) {// 1/30秒ずつセット

						memset(&effect[k], 0, sizeof(effect_t));//初期化
						effect[k].flag = 1;//フラグを立てる
						effect[k].bright = 255;//輝度を最大値に
						effect[k].angle = 0;
						effect[k].color = del_effect[i].counter / 12 % 5;
						effect[k].effect = 0;//1は光エフェクト。光エフェクトにセットする
						effect[k].img = img_del_effect[effect[k].color];//消滅する画像をセット
						effect[k].type = 0;//エフェクトの種類は0番(雑魚の消滅エフェクトは0とする)
						effect[k].x = del_effect[i].x;//座標をセット
						effect[k].y = del_effect[i].y;
						effect[k].speed = 0;
					}
					if (del_effect[i].counter > 60) {
						del_effect[i].flag = 0;
					}
					break;
				case 2:
					if (del_effect[i].counter % 9 == 0) {

						memset(&effect[k], 0, sizeof(effect_t));//初期化
						effect[k].flag = 1;
						effect[k].bright = 255;//輝度を最大値に
						effect[k].angle = 0;
						effect[k].color = del_effect[i].counter / 9;
						effect[k].effect = 0;
						effect[k].img = boss_del_effect[effect[k].color];//消滅する画像をセット
						effect[k].type = 5;//エフェクトの種類は0番(雑魚の消滅エフェクトは0とする)
						effect[k].x = del_effect[i].x;//座標をセット
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
						memset(&effect[k], 0, sizeof(effect_t));//初期化
						effect[k].flag = 1;//フラグを立てる
						effect[k].bright = 255;
						effect[k].angle = 0;
						effect[k].color = del_effect[i].counter / 9;
						effect[k].effect = 0;
						effect[k].img = boss_del_effect[effect[k].color];//消滅する画像をセット
						effect[k].type = 6;//エフェクトの種類は0番(雑魚の消滅エフェクトは0とする)
						effect[k].x = del_effect[i].x;//座標をセット
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

//ボム計算
void Effect_c::BomCalc() {
	int n, k, shot_angle[4] = { 0,M_PI,M_PI / 2,M_PI*1.5 };//4発エフェクトが飛ぶ角度
	if ((Player.GetFlag() == 0 || Player.GetFlag() == 1) && Player.GetBomFlag() == 0) {//ボムがオフなら
		if (Player.GetCoolFlag() == false) {
			if ((Controller.k_Get(Config.k_bom) == 1 || Controller.g_Get(Config.g_bom) == 1) && Player.GetEnergy() > 1200) {//エネルギーが十分な状態でボムボタンが押されたら
				Player.SetEnergyMax(Player.GetEnergyMax() - 1200);
				Player.SetEnergy(Player.GetEnergy() - 1200);
				EnterBom();
				if (Player.GetFlag() == 1) {
					Player.SetFlag(0);
				}
			}
		}
	}
	if (Player.GetBomFlag() == 1) {//ボムが登録されていたら
		if (Player.GetBomCounter() % 10 == 0) {//1/6秒に１回
			n = (Player.GetBomCounter() / 10);
			if (n<4 && (k = SearchEffect()) != -1) {
				if (n == 0) {
					bom_x = Player.GetX();
					bom_y = Player.GetY();
				}
			    effect[k].x = bom_x;//座標
			    effect[k].y = bom_y;
				effect[k].flag = 1;
				effect[k].counter = 0;
				effect[k].type = 1;//エフェクト番号１：ボムのエフェクト
				effect[k].bright = 5;
				effect[k].angle = Enemy.Rang(M_PI);//画像の向きはランダム
				effect[k].m_angle = shot_angle[n] - M_PI / 4;//飛ぶ方向
				effect[k].speed = 0;//スピード
				effect[k].r = 0.5;//大きさ
				effect[k].effect = 2;//αブレンド
				effect[k].img = bom_image[0];//画像		
			}
		}
		Player.SetBomCounter(Player.GetBomCounter()+1);
		if (Player.GetBomCounter() < 40) {
			bright_set.bright = 255 - Player.GetBomCounter() * 5;//画面の明るさ設定(暗く)
		}
		if (Player.GetBomCounter() > 90) {
			bright_set.bright = 255 - 40 * 5 + (Player.GetBomCounter() - 90) * 5;//画面の明るさ設定(明るく)
		}
		if (Player.GetBomCounter()>130) {
			Player.SetBomFlag(0);
			bright_set.bright = 255;
		}
	}
}

//ドガーンとゆれる画面の処理
void Effect_c::DnCalc() {
	if (dn.flag == 1) {
		dn.x = (int)Enemy.Rang(dn.size);
		dn.y = (int)Enemy.Rang(dn.size);
		dn.counter++;
		if (dn.counter>dn.time) {//指定された時間がたつと終わる
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
				effect[k].type = 4;//喰らいボムエフェクト
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
			if (effect[i].effect == 1) {//エフェクトが光エフェクトなら
				SetDrawBlendMode(DX_BLENDMODE_ADD, effect[i].bright);
			}
				if (effect[i].effect == 2){//エフェクトがαエフェクトなら
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
	Draw(0);//敵が死ぬエフェクト
	Draw(1);//ボムのエフェクト
  //Draw(4);//喰らいボムのエフェクト
	Draw(5);
	Draw(6);
}

void Effect_c::Loop() {
	DnCalc();//ゆれる画面の処理
	CalcDelEffect();//消滅エフェクトの計算
	CalcEffect();//エフェクトの計算
	BomCalc();//ボム計算
	//EnterDyingBomEffect();

	DrawEffect();//エフェクトをまとめて描画
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