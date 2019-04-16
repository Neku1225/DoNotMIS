#include "define.h"



//----------�Q�[�����ɌJ��Ԃ����鏈�����W�߂��֐�----------//

void Control_c::Loop(int stage){					//�֐��̌Ăяo�����ԂŌ��ʂ��ς��̂Œ���

	Back.DrawBoard();								//

	SetDrawArea(FIELD_X, FIELD_Y, FIELD_X + FIELD_MAX_X, FIELD_Y + FIELD_MAX_Y);//�`��\�G���A��ݒ�

	if (Effect.bright_set.bright != 255) {			//
		SetDrawBright(Effect.bright_set.bright,
			Effect.bright_set.bright,
			Effect.bright_set.bright);	//
	}

	Back.DrawStage();	
	
	SetDrawBright(255, 255, 255);
	Player.Draw();
	if (Effect.bright_set.bright != 255) {			//
		SetDrawBright(Effect.bright_set.bright,	Effect.bright_set.bright,Effect.bright_set.bright);	
	}

	Enemy.Loop();									//
	SetDrawArea(FIELD_X, FIELD_Y, FIELD_X + FIELD_MAX_X, FIELD_Y + FIELD_MAX_Y);//�`��\�G���A��ݒ�
	Boss.Loop(stage);								//

	if (Effect.bright_set.bright != 255) {			//
		SetDrawBright(255, 255, 255);				//
	}
	Player.Loop();
	Judge.Loop(stage);								//
	Effect.Loop();									//

	SetDrawArea(0, 0, 640, 480);//�G���A��߂�

	Boss.DrawHpBar();
	DrawMaskData();

		g_count++;
}


//----------�X�e�[�W�J�n���ƂɕK�v�ȏ�����������֐�---------//

void Control_c::Initialize(){
	g_count = 1;
	begin_erosion = erosion;
	begin_playernum = Player.GetPlayerNum();
	begin_score = score;
	Player.Initialize();
	Enemy.Initialize();
	Effect.Initialize();
}



//----------�Q�[���{�ҊJ�n���Ɏg���������̊֐�----------//

