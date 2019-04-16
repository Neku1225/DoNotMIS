#include "define.h"

//“n‚³‚ê‚½-ang`ang‚Ü‚Å‚Ìƒ‰ƒ“ƒ_ƒ€‚ÈŠp“x‚ğ•Ô‚·
double Enemy_obj::Rang(double ang){
	return (-ang + ang * 2 * GetRand(10000) / 10000.0);
}

//“G‚Ìƒpƒ^[ƒ“•Ê‚Å‚ÌˆÚ“®§Œä
void Enemy_obj::Move(int i){
	switch (enemy[i].pattern){
	case 0:
		if (enemy[i].counter < 60){
			enemy[i].vy = 2;
		}
		if (enemy[i].counter == 60){
			enemy[i].vy = 0;
		}
		if (enemy[i].counter > 60 + enemy[i].wait){
			enemy[i].vy = -2;
		}
		break;
	case 1:
		if (enemy[i].counter == 0){
			enemy[i].vy = 3;//‰º‚ª‚Á‚Ä‚­‚é
		}
		if (enemy[i].counter == 40){
			enemy[i].vy = 0;//~‚Ü‚é
		}
		if (enemy[i].counter == 40 + enemy[i].wait){//“o˜^‚³‚ê‚½ŠÔ‚¾‚¯’â‘Ø‚µ‚Ä
			enemy[i].vx = -1;//¶‚Ö
			enemy[i].vy = 2;//‰º‚ª‚Á‚Ä‚¢‚­
			enemy[i].direction = 0;//¶Œü‚«ƒZƒbƒg
		}
		break;
	case 2:
		if (enemy[i].counter == 0){
			enemy[i].vy = 3;//‰º‚ª‚Á‚Ä‚­‚é
		}
		if (enemy[i].counter == 40){
			enemy[i].vy = 0;//~‚Ü‚é
		}
		if (enemy[i].counter == 40 + enemy[i].wait){//“o˜^‚³‚ê‚½ŠÔ‚¾‚¯’â‘Ø‚µ‚Ä
			enemy[i].vx = 1;//‰E‚Ö
			enemy[i].vy = 2;//‰º‚ª‚Á‚Ä‚¢‚­
			enemy[i].direction = 2;//‰EŒü‚«ƒZƒbƒg
		}
		break;
	case 3:
		if (enemy[i].counter == 0){
			enemy[i].vy = 5;//‰º‚ª‚Á‚Ä‚­‚é
		}
		if (enemy[i].counter == 30){//“r’†‚Å¶Œü‚«‚É
			enemy[i].direction = 0;
		}
		if (enemy[i].counter<100){
			enemy[i].vx -= 5 / 100.0;//¶Œü‚«‰Á‘¬
			enemy[i].vy -= 5 / 100.0;//Œ¸‘¬
		}
		break;
	case 4:
		if (enemy[i].counter == 0){
			enemy[i].vy = 5;//‰º‚ª‚Á‚Ä‚­‚é
		}
		if (enemy[i].counter == 30){//“r’†‚Å‰EŒü‚«‚É
			enemy[i].direction = 2;
		}
		if (enemy[i].counter<100){
			enemy[i].vx += 5 / 100.0;//‰EŒü‚«‰Á‘¬
			enemy[i].vy -= 5 / 100.0;//Œ¸‘¬
		}
		break;
	case 5:
		if (enemy[i].counter == 0){
			enemy[i].vx -= 1;
			enemy[i].vy = 2;
			enemy[i].direction = 0;
		}
		break;
	case 6:
		if (enemy[i].counter == 0){
			enemy[i].vx += 1;
			enemy[i].vy = 2;
			enemy[i].direction = 2;
		}
		break;
	case 7:
		if (enemy[i].counter == enemy[i].wait){//“o˜^‚³‚ê‚½ŠÔ‚¾‚¯’â‘Ø‚µ‚Ä
			enemy[i].vx = -0.7;//¶‚Ö
			enemy[i].vy = -0.3;//ã‚ª‚Á‚Ä‚¢‚­
			enemy[i].direction = 0;//¶Œü‚«
		}
		break;
	case 8:
		if (enemy[i].counter == enemy[i].wait){//“o˜^‚³‚ê‚½ŠÔ‚¾‚¯’â‘Ø‚µ‚Ä
			enemy[i].vx = +0.7;//‰E‚Ö
			enemy[i].vy = -0.3;//ã‚ª‚Á‚Ä‚¢‚­
			enemy[i].direction = 2;//‰EŒü‚«
		}
		break;
	case 9:
		if (enemy[i].counter == enemy[i].wait){//“o˜^‚³‚ê‚½ŠÔ‚¾‚¯’â‘Ø‚µ‚Ä
			enemy[i].vy = -1;//ã‚ª‚Á‚Ä‚¢‚­
	}
		break;
	case 10:
		if (enemy[i].counter == 0) enemy[i].vy = 4;//‰º‚ª‚Á‚Ä‚­‚é
		if (enemy[i].counter == 40)enemy[i].vy = 0;//~‚Ü‚é
		if (enemy[i].counter >= 40){
			if (enemy[i].counter % 60 == 0){
				int r = cos(enemy[i].angle)< 0 ? 0 : 1;
				enemy[i].speed = 6 + Rang(2);
				enemy[i].angle = Rang(M_PI / 4) + M_PI*r;
				enemy[i].direction = 2 - 2 * r;
			}
			enemy[i].speed *= 0.95;
		}
		if (enemy[i].counter >= 40 + enemy[i].wait){
			enemy[i].vy -= 0.05;
		}
		break;
	case 11:
		if (enemy[i].counter == 0) {
			enemy[i].vx = -1.5;//¶‚Ö
			enemy[i].vy = -3;//ã‚ª‚Á‚Ä‚¢‚­
			enemy[i].direction = 0;//¶Œü‚«
		}
		break;
	case 12:
		if (enemy[i].counter == 0) {
			enemy[i].vx = 1.5;//‰E‚Ö
			enemy[i].vy = -3;//ã‚ª‚Á‚Ä‚¢‚­
			enemy[i].direction = 2;//‰EŒü‚«
		}
		break;
	case 13:
		if (enemy[i].counter == 0) {
			enemy[i].vx = -3;//¶‚Ö
			enemy[i].direction = 0;//¶Œü‚«
		}
		break;
	case 14:
		if (enemy[i].counter == 0) {
			enemy[i].vx = 3;//‰E‚Ö
			enemy[i].direction = 2;//‰EŒü‚«
		}
		break;
	case 15://¶‰º¶ã
		if (enemy[i].counter < 20) {
			enemy[i].vx -= 0.3;
			enemy[i].vy += 0.5;
			enemy[i].direction = 0;
		}
		if (enemy[i].counter == 20) {
			enemy[i].vx = 0;
			enemy[i].vy = 0;
		}
		if (enemy[i].counter > 20 + enemy[i].wait) {//“o˜^‚³‚ê‚½ŠÔ‚¾‚¯’â‘Ø‚µ‚Ä
			enemy[i].vx -= 0.5;
			enemy[i].vy -= 0.5;//ã‚ª‚Á‚Ä‚¢‚­
		}
		break;
	case 16://‰E‰º‰Eã
		if (enemy[i].counter < 20) {
			enemy[i].vx += 0.3;
			enemy[i].vy += 0.5;
			enemy[i].direction = 2;
		}
		if (enemy[i].counter == 20) {
			enemy[i].vx = 0;
			enemy[i].vy = 0;
		}
		if (enemy[i].counter > 20 + enemy[i].wait) {//“o˜^‚³‚ê‚½ŠÔ‚¾‚¯’â‘Ø‚µ‚Ä
			enemy[i].vx += 0.5;
			enemy[i].vy -= 0.5;//ã‚ª‚Á‚Ä‚¢‚­
		}
		break;
	case 17://‰E‰º
		if (enemy[i].counter == 0) {
			enemy[i].vx += 0.8;
			enemy[i].vy += 0.9;
			enemy[i].direction = 2;
		}
		break;
	case 18://¶‰º
		if (enemy[i].counter == 0) {
			enemy[i].vx -= 0.8;
			enemy[i].vy += 0.9;
			enemy[i].direction = 0;
		}
		break;
	case 19:
		if (enemy[i].counter == 0) {
			enemy[i].vy = 5;//‰º‚ª‚Á‚Ä‚­‚é
		}
		if (enemy[i].counter == 30) {//“r’†‚Å¶Œü‚«‚É
			enemy[i].direction = 0;
		}
		if (enemy[i].counter<100) {
			enemy[i].vx -= 2.5 / 100.0;//¶Œü‚«‰Á‘¬
			enemy[i].vy -= 5 / 100.0;//Œ¸‘¬
		}
		break;
	case 20:
		if (enemy[i].counter == 0) {
			enemy[i].vy = 5;//‰º‚ª‚Á‚Ä‚­‚é
		}
		if (enemy[i].counter == 30) {//“r’†‚Å‰EŒü‚«‚É
			enemy[i].direction = 2;
		}
		if (enemy[i].counter<100) {
			enemy[i].vx += 2.5 / 100.0;//‰EŒü‚«‰Á‘¬
			enemy[i].vy -= 5 / 100.0;//Œ¸‘¬
		}
		break;
	}
}