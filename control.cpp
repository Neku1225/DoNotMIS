#include "define.h"



//----------ゲーム中に繰り返しする処理を集めた関数----------//

void Control_c::Loop(int stage){					//関数の呼び出す順番で結果が変わるので注意

	Back.DrawBoard();								//

	SetDrawArea(FIELD_X, FIELD_Y, FIELD_X + FIELD_MAX_X, FIELD_Y + FIELD_MAX_Y);//描画可能エリアを設定

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
	SetDrawArea(FIELD_X, FIELD_Y, FIELD_X + FIELD_MAX_X, FIELD_Y + FIELD_MAX_Y);//描画可能エリアを設定
	Boss.Loop(stage);								//

	if (Effect.bright_set.bright != 255) {			//
		SetDrawBright(255, 255, 255);				//
	}
	Player.Loop();
	Judge.Loop(stage);								//
	Effect.Loop();									//

	SetDrawArea(0, 0, 640, 480);//エリアを戻す

	Boss.DrawHpBar();
	DrawMaskData();

		g_count++;
}


//----------ステージ開始ごとに必要な初期化をする関数---------//

void Control_c::Initialize(){
	g_count = 1;
	begin_erosion = erosion;
	begin_playernum = Player.GetPlayerNum();
	begin_score = score;
	Player.Initialize();
	Enemy.Initialize();
	Effect.Initialize();
}



//----------ゲーム本編開始時に使う初期化の関数----------//

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
	font[2] = CreateFontToHandle(NULL, 16, -1, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);//シナリオで使うフォント
	font[3] = CreateFontToHandle("OCRB", 13, -1, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);//キャラ名で使うフォント
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



//----------メインループを全て処理する関数----------//

