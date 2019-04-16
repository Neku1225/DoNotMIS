#pragma once

class menu_c {
private:
	int d_count;
	int tx[4];
	int lx[3];
	int back[1];
	int title_logo;
	int title_com;
	int level_select;
public:
	void BackDraw();
	void Title();
	void StaffRoll();
	void SetTx(int, int, int, int);
	void SetLx(int, int, int);
	void SetTCom(int);
	int font[3];
	void StartIni();
};

typedef enum {
	gamestart,
	config,
	credit,
	finish,
	tcom_num,
}title_com;

typedef enum {
	easy,
	normal,
	hard,
	level_num,
	notselect,
}level_select;

extern menu_c Menu;