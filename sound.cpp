#include "define.h"

void Sound_c::Initialize() {
	//音を鳴らすフラグの初期化
	memset(Enemy.se_flag, 0, sizeof(int)*SE_MAX);
}

void Sound_c::StartIni() {
	se[0] = LoadSoundMem("material/sound/se/eshot.wav");//雑魚敵の弾
	se[1] = LoadSoundMem("material/sound/se/shot.wav");//自機の弾
	se[2] = LoadSoundMem("material/sound/se/bangmoresmall.mp3");//雑魚敵の死亡音
	se[3] = LoadSoundMem("material/sound/se/bangbig.mp3");//ボスの死亡音
	se[4] = LoadSoundMem("material/sound/se/p_death.mp3");//自機死に音
	se[5] = LoadSoundMem("material/sound/se/shield.wav");//シールドの展開音
	se[8] = LoadSoundMem("material/sound/se/hit.mp3");//命中音
	se[9] = LoadSoundMem("material/sound/se/enter.wav");//決定音
	se[10] = LoadSoundMem("material/sound/se/pause.mp3");//ポーズ音
	se[11] = LoadSoundMem("material/sound/se/back.wav");//戻る音
	se[14] = LoadSoundMem("material/sound/se/bomgo2.wav");//ボム音
	se[15] = LoadSoundMem("material/sound/se/bomhit.mp3");
	se[50] = LoadSoundMem("material/sound/se/cvZaki.mp3");//←強そう

	bgm[2] = LoadSoundMem("material/sound/bgm/op1.wav");
	
	ChangeVolumeSoundMem(100, se[0]);//各素材の再生ボリュームを設定
	ChangeVolumeSoundMem(100, se[1]);
	ChangeVolumeSoundMem(150, se[2]);
	ChangeVolumeSoundMem(60, se[3]);

	ChangeVolumeSoundMem(120, se[5]);


	ChangeVolumeSoundMem(90, se[8]);
	ChangeVolumeSoundMem(120, se[9]);
	ChangeVolumeSoundMem(120, se[10]);
	ChangeVolumeSoundMem(120, se[11]);
	ChangeVolumeSoundMem(130, se[14]);
	ChangeVolumeSoundMem(120, se[15]);

	ChangeVolumeSoundMem(180, bgm[2]);

}

void Sound_c::LoadStage(int stage) {
	for (int i = 0; i < 2; i++) {
	StopSoundMem(bgm[i]);//デバッグ関数使用時に音楽が多重で再生されないようにする対策
	DeleteSoundMem(bgm[i]);
}
	switch (stage) {
	case 1:
		bgm[0] = LoadSoundMem("material/sound/bgm/south_normal.wav");
		bgm[1] = LoadSoundMem("material/sound/bgm/south_boss.wav");
		bgm_flag = 0;
		ChangeVolumeSoundMem(180, bgm[0]);
		ChangeVolumeSoundMem(180, bgm[1]);
		break;
	case 2:
		bgm[0] = LoadSoundMem("material/sound/bgm/east_normal.wav");
		bgm[1] = LoadSoundMem("material/sound/bgm/east_boss.wav");
		bgm_flag = 0;
		ChangeVolumeSoundMem(200, bgm[0]);
		ChangeVolumeSoundMem(180, bgm[1]);
		break;
	case 3:
		bgm[0] = LoadSoundMem("material/sound/bgm/west_normal.wav");
		bgm[1] = LoadSoundMem("material/sound/bgm/west_boss.wav");
		bgm_flag = 0;
		ChangeVolumeSoundMem(140, bgm[0]);
		ChangeVolumeSoundMem(180, bgm[1]);
		break;
	case 4:
		bgm[0] = LoadSoundMem("material/sound/bgm/north_normal.wav");
		bgm[1] = LoadSoundMem("material/sound/bgm/north_boss.wav");
		bgm_flag = 0;
		ChangeVolumeSoundMem(180, bgm[0]);
		ChangeVolumeSoundMem(200, bgm[1]);
		break;
	case 5:
		bgm[0] = LoadSoundMem("material/sound/bgm/final.wav");
		bgm[1] = LoadSoundMem("material/sound/bgm/final2.wav");
		bgm[3] = LoadSoundMem("material/sound/bgm/ending.wav");
		SetLoopPosSoundMem(5052, bgm[0]);
		bgm_flag = 0;
		ChangeVolumeSoundMem(180, bgm[0]);
		ChangeVolumeSoundMem(140, bgm[1]);
		ChangeVolumeSoundMem(180, bgm[3]);
		break;
	}
	
}

void Sound_c::PlaySe() {
	for (int i = 0; i<SE_MAX; i++) {
		if (Enemy.se_flag[i] == 1) {
			if (CheckSoundMem(se[i]) != 0) {
				StopSoundMem(se[i]);
			}
			PlaySoundMem(se[i], DX_PLAYTYPE_BACK);
		}
	}
}

void Sound_c::Pause() {
	memset(Enemy.se_flag, 0, sizeof(int)*SE_MAX);
	for (int i = 0; i < 3; i++) {
		StopSoundMem(bgm[i]);
	}
}

void Sound_c::PlayBgm(){
	switch (Control.GetMode()) {
	case game_play:
		if (Control.GetState() == s5_talk_l) {
			for (int i = 0; i < 2; i++) {
				if (CheckSoundMem(bgm[i]) != 0) {
					StopSoundMem(bgm[i]);
				}
			}
			if (CheckSoundMem(bgm[3]) == 0) {
				PlaySoundMem(bgm[3], DX_PLAYTYPE_BACK, FALSE);
			}
		}
		else {
			switch (bgm_flag) {
			case 0:
				if (Control.g_count == 60) {//はじまって60カウント後に再生
					PlaySoundMem(bgm[0], DX_PLAYTYPE_BACK);
					bgm_flag = 1;
				}
				break;
			case 1:
				if ((Control.GetState() != stage5 && Boss.GetBossFlag() == 1) || //最終面以外はボス登場時
					(Control.GetState() == stage5 && Boss.GetBossType() == 4 && Boss.BossShotCounter() == 120)) {//最終面はラスボスとの最終決戦時
					StopSoundMem(bgm[0]);
					DeleteSoundMem(bgm[0]);
					PlaySoundMem(bgm[1], DX_PLAYTYPE_LOOP);
					bgm_flag = 2;
				}
				else if (CheckSoundMem(bgm[0]) == 0) {
					PlaySoundMem(bgm[0], DX_PLAYTYPE_BACK, FALSE);
				}
				break;
			case 2:
				if (Boss.GetBossFlag() == 0) {
					StopSoundMem(bgm[1]);
				}
				else if (CheckSoundMem(bgm[1]) == 0) {
					PlaySoundMem(bgm[1], DX_PLAYTYPE_LOOP, FALSE);
				}
				break;
			}
		}
			break;
	case title:
		if (CheckSoundMem(bgm[3]) != 0) {
			StopSoundMem(bgm[3]);
			DeleteSoundMem(bgm[3]);
		}
	case setting:
		if (CheckSoundMem(bgm[2]) == 0) {
			PlaySoundMem(bgm[2], DX_PLAYTYPE_LOOP,false);
		}
		break;
	}
}