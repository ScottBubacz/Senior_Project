#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

ifstream indata;
ifstream inSert;

struct playerStats {
	string name;
	int min, gp, gs;
	double  fg, fga, tfg, tfga, ft, fta, orb, drb, asts, stls, blks, tov, pfs;
	bool fieldGoal, three, free, offreb, deereb, assis, stel, blok, turov, pfoul;
	bool out, justpassed, checkfoul, hasball, blkchance;
	//final stats
	double secPlayed;
	int pts, fgm, fgat, tfgm, tfgat, ftm, ftat, oreb, dreb, assists, steals, blocks, tovs, fouls;

};

struct team {
	int score, poss;
	playerStats roster[12];
	int q1, q2, q3, q4, ot;
};


void setStats(team& pros, team& joes, ifstream& indata, ifstream& inSert);
void randomize(int& num);
void chance(double& num);
void game(team& pros, team& joes, int& count, double& secGame, bool& turnov, double& shotClock);
void possession(team& pros, team& joes, int& count, double& secGame, bool& turnov, double& shotClock);
void quarter1(team& pros, team& joes, int& count, double& secGame, bool& turnov, double& shotClock);
void quarter2(team& pros, team& joes, int& count, double& secGame, bool& turnov, double& shotClock);
void quarter3(team& pros, team& joes, int& count, double& secGame, bool& turnov, double& shotClock);
void quarter4(team& pros, team& joes, int& count, double& secGame, bool& turnov, double& shotClock);
void overtime(team& pros, team& joes, int& count, double& secGame, bool& turnov, double& shotClock);
void setFieldGoal(team& pros);
void setThreePoint(team& pros);
void setFreeThrow(team& pros);
void setORebound(team& pros);
void setDRebound(team& pros);
void setAssists(team& pros);
void setSteals(team& pros);
void setBlocks(team& pros);
void setTurnovers(team& pros);
void setFouls(team& pros);
void detFreeThrow(team& pros, team& joes, int attempts);
void detRebound(team& pros, team& joes, int& count);
void detBlock(team& pros);
void detAfterPass(team& pros, team& joes, bool& turnov);
void detAssist(team& pros);
void detShotClock(team& pros, bool& turnov, double& secGame, double& shotClock);
void setTimePlayed(team& pros, team& joes, double& secGame);
void substitution(team& pros);
void boxscore(team& pros, team& joes);

int main() {
	int pcount;
	double games, sClock;
	bool turv;

	indata.open("Sixers.txt");
	inSert.open("Lakers.txt");
	team sixer;
	team laker;


	setStats(sixer, laker, indata, inSert);

	/*for (int i = 0; i < 12; i++) {
		cout << sixer.roster[i].name << sixer.roster[i].min << sixer.roster[i].gp << sixer.roster[i].gs << sixer.roster[i].fg <<
			sixer.roster[i].fga << sixer.roster[i].tfg << sixer.roster[i].tfga << sixer.roster[i].ft << sixer.roster[i].fta << sixer.roster[i].orb <<
			sixer.roster[i].drb << sixer.roster[i].asts << sixer.roster[i].stls << sixer.roster[i].blks << sixer.roster[i].tov << sixer.roster[i].pfs << endl;
	}*/

	game(sixer, laker, pcount, games, turv, sClock);
	//cout << pcount << endl;
	indata.close();
	inSert.close();

	cout << sixer.score << endl;
	cout << laker.score << endl;
	boxscore(sixer, laker);
}

