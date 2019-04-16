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
	strncpy_s(keyname[14], "BackSpace�L�[",14);
	strncpy_s(keyname[15], "Tab�L�[", 8);
	strncpy_s(keyname[28], "Enter�L�[", 10);
	strncpy_s(keyname[42], "��Shift�L�[", 12);
	strncpy_s(keyname[54], "�EShift�L�[", 12);
	strncpy_s(keyname[29], "��Ctrl�L�[", 11);
	strncpy_s(keyname[157], "�ECtrl�L�[", 11);
	strncpy_s(keyname[1], "Esc�L�[",8 );
	strncpy_s(keyname[57], "�X�y�[�X�L�[",13 );
	strncpy_s(keyname[201], "PageUp�L�[",11 );
	strncpy_s(keyname[209], "PageDown�L�[",13 );
	strncpy_s(keyname[207], "End�L�[", 8);
	strncpy_s(keyname[199], "Home�L�[",9 );
	strncpy_s(keyname[203], "���L�[", 7);
	strncpy_s(keyname[200], "��L�[", 7);
	strncpy_s(keyname[205], "�E�L�[", 7);
	strncpy_s(keyname[208], "���L�[", 7);
	strncpy_s(keyname[210], "Insert�L�[",11 );
	strncpy_s(keyname[211], "Delete�L�[",11 );
	strncpy_s(keyname[12], "�|�L�[",7 );
	strncpy_s(keyname[125], "���L�[",7 );
	strncpy_s(keyname[144], "�O�L�[",7 );
	strncpy_s(keyname[52], "�D�L�[", 7);
	strncpy_s(keyname[53], "�^�L�[", 7);
	strncpy_s(keyname[56], "��Alt�L�[",10 );
	strncpy_s(keyname[184], "�EAlt�L�[",10 );
	strncpy_s(keyname[70], "ScrollLock�L�[",15 );
	strncpy_s(keyname[39], "�G�L�[",7 );
	strncpy_s(keyname[146], "�F�L�[",7 );
	strncpy_s(keyname[26], "�m�L�[",7 );
	strncpy_s(keyname[27], "�n�L�[",7 );
	strncpy_s(keyname[145], "���L�[",7 );
	strncpy_s(keyname[43], "�_�L�[",7 );
	strncpy_s(keyname[51], "�C�L�[",7 );
	strncpy_s(keyname[148], "�����L�[",9 );
	strncpy_s(keyname[121], "�ϊ��L�[",9 );
	strncpy_s(keyname[123], "���ϊ��L�[",11 );
	strncpy_s(keyname[112], "�J�i�L�[", 9);
	strncpy_s(keyname[221], "���j���[�L�[", 13);
	strncpy_s(keyname[58], "CapsLock�L�[",13 );
	strncpy_s(keyname[183], "PrintScreen�L�[",16 );
	strncpy_s(keyname[197], "PauseBreak�L�[",15 );
	strncpy_s(keyname[219], "��Win�L�[",10 );
	strncpy_s(keyname[220], "�EWin�L�[",10 );
	strncpy_s(keyname[69], "�e���L�[NumLock�L�[",20 );
	strncpy_s(keyname[82], "�e���L�[�O",11 );
	strncpy_s(keyname[79], "�e���L�[�P",11 );
	strncpy_s(keyname[80], "�e���L�[�Q",11 );
	strncpy_s(keyname[81], "�e���L�[�R",11 );
	strncpy_s(keyname[75], "�e���L�[�S",11 );
	strncpy_s(keyname[76], "�e���L�[�T",11 );
	strncpy_s(keyname[77], "�e���L�[�U",11 );
	strncpy_s(keyname[71], "�e���L�[�V",11 );
	strncpy_s(keyname[72], "�e���L�[�W",11 );
	strncpy_s(keyname[73], "�e���L�[�X",11 );
	strncpy_s(keyname[55], "�e���L�[���L�[",15 );
	strncpy_s(keyname[78], "�e���L�[�{�L�[",15 );
	strncpy_s(keyname[74], "�e���L�[�|�L�[",15 );
	strncpy_s(keyname[83], "�e���L�[�D�L�[",15);
	strncpy_s(keyname[181], "�e���L�[�^�L�[",15 );
	strncpy_s(keyname[156], "�e���L�[�̃G���^�[�L�[",23 );
	strncpy_s(keyname[59], "�e�P�L�[",9 );
	strncpy_s(keyname[60], "�e�Q�L�[", 9);
	strncpy_s(keyname[61], "�e�R�L�[", 9);
	strncpy_s(keyname[62], "�e�S�L�[", 9);
	strncpy_s(keyname[63], "�e�T�L�[", 9);
	strncpy_s(keyname[64], "�e�U�L�[", 9);
	strncpy_s(keyname[65], "�e�V�L�[", 9);
	strncpy_s(keyname[66], "�e�W�L�[", 9);
	strncpy_s(keyname[67], "�e�X�L�[", 9);
	strncpy_s(keyname[68], "�e�P�O�L�[", 11);
	strncpy_s(keyname[87], "�e�P�P�L�[", 11);
	strncpy_s(keyname[88], "�e�P�Q�L�[", 11);
	strncpy_s(keyname[30], "�`�L�[", 7);
	strncpy_s(keyname[48], "�a�L�[", 7);
	strncpy_s(keyname[46], "�b�L�[", 7);
	strncpy_s(keyname[32], "�c�L�[", 7);
	strncpy_s(keyname[18], "�d�L�[", 7);
	strncpy_s(keyname[33], "�e�L�[", 7);
	strncpy_s(keyname[34], "�f�L�[", 7);
	strncpy_s(keyname[35], "�g�L�[", 7);
	strncpy_s(keyname[23], "�h�L�[", 7);
	strncpy_s(keyname[36], "�i�L�[", 7);
	strncpy_s(keyname[37], "�j�L�[", 7);
	strncpy_s(keyname[38], "�k�L�[", 7);
	strncpy_s(keyname[50], "�l�L�[", 7);
	strncpy_s(keyname[49], "�m�L�[", 7);
	strncpy_s(keyname[24], "�n�L�[", 7);
	strncpy_s(keyname[25], "�o�L�[", 7);
	strncpy_s(keyname[16], "�p�L�[", 7);
	strncpy_s(keyname[19], "�q�L�[", 7);
	strncpy_s(keyname[31], "�r�L�[", 7);
	strncpy_s(keyname[20], "�s�L�[", 7);
	strncpy_s(keyname[22], "�t�L�[", 7);
	strncpy_s(keyname[47], "�u�L�[", 7);
	strncpy_s(keyname[17], "�v�L�[", 7);
	strncpy_s(keyname[45], "�w�L�[", 7);
	strncpy_s(keyname[21], "�x�L�[", 7);
	strncpy_s(keyname[44], "�y�L�[", 7);
	strncpy_s(keyname[11], "�O�L�[", 7);
	strncpy_s(keyname[2], "�P�L�[", 7);
	strncpy_s(keyname[3], "�Q�L�[", 7);
	strncpy_s(keyname[4], "�R�L�[", 7);
	strncpy_s(keyname[5], "�S�L�[", 7);
	strncpy_s(keyname[6], "�T�L�[", 7);
	strncpy_s(keyname[7], "�U�L�[", 7);
	strncpy_s(keyname[8], "�V�L�[", 7);
	strncpy_s(keyname[9], "�W�L�[", 7);
	strncpy_s(keyname[10], "�X�L�[", 7);


}

