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
	void PlaySe();//�����Ă���t���O�����ɉ���炷
	void PlayBgm();
	int se_flag[SE_MAX]; //���Ȃ炷�t���O
};

extern Sound_c Sound;