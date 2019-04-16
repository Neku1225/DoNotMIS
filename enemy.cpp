#include "define.h"

//敵の情報の初期化
void Enemy_obj::Initialize() {
	memset(enemy, 0, sizeof(enemy_t)*ENEMY_MAX);//敵データの初期化
	memset(enemy_order, 0, sizeof(order_t)*ENEMY_ORDER_MAX);
	memset(shot, 0, sizeof(shot_t)*SHOT_MAX);
}

//空いている敵番号を検索
int Enemy_obj::EnemyNumSearch() {
	for (int i = 0; i<ENEMY_MAX; i++) {//フラグのたって無いenemyを探す
		if (enemy[i].flag == false) {
			return i;//使用可能番号を返す
		}
	}
	return -1;//全部埋まっていたらエラーを返す
}


//敵の行動を登録・制御する関数
void Enemy_obj::EnemyEnter() {
	int i;
	if (Boss.GetBossFlag() != 0) {
		return;
	}
	for (int k = 0; k<ENEMY_ORDER_MAX; k++) {
		if (enemy_order[k].counter == Control.g_count) {//現在の瞬間がオーダーの瞬間なら
			if ((i = EnemyNumSearch()) != -1) {//エラー(=-1)が出てないとき
				enemy[i].flag = true;//フラグ
				enemy[i].counter = 0;//カウンタ
				enemy[i].pattern = enemy_order[k].pattern;//移動パターン
				enemy[i].direction = 1;//向き
				enemy[i].type = enemy_order[k].type;//敵の種類
				enemy[i].back_color = GetRand(4);
				enemy[i].x = enemy_order[k].x;//座標
				enemy[i].y = enemy_order[k].y;
				enemy[i].speed = enemy_order[k].speed;//スピード
				enemy[i].bl_time = enemy_order[k].bl_time;//弾幕の開始時間
				enemy[i].bl_type = enemy_order[k].bl_type;//弾幕の種類
				enemy[i].bl_type2 = enemy_order[k].bl_type2;//弾の種類
				enemy[i].color = enemy_order[k].color;//色
				enemy[i].wait = enemy_order[k].wait;//停滞時間
				enemy[i].hp = enemy_order[k].hp;//体力
				enemy[i].hp_max = enemy[i].hp;//体力最大値
				enemy[i].vx = 0;//水平成分の速度
				enemy[i].vy = 0;//鉛直成分の速度
				enemy[i].angle = 0;//角度
				enemy[i].death_count = 1;//0だと初期化の値と被ってバグの原因になりかねない
				for (int j = 0; j<6; j++)
					enemy[i].item_n[j] = enemy_order[k].item_n[j];//落とすアイテム
			}
		}
	}
}


//敵の行動制御
void Enemy_obj::EnemyAct() {
	for (int i = 0; i<ENEMY_MAX; i++) {
		if (enemy[i].flag == true) {//その敵のフラグがオンになってたら
			Move(i);
			enemy[i].x += cos(enemy[i].angle)*enemy[i].speed;
			enemy[i].y += sin(enemy[i].angle)*enemy[i].speed;
			enemy[i].x += enemy[i].vx;
			enemy[i].y += enemy[i].vy;
			enemy[i].counter++;
			enemy[i].img = enemy[i].direction * 4 + (enemy[i].counter % 16) / 4;
			//敵が画面から外れたら消す
			if (enemy[i].x < -30 || FIELD_MAX_X + FIELD_X + 30 < enemy[i].x || enemy[i].y < -30 || FIELD_Y + FIELD_MAX_Y + 30 < enemy[i].y) {
				enemy[i].flag = false;
			}
			if (enemy[i].bl_time == enemy[i].counter) {
				EnterShot(i);
			}
		}
	}
}

void Enemy_obj::DrawEnemy() {
	for (int i = 0; i<ENEMY_MAX; i++) {
		if (enemy[i].flag == true) {
			DrawRotaGraphF((float)enemy[i].x, (float)enemy[i].y , 1.0f, 0.0f, ene_image[enemy[i].type][enemy[i].img], TRUE);
		}
		else if(enemy[i].death_count<=60){
			DrawRotaGraphF((float)enemy[i].x, (float)enemy[i].y,(float)(60 - enemy[i].death_count )/ 60, enemy[i].death_count*M_PI / 30, ene_image[enemy[i].type][enemy[i].img], TRUE);
			enemy[i].death_count++;
		}
	}
}


