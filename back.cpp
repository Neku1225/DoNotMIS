#include "define.h"

void Back_c::Load(int STAGE){
	for (int i = 0; i < 2; i++) {
		DeleteGraph(stage[i]);
	}
	switch (STAGE) {
	case 1:
		stage[0] = LoadGraph("material/img/back/south_back.png");//“ì
		stage[1] = LoadGraph("material/img/back/south_boss_back.png");
		break;
	case 2:
		stage[0] = LoadGraph("material/img/back/east_back.png");//“Œ
		stage[1] = LoadGraph("material/img/back/east_boss_back.png");
		break;
	case 3:
		stage[0] = LoadGraph("material/img/back/west_back.png");//¼
		stage[1] = LoadGraph("material/img/back/west_boss_back.png");
		break;
	case 4:
		stage[0] = LoadGraph("material/img/back/north_back.png");//–k
		stage[1] = LoadGraph("material/img/back/north_boss_back.png");
		break;
	case 5:
		stage[0] = LoadGraph("material/img/back/final_back.png");
		break;
	}
}

void Back_c::StartIni() {
	gh[0] = LoadGraph("material/img/back/scoreboard.png");
	gh[1] = LoadGraph("material/img/player/icon.png");

	font[0] = CreateFontToHandle("Microsoft Sans Serif", 25, -1, -1);
	font[1] = CreateFontToHandle("Microsoft Sans Serif", 50, -1, -1);
}

void Back_c::DrawBoard() {
	DrawGraph(0, 0, gh[0], FALSE);

	DrawFormatStringToHandle(FIELD_X + FIELD_MAX_X + 40, 150, GetColor(255, 255, 255), font[0], "%07d", Control.GetHighScore(Control.level_num));
	DrawFormatStringToHandle(FIELD_X + FIELD_MAX_X + 40, 210, GetColor(255, 255, 255), font[0], "%07d", Control.GetScore());
	//ƒGƒlƒ‹ƒM[ƒQ[ƒW‚Ì•`ŽÊ
	DrawBox(FIELD_X + FIELD_MAX_X + 92, 290, FIELD_X + FIELD_MAX_X + 212, 305, GetColor(0, 0, 0), true);
	if (Player.GetCoolFlag() == true) {
		DrawBox(FIELD_X + FIELD_MAX_X + 93, 291, FIELD_X + FIELD_MAX_X + 93 + Player.GetEnergy() * 118.0 / 6000.0, 304, GetColor(255, 0, 0), true);
	}
	else {
		DrawBox(FIELD_X + FIELD_MAX_X + 93, 291, FIELD_X + FIELD_MAX_X + 93 + Player.GetEnergy() * 118.0 / 6000.0, 304, GetColor(255, 255, 255), true);
	}
	
	if (Player.GetCharge() < 1200) {
		DrawFormatStringToHandle(FIELD_X + FIELD_MAX_X + 100, 316, GetColor(255, 255, 255), font[0], "%3d %%", Player.GetCharge() * 100 / 1200);
	}
	else {
		DrawStringToHandle(FIELD_X + FIELD_MAX_X + 100, 316, "MAX", GetColor(255, 255, 255), font[0]);
	}
	//ZH“x‚ÌF•Ï‰»
	if (Control.erosion < EROSION_MAX*0.8) {
		DrawFormatStringToHandle(FIELD_X + FIELD_MAX_X + 70, 60, GetColor(255 * Control.erosion / EROSION_MAX/0.8, 255, 255-255*Control.erosion/EROSION_MAX/0.8),
			font[1], "%3d%%", Control.erosion * 100 / EROSION_MAX);
	}
	else {
		DrawFormatStringToHandle(FIELD_X + FIELD_MAX_X + 70, 60,
			GetColor(255, 255 - 255 * ((Control.erosion - EROSION_MAX*0.8) / EROSION_MAX) / 0.2, 0), font[1], "%3d%%", Control.erosion * 100 / EROSION_MAX);
	}

	DrawFormatStringToHandle(FIELD_X + FIELD_MAX_X + 107, 253, GetColor(255, 255, 255), font[0],"%03d",Player.death_count);
	/*
	//Žc‹@‚Ì•\Ž¦
	for (int i = 0; i < Player.GetPlayerNum() - 1; i++) {
		DrawRotaGraphF(FIELD_X + FIELD_MAX_X + 107 + i * 30, 263, 0.8f, 0.0f, gh[1], true);
	}*/
}

void Back_c::DrawStageNormal() {
	DrawGraph(FIELD_X, Control.g_count % 700 + FIELD_Y - 700, stage[0], FALSE);
	DrawGraph(FIELD_X, Control.g_count % 700 + FIELD_Y, stage[0], FALSE);
}

void Back_c::DrawStageBoss() {//ƒ{ƒXí—p”wŒi
	DrawGraph(FIELD_X, (Control.g_count - Boss.GetAppearCount()) % 700 + FIELD_Y - 700, stage[1], FALSE);
	DrawGraph(FIELD_X, (Control.g_count - Boss.GetAppearCount()) % 700 + FIELD_Y, stage[1], FALSE);
}

void Back_c::DrawStage() {
	if (Control.GetState() != stage5 && Control.g_count>Boss.GetAppearCount()) {
		DrawStageBoss();
	}
	else {//‚»‚êˆÈŠO
		DrawStageNormal();
	}
}