#include "define.h"

//渡された-ang〜angまでのランダムな角度を返す
double Enemy_obj::Rang(double ang){
	return (-ang + ang * 2 * GetRand(10000) / 10000.0);
}

//敵のパターン別での移動制御
void Enemy_obj::Move(int i){
	switch (enemy[i].pattern){
	case 0:
		if (enemy[i].counter < 60){
			enemy[i].vy = 2;
		}
		if (enemy[i].counter == 60){
			enemy[i].vy = 0;
		}
		if (enemy[i].counter > 60 + enemy[i].wait){
			enemy[i].vy = -2;
		}
		break;
	case 1:
		if (enemy[i].counter == 0){
			enemy[i].vy = 3;//下がってくる
		}
		if (enemy[i].counter == 40){
			enemy[i].vy = 0;//止まる
		}
		if (enemy[i].counter == 40 + enemy[i].wait){//登録された時間だけ停滞して
			enemy[i].vx = -1;//左へ
			enemy[i].vy = 2;//下がっていく
			enemy[i].direction = 0;//左向きセット
		}
		break;
	case 2:
		if (enemy[i].counter == 0){
			enemy[i].vy = 3;//下がってくる
		}
		if (enemy[i].counter == 40){
			enemy[i].vy = 0;//止まる
		}
		if (enemy[i].counter == 40 + enemy[i].wait){//登録された時間だけ停滞して
			enemy[i].vx = 1;//右へ
			enemy[i].vy = 2;//下がっていく
			enemy[i].direction = 2;//右向きセット
		}
		break;
	case 3:
		if (enemy[i].counter == 0){
			enemy[i].vy = 5;//下がってくる
		}
		if (enemy[i].counter == 30){//途中で左向きに
			enemy[i].direction = 0;
		}
		if (enemy[i].counter<100){
			enemy[i].vx -= 5 / 100.0;//左向き加速
			enemy[i].vy -= 5 / 100.0;//減速
		}
		break;
	case 4:
		if (enemy[i].counter == 0){
			enemy[i].vy = 5;//下がってくる
		}
		if (enemy[i].counter == 30){//途中で右向きに
			enemy[i].direction = 2;
		}
		if (enemy[i].counter<100){
			enemy[i].vx += 5 / 100.0;//右向き加速
			enemy[i].vy -= 5 / 100.0;//減速
		}
		break;
	case 5:
		if (enemy[i].counter == 0){
			enemy[i].vx -= 1;
			enemy[i].vy = 2;
			enemy[i].direction = 0;
		}
		break;
	case 6:
		if (enemy[i].counter == 0){
			enemy[i].vx += 1;
			enemy[i].vy = 2;
			enemy[i].direction = 2;
		}
		break;
	case 7:
		if (enemy[i].counter == enemy[i].wait){//登録された時間だけ停滞して
			enemy[i].vx = -0.7;//左へ
			enemy[i].vy = -0.3;//上がっていく
			enemy[i].direction = 0;//左向き
		}
		break;
	case 8:
		if (enemy[i].counter == enemy[i].wait){//登録された時間だけ停滞して
			enemy[i].vx = +0.7;//右へ
			enemy[i].vy = -0.3;//上がっていく
			enemy[i].direction = 2;//右向き
		}
		break;
	case 9:
		if (enemy[i].counter == enemy[i].wait){//登録された時間だけ停滞して
			enemy[i].vy = -1;//上がっていく
	}
		break;
	case 10:
		if (enemy[i].counter == 0) enemy[i].vy = 4;//下がってくる
		if (enemy[i].counter == 40)enemy[i].vy = 0;//止まる
		if (enemy[i].counter >= 40){
			if (enemy[i].counter % 60 == 0){
				int r = cos(enemy[i].angle)< 0 ? 0 : 1;
				enemy[i].speed = 6 + Rang(2);
				enemy[i].angle = Rang(M_PI / 4) + M_PI*r;
				enemy[i].direction = 2 - 2 * r;
			}
			enemy[i].speed *= 0.95;
		}
		if (enemy[i].counter >= 40 + enemy[i].wait){
			enemy[i].vy -= 0.05;
		}
		break;
	case 11:
		if (enemy[i].counter == 0) {
			enemy[i].vx = -1.5;//左へ
			enemy[i].vy = -3;//上がっていく
			enemy[i].direction = 0;//左向き
		}
		break;
	case 12:
		if (enemy[i].counter == 0) {
			enemy[i].vx = 1.5;//右へ
			enemy[i].vy = -3;//上がっていく
			enemy[i].direction = 2;//右向き
		}
		break;
	case 13:
		if (enemy[i].counter == 0) {
			enemy[i].vx = -3;//左へ
			enemy[i].direction = 0;//左向き
		}
		break;
	case 14:
		if (enemy[i].counter == 0) {
			enemy[i].vx = 3;//右へ
			enemy[i].direction = 2;//右向き
		}
		break;
	case 15://左下左上
		if (enemy[i].counter < 20) {
			enemy[i].vx -= 0.3;
			enemy[i].vy += 0.5;
			enemy[i].direction = 0;
		}
		if (enemy[i].counter == 20) {
			enemy[i].vx = 0;
			enemy[i].vy = 0;
		}
		if (enemy[i].counter > 20 + enemy[i].wait) {//登録された時間だけ停滞して
			enemy[i].vx -= 0.5;
			enemy[i].vy -= 0.5;//上がっていく
		}
		break;
	case 16://右下右上
		if (enemy[i].counter < 20) {
			enemy[i].vx += 0.3;
			enemy[i].vy += 0.5;
			enemy[i].direction = 2;
		}
		if (enemy[i].counter == 20) {
			enemy[i].vx = 0;
			enemy[i].vy = 0;
		}
		if (enemy[i].counter > 20 + enemy[i].wait) {//登録された時間だけ停滞して
			enemy[i].vx += 0.5;
			enemy[i].vy -= 0.5;//上がっていく
		}
		break;
	case 17://右下
		if (enemy[i].counter == 0) {
			enemy[i].vx += 0.8;
			enemy[i].vy += 0.9;
			enemy[i].direction = 2;
		}
		break;
	case 18://左下
		if (enemy[i].counter == 0) {
			enemy[i].vx -= 0.8;
			enemy[i].vy += 0.9;
			enemy[i].direction = 0;
		}
		break;
	case 19:
		if (enemy[i].counter == 0) {
			enemy[i].vy = 5;//下がってくる
		}
		if (enemy[i].counter == 30) {//途中で左向きに
			enemy[i].direction = 0;
		}
		if (enemy[i].counter<100) {
			enemy[i].vx -= 2.5 / 100.0;//左向き加速
			enemy[i].vy -= 5 / 100.0;//減速
		}
		break;
	case 20:
		if (enemy[i].counter == 0) {
			enemy[i].vy = 5;//下がってくる
		}
		if (enemy[i].counter == 30) {//途中で右向きに
			enemy[i].direction = 2;
		}
		if (enemy[i].counter<100) {
			enemy[i].vx += 2.5 / 100.0;//右向き加速
			enemy[i].vy -= 5 / 100.0;//減速
		}
		break;
	}
}