void::Enemy_obj::LoadEneBul(int stage){

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 12; j++) {
			DeleteGraph(ene_image[i][j]);
		}
	}
	for (int i = 0; i < 10; i++) {
		DeleteGraph(bul_image[1][i]);
		DeleteGraph(bul_image[5][i]);
		DeleteGraph(bul_image[7][i]);
		DeleteGraph(bul_image[9][i]);
	}

	//ステージ固有の敵と弾を読み込む
	switch(stage){
	case 1://南
		LoadDivGraph("material/img/enemy/SS.png", 12, 4, 3, 64, 64, ene_image[0]);
		LoadDivGraph("material/img/enemy/S1.png", 12, 4, 3, 64, 64, ene_image[1]);
		LoadDivGraph("material/img/enemy/S2.png", 12, 4, 3, 64, 64, ene_image[2]);

		LoadDivGraph("material/img/bullet/b1S.png", 1, 1, 1, 22, 22, bul_image[1]);
		LoadDivGraph("material/img/bullet/b5C.png", 4, 4, 1, 14, 16, bul_image[5]);
		LoadDivGraph("material/img/bullet/b7C.png", 9, 9, 1, 16, 16, bul_image[7]);
		LoadDivGraph("material/img/bullet/b9S.png", 1, 1, 1, 13, 19, bul_image[9]);
		break;
	case 2://東
		LoadDivGraph("material/img/enemy/SE.png", 12, 4, 3, 64, 64, ene_image[0]);
		LoadDivGraph("material/img/enemy/E1.png", 12, 4, 3, 64, 64, ene_image[1]);
		LoadDivGraph("material/img/enemy/E2.png", 12, 4, 3, 64, 64, ene_image[2]);

		LoadDivGraph("material/img/bullet/b1C.png", 6, 6, 1, 22, 22, bul_image[1]);
		LoadDivGraph("material/img/bullet/b5E.png", 3, 3, 1, 14, 16, bul_image[5]);
		LoadDivGraph("material/img/bullet/b7C.png", 9, 9, 1, 16, 16, bul_image[7]);
		LoadDivGraph("material/img/bullet/b9C.png", 3, 3, 1, 13, 19, bul_image[9]);
		break;
	case 3://西
		LoadDivGraph("material/img/enemy/SW.png", 12, 4, 3, 64, 64, ene_image[0]);
		LoadDivGraph("material/img/enemy/W1.png", 12, 4, 3, 64, 64, ene_image[1]);
		LoadDivGraph("material/img/enemy/W2.png", 12, 4, 3, 64, 64, ene_image[2]);

		LoadDivGraph("material/img/bullet/b1C.png", 6, 6, 1, 22, 22, bul_image[1]);
		LoadDivGraph("material/img/bullet/b5W.png", 4, 4, 1, 14, 16, bul_image[5]);
		LoadDivGraph("material/img/bullet/b7C.png", 9, 9, 1, 16, 16, bul_image[7]);
		LoadDivGraph("material/img/bullet/b9C.png", 3, 3, 1, 14, 16, bul_image[9]);
		break;
	case 4://北
		LoadDivGraph("material/img/enemy/SN.png", 12, 4, 3, 64, 64, ene_image[0]);
		LoadDivGraph("material/img/enemy/N1.png", 12, 4, 3, 64, 64, ene_image[1]);
		LoadDivGraph("material/img/enemy/N2.png", 12, 4, 3, 64, 64, ene_image[2]);

		LoadDivGraph("material/img/bullet/b1C.png", 6, 6, 1, 22, 22, bul_image[1]);
		LoadDivGraph("material/img/bullet/b5C.png", 4, 4, 1, 14, 16, bul_image[5]);
		LoadDivGraph("material/img/bullet/b7N.png", 1, 1, 1, 16, 16, bul_image[7]);
		LoadDivGraph("material/img/bullet/b9C.png", 3, 3, 1, 14, 16, bul_image[9]);
		break;
	case 5:
		LoadDivGraph("material/img/bullet/b1C.png", 6, 6, 1, 22, 22, bul_image[1]);
		LoadDivGraph("material/img/bullet/b5C.png", 4, 4, 1, 14, 16, bul_image[5]);
		LoadDivGraph("material/img/bullet/b7C.png", 9, 9, 1, 16, 16, bul_image[7]);
		LoadDivGraph("material/img/bullet/b9C.png", 3, 3, 1, 14, 16, bul_image[9]);
		break;
	}
}

void Enemy_obj::StartIni() {

	//弾画像のファイルを読み込む
	LoadDivGraph("material/img/bullet/b0C.png", 5, 5, 1, 77,77, bul_image[0]);
	LoadDivGraph("material/img/bullet/b1C.png", 6, 6, 1, 22, 22, bul_image[1]);
	LoadDivGraph("material/img/bullet/b2C.png", 10, 10, 1, 5, 120, bul_image[2]);
	LoadDivGraph("material/img/bullet/b3C.png", 5, 5, 1, 19, 34, bul_image[3]);
	LoadDivGraph("material/img/bullet/b4C.png", 10, 10, 1, 38, 38, bul_image[4]);
	LoadDivGraph("material/img/bullet/b5C.png", 4, 4, 1, 14, 16, bul_image[5]);
	LoadDivGraph("material/img/bullet/b6C.png", 3, 3, 1, 14, 18, bul_image[6]);
	LoadDivGraph("material/img/bullet/b7C.png", 9, 9, 1, 16, 16, bul_image[7]);
	LoadDivGraph("material/img/bullet/b8C.png", 10, 10, 1, 12, 18, bul_image[8]);
	LoadDivGraph("material/img/bullet/b9C.png", 3, 3, 1, 13, 19, bul_image[9]);

	//例：弾0は76x76ピクセルで、5色あり、当たり範囲17ピクセル
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
	}

