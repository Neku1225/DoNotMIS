#pragma once

class Judge_c {
private:
	bool JudgePS(int s, int t);
	bool JudgePSBoss(int stage, int s);
public:
	bool JudgeES(int s, int t, int plus_range);
	bool JudgeBS(int s, int plus_range);
	void JudgeTouch(int stage);
	void JudgeHitPS(int stage);//���@�V���b�g���G�ɓ�������������
	void JudgeHitES(int stage);//�G�V���b�g�����@�ɓ�������������
	bool JudgePL(int t);
	bool JudgePLBoss(int stage);
	void Loop(int stage);
	void EnemyDeathJudge(int t);
	void JudgeHitPB(int);
	int OutJudge(double x1, double y1, double x2, double y2,
		double range1, double range2, double speed1, double angle1);
};

extern Judge_c Judge;