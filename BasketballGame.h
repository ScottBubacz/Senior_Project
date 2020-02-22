#include <iostream>
#include <string>
#include <fstream>
#include <cmath>

using namespace std;

struct team{
	string name;
	int score, poss;
	playerStats roster[12];}

struct playerStats{
	string name;
	int gp, gs, min;
	double fg, fga, tfg, tfga, ft, fta, orb, drb, asts, stls, blks, tov, pfs;
	finalStats final;}

struct finalStats{
	int pts, fgm, fgat, tfgm, tfgat, ftm, ftat, oreb, dreb, assists, steals, blocks, tovs, fouls;}

class basketballGame{
	public:
	basletballGame();
	team team1;
	team team2;
	void setStats(team &pros, team &joes, inFile &indata, inFile &inSert);
	void game(team &pros, team &joes);
	void possession(team &pros);
	void setScore(team &pros);
	void setPoints(team &pros.player);
	void setFieldGoal(team &pros.player);
	void setThreePoint(team &pros.player);
	void setORebound(team &pros.player);
	void setDRebound(team &pros.player);
	void setAssists(team &pros.player);
	void setSteals(team &pros.player);
	void setBlocks(team &pros.player);
	void setTurnovers(team &pros.player);
	void setFouls(team &pros.player);
	void substitution(team &pros);

	private:
	int shotClock;
	int team1onCourt[5];
	int team2onCourt[5];
}