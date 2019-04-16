#include "define.h"

Control_c Control;
Config_c Config;
Controller_c Controller;
Player_obj Player;
Back_c Back;
Enemy_obj Enemy;
Sound_c Sound;
Effect_c Effect;
Judge_c Judge;
Boss_obj Boss;
menu_c Menu;


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	SetDXArchiveKeyString("mischan");
	SetOutApplicationLogValidFlag(FALSE);
	Config.ConfigDataRead();//�ݒ�̓ǂݍ���
	SetMainWindowText("Don't MIS");
	ChangeWindowMode(Config.window_mode);							
	SetGraphMode(WINDOW_X, WINDOW_Y, WINDOW_COLOR_BIT);	// ��ʂ̑傫����ς���
	if (DxLib_Init() == -1) return -1;					// DX���C�u����������������,�G���[���N������I��
	SetDrawScreen(DX_SCREEN_BACK);						// ����ʂɕ`�悷�邱�Ƃ�����


	//-----�������ݒ肱������-----//


	srand((unsigned)time(NULL));						// �����̏�����

	Control.StartIni();									// �Q�[���N�����Ɉ�x����Ηǂ�������������
	Control.SetMode(title);
	Control.SetLevel('H');//�f�o�b�O�p�A�Q�[���{�҂��璼�ڎn�߂�ׂɕK�v(�����Ɠ�Փx���s��ɂȂ�)
	Control.SetStage(s1_loading);

	//-----�������ݒ肱���܂�-----//

	while (ScreenFlip() == 0							// ����ʂ�\��ʂɔ��f
		&& ProcessMessage() == 0						// ���b�Z�[�W����
		&& ClearDrawScreen() == 0						// ��ʂ��N���A����
		&& Controller.k_Update() == 0					// �L�[�{�[�h�̓��͏�Ԃ��L��
		&& Controller.g_Update() == 0)					// �Q�[���p�b�h�̓��͏�Ԃ��L��
	{
		//-----���C�����[�v��������-----//
		Control.All();									// �Q�[���̗�����Ǘ�����֐�
		//Control.DrawMaskData();							// �f�o�b�O�p�̊֐��̂��ߊ������O�ŏ����K�v����
		//-----���C�����[�v�����܂�-----//
	}

	DxLib_End();										// DX���C�u�����g�p�̏I������

	return 0;											// �\�t�g�̐���I�� 
}