void Enemy_obj::Load_story(char level,int stage) {
	int n, num, i, fp;
	char fname[32];
	sprintf_s(fname, "material/csv/story%c%d.csv",level,stage);
	int input[64];
	char inputc[64];

	fp = FileRead_open(fname);//ファイル読み込み
	if (fp == NULL) {
		printfDx("read error\n");
		return;
	}
	for (i = 0; i < 2; i++)//最初の2行読み飛ばす
		while (FileRead_getc(fp) != '\n');

	n = 0, num = 0;
	while (1) {
		for (i = 0; i<64; i++) {
			inputc[i] = input[i] = FileRead_getc(fp);//1文字取得する
			if (inputc[i] == '/') {//スラッシュがあれば
				while (FileRead_getc(fp) != '\n');//改行までループ
				i = -1;//カウンタを最初に戻して
				continue;
			}
			if (input[i] == ',' || input[i] == '\n') {//カンマか改行なら
				inputc[i] = '\0';//そこまでを文字列とし
				break;
			}
			if (input[i] == EOF) {//ファイルの終わりなら
				goto EXFILE;//終了
			}
		}
		switch (num) {
		case 0: enemy_order[n].counter = atoi(inputc); break;
		case 1: enemy_order[n].pattern = atoi(inputc); break;
		case 2: enemy_order[n].type = atoi(inputc); break;
		case 3: enemy_order[n].x = atof(inputc); break;
		case 4: enemy_order[n].y = atof(inputc); break;
		case 5: enemy_order[n].speed = atof(inputc); break;
		case 6: enemy_order[n].bl_time = atoi(inputc); break;
		case 7: enemy_order[n].bl_type = atoi(inputc); break;
		case 8: enemy_order[n].color = atoi(inputc); break;
		case 9: enemy_order[n].hp = atoi(inputc); break;
		case 10:enemy_order[n].bl_type2 = atoi(inputc); break;
		case 11:enemy_order[n].wait = atoi(inputc); break;
		case 12:enemy_order[n].item_n[0] = atoi(inputc); break;
		case 13:enemy_order[n].item_n[1] = atoi(inputc); break;
		case 14:enemy_order[n].item_n[2] = atoi(inputc); break;
		case 15:enemy_order[n].item_n[3] = atoi(inputc); break;
		case 16:enemy_order[n].item_n[4] = atoi(inputc); break;
		case 17:enemy_order[n].item_n[5] = atoi(inputc); break;
		}
		num++;
		if (num == 18) {
			num = 0;
			n++;
		}
	}
EXFILE:
	FileRead_close(fp);
}



void Enemy_obj::Loop() {
	EnemyEnter();
	EnemyAct();
	DrawEnemy();
	DrawBullet();
	ShotMain();
}

int Enemy_obj::GetBackColor(int i){
	return enemy[i].back_color;
}

double Enemy_obj::GetX(int i) {
	return enemy[i].x;
}

double Enemy_obj::GetY(int i) {
	return enemy[i].y;
}

int Enemy_obj::GetRange(int i) {
	return enemy_range[i];
}

int Enemy_obj::GetType(int i) {
	return enemy[i].type;
}

bool Enemy_obj::GetFlag(int i) {
	return enemy[i].flag;
}

void Enemy_obj::SetFlag(int i, bool setflag) {
	enemy[i].flag = setflag;
}

int Enemy_obj::GetHp(int i) {
	return enemy[i].hp;
}

int Enemy_obj::GetHpMax(int i) {
	return enemy[i].hp_max;
}

void Enemy_obj::MinusHp(int i, int minushp) {
	enemy[i].hp -= minushp;
	Judge.EnemyDeathJudge(i);//敵が死ぬかどうかを決める

}

int Enemy_obj::GetShotFlag(int i) {
	return shot[i].flag;
}

void Enemy_obj::SetShotFlag(int i, int setflag) {
	shot[i].flag = setflag;
}

int Enemy_obj::GetShotNum(int i) {
	return shot[i].num;
}

int Enemy_obj::GetBulletCount(int i,int j) {
	return shot[i].bullet[j].counter;
}

int Enemy_obj::GetBulletType(int i, int j) {
	return shot[i].bullet[j].type;
}

double Enemy_obj::GetBulletX(int i, int j) {
	return shot[i].bullet[j].x;
}

double Enemy_obj::GetBulletY(int i, int j) {
	return shot[i].bullet[j].y;
}

double Enemy_obj::GetBulletSpeed(int i, int j) {
	return shot[i].bullet[j].speed;
}

double Enemy_obj::GetBulletAngle(int i, int j) {
	return shot[i].bullet[j].angle;
}

int Enemy_obj::GetBulletFlag(int i, int j) {
	return shot[i].bullet[j].flag;
}

void Enemy_obj::SetBulletFlag(int i, int j,int setflag) {
	shot[i].bullet[j].flag = setflag;
}

int Enemy_obj::GetBulletRange(int i) {
	return bullet_info[i].range;
}

int Enemy_obj::GetEneBulType(int i) {
	return enemy[i].bl_type;
}

