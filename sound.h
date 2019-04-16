#pragma once


class Sound_c{
private:
	int se[SE_MAX];
	int bgm[5];
	int bgm_flag;
public:
	void Pause();
	void Initialize();
	void StartIni();
	void LoadStage(int);
	void PlaySe();//立っているフラグを元に音を鳴らす
	void PlayBgm();
	int se_flag[SE_MAX]; //音ならすフラグ
};

extern Sound_c Sound;