void setStats(team& pros, team& joes, ifstream& indata, ifstream& inSert) {
	for (int i = 0; i < 12; i++) {
		indata >> pros.roster[i].name >> pros.roster[i].min >> pros.roster[i].gp >> pros.roster[i].gs >> pros.roster[i].fg >>
			pros.roster[i].fga >> pros.roster[i].tfg >> pros.roster[i].tfga >> pros.roster[i].ft >> pros.roster[i].fta >> pros.roster[i].orb >>
			pros.roster[i].drb >> pros.roster[i].asts >> pros.roster[i].stls >> pros.roster[i].blks >> pros.roster[i].tov >> pros.roster[i].pfs;
	}
	for (int i = 0; i < 12; i++) {
		inSert >> joes.roster[i].name >> joes.roster[i].min >> joes.roster[i].gp >> joes.roster[i].gs >> joes.roster[i].fg >>
			joes.roster[i].fga >> joes.roster[i].tfg >> joes.roster[i].tfga >> joes.roster[i].ft >> joes.roster[i].fta >> joes.roster[i].orb >>
			joes.roster[i].drb >> joes.roster[i].asts >> joes.roster[i].stls >> joes.roster[i].blks >> joes.roster[i].tov >> joes.roster[i].pfs;
	}
}
void game(team& pros, team& joes, int& count, double& secGame, bool& turnov, double& shotClock) {
	while (secGame <= 720.00) {
		if (count % 2 == 0) {
			quarter1(pros, joes, count, secGame, turnov, shotClock);
		}
		else {
			quarter1(joes, pros, count, secGame, turnov, shotClock);
		}
	}
	secGame = 720.00;
	while (secGame > 720.00 && secGame <= 1440.00) {
		if (count % 2 == 0) {
			quarter2(pros, joes, count, secGame, turnov, shotClock);
		}
		else {
			quarter2(joes, pros, count, secGame, turnov, shotClock);
		}
	}
	secGame = 1440.00;
	while (secGame > 1440.00 && secGame <= 2160.00) {
		if (count % 2 == 0) {
			quarter3(pros, joes, count, secGame, turnov, shotClock);
		}
		else {
			quarter3(joes, pros, count, secGame, turnov, shotClock);
		}
	}
	secGame = 2160.00;
	while (secGame > 2160.00 && secGame <= 2880.00) {
		if (count % 2 == 0) {
			quarter4(pros, joes, count, secGame, turnov, shotClock);
		}
		else {
			quarter4(joes, pros, count, secGame, turnov, shotClock);
		}
	}
	secGame = 2880.00;
	if (pros.score == joes.score) {
		while (secGame > 2880.00 && secGame <= 3180.00) {
			if (count % 2 == 0) {
				overtime(pros, joes, count, secGame, turnov, shotClock);
			}
			else {
				overtime(joes, pros, count, secGame, turnov, shotClock);
			}
		}
		secGame = 3180.00;
		if (pros.score == joes.score) {
			while (secGame > 3180.00 && secGame <= 3480.00) {
				if (count % 2 == 0) {
					overtime(pros, joes, count, secGame, turnov, shotClock);
				}
				else {
					overtime(joes, pros, count, secGame, turnov, shotClock);
				}
			}
			secGame = 3480.00;
			if (pros.score == joes.score) {
				while (secGame > 3480.00 && secGame <= 3780.00) {
					if (count % 2 == 0) {
						overtime(pros, joes, count, secGame, turnov, shotClock);
					}
					else {
						overtime(joes, pros, count, secGame, turnov, shotClock);
					}
				}
			}
		}
	}
}
void randomize(int& num) {
	srand((unsigned)time(NULL));
	num = (rand() % 10) / 2;
	if (num == 5) {
		randomize(num);
	}
}
void chance(double& num) {
	srand((unsigned)time(NULL));
	float x = (float) rand() / RAND_MAX;
	num = static_cast<double>(x);
}
void possession(team& pros, team& joes, int& count, double& secGame, bool& turnov, double& shotClock) {
	int x;
	double choice;
	randomize(x);
	chance(choice);
	double shotMake = (pros.roster[x].tfg / pros.roster[x].tfga);
	double shotPick = (pros.roster[x].tfga / pros.roster[x].fga);
	double shotTMake = ((pros.roster[x].fg - pros.roster[x].tfg) / (pros.roster[x].fga - pros.roster[x].tfga));
	if (pros.roster[x].justpassed == false) {
		pros.roster[x].hasball = true;
		if (choice <= (pros.roster[x].fga / 100)) {
			chance(choice);
			cout << choice;
			if (choice <= shotPick) {
				chance(choice);
				if (choice <= shotMake) {
					pros.roster[x].three = true;
					setThreePoint(pros);
					pros.poss++;
					pros.score = pros.score + 3;
					detAssist(pros);
					joes.roster[x].checkfoul = true;
					detFreeThrow(pros, joes, 1);
					if (pros.roster[x].free == false) {
						detRebound(pros, joes, count);
					}
					else {
						count++;
						pros.roster[x].free = false;
					}
					secGame = secGame + shotClock;
					setTimePlayed(pros, joes, secGame);
					pros.roster[x].hasball = false;
					shotClock = 8;
				}
				else
				{
					setThreePoint(pros);
					pros.poss++;
					joes.roster[x].checkfoul = true;
					detFreeThrow(pros, joes, 3);
					if (pros.roster[x].free == true) {
						count++;
						pros.roster[x].free = false;
					}
					else {
						joes.roster[x].blkchance = true;
						detBlock(joes);
						detRebound(pros, joes, count);
					}
					secGame = secGame + shotClock;
					setTimePlayed(pros, joes, secGame);
					pros.roster[x].hasball = false;
					shotClock = 8;
				}
			}
			else {
				chance(choice);
				if (choice <= shotTMake) {
					setFieldGoal(pros);
					pros.score = pros.score + 2;
					pros.poss++;
					detAssist(pros);
					detFreeThrow(pros, joes, 1);
					if (pros.roster[x].free == false) {
						detRebound(pros, joes, count);
					}
					else {
						count++;
						pros.roster[x].free = false;
					}
					secGame = secGame + shotClock;
					setTimePlayed(pros, joes, secGame);
					pros.roster[x].hasball = false;
					shotClock = 8;
				}
				else {
					setFieldGoal(pros);
					pros.poss++;
					detFreeThrow(pros, joes, 2);
					if (pros.roster[x].free == true) {
						count++;
						pros.roster[x].free = false;
					}
					else {
						joes.roster[x].blkchance = true;
						detBlock(joes);
						detRebound(pros, joes, count);
					}
					secGame = secGame + shotClock;
					setTimePlayed(pros, joes, secGame);
					pros.roster[x].hasball = false;
					shotClock = 8;
				}
			}
		}
		else {
			for (int i = 0; i < 5; i++) {
				pros.roster[i].justpassed = false;
			}
			pros.roster[x].justpassed = true;
			detShotClock(pros, turnov, secGame, shotClock);
			if (turnov == true) {
				count++;
				pros.roster[x].justpassed = false;
				turnov = false;
			}
			else {
				detAfterPass(pros, joes, turnov);
				if (turnov == true) {
					pros.poss++;
					turnov = false;
					pros.roster[x].justpassed = false;
					count++;
					secGame = secGame + shotClock;
					setTimePlayed(pros, joes, secGame);
					shotClock = 8;
				}
				else {
					count += 2;
				}
			}
			pros.roster[x].hasball = false;
		}
	}
	else {
		count += 2;
	}
}