void Control_c::StartIni(){
	ReadHighScore();
	Config.StartIni();
	Sound.StartIni();
	Player.StartIni();
	Boss.StartIni();
	Enemy.StartIni();
	Effect.StartIni();
	Back.StartIni();
	Menu.StartIni();
	out[0] = LoadGraph("material/img/effect/white.png");
	out[1] = LoadGraph("material/img/effect/black.png");
	mispic[0] = LoadGraph("material/img/stand/mis_normal.png");
	mispic[1] = LoadGraph("material/img/stand/mis_smile.png");
	mispic[2] = LoadGraph("material/img/stand/mis_bsmile.png");
	mispic[3] = LoadGraph("material/img/stand/mis_dull.png");
	mispic[4] = LoadGraph("material/img/stand/mis_surprised.png");
	mispic[5] = LoadGraph("material/img/stand/mis_determine.png");
	runapic[0]= LoadGraph("material/img/stand/runa_normal.png");
	runapic[1] = LoadGraph("material/img/stand/runa_hurry.png");
	runapic[2] = LoadGraph("material/img/stand/runa_serious.png");
	kernpic[0] = LoadGraph("material/img/stand/lastboss normal.png");
	kernpic[1] = LoadGraph("material/img/stand/lastboss smile.png");
	font[0] = CreateFontToHandle("Microsoft Sans Serif", 40, -1, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
	font[1] = CreateFontToHandle(NULL, 20, -1, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
	font[2] = CreateFontToHandle(NULL, 16, -1, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);//�V�i���I�Ŏg���t�H���g
	font[3] = CreateFontToHandle("OCRB", 13, -1, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);//�L�������Ŏg���t�H���g
	out_mode = 0;
	erosion = 0;
	s_change = 0;
	score = 0;
	out_counter = 0;
	story_load_flag = false;
	Player.death_count = 0;
}

void Control_c::LoadStage(int stage) {
	Back.Load(stage);
	Sound.LoadStage(stage);
	Enemy.LoadEneBul(stage);
}



//----------���C�����[�v��S�ď�������֐�----------//

void Control_c::All() {

	ChangeStage();										//�X�e�[�W��������f�o�b�O�p�̊֐�(F1�`F5�L�[�ŕύX)
	SetDifficulty();                               //��Փx��������f�o�b�O�p�̊֐�(1�`3�L�[�ŕύX)
	Sound.PlaySe();
	Sound.PlayBgm();
	Sound.Initialize();								//����炷�t���O�����ׂĐ܂�
	switch (mode) {
	case title:
		Menu.Title();
		break;

	case pause:
		Pause();
		break;

	case retry:
		Continue();
		break;

	case setting:
		Config.Config();
		break;

	case gameover:
		DrawStopTime();
		DrawFormatStringToHandle(92, 100, GetColor(255, 255, 255), font[0], "GAME OVER");
		DrawFormatStringToHandle(37, 296, GetColor(255, 255, 255), font[1], "�V���b�g�{�^���Ń^�C�g���ɖ߂�܂�");
		if (Controller.k_Get(Config.k_shot) == 1 || Controller.g_Get(Config.g_shot) == 1) {
			mode = title;
		}
		break;

	case staff_roll:
		Menu.StaffRoll();
		break;

	case game_play:
		switch (state) {
		case s1_loading:
			LoadStage(1);
			Boss.Initialize(1);
			Initialize();  // �X�e�[�W�̊J�n���ƂɕK�v�ȏ�����������
			Enemy.Load_story(level, 1);
			state = s1_talk_f;
			break;

		case s1_talk_f:
			DrawStopTime();
			Story(0);
			break;

		case stage1:
			Loop(1);
			Pause();
			break;

		case s1_talk_l:
			DrawStopTime();
			Story(1);
			break;

		case s2_loading:
			LoadStage(2);
			Initialize();
			Boss.Initialize(2);
			Enemy.Load_story(level, 2);
			state = s2_talk_f;
			break;

		case s2_talk_f:
			DrawStopTime();
			Story(2);
			break;

		case stage2:
			Loop(2);
			Pause();
			break;

		case s2_talk_l:
			DrawStopTime();
			Story(3);
			break;

		case s3_loading:
			LoadStage(3);
			Initialize();
			Boss.Initialize(3);
			Enemy.Load_story(level, 3);
			state = s3_talk_f;
			break;

		case s3_talk_f:
			DrawStopTime();
			Story(4);
			break;

		case stage3:
			Loop(3);
			Pause();
			break;

		case s3_talk_l:
			DrawStopTime();
			Story(5);
			break;

		case s4_loading:
			LoadStage(4);
			Initialize();
			Boss.Initialize(4);
			Enemy.Load_story(level, 4);
			state = s4_talk_f;
			break;

		case s4_talk_f:
			DrawStopTime();
			Story(6);
			break;

		case stage4:
			Loop(4);
			Pause();
			break;

		case s4_talk_l:
			DrawStopTime();
			Story(7);
			break;

		case s5_loading:
			LoadStage(5);
			Initialize();
			Boss.Initialize(5);
			state = s5_talk_f;
			break;

		case s5_talk_f:
			DrawStopTime();
			Story(8);
			break;

		case stage5:
			Loop(5);
			Pause();
			Out();//��ʂ̃u���b�N�A�E�g�A�z���C�g�A�E�g
			break;

		case s5_talk_l:
			Story(9);
			break;

		}
		/*if (erosion >= EROSION_MAX) {
			mode = gameover;
		}*/
		Continue();
		break;
	}
}

void Control_c::Story(int stage) {
	if (story_load_flag == false) {
		m_face = 0;
		r_face = 0;
		k_face = 0;
		m_draw_flag = true;
		r_draw_flag = true;
		k_draw_flag = true;
		story_load_flag = true;
		//1�s�ӂ�̕������Ɋւ���w��
		if (stage == 9) {
			i_max = 98;
		}
		else {
			i_max = 44;
		}
	if (stage == 0) {
		strncpy_s(name[0], "MIS", 5);
		face[0] = 0;
		strncpy_s(ch[0], "����`�H", 44);
		strncpy_s(ch[1], "���������͑S�R�d�������Ȃ��Ȃ��c�c�B", 44);
		strncpy_s(ch[2], "�ǂ������񂾂�H", 44);
		strncpy_s(ch[3], "", 44);
		strncpy_s(name[1], "MIS", 5);
		face[1] = 0;
		strncpy_s(ch[4], "���[��c�c�B", 44);
		strncpy_s(ch[5], "����̊F���Q�����������c�c�B", 44);
		strncpy_s(ch[6], "�����������̂��ȁH", 44);
		strncpy_s(ch[7], "", 44);
		strncpy_s(name[2], "MIS", 5);
		face[2] = 2;
		strncpy_s(ch[8], "�ł��A�܂��������B", 44);
		strncpy_s(ch[9], "���������d���������񂾂���A", 44);
		strncpy_s(ch[10], "�������x�����\�\�\", 44);
		strncpy_s(ch[11], "", 44);
		strncpy_s(name[3], "RUNA", 5);
		face[3] = 1;
		strncpy_s(ch[12], "�݂��[���I�I�@������ˁ[�I�H", 44);
		strncpy_s(ch[13], "", 44);
		strncpy_s(ch[14], "", 44);
		strncpy_s(ch[15], "", 44);
		strncpy_s(name[4], "MIS", 5);
		face[4] = 4;
		strncpy_s(ch[16], "���킟�I�I", 44);
		strncpy_s(ch[17], "���ĉ����A���i����񂩁B", 44);
		strncpy_s(ch[18], "�������Ȃ��ł�[�c�c�����B", 44);
		strncpy_s(ch[19], "", 44);
		strncpy_s(name[5], "RUNA", 5);
		face[5] = 2;
		strncpy_s(ch[20], "�����A����Ȃ����I�I", 44);
		strncpy_s(ch[21], "����ȏ󋵂ŗ��������Ă�����킯���Ȃ���", 44);
		strncpy_s(ch[22], "����I�I", 44);
		strncpy_s(ch[23], "", 44);
		strncpy_s(name[6], "MIS", 5);
		face[6] = 3;
		strncpy_s(ch[24], "�c�c���[���ƁA���i�����H", 44);
		strncpy_s(ch[25], "���������ĉ����C���C�����邱�Ƃł���������", 44);
		strncpy_s(ch[26], "�����H", 44);
		strncpy_s(ch[27], "", 44);
		strncpy_s(name[7], "RUNA", 5);
		face[7] = 1;
		strncpy_s(ch[28], "�c�c�݂��A�A���^�܂����A�����m��Ȃ��́H", 44);
		strncpy_s(ch[29], "", 44);
		strncpy_s(ch[30], "", 44);
		strncpy_s(ch[31], "", 44);
		strncpy_s(name[8], "MIS", 5);
		face[8] = 0;
		strncpy_s(ch[32], "�H�@����B", 44);
		strncpy_s(ch[33], "", 44);
		strncpy_s(ch[34], "", 44);
		strncpy_s(ch[35], "", 44);
		strncpy_s(name[9], "RUNA", 5);
		face[9] = 2;
		strncpy_s(ch[36], "�R�ł���c�c�B", 44);
		strncpy_s(ch[37], "���̃G���g�����̈�厖���Ď��Ɂc�c�B", 44);
		strncpy_s(ch[38], "", 44);
		strncpy_s(ch[39], "", 44);
		strncpy_s(name[10], "RUNA", 5);
		face[10] = 2;
		strncpy_s(ch[40], "�܂�������c�c�B", 44);
		strncpy_s(ch[41], "������������邩��A�悭�����āB", 44);
		strncpy_s(ch[42], "", 44);
		strncpy_s(ch[43], "", 44);
		//Black Out
		strncpy_s(name[11], "RUNA", 5);
		face[11] = 2;
		strncpy_s(ch[44], "�\�\�\���Ă��ƂȂ́B", 44);
		strncpy_s(ch[45], "���������H", 44);
		strncpy_s(ch[46], "", 44);
		strncpy_s(ch[47], "", 44);
		strncpy_s(name[12], "MIS", 5);
		face[12] = 4;
		strncpy_s(ch[48], "�W���}�[���Ă����R���s���[�^�[�E�C���X���A", 44);//MIS
		strncpy_s(ch[49], "���̓s�s�̃l�b�g���[�N���󂵂Ă�H�I", 44);
		strncpy_s(ch[50], "������A�F�̗l�q���ς������񂾁c�c", 44);
		strncpy_s(ch[51], "", 44);
		strncpy_s(name[13], "RUNA", 5);
		face[13] = 1;
		strncpy_s(ch[52], "�C�Â��Ȃ��A���^���A���^�����ǂˁc�c�B", 44);//RUNA
		strncpy_s(ch[53], "", 44);
		strncpy_s(ch[54], "", 44);
		strncpy_s(ch[55], "", 44);
		strncpy_s(name[14], "RUNA", 5);
		face[14] = 2;
		strncpy_s(ch[56], "����ŁA�݂��B", 44);
		strncpy_s(ch[57], "�����͗��݂������ė����́B", 44);
		strncpy_s(ch[58], "", 44);
		strncpy_s(ch[59], "", 44);
		strncpy_s(name[15], "MIS", 5);
		face[15] = 5;
		strncpy_s(ch[60], "���݁H", 44);//MIS
		strncpy_s(ch[61], "", 44);
		strncpy_s(ch[62], "", 44);
		strncpy_s(ch[63], "", 44);
		strncpy_s(name[16], "RUNA", 5);
		face[16] = 2;
		strncpy_s(ch[64], "�����B", 44);//RUNA
		strncpy_s(ch[65], "�A���^�A�m�����N�`���v���O���������͂ō쐬", 44);
		strncpy_s(ch[66], "�ł���̂�ˁH", 44);
		strncpy_s(ch[67], "", 44);
		strncpy_s(name[17], "MIS", 5);
		face[17] = 5;
		strncpy_s(ch[68], "����A�����͂������Ă邯�ǁc�c�B", 44);//MIS
		strncpy_s(ch[69], "", 44);
		strncpy_s(ch[70], "", 44);
		strncpy_s(ch[71], "", 44);
		strncpy_s(name[18], "RUNA", 5);
		face[18] = 0;
		strncpy_s(ch[72], "�������Ă邾���ŏ\����B", 44);
		strncpy_s(ch[73], "", 44);
		strncpy_s(ch[74], "", 44);
		strncpy_s(ch[75], "", 44);
		strncpy_s(name[19], "RUNA", 5);
		face[19] = 0;
		strncpy_s(ch[76], "�G���g�����ɂ͂��������Z�p�������Ă�l���A", 44);
		strncpy_s(ch[77], "���Ȃ��񂾂���B", 44);
		strncpy_s(ch[78], "", 44);
		strncpy_s(ch[79], "", 44);
		strncpy_s(name[20], "MIS", 5);
		face[20] = 3;
		strncpy_s(ch[80], "�\�\�\�܂����A���Ƀ��N�`��������ăW���}�[", 44);
		strncpy_s(ch[81], "�������܂���A���Ă��肢���ɗ����́c�c�H", 44);
		strncpy_s(ch[82], "", 44);
		strncpy_s(ch[83], "", 44);
		strncpy_s(name[21], "RUNA", 5);
		face[21] = 0;
		strncpy_s(ch[84], "�܂��A�v����ɂ����������ƂˁB", 44);
		strncpy_s(ch[85], "", 44);
		strncpy_s(ch[86], "", 44);
		strncpy_s(ch[87], "", 44);
		strncpy_s(name[22], "RUNA", 5);
		face[22] = 0;
		strncpy_s(ch[88], "�l�b�g���[�N�Ń��N�`���𑗂荞�߂Ȃ�����A", 44);
		strncpy_s(ch[89], "���ڂԂ��邵���Ȃ�����ǁB", 44);
		strncpy_s(ch[90], "", 44);
		strncpy_s(ch[91], "", 44);
		strncpy_s(name[23], "MIS", 5);
		face[23] = 4;
		strncpy_s(ch[92], "���₢�₢�₢�△������I�I", 44);
		strncpy_s(ch[93], "�퓬�݂����Ȑ^���Ȃ񂩂������ƂȂ�����I�I", 44);
		strncpy_s(ch[94], "", 44);
		strncpy_s(ch[95], "", 44);
		strncpy_s(name[24], "RUNA", 5);
		face[24] = 2;
		strncpy_s(ch[96], "����Ȃ��Ƃ͕������Ă邯��ǁA", 44);
		strncpy_s(ch[97], "�������Ԃ��Ȃ��̂�c�c�B", 44);
		strncpy_s(ch[98], "", 44);
		strncpy_s(ch[99], "", 44);
		strncpy_s(name[25], "RUNA", 5);
		face[25] = 0;
		strncpy_s(ch[100], "�ق�A�A�^�V���T�|�[�g���邩��B�@�ˁH", 44);
		strncpy_s(ch[101], "", 44);
		strncpy_s(ch[102], "", 44);
		strncpy_s(ch[103], "", 44);
		strncpy_s(name[26], "MIS", 5);
		face[26] = 3;
		strncpy_s(ch[104], "�ށ[�c�c���i����񂪂��������Ȃ�B", 44);
		strncpy_s(ch[105], "����܂�C���i�܂Ȃ����ǁA���傤���Ȃ��A���B", 44);
		strncpy_s(ch[106], "", 44);
		strncpy_s(ch[107], "", 44);
		strncpy_s(name[27], "RUNA", 5);
		face[27] = 0;
		strncpy_s(ch[108], "�݂��c�c���肪�Ƃ��B", 44);
		strncpy_s(ch[109], "���ɒ����B", 44);
		strncpy_s(ch[110], "", 44);
		strncpy_s(ch[111], "", 44);
		strncpy_s(name[28], "MIS", 5);
		face[28] = 0;
		strncpy_s(ch[112], "����A���ꂶ�Ⴀ�����s���Ă����I�I", 44);
		strncpy_s(ch[113], "�����ƃA�V�X�g���Ă�ˁH", 44);
		strncpy_s(ch[114], "", 44);
		strncpy_s(ch[115], "", 44);
		strncpy_s(name[29], "RUNA", 5);
		face[29] = 0;
		strncpy_s(ch[116], "�����A����������I�I", 44);
		strncpy_s(ch[117], "�撣���āI�I", 44);
		strncpy_s(ch[118], "", 44);
		strncpy_s(ch[119], "", 44);

		ch_max = 120;
	}

	if (stage == 1) {
		strncpy_s(name[0], "MIS", 5);
		face[0] = 5;
		strncpy_s(ch[0], "�\�\�\�˂��A���i�����B", 44);
		strncpy_s(ch[1], "�Ō�ɏo�Ă����G���āA���ǉ��������́H", 44);
		strncpy_s(ch[2], "����ς�W���}�[�H", 44);
		strncpy_s(ch[3], "", 44);
		strncpy_s(name[1], "RUNA", 5);
		face[1] = 2;
		strncpy_s(ch[4], "������Ƒ҂��ĂȂ������Ắc�c�B", 44);
		strncpy_s(ch[5], "���A�����̍��Ղ𒲂ׂĂ���񂾂���B", 44);
		strncpy_s(ch[6], "", 44);
		strncpy_s(ch[7], "", 44);
		strncpy_s(name[2], "MIS", 5);
		face[2] = 0;
		strncpy_s(ch[8], "�|����������̂ɒ��ׂ������Ȃ񂾂ˁB", 44);
		strncpy_s(ch[9], "���������I�I", 44);
		strncpy_s(ch[10], "", 44);
		strncpy_s(ch[11], "", 44);
		strncpy_s(name[3], "RUNA", 5);
		face[3] = 0;
		strncpy_s(ch[12], "�����āA���i�̃A�^�V�̎d���́A", 44);
		strncpy_s(ch[13], "��ꂽ�f�[�^�̕�����H", 44);
		strncpy_s(ch[14], "���ꂭ�炢�o���Ȃ��Ăǂ�����̂�B", 44);
		strncpy_s(ch[15], "", 44);
		strncpy_s(name[4], "MIS", 5);
		face[4] = 4;
		strncpy_s(ch[16], "���c�c��������C�Ȃ́H�I", 44);
		strncpy_s(ch[17], "", 44);
		strncpy_s(ch[18], "", 44);
		strncpy_s(ch[19], "", 44);
		strncpy_s(name[5], "RUNA", 5);
		face[5] = 1;
		strncpy_s(ch[20], "��Ȃ킯�Ȃ��ł���[���I�I", 44);
		strncpy_s(ch[21], "��͂��Ă邾����A���E���E���E���I�I", 44);
		strncpy_s(ch[22], "", 44);
		strncpy_s(ch[23], "", 44);
		strncpy_s(name[6], "RUNA", 5);
		face[6] = 2;
		strncpy_s(ch[24], "���ƁA��͂��I������݂����ˁB", 44);
		strncpy_s(ch[25], "�ǂ�ǂ�c�c�B", 44);
		strncpy_s(ch[26], "", 44);
		strncpy_s(ch[27], "", 44);
		strncpy_s(name[7], "RUNA", 5);
		face[7] = 2;
		strncpy_s(ch[28], "���[��c�c�B", 44);
		strncpy_s(ch[29], "�m���ɁA�z�̓W���}�[�ł͂Ȃ��݂����ˁB", 44);
		strncpy_s(ch[30], "", 44);
		strncpy_s(ch[31], "", 44);
		strncpy_s(name[8], "MIS", 5);
		face[8] = 5;
		strncpy_s(ch[32], "���Ⴀ�A���Ȃ́H", 44);
		strncpy_s(ch[33], "", 44);
		strncpy_s(ch[34], "", 44);
		strncpy_s(ch[35], "", 44);
		strncpy_s(name[9], "RUNA", 5);
		face[9] = 2;
		strncpy_s(ch[36], "�ǂ����A�w�����݂����Ȗ����݂����ˁB", 44);
		strncpy_s(ch[37], "�W���}�[�𓮂����悤�ȃv���O�����̎c�[����", 44);
		strncpy_s(ch[38], "����������B", 44);
		strncpy_s(ch[39], "", 44);
		strncpy_s(name[10], "RUNA", 5);
		face[10] = 2;
		strncpy_s(ch[40], "���łɁA�W���}�[���̂̍��Ղ����ׂ����ǁA", 44);
		strncpy_s(ch[41], "�������ē�����悤�ȃv���O�����͌��������", 44);
		strncpy_s(ch[42], "���������B", 44);
		strncpy_s(ch[43], "", 44);
		strncpy_s(name[11], "RUNA", 5);
		face[11] = 2;
		strncpy_s(ch[44], "����A�ԈႢ�Ȃ��񂶂�Ȃ�������B", 44);
		strncpy_s(ch[45], "", 44);
		strncpy_s(ch[46], "", 44);
		strncpy_s(ch[47], "", 44);
		strncpy_s(name[12], "MIS", 5);
		face[12] = 1;
		strncpy_s(ch[48], "���Ⴀ�A�����W���}�[�͎g�����ɂȂ�Ȃ�����", 44);
		strncpy_s(ch[49], "���Ƃ���ˁI�H", 44);
		strncpy_s(ch[50], "�΂񂴁[���I�I", 44);
		strncpy_s(ch[51], "", 44);
		strncpy_s(name[13], "RUNA", 5);
		face[13] = 1;
		strncpy_s(ch[52], "�c�c�܂��A�����Ƃ��������ˁB", 44);
		strncpy_s(ch[53], "���Ȃ��Ƃ������A", 44);
		strncpy_s(ch[54], "�G���A���T�U���Ɋւ��ẮA�����ǁB", 44);
		strncpy_s(ch[55], "", 44);
		strncpy_s(name[14], "MIS", 5);
		face[14] = 4;
		strncpy_s(ch[56], "�����B", 44);
		strncpy_s(ch[57], "", 44);
		strncpy_s(ch[58], "", 44);
		strncpy_s(ch[59], "", 44);
		strncpy_s(name[15], "RUNA", 5);
		face[15] = 2;
		strncpy_s(ch[60], "��͌��ʂɂ��ƁA", 44);
		strncpy_s(ch[61], "�R�C�c���������Ă��W���}�[�́A", 44);
		strncpy_s(ch[62], "�w�G���A���T�U���ɂ���x�W���}�[������B", 44);
		strncpy_s(ch[63], "", 44);
		strncpy_s(name[16], "MIS", 5);
		face[16] = 4;
		strncpy_s(ch[64], "���A�����B", 44);
		strncpy_s(ch[65], "", 44);
		strncpy_s(ch[66], "", 44);
		strncpy_s(ch[67], "", 44);
		strncpy_s(name[17], "RUNA", 5);
		face[17] = 2;
		strncpy_s(ch[68], "���Ԃ��΁A���̃G���A�ɂ������l�ȓz������A", 44);
		strncpy_s(ch[69], "���Ă��ƂɂȂ��ˁB", 44);
		strncpy_s(ch[70], "", 44);
		strncpy_s(ch[71], "", 44);
		strncpy_s(name[18], "MIS", 5);
		face[18] = 4;
		strncpy_s(ch[72], "���A���A�����B", 44);
		strncpy_s(ch[73], "", 44);
		strncpy_s(ch[74], "", 44);
		strncpy_s(ch[75], "", 44);
		strncpy_s(name[19], "RUNA", 5);
		face[19] = 2;
		strncpy_s(ch[76], "���傤���Ȃ��ł���c�c�B", 44);
		strncpy_s(ch[77], "�����A�݂��I�I", 44);
		strncpy_s(ch[78], "�������Ǝ��ɍs�����I�I", 44);
		strncpy_s(ch[79], "", 44);
		strncpy_s(name[20], "MIS", 5);
		face[20] = 3;
		strncpy_s(ch[80], "���`�I�I", 44);
		strncpy_s(ch[81], "����ς�A�܂����Ȃ��ƃ_���Ȃ́`�H�I", 44);
		strncpy_s(ch[82], "", 44);
		strncpy_s(ch[83], "", 44);

			ch_max = 84;
		}

	if (stage == 2) {
		strncpy_s(name[0], "MIS", 5);
		face[0] = 3;
		strncpy_s(ch[0], "���킟�c�c�G���񑝂��Ă�B", 44);
		strncpy_s(ch[1], "", 44);
		strncpy_s(ch[2], "", 44);
		strncpy_s(ch[3], "", 44);
		strncpy_s(name[1], "RUNA", 5);
		face[1] = 0;
		strncpy_s(ch[4], "�G���A���C�[�X�^���\�\�\", 44);
		strncpy_s(ch[5], "�G���g�����S�̂ōl������A", 44);
		strncpy_s(ch[6], "����Ȃɏd�v�ȏ��͎�舵���ĂȂ����ǁB", 44);
		strncpy_s(ch[7], "�G���A���T�U���ɔ�ׂ���˂��c�c�B", 44);
		strncpy_s(name[2], "MIS", 5);
		face[2] = 2;
		strncpy_s(ch[8], "�G���A���T�U���́A�Q�[���Ƃ��C���X�g�Ƃ�", 44);
		strncpy_s(ch[9], "���y�Ƃ��̃f�[�^�������Ȃ�����ˁB", 44);
		strncpy_s(ch[10], "���̖{�Ƃ��A���y�f�[�^�̊Ǘ������B", 44);
		strncpy_s(ch[11], "", 44);
		strncpy_s(name[3], "RUNA", 5);
		face[3] = 2;
		strncpy_s(ch[12], "�܂��A�W���}�[�������Ă���͎̂�����B", 44);
		strncpy_s(ch[13], "�C���������߂āB", 44);
		strncpy_s(ch[14], "", 44);
		strncpy_s(ch[15], "", 44);
		strncpy_s(name[4], "MIS", 5);
		face[4] = 0;
		strncpy_s(ch[16], "�ށ[�c�c�����B", 44);
		strncpy_s(ch[17], "���Ⴀ�A�܂��s���Ă���ˁI�I", 44);
		strncpy_s(ch[18], "", 44);
		strncpy_s(ch[19], "", 44);
		strncpy_s(name[5], "RUNA", 5);
		face[5] = 0;
		strncpy_s(ch[20], "��낵�����ނ�I�I", 44);
		strncpy_s(ch[21], "", 44);
		strncpy_s(ch[22], "", 44);
		strncpy_s(ch[23], "", 44);
		//Margin
		face[6] = 5;
		strncpy_s(name[6], "MIS", 5);
		strncpy_s(ch[24], "��c�c�H", 44);
		strncpy_s(ch[25], "�W���}�[�����������Ă��Ƃ�", 44);
		strncpy_s(ch[26], "������w����������X�Ɂc�c", 44);
		strncpy_s(ch[27], "���A����l���Ȃ����Ƃɂ�����ƁB", 44);

			ch_max = 28;
		}

	if (stage == 3) {
		strncpy_s(name[0], "MIS", 5);
		face[0] = 3;
		strncpy_s(ch[0], "����ς�A�{�X�����Ȃ��Ă邶���c�c", 44);
		strncpy_s(ch[1], "", 44);
		strncpy_s(ch[2], "", 44);
		strncpy_s(ch[3], "", 44);
		strncpy_s(name[1], "RUNA", 5);
		face[1] = 1;
		strncpy_s(ch[4], "�����A�������������Ă���񂾂���A", 44);
		strncpy_s(ch[5], "��荂�x�ɍ\������Ă���Ɍ��܂��Ă���ł�", 44);
		strncpy_s(ch[6], "��B", 44);
		strncpy_s(ch[7], "", 44);
		strncpy_s(name[2], "MIS", 5);
		face[2] = 2;
		strncpy_s(ch[8], "����A����ȋC�͔��X�����Ă����ǂˁI�I", 44);
		strncpy_s(ch[9], "����ł��A������Ɗ��҂���������񂾂�I�I", 44);
		strncpy_s(ch[10], "", 44);
		strncpy_s(ch[11], "", 44);
		strncpy_s(name[3], "RUNA", 5);
		face[3] = 0;
		strncpy_s(ch[12], "�܂��܂��B", 44);
		strncpy_s(ch[13], "�ł��A���͂Ƃ�����A", 44);
		strncpy_s(ch[14], "�G���A���C�[�X�^������i�����ĂƂ���ˁB", 44);
		strncpy_s(ch[15], "", 44);
		strncpy_s(name[4], "RUNA", 5);
		face[4] = 0;
		strncpy_s(ch[16], "���Ďc��̓E�F�X�^�����m�[�U�������ǁc�c�B", 44);
		strncpy_s(ch[17], "", 44);
		strncpy_s(ch[18], "", 44);
		strncpy_s(ch[19], "", 44);
		strncpy_s(name[5], "MIS", 5);
		face[5] = 5;
		strncpy_s(ch[20], "���́A�E�F�X�^���̕��������񂶂�Ȃ����ȁB", 44);
		strncpy_s(ch[21], "�m�[�U���́A", 44);
		strncpy_s(ch[22], "�d�v�ȂƂ���΂����肠����ĕ������c�c�B", 44);
		strncpy_s(ch[23], "�߂��Ⴍ����G�����Ȃ��Ă邾�낤���c�c�B", 44);
		strncpy_s(name[6], "RUNA", 5);
		face[6] = 2;
		strncpy_s(ch[24], "�ǂ����A�ǂ������s���Ȃ���Ȃ�Ȃ��񂾂�", 44);
		strncpy_s(ch[25], "�ǁc�c�B", 44);
		strncpy_s(ch[26], "�݂��A�������Ă�H", 44);
		strncpy_s(ch[27], "", 44);
		strncpy_s(name[7], "MIS", 5);
		face[7] = 3;
		strncpy_s(ch[28], "�������Ă邯�ǂ��`�c�c", 44);
		strncpy_s(ch[29], "", 44);
		strncpy_s(ch[30], "", 44);
		strncpy_s(ch[31], "", 44);
		strncpy_s(name[8], "MIS", 5);
		face[8] = 0;
		strncpy_s(ch[32], "�c�c����B", 44);
		strncpy_s(ch[33], "����ς�G���A���C�[�X�^������̕�����ɂ�", 44);
		strncpy_s(ch[34], "�悤�B", 44);
		strncpy_s(ch[35], "", 44);
		strncpy_s(name[9], "MIS", 5);
		face[9] = 0;
		strncpy_s(ch[36], "�����̎��͂��ÂɌ��ɂ߂�̂͑厖����B", 44);
		strncpy_s(ch[37], "����B", 44);
		strncpy_s(ch[38], "", 44);
		strncpy_s(ch[39], "", 44);
		strncpy_s(name[10], "RUNA", 5);
		face[10] = 0;
		strncpy_s(ch[40], "�݂����A�����������}�g���Ȃ��ƌ����Ă�C��", 44);
		strncpy_s(ch[41], "�����c�c", 44);
		strncpy_s(ch[42], "", 44);
		strncpy_s(ch[43], "", 44);

			ch_max = 44;
		}

	if (stage == 4) {
		strncpy_s(name[0], "RUNA", 5);
		face[0] = 0;
		strncpy_s(ch[0], "���āA�G���A���E�F�X�^���ɒ�������ˁB", 44);
		strncpy_s(ch[1], "", 44);
		strncpy_s(ch[2], "", 44);
		strncpy_s(ch[3], "", 44);
		strncpy_s(name[1], "MIS", 5);
		face[1] = 5;
		strncpy_s(ch[4], "����[�H", 44);
		strncpy_s(ch[5], "�W���}�[���E�W���E�W������Ǝv���Ă��̂ɁB", 44);
		strncpy_s(ch[6], "����A�G���A���T�U���Ɠ������炢�̐�������", 44);
		strncpy_s(ch[7], "�Ȃ���H", 44);
		strncpy_s(name[2], "RUNA", 5);
		face[2] = 2;
		strncpy_s(ch[8], "�����c�c�����ˁB", 44);
		strncpy_s(ch[9], "�����́A�G���A���m�[�U���ɂ͋y�΂Ȃ����ǁA", 44);
		strncpy_s(ch[10], "�G���g�����ł��L���̏d�v�n��Ȃ̂Ɂc�c�B", 44);
		strncpy_s(ch[11], "����������c�c�B", 44);
		strncpy_s(name[3], "MIS", 5);
		face[3] = 1;
		strncpy_s(ch[12], "���[��B", 44);
		strncpy_s(ch[13], "�P���Ɏ����������b�L�[�������񂶂�Ȃ��H", 44);
		strncpy_s(ch[14], "", 44);
		strncpy_s(ch[15], "", 44);
		strncpy_s(name[4], "MIS", 5);
		face[3] = 1;
		strncpy_s(ch[16], "�ق�A���Ƃ������̍s�����������I�I", 44);
		strncpy_s(ch[17], "", 44);
		strncpy_s(ch[18], "", 44);
		strncpy_s(ch[19], "", 44);
		strncpy_s(name[5], "RUNA", 5);
		face[4] = 1;
		strncpy_s(ch[20], "����ȒP���ȁc�c�B", 44);
		strncpy_s(ch[21], "�A�^�V�͉������L�i�L�������������Ȃ����H", 44);
		strncpy_s(ch[22], "", 44);
		strncpy_s(ch[23], "", 44);
		strncpy_s(name[6], "MIS", 5);
		face[5] = 1;
		strncpy_s(ch[24], "���i�����̍l����������`�I�I", 44);
		strncpy_s(ch[25], "���v�A���v�I�I", 44);
		strncpy_s(ch[26], "", 44);
		strncpy_s(ch[27], "", 44);
		strncpy_s(name[7], "MIS", 5);
		face[6] = 0;
		strncpy_s(ch[28], "���Ⴀ�A�����n�߂��Ⴈ�����ȁB", 44);
		strncpy_s(ch[29], "����ȃ`�����X�͐������Ȃ��ƂˁI�I", 44);
		strncpy_s(ch[30], "", 44);
		strncpy_s(ch[31], "", 44);
		strncpy_s(name[8], "RUNA", 5);
		face[7] = 1;
		strncpy_s(ch[32], "�����A�݂��I�I", 44);
		strncpy_s(ch[33], "�\�\�\���āA�����s����������B", 44);
		strncpy_s(ch[34], "", 44);
		strncpy_s(ch[35], "", 44);
		strncpy_s(name[9], "RUNA", 5);
		face[8] = 2;
		strncpy_s(ch[36], "�m���ɁA�݂��̌����ʂ莄�̍l���߂���������", 44);
		strncpy_s(ch[37], "�Ȃ����ǁc�c�B", 44);
		strncpy_s(ch[38], "", 44);
		strncpy_s(ch[39], "", 44);
		strncpy_s(name[10], "RUNA", 5);
		face[9] = 2;
		strncpy_s(ch[40], "�z���g�ɑ��v������c�c�B", 44);
		strncpy_s(ch[41], "", 44);
		strncpy_s(ch[42], "", 44);
		strncpy_s(ch[43], "", 44);

			ch_max = 44;
		}

	if (stage == 5) {
		strncpy_s(name[0], "MIS", 5);
		face[0] = 3;
		strncpy_s(ch[0], "�c�c�G�O���B", 44);
		strncpy_s(ch[1], "���ɃG�O���B", 44);
		strncpy_s(ch[2], "", 44);
		strncpy_s(ch[3], "", 44);
		strncpy_s(name[1], "RUNA", 5);
		face[1] = 2;
		strncpy_s(ch[4], "����ς�A", 44);
		strncpy_s(ch[5], "�W���}�[�̃v���O�������X�V����Ă�c�c�B", 44);
		strncpy_s(ch[6], "", 44);
		strncpy_s(ch[7], "", 44);
		strncpy_s(name[2], "RUNA", 5);
		face[2] = 2;
		strncpy_s(ch[8], "�A�^�V�������h��ɂ���Ă�̂��A", 44);
		strncpy_s(ch[9], "�������������������Ă邾���Ȃ킯���Ȃ����B", 44);
		strncpy_s(ch[10], "", 44);
		strncpy_s(ch[11], "", 44);
		strncpy_s(name[3], "MIS", 5);
		face[3] = 3;
		strncpy_s(ch[12], "�f�X���l�[�c�c�B", 44);
		strncpy_s(ch[13], "", 44);
		strncpy_s(ch[14], "", 44);
		strncpy_s(ch[15], "", 44);
		strncpy_s(name[4], "RUNA", 5);
		face[4] = 2;
		strncpy_s(ch[16], "�ł��A����Ǝ��ōŌ�B", 44);
		strncpy_s(ch[17], "�c��̓G���A���m�[�U��������B", 44);
		strncpy_s(ch[18], "", 44);
		strncpy_s(ch[19], "", 44);
		strncpy_s(name[5], "RUNA", 5);
		face[5] = 2;
		strncpy_s(ch[20], "�G���A���m�[�U���\�\�\", 44);
		strncpy_s(ch[21], "�l�b�g���[�N�̈ꕔ�̊Ǘ����C����Ă�����A", 44);
		strncpy_s(ch[22], "�@��������舵������c�c", 44);
		strncpy_s(ch[23], "�܂��A�e�����X�g���D�݂����Ȓn��ˁB", 44);
		strncpy_s(name[6], "RUNA", 5);
		face[6] = 2;
		strncpy_s(ch[24], "�c��̓G���W�����Ă邱�ƊԈႢ�Ȃ��A", 44);
		strncpy_s(ch[25], "���Ċ����B", 44);
		strncpy_s(ch[26], "", 44);
		strncpy_s(ch[27], "", 44);
		strncpy_s(name[7], "MIS", 5);
		face[7] = 5;
		strncpy_s(ch[28], "����c�c�B", 44);
		strncpy_s(ch[29], "�ł��A�㉹�΂�����f���Ă������ς��Ȃ���", 44);
		strncpy_s(ch[30], "��ˁB", 44);
		strncpy_s(ch[31], "", 44);
		strncpy_s(name[8], "MIS", 5);
		face[8] = 5;
		strncpy_s(ch[32], "���邾������Ă݂��B", 44);
		strncpy_s(ch[33], "", 44);
		strncpy_s(ch[34], "", 44);
		strncpy_s(ch[35], "", 44);
		strncpy_s(name[9], "RUNA", 5);
		face[9] = 0;
		strncpy_s(ch[36], "���邾���A����Ȃ��ł���B", 44);
		strncpy_s(ch[37], "��肫��Ȃ��ƃ_����H", 44);
		strncpy_s(ch[38], "", 44);
		strncpy_s(ch[39], "", 44);
		strncpy_s(name[10], "MIS", 5);
		face[10] = 0;
		strncpy_s(ch[40], "�c�c�������ˁB", 44);
		strncpy_s(ch[41], "���Ⴀ�A��肫���Č������I�I", 44);
		strncpy_s(ch[42], "", 44);
		strncpy_s(ch[43], "", 44);
		strncpy_s(name[11], "RUNA", 5);
		face[11] = 0;
		strncpy_s(ch[44], "�����A�������̕���������B", 44);
		strncpy_s(ch[45], "", 44);
		strncpy_s(ch[46], "", 44);
		strncpy_s(ch[47], "", 44);
		strncpy_s(name[12], "RUNA", 5);
		face[12] = 0;
		strncpy_s(ch[48], "�c�c���ꂶ�Ⴀ�A�s�����I�I", 44);
		strncpy_s(ch[49], "", 44);
		strncpy_s(ch[50], "", 44);
		strncpy_s(ch[51], "", 44);
		strncpy_s(name[13], "MIS", 5);
		face[13] = 1;
		strncpy_s(ch[52], "���b�c�E�S�[�I�I", 44);
		strncpy_s(ch[53], "", 44);
		strncpy_s(ch[54], "", 44);
		strncpy_s(ch[55], "", 44);

			ch_max = 56;
		}

	if (stage == 6) {
		strncpy_s(name[0], "RUNA", 5);
		face[0] = 2;
		strncpy_s(ch[0], "�o��͂��Ă����ǁc�c�B", 44);
		strncpy_s(ch[1], "����́c�c�}�Y�C��ˁc�c�B", 44);
		strncpy_s(ch[2], "", 44);
		strncpy_s(ch[3], "", 44);
		strncpy_s(name[1], "MIS", 5);
		face[1] = 5;
		strncpy_s(ch[4], "�W���}�[���炵�Ă��A", 44);
		strncpy_s(ch[5], "�ŏI�h�q���C���݂����Ȋ����Ȃ̂��ȁB", 44);
		strncpy_s(ch[6], "", 44);
		strncpy_s(ch[7], "", 44);
		strncpy_s(name[2], "RUNA", 5);
		face[2] = 2;
		strncpy_s(ch[8], "�ł��傤�ˁB", 44);
		strncpy_s(ch[9], "�����z��ɂ͂��������c���ĂȂ��킯�����B", 44);
		strncpy_s(ch[10], "", 44);
		strncpy_s(ch[11], "", 44);
		strncpy_s(name[3], "RUNA", 5);
		face[3] = 2;
		strncpy_s(ch[12], "�ǂ�����́H", 44);
		strncpy_s(ch[13], "��U�߂��āA����c������Ď��������H", 44);
		strncpy_s(ch[14], "", 44);
		strncpy_s(ch[15], "", 44);
		strncpy_s(name[4], "MIS", 5);
		face[4] = 5;
		strncpy_s(ch[16], "�{���͂������������ǁc�c�B", 44);
		strncpy_s(ch[17], "�������Ă���ɂ��A�G���g�����̃l�b�g���[�N", 44);
		strncpy_s(ch[18], "�͐N�H���ꑱ���Ă���񂾂�H", 44);
		strncpy_s(ch[19], "", 44);
		strncpy_s(name[5], "MIS", 5);
		face[5] = 5;
		strncpy_s(ch[20], "�����l������A", 44);
		strncpy_s(ch[21], "�����ɂł��s���ׂ��Ȃ񂾂Ǝv���B", 44);
		strncpy_s(ch[22], "", 44);
		strncpy_s(ch[23], "", 44);
		strncpy_s(name[6], "RUNA", 5);
		face[6] = 0;
		strncpy_s(ch[24], "�ւ��c�c�B", 44);
		strncpy_s(ch[25], "�݂��A�A���^�����ȃR�g�����悤�ɂȂ�����", 44);
		strncpy_s(ch[26], "��Ȃ��H", 44);
		strncpy_s(ch[27], "", 44);
		strncpy_s(name[7], "MIS", 5);
		face[7] = 3;
		strncpy_s(ch[28], "����ȁ[�B", 44);
		strncpy_s(ch[29], "���܂ł��A�q������Ȃ��ł���[���I�I", 44);
		strncpy_s(ch[30], "", 44);
		strncpy_s(ch[31], "", 44);
		strncpy_s(name[8], "RUNA", 5);
		face[8] = 0;
		strncpy_s(ch[32], "���������Ƃ��낪�q�����ۂ��́B", 44);
		strncpy_s(ch[33], "", 44);
		strncpy_s(ch[34], "", 44);
		strncpy_s(ch[35], "", 44);
		strncpy_s(name[9], "MIS", 5);
		face[9] = 3;
		strncpy_s(ch[36], "�������B", 44);
		strncpy_s(ch[37], "", 44);
		strncpy_s(ch[38], "", 44);
		strncpy_s(ch[39], "", 44);
		strncpy_s(name[10], "RUNA", 5);
		face[10] = 0;
		strncpy_s(ch[40], "�c�c�ł��o��͌��܂����悤�ˁB", 44);
		strncpy_s(ch[41], "", 44);
		strncpy_s(ch[42], "", 44);
		strncpy_s(ch[43], "", 44);
		strncpy_s(name[11], "MIS", 5);
		face[11] = 5;
		strncpy_s(ch[44], "�c�c�B", 44);
		strncpy_s(ch[45], "", 44);
		strncpy_s(ch[46], "", 44);
		strncpy_s(ch[47], "", 44);
		strncpy_s(name[12], "RUNA", 5);
		face[12] = 2;
		strncpy_s(ch[48], "�݂��c�c��΂ɁA�����ŋA���Ă��āB", 44);
		strncpy_s(ch[49], "��΂�����b�c�c�I�I", 44);
		strncpy_s(ch[50], "", 44);
		strncpy_s(ch[51], "", 44);
		strncpy_s(name[13], "MIS", 5);
		face[13] = 0;
		strncpy_s(ch[52], "�c�c����A���������B", 44);
		strncpy_s(ch[53], "�񑩂���I�I", 44);
		strncpy_s(ch[54], "", 44);
		strncpy_s(ch[55], "", 44);

			ch_max = 56;
		}

	if (stage == 7) {
		strncpy_s(name[0], "MIS", 5);
		face[0] = 0;
		strncpy_s(ch[0], "����̃W���}�[�������Ȃ��Ȃ����c�c", 44);
		strncpy_s(ch[1], "���Ă��Ƃ́A���������āc�c�I�I", 44);
		strncpy_s(ch[2], "", 44);
		strncpy_s(ch[3], "", 44);
		strncpy_s(name[1], "MIS", 5);
		face[1] = 1;
		strncpy_s(ch[4], "��A������c�c�I�H", 44);
		strncpy_s(ch[5], "", 44);
		strncpy_s(ch[6], "", 44);
		strncpy_s(ch[7], "", 44);
		strncpy_s(name[2], "MIS", 5);
		face[2] = 1;
		strncpy_s(ch[8], "���A�{�X��|�����́c�c�H", 44);
		strncpy_s(ch[9], "���A�G���g��������ꂽ�́c�c�H", 44);
		strncpy_s(ch[10], "", 44);
		strncpy_s(ch[11], "", 44);
		strncpy_s(name[3], "MIS", 5);
		face[3] = 2;
		strncpy_s(ch[12], "�c�c����B", 44);
		strncpy_s(ch[13], "���ƃ��i�����Ƃ̖񑩂���ꂽ���B", 44);
		strncpy_s(ch[14], "", 44);
		strncpy_s(ch[15], "", 44);
		strncpy_s(name[4], "MIS", 5);
		face[4] = 2;
		strncpy_s(ch[16], "�������`�A�ǂ��������������`�I�I", 44);
		strncpy_s(ch[17], "�������A�悵�A�����ɂł��߂���I�I", 44);
		strncpy_s(ch[18], "", 44);
		strncpy_s(ch[19], "", 44);
		strncpy_s(ch[20], "�c�c�B", 44);
		strncpy_s(ch[21], "�c�c�B", 44);
		strncpy_s(ch[22], "�c�c�B", 44);
		strncpy_s(ch[23], "�c�c�B", 44);
		strncpy_s(name[6], "???", 5);
		strncpy_s(ch[24], "�c�c�}�T�J�A�S�Ńg�n�B", 44);
		strncpy_s(ch[25], "�c�c�S�N�B", 44);
		strncpy_s(ch[26], "�S�N�A�g�G�i�C���S�h���_�c�c�B", 44);
		strncpy_s(ch[27], "", 44);
		//Black Out
		strncpy_s(name[7], "RUNA", 5);
		face[7] = 2;
		strncpy_s(ch[28], "�e�n�̃W���}�[���ċN���H�I", 44);
		strncpy_s(ch[29], "�����N�����Ă�́H�I", 44);
		strncpy_s(ch[30], "", 44);
		strncpy_s(ch[31], "", 44);
		strncpy_s(name[8], "MIS", 5);
		face[8] = 1;
		strncpy_s(ch[32], "���i����[��I�I", 44);
		strncpy_s(ch[33], "���Ƃ��A�{�X�̂��Ɠ|���\�\�\", 44);
		strncpy_s(ch[34], "���āA�ǂ������́H", 44);
		strncpy_s(ch[35], "", 44);
		strncpy_s(name[9], "RUNA", 5);
		face[9] = 0;
		strncpy_s(ch[36], "�݂��I�I", 44);
		strncpy_s(ch[37], "�ǂ������A�����������̂ˁc�c�B", 44);
		strncpy_s(ch[38], "", 44);
		strncpy_s(ch[39], "", 44);
		strncpy_s(name[10], "MIS", 5);
		face[10] = 2;
		strncpy_s(ch[40], "����A�M���M�����������ǂˁB", 44);
		strncpy_s(ch[41], "������ǂ����čQ�ĂĂ�́H", 44);
		strncpy_s(ch[42], "", 44);
		strncpy_s(ch[43], "", 44);
		strncpy_s(name[11], "RUNA", 5);
		face[11] = 2;
		strncpy_s(ch[44], "���ꂪ�ˁc�c�B", 44);
		strncpy_s(ch[45], "�{�X�ɂ�铝���������ċ@�\��~���Ă��͂���", 44);
		strncpy_s(ch[46], "�W���}�[���A�������ĊJ�����݂����Ȃ̂�B", 44);
		strncpy_s(ch[47], "", 44);
		strncpy_s(name[12], "MIS", 5);
		face[12] = 4;
		strncpy_s(ch[48], "�������H�I�@���ŁH�I", 44);
		strncpy_s(ch[49], "�W���}�[���Ė��߂��Ȃ��ƁA", 44);
		strncpy_s(ch[50], "�����Ȃ��񂶂�c�c�B", 44);
		strncpy_s(ch[51], "", 44);
		strncpy_s(name[13], "RUNA", 5);
		face[13] = 2;
		strncpy_s(ch[52], "����͊ԈႢ�Ȃ��͂���B", 44);
		strncpy_s(ch[53], "�A�^�V�A��͂ɂ͎��M�����邩��B", 44);
		strncpy_s(ch[54], "", 44);
		strncpy_s(ch[55], "", 44);
		strncpy_s(name[14], "MIS", 5);
		face[14] = 3;
		strncpy_s(ch[56], "���Ƃ���ƁA�܂����c�c�B", 44);
		strncpy_s(ch[57], "", 44);
		strncpy_s(ch[58], "", 44);
		strncpy_s(ch[59], "", 44);
		strncpy_s(name[15], "RUNA", 5);
		face[15] = 1;
		strncpy_s(ch[60], "�����A���́w�܂����x��B", 44);
		strncpy_s(ch[61], "", 44);
		strncpy_s(ch[62], "", 44);
		strncpy_s(ch[63], "", 44);
		strncpy_s(name[16], "RUNA", 5);
		face[16] = 1;
		strncpy_s(ch[64], "�V�������ߎ҂��A�ǂ����ɂ���\��������", 44);
		strncpy_s(ch[65], "������B", 44);
		strncpy_s(ch[66], "", 44);
		strncpy_s(ch[67], "", 44);
		strncpy_s(name[17], "MIS", 5);
		face[17] = 3;
		strncpy_s(ch[68], "���A����Ȃ��c�c�B", 44);
		strncpy_s(ch[69], "", 44);
		strncpy_s(ch[70], "", 44);
		strncpy_s(ch[71], "", 44);
		strncpy_s(name[18], "RUNA", 5);
		face[18] = 2;
		strncpy_s(ch[72], "���̓\�C�c���ǂ��ɂ��邩���Ă��Ƃ����ǁA", 44);
		strncpy_s(ch[73], "�c�c���ƁA�܂�����B", 44);
		strncpy_s(ch[74], "", 44);
		strncpy_s(ch[75], "", 44);
		strncpy_s(name[19], "MIS", 5);
		face[19] = 5;
		strncpy_s(ch[76], "��A���i�����H", 44);
		strncpy_s(ch[77], "�������������́H", 44);
		strncpy_s(ch[78], "", 44);
		strncpy_s(ch[79], "", 44);
		strncpy_s(name[20], "RUNA", 5);
		face[20] = 1;
		strncpy_s(ch[80], "���₳��������A", 44);
		strncpy_s(ch[81], "���낤���Đ����Ă�l�b�g���[�N��ʂ��āA", 44);
		strncpy_s(ch[82], "�W���}�[�̓����𒲂ׂĂ����񂾂��ǁc�c�B", 44);
		strncpy_s(ch[83], "1�C�ɂȂ�Ƃ��낪����̂�B", 44);
		strncpy_s(name[21], "MIS", 5);
		face[21] = 5;
		strncpy_s(ch[84], "�Ƃ����ƁH", 44);
		strncpy_s(ch[85], "", 44);
		strncpy_s(ch[86], "", 44);
		strncpy_s(ch[87], "", 44);
		strncpy_s(name[22], "RUNA", 5);
		face[22] = 2;
		strncpy_s(ch[88], "�c�c�ǂ����A�W���}�[�������Ƃ����ڎw����", 44);
		strncpy_s(ch[89], "�W�܂��Ă��Ă���݂����Ȃ́B", 44);
		strncpy_s(ch[90], "", 44);
		strncpy_s(ch[91], "", 44);
		strncpy_s(name[23], "MIS", 5);
		face[23] = 3;
		strncpy_s(ch[92], "�W���H�I", 44);
		strncpy_s(ch[93], "�c�c����ŁA���̏ꏊ�́H", 44);
		strncpy_s(ch[94], "", 44);
		strncpy_s(ch[95], "", 44);
		strncpy_s(name[24], "RUNA", 5);
		face[24] = 1;
		strncpy_s(ch[96], "�m���A���̍��W�n�_�ɂ������̂́\�\�\", 44);
		strncpy_s(ch[97], "", 44);
		strncpy_s(ch[98], "", 44);
		strncpy_s(ch[99], "", 44);
		strncpy_s(name[25], "RUNA", 5);
		face[25] = 2;
		strncpy_s(ch[100], "�\�\�\�Z���g�����E�^���[�H", 44);
		strncpy_s(ch[101], "", 44);
		strncpy_s(ch[102], "", 44);
		strncpy_s(ch[103], "", 44);


		ch_max = 104;
	}

	if (stage == 8) {
		strncpy_s(name[0], "MIS", 5);
		face[0] = 3;
		strncpy_s(ch[0], "�r���S�݂����B", 44);
		strncpy_s(ch[1], "�W���}�[���^���[�����͂�ł��c�c�B", 44);
		strncpy_s(ch[2], "", 44);
		strncpy_s(ch[3], "", 44);
		strncpy_s(name[1], "RUNA", 5);
		face[1] = 2;
		strncpy_s(ch[4], "�^���[�̐E�����F�A���Ă���c�c�B", 44);
		strncpy_s(ch[5], "", 44);
		strncpy_s(ch[6], "", 44);
		strncpy_s(ch[7], "", 44);
		strncpy_s(name[2], "MIS", 5);
		face[2] = 5;
		strncpy_s(ch[8], "���΂ɁA���ꂾ���̐��̃W���}�[��S���|����", 44);
		strncpy_s(ch[9], "�͖���������A�����Ƃ��{���̃��X�{�X������", 44);
		strncpy_s(ch[10], "���Ȃ��Ɓc�c�B", 44);
		strncpy_s(ch[11], "", 44);
		strncpy_s(name[3], "RUNA", 5);
		face[3] = 2;
		strncpy_s(ch[12], "�����B", 44);
		strncpy_s(ch[13], "�l�b�g���[�N�̐N�H���i��ł��Ă邵�c�c�B", 44);
		strncpy_s(ch[14], "", 44);
		strncpy_s(ch[15], "", 44);
		strncpy_s(name[4], "MIS", 5);
		face[4] = 3;
		strncpy_s(ch[16], "���[�A�������Ԃ��Ȃ��I�I", 44);
		strncpy_s(ch[17], "�������ƃ��X�{�X�o�ė��\���I�I", 44);
		strncpy_s(ch[18], "", 44);
		strncpy_s(ch[19], "", 44);
		strncpy_s(name[5], "RUNA", 5);
		face[5] = 1;
		strncpy_s(ch[20], "�����A����Ȃ��Ƃŏo�ė���킯�ȁ\�\�\", 44);
		strncpy_s(ch[21], "", 44);
		strncpy_s(ch[22], "", 44);
		strncpy_s(ch[23], "", 44);
		strncpy_s(name[6], "???", 5);
		strncpy_s(ch[24], "�c�c�M�l���_�i�H", 44);
		strncpy_s(ch[25], "���m�v�惒�R�g�S�g�N�ז��V�^�m�n�B", 44);
		strncpy_s(ch[26], "", 44);
		strncpy_s(ch[27], "", 44);
		strncpy_s(name[7], "RUNA", 5);
		face[7] = 2;
		strncpy_s(ch[28], "���I�I�@�N�H�I", 44);
		strncpy_s(ch[29], "", 44);
		strncpy_s(ch[30], "", 44);
		strncpy_s(ch[31], "", 44);
		strncpy_s(name[8], "MIS", 5);
		face[8] = 4;
		strncpy_s(ch[32], "�����A���i�����I�I", 44);
		strncpy_s(ch[33], "��I�I�@�^���[�̒���ɁI�I", 44);
		strncpy_s(ch[34], "", 44);
		strncpy_s(ch[35], "", 44);
		strncpy_s(name[9], "RUNA", 5);
		face[9] = 1;
		strncpy_s(ch[36], "����A�ł����āH", 44);
		strncpy_s(ch[37], "", 44);
		strncpy_s(ch[38], "", 44);
		strncpy_s(ch[39], "", 44);
		//�����Ń��X�{�X�o��
		strncpy_s(name[10], "???", 5);
		face[10] = 0;
		strncpy_s(ch[40], "�}�A�C�C�A�h�E�Z������j�n�A", 44);
		strncpy_s(ch[41], "�l�b�g���[�N�����S�񏶈��V�e�A", 44);
		strncpy_s(ch[42], "ELATREM�n���m���m�j�i���B", 44);
		strncpy_s(ch[43], "", 44);
		strncpy_s(name[11], "???", 5);
		face[11] = 0;
		strncpy_s(ch[44], "�M�l���m��R�n�A�S�e�k�J��I�������P�_�B", 44);
		strncpy_s(ch[45], "", 44);
		strncpy_s(ch[46], "", 44);
		strncpy_s(ch[47], "", 44);
		strncpy_s(name[12], "RUNA", 5);
		face[12] = 2;
		strncpy_s(ch[48], "�R�C�c���e�ʂ̂悤�ˁc�c�B", 44);
		strncpy_s(ch[49], "", 44);
		strncpy_s(ch[50], "", 44);
		strncpy_s(ch[51], "", 44);
		strncpy_s(name[13], "MIS", 5);
		face[13] = 5;
		strncpy_s(ch[52], "�����A�������܂ł̃{�X�����Ƃ́A", 44);
		strncpy_s(ch[53], "�S�R�A�Ⴄ�c�c�B", 44);
		strncpy_s(ch[54], "", 44);
		strncpy_s(ch[55], "", 44);
		strncpy_s(name[14], "???", 5);
		face[14] = 0;
		strncpy_s(ch[56], "�A�m���S�h���g�ꏏ�j�X���i�B", 44);
		strncpy_s(ch[57], "", 44);
		strncpy_s(ch[58], "", 44);
		strncpy_s(ch[59], "", 44);
		strncpy_s(name[15], "???", 5);
		face[15] = 0;
		strncpy_s(ch[60], "���n�R�mProgram�m�j�\�\�\", 44);
		strncpy_s(ch[61], "", 44);
		strncpy_s(ch[62], "", 44);
		strncpy_s(ch[63], "", 44);
		strncpy_s(name[16], "KERN", 5);
		face[16] = 1;
		strncpy_s(ch[64], "KERN(�P����)�i�m�_�J���i�B", 44);
		strncpy_s(ch[65], "", 44);
		strncpy_s(ch[66], "", 44);
		strncpy_s(ch[67], "", 44);
		strncpy_s(name[17], "MIS", 5);
		face[17] = 5;
		strncpy_s(ch[68], "�c�c�P�����H", 44);
		strncpy_s(ch[69], "���̃v���O�����S�̊j�H", 44);
		strncpy_s(ch[70], "", 44);
		strncpy_s(ch[71], "", 44);
		strncpy_s(name[18], "MIS", 5);
		face[18] = 5;
		strncpy_s(ch[72], "���Ⴀ���̃P������|���΁A", 44);
		strncpy_s(ch[73], "���̃v���O�����͊��S�ɒ�~������Ă��ƁH", 44);
		strncpy_s(ch[74], "", 44);
		strncpy_s(ch[75], "", 44);
		strncpy_s(name[19], "RUNA", 5);
		face[19] = 2;
		strncpy_s(ch[76], "�����A�����炭�B", 44);
		strncpy_s(ch[77], "�ł����ꂾ���W���}�[������ƁA", 44);
		strncpy_s(ch[78], "�P�����ɋ߂Â��̂����J��c�c�B", 44);
		strncpy_s(ch[79], "", 44);
		strncpy_s(name[20], "MIS", 5);
		face[20] = 0;
		strncpy_s(ch[80], "����͔C���āI�I", 44);
		strncpy_s(ch[81], "�������Ƃ����Ă݂��邩��I�I", 44);
		strncpy_s(ch[82], "", 44);
		strncpy_s(ch[83], "", 44);
		strncpy_s(name[21], "RUNA", 5);
		face[21] = 0;
		strncpy_s(ch[84], "�c�c�݂��A����痂����Ȃ����������ˁB", 44);
		strncpy_s(ch[85], "", 44);
		strncpy_s(ch[86], "", 44);
		strncpy_s(ch[87], "", 44);
		strncpy_s(name[22], "MIS", 5);
		face[22] = 3;
		strncpy_s(ch[88], "���[���[��[�A", 44);
		strncpy_s(ch[89], "�q������Ȃ����Č����Ă�̂Ɂc�c�B", 44);
		strncpy_s(ch[90], "", 44);
		strncpy_s(ch[91], "", 44);
		strncpy_s(name[23], "RUNA", 5);
		face[23] = 0;
		strncpy_s(ch[92], "���͂́A�S�����S�����B", 44);
		strncpy_s(ch[93], "���Ⴀ�A�A���^�ɃP�����͔C����B", 44);
		strncpy_s(ch[94], "�A�^�V�̓l�b�g���[�N�̐N�H�����Ƃ��x�炵��", 44);
		strncpy_s(ch[95], "�݂��B", 44);
		strncpy_s(name[24], "MIS", 5);
		face[24] = 1;
		strncpy_s(ch[96], "����A���Ⴀ�������͂��肢����ˁI�I", 44);
		strncpy_s(ch[97], "", 44);
		strncpy_s(ch[98], "", 44);
		strncpy_s(ch[99], "", 44);
		strncpy_s(name[25], "RUNA", 5);
		face[25] = 0;
		strncpy_s(ch[100], "�A���^������������̂�I�I", 44);
		strncpy_s(ch[101], "", 44);
		strncpy_s(ch[102], "", 44);
		strncpy_s(ch[103], "", 44);
		strncpy_s(name[26], "MIS", 5);
		face[26] = 0;
		strncpy_s(ch[104], "���������I�I", 42);
		strncpy_s(ch[105], "�c�c�����A�����s����I�I", 42);
		strncpy_s(ch[106], "", 42);
		strncpy_s(ch[107], "", 42);
		strncpy_s(name[27], "KERN", 5);
		face[27] = 1;
		strncpy_s(ch[108], "���j���c�C�J�H�@���J�i�c�c", 44);
		strncpy_s(ch[109], "", 44);
		strncpy_s(ch[110], "", 44);
		strncpy_s(ch[111], "", 44);
		strncpy_s(name[28], "KERN", 5);
		face[28] = 1;
		strncpy_s(ch[112], "�i���o�]�~�ʃ��A", 42);
		strncpy_s(ch[113], "�M�l���d�q�m�o�w�g�σG�e�N�������I�I", 42);
		strncpy_s(ch[114], "", 42);
		strncpy_s(ch[115], "", 42);

		ch_max = 116;
	}


		if (stage == 9) {
			last_picture[0] = LoadGraph("material/img/back/ending.png");
			strncpy_s(name[0], "", 5);
			strncpy_s(ch[0], "�\�\�\ ���ꂩ�琔���B", 100);
			strncpy_s(ch[1], "�G���g�����͕��������߂��������B", 100);
			strncpy_s(ch[2], "����͔ޏ��B�ɂ������̓��킪�߂��Ă������Ƃ��Ӗ����Ă��ā\�\�\", 100);
			strncpy_s(ch[3], "", 44);
			strncpy_s(name[1], "MIS", 5);
			face[1] = 1;
			strncpy_s(ch[4], "���i����[��I�I�@���͂�[�I�I", 100);
			strncpy_s(ch[5], "", 44);
			strncpy_s(ch[6], "", 44);
			strncpy_s(ch[7], "", 44);
			strncpy_s(name[2], "RUNA", 5);
			face[2] = 0;
			strncpy_s(ch[8], "�݂��H�@�ǂ������́A����Ȓ���������B", 100);
			strncpy_s(ch[9], "", 44);
			strncpy_s(ch[10], "", 44);
			strncpy_s(ch[11], "", 44);
			strncpy_s(name[3], "RUNA", 5);
			face[3] = 2;
			strncpy_s(ch[12], "�A�^�V�A��������������d���ɍs���Ȃ��Ⴂ���Ȃ��񂾂��ǁc�c�B", 100);
			strncpy_s(ch[13], "", 44);
			strncpy_s(ch[14], "", 44);
			strncpy_s(ch[15], "", 44);
			strncpy_s(name[4], "MIS", 5);
			face[4] = 3;
			strncpy_s(ch[16], "���[�c�c�B", 100);
			strncpy_s(ch[17], "����Ȃ��Ƃ��������΂�����Ȃ̂ɁA�����d�����Ă�́H", 44);
			strncpy_s(ch[18], "", 44);
			strncpy_s(ch[19], "", 44);
			strncpy_s(name[5], "RUNA", 5);
			face[5] = 2;
			strncpy_s(ch[20], "���x���������ǁA�A�^�V�̖{�Ƃ͉�ꂽ�f�[�^�̏C���Ȃ́B", 100);
			strncpy_s(ch[21], "", 44);
			strncpy_s(ch[22], "", 44);
			strncpy_s(ch[23], "", 44);
			strncpy_s(name[6], "RUNA", 5);
			face[6] = 2;
			strncpy_s(ch[24], "�w����Ȃ��Ɓx������������A�d���܂݂�ɂȂ��Ă��ł���c�c�B", 100);
			strncpy_s(ch[25], "�͂��c�c�B", 44);
			strncpy_s(ch[26], "", 44);
			strncpy_s(ch[27], "", 44);
			strncpy_s(name[7], "MIS", 5);
			face[7] = 2;
			strncpy_s(ch[28], "�����c�c", 100);
			strncpy_s(ch[29], "", 44);
			strncpy_s(ch[30], "", 44);
			strncpy_s(ch[31], "", 44);
			strncpy_s(name[8], "RUNA", 5);
			face[8] = 2;
			strncpy_s(ch[32], "���������΁A�A���^�̕��͎d���Ȃ��́H", 100);
			strncpy_s(ch[33], "", 44);
			strncpy_s(ch[34], "", 44);
			strncpy_s(ch[35], "", 44);
			strncpy_s(name[9], "MIS", 5);
			face[9] = 1;
			strncpy_s(ch[36], "����[�B", 100);
			strncpy_s(ch[37], "�����݂�Ȃ���w�~����T�}���I�I�x�Ȃ�čՂ�グ��ꂿ����Ă��B", 100);
			strncpy_s(ch[38], "", 44);
			strncpy_s(ch[39], "", 44);
			strncpy_s(name[10], "MIS", 5);
			face[10] = 1;
			strncpy_s(ch[40], "���̏�i���A", 100);
			strncpy_s(ch[41], "�w�݂�����́A1�T�Ԃ��炢�x��łĂ�������x", 100);
			strncpy_s(ch[42], "�Ȃ�Č����Ă���ā[�A�G�w�w�B", 100);
			strncpy_s(ch[43], "", 44);
			strncpy_s(name[11], "RUNA", 5);
			face[11] = 0;
			strncpy_s(ch[44], "�ǂ����g���ˁc�c�B", 100);
			strncpy_s(ch[45], "�A�^�V������ȐE��ɂ�����������B", 44);
			strncpy_s(ch[46], "", 44);
			strncpy_s(ch[47], "", 44);
			strncpy_s(name[12], "RUNA", 5);
			face[12] = 1;
			strncpy_s(ch[48], "�������̏�i����́A", 100);
			strncpy_s(ch[49], "�w����J�l�������ȁx", 100);
			strncpy_s(ch[50], "���ďΊ�Ō����Ȃ���A��ʂ̎d���n���ꂽ���B", 100);
			strncpy_s(ch[51], "", 44);
			strncpy_s(name[13], "MIS", 5);
			face[13] = 2;
			strncpy_s(ch[52], "�܂��܂��A���i�����̏�i������撣���Ă�񂾂낤����A����Ȃ�", 100);
			strncpy_s(ch[53], "�ƌ��킸�ɁA�ˁH", 44);
			strncpy_s(ch[54], "", 44);
			strncpy_s(ch[55], "", 44);
			strncpy_s(name[14], "MIS", 5);
			face[14] = 0;
			strncpy_s(ch[56], "�Ƃ���ŁA���i�����B", 100);
			strncpy_s(ch[57], "�����́A���Ŏ����������ɗ�����������H", 100);
			strncpy_s(ch[58], "", 44);
			strncpy_s(ch[59], "", 44);
			strncpy_s(name[15], "RUNA", 5);
			face[15] = 2;
			strncpy_s(ch[60], "���H�@�܂����A�܂������ُ�ł��������́H", 100);
			strncpy_s(ch[61], "", 44);
			strncpy_s(ch[62], "", 44);
			strncpy_s(ch[63], "", 44);
			strncpy_s(name[16], "MIS", 5);
			face[16] = 3;
			strncpy_s(ch[64], "�c�c", 100);
			strncpy_s(ch[65], "", 44);
			strncpy_s(ch[66], "", 44);
			strncpy_s(ch[67], "", 44);
			strncpy_s(name[17], "RUNA", 5);
			face[17] = 1;
			strncpy_s(ch[68], "����ς�܂��_���[�W�̎c���Ă�ӏ����������̂�����c�c�B", 100);
			strncpy_s(ch[69], "���āA���悻�̖ڂ́B", 44);
			strncpy_s(ch[70], "", 44);
			strncpy_s(ch[71], "", 44);
			strncpy_s(name[18], "MIS", 5);
			face[18] = 3;
			strncpy_s(ch[72], "�c�c����ς�Y��Ă�B", 100);
			strncpy_s(ch[73], "", 44);
			strncpy_s(ch[74], "", 44);
			strncpy_s(ch[75], "", 44);
			strncpy_s(name[19], "RUNA", 5);
			face[19] = 2;
			strncpy_s(ch[76], "�Y��Ă�H�@�����H", 100);
			strncpy_s(ch[77], "", 44);
			strncpy_s(ch[78], "", 44);
			strncpy_s(ch[79], "", 44);
			strncpy_s(name[20], "MIS", 5);
			face[20] = 3;
			strncpy_s(ch[80], "���i�����B�@�������āA���������������H", 100);
			strncpy_s(ch[81], "", 44);
			strncpy_s(ch[82], "", 44);
			strncpy_s(ch[83], "", 44);
			strncpy_s(name[21], "RUNA", 5);
			face[21] = 2;
			strncpy_s(ch[84], "�����āA6��30���\�\���B", 100);
			strncpy_s(ch[85], "", 44);
			strncpy_s(ch[86], "", 44);
			strncpy_s(ch[87], "", 44);
			strncpy_s(name[22], "MIS", 5);
			face[22] = 0;
			strncpy_s(ch[88], "�����A���i�����̒a��������I�I", 100);
			strncpy_s(ch[89], "", 44);
			strncpy_s(ch[90], "", 44);
			strncpy_s(ch[91], "", 44);
			strncpy_s(name[23],"MIS", 5);
			face[23] = 3;
			strncpy_s(ch[92], "�����̒a�������炢�����Ɗo���ĂĂ�ˁB", 100);
			strncpy_s(ch[93], "�܂����������B", 44);
			strncpy_s(ch[94], "", 44);
			strncpy_s(ch[95], "", 44);
			strncpy_s(name[24], "RUNA", 5);
			face[24] = 0;
			strncpy_s(ch[96], "�d���Ђ������������ŁA��������Y��Ă���c�c�B", 100);
			strncpy_s(ch[97], "", 44);
			strncpy_s(ch[98], "", 44);
			strncpy_s(ch[99], "", 44);
			strncpy_s(name[25], "MIS", 5);
			strncpy_s(ch[100], "�Ƃ������ƂŁA�a�����v���[���g�������Ă����́B", 100);
			strncpy_s(ch[101], "�͂��A����I�I", 100);
			strncpy_s(ch[102], "���Č����Ă��A���Ԃ��Ȃ��������疞�����Ă��炦�邩������Ȃ���", 100);
			strncpy_s(ch[103], "���ǁc�c�B", 44);
			strncpy_s(name[26], "RUNA", 5);
			strncpy_s(ch[104], "�킴�킴�v���[���g����ɗ��Ă��ꂽ�́H", 100);
			strncpy_s(ch[105], "�ւ��`�A�݂��ɂ��Ă͈ӊO�ɋC���������Ƃ��邶��Ȃ�", 100);
			strncpy_s(ch[106], "", 44);
			strncpy_s(ch[107], "", 44);
			strncpy_s(name[27], "MIS", 5);
			strncpy_s(ch[108], "���[���[��[�A�w�ӊO�Ɂx�͗]�v�����āI�I", 100);
			strncpy_s(ch[109], "", 44);
			strncpy_s(ch[110], "", 44);
			strncpy_s(ch[111], "", 44);
			strncpy_s(name[28], "RUNA", 5);
			strncpy_s(ch[112], "�ӂӁA���肪�ƂˁB", 100);
			strncpy_s(ch[113], "�����J���Ă��ǂ�������H", 44);
			strncpy_s(ch[114], "", 44);
			strncpy_s(ch[115], "", 44);
			strncpy_s(name[29], "MIS", 5);
			strncpy_s(ch[116], "���������I�I", 100);
			strncpy_s(ch[117], "", 44);
			strncpy_s(ch[118], "", 44);
			strncpy_s(ch[119], "", 44);
			strncpy_s(name[30], "RUNA", 5);
			strncpy_s(ch[120], "����A�����Ȃ��c�c�B", 100);
			strncpy_s(ch[121], "", 44);
			strncpy_s(ch[122], "", 44);
			strncpy_s(ch[123], "", 44);
			strncpy_s(name[31], "RUNA", 5);
			strncpy_s(ch[124], "�\�\���ƁA�����CD�H", 100);
			strncpy_s(ch[125], "", 44);
			strncpy_s(ch[126], "", 44);
			strncpy_s(ch[127], "", 44);
			strncpy_s(name[32], "MIS", 5);
			strncpy_s(ch[128], "����A��������B", 100);
			strncpy_s(ch[129], "���i�����̂��߂ɁA�Ȃ�����Ă����񂾁`�B", 100);
			strncpy_s(ch[130], "���i�������āA��ƒ��ɂ悭���y�����Ă邵�A��Ȃ͎��̓��ӕ��삾", 100);
			strncpy_s(ch[131], "���A���傤�ǂ������Ȃ��āB", 100);
			strncpy_s(name[33], "RUNA", 5);
			strncpy_s(ch[132], "����Ȃ��Ƃ܂Ŋo���ĂĂ��ꂽ�́c�c�H", 100);
			strncpy_s(ch[133], "�����A�Ƃ��Ă���������B", 44);
			strncpy_s(ch[134], "", 44);
			strncpy_s(ch[135], "", 44);
			strncpy_s(name[34], "MIS", 5);
			strncpy_s(ch[136], "�������I�I", 100);
			strncpy_s(ch[137], "�˂��A������Ƃ����Œ����Ă݂Ă�B", 44);
			strncpy_s(ch[138], "���z�����炢�������ˁ�", 44);
			strncpy_s(ch[139], "", 44);
			strncpy_s(name[35], "RUNA", 5);
			strncpy_s(ch[140], "����A�����́H", 100);
			strncpy_s(ch[141], "�A�^�V���\�h����H", 44);
			strncpy_s(ch[142], "", 44);
			strncpy_s(ch[143], "", 44);
			strncpy_s(name[36], "MIS", 5);
			strncpy_s(ch[144], "���[�A�����͂���_�炩�ɂ��肢�������ȁ[�A�Ȃ�āB", 100);
			strncpy_s(ch[145], "", 44);
			strncpy_s(ch[146], "", 44);
			strncpy_s(ch[147], "", 44);
			strncpy_s(name[37], "RUNA", 5);
			strncpy_s(ch[148], "�ӂӁA�P�������B", 100);
			strncpy_s(ch[149], "", 44);
			strncpy_s(ch[150], "", 44);
			strncpy_s(ch[151], "", 44);
			strncpy_s(name[38], "RUNA", 5);
			strncpy_s(ch[152], "���āA��̂ǂ�ȋȂȂ̂�����\�\", 100);
			strncpy_s(ch[153], "", 44);
			strncpy_s(ch[154], "", 44);
			strncpy_s(ch[155], "", 44);
			strncpy_s(name[39], "", 5);
			strncpy_s(ch[156], "�c�c", 100);
			strncpy_s(ch[157], "�c�c�c�c", 44);
			strncpy_s(ch[158], "�c�c�c�c�c�c", 44);
			strncpy_s(ch[159], "�c�c�c�c�c�c�c�c�c�c�c�c�c�c�c�c�c�c�c�c�c�c�c�c�c�cTHE END.", 100);
			
			ch_max = 160;
		}
	}

	for (int i = 0; i < 3; i++) {
			if (strlen(ch[ch_i]) == 0) {//���̍s���󔒂Ȃ�
				if (ch_i % 4 != 3) {
					ch_i++;
					i = 0;
				}
		}
	}

	if ((i > i_max - 2 || ch[ch_i][i] == '\0') && ch_i % 4 != 3) {//�����P�s�ɓ��镶�����������Ȃ��I�������
		ch_i++;
		i = 0;
	}

	if (Controller.k_Get(Config.k_shot) == 1 || Controller.g_Get(Config.g_shot) == 1) {
		i = i_max;
		switch (ch_i % 4) {
		case 3:
			strncpy_s(str1, ch[ch_i], 0);
			strncpy_s(str2, ch[ch_i], 0);
			strncpy_s(str3, ch[ch_i], 0);
			strncpy_s(str4, ch[ch_i], 0);
			ch_i++;
			i = 0;
			break;
		case 0:
			strncpy_s(str1, ch[ch_i], i);// i�o�C�g�܂ł̔z��v�f��str�z��ɃR�s�[
			str1[i] = '\0';            // �I�[�L������
			strncpy_s(str2, ch[ch_i+1], i);
			str2[i] = '\0';
			strncpy_s(str3, ch[ch_i+2], i);
			str3[i] = '\0';
			strncpy_s(str4, ch[ch_i+3], i);
			str4[i] = '\0';
			ch_i += 3;
			break;
		case 1:
			strncpy_s(str2, ch[ch_i], i);
			str2[i] = '\0';
			strncpy_s(str3, ch[ch_i + 1], i);
			str3[i] = '\0';
			strncpy_s(str4, ch[ch_i + 2], i);
			str4[i] = '\0';
			ch_i += 2;
			break;
		case 2:
			strncpy_s(str3, ch[ch_i ], i);
			str3[i] = '\0';
			strncpy_s(str4, ch[ch_i + 1], i);
			str4[i] = '\0';
			ch_i += 1;
			break;
		
		
		/*case 4:
			strncpy_s(str5, ch[ch_i], 0);
			break;*/
		}
	}

	// �z��̏I�[-2�ȉ��ŁA����R�s�[����i�܂ł̔z��v�f��i�Ԗڂ�\0����Ȃ��J�E���^�[��5�̔{���Ȃ�
		if (i <= i_max - 2 && ch[ch_i][i] != '\0' && counter % 5 == 0) {

			i += 2;                    // �S�p�����Ȃ̂Ŕz��v�f2���J�E���g�A�b�v
			switch (ch_i % 4) {
			case 0:
				if (i == 2) {
					strncpy_s(str2, ch[ch_i], 0);
					strncpy_s(str3, ch[ch_i], 0);
					strncpy_s(str4, ch[ch_i], 0);
				}
				strncpy_s(str5, name[ch_i/4], 5);
				strncpy_s(str1, ch[ch_i], i);// i�o�C�g�܂ł̔z��v�f��str�z��ɃR�s�[
				str1[i] = '\0';            // �I�[�L������
				break;
			case 1:
				strncpy_s(str2, ch[ch_i], i);
				str2[i] = '\0';            
				break;
			case 2:
				strncpy_s(str3, ch[ch_i], i);
				str3[i] = '\0';            
				break;
			case 3:
				strncpy_s(str4, ch[ch_i], i);
				str4[i] = '\0';
				break;
			/*case 4:
				strncpy_s(str5, ch[ch_i], i);
				str5[i] = '\0';
				break;*/
			}
			
		}
		if (stage == 9) {
			DrawRotaGraphF(320, 240, 1.0f, 0.0f, last_picture[0], TRUE);
			if (ch_i >= 100 && whiteout_counter != 0) {//�ꖇ�G���o����b���n�܂鎞�ɂȂ�����
				out_mode = 1;
			}
		}

		Out();//��ʂ̃u���b�N�A�E�g�A�z���C�g�A�E�g


		if (stage == 9) {
			if (ch_i < 100){//�ꖇ�G���o���^�C�~���O���O�Ȃ�
				//�䎌��b���Ă��Ȃ��L�����̕`��
				SetDrawBright(150, 150, 150);//�b���Ă��Ȃ��L�����͈Â�����
					if (strcmp(name[ch_i / 4], "MIS") != 0 && m_draw_flag == true) {
						DrawRotaGraphF(200, (FIELD_Y + FIELD_MAX_Y) / 2 + 70, 1.0f, 0.0f, mispic[m_face], TRUE);
					}
					if (strcmp(name[ch_i / 4], "RUNA") != 0 && r_draw_flag == true) {
						DrawRotaGraphF(WINDOW_X - 160, (FIELD_Y + FIELD_MAX_Y) / 2 + 70, 1.0f, 0.0f, runapic[r_face], TRUE);
					}
				SetDrawBright(255, 255, 255);

				//�䎌��b���Ă���L�����̕`��
				if (strcmp(name[ch_i / 4], "MIS") == 0) {
					m_face = face[ch_i / 4];
					m_talk_time = ch_i / 4;
					DrawRotaGraphF(200, (FIELD_Y + FIELD_MAX_Y) / 2 + 70, 1.0f, 0.0f, mispic[m_face], TRUE);
				}
				else if (strcmp(name[ch_i / 4], "RUNA") == 0) {
					r_face = face[ch_i / 4];
					r_talk_time = ch_i / 4;
					DrawRotaGraphF(WINDOW_X - 160, (FIELD_Y + FIELD_MAX_Y) / 2 + 70, 1.0f, 0.0f, runapic[r_face], TRUE);
				}
			}
		}
		else {
			SetDrawArea(FIELD_X, FIELD_Y, FIELD_X + FIELD_MAX_X, FIELD_Y + FIELD_MAX_Y);//�`��\�G���A��ݒ�

			//�䎌��b���Ă��Ȃ��L�����̕`��
			SetDrawBright(150, 150, 150);//�b���Ă��Ȃ��L�����͈Â�����
			if (stage == 8 && ch_i/4 > 9) {//���X�{�X������Ƃ�
					if (strcmp(name[ch_i / 4], "???") != 0 && strcmp(name[ch_i / 4], "KERN") != 0) {
						DrawRotaGraphF(FIELD_X + FIELD_MAX_X - 100, (FIELD_Y + FIELD_MAX_Y) / 2 + 80, 1.0f, 0.0f, kernpic[k_face], TRUE);
					}
					else {
						if (m_talk_time > r_talk_time && m_draw_flag == true) {//�݂��̕������i������ɉ�b���Ă���ꍇ
							DrawRotaGraphF(FIELD_X + 100, (FIELD_Y + FIELD_MAX_Y) / 2 + 70, 1.0f, 0.0f, mispic[m_face], TRUE);
						}
						if (r_talk_time > m_talk_time && r_draw_flag == true) {//���i�̕����݂�������ɉ�b���Ă���ꍇ
							DrawRotaGraphF(FIELD_X + 100, (FIELD_Y + FIELD_MAX_Y) / 2 + 70, 1.0f, 0.0f, runapic[r_face], TRUE, TRUE);
						}
					}
				
			}
			else {//���X�{�X�����Ȃ�(�ʏ펞��)�v�����[�O�łȂ�(�L������o�ꂳ����)�Ƃ�
				if (strcmp(name[ch_i / 4], "MIS") != 0 && m_draw_flag==true) {//���ɂ݂�
					DrawRotaGraphF(FIELD_X + 100, (FIELD_Y + FIELD_MAX_Y) / 2 + 70, 1.0f, 0.0f, mispic[m_face], TRUE);
				}
				if (!(stage == 7 && ch_i/4 < 7) && strcmp(name[ch_i / 4], "RUNA") != 0 ) {//�E���Ƀ��i
					DrawRotaGraphF(FIELD_X + FIELD_MAX_X - 80, (FIELD_Y + FIELD_MAX_Y) / 2 + 70, 1.0f, 0.0f, runapic[r_face], TRUE);
				}
			}
			SetDrawBright(255, 255, 255);

			//�䎌��b���Ă���L�����̕`��
			if (strcmp(name[ch_i / 4], "MIS") == 0) {
				m_face = face[ch_i / 4];
				m_talk_time = ch_i / 4;
				DrawRotaGraphF(FIELD_X + 100, (FIELD_Y + FIELD_MAX_Y) / 2 + 70, 1.0f, 0.0f, mispic[m_face], TRUE);
			}
			else if (strcmp(name[ch_i / 4], "RUNA") == 0) {
				r_face = face[ch_i / 4];
				r_talk_time = ch_i / 4;
				if (stage == 8 && ch_i / 4 > 9) {//���X�{�X����Ƃ�
					DrawRotaGraphF(FIELD_X + 100, (FIELD_Y + FIELD_MAX_Y) / 2 + 70, 1.0f, 0.0f, runapic[r_face], TRUE, TRUE);
				}
				else {
					DrawRotaGraphF(FIELD_X + FIELD_MAX_X - 80, (FIELD_Y + FIELD_MAX_Y) / 2 + 70, 1.0f, 0.0f, runapic[r_face], TRUE);
				}
			}
			else if (ch_i / 4 > 9 && (strcmp(name[ch_i / 4], "???") == 0 || strcmp(name[ch_i / 4], "KERN") == 0)) {//�ŏ��̏����͎�l���B�����X�{�X�����F����(�o�ꂷ��)�^�C�~���O
				k_face = face[ch_i / 4];
				k_talk_time = ch_i / 4;
				DrawRotaGraphF(FIELD_X + FIELD_MAX_X - 100, (FIELD_Y + FIELD_MAX_Y) / 2 + 80, 1.0f, 0.0f, kernpic[k_face], TRUE);
			}

			SetDrawArea(0, 0, 640, 480);//�`��\�G���A��ݒ�
			if (strcmp(str5, "MIS") == 0) {//�݂��������Ă�Ƃ�
				font_color = GetColor(255, 255, 255);
			}
			else if (strcmp(str5, "RUNA") == 0) {//���i�������Ă���Ƃ�
				font_color = GetColor(255, 255, 255);
			}
			else if ((strcmp(str5, "???") == 0) || strcmp(str5, "KERN")) {//���X�{�X�������Ă��鎞
				font_color = GetColor(255, 255, 255);
			}
		}

		DrawFormatStringToHandle(FIELD_X, 360, font_color, font[3], "%s", str5);//�L������
		DrawFormatStringToHandle(FIELD_X, 380, GetColor(255, 255, 255), font[2], "%s", str1);
		DrawFormatStringToHandle(FIELD_X, 400, GetColor(255, 255, 255), font[2], "%s", str2);
		DrawFormatStringToHandle(FIELD_X, 420, GetColor(255, 255, 255), font[2], "%s", str3);
		DrawFormatStringToHandle(FIELD_X, 440, GetColor(255, 255, 255), font[2], "%s", str4);
		

	counter++;
	if (ch_i >= ch_max || (Controller.k_Get(Config.k_start) == 1 || Controller.g_Get(Config.g_start) == 1)) {//�V�i���I�I�����̏���
		ch_i = 0;
		strncpy_s(str1, ch[ch_i], 0);
		strncpy_s(str2, ch[ch_i], 0);
		strncpy_s(str3, ch[ch_i], 0);
		strncpy_s(str4, ch[ch_i], 0);
		strncpy_s(str5, name[ch_i], 0);
		
		i = 0;
		counter = 0;
		story_load_flag = false;
		if (state == s5_talk_l) {
			whiteout_counter = 0;
			out_counter = 0;
		}
		if (stage == 0) state = stage1;
		if (stage == 1) state = s2_loading;
		if (stage == 2) state = stage2;
		if (stage == 3) state = s3_loading;
		if (stage == 4) state = stage3;
		if (stage == 5) state = s4_loading;
		if (stage == 6) state = stage4;
		if (stage == 7) state = s5_loading;
		if (stage == 8) state = stage5;
		if (stage == 9) {
			mode = title;
			DeleteGraph(last_picture[0]);
		}
	}
}


//----------�X�e�[�W��������̂Ɏg���f�o�b�O�p�̊֐�(�����i�ł͎g��Ȃ�)----------//
void Control_c::ChangeStage() {
	if (Controller.k_Get(KEY_INPUT_F1) == 1) {
		state = s1_loading;
		s_change = 0;
		score = 0;
		scoresave_flag = 1;
		story_load_flag = false;
	}
	if (Controller.k_Get(KEY_INPUT_F2) == 1) {
		state = s2_loading;
		s_change = 0;
		score = 0;
		scoresave_flag = 0;
		story_load_flag = false;
	}
	if (Controller.k_Get(KEY_INPUT_F3) == 1) {
		state = s3_loading;
		s_change = 0;
		score = 0;
		scoresave_flag = 0;
		story_load_flag = false;
	}
	if (Controller.k_Get(KEY_INPUT_F4) == 1) {
		state = s4_loading;
		s_change = 0;
		score = 0;
		scoresave_flag = 0;
		story_load_flag = false;
	}
	if (Controller.k_Get(KEY_INPUT_F5) == 1) {
		state = s5_loading;
		s_change = 0;
		score = 0;
		scoresave_flag = 0;
		story_load_flag = false;
	}
	if (Controller.k_Get(KEY_INPUT_F6) == 1) {
		s_change = 0;
		score = 0;
		scoresave_flag = 0;
		story_load_flag = false;
	}
}

//----------��Փx��������̂Ɏg���f�o�b�O�p�̊֐�(�����i�ł͎g��Ȃ�)----------//
//(��)�F��Փx��ς�����͕K���X�e�[�W��I������������(�������Ȃ��ƓG�f�[�^�̃��[�h������ɍs���Ȃ�����)
void Control_c::SetDifficulty(){
	if (Controller.k_Get(KEY_INPUT_1) == 1) {
		level = 'E';
		s_change = 1;
		score = 0;
		scoresave_flag = 0;
	}
	if (Controller.k_Get(KEY_INPUT_2) == 1) {
		level = 'N';
		s_change = 1;
		score = 0;
		scoresave_flag = 0;
	}
	if (Controller.k_Get(KEY_INPUT_3) == 1) {
		level = 'H';
		s_change = 1;
		score = 0;
		scoresave_flag = 0;
	}
}

char Control_c::GetLevel() {
	return level;
}

int Control_c::GetState() {
	return state;
}

int Control_c::GetMode() {
	return mode;
}

int Control_c::GetScore() {
	return score;
}

int Control_c::HighScore() {
	if (highscore[level_num] < score && scoresave_flag==1) {
		highscore[level_num] = score;
		FILE *fp;
		if (errno_t error = fopen_s(&fp, "score.dat", "wb") != 0) {  // �t�@�C�����J��
			return 0;
		}
		fwrite(&highscore, sizeof(int), 3, fp); // �t�@�C����highscore�̒l���o�͂���
		fclose(fp); //�t�@�C�������
	}
	return 0;
}
int Control_c::ReadHighScore() {
	FILE *fp;
	if (errno_t error = fopen_s(&fp, "score.dat", "rb") != 0) {
		return 0;
	}
	fread(&highscore, sizeof(int), 3, fp); //�t�@�C������highscore�ɒl���o�͂���
	fclose(fp);
	return 0;
}

int Control_c::GetHighScore(int level) {
	return highscore[level];
}

void Control_c::AddScore(int addscore) {
	score += addscore;
}

void Control_c::SetLevel(char setlevel) {
	level = setlevel;
	if (setlevel == 'E') {
		level_num = 0;
	}
	else if(setlevel == 'N') {
		level_num = 1;
	}
	else if (setlevel == 'H') {
		level_num = 2;
	}
}

void Control_c::SetMode(int setmode) {
	mode = setmode;
}

void Control_c::SetStage(int setstage) {
	state = setstage;
	if (setstage == s1_loading) {
		scoresave_flag = 1;
	}
}

void Control_c::SetScore(int setscore) {
	score = setscore;
}

void Control_c::SetPx(int setpx0, int setpx1,int setpx2) {
	px[0] = setpx0;
	px[1] = setpx1;
	px[2] = setpx2;
}

void Control_c::SetRx(int setrx0, int setrx1) {
	rx[0] = setrx0;
	rx[1] = setrx1;
}

void Control_c::DrawStopTime(){
	Sound.Pause();

	Back.DrawBoard();

	SetDrawArea(FIELD_X, FIELD_Y, FIELD_X + FIELD_MAX_X, FIELD_Y + FIELD_MAX_Y);//�`��\�G���A��ݒ�
	//if (mode != game_play) {
		SetDrawBright(120, 120, 120);
	//}

	Back.DrawStage();
	Enemy.DrawEnemy();
	Boss.DrawBoss();
	Player.Draw();
	Effect.DrawEffect();

	SetDrawBright(255, 255, 255);
	
	SetDrawArea(0, 0, 640, 480);//�G���A��߂�


	Boss.DrawHpBar();
}

void Control_c::Continue() {
	if (mode == retry) {
		if (erosion >= EROSION_MAX*0.8) {
			erosion = EROSION_MAX;
			mode = gameover;
		}
		//�R�}���h�̈ʒu�̐���
		for (int i = 0; i < rcom_num; i++) {
			if (retry_com == i) {
				rx[i] = 255;
			}
			else {
				rx[i] = 120;
			}
		}

		DrawStopTime();
		DrawStringToHandle(148, 200, "�R���e�B�j���[", GetColor(rx[0], rx[0], rx[0]), font[1]);
		DrawStringToHandle(148, 250, "�^�C�g���ɖ߂�", GetColor(rx[1], rx[1], rx[1]), font[1]);

		if (Controller.k_Get(Config.k_up) == 1 || Controller.g_Get(Config.g_up) == 1) {
			retry_com = (retry_com + rcom_num - 1) % rcom_num;
		}else if (Controller.k_Get(Config.k_down) == 1 || Controller.g_Get(Config.g_down) == 1) {
			retry_com = (retry_com + 1) % rcom_num;
		}
		
			switch (retry_com) {
			case playagain:
				//����L�[��������̑���
				if (Controller.k_Get(Config.k_shot) == 1 || Controller.g_Get(Config.g_shot) == 1) {
					Enemy.se_flag[9] = 1;
					erosion += EROSION_MAX * 3 / 20;
					Player.SetPlayerNum(DEFAULT_P_NUM);
					mode = game_play;
					score = 0;
				}
				break;

			case rcom_title:
				if (Controller.k_Get(Config.k_shot) == 1 || Controller.g_Get(Config.g_shot) == 1) {	
					Enemy.se_flag[9] = 1;
					mode = title;
					Menu.SetTCom(gamestart);
				}
				break;
			}
		}
	}
/*else if (Player.GetPlayerNum() == 0) {
		mode = retry; //�R���e�B�j���[���邩�ǂ���������ʂ��o��
		retry_com = playagain;
	}*/

void Control_c::Pause() {
	if (Controller.k_Get(Config.k_start) == 1 || Controller.g_Get(Config.g_start) == 1) {
		if (mode == game_play ) {
			pause_com = play;
			mode = pause;
			Enemy.se_flag[10] = 1;
		}
		else if (mode == pause) {
			Enemy.se_flag[11] = 1;
			mode = game_play;
		}

	}else if (mode == pause) {

		//�R�}���h�̈ʒu�̐���
		for (int i = 0; i < pcom_num; i++) {
			if (pause_com== i) {
				px[i] = 255;
			}
			else {
				px[i] = 120;
			}
		}
		DrawStopTime();
		DrawStringToHandle(158, 200, "�Q�[���ɖ߂�", GetColor(px[0], px[0], px[0]), font[1]);
		DrawStringToHandle(105, 250, "�X�e�[�W���ŏ�������", GetColor(px[1], px[1], px[1]), font[1]);
		DrawStringToHandle(148, 300, "�^�C�g���ɖ߂�", GetColor(px[2], px[2], px[2]), font[1]);
		
		if (Controller.k_Get(Config.k_up) == 1 || Controller.g_Get(Config.g_up) == 1) {
			pause_com = (pause_com + pcom_num - 1) % pcom_num;
		}
		else if (Controller.k_Get(Config.k_down) == 1 || Controller.g_Get(Config.g_down) == 1) {
			pause_com = (pause_com + 1) % pcom_num;
		}

		switch (pause_com) {
		case play:
			//����L�[��������̑���
			if (Controller.k_Get(Config.k_shot) == 1 || Controller.g_Get(Config.g_shot) == 1) {
				Enemy.se_flag[9] = 1;
				mode = game_play;
			}
			break;

		case stage_retry:
			if (Controller.k_Get(Config.k_shot) == 1 || Controller.g_Get(Config.g_shot) == 1) {
				Enemy.se_flag[9] = 1;
				state--;
				Player.SetPlayerNum(begin_playernum);
				erosion = begin_erosion;
				score = begin_score;
				mode = game_play;
			}
			break;

		case pcom_title:
			if (Controller.k_Get(Config.k_shot) == 1 || Controller.g_Get(Config.g_shot) == 1) {
				Enemy.se_flag[9] = 1;
				mode = title;
				Menu.SetTCom(gamestart);
			}
			break;
		}
	}
}

void Control_c::Out() {
		if (whiteout_counter == 0 && blackout_counter==0) {
			return;
		}
		if(blackout_counter>0){
			if (out_counter < 254/5) {
				blackout_counter += 5;
			}
			else if (out_counter < (254 + 255) / 5) {
				blackout_counter -= 5;
			}
			else {
				blackout_counter = 0;
				out_counter = 0;
				return;
			}
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, blackout_counter);
			DrawRotaGraphF(320, 240, 1.0f, 0.0f, out[1], TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			out_counter++;
		}
		else if (whiteout_counter>0) {
			if (out_counter < 51) {
				whiteout_counter += 5;
				out_counter++;
			}
			else if (out_counter < 101) {
				if (state == stage5) {
					state = s5_talk_l;
				}
				else if (out_mode == 1) {
					out_counter++;
					whiteout_counter -= 5;
				}
			}
			else {
				whiteout_counter = 0;
				out_counter = 0;
				out_mode = 0;
				return;
			}
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, whiteout_counter);
			DrawRotaGraphF(320, 240, 1.0f, 0.0f, out[0], TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
}

//----------�f�o�b�O�ɕK�v�ȗv�f��\������֐�(�����i�ł͎g��Ȃ�)----------//

void Control_c::DrawMaskData() {
	if (mode == game_play && state != s5_talk_l) {

		DrawFormatString(0, 0, GetColor(255, 255, 255), "%c-%d", level, (state + 1)/2);
		DrawFormatString(0, 15, GetColor(255, 255, 255), "%d", g_count);
	}
}
