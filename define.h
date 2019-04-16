#pragma once
#define _USE_MATH_DEFINES

//画面の大きさ
#define WINDOW_X 640			//ウィンドウサイズ横(pixel)
#define WINDOW_Y 480			//ウィンドウサイズ縦(pixel)
#define WINDOW_COLOR_BIT 32		//画面色深度(bit)
//フィールドの広さ
#define FIELD_MAX_X 384
#define FIELD_MAX_Y 448
//フィールドの左上の座標
#define FIELD_X 32
#define FIELD_Y 16
//パッドキーの最大数
#define PAD_MAX 16
//自機ショットの登録最大数
#define P_SHOT_MAX 200
//自機ショットの種類
#define P_SHOT_TYPE 5
//自機の当たり判定の大きさ
#define P_RANGE 4.0
//自機ショットの当たり判定の種類の最大数
#define PSHOT_RANGE_MAX 5
//敵の当たり判定の種類の最大数
#define ENEMY_RANGE_MAX 5
//敵の同時表示最大数
#define ENEMY_MAX 30
//敵の出現情報最大数
#define ENEMY_ORDER_MAX 500
//敵１匹が持つ弾の最大数
#define SHOT_BULLET_MAX 1000
//一度に画面に表示できる敵の弾幕の最大数
#define SHOT_MAX 30
//ボスショットの種類の最大数
#define BSHOT_TYPE_MAX 10
//ショットの種類の最大数
#define SHOT_TYPE_MAX 20
//効果音の種類の最大数
#define SE_MAX 51
//敵の行動パターンの最大数
#define ENEMY_PATTERN_MAX 30
//エフェクト登録最大数
#define EFFECT_MAX 100
//消滅エフェクト登録最大数
#define DEL_EFFECT_MAX 30
//ボスの定位置
#define BOSS_POS_X (FIELD_MAX_X+FIELD_X*2)/2
#define BOSS_POS_Y 100.0
//ボスが持つ弾の最大数
#define BOSS_BULLET_MAX 3000
//ボスの当たり判定の種類
#define B_RANGE_MAX 5
//弾幕最大数
#define DANMAKU_MAX 50
//侵食度の最大値
#define EROSION_MAX 180000
//残機の初期値
#define DEFAULT_P_NUM 5 
//一体のボス辺りの画像の最大数
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
