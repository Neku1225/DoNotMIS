#pragma once
#define _USE_MATH_DEFINES

//��ʂ̑傫��
#define WINDOW_X 640			//�E�B���h�E�T�C�Y��(pixel)
#define WINDOW_Y 480			//�E�B���h�E�T�C�Y�c(pixel)
#define WINDOW_COLOR_BIT 32		//��ʐF�[�x(bit)
//�t�B�[���h�̍L��
#define FIELD_MAX_X 384
#define FIELD_MAX_Y 448
//�t�B�[���h�̍���̍��W
#define FIELD_X 32
#define FIELD_Y 16
//�p�b�h�L�[�̍ő吔
#define PAD_MAX 16
//���@�V���b�g�̓o�^�ő吔
#define P_SHOT_MAX 200
//���@�V���b�g�̎��
#define P_SHOT_TYPE 5
//���@�̓����蔻��̑傫��
#define P_RANGE 4.0
//���@�V���b�g�̓����蔻��̎�ނ̍ő吔
#define PSHOT_RANGE_MAX 5
//�G�̓����蔻��̎�ނ̍ő吔
#define ENEMY_RANGE_MAX 5
//�G�̓����\���ő吔
#define ENEMY_MAX 30
//�G�̏o�����ő吔
#define ENEMY_ORDER_MAX 500
//�G�P�C�����e�̍ő吔
#define SHOT_BULLET_MAX 1000
//��x�ɉ�ʂɕ\���ł���G�̒e���̍ő吔
#define SHOT_MAX 30
//�{�X�V���b�g�̎�ނ̍ő吔
#define BSHOT_TYPE_MAX 10
//�V���b�g�̎�ނ̍ő吔
#define SHOT_TYPE_MAX 20
//���ʉ��̎�ނ̍ő吔
#define SE_MAX 51
//�G�̍s���p�^�[���̍ő吔
#define ENEMY_PATTERN_MAX 30
//�G�t�F�N�g�o�^�ő吔
#define EFFECT_MAX 100
//���ŃG�t�F�N�g�o�^�ő吔
#define DEL_EFFECT_MAX 30
//�{�X�̒�ʒu
#define BOSS_POS_X (FIELD_MAX_X+FIELD_X*2)/2
#define BOSS_POS_Y 100.0
//�{�X�����e�̍ő吔
#define BOSS_BULLET_MAX 3000
//�{�X�̓����蔻��̎��
#define B_RANGE_MAX 5
//�e���ő吔
#define DANMAKU_MAX 50
//�N�H�x�̍ő�l
#define EROSION_MAX 180000
//�c�@�̏����l
#define DEFAULT_P_NUM 5 
//��̂̃{�X�ӂ�̉摜�̍ő吔
#define BOSS_IMG_MAX 18 

#include "DxLib.h"
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include "controller.h"
#include "player.h"
#include "back.h"
#include "control.h"
#include "enemy.h"
#include "sound.h"
#include "effect.h"
#include "judge.h"
#include "boss.h"
#include "menu.h"
#include <string.h>
