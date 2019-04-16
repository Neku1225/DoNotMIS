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
	Config.ConfigDataRead();//設定の読み込み
	SetMainWindowText("Don't MIS");
	ChangeWindowMode(Config.window_mode);							
	SetGraphMode(WINDOW_X, WINDOW_Y, WINDOW_COLOR_BIT);	// 画面の大きさを変える
	if (DxLib_Init() == -1) return -1;					// DXライブラリを初期化処理,エラーが起きたら終了
	SetDrawScreen(DX_SCREEN_BACK);						// 裏画面に描画することを決定


	//-----初期化設定ここから-----//


	srand((unsigned)time(NULL));						// 乱数の初期化

	Control.StartIni();									// ゲーム起動時に一度すれば良い初期化をする
	Control.SetMode(title);
	Control.SetLevel('H');//デバッグ用、ゲーム本編から直接始める為に必要(無いと難易度が不定になる)
	Control.SetStage(s1_loading);

	//-----初期化設定ここまで-----//

	while (ScreenFlip() == 0							// 裏画面を表画面に反映
		&& ProcessMessage() == 0						// メッセージ処理
		&& ClearDrawScreen() == 0						// 画面をクリアする
		&& Controller.k_Update() == 0					// キーボードの入力状態を記憶
		&& Controller.g_Update() == 0)					// ゲームパッドの入力状態を記憶
	{
		//-----メインループここから-----//
		Control.All();									// ゲームの流れを管理する関数
		//Control.DrawMaskData();							// デバッグ用の関数のため完成直前で消す必要あり
		//-----メインループここまで-----//
	}

	DxLib_End();										// DXライブラリ使用の終了処理

	return 0;											// ソフトの正常終了 
}