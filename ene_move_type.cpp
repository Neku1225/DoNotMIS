#include "define.h"

//�n���ꂽ-ang�`ang�܂ł̃����_���Ȋp�x��Ԃ�
double Enemy_obj::Rang(double ang){
	return (-ang + ang * 2 * GetRand(10000) / 10000.0);
}

//�G�̃p�^�[���ʂł̈ړ�����
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
			enemy[i].vy = 3;//�������Ă���
		}
		if (enemy[i].counter == 40){
			enemy[i].vy = 0;//�~�܂�
		}
		if (enemy[i].counter == 40 + enemy[i].wait){//�o�^���ꂽ���Ԃ�����؂���
			enemy[i].vx = -1;//����
			enemy[i].vy = 2;//�������Ă���
			enemy[i].direction = 0;//�������Z�b�g
		}
		break;
	case 2:
		if (enemy[i].counter == 0){
			enemy[i].vy = 3;//�������Ă���
		}
		if (enemy[i].counter == 40){
			enemy[i].vy = 0;//�~�܂�
		}
		if (enemy[i].counter == 40 + enemy[i].wait){//�o�^���ꂽ���Ԃ�����؂���
			enemy[i].vx = 1;//�E��
			enemy[i].vy = 2;//�������Ă���
			enemy[i].direction = 2;//�E�����Z�b�g
		}
		break;
	case 3:
		if (enemy[i].counter == 0){
			enemy[i].vy = 5;//�������Ă���
		}
		if (enemy[i].counter == 30){//�r���ō�������
			enemy[i].direction = 0;
		}
		if (enemy[i].counter<100){
			enemy[i].vx -= 5 / 100.0;//����������
			enemy[i].vy -= 5 / 100.0;//����
		}
		break;
	case 4:
		if (enemy[i].counter == 0){
			enemy[i].vy = 5;//�������Ă���
		}
		if (enemy[i].counter == 30){//�r���ŉE������
			enemy[i].direction = 2;
		}
		if (enemy[i].counter<100){
			enemy[i].vx += 5 / 100.0;//�E��������
			enemy[i].vy -= 5 / 100.0;//����
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
		if (enemy[i].counter == enemy[i].wait){//�o�^���ꂽ���Ԃ�����؂���
			enemy[i].vx = -0.7;//����
			enemy[i].vy = -0.3;//�オ���Ă���
			enemy[i].direction = 0;//������
		}
		break;
	case 8:
		if (enemy[i].counter == enemy[i].wait){//�o�^���ꂽ���Ԃ�����؂���
			enemy[i].vx = +0.7;//�E��
			enemy[i].vy = -0.3;//�オ���Ă���
			enemy[i].direction = 2;//�E����
		}
		break;
	case 9:
		if (enemy[i].counter == enemy[i].wait){//�o�^���ꂽ���Ԃ�����؂���
			enemy[i].vy = -1;//�オ���Ă���
	}
		break;
	case 10:
		if (enemy[i].counter == 0) enemy[i].vy = 4;//�������Ă���
		if (enemy[i].counter == 40)enemy[i].vy = 0;//�~�܂�
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
			enemy[i].vx = -1.5;//����
			enemy[i].vy = -3;//�オ���Ă���
			enemy[i].direction = 0;//������
		}
		break;
	case 12:
		if (enemy[i].counter == 0) {
			enemy[i].vx = 1.5;//�E��
			enemy[i].vy = -3;//�オ���Ă���
			enemy[i].direction = 2;//�E����
		}
		break;
	case 13:
		if (enemy[i].counter == 0) {
			enemy[i].vx = -3;//����
			enemy[i].direction = 0;//������
		}
		break;
	case 14:
		if (enemy[i].counter == 0) {
			enemy[i].vx = 3;//�E��
			enemy[i].direction = 2;//�E����
		}
		break;
	case 15://��������
		if (enemy[i].counter < 20) {
			enemy[i].vx -= 0.3;
			enemy[i].vy += 0.5;
			enemy[i].direction = 0;
		}
		if (enemy[i].counter == 20) {
			enemy[i].vx = 0;
			enemy[i].vy = 0;
		}
		if (enemy[i].counter > 20 + enemy[i].wait) {//�o�^���ꂽ���Ԃ�����؂���
			enemy[i].vx -= 0.5;
			enemy[i].vy -= 0.5;//�オ���Ă���
		}
		break;
	case 16://�E���E��
		if (enemy[i].counter < 20) {
			enemy[i].vx += 0.3;
			enemy[i].vy += 0.5;
			enemy[i].direction = 2;
		}
		if (enemy[i].counter == 20) {
			enemy[i].vx = 0;
			enemy[i].vy = 0;
		}
		if (enemy[i].counter > 20 + enemy[i].wait) {//�o�^���ꂽ���Ԃ�����؂���
			enemy[i].vx += 0.5;
			enemy[i].vy -= 0.5;//�オ���Ă���
		}
		break;
	case 17://�E��
		if (enemy[i].counter == 0) {
			enemy[i].vx += 0.8;
			enemy[i].vy += 0.9;
			enemy[i].direction = 2;
		}
		break;
	case 18://����
		if (enemy[i].counter == 0) {
			enemy[i].vx -= 0.8;
			enemy[i].vy += 0.9;
			enemy[i].direction = 0;
		}
		break;
	case 19:
		if (enemy[i].counter == 0) {
			enemy[i].vy = 5;//�������Ă���
		}
		if (enemy[i].counter == 30) {//�r���ō�������
			enemy[i].direction = 0;
		}
		if (enemy[i].counter<100) {
			enemy[i].vx -= 2.5 / 100.0;//����������
			enemy[i].vy -= 5 / 100.0;//����
		}
		break;
	case 20:
		if (enemy[i].counter == 0) {
			enemy[i].vy = 5;//�������Ă���
		}
		if (enemy[i].counter == 30) {//�r���ŉE������
			enemy[i].direction = 2;
		}
		if (enemy[i].counter<100) {
			enemy[i].vx += 2.5 / 100.0;//�E��������
			enemy[i].vy -= 5 / 100.0;//����
		}
		break;
	}
}