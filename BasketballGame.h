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
	finalStats final;
	bool out;}

struct finalStats{
	double secPlayed;
	int pts, fgm, fgat, tfgm, tfgat, ftm, ftat, oreb, dreb, assists, steals, blocks, tovs, fouls;}

class basketballGame{
	public:
	basletballGame();
	void setStats(team &pros, team &joes, inFile &indata, inFile &inSert);
	void randomize(int& num);
	void chance(double& num);
	void game(team& pros, team& joes);
	void possession(team& pros, team& joes);
	void quarter1(team &pros, team &joes);
	void quarter2(team& pros, team& joes);
	void quarter3(team& pros, team& joes);
	void quarter4(team& pros, team& joes);
	void overtime(team& pros, team& joes);
	void setFieldGoal(team &pros.player, bool shot);
	void setThreePoint(team &pros.player, bool shot);
	void setFreeThrow(team &pros.player, bool shot);
	void setORebound(team &pros.player);
	void setDRebound(team &pros.player);
	void setAssists(team &pros.player);
	void setSteals(team &pros.player);
	void setBlocks(team &pros.player);
	void setTurnovers(team &pros.player);
	void setFouls(team &pros.player);
	void detFreeThrow(team& pros.player, team& joes.player, double num, int attempts);
	void substitution(team &pros.player);

	private:
	int shotClock, count; 
	int q1t1, q1t2, q2t1.q2t2, q3t1, q3t2, q4t1, q4t2;
	double secGame;
	bool make;
}