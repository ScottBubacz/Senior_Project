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
	secGame = 2880
	make = false;
}
void basketballGame::game(team& pros, team& joes) {
	quarter1(pros, joes);
	quarter2(pros, joes);
	quarter3(pros, joes);
	quarter4(pros, joes);
	if (pros.score == joes.score) {
		overtime(pros, joes);
	}
}
void basketballGame::randomize(int& num) {
	num = (rand() % 10) / 2;
	if (num == 5) {
		randomize(num);
	}
}
void basketballGame::chance(double& num) {
	num = (rand()/RAND_MAX);
}
void basketballGame::possession(team& pros, team& joes) {
	int x;
	double choice;
	if (count % 2 == 0) {
		randomize(x);
		chance(choice);
		if (choice <= (pros.roster[x].fga/100)) {
			chance(choice);
			double shotPick = (pros.roster[x].tfga / pros.roster[x].fga);
			if (choice <= shotPick) {
				chance(choice);
				double shotMake = (pros.roster[x].tfg / pros.roster[x].tfga);
				if (choice <= shotMake) {
					make = true;
					setThreePoint(pros.roster[x], make);
					pros.poss++;
					pros.score += 3;
					//secGame + whatever
					detFreeThrow(pros.roster[x], joes.roster[x], choice, 1, make);
					if (make == false) {
					/*Write Rebound Section
					count++; if OREB, count does not get ++, but possession is run again
					possession(pros, joes);*/
					}
				}
				else
				{
					make = false;
					setThreePoint(pros.roster[x], make);
					pros.poss++;
					detFreeThrow(pros.roster[x], joes.roster[x], choice, 3, make);
					if (make == true) {
						//secGame + whatever
					}
					else {
						/*Write Rebound Section
						count++; if OREB, count does not get ++, but possession is run again
						possession(pros, joes);*/
					}
				}
			}
			else {
				chance(choice);
				double shotMake = ((pros.roster[x].fg - pros.roster[x].tfg) / (pros.roster[x].fga - pros.roster[x].tfga));
				if (choice <= shotMake) {
					make = true;
					setFieldGoal(pros.roster[x], make);
					pros.score += 2;
					pros.poss++;
					//secGame + whatever
					detFreeThrow(pros.roster[x], joes.roster[x], choice, 1, make);
					if (make == false) {
						/*Write Rebound Section
						count++; if OREB, count does not get ++, but possession is run again
						possession(pros, joes);*/
					}

				}
				else {
					make = false;
					setFieldGoal(pros.roster[x], make);
					pros.poss++;
					detFreeThrow(pros.roster[x], joes.roster[x], choice, 1, make);
					if (make == true) {
						//secGame + whatever
					}
					else {
						/*Write Rebound Section
						count++; if OREB, count does not get ++, but possession is run again
						possession(pros, joes);*/
					}
				}
			}
		}
		else {

		}
	}
	else {
		randomize(x);
		chance(choice);
		if (choice <= (joes.roster[x].fga / 100)) {
			chance(choice);
			double shotPick = (joes.roster[x].tfga / joes.roster[x].fga);
			if (choice <= shotPick) {
				chance(choice);
				double shotMake = (joes.roster[x].tfg / joes.roster[x].tfga);
				if (choice <= shotMake) {
					make = true;
					setThreePoint(joes.roster[x], make);
					joes.poss++;
					joes.score += 3;
					//secGame + whatever
					detFreeThrow(joes.roster[x], pros.roster[x], choice, 1, make);
					if (make == false) {
						/*Write Rebound Section
						count++; if OREB, count does not get ++, but possession is run again
						possession(pros, joes);*/
					}
				}
				else
				{
					make = false;
					setThreePoint(joes.roster[x], make);
					joes.poss++;
					detFreeThrow(joes.roster[x], pros.roster[x], choice, 3, make);
					if (make == true) {
						//secGame + whatever
					}
					else {
						/*Write Rebound Section
						count++; if OREB, count does not get ++, but possession is run again
						possession(pros, joes);*/
					}
				}
			}
			else {
				chance(choice);
				double shotMake = ((joes.roster[x].fg - joes.roster[x].tfg) / (joes.roster[x].fga - joes.roster[x].tfga));
				if (choice <= shotMake) {
					make = true;
					setFieldGoal(joes.roster[x], make);
					joes.score += 2;
					joes.poss++;
					//secGame + whatever
					detFreeThrow(joes.roster[x], pros.roster[x], choice, 1, make);
					if (make == false) {
						/*Write Rebound Section
						count++; if OREB, count does not get ++, but possession is run again
						possession(pros, joes);*/
					}

				}
				else {
					make = false;
					setFieldGoal(joes.roster[x], make);
					joes.poss++;
					detFreeThrow(joes.roster[x], pros.roster[x], choice, 1, make);
					if (make == true) {
						//secGame + whatever
					}
					else {
						/*Write Rebound Section
						count++; if OREB, count does not get ++, but possession is run again
						possession(pros, joes);*/
					}
				}
			}
		}
		else {

		}
	}
}
void basketballGame::quarter1(team& pros, team& joes) {
	count = 0;
	while (secGame <= 720.00) {
		possession(pros, joes);
	}
	q1t1 = pros.score;
	q1t2 = joes.score;
}
void basketballGame::quarter2(team& pros, team& joes) {
	count = 1;
	while (secGame >= 720.00 && secGame <= 1440.00) {
		possession(pros, joes);
	}
	q2t1 = pros.score - q1t1;
	q2t2 = joes.score - q1t2;
}
void basketballGame::quarter3(team& pros, team& joes) {
	count = 0;
	while (secGame >= 1440.00 && secGame <= 2160.00) {
		possession(pros, joes);
	}
	q3t1 = pros.score - (q1t1 + q2t1);
	q3t2 = joes.score - (q1t2 + q2t2);
}
void basketballGame::quarter4(team& pros, team& joes) {
	count = 1;
	while (secGame >= 2160.00 && secGame <= 2880.00) {
		possession(pros, joes);
	}
	q4t1 = pros.score - (q1t1 + q2t1 + q3t1);
	q4t2 = joes.score - (q1t2 + q2t2 + q3t2);
}
void basketballGame::overtime(team& pros, team& joes) {
	while (secGame >= 2880.00 && secGame <= 3180.00) {
		possession(pros, joes);
	}
	if (pros.score == joes.score) {
		while (secGame >= 3180.00 && secGame <= 3480.00) {
			possession(pros, joes);
		}
		if (pros.score == joes.score) {
			while (secGame >= 3480.00 && secGame <= 3780.00) {
				possession(pros, joes);
			}
		}
	}
}
void basketballGame::setFieldGoal(team &pros.player, bool shot){
	pros.player.final.fgat += 1;
	if (shot == true) {
		pros.player.final.fgm += 1;
		pros.player.final.pts += 2;
	}
}
void basketballGame::setThreePoint(team &pros.player, bool shot){
	pros.player.final.tfgat += 1;
	pros.player.final.fgat += 1;
	if(shot == true){
		pros.player.final.tfgm += 1;
		pros.player.final.fgm += 1;
		pros.player.final.pts += 3;
	}
}
void basketballGame::setFreeThrow(team &pros.player, bool shot){
	pros.player.final.ftat += 1;
	if (shot == true) {
		pros.player.final.ftm += 1;
		pros.player.final.pts += 1;
	}
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
void basketballGame::detFreeThrow(team& pros.player, team& joes.player, double num, int attempts, bool shot) {
	chance(num);
	if (num <= (joes.roster[x].pfs)) {
		joes.roster[x].final.fouls++;
		double freeThrow = (pros.roster[x].ft / pros.roster[x].fta);
		while (attempts > 1) {
			chance(num);
			if (num <= freeThrow) {
				make = true;
				setFreeThrow(pros.roster[x], make);
				pros.score++;
				count++;
			}
			else {
				make = false;
				setFreeThrow(pros.roster[x], make)
			}
			attempts--;
		};
		chance(num);
		if (num <= freeThrow) {
			shot = true;
			pros.score++;
			setFreeThrow(pros.roster[x], make);
			count++;
		}
		else {
			shot = false;
			setFreeThrow(pros.roster[x], make);
		}
	}
}