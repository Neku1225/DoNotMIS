#include "define.h"


void menu_c::Title(){
	BackDraw();
	DrawRotaGraphF(320, 130, 1.0f, 0.0f, title_logo, TRUE);
	if (level_select == notselect) {
		//コマンドの位置の制御
		for (int i = 0; i < tcom_num; i++) {
			if (title_com == i) {
				tx[i] = 255;
			}
			else {
				tx[i] = 120;
			}
		}
		
		DrawStringToHandle(250, 280, "ゲームスタート", GetColor(tx[0], tx[0], tx[0]), font[1]);
		DrawStringToHandle(270, 330, "コンフィグ", GetColor(tx[1], tx[1], tx[1]), font[1]);
		DrawStringToHandle(270, 380, "クレジット", GetColor(tx[2], tx[2], tx[2]), font[1]);
		DrawStringToHandle(270, 430, "ゲーム終了", GetColor(tx[3], tx[3], tx[3]), font[1]);
	}
	else {
		for (int i = 0; i < level_num; i++) {
			if (level_select == i) {
				lx[i] = 250;
			}
			else {
				lx[i] = 120;
			}
		}

		DrawStringToHandle(300, 280, "Easy", GetColor(lx[0], lx[0], lx[0]), font[1]);
		DrawStringToHandle(290, 330, "Normal", GetColor(lx[1], lx[1], lx[1]), font[1]);
		DrawStringToHandle(300, 380, "Hard", GetColor(lx[2], lx[2], lx[2]), font[1]);
	}

		if (Controller.k_Get(Config.k_up) == 1 || Controller.g_Get(Config.g_up) == 1) {
			if (level_select == notselect) {
				title_com = (title_com + tcom_num - 1) % tcom_num;
			}
			else {
				level_select = (level_select + level_num - 1) % level_num;
			}
		}
		else if (Controller.k_Get(Config.k_down) == 1 || Controller.g_Get(Config.g_down) == 1) {
			if (level_select == notselect) {
				title_com = (title_com + 1) % tcom_num;
			}
			else {
				level_select = (level_select + 1) % level_num;
			}
		}

	switch (title_com) {

	case gamestart:
		SetTx(250, 270, 270, 270);
		
			switch (level_select) {
				case easy:
					SetLx(280, 300, 300);
					Control.SetLevel('E');
					break;
				case normal:
					SetLx(300, 280, 300);
					Control.SetLevel('N');
					break;
				case hard:
					SetLx(300, 300, 280);
					Control.SetLevel('H');
					break;
				}

			if(Controller.k_Get(Config.k_shot) == 1 || Controller.g_Get(Config.g_shot) == 1){
				if (level_select == notselect) {
					level_select = easy;
					Enemy.se_flag[9] = 1;
				}
				else {
					Sound.Pause();
					Control.SetStage(s1_loading);
					Control.SetMode(game_play);
					Player.Initialize();
					Control.erosion = 0;
					Control.SetScore(0);
					level_select = notselect;
					Enemy.se_flag[9] = 1;
				}
			}
		else if (Controller.k_Get(Config.k_bom) == 1 || Controller.g_Get(Config.g_bom) == 1) {
			Enemy.se_flag[11] = 1;
				level_select = notselect;
		}
		break;

	case config:
		SetTx(270, 250, 270, 270);
		if (Controller.k_Get(Config.k_shot) == 1 || Controller.g_Get(Config.g_shot) == 1) {
			Enemy.se_flag[9] = 1;
			Control.SetMode(setting);
		}
		break;

	case credit:
		SetTx(270, 270, 250, 270);
		if (Controller.k_Get(Config.k_shot) == 1 || Controller.g_Get(Config.g_shot) == 1) {
			Enemy.se_flag[9] = 1;
			Control.SetMode(staff_roll);
		}
		break;

	case finish:
		SetTx(270, 270, 270, 250);
		if (Controller.k_Get(Config.k_shot) == 1 || Controller.g_Get(Config.g_shot) == 1) {
			DxLib_End();
			exit(1);
		}
		break;
	}
}

void menu_c::StaffRoll() {
	BackDraw();
	if (Controller.k_Get(Config.k_bom) == 1 || Controller.g_Get(Config.g_bom) == 1) {
		Enemy.se_flag[11] = 1;
		Control.SetMode(title);
	}
	DrawStringToHandle(40, 20, "企画長　：Uta", GetColor(255, 255, 255), font[1]);
	DrawStringToHandle(40, 40, "副企画長：neku", GetColor(255, 255, 255), font[1]);

	DrawStringToHandle(40, 80, "プログラミング", GetColor(255, 255, 255), font[1]);
	DrawStringToHandle(100, 110, "neku", GetColor(255, 255, 255), font[1]);
	DrawStringToHandle(100, 140, "sada", GetColor(255, 255, 255), font[1]);
	DrawStringToHandle(100, 170, "ZAKI", GetColor(255, 255, 255), font[1]);
	DrawStringToHandle(320, 80, "CG", GetColor(255, 255, 255), font[1]);
	DrawStringToHandle(313, 110, "Uta", GetColor(255, 255, 255), font[1]);
	DrawStringToHandle(290, 140, "ぐっちー", GetColor(255, 255, 255), font[1]);
	DrawStringToHandle(290, 170, "すずしろ", GetColor(255, 255, 255), font[1]);
	DrawStringToHandle(310, 200, "fumi", GetColor(255, 255, 255), font[1]);
	//DrawStringToHandle(300, 230, "たすく", GetColor(255, 255, 255), font[1]);
	DrawStringToHandle(500, 80, "MIDI", GetColor(255, 255, 255), font[1]);
	DrawStringToHandle(520, 110, "Q", GetColor(255, 255, 255), font[1]);
	DrawStringToHandle(480, 140, "karasumi", GetColor(255, 255, 255), font[1]);
	DrawStringToHandle(480, 170, "まっしー", GetColor(255, 255, 255), font[1]);
//DrawStringToHandle(40, 400, "参考にしたサイト：新・ゲームプログラミングの館", GetColor(255, 255, 255),font[1]);
}

void menu_c::BackDraw() {
	DrawGraph(0, d_count % 970 - 970, back[0], FALSE);
	DrawGraph(0, d_count % 970, back[0], FALSE);
	d_count++;
}

void menu_c::SetTx(int settx0, int settx1, int settx2, int settx3) {
	tx[0] = settx0;
	tx[1] = settx1;
	tx[2] = settx2;
	tx[3] = settx3;
}

void menu_c::SetLx(int setlx0, int setlx1, int setlx2) {
	lx[0] = setlx0;
	lx[1] = setlx1;
	lx[2] = setlx2;
}

void menu_c::SetTCom(int settcom) {
	title_com = settcom;
}

void menu_c::StartIni() {
	font[0] = CreateFontToHandle(NULL, 100, -1, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
	font[1] = CreateFontToHandle(NULL, 20, -1, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
	title_logo = LoadGraph("material/img/back/title_logo.png");
	back[0] = LoadGraph("material/img/back/title_back.jpg");
	SetTx(250, 270, 270, 270);
	title_com = gamestart;
	SetLx(280, 300, 300);
	level_select = notselect;
	d_count = 0;
}