void Control_c::All() {

	ChangeStage();										//ステージをいじるデバッグ用の関数(F1～F5キーで変更)
	SetDifficulty();                               //難易度をいじるデバッグ用の関数(1～3キーで変更)
	Sound.PlaySe();
	Sound.PlayBgm();
	Sound.Initialize();								//音を鳴らすフラグをすべて折る
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
		DrawFormatStringToHandle(37, 296, GetColor(255, 255, 255), font[1], "ショットボタンでタイトルに戻ります");
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
			Initialize();  // ステージの開始ごとに必要な初期化をする
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
			Out();//画面のブラックアウト、ホワイトアウト
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
		//1行辺りの文字数に関する指定
		if (stage == 9) {
			i_max = 98;
		}
		else {
			i_max = 44;
		}
	if (stage == 0) {
		strncpy_s(name[0], "MIS", 5);
		face[0] = 0;
		strncpy_s(ch[0], "あれ～？", 44);
		strncpy_s(ch[1], "何か今日は全然仕事が来ないなぁ……。", 44);
		strncpy_s(ch[2], "どうしたんだろ？", 44);
		strncpy_s(ch[3], "", 44);
		strncpy_s(name[1], "MIS", 5);
		face[1] = 0;
		strncpy_s(ch[4], "うーん……。", 44);
		strncpy_s(ch[5], "周りの皆も慌ただしいし……。", 44);
		strncpy_s(ch[6], "何かあったのかな？", 44);
		strncpy_s(ch[7], "", 44);
		strncpy_s(name[2], "MIS", 5);
		face[2] = 2;
		strncpy_s(ch[8], "でも、まっいっか。", 44);
		strncpy_s(ch[9], "せっかく仕事が無いんだから、", 44);
		strncpy_s(ch[10], "ゆっくり休もう―――", 44);
		strncpy_s(ch[11], "", 44);
		strncpy_s(name[3], "RUNA", 5);
		face[3] = 1;
		strncpy_s(ch[12], "みすーっ！！　いるわよねー！？", 44);
		strncpy_s(ch[13], "", 44);
		strncpy_s(ch[14], "", 44);
		strncpy_s(ch[15], "", 44);
		strncpy_s(name[4], "MIS", 5);
		face[4] = 4;
		strncpy_s(ch[16], "うわぁ！！", 44);
		strncpy_s(ch[17], "って何だ、ルナちゃんか。", 44);
		strncpy_s(ch[18], "驚かさないでよー……もう。", 44);
		strncpy_s(ch[19], "", 44);
		strncpy_s(name[5], "RUNA", 5);
		face[5] = 2;
		strncpy_s(ch[20], "何だ、じゃないわよ！！", 44);
		strncpy_s(ch[21], "こんな状況で落ち着いていられるわけがないで", 44);
		strncpy_s(ch[22], "しょ！！", 44);
		strncpy_s(ch[23], "", 44);
		strncpy_s(name[6], "MIS", 5);
		face[6] = 3;
		strncpy_s(ch[24], "……えーっと、ルナちゃん？", 44);
		strncpy_s(ch[25], "もしかして何かイライラすることでもあったり", 44);
		strncpy_s(ch[26], "した？", 44);
		strncpy_s(ch[27], "", 44);
		strncpy_s(name[7], "RUNA", 5);
		face[7] = 1;
		strncpy_s(ch[28], "……みす、アンタまさか、何も知らないの？", 44);
		strncpy_s(ch[29], "", 44);
		strncpy_s(ch[30], "", 44);
		strncpy_s(ch[31], "", 44);
		strncpy_s(name[8], "MIS", 5);
		face[8] = 0;
		strncpy_s(ch[32], "？　うん。", 44);
		strncpy_s(ch[33], "", 44);
		strncpy_s(ch[34], "", 44);
		strncpy_s(ch[35], "", 44);
		strncpy_s(name[9], "RUNA", 5);
		face[9] = 2;
		strncpy_s(ch[36], "嘘でしょ……。", 44);
		strncpy_s(ch[37], "このエラトレムの一大事って時に……。", 44);
		strncpy_s(ch[38], "", 44);
		strncpy_s(ch[39], "", 44);
		strncpy_s(name[10], "RUNA", 5);
		face[10] = 2;
		strncpy_s(ch[40], "まあいいわ……。", 44);
		strncpy_s(ch[41], "今から説明するから、よく聞いて。", 44);
		strncpy_s(ch[42], "", 44);
		strncpy_s(ch[43], "", 44);
		//Black Out
		strncpy_s(name[11], "RUNA", 5);
		face[11] = 2;
		strncpy_s(ch[44], "―――ってことなの。", 44);
		strncpy_s(ch[45], "分かった？", 44);
		strncpy_s(ch[46], "", 44);
		strncpy_s(ch[47], "", 44);
		strncpy_s(name[12], "MIS", 5);
		face[12] = 4;
		strncpy_s(ch[48], "ジャマーっていうコンピューターウイルスが、", 44);//MIS
		strncpy_s(ch[49], "この都市のネットワークを壊してる？！", 44);
		strncpy_s(ch[50], "だから、皆の様子が変だったんだ……", 44);
		strncpy_s(ch[51], "", 44);
		strncpy_s(name[13], "RUNA", 5);
		face[13] = 1;
		strncpy_s(ch[52], "気づかないアンタもアンタだけどね……。", 44);//RUNA
		strncpy_s(ch[53], "", 44);
		strncpy_s(ch[54], "", 44);
		strncpy_s(ch[55], "", 44);
		strncpy_s(name[14], "RUNA", 5);
		face[14] = 2;
		strncpy_s(ch[56], "それで、みす。", 44);
		strncpy_s(ch[57], "今日は頼みがあって来たの。", 44);
		strncpy_s(ch[58], "", 44);
		strncpy_s(ch[59], "", 44);
		strncpy_s(name[15], "MIS", 5);
		face[15] = 5;
		strncpy_s(ch[60], "頼み？", 44);//MIS
		strncpy_s(ch[61], "", 44);
		strncpy_s(ch[62], "", 44);
		strncpy_s(ch[63], "", 44);
		strncpy_s(name[16], "RUNA", 5);
		face[16] = 2;
		strncpy_s(ch[64], "そう。", 44);//RUNA
		strncpy_s(ch[65], "アンタ、確かワクチンプログラムを自力で作成", 44);
		strncpy_s(ch[66], "できるのよね？", 44);
		strncpy_s(ch[67], "", 44);
		strncpy_s(name[17], "MIS", 5);
		face[17] = 5;
		strncpy_s(ch[68], "うん、少しはかじってるけど……。", 44);//MIS
		strncpy_s(ch[69], "", 44);
		strncpy_s(ch[70], "", 44);
		strncpy_s(ch[71], "", 44);
		strncpy_s(name[18], "RUNA", 5);
		face[18] = 0;
		strncpy_s(ch[72], "かじってるだけで十分よ。", 44);
		strncpy_s(ch[73], "", 44);
		strncpy_s(ch[74], "", 44);
		strncpy_s(ch[75], "", 44);
		strncpy_s(name[19], "RUNA", 5);
		face[19] = 0;
		strncpy_s(ch[76], "エラトレムにはそういう技術を持ってる人が、", 44);
		strncpy_s(ch[77], "少ないんだから。", 44);
		strncpy_s(ch[78], "", 44);
		strncpy_s(ch[79], "", 44);
		strncpy_s(name[20], "MIS", 5);
		face[20] = 3;
		strncpy_s(ch[80], "―――まさか、私にワクチンを作ってジャマー", 44);
		strncpy_s(ch[81], "を消しまくれ、ってお願いしに来たの……？", 44);
		strncpy_s(ch[82], "", 44);
		strncpy_s(ch[83], "", 44);
		strncpy_s(name[21], "RUNA", 5);
		face[21] = 0;
		strncpy_s(ch[84], "まあ、要するにそういうことね。", 44);
		strncpy_s(ch[85], "", 44);
		strncpy_s(ch[86], "", 44);
		strncpy_s(ch[87], "", 44);
		strncpy_s(name[22], "RUNA", 5);
		face[22] = 0;
		strncpy_s(ch[88], "ネットワークでワクチンを送り込めないから、", 44);
		strncpy_s(ch[89], "直接ぶつけるしかないけれど。", 44);
		strncpy_s(ch[90], "", 44);
		strncpy_s(ch[91], "", 44);
		strncpy_s(name[23], "MIS", 5);
		face[23] = 4;
		strncpy_s(ch[92], "いやいやいやいや無理だよ！！", 44);
		strncpy_s(ch[93], "戦闘みたいな真似なんかしたことないもん！！", 44);
		strncpy_s(ch[94], "", 44);
		strncpy_s(ch[95], "", 44);
		strncpy_s(name[24], "RUNA", 5);
		face[24] = 2;
		strncpy_s(ch[96], "そんなことは分かってるけれど、", 44);
		strncpy_s(ch[97], "もう時間がないのよ……。", 44);
		strncpy_s(ch[98], "", 44);
		strncpy_s(ch[99], "", 44);
		strncpy_s(name[25], "RUNA", 5);
		face[25] = 0;
		strncpy_s(ch[100], "ほら、アタシもサポートするから。　ね？", 44);
		strncpy_s(ch[101], "", 44);
		strncpy_s(ch[102], "", 44);
		strncpy_s(ch[103], "", 44);
		strncpy_s(name[26], "MIS", 5);
		face[26] = 3;
		strncpy_s(ch[104], "むー……ルナちゃんがそう言うなら。", 44);
		strncpy_s(ch[105], "あんまり気が進まないけど、しょうがない、か。", 44);
		strncpy_s(ch[106], "", 44);
		strncpy_s(ch[107], "", 44);
		strncpy_s(name[27], "RUNA", 5);
		face[27] = 0;
		strncpy_s(ch[108], "みす……ありがとう。", 44);
		strncpy_s(ch[109], "恩に着るわ。", 44);
		strncpy_s(ch[110], "", 44);
		strncpy_s(ch[111], "", 44);
		strncpy_s(name[28], "MIS", 5);
		face[28] = 0;
		strncpy_s(ch[112], "うん、それじゃあ早速行ってくるよ！！", 44);
		strncpy_s(ch[113], "ちゃんとアシストしてよね？", 44);
		strncpy_s(ch[114], "", 44);
		strncpy_s(ch[115], "", 44);
		strncpy_s(name[29], "RUNA", 5);
		face[29] = 0;
		strncpy_s(ch[116], "ええ、分かったわ！！", 44);
		strncpy_s(ch[117], "頑張って！！", 44);
		strncpy_s(ch[118], "", 44);
		strncpy_s(ch[119], "", 44);

		ch_max = 120;
	}

	if (stage == 1) {
		strncpy_s(name[0], "MIS", 5);
		face[0] = 5;
		strncpy_s(ch[0], "―――ねえ、ルナちゃん。", 44);
		strncpy_s(ch[1], "最後に出てきた敵って、結局何だったの？", 44);
		strncpy_s(ch[2], "やっぱりジャマー？", 44);
		strncpy_s(ch[3], "", 44);
		strncpy_s(name[1], "RUNA", 5);
		face[1] = 2;
		strncpy_s(ch[4], "ちょっと待ってなさいっての……。", 44);
		strncpy_s(ch[5], "今、そいつの痕跡を調べているんだから。", 44);
		strncpy_s(ch[6], "", 44);
		strncpy_s(ch[7], "", 44);
		strncpy_s(name[2], "MIS", 5);
		face[2] = 0;
		strncpy_s(ch[8], "倒しちゃったのに調べられるもんなんだね。", 44);
		strncpy_s(ch[9], "さっすが！！", 44);
		strncpy_s(ch[10], "", 44);
		strncpy_s(ch[11], "", 44);
		strncpy_s(name[3], "RUNA", 5);
		face[3] = 0;
		strncpy_s(ch[12], "だって、普段のアタシの仕事は、", 44);
		strncpy_s(ch[13], "壊れたデータの復元よ？", 44);
		strncpy_s(ch[14], "これくらい出来なくてどうするのよ。", 44);
		strncpy_s(ch[15], "", 44);
		strncpy_s(name[4], "MIS", 5);
		face[4] = 4;
		strncpy_s(ch[16], "え……復元する気なの？！", 44);
		strncpy_s(ch[17], "", 44);
		strncpy_s(ch[18], "", 44);
		strncpy_s(ch[19], "", 44);
		strncpy_s(name[5], "RUNA", 5);
		face[5] = 1;
		strncpy_s(ch[20], "んなわけないでしょーが！！", 44);
		strncpy_s(ch[21], "解析してるだけよ、か・い・せ・き！！", 44);
		strncpy_s(ch[22], "", 44);
		strncpy_s(ch[23], "", 44);
		strncpy_s(name[6], "RUNA", 5);
		face[6] = 2;
		strncpy_s(ch[24], "っと、解析が終わったみたいね。", 44);
		strncpy_s(ch[25], "どれどれ……。", 44);
		strncpy_s(ch[26], "", 44);
		strncpy_s(ch[27], "", 44);
		strncpy_s(name[7], "RUNA", 5);
		face[7] = 2;
		strncpy_s(ch[28], "うーん……。", 44);
		strncpy_s(ch[29], "確かに、奴はジャマーではないみたいね。", 44);
		strncpy_s(ch[30], "", 44);
		strncpy_s(ch[31], "", 44);
		strncpy_s(name[8], "MIS", 5);
		face[8] = 5;
		strncpy_s(ch[32], "じゃあ、何なの？", 44);
		strncpy_s(ch[33], "", 44);
		strncpy_s(ch[34], "", 44);
		strncpy_s(ch[35], "", 44);
		strncpy_s(name[9], "RUNA", 5);
		face[9] = 2;
		strncpy_s(ch[36], "どうも、指揮官みたいな役割みたいね。", 44);
		strncpy_s(ch[37], "ジャマーを動かすようなプログラムの残骸が見", 44);
		strncpy_s(ch[38], "つかったから。", 44);
		strncpy_s(ch[39], "", 44);
		strncpy_s(name[10], "RUNA", 5);
		face[10] = 2;
		strncpy_s(ch[40], "ついでに、ジャマー自体の痕跡も調べたけど、", 44);
		strncpy_s(ch[41], "自律して動けるようなプログラムは見当たらな", 44);
		strncpy_s(ch[42], "かったし。", 44);
		strncpy_s(ch[43], "", 44);
		strncpy_s(name[11], "RUNA", 5);
		face[11] = 2;
		strncpy_s(ch[44], "大方、間違いないんじゃないかしら。", 44);
		strncpy_s(ch[45], "", 44);
		strncpy_s(ch[46], "", 44);
		strncpy_s(ch[47], "", 44);
		strncpy_s(name[12], "MIS", 5);
		face[12] = 1;
		strncpy_s(ch[48], "じゃあ、もうジャマーは使い物にならないって", 44);
		strncpy_s(ch[49], "ことだよね！？", 44);
		strncpy_s(ch[50], "ばんざーい！！", 44);
		strncpy_s(ch[51], "", 44);
		strncpy_s(name[13], "RUNA", 5);
		face[13] = 1;
		strncpy_s(ch[52], "……まあ、そうとも言えるわね。", 44);
		strncpy_s(ch[53], "少なくともここ、", 44);
		strncpy_s(ch[54], "エリア＝サザンに関しては、だけど。", 44);
		strncpy_s(ch[55], "", 44);
		strncpy_s(name[14], "MIS", 5);
		face[14] = 4;
		strncpy_s(ch[56], "えっ。", 44);
		strncpy_s(ch[57], "", 44);
		strncpy_s(ch[58], "", 44);
		strncpy_s(ch[59], "", 44);
		strncpy_s(name[15], "RUNA", 5);
		face[15] = 2;
		strncpy_s(ch[60], "解析結果によると、", 44);
		strncpy_s(ch[61], "コイツが動かしてたジャマーは、", 44);
		strncpy_s(ch[62], "『エリア＝サザンにいる』ジャマーだけよ。", 44);
		strncpy_s(ch[63], "", 44);
		strncpy_s(name[16], "MIS", 5);
		face[16] = 4;
		strncpy_s(ch[64], "え、えっ。", 44);
		strncpy_s(ch[65], "", 44);
		strncpy_s(ch[66], "", 44);
		strncpy_s(ch[67], "", 44);
		strncpy_s(name[17], "RUNA", 5);
		face[17] = 2;
		strncpy_s(ch[68], "裏返せば、他のエリアにも同じ様な奴がいる、", 44);
		strncpy_s(ch[69], "ってことになるわね。", 44);
		strncpy_s(ch[70], "", 44);
		strncpy_s(ch[71], "", 44);
		strncpy_s(name[18], "MIS", 5);
		face[18] = 4;
		strncpy_s(ch[72], "え、え、えっ。", 44);
		strncpy_s(ch[73], "", 44);
		strncpy_s(ch[74], "", 44);
		strncpy_s(ch[75], "", 44);
		strncpy_s(name[19], "RUNA", 5);
		face[19] = 2;
		strncpy_s(ch[76], "しょうがないでしょ……。", 44);
		strncpy_s(ch[77], "さあ、みす！！", 44);
		strncpy_s(ch[78], "さっさと次に行くわよ！！", 44);
		strncpy_s(ch[79], "", 44);
		strncpy_s(name[20], "MIS", 5);
		face[20] = 3;
		strncpy_s(ch[80], "え～！！", 44);
		strncpy_s(ch[81], "やっぱり、まだ戦わないとダメなの～？！", 44);
		strncpy_s(ch[82], "", 44);
		strncpy_s(ch[83], "", 44);

			ch_max = 84;
		}

	if (stage == 2) {
		strncpy_s(name[0], "MIS", 5);
		face[0] = 3;
		strncpy_s(ch[0], "うわぁ……敵さん増えてる。", 44);
		strncpy_s(ch[1], "", 44);
		strncpy_s(ch[2], "", 44);
		strncpy_s(ch[3], "", 44);
		strncpy_s(name[1], "RUNA", 5);
		face[1] = 0;
		strncpy_s(ch[4], "エリア＝イースタン―――", 44);
		strncpy_s(ch[5], "エラトレム全体で考えたら、", 44);
		strncpy_s(ch[6], "そんなに重要な情報は取り扱ってないけど。", 44);
		strncpy_s(ch[7], "エリア＝サザンに比べたらねぇ……。", 44);
		strncpy_s(name[2], "MIS", 5);
		face[2] = 2;
		strncpy_s(ch[8], "エリア＝サザンは、ゲームとかイラストとか", 44);
		strncpy_s(ch[9], "音楽とかのデータしか来ないからね。", 44);
		strncpy_s(ch[10], "私の本業も、音楽データの管理だし。", 44);
		strncpy_s(ch[11], "", 44);
		strncpy_s(name[3], "RUNA", 5);
		face[3] = 2;
		strncpy_s(ch[12], "まぁ、ジャマーが増えているのは事実よ。", 44);
		strncpy_s(ch[13], "気を引き締めて。", 44);
		strncpy_s(ch[14], "", 44);
		strncpy_s(ch[15], "", 44);
		strncpy_s(name[4], "MIS", 5);
		face[4] = 0;
		strncpy_s(ch[16], "むー……了解。", 44);
		strncpy_s(ch[17], "じゃあ、また行ってくるね！！", 44);
		strncpy_s(ch[18], "", 44);
		strncpy_s(ch[19], "", 44);
		strncpy_s(name[5], "RUNA", 5);
		face[5] = 0;
		strncpy_s(ch[20], "よろしく頼むわ！！", 44);
		strncpy_s(ch[21], "", 44);
		strncpy_s(ch[22], "", 44);
		strncpy_s(ch[23], "", 44);
		//Margin
		face[6] = 5;
		strncpy_s(name[6], "MIS", 5);
		strncpy_s(ch[24], "ん……？", 44);
		strncpy_s(ch[25], "ジャマーが増えたってことは", 44);
		strncpy_s(ch[26], "それを指揮する方も更に……", 44);
		strncpy_s(ch[27], "い、いや考えないことにしよっと。", 44);

			ch_max = 28;
		}

	if (stage == 3) {
		strncpy_s(name[0], "MIS", 5);
		face[0] = 3;
		strncpy_s(ch[0], "やっぱり、ボス強くなってるじゃん……", 44);
		strncpy_s(ch[1], "", 44);
		strncpy_s(ch[2], "", 44);
		strncpy_s(ch[3], "", 44);
		strncpy_s(name[1], "RUNA", 5);
		face[1] = 1;
		strncpy_s(ch[4], "そりゃ、処理数が増えているんだから、", 44);
		strncpy_s(ch[5], "より高度に構成されているに決まっているでし", 44);
		strncpy_s(ch[6], "ょ。", 44);
		strncpy_s(ch[7], "", 44);
		strncpy_s(name[2], "MIS", 5);
		face[2] = 2;
		strncpy_s(ch[8], "いや、そんな気は薄々感じてたけどね！！", 44);
		strncpy_s(ch[9], "それでも、ちょっと期待しちゃったんだよ！！", 44);
		strncpy_s(ch[10], "", 44);
		strncpy_s(ch[11], "", 44);
		strncpy_s(name[3], "RUNA", 5);
		face[3] = 0;
		strncpy_s(ch[12], "まあまあ。", 44);
		strncpy_s(ch[13], "でも、何はともあれ、", 44);
		strncpy_s(ch[14], "エリア＝イースタンも一段落ってところね。", 44);
		strncpy_s(ch[15], "", 44);
		strncpy_s(name[4], "RUNA", 5);
		face[4] = 0;
		strncpy_s(ch[16], "さて残りはウェスタンかノーザンだけど……。", 44);
		strncpy_s(ch[17], "", 44);
		strncpy_s(ch[18], "", 44);
		strncpy_s(ch[19], "", 44);
		strncpy_s(name[5], "MIS", 5);
		face[5] = 5;
		strncpy_s(ch[20], "次は、ウェスタンの方がいいんじゃないかな。", 44);
		strncpy_s(ch[21], "ノーザンは、", 44);
		strncpy_s(ch[22], "重要なところばっかりあるって聞くし……。", 44);
		strncpy_s(ch[23], "めちゃくちゃ敵強くなってるだろうし……。", 44);
		strncpy_s(name[6], "RUNA", 5);
		face[6] = 2;
		strncpy_s(ch[24], "どうせ、どっちも行かなきゃならないんだけ", 44);
		strncpy_s(ch[25], "ど……。", 44);
		strncpy_s(ch[26], "みす、分かってる？", 44);
		strncpy_s(ch[27], "", 44);
		strncpy_s(name[7], "MIS", 5);
		face[7] = 3;
		strncpy_s(ch[28], "分かってるけどさ～……", 44);
		strncpy_s(ch[29], "", 44);
		strncpy_s(ch[30], "", 44);
		strncpy_s(ch[31], "", 44);
		strncpy_s(name[8], "MIS", 5);
		face[8] = 0;
		strncpy_s(ch[32], "……うん。", 44);
		strncpy_s(ch[33], "やっぱりエリア＝イースタンからの方からにし", 44);
		strncpy_s(ch[34], "よう。", 44);
		strncpy_s(ch[35], "", 44);
		strncpy_s(name[9], "MIS", 5);
		face[9] = 0;
		strncpy_s(ch[36], "自分の実力を冷静に見極めるのは大事だよ。", 44);
		strncpy_s(ch[37], "うん。", 44);
		strncpy_s(ch[38], "", 44);
		strncpy_s(ch[39], "", 44);
		strncpy_s(name[10], "RUNA", 5);
		face[10] = 0;
		strncpy_s(ch[40], "みすが、何かすごくマトモなこと言ってる気が", 44);
		strncpy_s(ch[41], "するわ……", 44);
		strncpy_s(ch[42], "", 44);
		strncpy_s(ch[43], "", 44);

			ch_max = 44;
		}

	if (stage == 4) {
		strncpy_s(name[0], "RUNA", 5);
		face[0] = 0;
		strncpy_s(ch[0], "さて、エリア＝ウェスタンに着いたわね。", 44);
		strncpy_s(ch[1], "", 44);
		strncpy_s(ch[2], "", 44);
		strncpy_s(ch[3], "", 44);
		strncpy_s(name[1], "MIS", 5);
		face[1] = 5;
		strncpy_s(ch[4], "あれー？", 44);
		strncpy_s(ch[5], "ジャマーがウジャウジャいると思ってたのに。", 44);
		strncpy_s(ch[6], "これ、エリア＝サザンと同じぐらいの数しかい", 44);
		strncpy_s(ch[7], "ないよ？", 44);
		strncpy_s(name[2], "RUNA", 5);
		face[2] = 2;
		strncpy_s(ch[8], "ええ……そうね。", 44);
		strncpy_s(ch[9], "ここは、エリア＝ノーザンには及ばないけど、", 44);
		strncpy_s(ch[10], "エラトレムでも有数の重要地区なのに……。", 44);
		strncpy_s(ch[11], "おかしいわ……。", 44);
		strncpy_s(name[3], "MIS", 5);
		face[3] = 1;
		strncpy_s(ch[12], "うーん。", 44);
		strncpy_s(ch[13], "単純に私たちがラッキーだったんじゃない？", 44);
		strncpy_s(ch[14], "", 44);
		strncpy_s(ch[15], "", 44);
		strncpy_s(name[4], "MIS", 5);
		face[3] = 1;
		strncpy_s(ch[16], "ほら、私とか日頃の行い完璧だし！！", 44);
		strncpy_s(ch[17], "", 44);
		strncpy_s(ch[18], "", 44);
		strncpy_s(ch[19], "", 44);
		strncpy_s(name[5], "RUNA", 5);
		face[4] = 1;
		strncpy_s(ch[20], "そんな単純な……。", 44);
		strncpy_s(ch[21], "アタシは何だかキナ臭い匂いしかしないわよ？", 44);
		strncpy_s(ch[22], "", 44);
		strncpy_s(ch[23], "", 44);
		strncpy_s(name[6], "MIS", 5);
		face[5] = 1;
		strncpy_s(ch[24], "ルナちゃんの考えすぎだよ～！！", 44);
		strncpy_s(ch[25], "大丈夫、大丈夫！！", 44);
		strncpy_s(ch[26], "", 44);
		strncpy_s(ch[27], "", 44);
		strncpy_s(name[7], "MIS", 5);
		face[6] = 0;
		strncpy_s(ch[28], "じゃあ、早速始めちゃおうかな。", 44);
		strncpy_s(ch[29], "こんなチャンスは生かさないとね！！", 44);
		strncpy_s(ch[30], "", 44);
		strncpy_s(ch[31], "", 44);
		strncpy_s(name[8], "RUNA", 5);
		face[7] = 1;
		strncpy_s(ch[32], "あっ、みす！！", 44);
		strncpy_s(ch[33], "―――って、もう行っちゃった。", 44);
		strncpy_s(ch[34], "", 44);
		strncpy_s(ch[35], "", 44);
		strncpy_s(name[9], "RUNA", 5);
		face[8] = 2;
		strncpy_s(ch[36], "確かに、みすの言う通り私の考え過ぎかもしれ", 44);
		strncpy_s(ch[37], "ないけど……。", 44);
		strncpy_s(ch[38], "", 44);
		strncpy_s(ch[39], "", 44);
		strncpy_s(name[10], "RUNA", 5);
		face[9] = 2;
		strncpy_s(ch[40], "ホントに大丈夫かしら……。", 44);
		strncpy_s(ch[41], "", 44);
		strncpy_s(ch[42], "", 44);
		strncpy_s(ch[43], "", 44);

			ch_max = 44;
		}

	if (stage == 5) {
		strncpy_s(name[0], "MIS", 5);
		face[0] = 3;
		strncpy_s(ch[0], "……エグい。", 44);
		strncpy_s(ch[1], "非常にエグい。", 44);
		strncpy_s(ch[2], "", 44);
		strncpy_s(ch[3], "", 44);
		strncpy_s(name[1], "RUNA", 5);
		face[1] = 2;
		strncpy_s(ch[4], "やっぱり、", 44);
		strncpy_s(ch[5], "ジャマーのプログラムが更新されてる……。", 44);
		strncpy_s(ch[6], "", 44);
		strncpy_s(ch[7], "", 44);
		strncpy_s(name[2], "RUNA", 5);
		face[2] = 2;
		strncpy_s(ch[8], "アタシたちが派手にやってるのを、", 44);
		strncpy_s(ch[9], "向こうがただただ見てるだけなわけもないか。", 44);
		strncpy_s(ch[10], "", 44);
		strncpy_s(ch[11], "", 44);
		strncpy_s(name[3], "MIS", 5);
		face[3] = 3;
		strncpy_s(ch[12], "デスヨネー……。", 44);
		strncpy_s(ch[13], "", 44);
		strncpy_s(ch[14], "", 44);
		strncpy_s(ch[15], "", 44);
		strncpy_s(name[4], "RUNA", 5);
		face[4] = 2;
		strncpy_s(ch[16], "でも、やっと次で最後。", 44);
		strncpy_s(ch[17], "残りはエリア＝ノーザンだけよ。", 44);
		strncpy_s(ch[18], "", 44);
		strncpy_s(ch[19], "", 44);
		strncpy_s(name[5], "RUNA", 5);
		face[5] = 2;
		strncpy_s(ch[20], "エリア＝ノーザン―――", 44);
		strncpy_s(ch[21], "ネットワークの一部の管理が任されていたり、", 44);
		strncpy_s(ch[22], "機密情報を取り扱ったり……", 44);
		strncpy_s(ch[23], "まあ、テロリストが好みそうな地区ね。", 44);
		strncpy_s(name[6], "RUNA", 5);
		face[6] = 2;
		strncpy_s(ch[24], "残りの敵も集結してること間違いなし、", 44);
		strncpy_s(ch[25], "って感じ。", 44);
		strncpy_s(ch[26], "", 44);
		strncpy_s(ch[27], "", 44);
		strncpy_s(name[7], "MIS", 5);
		face[7] = 5;
		strncpy_s(ch[28], "うん……。", 44);
		strncpy_s(ch[29], "でも、弱音ばっかり吐いても何も変わらないも", 44);
		strncpy_s(ch[30], "んね。", 44);
		strncpy_s(ch[31], "", 44);
		strncpy_s(name[8], "MIS", 5);
		face[8] = 5;
		strncpy_s(ch[32], "やれるだけやってみるよ。", 44);
		strncpy_s(ch[33], "", 44);
		strncpy_s(ch[34], "", 44);
		strncpy_s(ch[35], "", 44);
		strncpy_s(name[9], "RUNA", 5);
		face[9] = 0;
		strncpy_s(ch[36], "やれるだけ、じゃないでしょ。", 44);
		strncpy_s(ch[37], "やりきらないとダメよ？", 44);
		strncpy_s(ch[38], "", 44);
		strncpy_s(ch[39], "", 44);
		strncpy_s(name[10], "MIS", 5);
		face[10] = 0;
		strncpy_s(ch[40], "……そうだね。", 44);
		strncpy_s(ch[41], "じゃあ、やりきって見せるよ！！", 44);
		strncpy_s(ch[42], "", 44);
		strncpy_s(ch[43], "", 44);
		strncpy_s(name[11], "RUNA", 5);
		face[11] = 0;
		strncpy_s(ch[44], "ええ、そっちの方がいいわ。", 44);
		strncpy_s(ch[45], "", 44);
		strncpy_s(ch[46], "", 44);
		strncpy_s(ch[47], "", 44);
		strncpy_s(name[12], "RUNA", 5);
		face[12] = 0;
		strncpy_s(ch[48], "……それじゃあ、行くわよ！！", 44);
		strncpy_s(ch[49], "", 44);
		strncpy_s(ch[50], "", 44);
		strncpy_s(ch[51], "", 44);
		strncpy_s(name[13], "MIS", 5);
		face[13] = 1;
		strncpy_s(ch[52], "レッツ・ゴー！！", 44);
		strncpy_s(ch[53], "", 44);
		strncpy_s(ch[54], "", 44);
		strncpy_s(ch[55], "", 44);

			ch_max = 56;
		}

	if (stage == 6) {
		strncpy_s(name[0], "RUNA", 5);
		face[0] = 2;
		strncpy_s(ch[0], "覚悟はしてたけど……。", 44);
		strncpy_s(ch[1], "これは……マズイわね……。", 44);
		strncpy_s(ch[2], "", 44);
		strncpy_s(ch[3], "", 44);
		strncpy_s(name[1], "MIS", 5);
		face[1] = 5;
		strncpy_s(ch[4], "ジャマーからしても、", 44);
		strncpy_s(ch[5], "最終防衛ラインみたいな感じなのかな。", 44);
		strncpy_s(ch[6], "", 44);
		strncpy_s(ch[7], "", 44);
		strncpy_s(name[2], "RUNA", 5);
		face[2] = 2;
		strncpy_s(ch[8], "でしょうね。", 44);
		strncpy_s(ch[9], "もう奴らにはここしか残ってないわけだし。", 44);
		strncpy_s(ch[10], "", 44);
		strncpy_s(ch[11], "", 44);
		strncpy_s(name[3], "RUNA", 5);
		face[3] = 2;
		strncpy_s(ch[12], "どうするの？", 44);
		strncpy_s(ch[13], "一旦戻って、作戦会議するって手もあるわよ？", 44);
		strncpy_s(ch[14], "", 44);
		strncpy_s(ch[15], "", 44);
		strncpy_s(name[4], "MIS", 5);
		face[4] = 5;
		strncpy_s(ch[16], "本当はそうしたいけど……。", 44);
		strncpy_s(ch[17], "こうしてる内にも、エラトレムのネットワーク", 44);
		strncpy_s(ch[18], "は侵食され続けているんだよ？", 44);
		strncpy_s(ch[19], "", 44);
		strncpy_s(name[5], "MIS", 5);
		face[5] = 5;
		strncpy_s(ch[20], "そう考えたら、", 44);
		strncpy_s(ch[21], "すぐにでも行くべきなんだと思う。", 44);
		strncpy_s(ch[22], "", 44);
		strncpy_s(ch[23], "", 44);
		strncpy_s(name[6], "RUNA", 5);
		face[6] = 0;
		strncpy_s(ch[24], "へぇ……。", 44);
		strncpy_s(ch[25], "みす、アンタ随分なコト言うようになったんじ", 44);
		strncpy_s(ch[26], "ゃない？", 44);
		strncpy_s(ch[27], "", 44);
		strncpy_s(name[7], "MIS", 5);
		face[7] = 3;
		strncpy_s(ch[28], "失礼なー。", 44);
		strncpy_s(ch[29], "いつまでも、子供じゃないですよーだ！！", 44);
		strncpy_s(ch[30], "", 44);
		strncpy_s(ch[31], "", 44);
		strncpy_s(name[8], "RUNA", 5);
		face[8] = 0;
		strncpy_s(ch[32], "そういうところが子供っぽいの。", 44);
		strncpy_s(ch[33], "", 44);
		strncpy_s(ch[34], "", 44);
		strncpy_s(ch[35], "", 44);
		strncpy_s(name[9], "MIS", 5);
		face[9] = 3;
		strncpy_s(ch[36], "うぐっ。", 44);
		strncpy_s(ch[37], "", 44);
		strncpy_s(ch[38], "", 44);
		strncpy_s(ch[39], "", 44);
		strncpy_s(name[10], "RUNA", 5);
		face[10] = 0;
		strncpy_s(ch[40], "……でも覚悟は決まったようね。", 44);
		strncpy_s(ch[41], "", 44);
		strncpy_s(ch[42], "", 44);
		strncpy_s(ch[43], "", 44);
		strncpy_s(name[11], "MIS", 5);
		face[11] = 5;
		strncpy_s(ch[44], "……。", 44);
		strncpy_s(ch[45], "", 44);
		strncpy_s(ch[46], "", 44);
		strncpy_s(ch[47], "", 44);
		strncpy_s(name[12], "RUNA", 5);
		face[12] = 2;
		strncpy_s(ch[48], "みす……絶対に、無事で帰ってきて。", 44);
		strncpy_s(ch[49], "絶対だからッ……！！", 44);
		strncpy_s(ch[50], "", 44);
		strncpy_s(ch[51], "", 44);
		strncpy_s(name[13], "MIS", 5);
		face[13] = 0;
		strncpy_s(ch[52], "……うん、分かった。", 44);
		strncpy_s(ch[53], "約束だよ！！", 44);
		strncpy_s(ch[54], "", 44);
		strncpy_s(ch[55], "", 44);

			ch_max = 56;
		}

	if (stage == 7) {
		strncpy_s(name[0], "MIS", 5);
		face[0] = 0;
		strncpy_s(ch[0], "周りのジャマーが動かなくなった……", 44);
		strncpy_s(ch[1], "ってことは、もしかして……！！", 44);
		strncpy_s(ch[2], "", 44);
		strncpy_s(ch[3], "", 44);
		strncpy_s(name[1], "MIS", 5);
		face[1] = 1;
		strncpy_s(ch[4], "や、やった……！？", 44);
		strncpy_s(ch[5], "", 44);
		strncpy_s(ch[6], "", 44);
		strncpy_s(ch[7], "", 44);
		strncpy_s(name[2], "MIS", 5);
		face[2] = 1;
		strncpy_s(ch[8], "私、ボスを倒せたの……？", 44);
		strncpy_s(ch[9], "私、エラトレムを守れたの……？", 44);
		strncpy_s(ch[10], "", 44);
		strncpy_s(ch[11], "", 44);
		strncpy_s(name[3], "MIS", 5);
		face[3] = 2;
		strncpy_s(ch[12], "……うん。", 44);
		strncpy_s(ch[13], "あとルナちゃんとの約束も守れたし。", 44);
		strncpy_s(ch[14], "", 44);
		strncpy_s(ch[15], "", 44);
		strncpy_s(name[4], "MIS", 5);
		face[4] = 2;
		strncpy_s(ch[16], "うぅぅ～、良かったあぁぁぁ～！！", 44);
		strncpy_s(ch[17], "ぐすっ、よし、すぐにでも戻ろっ！！", 44);
		strncpy_s(ch[18], "", 44);
		strncpy_s(ch[19], "", 44);
		strncpy_s(ch[20], "……。", 44);
		strncpy_s(ch[21], "……。", 44);
		strncpy_s(ch[22], "……。", 44);
		strncpy_s(ch[23], "……。", 44);
		strncpy_s(name[6], "???", 5);
		strncpy_s(ch[24], "……マサカ、全滅トハ。", 44);
		strncpy_s(ch[25], "……全ク。", 44);
		strncpy_s(ch[26], "全ク、使エナイ傀儡ドモダ……。", 44);
		strncpy_s(ch[27], "", 44);
		//Black Out
		strncpy_s(name[7], "RUNA", 5);
		face[7] = 2;
		strncpy_s(ch[28], "各地のジャマーが再起動？！", 44);
		strncpy_s(ch[29], "何が起こってるの？！", 44);
		strncpy_s(ch[30], "", 44);
		strncpy_s(ch[31], "", 44);
		strncpy_s(name[8], "MIS", 5);
		face[8] = 1;
		strncpy_s(ch[32], "ルナちゃーん！！", 44);
		strncpy_s(ch[33], "何とか、ボスのこと倒せ―――", 44);
		strncpy_s(ch[34], "って、どうしたの？", 44);
		strncpy_s(ch[35], "", 44);
		strncpy_s(name[9], "RUNA", 5);
		face[9] = 0;
		strncpy_s(ch[36], "みす！！", 44);
		strncpy_s(ch[37], "良かった、無事だったのね……。", 44);
		strncpy_s(ch[38], "", 44);
		strncpy_s(ch[39], "", 44);
		strncpy_s(name[10], "MIS", 5);
		face[10] = 2;
		strncpy_s(ch[40], "うん、ギリギリだったけどね。", 44);
		strncpy_s(ch[41], "それよりどうして慌ててるの？", 44);
		strncpy_s(ch[42], "", 44);
		strncpy_s(ch[43], "", 44);
		strncpy_s(name[11], "RUNA", 5);
		face[11] = 2;
		strncpy_s(ch[44], "それがね……。", 44);
		strncpy_s(ch[45], "ボスによる統率を失って機能停止してたはずの", 44);
		strncpy_s(ch[46], "ジャマーが、活動を再開したみたいなのよ。", 44);
		strncpy_s(ch[47], "", 44);
		strncpy_s(name[12], "MIS", 5);
		face[12] = 4;
		strncpy_s(ch[48], "えええ？！　何で？！", 44);
		strncpy_s(ch[49], "ジャマーって命令がないと、", 44);
		strncpy_s(ch[50], "動けないんじゃ……。", 44);
		strncpy_s(ch[51], "", 44);
		strncpy_s(name[13], "RUNA", 5);
		face[13] = 2;
		strncpy_s(ch[52], "それは間違いないはずよ。", 44);
		strncpy_s(ch[53], "アタシ、解析には自信があるから。", 44);
		strncpy_s(ch[54], "", 44);
		strncpy_s(ch[55], "", 44);
		strncpy_s(name[14], "MIS", 5);
		face[14] = 3;
		strncpy_s(ch[56], "だとすると、まさか……。", 44);
		strncpy_s(ch[57], "", 44);
		strncpy_s(ch[58], "", 44);
		strncpy_s(ch[59], "", 44);
		strncpy_s(name[15], "RUNA", 5);
		face[15] = 1;
		strncpy_s(ch[60], "ええ、その『まさか』よ。", 44);
		strncpy_s(ch[61], "", 44);
		strncpy_s(ch[62], "", 44);
		strncpy_s(ch[63], "", 44);
		strncpy_s(name[16], "RUNA", 5);
		face[16] = 1;
		strncpy_s(ch[64], "新しい命令者が、どこかにいる可能性が非常に", 44);
		strncpy_s(ch[65], "高いわ。", 44);
		strncpy_s(ch[66], "", 44);
		strncpy_s(ch[67], "", 44);
		strncpy_s(name[17], "MIS", 5);
		face[17] = 3;
		strncpy_s(ch[68], "そ、そんなぁ……。", 44);
		strncpy_s(ch[69], "", 44);
		strncpy_s(ch[70], "", 44);
		strncpy_s(ch[71], "", 44);
		strncpy_s(name[18], "RUNA", 5);
		face[18] = 2;
		strncpy_s(ch[72], "問題はソイツがどこにいるかってことだけど、", 44);
		strncpy_s(ch[73], "……っと、まただわ。", 44);
		strncpy_s(ch[74], "", 44);
		strncpy_s(ch[75], "", 44);
		strncpy_s(name[19], "MIS", 5);
		face[19] = 5;
		strncpy_s(ch[76], "ん、ルナちゃん？", 44);
		strncpy_s(ch[77], "何か分かったの？", 44);
		strncpy_s(ch[78], "", 44);
		strncpy_s(ch[79], "", 44);
		strncpy_s(name[20], "RUNA", 5);
		face[20] = 1;
		strncpy_s(ch[80], "いやさっきから、", 44);
		strncpy_s(ch[81], "かろうじて生きてるネットワークを通じて、", 44);
		strncpy_s(ch[82], "ジャマーの動向を調べていたんだけど……。", 44);
		strncpy_s(ch[83], "1つ気になるところがあるのよ。", 44);
		strncpy_s(name[21], "MIS", 5);
		face[21] = 5;
		strncpy_s(ch[84], "というと？", 44);
		strncpy_s(ch[85], "", 44);
		strncpy_s(ch[86], "", 44);
		strncpy_s(ch[87], "", 44);
		strncpy_s(name[22], "RUNA", 5);
		face[22] = 2;
		strncpy_s(ch[88], "……どうも、ジャマーが同じところを目指して", 44);
		strncpy_s(ch[89], "集まってきているみたいなの。", 44);
		strncpy_s(ch[90], "", 44);
		strncpy_s(ch[91], "", 44);
		strncpy_s(name[23], "MIS", 5);
		face[23] = 3;
		strncpy_s(ch[92], "集結？！", 44);
		strncpy_s(ch[93], "……それで、その場所は？", 44);
		strncpy_s(ch[94], "", 44);
		strncpy_s(ch[95], "", 44);
		strncpy_s(name[24], "RUNA", 5);
		face[24] = 1;
		strncpy_s(ch[96], "確か、この座標地点にあったのは―――", 44);
		strncpy_s(ch[97], "", 44);
		strncpy_s(ch[98], "", 44);
		strncpy_s(ch[99], "", 44);
		strncpy_s(name[25], "RUNA", 5);
		face[25] = 2;
		strncpy_s(ch[100], "―――セントラル・タワー？", 44);
		strncpy_s(ch[101], "", 44);
		strncpy_s(ch[102], "", 44);
		strncpy_s(ch[103], "", 44);


		ch_max = 104;
	}

	if (stage == 8) {
		strncpy_s(name[0], "MIS", 5);
		face[0] = 3;
		strncpy_s(ch[0], "ビンゴみたい。", 44);
		strncpy_s(ch[1], "ジャマーがタワーを取り囲んでるよ……。", 44);
		strncpy_s(ch[2], "", 44);
		strncpy_s(ch[3], "", 44);
		strncpy_s(name[1], "RUNA", 5);
		face[1] = 2;
		strncpy_s(ch[4], "タワーの職員も皆、避難している……。", 44);
		strncpy_s(ch[5], "", 44);
		strncpy_s(ch[6], "", 44);
		strncpy_s(ch[7], "", 44);
		strncpy_s(name[2], "MIS", 5);
		face[2] = 5;
		strncpy_s(ch[8], "流石に、これだけの数のジャマーを全部倒すの", 44);
		strncpy_s(ch[9], "は無理だから、早いとこ本当のラスボスを見つ", 44);
		strncpy_s(ch[10], "けないと……。", 44);
		strncpy_s(ch[11], "", 44);
		strncpy_s(name[3], "RUNA", 5);
		face[3] = 2;
		strncpy_s(ch[12], "ええ。", 44);
		strncpy_s(ch[13], "ネットワークの侵食も進んできてるし……。", 44);
		strncpy_s(ch[14], "", 44);
		strncpy_s(ch[15], "", 44);
		strncpy_s(name[4], "MIS", 5);
		face[4] = 3;
		strncpy_s(ch[16], "あー、もう時間がない！！", 44);
		strncpy_s(ch[17], "さっさとラスボス出て来―い！！", 44);
		strncpy_s(ch[18], "", 44);
		strncpy_s(ch[19], "", 44);
		strncpy_s(name[5], "RUNA", 5);
		face[5] = 1;
		strncpy_s(ch[20], "もう、そんなことで出て来るわけな―――", 44);
		strncpy_s(ch[21], "", 44);
		strncpy_s(ch[22], "", 44);
		strncpy_s(ch[23], "", 44);
		strncpy_s(name[6], "???", 5);
		strncpy_s(ch[24], "……貴様ラダナ？", 44);
		strncpy_s(ch[25], "俺ノ計画ヲコトゴトク邪魔シタノハ。", 44);
		strncpy_s(ch[26], "", 44);
		strncpy_s(ch[27], "", 44);
		strncpy_s(name[7], "RUNA", 5);
		face[7] = 2;
		strncpy_s(ch[28], "っ！！　誰？！", 44);
		strncpy_s(ch[29], "", 44);
		strncpy_s(ch[30], "", 44);
		strncpy_s(ch[31], "", 44);
		strncpy_s(name[8], "MIS", 5);
		face[8] = 4;
		strncpy_s(ch[32], "あっ、ルナちゃん！！", 44);
		strncpy_s(ch[33], "上！！　タワーの頂上に！！", 44);
		strncpy_s(ch[34], "", 44);
		strncpy_s(ch[35], "", 44);
		strncpy_s(name[9], "RUNA", 5);
		face[9] = 1;
		strncpy_s(ch[36], "頂上、ですって？", 44);
		strncpy_s(ch[37], "", 44);
		strncpy_s(ch[38], "", 44);
		strncpy_s(ch[39], "", 44);
		//ここでラスボス登場
		strncpy_s(name[10], "???", 5);
		face[10] = 0;
		strncpy_s(ch[40], "マアイイ、ドウセ数分後ニハ、", 44);
		strncpy_s(ch[41], "ネットワークヲ完全二掌握シテ、", 44);
		strncpy_s(ch[42], "ELATREMハ俺ノモノニナル。", 44);
		strncpy_s(ch[43], "", 44);
		strncpy_s(name[11], "???", 5);
		face[11] = 0;
		strncpy_s(ch[44], "貴様ラノ抵抗ハ、全テ徒労二終ワルワケダ。", 44);
		strncpy_s(ch[45], "", 44);
		strncpy_s(ch[46], "", 44);
		strncpy_s(ch[47], "", 44);
		strncpy_s(name[12], "RUNA", 5);
		face[12] = 2;
		strncpy_s(ch[48], "コイツが親玉のようね……。", 44);
		strncpy_s(ch[49], "", 44);
		strncpy_s(ch[50], "", 44);
		strncpy_s(ch[51], "", 44);
		strncpy_s(name[13], "MIS", 5);
		face[13] = 5;
		strncpy_s(ch[52], "うぅ、さっきまでのボスたちとは、", 44);
		strncpy_s(ch[53], "全然、違う……。", 44);
		strncpy_s(ch[54], "", 44);
		strncpy_s(ch[55], "", 44);
		strncpy_s(name[14], "???", 5);
		face[14] = 0;
		strncpy_s(ch[56], "アノ傀儡ドモト一緒ニスルナ。", 44);
		strncpy_s(ch[57], "", 44);
		strncpy_s(ch[58], "", 44);
		strncpy_s(ch[59], "", 44);
		strncpy_s(name[15], "???", 5);
		face[15] = 0;
		strncpy_s(ch[60], "俺ハコノProgramノ核―――", 44);
		strncpy_s(ch[61], "", 44);
		strncpy_s(ch[62], "", 44);
		strncpy_s(ch[63], "", 44);
		strncpy_s(name[16], "KERN", 5);
		face[16] = 1;
		strncpy_s(ch[64], "KERN(ケルン)ナノダカラナ。", 44);
		strncpy_s(ch[65], "", 44);
		strncpy_s(ch[66], "", 44);
		strncpy_s(ch[67], "", 44);
		strncpy_s(name[17], "MIS", 5);
		face[17] = 5;
		strncpy_s(ch[68], "……ケルン？", 44);
		strncpy_s(ch[69], "このプログラム郡の核？", 44);
		strncpy_s(ch[70], "", 44);
		strncpy_s(ch[71], "", 44);
		strncpy_s(name[18], "MIS", 5);
		face[18] = 5;
		strncpy_s(ch[72], "じゃあこのケルンを倒せば、", 44);
		strncpy_s(ch[73], "このプログラムは完全に停止するってこと？", 44);
		strncpy_s(ch[74], "", 44);
		strncpy_s(ch[75], "", 44);
		strncpy_s(name[19], "RUNA", 5);
		face[19] = 2;
		strncpy_s(ch[76], "ええ、おそらく。", 44);
		strncpy_s(ch[77], "でもこれだけジャマーがいると、", 44);
		strncpy_s(ch[78], "ケルンに近づくのも一苦労よ……。", 44);
		strncpy_s(ch[79], "", 44);
		strncpy_s(name[20], "MIS", 5);
		face[20] = 0;
		strncpy_s(ch[80], "それは任せて！！", 44);
		strncpy_s(ch[81], "私が何とかしてみせるから！！", 44);
		strncpy_s(ch[82], "", 44);
		strncpy_s(ch[83], "", 44);
		strncpy_s(name[21], "RUNA", 5);
		face[21] = 0;
		strncpy_s(ch[84], "……みす、何か逞しくなっちゃったわね。", 44);
		strncpy_s(ch[85], "", 44);
		strncpy_s(ch[86], "", 44);
		strncpy_s(ch[87], "", 44);
		strncpy_s(name[22], "MIS", 5);
		face[22] = 3;
		strncpy_s(ch[88], "だーかーらー、", 44);
		strncpy_s(ch[89], "子供じゃないって言ってるのに……。", 44);
		strncpy_s(ch[90], "", 44);
		strncpy_s(ch[91], "", 44);
		strncpy_s(name[23], "RUNA", 5);
		face[23] = 0;
		strncpy_s(ch[92], "あはは、ゴメンゴメン。", 44);
		strncpy_s(ch[93], "じゃあ、アンタにケルンは任せる。", 44);
		strncpy_s(ch[94], "アタシはネットワークの侵食を何とか遅らして", 44);
		strncpy_s(ch[95], "みるわ。", 44);
		strncpy_s(name[24], "MIS", 5);
		face[24] = 1;
		strncpy_s(ch[96], "うん、じゃあそっちはお願いするね！！", 44);
		strncpy_s(ch[97], "", 44);
		strncpy_s(ch[98], "", 44);
		strncpy_s(ch[99], "", 44);
		strncpy_s(name[25], "RUNA", 5);
		face[25] = 0;
		strncpy_s(ch[100], "アンタもしっかりやるのよ！！", 44);
		strncpy_s(ch[101], "", 44);
		strncpy_s(ch[102], "", 44);
		strncpy_s(ch[103], "", 44);
		strncpy_s(name[26], "MIS", 5);
		face[26] = 0;
		strncpy_s(ch[104], "分かった！！", 42);
		strncpy_s(ch[105], "……さぁ、私も行くよ！！", 42);
		strncpy_s(ch[106], "", 42);
		strncpy_s(ch[107], "", 42);
		strncpy_s(name[27], "KERN", 5);
		face[27] = 1;
		strncpy_s(ch[108], "俺ニ勝ツ気カ？　愚カナ……", 44);
		strncpy_s(ch[109], "", 44);
		strncpy_s(ch[110], "", 44);
		strncpy_s(ch[111], "", 44);
		strncpy_s(name[28], "KERN", 5);
		face[28] = 1;
		strncpy_s(ch[112], "ナラバ望ミ通リ、", 42);
		strncpy_s(ch[113], "貴様ヲ電子ノ塵ヘト変エテクレルワ！！", 42);
		strncpy_s(ch[114], "", 42);
		strncpy_s(ch[115], "", 42);

		ch_max = 116;
	}


		if (stage == 9) {
			last_picture[0] = LoadGraph("material/img/back/ending.png");
			strncpy_s(name[0], "", 5);
			strncpy_s(ch[0], "――― あれから数日。", 100);
			strncpy_s(ch[1], "エラトレムは平穏を取り戻しつつあった。", 100);
			strncpy_s(ch[2], "それは彼女達にもいつもの日常が戻ってきたことを意味していて―――", 100);
			strncpy_s(ch[3], "", 44);
			strncpy_s(name[1], "MIS", 5);
			face[1] = 1;
			strncpy_s(ch[4], "ルナちゃーん！！　おはよー！！", 100);
			strncpy_s(ch[5], "", 44);
			strncpy_s(ch[6], "", 44);
			strncpy_s(ch[7], "", 44);
			strncpy_s(name[2], "RUNA", 5);
			face[2] = 0;
			strncpy_s(ch[8], "みす？　どうしたの、こんな朝早くから。", 100);
			strncpy_s(ch[9], "", 44);
			strncpy_s(ch[10], "", 44);
			strncpy_s(ch[11], "", 44);
			strncpy_s(name[3], "RUNA", 5);
			face[3] = 2;
			strncpy_s(ch[12], "アタシ、もう少ししたら仕事に行かなきゃいけないんだけど……。", 100);
			strncpy_s(ch[13], "", 44);
			strncpy_s(ch[14], "", 44);
			strncpy_s(ch[15], "", 44);
			strncpy_s(name[4], "MIS", 5);
			face[4] = 3;
			strncpy_s(ch[16], "えー……。", 100);
			strncpy_s(ch[17], "あんなことがあったばっかりなのに、もう仕事してるの？", 44);
			strncpy_s(ch[18], "", 44);
			strncpy_s(ch[19], "", 44);
			strncpy_s(name[5], "RUNA", 5);
			face[5] = 2;
			strncpy_s(ch[20], "何度も言うけど、アタシの本業は壊れたデータの修復なの。", 100);
			strncpy_s(ch[21], "", 44);
			strncpy_s(ch[22], "", 44);
			strncpy_s(ch[23], "", 44);
			strncpy_s(name[6], "RUNA", 5);
			face[6] = 2;
			strncpy_s(ch[24], "『あんなこと』があったから、仕事まみれになってるんでしょ……。", 100);
			strncpy_s(ch[25], "はぁ……。", 44);
			strncpy_s(ch[26], "", 44);
			strncpy_s(ch[27], "", 44);
			strncpy_s(name[7], "MIS", 5);
			face[7] = 2;
			strncpy_s(ch[28], "あらら……", 100);
			strncpy_s(ch[29], "", 44);
			strncpy_s(ch[30], "", 44);
			strncpy_s(ch[31], "", 44);
			strncpy_s(name[8], "RUNA", 5);
			face[8] = 2;
			strncpy_s(ch[32], "そういえば、アンタの方は仕事ないの？", 100);
			strncpy_s(ch[33], "", 44);
			strncpy_s(ch[34], "", 44);
			strncpy_s(ch[35], "", 44);
			strncpy_s(name[9], "MIS", 5);
			face[9] = 1;
			strncpy_s(ch[36], "いやー。", 100);
			strncpy_s(ch[37], "何かみんなから『救世主サマだ！！』なんて祭り上げられちゃってさ。", 100);
			strncpy_s(ch[38], "", 44);
			strncpy_s(ch[39], "", 44);
			strncpy_s(name[10], "MIS", 5);
			face[10] = 1;
			strncpy_s(ch[40], "私の上司も、", 100);
			strncpy_s(ch[41], "『みすさんは、1週間くらい休んでていいから』", 100);
			strncpy_s(ch[42], "なんて言ってくれてー、エヘヘ。", 100);
			strncpy_s(ch[43], "", 44);
			strncpy_s(name[11], "RUNA", 5);
			face[11] = 0;
			strncpy_s(ch[44], "良いご身分ね……。", 100);
			strncpy_s(ch[45], "アタシもそんな職場にいたかったわ。", 44);
			strncpy_s(ch[46], "", 44);
			strncpy_s(ch[47], "", 44);
			strncpy_s(name[12], "RUNA", 5);
			face[12] = 1;
			strncpy_s(ch[48], "こっちの上司からは、", 100);
			strncpy_s(ch[49], "『ご苦労様だったな』", 100);
			strncpy_s(ch[50], "って笑顔で言われながら、大量の仕事渡されたわよ。", 100);
			strncpy_s(ch[51], "", 44);
			strncpy_s(name[13], "MIS", 5);
			face[13] = 2;
			strncpy_s(ch[52], "まあまあ、ルナちゃんの上司さんも頑張ってるんだろうから、そんなこ", 100);
			strncpy_s(ch[53], "と言わずに、ね？", 44);
			strncpy_s(ch[54], "", 44);
			strncpy_s(ch[55], "", 44);
			strncpy_s(name[14], "MIS", 5);
			face[14] = 0;
			strncpy_s(ch[56], "ところで、ルナちゃん。", 100);
			strncpy_s(ch[57], "今日は、何で私が朝から会いに来たか分かる？", 100);
			strncpy_s(ch[58], "", 44);
			strncpy_s(ch[59], "", 44);
			strncpy_s(name[15], "RUNA", 5);
			face[15] = 2;
			strncpy_s(ch[60], "え？　まさか、また何か異常でもあったの？", 100);
			strncpy_s(ch[61], "", 44);
			strncpy_s(ch[62], "", 44);
			strncpy_s(ch[63], "", 44);
			strncpy_s(name[16], "MIS", 5);
			face[16] = 3;
			strncpy_s(ch[64], "……", 100);
			strncpy_s(ch[65], "", 44);
			strncpy_s(ch[66], "", 44);
			strncpy_s(ch[67], "", 44);
			strncpy_s(name[17], "RUNA", 5);
			face[17] = 1;
			strncpy_s(ch[68], "やっぱりまだダメージの残ってる箇所があったのかしら……。", 100);
			strncpy_s(ch[69], "って、何よその目は。", 44);
			strncpy_s(ch[70], "", 44);
			strncpy_s(ch[71], "", 44);
			strncpy_s(name[18], "MIS", 5);
			face[18] = 3;
			strncpy_s(ch[72], "……やっぱり忘れてる。", 100);
			strncpy_s(ch[73], "", 44);
			strncpy_s(ch[74], "", 44);
			strncpy_s(ch[75], "", 44);
			strncpy_s(name[19], "RUNA", 5);
			face[19] = 2;
			strncpy_s(ch[76], "忘れてる？　何を？", 100);
			strncpy_s(ch[77], "", 44);
			strncpy_s(ch[78], "", 44);
			strncpy_s(ch[79], "", 44);
			strncpy_s(name[20], "MIS", 5);
			face[20] = 3;
			strncpy_s(ch[80], "ルナちゃん。　今日って、何月何日だっけ？", 100);
			strncpy_s(ch[81], "", 44);
			strncpy_s(ch[82], "", 44);
			strncpy_s(ch[83], "", 44);
			strncpy_s(name[21], "RUNA", 5);
			face[21] = 2;
			strncpy_s(ch[84], "何って、6月30日――あ。", 100);
			strncpy_s(ch[85], "", 44);
			strncpy_s(ch[86], "", 44);
			strncpy_s(ch[87], "", 44);
			strncpy_s(name[22], "MIS", 5);
			face[22] = 0;
			strncpy_s(ch[88], "そう、ルナちゃんの誕生日だよ！！", 100);
			strncpy_s(ch[89], "", 44);
			strncpy_s(ch[90], "", 44);
			strncpy_s(ch[91], "", 44);
			strncpy_s(name[23],"MIS", 5);
			face[23] = 3;
			strncpy_s(ch[92], "自分の誕生日ぐらいちゃんと覚えててよね。", 100);
			strncpy_s(ch[93], "まったくもう。", 44);
			strncpy_s(ch[94], "", 44);
			strncpy_s(ch[95], "", 44);
			strncpy_s(name[24], "RUNA", 5);
			face[24] = 0;
			strncpy_s(ch[96], "仕事漬けだったせいで、すっかり忘れてたわ……。", 100);
			strncpy_s(ch[97], "", 44);
			strncpy_s(ch[98], "", 44);
			strncpy_s(ch[99], "", 44);
			strncpy_s(name[25], "MIS", 5);
			strncpy_s(ch[100], "ということで、誕生日プレゼントを持ってきたの。", 100);
			strncpy_s(ch[101], "はい、これ！！", 100);
			strncpy_s(ch[102], "って言っても、時間がなかったから満足してもらえるか分からないんだ", 100);
			strncpy_s(ch[103], "けど……。", 44);
			strncpy_s(name[26], "RUNA", 5);
			strncpy_s(ch[104], "わざわざプレゼントくれに来てくれたの？", 100);
			strncpy_s(ch[105], "へぇ～、みすにしては意外に気が利くことするじゃない", 100);
			strncpy_s(ch[106], "", 44);
			strncpy_s(ch[107], "", 44);
			strncpy_s(name[27], "MIS", 5);
			strncpy_s(ch[108], "だーかーらー、『意外に』は余計だって！！", 100);
			strncpy_s(ch[109], "", 44);
			strncpy_s(ch[110], "", 44);
			strncpy_s(ch[111], "", 44);
			strncpy_s(name[28], "RUNA", 5);
			strncpy_s(ch[112], "ふふ、ありがとね。", 100);
			strncpy_s(ch[113], "早速開けても良いかしら？", 44);
			strncpy_s(ch[114], "", 44);
			strncpy_s(ch[115], "", 44);
			strncpy_s(name[29], "MIS", 5);
			strncpy_s(ch[116], "もっちろん！！", 100);
			strncpy_s(ch[117], "", 44);
			strncpy_s(ch[118], "", 44);
			strncpy_s(ch[119], "", 44);
			strncpy_s(name[30], "RUNA", 5);
			strncpy_s(ch[120], "じゃ、遠慮なく……。", 100);
			strncpy_s(ch[121], "", 44);
			strncpy_s(ch[122], "", 44);
			strncpy_s(ch[123], "", 44);
			strncpy_s(name[31], "RUNA", 5);
			strncpy_s(ch[124], "――っと、これはCD？", 100);
			strncpy_s(ch[125], "", 44);
			strncpy_s(ch[126], "", 44);
			strncpy_s(ch[127], "", 44);
			strncpy_s(name[32], "MIS", 5);
			strncpy_s(ch[128], "うん、そうだよ。", 100);
			strncpy_s(ch[129], "ルナちゃんのために、曲を作ってきたんだ～。", 100);
			strncpy_s(ch[130], "ルナちゃんって、作業中によく音楽聴いてるし、作曲は私の得意分野だ", 100);
			strncpy_s(ch[131], "し、ちょうどいいかなって。", 100);
			strncpy_s(name[33], "RUNA", 5);
			strncpy_s(ch[132], "そんなことまで覚えててくれたの……？", 100);
			strncpy_s(ch[133], "ええ、とっても嬉しいわ。", 44);
			strncpy_s(ch[134], "", 44);
			strncpy_s(ch[135], "", 44);
			strncpy_s(name[34], "MIS", 5);
			strncpy_s(ch[136], "そうだ！！", 100);
			strncpy_s(ch[137], "ねえ、ちょっとここで聴いてみてよ。", 44);
			strncpy_s(ch[138], "感想ももらいたいしね♪", 44);
			strncpy_s(ch[139], "", 44);
			strncpy_s(name[35], "RUNA", 5);
			strncpy_s(ch[140], "あら、いいの？", 100);
			strncpy_s(ch[141], "アタシ結構辛口よ？", 44);
			strncpy_s(ch[142], "", 44);
			strncpy_s(ch[143], "", 44);
			strncpy_s(name[36], "MIS", 5);
			strncpy_s(ch[144], "えー、そこはお手柔らかにお願いしたいなー、なんて。", 100);
			strncpy_s(ch[145], "", 44);
			strncpy_s(ch[146], "", 44);
			strncpy_s(ch[147], "", 44);
			strncpy_s(name[37], "RUNA", 5);
			strncpy_s(ch[148], "ふふ、善処するわ。", 100);
			strncpy_s(ch[149], "", 44);
			strncpy_s(ch[150], "", 44);
			strncpy_s(ch[151], "", 44);
			strncpy_s(name[38], "RUNA", 5);
			strncpy_s(ch[152], "さて、一体どんな曲なのかしら――", 100);
			strncpy_s(ch[153], "", 44);
			strncpy_s(ch[154], "", 44);
			strncpy_s(ch[155], "", 44);
			strncpy_s(name[39], "", 5);
			strncpy_s(ch[156], "……", 100);
			strncpy_s(ch[157], "…………", 44);
			strncpy_s(ch[158], "………………", 44);
			strncpy_s(ch[159], "……………………………………………………………………THE END.", 100);
			
			ch_max = 160;
		}
	}

	for (int i = 0; i < 3; i++) {
			if (strlen(ch[ch_i]) == 0) {//次の行が空白なら
				if (ch_i % 4 != 3) {
					ch_i++;
					i = 0;
				}
		}
	}

	if ((i > i_max - 2 || ch[ch_i][i] == '\0') && ch_i % 4 != 3) {//文が１行に入る文字数よりも少なく終わったら
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
			strncpy_s(str1, ch[ch_i], i);// iバイトまでの配列要素をstr配列にコピー
			str1[i] = '\0';            // 終端記号を代入
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

	// 配列の終端-2以下で、今回コピーするiまでの配列要素のi番目が\0じゃなくカウンターが5の倍数なら
		if (i <= i_max - 2 && ch[ch_i][i] != '\0' && counter % 5 == 0) {

			i += 2;                    // 全角文字なので配列要素2つずつカウントアップ
			switch (ch_i % 4) {
			case 0:
				if (i == 2) {
					strncpy_s(str2, ch[ch_i], 0);
					strncpy_s(str3, ch[ch_i], 0);
					strncpy_s(str4, ch[ch_i], 0);
				}
				strncpy_s(str5, name[ch_i/4], 5);
				strncpy_s(str1, ch[ch_i], i);// iバイトまでの配列要素をstr配列にコピー
				str1[i] = '\0';            // 終端記号を代入
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
			if (ch_i >= 100 && whiteout_counter != 0) {//一枚絵を出す会話が始まる時になったら
				out_mode = 1;
			}
		}

		Out();//画面のブラックアウト、ホワイトアウト


		if (stage == 9) {
			if (ch_i < 100){//一枚絵を出すタイミングより前なら
				//台詞を話していないキャラの描画
				SetDrawBright(150, 150, 150);//話していないキャラは暗くする
					if (strcmp(name[ch_i / 4], "MIS") != 0 && m_draw_flag == true) {
						DrawRotaGraphF(200, (FIELD_Y + FIELD_MAX_Y) / 2 + 70, 1.0f, 0.0f, mispic[m_face], TRUE);
					}
					if (strcmp(name[ch_i / 4], "RUNA") != 0 && r_draw_flag == true) {
						DrawRotaGraphF(WINDOW_X - 160, (FIELD_Y + FIELD_MAX_Y) / 2 + 70, 1.0f, 0.0f, runapic[r_face], TRUE);
					}
				SetDrawBright(255, 255, 255);

				//台詞を話しているキャラの描画
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
			SetDrawArea(FIELD_X, FIELD_Y, FIELD_X + FIELD_MAX_X, FIELD_Y + FIELD_MAX_Y);//描画可能エリアを設定

			//台詞を話していないキャラの描画
			SetDrawBright(150, 150, 150);//話していないキャラは暗くする
			if (stage == 8 && ch_i/4 > 9) {//ラスボスが居るとき
					if (strcmp(name[ch_i / 4], "???") != 0 && strcmp(name[ch_i / 4], "KERN") != 0) {
						DrawRotaGraphF(FIELD_X + FIELD_MAX_X - 100, (FIELD_Y + FIELD_MAX_Y) / 2 + 80, 1.0f, 0.0f, kernpic[k_face], TRUE);
					}
					else {
						if (m_talk_time > r_talk_time && m_draw_flag == true) {//みすの方がルナよりも後に会話している場合
							DrawRotaGraphF(FIELD_X + 100, (FIELD_Y + FIELD_MAX_Y) / 2 + 70, 1.0f, 0.0f, mispic[m_face], TRUE);
						}
						if (r_talk_time > m_talk_time && r_draw_flag == true) {//ルナの方がみすよりも後に会話している場合
							DrawRotaGraphF(FIELD_X + 100, (FIELD_Y + FIELD_MAX_Y) / 2 + 70, 1.0f, 0.0f, runapic[r_face], TRUE, TRUE);
						}
					}
				
			}
			else {//ラスボスがいなく(通常時で)プロローグでない(キャラを登場させる)とき
				if (strcmp(name[ch_i / 4], "MIS") != 0 && m_draw_flag==true) {//左にみす
					DrawRotaGraphF(FIELD_X + 100, (FIELD_Y + FIELD_MAX_Y) / 2 + 70, 1.0f, 0.0f, mispic[m_face], TRUE);
				}
				if (!(stage == 7 && ch_i/4 < 7) && strcmp(name[ch_i / 4], "RUNA") != 0 ) {//右側にルナ
					DrawRotaGraphF(FIELD_X + FIELD_MAX_X - 80, (FIELD_Y + FIELD_MAX_Y) / 2 + 70, 1.0f, 0.0f, runapic[r_face], TRUE);
				}
			}
			SetDrawBright(255, 255, 255);

			//台詞を話しているキャラの描画
			if (strcmp(name[ch_i / 4], "MIS") == 0) {
				m_face = face[ch_i / 4];
				m_talk_time = ch_i / 4;
				DrawRotaGraphF(FIELD_X + 100, (FIELD_Y + FIELD_MAX_Y) / 2 + 70, 1.0f, 0.0f, mispic[m_face], TRUE);
			}
			else if (strcmp(name[ch_i / 4], "RUNA") == 0) {
				r_face = face[ch_i / 4];
				r_talk_time = ch_i / 4;
				if (stage == 8 && ch_i / 4 > 9) {//ラスボスいるとき
					DrawRotaGraphF(FIELD_X + 100, (FIELD_Y + FIELD_MAX_Y) / 2 + 70, 1.0f, 0.0f, runapic[r_face], TRUE, TRUE);
				}
				else {
					DrawRotaGraphF(FIELD_X + FIELD_MAX_X - 80, (FIELD_Y + FIELD_MAX_Y) / 2 + 70, 1.0f, 0.0f, runapic[r_face], TRUE);
				}
			}
			else if (ch_i / 4 > 9 && (strcmp(name[ch_i / 4], "???") == 0 || strcmp(name[ch_i / 4], "KERN") == 0)) {//最初の条件は主人公達がラスボスを視認する(登場する)タイミング
				k_face = face[ch_i / 4];
				k_talk_time = ch_i / 4;
				DrawRotaGraphF(FIELD_X + FIELD_MAX_X - 100, (FIELD_Y + FIELD_MAX_Y) / 2 + 80, 1.0f, 0.0f, kernpic[k_face], TRUE);
			}

			SetDrawArea(0, 0, 640, 480);//描画可能エリアを設定
			if (strcmp(str5, "MIS") == 0) {//みすが喋ってるとき
				font_color = GetColor(255, 255, 255);
			}
			else if (strcmp(str5, "RUNA") == 0) {//ルナが喋っているとき
				font_color = GetColor(255, 255, 255);
			}
			else if ((strcmp(str5, "???") == 0) || strcmp(str5, "KERN")) {//ラスボスが喋っている時
				font_color = GetColor(255, 255, 255);
			}
		}

		DrawFormatStringToHandle(FIELD_X, 360, font_color, font[3], "%s", str5);//キャラ名
		DrawFormatStringToHandle(FIELD_X, 380, GetColor(255, 255, 255), font[2], "%s", str1);
		DrawFormatStringToHandle(FIELD_X, 400, GetColor(255, 255, 255), font[2], "%s", str2);
		DrawFormatStringToHandle(FIELD_X, 420, GetColor(255, 255, 255), font[2], "%s", str3);
		DrawFormatStringToHandle(FIELD_X, 440, GetColor(255, 255, 255), font[2], "%s", str4);
		

	counter++;
	if (ch_i >= ch_max || (Controller.k_Get(Config.k_start) == 1 || Controller.g_Get(Config.g_start) == 1)) {//シナリオ終了時の処理
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


//----------ステージをいじるのに使うデバッグ用の関数(完成品では使わない)----------//
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

//----------難易度をいじるのに使うデバッグ用の関数(完成品では使わない)----------//
//(注)：難易度を変えた後は必ずステージを選択し直すこと(そうしないと敵データのロードが正常に行われないため)
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
		if (errno_t error = fopen_s(&fp, "score.dat", "wb") != 0) {  // ファイルを開く
			return 0;
		}
		fwrite(&highscore, sizeof(int), 3, fp); // ファイルにhighscoreの値を出力する
		fclose(fp); //ファイルを閉じる
	}
	return 0;
}
int Control_c::ReadHighScore() {
	FILE *fp;
	if (errno_t error = fopen_s(&fp, "score.dat", "rb") != 0) {
		return 0;
	}
	fread(&highscore, sizeof(int), 3, fp); //ファイルからhighscoreに値を出力する
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

	SetDrawArea(FIELD_X, FIELD_Y, FIELD_X + FIELD_MAX_X, FIELD_Y + FIELD_MAX_Y);//描画可能エリアを設定
	//if (mode != game_play) {
		SetDrawBright(120, 120, 120);
	//}

	Back.DrawStage();
	Enemy.DrawEnemy();
	Boss.DrawBoss();
	Player.Draw();
	Effect.DrawEffect();

	SetDrawBright(255, 255, 255);
	
	SetDrawArea(0, 0, 640, 480);//エリアを戻す


	Boss.DrawHpBar();
}

void Control_c::Continue() {
	if (mode == retry) {
		if (erosion >= EROSION_MAX*0.8) {
			erosion = EROSION_MAX;
			mode = gameover;
		}
		//コマンドの位置の制御
		for (int i = 0; i < rcom_num; i++) {
			if (retry_com == i) {
				rx[i] = 255;
			}
			else {
				rx[i] = 120;
			}
		}

		DrawStopTime();
		DrawStringToHandle(148, 200, "コンティニュー", GetColor(rx[0], rx[0], rx[0]), font[1]);
		DrawStringToHandle(148, 250, "タイトルに戻る", GetColor(rx[1], rx[1], rx[1]), font[1]);

		if (Controller.k_Get(Config.k_up) == 1 || Controller.g_Get(Config.g_up) == 1) {
			retry_com = (retry_com + rcom_num - 1) % rcom_num;
		}else if (Controller.k_Get(Config.k_down) == 1 || Controller.g_Get(Config.g_down) == 1) {
			retry_com = (retry_com + 1) % rcom_num;
		}
		
			switch (retry_com) {
			case playagain:
				//決定キー押した後の操作
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
		mode = retry; //コンティニューするかどうか聞く画面を出す
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

		//コマンドの位置の制御
		for (int i = 0; i < pcom_num; i++) {
			if (pause_com== i) {
				px[i] = 255;
			}
			else {
				px[i] = 120;
			}
		}
		DrawStopTime();
		DrawStringToHandle(158, 200, "ゲームに戻る", GetColor(px[0], px[0], px[0]), font[1]);
		DrawStringToHandle(105, 250, "ステージを最初からやる", GetColor(px[1], px[1], px[1]), font[1]);
		DrawStringToHandle(148, 300, "タイトルに戻る", GetColor(px[2], px[2], px[2]), font[1]);
		
		if (Controller.k_Get(Config.k_up) == 1 || Controller.g_Get(Config.g_up) == 1) {
			pause_com = (pause_com + pcom_num - 1) % pcom_num;
		}
		else if (Controller.k_Get(Config.k_down) == 1 || Controller.g_Get(Config.g_down) == 1) {
			pause_com = (pause_com + 1) % pcom_num;
		}

		switch (pause_com) {
		case play:
			//決定キー押した後の操作
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

//----------デバッグに必要な要素を表示する関数(完成品では使わない)----------//

void Control_c::DrawMaskData() {
	if (mode == game_play && state != s5_talk_l) {

		DrawFormatString(0, 0, GetColor(255, 255, 255), "%c-%d", level, (state + 1)/2);
		DrawFormatString(0, 15, GetColor(255, 255, 255), "%d", g_count);
	}
}