void Config_c::StartIni() {
	font[0] = CreateFontToHandle(NULL, 20, -1, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
}

void Config_c::ChangeWindow() {
	Sound.Pause();
	ChangeWindowMode(window_mode);								
	SetGraphMode(WINDOW_X, WINDOW_Y, WINDOW_COLOR_BIT);	// ��ʂ̑傫����ς���
	SetDrawScreen(DX_SCREEN_BACK);						// ����ʂɕ`�悷�邱�Ƃ�����
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
	fclose(fp); //�t�@�C�������
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
			//���Ɏg�p����Ă���L�[��o�^���悤�Ƃ����Ƃ��̏���
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
			//���Ɏg�p����Ă���L�[��o�^���悤�Ƃ����Ƃ��̏���
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
			DrawStringToHandle(280, 20, "�L�[�ݒ�", GetColor(255, 255, 255), font[0]);
			DrawFormatStringToHandle(255, 60, GetColor(kx[0], kx[0], kx[0]),font[0], "���L�[�@�F%s", keyname[k_left]);
			DrawFormatStringToHandle(255, 60 + 1 * 40, GetColor(kx[1], kx[1], kx[1]), font[0], "���L�[�@�F%s", keyname[k_up]);
			DrawFormatStringToHandle(255, 60 + 2 * 40, GetColor(kx[2], kx[2], kx[2]), font[0], "���L�[�@�F%s", keyname[k_right]);
			DrawFormatStringToHandle(255, 60 + 3 * 40, GetColor(kx[3], kx[3], kx[3]), font[0], "���L�[�@�F%s", keyname[k_down]);
			DrawFormatStringToHandle(253, 60 + 4 * 40, GetColor(kx[4], kx[4], kx[4]), font[0], "�V���b�g�F%s", keyname[k_shot]);
			DrawFormatStringToHandle(257, 60 + 5 * 40, GetColor(kx[5], kx[5], kx[5]), font[0], "�{���@�@�F%s", keyname[k_bom]);
			DrawFormatStringToHandle(253, 60 + 6 * 40, GetColor(kx[6], kx[6], kx[6]), font[0], "�V�[���h�F%s", keyname[k_change]);
			DrawFormatStringToHandle(253, 60 + 7 * 40, GetColor(kx[7], kx[7], kx[7]), font[0], "�ᑬ�ړ��F%s", keyname[k_slow]);
			DrawFormatStringToHandle(255, 60 + 8 * 40, GetColor(kx[8], kx[8], kx[8]), font[0], "�|�[�Y�@�F%s", keyname[k_start]);
		}
		else {
			DrawStringToHandle(270, 20, "�p�b�h�ݒ�", GetColor(255, 255, 255), font[0]);
			DrawFormatStringToHandle(255, 60, GetColor(kx[0], kx[0], kx[0]), font[0], "���L�[�@�F%3d", g_left);
			DrawFormatStringToHandle(255, 60 + 1 * 40, GetColor(kx[1], kx[1], kx[1]), font[0], "���L�[�@�F%3d", *(&g_left + 1));
			DrawFormatStringToHandle(255, 60 + 2 * 40, GetColor(kx[2], kx[2], kx[2]), font[0], "���L�[�@�F%3d", *(&g_left + 2));
			DrawFormatStringToHandle(255, 60 + 3 * 40, GetColor(kx[3], kx[3], kx[3]), font[0], "���L�[�@�F%3d", *(&g_left + 3));
			DrawFormatStringToHandle(253, 60 + 4 * 40, GetColor(kx[4], kx[4], kx[4]), font[0], "�V���b�g�F%3d", *(&g_left + 4));
			DrawFormatStringToHandle(257, 60 + 5 * 40, GetColor(kx[5], kx[5], kx[5]), font[0], "�{���@�@�F%3d", *(&g_left + 5));
			DrawFormatStringToHandle(253, 60 + 6 * 40, GetColor(kx[6], kx[6], kx[6]), font[0], "�V�[���h�F%3d", *(&g_left + 6));
			DrawFormatStringToHandle(253, 60 + 7 * 40, GetColor(kx[7], kx[7], kx[7]), font[0], "�ᑬ�ړ��F%3d", *(&g_left + 7));
			DrawFormatStringToHandle(255, 60 + 8 * 40, GetColor(kx[8], kx[8], kx[8]), font[0], "�|�[�Y�@�F%3d", *(&g_left + 8));
		}

		DrawStringToHandle(210, 440, "�E�B���h�E���[�h�̕ύX", GetColor(kx[9], kx[9], kx[9]), font[0]);

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
			DrawStringToHandle(180, 240, "�ݒ肵�����L�[�������ĉ�����", GetColor(255, 255, 255), font[0]);
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
		else {//�Q�[���p�b�h�ڑ����Ȃ�Q�[���p�b�h�̐ݒ������
			DrawStringToHandle(170, 240, "�ݒ肵�����{�^���������ĉ�����", GetColor(255, 255, 255), font[0]);
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


//----------�L�[�{�[�h�̓��͏�Ԃ��L������֐�----------//

int Controller_c::k_Update(){

	char nKey[256];									// ���݂̃L�[�{�[�h�̓��͏�Ԃ��i�[����nKey��p�ӂ���

	GetHitKeyStateAll(nKey);						// �L�[�{�[�h�̑S�Ă̓��͏�Ԃ�nKey�Ɋi�[

	for (int i = 0; i < 256; i++){
		if (nKey[i] != 0){							// i�Ԃ̃L�[�R�[�h�ɑΉ�����L�[��������Ă�����
			k_Key[i]++;								// �L�[�{�[�h�̑Ή�����L�[�̓��͉񐔂����Z
		}
		else {										// ������Ă��Ȃ����
			k_Key[i] = 0;							// 0�ɂ���
		}
	}

	return 0;										// ����I��0��Ԃ�
}



//----------�w�肳�ꂽ�L�[�R�[�h�̃L�[�̓��͏�Ԃ�Ԃ��֐�----------//

int Controller_c::k_Get(int KeyCode){

	return k_Key[KeyCode];							// KeyCode�ɑΉ�����L�[�̓��͏�Ԃ�Ԃ�
}



//----------�Q�[���p�b�h�̓��͏�Ԃ��L������֐�----------//

int Controller_c::g_Update(){

	int PadInput;									// �Q�[���p�b�h�̓��͏�Ԃ��i�[����PadInput��p��
	int mul = 1;									//

	PadInput = GetJoypadInputState(DX_INPUT_PAD1);	// �Q�[���p�b�h�̓��͏�Ԃ�PadInput�Ɋi�[

	for (int i = 0; i < PAD_MAX; i++){
		if ((PadInput & mul) != 0){					// i�Ԃ̃L�[�R�[�h�ɑΉ�����L�[��������Ă�����
			g_Key[i]++;								// ���Z
		}
		else {										// ������Ă��Ȃ����
			g_Key[i] = 0;							// 0�ɂ���
		}
		mul *= 2;									// mul��2���|����
	}

	return 0;										// ����I��0��Ԃ�
}



//-----c-----//

int Controller_c::g_Get(int KeyCode){

	if (0 <= KeyCode && KeyCode < PAD_MAX){
		return g_Key[KeyCode];						// KeyCode�̓��͏�Ԃ�Ԃ�
	}
	else{
		printfDx("CheckStatePad�ɓn�����l���s���ł�\n");
		return -1;
	}

}