void quarter1(team& pros, team& joes, int& count, double& secGame, bool& turnov, double& shotClock) {
	possession(pros, joes, count, secGame, turnov, shotClock);
	substitution(pros);
	substitution(joes);
	pros.q1 = pros.score;
	joes.q1 = joes.score;
}
void quarter2(team& pros, team& joes, int& count, double& secGame, bool& turnov, double& shotClock) {
	possession(pros, joes, count, secGame, turnov, shotClock);
	substitution(pros);
	substitution(joes);
	pros.q2 = pros.score - pros.q1;
	joes.q2 = joes.score - joes.q1;
}
void quarter3(team& pros, team& joes, int& count, double& secGame, bool& turnov, double& shotClock) {
	possession(pros, joes, count, secGame, turnov, shotClock);
	substitution(pros);
	substitution(joes);
	pros.q3 = pros.score - (pros.q1 + pros.q2);
	joes.q3 = joes.score - (joes.q1 + joes.q2);
}
void quarter4(team& pros, team& joes, int& count, double& secGame, bool& turnov, double& shotClock) {
	possession(pros, joes, count, secGame, turnov, shotClock);
	substitution(pros);
	substitution(joes);
	pros.q4 = pros.score - (pros.q1 + pros.q2 + pros.q3);
	joes.q4 = joes.score - (joes.q1 + joes.q2 + joes.q3);
}
void overtime(team& pros, team& joes, int& count, double& secGame, bool& turnov, double& shotClock) {
	possession(pros, joes, count, secGame, turnov, shotClock);
	pros.ot = pros.score - (pros.q1 + pros.q2 + pros.q3 + pros.q4);
	joes.ot = joes.score - (joes.q1 + joes.q2 + joes.q3 + joes.q4);
}
void setFieldGoal(team& pros) {
	for (int i = 0; i < 4; i++) {
		if (pros.roster[i].fieldGoal == false) {
			pros.roster[i].fgat += 1;
		}
		else if (pros.roster[i].fieldGoal == true) {
			pros.roster[i].fgat += 1;
			pros.roster[i].fgm += 1;
			pros.roster[i].pts += 2;
			pros.roster[i].fieldGoal = false;
		}
	}
}
void setThreePoint(team& pros) {
	for (int i = 0; i < 4; i++) {
		if (pros.roster[i].three == false) {
			pros.roster[i].tfgat += 1;
			pros.roster[i].fgat += 1;
		}
		if (pros.roster[i].three == true) {
			pros.roster[i].tfgm += 1;
			pros.roster[i].fgm += 1;
			pros.roster[i].pts += 3;
			pros.roster[i].tfgat += 1;
			pros.roster[i].fgat += 1;
			pros.roster[i].three = false;
		}
	}
}
void setFreeThrow(team& pros) {
	for (int i = 0; i < 4; i++) {
		if (pros.roster[i].free == false) {
			pros.roster[i].ftat += 1;
		}
		else if (pros.roster[i].free == true) {
			pros.roster[i].ftat += 1;
			pros.roster[i].ftm += 1;
			pros.roster[i].pts += 1;
		}
	}
}
void setORebound(team& pros) {
	for (int i = 0; i < 4; i++) {
		if (pros.roster[i].offreb == true) {
			pros.roster[i].oreb += 1;
			pros.roster[i].offreb = false;
		}
	}
}
void setDRebound(team& pros) {
	for (int i = 0; i < 4; i++) {
		if (pros.roster[i].deereb == true) {
			pros.roster[i].dreb += 1;
			pros.roster[i].deereb = false;
		}
	}
}
void setAssists(team& pros) {
	for (int i = 0; i < 4; i++) {
		if (pros.roster[i].assis == true) {
			pros.roster[i].assists += 1;
			pros.roster[i].assis = false;
		}
	}
}
void setSteals(team& pros) {
	for (int i = 0; i < 4; i++) {
		if (pros.roster[i].stel == true) {
			pros.roster[i].steals += 1;
			pros.roster[i].stel = false;
		}
	}
}
void setBlocks(team& pros) {
	for (int i = 0; i < 4; i++) {
		if (pros.roster[i].blok == true) {
			pros.roster[i].blocks += 1;
			pros.roster[i].blok = false;
		}
	}
}
void setTurnovers(team& pros) {
	for (int i = 0; i < 4; i++) {
		if (pros.roster[i].turov == true) {
			pros.roster[i].tovs += 1;
			pros.roster[i].turov = false;
		}
	}
}
void setFouls(team& pros) {
	for (int i = 0; i < 4; i++) {
		if (pros.roster[i].pfoul == true) {
			pros.roster[i].fouls += 1;
			if (pros.roster[i].fouls == 6) {
				pros.roster[i].out = true;
			}
			pros.roster[i].pfoul = false;
		}
	}
}
void detFreeThrow(team& pros, team& joes, int attempts) {
	double x;
	chance(x);
	for (int i = 0; i < 4; i++) {
		if (joes.roster[i].checkfoul == true) {
			if (x <= (joes.roster[i].pfs / 100)) {
				joes.roster[i].pfoul = true;
				setFouls(joes);
				double freeThrow = (pros.roster[i].ft / pros.roster[i].fta);
				while (attempts > 1) {
					chance(x);
					if (x <= freeThrow) {
						pros.roster[i].free = true;
						setFreeThrow(pros);
						pros.score++;
					}
					else {
						setFreeThrow(pros);
					}
					attempts--;
				};
				chance(x);
				if (x <= freeThrow) {
					pros.roster[i].free = true;
					pros.score++;
					setFreeThrow(pros);
				}
				else {
					setFreeThrow(pros);
				}
			}
		}
	}
}
void detRebound(team& pros, team& joes, int& count) {
	double oreb1, oreb2, oreb3, oreb4, oreb5, dreb1, dreb2, dreb3, dreb4, dreb5, x;
	oreb1 = pros.roster[0].orb / 100;
	oreb2 = pros.roster[1].orb / 100;
	oreb3 = pros.roster[2].orb / 100;
	oreb4 = pros.roster[3].orb / 100;
	oreb5 = pros.roster[4].orb / 100;
	dreb1 = joes.roster[0].drb / 100;
	dreb2 = joes.roster[1].drb / 100;
	dreb3 = joes.roster[2].drb / 100;
	dreb4 = joes.roster[3].drb / 100;
	dreb5 = joes.roster[4].drb / 100;
	double totalRebound = (oreb1 + oreb2 + oreb3 + oreb4 + oreb5 + dreb1 + dreb2 + dreb3 + dreb4 + dreb5 + .05);
	double orebound1 = totalRebound - (oreb2 + oreb3 + oreb4 + oreb5 + dreb1 + dreb2 + dreb3 + dreb4 + dreb5 + .05);
	double orebound2 = totalRebound - (oreb3 + oreb4 + oreb5 + dreb1 + dreb2 + dreb3 + dreb4 + dreb5 + .05);
	double orebound3 = totalRebound - (oreb4 + oreb5 + dreb1 + dreb2 + dreb3 + dreb4 + dreb5 + .05);
	double orebound4 = totalRebound - (oreb5 + dreb1 + dreb2 + dreb3 + dreb4 + dreb5 + .05);
	double orebound5 = totalRebound - (dreb1 + dreb2 + dreb3 + dreb4 + dreb5 + .05);
	double drebound1 = totalRebound - (dreb2 + dreb3 + dreb4 + dreb5 + .05);
	double drebound2 = totalRebound - (dreb3 + dreb4 + dreb5 + .05);
	double drebound3 = totalRebound - (dreb4 + dreb5 + .05);
	double drebound4 = totalRebound - (dreb5 + .05);
	double drebound5 = totalRebound - .05;
	chance(x);
	if (x <= orebound1) {
		pros.roster[0].offreb = true;
		setORebound(pros);
		count += 2;
	}
	else if (x <= orebound2 && x > orebound1) {
		pros.roster[1].offreb = true;
		setORebound(pros);
		count += 2;
	}
	else if (x <= orebound3 && x > orebound2) {
		pros.roster[2].offreb = true;
		setORebound(pros);
		count += 2;
	}
	else if (x <= orebound4 && x > orebound3) {
		pros.roster[3].offreb = true;
		setORebound(pros);
		count += 2;
	}
	else if (x <= orebound5 && x > orebound4) {
		pros.roster[4].offreb = true;
		setORebound(pros);
		count += 2;
	}
	else if (x <= drebound1 && x > orebound5) {
		joes.roster[0].deereb = true;
		setDRebound(joes);
		count++;
	}
	else if (x <= drebound2 && x > drebound1) {
		joes.roster[1].deereb = true;
		setDRebound(joes);
		count++;
	}
	else if (x <= drebound3 && x > drebound2) {
		joes.roster[2].deereb = true;
		setDRebound(joes);
		count++;
	}
	else if (x <= drebound4 && x > drebound3) {
		joes.roster[3].deereb = true;
		setDRebound(joes);
		count++;
	}
	else if (x <= drebound5 && x > drebound4) {
		joes.roster[4].deereb = true;
		setDRebound(joes);
		count++;
	}
	else {
		chance(x);
		if (x < .5) {
			count++;
		}
		else {
			count += 2;
		}
	}
}
void detBlock(team& pros) {
	for (int i = 0; i < 4; i++) {
		if (pros.roster[i].blkchance == true) {
			double blockChance, x;
			blockChance = pros.roster[i].blks / 100;
			chance(x);
			if (x <= blockChance) {
				pros.roster[i].blok = true;
				setBlocks(pros);
			}
			pros.roster[i].blkchance = false;
		}
	}

}
void detAfterPass(team& pros, team& joes, bool& turnov) {
	for (int i = 0; i < 4; i++) {
		if (pros.roster[i].justpassed == true) {
			double turnover = (pros.roster[i].tov / 100);
			double steal = (joes.roster[i].stls / 100);
			double x;
			chance(x);
			if (x <= turnover) {
				chance(x);
				if (x <= steal) {
					joes.roster[i].stel = true;
					setSteals(joes);
				}
				pros.roster[i].turov = true;
				setTurnovers(pros);
				turnov = true;
			}
		}
	}
}
void detAssist(team& pros) {
	for (int i = 0; i < 4; i++) {
		if (pros.roster[i].justpassed == true) {
			double x, assistChance;
			chance(x);
			assistChance = pros.roster[i].asts / 100;
			if (x < assistChance) {
				pros.roster[i].assis = true;
				setAssists(pros);
				pros.roster[i].assis = false;
			}
		}
	}
}
void detShotClock(team& pros, bool& turnov, double& secGame, double& shotClock) {
	srand((unsigned)time(NULL));
	float num = (float)rand() / RAND_MAX;
	int x;
	randomize(x);
	num = num + x;
	shotClock = shotClock + static_cast<double>(num);
	if (shotClock >= 24.00) {
		turnov = true;
		secGame += 24.00;
		for (int i = 0; i < 4; i++) {
			if (pros.roster[i].hasball == true) {
				pros.roster[i].turov = true;
			}
		}
		setTurnovers(pros);
	}
}
void setTimePlayed(team& pros, team& joes, double& secGame) {
	for (int i = 0; i < 4; i++) {
		pros.roster[i].secPlayed += secGame;
		joes.roster[i].secPlayed += secGame;
	}
}
void substitution(team& pros) {
	for (int i = 0; i < 4; i++) {
		double minMax = (pros.roster[i].min * 60) / pros.roster[i].gp;
		if (pros.roster[i].secPlayed > minMax || pros.roster[i].fouls == 6) {
			pros.roster[i].out = true;
			playerStats temp = pros.roster[i];
			if (pros.roster[5].out == false) {
				pros.roster[i] = pros.roster[5];
				pros.roster[5] = temp;
			}
			else if (pros.roster[6].out == false) {
				pros.roster[i] = pros.roster[6];
				pros.roster[6] = temp;
			}
			else if (pros.roster[7].out == false) {
				pros.roster[i] = pros.roster[7];
				pros.roster[7] = temp;
			}
			else if (pros.roster[8].out == false) {
				pros.roster[i] = pros.roster[8];
				pros.roster[8] = temp;
			}
			else if (pros.roster[9].out == false) {
				pros.roster[i] = pros.roster[9];
				pros.roster[9] = temp;
			}
			else if (pros.roster[10].out == false) {
				pros.roster[i] = pros.roster[10];
				pros.roster[10] = temp;
			}
			else if (pros.roster[11].out == false) {
				pros.roster[i] = pros.roster[11];
				pros.roster[11] = temp;
			}
		}
	}
}
void boxscore(team& pros, team& joes) {
	cout << "Team 1: " << pros.q1 << " " << pros.q2 << " " << pros.q3 << " " << pros.q4 << " " << pros.ot << endl;
	cout << "Team 2: " << joes.q1 << " " << joes.q2 << " " << joes.q3 << " " << joes.q4 << " " << joes.ot << endl;
}