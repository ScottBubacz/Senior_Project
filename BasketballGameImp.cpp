#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include "basketballGame.h"

using namespace std;

void basketballGame::void setStats(team &pros, team &joes, inFile &indata, inFile &inSert){
	for(int i = 0; i < 15; i++;){
		indata >> pros.roster[i].name >> pros.roster[i].gp >> pros.roster[i].gd >> pros.roster[i].min >> pros.roster[i].fg >>
		pros.roster[i].fga >> pros.roster[i].tfg >> pros.roster[i].tfga >> pros.roster[i].ft >> pros.roster[i].fta >> pros.roster[i].orb >>
		pros.roster[i].drb >> pros.roster[i].asts >> pros.roster[i].stls >> pros.roster[i].blks >> pros.roster[i].tov >> pros.roster[i].pfs;
	}
	for(int i = 0; i < 15; i++;){
		inSert >> joes.roster[i].name >> joes.roster[i].gp >> joes.roster[i].gd >> joes.roster[i].min >> joes.roster[i].fg >>
		joes.roster[i].fga >> joes.roster[i].tfg >> joes.roster[i].tfga >> joes.roster[i].ft >> joes.roster[i].fta >> joes.roster[i].orb >>
		joes.roster[i].drb >> joes.roster[i].asts >> joes.roster[i].stls >> joes.roster[i].blks >> joes.roster[i].tov >> joes.roster[i].pfs;
	}
}
basketballGame::basketballGame(){
	shotClock = 24;
	make = false;
}
void basketballGame::setScore(team &pros, int x){
	pros.score += x;
}
void basketballGame::setPoints(team &pros.player, int x){
	pros.player.final.pts += x;
}
void basketballGame::setFieldGoal(team &pros.player, bool shot){
	pros.player.final.fgat += 1;
	if(shot == true){
		pros.player.final.fgm += 1;}
}
void basketballGame::setThreePoint(team &pros.player, bool shot){
	pros.player.final.tfgat += 1;
	if(shot == true){
		pros.player.final.tfgm += 1;}
}
void basketballGame::setFreeThrow(team &pros.player, bool shot){
	pros.player.final.ftat += 1;
	if(shot == true){
		pros.player.final.ftm += 1;}
}
void basketballGame::setORebound(team &pros.player){
	pros.player.final.oreb += 1;
}
void basketballGame::setDRebound(team &pros.player){
	pros.player.final.dreb += 1;
}
void basketballGame::setAssists(team &pros.player){
	pros.player.final.assists += 1;
}
void basketballGame::setSteals(team &pros.player){
	pros.player.final.steals += 1;
}
void basketballGame::setBlocks(team &pros.player){
	pros.player.final.blocks += 1;
}
void basketballGame::setTurnovers(team &pros.player){
	pros.player.final.turnovers += 1;
}
void basketballGame::setFouls(team &pros.player){
	pros.player.final.fouls += 1;
	if(pros.player.final.fouls == 6){
		pros.player.out = true;
		substitution(pros.player);
	}
}