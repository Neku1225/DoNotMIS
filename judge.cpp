#include "define.h"

//当たり判定
//ショットの座標:1  当たりを判定する物体:2
int Judge_c::OutJudge(double x1, double y1, double x2, double y2,
	double range1, double range2, double speed1, double angle1) {
	int j;
	double x = x1 - x2;//ショットと物体の距離
	double y = y1 - y2;
	//物体の当たり判定とショットの当たり判定の合計範囲
	double r = range1 + range2;
	//中間を計算する必要があれば
	if (speed1>r) {
		//１フレーム前にいた位置を格納する
		double pre_x = x1 + cos(angle1 + M_PI)*speed1;
		double pre_y = y1 + sin(angle1 + M_PI)*speed1;
		double px, py;
		for (j = 0; j<speed1 / r; j++) {//進んだ分÷当たり判定分ループ
			px = pre_x - x2;
			py = pre_y - y2;
			if (px*px + py*py<r*r)
				return 1;
			pre_x += cos(angle1)*r;
			pre_y += sin(angle1)*r;
		}
	}
	if (x*x + y*y < r*r) {//当たり判定内なら
		return 1;//当たり
	}
	return 0;
}

//敵と自機ショットが当たったかどうかを判定する
bool Judge_c::JudgePS(int s, int t) {
	if (Player.GetShotCounter(s)>0) {//ショットの軌道が１度でも計算されていたら
		if (OutJudge(Player.GetShotX(s), Player.GetShotY(s), Enemy.GetX(t), Enemy.GetY(t),
			Player.GetShotRange(Player.GetShotType(s)), Enemy.GetRange(Enemy.GetType(t)),
			Player.GetShotSpeed(s), Player.GetShotAngle(s))==1) {
			return true;
		}
	}
	return false;
}

//ボスと自機ショットが当たったかどうかを判定する
bool Judge_c::JudgePSBoss(int stage,int s) {
	if (Player.GetShotCounter(s)>0) {//ショットの軌道が１度でも計算されていたら
		if (OutJudge(Player.GetShotX(s), Player.GetShotY(s), Boss.GetX(), Boss.GetY(),
			Player.GetShotRange(Player.GetShotType(s)), Boss.GetRange(stage)+Boss.GetPlusRange(), 
			Player.GetShotSpeed(s), Player.GetShotAngle(s))==1) {
			return true;
		}
	}
	return false;
}

