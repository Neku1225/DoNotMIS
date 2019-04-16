#pragma once

class Back_c{
private:
	int gh[2];
	int stage[3];
	int font[2];
public:
	void DrawBoard();//スコアボードの描写
	void DrawStageNormal();
	void DrawStageBoss();
	void DrawStage();
	void Load(int);//ステージの背景の読み込み
	void StartIni();
};

extern Back_c Back;