#pragma once

//k_�̓L�[�{�[�hg_�̓Q�[���p�b�h

class Config_c{
private:
	char keyname[256][25];
	int font[1];
	void KeyboardConfig(int);
	void PadConfig(int);
	void SettingKey(int*);
	void SettingPad(int*);
	void ChangeWindow();
	int config;
	int kx[10];
	int setting_flag;
public:
	Config_c();
	void StartIni();
	bool window_mode;
	int ConfigDataRead();
	int ConfigDataWrite();
	void Config();
	int g_left, g_up, g_right, g_down, g_shot, g_bom, g_change, g_slow, g_start;
	int k_left, k_up, k_right, k_down, k_shot, k_bom, k_change, k_slow, k_start;
};

class Controller_c{
private:
	// �L�[�̓��͏�Ԋi�[�p�ϐ�
	int k_Key[256];
	int g_Key[PAD_MAX];

public:
	// �����̃L�[�R�[�h�̃L�[�̓��͏�Ԃ�Ԃ�
	int k_Get(int KeyCode);
	int g_Get(int KeyCode);
	// �L�[�̓��͏�Ԃ��X�V����
	int k_Update();
	int g_Update();
};

typedef enum {
	left,
	up,
	right,
	down,
	shot,
	bom,
	change,
	slow,
	start,
	window_size,
	key_num
}config_select;


extern Controller_c Controller;
extern Config_c Config;