//自機と敵ショットが当たったかどうかを判定する
bool Judge_c::JudgeES(int s, int t,int plus_range) {
	if (Enemy.GetBulletCount(s, t)>0) {//ショットの軌道が１度でも計算されていたら
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

//自機とボスショットが当たったかどうかを判定する
bool Judge_c::JudgeBS(int s,int plus_range) {
	if (Boss.GetBulletCount(s)>0) {//ショットの軌道が１度でも計算されていたら
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



//敵が死ぬかどうかの決定
void  Judge_c::EnemyDeathJudge(int t) {
	Enemy.se_flag[8] = 1;//敵に当たった音
	if (Enemy.GetHp(t) < 0) {//敵のHPが０未満になったら
		Enemy.SetFlag(t, false);//敵を消滅させる
		Enemy.se_flag[2] = 1;//敵のピチュり音
		Effect.EnterDelEffect(t);
		Control.AddScore(Enemy.GetHpMax(t) *(0.75 + Control.GetState() / 4) / 10 * 10);
		for (int i = 0; i < SHOT_MAX; i++) {//敵総数分
			if (Enemy.GetShotFlag(i) != 0) {//登録されている弾幕データがあれば
				if (t == Enemy.GetShotNum(i)) {//その敵が登録した弾幕があれば
					Enemy.SetShotFlag(i, 2);//それ以上弾幕を続けないフラグを立てる
					break;
				}
			}
		}
	}
}

//自機ショットと敵との処理
void Judge_c::JudgeHitPS(int stage) {
	for (int s = 0; s < SHOT_MAX; s++) {//自機ショット総数
		if (Player.GetShotFlag(s) == true) {
			for (int t = 0; t < ENEMY_MAX; t++) {//敵総数
				if (Enemy.GetFlag(t) == true) {
					if (JudgePS(s, t) == true) {//自機ショットと敵が当たっていれば
						Player.SetShotFlag(s, false);//その自機ショットを消す
						Enemy.MinusHp(t, Player.GetShotAtk(s));//弾の持つパワー分HPを減らす
						break;
					}
				}
			}
			//ボスが出現していて、描画しないフラグがオフで、ショット中なら
			if (Boss.GetFlag() == 1 && Boss.GetGraphFlag() == 0 ) {
				if (JudgePSBoss(stage, s) == true) {
					Player.SetShotFlag(s, false);//その自機ショットを消す
					Boss.MinusHp(Player.GetShotAtk(s));
				}
			}
		}
	}

	/*
	//レーザーを撃っているとき
	if (Player.GetCoolFlag() == false) {
		if (Player.GetShotMode() == laser && (Controller.k_Get(Config.k_shot) > 0 || Controller.g_Get(Config.g_shot) > 0)) {
			for (int t = 0; t < ENEMY_MAX; t++) {//敵総数
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

//敵ショットと自機との処理
void Judge_c::JudgeHitES(int stage) {
	for (int s = 0; s<SHOT_MAX; s++) {//敵ショット総数
		if (Enemy.GetShotFlag(s)>0) {//そのショットが登録されていたら
			for (int t = 0; t<SHOT_BULLET_MAX; t++) {//弾総数
				if (Enemy.GetBulletFlag(s, t) == 1) {//弾が登録されていたら
					if (Player.GetFlag() == 2 && Player.GetCount() == 1) {//無敵になった瞬間
							Enemy.SetBulletFlag(s, t, 0);//弾をオフ
					}else if (JudgeES(s, t,0) == true) {//自機にその弾が接触していたら
						Enemy.SetBulletFlag(s, t, 0);//弾をオフ
						if (Player.GetFlag() == 3) {
							Control.AddScore(100);
						}else if (Player.GetFlag() == 0 && Player.GetInvCount() == 0) {//ステータスが通常で、無敵じゃなかったら
							Player.SetFlag(1);     //1:喰らいボム受付中　2:喰らいボム受付終了、死亡確定
							Player.SetCount(0);
						}
					}
				}
			}
		}
	}
	//ボスのショット
	if (Boss.GetFlag() > 0) {//そのショットが登録されていたら
		for (int t = 0; t < BOSS_BULLET_MAX; t++) {//弾総数
			if (Boss.GetBulletFlag(t) > 0) {//弾が登録されていたら
				if (Player.GetFlag() == 2 && Player.GetCount() == 1) {//無敵になった瞬間
					if (Boss.GetBulletFlag(t) != 10) {
						Boss.SetBulletFlag(t, 0);//弾をオフ
					}
				}
				else if (JudgeBS(t, 0) == true && Boss.GetBulletFlag(t) != 10) {//自機にその弾が接触していたら
					Boss.SetBulletFlag(t, 0);//弾をオフ
					if (Player.GetFlag() == 3) {
						Control.AddScore(100);
					}else if (Player.GetFlag() == 0 && Player.GetInvCount() == 0) {
						Player.SetCount(0);
						Player.SetFlag(1);
					}
				}
			}
		}
	//ボスと接触したとき
		if (OutJudge(Boss.GetX(), Boss.GetY(), Player.GetX(), Player.GetY(), Boss.GetRange(stage), P_RANGE, Boss.GetBossSpeed(), Boss.GetBossAngle() == 1)){
			if (Player.GetFlag() == 0 && Player.GetInvCount() == 0) {//ステータスが通常で、無敵じゃなかったら
				Player.SetFlag(1);     //1:喰らいボム受付中　2:喰らいボム受付終了、死亡確定
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
	for (int s = 0; s<ENEMY_MAX; s++) {//敵総数
		if (Enemy.GetFlag(s) == true) {//その敵がいれば
			if (Enemy.GetX(s) > FIELD_X && Enemy.GetX(s) < FIELD_X + FIELD_MAX_X) {
				if (Enemy.GetY(s) > FIELD_Y && Enemy.GetY(s) < FIELD_Y + FIELD_MAX_Y) {
					Enemy.MinusHp(s, 20);//ダメージを与える
				}
			}
		}
	}
	//ボスがいて、描画しないフラグがオフで、ショット中なら
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
			Boss.MinusHp(40*rate);//喰らわす
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

