#pragma once

class Back_c{
private:
	int gh[2];
	int stage[3];
	int font[2];
public:
	void DrawBoard();//�X�R�A�{�[�h�̕`��
	void DrawStageNormal();
	void DrawStageBoss();
	void DrawStage();
	void Load(int);//�X�e�[�W�̔w�i�̓ǂݍ���
	void StartIni();
};

extern Back_c Back;