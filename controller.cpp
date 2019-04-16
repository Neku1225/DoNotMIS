#include "define.h"

Config_c::Config_c(){
	window_mode = true;
	k_up = KEY_INPUT_UP;
	k_down = KEY_INPUT_DOWN;
	k_left = KEY_INPUT_LEFT;
	k_right = KEY_INPUT_RIGHT;
	k_shot = KEY_INPUT_Z;
	k_bom = KEY_INPUT_X;
	k_change = KEY_INPUT_LCONTROL;
	k_slow = KEY_INPUT_LSHIFT;
	k_start = KEY_INPUT_ESCAPE;
	g_left = 1;
	g_up = 3;
	g_right = 2;
	g_down = 0;
	g_shot = 4;
	g_bom = 5;
	g_change = 8;
	g_slow = 6;
	g_start = 7;
	setting_flag = 0;
	strncpy_s(keyname[14], "BackSpaceキー",14);
	strncpy_s(keyname[15], "Tabキー", 8);
	strncpy_s(keyname[28], "Enterキー", 10);
	strncpy_s(keyname[42], "左Shiftキー", 12);
	strncpy_s(keyname[54], "右Shiftキー", 12);
	strncpy_s(keyname[29], "左Ctrlキー", 11);
	strncpy_s(keyname[157], "右Ctrlキー", 11);
	strncpy_s(keyname[1], "Escキー",8 );
	strncpy_s(keyname[57], "スペースキー",13 );
	strncpy_s(keyname[201], "PageUpキー",11 );
	strncpy_s(keyname[209], "PageDownキー",13 );
	strncpy_s(keyname[207], "Endキー", 8);
	strncpy_s(keyname[199], "Homeキー",9 );
	strncpy_s(keyname[203], "左キー", 7);
	strncpy_s(keyname[200], "上キー", 7);
	strncpy_s(keyname[205], "右キー", 7);
	strncpy_s(keyname[208], "下キー", 7);
	strncpy_s(keyname[210], "Insertキー",11 );
	strncpy_s(keyname[211], "Deleteキー",11 );
	strncpy_s(keyname[12], "－キー",7 );
	strncpy_s(keyname[125], "￥キー",7 );
	strncpy_s(keyname[144], "＾キー",7 );
	strncpy_s(keyname[52], "．キー", 7);
	strncpy_s(keyname[53], "／キー", 7);
	strncpy_s(keyname[56], "左Altキー",10 );
	strncpy_s(keyname[184], "右Altキー",10 );
	strncpy_s(keyname[70], "ScrollLockキー",15 );
	strncpy_s(keyname[39], "；キー",7 );
	strncpy_s(keyname[146], "：キー",7 );
	strncpy_s(keyname[26], "［キー",7 );
	strncpy_s(keyname[27], "］キー",7 );
	strncpy_s(keyname[145], "＠キー",7 );
	strncpy_s(keyname[43], "＼キー",7 );
	strncpy_s(keyname[51], "，キー",7 );
	strncpy_s(keyname[148], "漢字キー",9 );
	strncpy_s(keyname[121], "変換キー",9 );
	strncpy_s(keyname[123], "無変換キー",11 );
	strncpy_s(keyname[112], "カナキー", 9);
	strncpy_s(keyname[221], "メニューキー", 13);
	strncpy_s(keyname[58], "CapsLockキー",13 );
	strncpy_s(keyname[183], "PrintScreenキー",16 );
	strncpy_s(keyname[197], "PauseBreakキー",15 );
	strncpy_s(keyname[219], "左Winキー",10 );
	strncpy_s(keyname[220], "右Winキー",10 );
	strncpy_s(keyname[69], "テンキーNumLockキー",20 );
	strncpy_s(keyname[82], "テンキー０",11 );
	strncpy_s(keyname[79], "テンキー１",11 );
	strncpy_s(keyname[80], "テンキー２",11 );
	strncpy_s(keyname[81], "テンキー３",11 );
	strncpy_s(keyname[75], "テンキー４",11 );
	strncpy_s(keyname[76], "テンキー５",11 );
	strncpy_s(keyname[77], "テンキー６",11 );
	strncpy_s(keyname[71], "テンキー７",11 );
	strncpy_s(keyname[72], "テンキー８",11 );
	strncpy_s(keyname[73], "テンキー９",11 );
	strncpy_s(keyname[55], "テンキー＊キー",15 );
	strncpy_s(keyname[78], "テンキー＋キー",15 );
	strncpy_s(keyname[74], "テンキー－キー",15 );
	strncpy_s(keyname[83], "テンキー．キー",15);
	strncpy_s(keyname[181], "テンキー／キー",15 );
	strncpy_s(keyname[156], "テンキーのエンターキー",23 );
	strncpy_s(keyname[59], "Ｆ１キー",9 );
	strncpy_s(keyname[60], "Ｆ２キー", 9);
	strncpy_s(keyname[61], "Ｆ３キー", 9);
	strncpy_s(keyname[62], "Ｆ４キー", 9);
	strncpy_s(keyname[63], "Ｆ５キー", 9);
	strncpy_s(keyname[64], "Ｆ６キー", 9);
	strncpy_s(keyname[65], "Ｆ７キー", 9);
	strncpy_s(keyname[66], "Ｆ８キー", 9);
	strncpy_s(keyname[67], "Ｆ９キー", 9);
	strncpy_s(keyname[68], "Ｆ１０キー", 11);
	strncpy_s(keyname[87], "Ｆ１１キー", 11);
	strncpy_s(keyname[88], "Ｆ１２キー", 11);
	strncpy_s(keyname[30], "Ａキー", 7);
	strncpy_s(keyname[48], "Ｂキー", 7);
	strncpy_s(keyname[46], "Ｃキー", 7);
	strncpy_s(keyname[32], "Ｄキー", 7);
	strncpy_s(keyname[18], "Ｅキー", 7);
	strncpy_s(keyname[33], "Ｆキー", 7);
	strncpy_s(keyname[34], "Ｇキー", 7);
	strncpy_s(keyname[35], "Ｈキー", 7);
	strncpy_s(keyname[23], "Ｉキー", 7);
	strncpy_s(keyname[36], "Ｊキー", 7);
	strncpy_s(keyname[37], "Ｋキー", 7);
	strncpy_s(keyname[38], "Ｌキー", 7);
	strncpy_s(keyname[50], "Ｍキー", 7);
	strncpy_s(keyname[49], "Ｎキー", 7);
	strncpy_s(keyname[24], "Ｏキー", 7);
	strncpy_s(keyname[25], "Ｐキー", 7);
	strncpy_s(keyname[16], "Ｑキー", 7);
	strncpy_s(keyname[19], "Ｒキー", 7);
	strncpy_s(keyname[31], "Ｓキー", 7);
	strncpy_s(keyname[20], "Ｔキー", 7);
	strncpy_s(keyname[22], "Ｕキー", 7);
	strncpy_s(keyname[47], "Ｖキー", 7);
	strncpy_s(keyname[17], "Ｗキー", 7);
	strncpy_s(keyname[45], "Ｘキー", 7);
	strncpy_s(keyname[21], "Ｙキー", 7);
	strncpy_s(keyname[44], "Ｚキー", 7);
	strncpy_s(keyname[11], "０キー", 7);
	strncpy_s(keyname[2], "１キー", 7);
	strncpy_s(keyname[3], "２キー", 7);
	strncpy_s(keyname[4], "３キー", 7);
	strncpy_s(keyname[5], "４キー", 7);
	strncpy_s(keyname[6], "５キー", 7);
	strncpy_s(keyname[7], "６キー", 7);
	strncpy_s(keyname[8], "７キー", 7);
	strncpy_s(keyname[9], "８キー", 7);
	strncpy_s(keyname[10], "９キー", 7);


}

