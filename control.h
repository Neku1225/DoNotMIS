#pragma once

class Control_c{
private:
	bool story_load_flag;
	int state;//state�̓Q�[���{�҂̃X�e�[�W�̏�Ԃ�����
	int mode;//mode�̓^�C�g�����|�[�Y���Q�[���v���C�����Ƃ�����g������
	int retry_com;
	int pause_com;
	char level;
	void Continue();
	void Pause();
	void DrawStopTime();
	void  Story(int);
	int mispic[6];//0:�ʏ� 1:�j�R�j�R 2:��� 3:���f 4:���� 5:����
	int runapic[3];//0:�ʏ� 1: 2:
	int kernpic[2];//0:�ʏ� 1:�}��
	int out[2];
	int last_picture[1];
	int px[3];
	int rx[2];
	int font[4];
	int font_color;
	int highscore[3];
	int scoresave_flag;
	int score;
	int begin_score;//�X�e�[�W�J�n���̃X�R�A
	int begin_erosion;//�X�e�[�W�J�n���̃X�R�A
	int begin_playernum;
	int i = 0, j, ch_i = 0, counter = 0;
	int out_counter;
	int out_mode;
	char str1[100] = "", str2[100] = "", str3[100] = "", str4[100] = "", str5[100] = "", str6[100] = "";//�ʏ��22�����A�G���f�B���O��??����
	int face[50];
	int m_face;
	int r_face;
	int k_face;
	bool m_draw_flag;//�`�ʂ��邩���Ȃ���
	bool r_draw_flag;
	bool k_draw_flag;
	int m_talk_time;
	int r_talk_time;
	int k_talk_time;
	char ch[185][100];
	char name[50][7];
	int ch_max;
	int i_max;
public:
	int blackout_counter;
	int whiteout_counter;
	void Out();
	int level_num;
	int GetScore();
	void SetScore(int);
	int HighScore();
	int ReadHighScore();
	int GetHighScore(int);
	void AddScore(int);
	int g_count;//�G�̏o����U���̃^�C�~���O���w�肷��̂Ɏg��
	void Loop(int);//�����[�v���ƂɌĂяo��
	void Initialize();//�X�e�[�W���n�܂邽�тɍs��������(�G�f�[�^�Ƃ����@�̏����ʒu�Ƃ�)
	void StartIni();//�摜�A���y�Ȃǈ�x�ł������̂̓ǂݍ���
	void LoadStage(int);//�����X�e�[�W���ƂɕK�v�ȗv�f�݂̂̓ǂݍ��݂ɕύX
	void All();
	void ChangeStage();
	void SetLevel(char);
	void SetStage(int);
	void SetMode(int);
	void SetDifficulty();
	void DrawMaskData();
	char GetLevel();
	int erosion;
	int s_change;//�X�e�[�W�̕ύX���K�v���ǂ����������߂Ɏg���ϐ�(�f�o�b�O�p)
	int GetState();
	int GetMode();
	void SetPx(int, int, int);
	void SetRx(int, int);
};

typedef enum {
	s1_loading,  //s1_loading�̓X�e�[�W1�ɕK�v�ȃf�[�^��ǂݍ��ޏ��
	stage1,
	s2_loading,
	stage2,
	s3_loading,
	stage3,
	s4_loading,
	stage4,
	s5_loading,
	stage5,
	s1_talk_f,
	s1_talk_l,
	s2_talk_f,
	s2_talk_l,
	s3_talk_f,
	s3_talk_l,
	s4_talk_f,
	s4_talk_l,
	s5_talk_f,
	s5_talk_l,
} state;

typedef enum{
	title,
	pause,
	retry,
	game_play,
	setting,
	gameover,
	staff_roll,
}mode;

typedef enum {
	playagain,
	rcom_title,
	rcom_num
}retry_com;

typedef enum {
	play,
	stage_retry,
	pcom_title,
	pcom_num
}pause_com;

extern Control_c Control;