void Config_c::StartIni() {
	font[0] = CreateFontToHandle(NULL, 20, -1, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
}

void Config_c::ChangeWindow() {
	Sound.Pause();
	ChangeWindowMode(window_mode);								
	SetGraphMode(WINDOW_X, WINDOW_Y, WINDOW_COLOR_BIT);	// 画面の大きさを変える
	SetDrawScreen(DX_SCREEN_BACK);						// 裏画面に描画することを決定
	Control.StartIni();
	Sound.PlayBgm();
}

int Config_c::ConfigDataRead() {
	FILE *fp;
	if (errno_t error = fopen_s(&fp, "config.dat", "r") != 0) {
		return 0;
	}
	fread(&k_left, sizeof(int) * 9, 9, fp);
	fread(&g_left, sizeof(int) * 9, 9, fp);
	fread(&window_mode, sizeof(bool) , 1, fp);
	fclose(fp);
	return 0;
}

int Config_c::ConfigDataWrite() {
	FILE *fp;
	if (errno_t error = fopen_s(&fp, "config.dat", "w") != 0) {
		return 0;
	}
	fwrite(&k_left, sizeof(int) * 9, 9, fp);
	fwrite(&g_left, sizeof(int) * 9, 9, fp);
	fwrite(&window_mode, sizeof(bool) , 1, fp);
	fclose(fp); //ファイルを閉じる
	return 0;
}

void Config_c::KeyboardConfig(int Keycode){
	for (int i = 0; i < 256; i++) {
		if (Controller.k_Get(i) > 0) {
			Keycode = i;
		}
	}
}

void Config_c::PadConfig(int Keycode) {
	for (int i = 0; i < PAD_MAX; i++) {
		if (Controller.g_Get(i) > 0) {
			Keycode = i;
		}
	}
}

void Config_c::SettingKey(int* configkey) {
	for (int i = 0; i < 256; i++) {
		if (Controller.k_Get(i) == 1) {
			//既に使用されているキーを登録しようとしたときの処理
			for (int j = 0; j < 9; j++) {
				if (*(&k_left + j) == i) {
					*(&k_left + j) = *configkey;
					Enemy.se_flag[9] = 1;
				}
			}
			*configkey = i;
			setting_flag = 0;
			break;
		}
	}
}

void Config_c::SettingPad(int* configpad) {
	for (int i = 0; i < PAD_MAX; i++) {
		if (Controller.g_Get(i) == 1) {
			//既に使用されているキーを登録しようとしたときの処理
			for (int j = 0; j < 9; j++) {
				if (*(&g_left + j) == i) {
					*(&g_left + j) = *configpad;
					Enemy.se_flag[9] = 1;
				}
			}
			*configpad = i;
			setting_flag = 0;
			break;
		}
	}
}

void Config_c::Config() {
	Menu.BackDraw();
	if (Controller.k_Get(k_up) == 1 || Controller.g_Get(g_up) == 1) {
		config = (config + key_num - 1) % key_num;
	}
	else if (Controller.k_Get(k_down) == 1 || Controller.g_Get(g_down) == 1) {
		config = (config + 1) % key_num;
	}

	if (setting_flag == 0) {
		for (int i = 0; i < key_num; i++) {
			if (config == i) {
				kx[i] = 255;
			}
			else {
				kx[i] = 120;
			}
		}

		if (GetJoypadNum() == 0) {
			DrawStringToHandle(280, 20, "キー設定", GetColor(255, 255, 255), font[0]);
			DrawFormatStringToHandle(255, 60, GetColor(kx[0], kx[0], kx[0]),font[0], "←キー　：%s", keyname[k_left]);
			DrawFormatStringToHandle(255, 60 + 1 * 40, GetColor(kx[1], kx[1], kx[1]), font[0], "↑キー　：%s", keyname[k_up]);
			DrawFormatStringToHandle(255, 60 + 2 * 40, GetColor(kx[2], kx[2], kx[2]), font[0], "→キー　：%s", keyname[k_right]);
			DrawFormatStringToHandle(255, 60 + 3 * 40, GetColor(kx[3], kx[3], kx[3]), font[0], "↓キー　：%s", keyname[k_down]);
			DrawFormatStringToHandle(253, 60 + 4 * 40, GetColor(kx[4], kx[4], kx[4]), font[0], "ショット：%s", keyname[k_shot]);
			DrawFormatStringToHandle(257, 60 + 5 * 40, GetColor(kx[5], kx[5], kx[5]), font[0], "ボム　　：%s", keyname[k_bom]);
			DrawFormatStringToHandle(253, 60 + 6 * 40, GetColor(kx[6], kx[6], kx[6]), font[0], "シールド：%s", keyname[k_change]);
			DrawFormatStringToHandle(253, 60 + 7 * 40, GetColor(kx[7], kx[7], kx[7]), font[0], "低速移動：%s", keyname[k_slow]);
			DrawFormatStringToHandle(255, 60 + 8 * 40, GetColor(kx[8], kx[8], kx[8]), font[0], "ポーズ　：%s", keyname[k_start]);
		}
		else {
			DrawStringToHandle(270, 20, "パッド設定", GetColor(255, 255, 255), font[0]);
			DrawFormatStringToHandle(255, 60, GetColor(kx[0], kx[0], kx[0]), font[0], "←キー　：%3d", g_left);
			DrawFormatStringToHandle(255, 60 + 1 * 40, GetColor(kx[1], kx[1], kx[1]), font[0], "↑キー　：%3d", *(&g_left + 1));
			DrawFormatStringToHandle(255, 60 + 2 * 40, GetColor(kx[2], kx[2], kx[2]), font[0], "→キー　：%3d", *(&g_left + 2));
			DrawFormatStringToHandle(255, 60 + 3 * 40, GetColor(kx[3], kx[3], kx[3]), font[0], "↓キー　：%3d", *(&g_left + 3));
			DrawFormatStringToHandle(253, 60 + 4 * 40, GetColor(kx[4], kx[4], kx[4]), font[0], "ショット：%3d", *(&g_left + 4));
			DrawFormatStringToHandle(257, 60 + 5 * 40, GetColor(kx[5], kx[5], kx[5]), font[0], "ボム　　：%3d", *(&g_left + 5));
			DrawFormatStringToHandle(253, 60 + 6 * 40, GetColor(kx[6], kx[6], kx[6]), font[0], "シールド：%3d", *(&g_left + 6));
			DrawFormatStringToHandle(253, 60 + 7 * 40, GetColor(kx[7], kx[7], kx[7]), font[0], "低速移動：%3d", *(&g_left + 7));
			DrawFormatStringToHandle(255, 60 + 8 * 40, GetColor(kx[8], kx[8], kx[8]), font[0], "ポーズ　：%3d", *(&g_left + 8));
		}

		DrawStringToHandle(210, 440, "ウィンドウモードの変更", GetColor(kx[9], kx[9], kx[9]), font[0]);

		if (Controller.k_Get(k_shot) == 1 || Controller.g_Get(g_shot) == 1) {
			Enemy.se_flag[9] = 1;
			if (config == window_size) {
				setting_flag = 2;
			}
			else {
				setting_flag = 1;
			}
		}else if (Controller.k_Get(k_bom) == 1 || Controller.g_Get(g_bom) == 1) {
			Enemy.se_flag[11] = 1;
			ConfigDataWrite();
			Control.SetMode(title);
		}
	}
	else if(setting_flag==1){

		if (GetJoypadNum() == 0) {
			DrawStringToHandle(180, 240, "設定したいキーを押して下さい", GetColor(255, 255, 255), font[0]);
			switch (config) {
			case left:
				SettingKey(&k_left);
				break;
			case up:
				SettingKey(&k_up);
				break;
			case right:
				SettingKey(&k_right);
				break;
			case down:
				SettingKey(&k_down);
				break;
			case shot:
				SettingKey(&k_shot);
				break;
			case bom:
				SettingKey(&k_bom);
				break;
			case change:
				SettingKey(&k_change);
				break;
			case slow:
				SettingKey(&k_slow);
				break;
			case start:
				SettingKey(&k_start);
				break;

			}
		}
		else {//ゲームパッド接続中ならゲームパッドの設定をする
			DrawStringToHandle(170, 240, "設定したいボタンを押して下さい", GetColor(255, 255, 255), font[0]);
			switch (config) {
			case left:
				SettingPad(&g_left);
				break;
			case up:
				SettingPad(&g_up);
				break;
			case right:
				SettingPad(&g_right);
				break;
			case down:
				SettingPad(&g_down);
				break;
			case shot:
				SettingPad(&g_shot);
				break;
			case bom:
				SettingPad(&g_bom);
				break;
			case change:
				SettingPad(&g_change);
				break;
			case slow:
				SettingPad(&g_slow);
				break;
			case start:
				SettingPad(&g_start);
				break;

			}
		}
	}
	else if (setting_flag == 2) {
		if (window_mode == true) {
			window_mode = false;
		}
		else {
			window_mode = true;
		}
		ChangeWindow();
		setting_flag = 0;
	}
}


//----------キーボードの入力状態を記憶する関数----------//

int Controller_c::k_Update(){

	char nKey[256];									// 現在のキーボードの入力状態を格納するnKeyを用意する

	GetHitKeyStateAll(nKey);						// キーボードの全ての入力状態をnKeyに格納

	for (int i = 0; i < 256; i++){
		if (nKey[i] != 0){							// i番のキーコードに対応するキーが押されていたら
			k_Key[i]++;								// キーボードの対応するキーの入力回数を加算
		}
		else {										// 押されていなければ
			k_Key[i] = 0;							// 0にする
		}
	}

	return 0;										// 正常終了0を返す
}



//----------指定されたキーコードのキーの入力状態を返す関数----------//

int Controller_c::k_Get(int KeyCode){

	return k_Key[KeyCode];							// KeyCodeに対応するキーの入力状態を返す
}



//----------ゲームパッドの入力状態を記憶する関数----------//

int Controller_c::g_Update(){

	int PadInput;									// ゲームパッドの入力状態を格納するPadInputを用意
	int mul = 1;									//

	PadInput = GetJoypadInputState(DX_INPUT_PAD1);	// ゲームパッドの入力状態をPadInputに格納

	for (int i = 0; i < PAD_MAX; i++){
		if ((PadInput & mul) != 0){					// i番のキーコードに対応するキーが押されていたら
			g_Key[i]++;								// 加算
		}
		else {										// 押されていなければ
			g_Key[i] = 0;							// 0にする
		}
		mul *= 2;									// mulに2を掛ける
	}

	return 0;										// 正常終了0を返す
}



//-----c-----//

int Controller_c::g_Get(int KeyCode){

	if (0 <= KeyCode && KeyCode < PAD_MAX){
		return g_Key[KeyCode];						// KeyCodeの入力状態を返す
	}
	else{
		printfDx("CheckStatePadに渡した値が不正です\n");
		return -1;
	}

}

