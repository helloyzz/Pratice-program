#include "acllib.h"
#include "image.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

ACL_Image* mainTank;
ACL_Image* comTank;
ACL_Image* tankInit;

ACL_Image* mapEle;

ACL_Image* tankBullet;
ACL_Image* bulletBomb;

ACL_Image* gameInterface;
ACL_Image* gameUpdate;

mapCoorCon** mcc;
mapCoorCon* gameOver;
tankCoorCon* mainTkCoorCon;
tankCoorCon* comTkCoorCon;
bulletCoorCon* bullet;

int mainTankLife = 6;	//main tank living life
int comTankCount = 0;	//tank total count
int comTankInitX = 0;	//computer tank initial x
int comTankInitY = 12;	//computer tank initial y
int comTimer = 0;		//computer tank timer

//load image
void loadPicture() {
	//load main tank
	mainTank = (ACL_Image*)calloc(4, sizeof(ACL_Image));
	loadImage(MAIN_TANK_1_U, mainTank);
	loadImage(MAIN_TANK_1_D, mainTank+1);
	loadImage(MAIN_TANK_1_L, mainTank+2);
	loadImage(MAIN_TANK_1_R, mainTank+3);
	//load computer tank
	comTank = (ACL_Image*)calloc(4, sizeof(ACL_Image));
	loadImage(COM_TANK_GREY_1_U, comTank);
	loadImage(COM_TANK_GREY_1_D, comTank+1);
	loadImage(COM_TANK_GREY_1_L, comTank+2);
	loadImage(COM_TANK_GREY_1_R, comTank+3);
	//load tank initialize
	tankInit = (ACL_Image*)calloc(4, sizeof(ACL_Image));
	loadImage(TANK_INIT_1, tankInit);
	loadImage(TANK_INIT_2, tankInit+1);
	loadImage(TANK_INIT_3, tankInit+2);
	loadImage(TANK_INIT_4, tankInit+3);
	//load map
	mapEle = (ACL_Image*)calloc(5, sizeof(ACL_Image));
	loadImage(MAP_BRICK, mapEle);
	loadImage(MAP_STEEL, mapEle+1);
	loadImage(MAP_HOME, mapEle+2);
	loadImage(MAP_GRASS, mapEle+3);
	loadImage(MAP_WATER, mapEle+4);
	//load tank bullet
	tankBullet = (ACL_Image*)calloc(4, sizeof(ACL_Image));
	loadImage(TANK_BULLET_U, tankBullet);
	loadImage(TANK_BULLET_D, tankBullet+1);
	loadImage(TANK_BULLET_L, tankBullet+2);
	loadImage(TANK_BULLET_R, tankBullet+3);
	//tank bomb
	bulletBomb = (ACL_Image*)calloc(1, sizeof(ACL_Image));
	loadImage(TANK_BOMB, bulletBomb);
	//load game interface
	gameInterface = (ACL_Image*)calloc(6, sizeof(ACL_Image));
	loadImage(LEFT_ARROW, gameInterface);
	loadImage(RIGHT_ARROW, gameInterface+1);
	loadImage(GAME_START, gameInterface+2);
	loadImage(BANNER, gameInterface+3);
	loadImage(ENEMY_TANK_COUNT, gameInterface+4);
	loadImage(GAME_OVER, gameInterface+5);
	//load game update
	gameUpdate = (ACL_Image*)calloc(6, sizeof(ACL_Image));
	loadImage(ADD_LIFE, gameUpdate);
	loadImage(PAUSE, gameUpdate+1);
	loadImage(UPGRADE, gameUpdate+2);
	loadImage(CONSTRUCTOR, gameUpdate+3);
	loadImage(DESTROY_ENEMY, gameUpdate+4);
	loadImage(UNBEATABLE, gameUpdate+5);
}
//initialize data
void initMap() {
	int i;
	int j;
	int flag = 0;
	//init brick
	for(i=2; i<23; i++) {
		if(i==10 || i==11 || i==12 || i==13 || i==14) continue;
		for(j=2; j<24; j++) {
			flag = 0;
			if(j==12 || j==13) flag = 1;
			if(flag && (i!=8 && i!=9 && i!=15 && i!=16 && i!=20 && i!=21)) continue;
			if(j==4 || j==5 || j==8 || j==9 || j==16 || j==17 || j==20 || j==21) continue;
			mcc[i][j].x = i;
			mcc[i][j].y = j;
			mcc[i][j].left = j*DRAW_MAP_SIZE;
			mcc[i][j].top = i*DRAW_MAP_SIZE;
			mcc[i][j].width = DRAW_MAP_SIZE;
			mcc[i][j].height = DRAW_MAP_SIZE;
			mcc[i][j].type = BRICK;
			mcc[i][j].pimage = mapEle;
			mcc[i][j].display = 1;
		}
	}
	//init steel
	for(i=4; i<=5; i++) {
		for(j=12; j<=13; j++) {
			mcc[i][j].x = i;
			mcc[i][j].y = j;
			mcc[i][j].left = j*DRAW_MAP_SIZE;
			mcc[i][j].top = i*DRAW_MAP_SIZE;
			mcc[i][j].width = DRAW_MAP_SIZE;
			mcc[i][j].height = DRAW_MAP_SIZE;
			mcc[i][j].type = STEEL;
			mcc[i][j].pimage = mapEle+1;
			mcc[i][j].display = 1;
		}
	}
	for(i=12; i<=12; i++) {
		for(j=0; j<COORDINATE_LIST; j++) {
			mcc[i][j].x = i;
			mcc[i][j].y = j;
			mcc[i][j].left = j*DRAW_MAP_SIZE;
			mcc[i][j].top = i*DRAW_MAP_SIZE;
			mcc[i][j].width = DRAW_MAP_SIZE;
			mcc[i][j].height = DRAW_MAP_SIZE;
			mcc[i][j].type = STEEL;
			mcc[i][j].pimage = mapEle+1;
			mcc[i][j].display = 1;
			if(j==1) j = 23;
		}
	}
	//init home
	for(i=24; i<COORDINATE_ROW; i++) {
		for(j=10; j<16; j++) {
			if((i==26 || i==27) && (j==12 || j==13)) {
				mcc[i][j].type = HOME;
				if(i==26 && j==12) {
					mcc[i][j].x = i;
					mcc[i][j].y = j;
					mcc[i][j].left = j*DRAW_MAP_SIZE;
					mcc[i][j].top = i*DRAW_MAP_SIZE;
					mcc[i][j].width = DRAW_OTHER_SIZE;
					mcc[i][j].height = DRAW_OTHER_SIZE;
					mcc[i][j].pimage = mapEle+2;
					mcc[i][j].display = 1;
				}
			} else {
				mcc[i][j].type = BRICK;
				mcc[i][j].x = i;
				mcc[i][j].y = j;
				mcc[i][j].left = j*DRAW_MAP_SIZE;
				mcc[i][j].top = i*DRAW_MAP_SIZE;
				mcc[i][j].width = DRAW_MAP_SIZE;
				mcc[i][j].height = DRAW_MAP_SIZE;
				mcc[i][j].type = BRICK;
				mcc[i][j].pimage = mapEle;
				mcc[i][j].display = 1;
			}
		}
	}
}
//initialize window and data
void beginInit() {
	int i;
	initWindow("TKFight", WINDOW_TO_SCREEN_LEFT, WINDOW_TO_SCREEN_TOP, SCREEN_WIDTH, SCREEN_HEIGHT);
	loadPicture();
	//init coordinate use condition
	mcc = (mapCoorCon**)calloc(COORDINATE_ROW, sizeof(int*));
	for(i=0; i<COORDINATE_ROW_SIZE; i++) {
		mcc[i] = (mapCoorCon*)calloc(COORDINATE_LIST_SIZE, sizeof(mapCoorCon));
	}
	mainTkCoorCon = (tankCoorCon*)calloc(1, sizeof(tankCoorCon));
	comTkCoorCon = (tankCoorCon*)calloc(SCREEN_COM_TANK_MAX, sizeof(tankCoorCon));
	bullet = (bulletCoorCon*)calloc(SCREEN_BULLET_MAX, sizeof(bulletCoorCon));
	gameOver = (mapCoorCon*)calloc(1, sizeof(mapCoorCon));
	initMap();
}
void drawMap() {
	int i,j;
	beginPaint();
	setBrushColor(BLACK);
	rectangle(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
	for(i=2; i<COORDINATE_ROW; i++) {
		for(j=0; j<COORDINATE_LIST; j++) {
			if(mcc[i]!=NULL && mcc[i][j].display==1) {
				putImageTransparent(mcc[i][j].pimage, mcc[i][j].left, mcc[i][j].top, mcc[i][j].width, mcc[i][j].height, BLACK);
			}
		}
	}
	for(i=0; i<SCREEN_COM_TANK_MAX; i++) {
		if(comTkCoorCon!=NULL && comTkCoorCon[i].display==1) {
			putImageTransparent(comTkCoorCon[i].pimage, comTkCoorCon[i].left, comTkCoorCon[i].top, comTkCoorCon[i].width, comTkCoorCon[i].height, BLACK);
		}
	}
	if(mainTkCoorCon!=NULL && mainTkCoorCon->display==1) {
		putImageTransparent(mainTkCoorCon->pimage, mainTkCoorCon->left, mainTkCoorCon->top, mainTkCoorCon->width, mainTkCoorCon->height, BLACK);
	}
	for(i=0; i<SCREEN_BULLET_MAX; i++) {
		if(bullet!=NULL && bullet[i].display==1) {
			putImageTransparent(bullet[i].pimage, bullet[i].left, bullet[i].top, bullet[i].width, bullet[i].height, BLACK);
		}
	}
	if(gameOver->display==1) {
		putImageTransparent(gameOver->pimage, gameOver->left, gameOver->top, gameOver->width, gameOver->height, BLACK);
	}
	endPaint();
}
void updateData() {
	int i;
	if(mainTankLife!=0 && mcc[26][12].display==1) {
		//main tank update
		if(mainTkCoorCon->flickerTimes<4) {
			mainTkCoorCon->display = 1;
			mainTkCoorCon->x = MAIN_TANK_INIT_X;
			mainTkCoorCon->y = MAIN_TANK_INIT_Y;
			mainTkCoorCon->left = mainTkCoorCon->y*DRAW_MAP_SIZE+TANK_TO_LEFT_DISTANCE;
			mainTkCoorCon->top = mainTkCoorCon->x*DRAW_MAP_SIZE+TANK_TO_TOP_DISTANCE;
			mainTkCoorCon->width = TANK_WIDTH;
			mainTkCoorCon->height = TANK_HEIGHT;
			mainTkCoorCon->dir = UP;
			mainTkCoorCon->pimage = tankInit+mainTkCoorCon->flickerTimes;
			mainTkCoorCon->flickerTimes++;
		} else if(mainTkCoorCon->flickerTimes>=4 && mainTkCoorCon->move!=1) {
			mainTkCoorCon->pimage = mainTank;
			mainTkCoorCon->type = MAINTANK;
			mainTkCoorCon->move = 1;
			mcc[mainTkCoorCon->x][mainTkCoorCon->y].type = MAINTANK;
			mcc[mainTkCoorCon->x][mainTkCoorCon->y+1].type = MAINTANK;
			mcc[mainTkCoorCon->x+1][mainTkCoorCon->y].type = MAINTANK;
			mcc[mainTkCoorCon->x+1][mainTkCoorCon->y+1].type = MAINTANK;
		}
		//computer tank update
		for(i=0; i<=comTankCount; i++) {
			if(comTkCoorCon[i].flickerTimes<4 && comTimer==COM_TANK_INIT_INTERVAL) {
				comTkCoorCon[i].dir = DOWN;
				comTkCoorCon[i].display = 1;
				comTkCoorCon[i].x = comTankInitX;
				comTkCoorCon[i].y = comTankInitY;
				comTkCoorCon[i].left = comTkCoorCon[i].y*DRAW_MAP_SIZE+TANK_TO_LEFT_DISTANCE;
				comTkCoorCon[i].top = comTkCoorCon[i].x*DRAW_MAP_SIZE+TANK_TO_TOP_DISTANCE;
				comTkCoorCon[i].width = TANK_WIDTH;
				comTkCoorCon[i].height = TANK_HEIGHT;
				comTkCoorCon[i].pimage = tankInit+comTkCoorCon[i].flickerTimes;
				comTkCoorCon[i].flickerTimes++;
			} else if(comTkCoorCon[i].flickerTimes>=4 && comTkCoorCon[i].move!=1) {
				comTimer = 0;
				if(i==0) comTkCoorCon[i].type = COMTANK1;
				if(i==1) comTkCoorCon[i].type = COMTANK2;
				if(i==2) comTkCoorCon[i].type = COMTANK3;
				if(i==3) comTkCoorCon[i].type = COMTANK4;
				comTkCoorCon[i].pimage = comTank+1;
				comTkCoorCon[i].move = 1;
				mcc[comTkCoorCon[i].x][comTkCoorCon[i].y].type = comTkCoorCon[i].type;
				mcc[comTkCoorCon[i].x][comTkCoorCon[i].y+1].type = comTkCoorCon[i].type;
				mcc[comTkCoorCon[i].x+1][comTkCoorCon[i].y].type = comTkCoorCon[i].type;
				mcc[comTkCoorCon[i].x+1][comTkCoorCon[i].y+1].type = comTkCoorCon[i].type;
				if(comTankCount<(SCREEN_COM_TANK_MAX-1)) comTankCount++;
				if(comTankInitY==12) {
					comTankInitY = 0;
				} else if(comTankInitY==0) {
					comTankInitY = 24;
				} else if(comTankInitY==24) {
					comTankInitY = 12;
				}
			} else if(comTkCoorCon[i].flickerTimes>=4 && comTkCoorCon[i].move==1) {
				int turnWay = rand()%4;
				int cmove = 0;
				if(comTkCoorCon[i].dir==DOWN) {
					if((comTkCoorCon[i].top+TANK_HEIGHT+COM_TANK_SPEED)<=MAP_MOVE_DOWN_END && 
						(comTkCoorCon[i].top+TANK_HEIGHT+COM_TANK_SPEED)<=(comTkCoorCon[i].x+2)*DRAW_MAP_SIZE) {
							comTkCoorCon[i].top += COM_TANK_SPEED;
					} else if((comTkCoorCon[i].top+TANK_HEIGHT+COM_TANK_SPEED)<=MAP_MOVE_DOWN_END && 
						(comTkCoorCon[i].top+TANK_HEIGHT+COM_TANK_SPEED)>(comTkCoorCon[i].x+2)*DRAW_MAP_SIZE && 
						mcc[comTkCoorCon[i].x+2][comTkCoorCon[i].y].type==NONE && mcc[comTkCoorCon[i].x+2][comTkCoorCon[i].y+1].type==NONE) {
							mcc[comTkCoorCon[i].x][comTkCoorCon[i].y].type = NONE;
							mcc[comTkCoorCon[i].x][comTkCoorCon[i].y+1].type = NONE;
							mcc[comTkCoorCon[i].x+1][comTkCoorCon[i].y].type = NONE;
							mcc[comTkCoorCon[i].x+1][comTkCoorCon[i].y+1].type = NONE;
							comTkCoorCon[i].top += COM_TANK_SPEED;
							comTkCoorCon[i].x += 1;
							mcc[comTkCoorCon[i].x][comTkCoorCon[i].y].type = comTkCoorCon[i].type;
							mcc[comTkCoorCon[i].x][comTkCoorCon[i].y+1].type = comTkCoorCon[i].type;
							mcc[comTkCoorCon[i].x+1][comTkCoorCon[i].y].type = comTkCoorCon[i].type;
							mcc[comTkCoorCon[i].x+1][comTkCoorCon[i].y+1].type = comTkCoorCon[i].type;
					} else {
						cmove = 1;
					}
				} else if(comTkCoorCon[i].dir==RIGHT) {
					if((comTkCoorCon[i].left+TANK_WIDTH+COM_TANK_SPEED)<=MAP_MOVE_RIGHT_END && 
						(comTkCoorCon[i].left+TANK_WIDTH+COM_TANK_SPEED)<=(comTkCoorCon[i].y+2)*DRAW_MAP_SIZE) {
							comTkCoorCon[i].left += COM_TANK_SPEED;
					} else if((comTkCoorCon[i].left+TANK_WIDTH+COM_TANK_SPEED)<=MAP_MOVE_RIGHT_END && 
						(comTkCoorCon[i].left+TANK_WIDTH+COM_TANK_SPEED)>(comTkCoorCon[i].y+2)*DRAW_MAP_SIZE && 
						mcc[comTkCoorCon[i].x][comTkCoorCon[i].y+2].type==NONE && mcc[comTkCoorCon[i].x+1][comTkCoorCon[i].y+2].type==NONE) {
							mcc[comTkCoorCon[i].x][comTkCoorCon[i].y].type = NONE;
							mcc[comTkCoorCon[i].x][comTkCoorCon[i].y+1].type = NONE;
							mcc[comTkCoorCon[i].x+1][comTkCoorCon[i].y].type = NONE;
							mcc[comTkCoorCon[i].x+1][comTkCoorCon[i].y+1].type = NONE;
							comTkCoorCon[i].left += COM_TANK_SPEED;
							comTkCoorCon[i].y += 1;
							mcc[comTkCoorCon[i].x][comTkCoorCon[i].y].type = comTkCoorCon[i].type;
							mcc[comTkCoorCon[i].x+1][comTkCoorCon[i].y].type = comTkCoorCon[i].type;
							mcc[comTkCoorCon[i].x][comTkCoorCon[i].y+1].type = comTkCoorCon[i].type;
							mcc[comTkCoorCon[i].x+1][comTkCoorCon[i].y+1].type = comTkCoorCon[i].type;
					} else {
						cmove = 1;
					}
				} else if(comTkCoorCon[i].dir==UP) {
					if((comTkCoorCon[i].top-COM_TANK_SPEED)>=MAP_MOVE_UP_END && 
						(comTkCoorCon[i].top-COM_TANK_SPEED)>=comTkCoorCon[i].x*DRAW_MAP_SIZE) {
							comTkCoorCon[i].top -= COM_TANK_SPEED;
					} else if((comTkCoorCon[i].top-COM_TANK_SPEED)>=MAP_MOVE_UP_END && 
						(comTkCoorCon[i].top-COM_TANK_SPEED)<comTkCoorCon[i].x*DRAW_MAP_SIZE && 
						mcc[comTkCoorCon[i].x-1][comTkCoorCon[i].y].type==NONE && mcc[comTkCoorCon[i].x-1][comTkCoorCon[i].y+1].type==NONE) {
							mcc[comTkCoorCon[i].x][comTkCoorCon[i].y].type = NONE;
							mcc[comTkCoorCon[i].x][comTkCoorCon[i].y+1].type = NONE;
							mcc[comTkCoorCon[i].x+1][comTkCoorCon[i].y].type = NONE;
							mcc[comTkCoorCon[i].x+1][comTkCoorCon[i].y+1].type = NONE;
							comTkCoorCon[i].top -= COM_TANK_SPEED;
							comTkCoorCon[i].x -= 1;
							mcc[comTkCoorCon[i].x][comTkCoorCon[i].y].type = comTkCoorCon[i].type;
							mcc[comTkCoorCon[i].x][comTkCoorCon[i].y+1].type = comTkCoorCon[i].type;
							mcc[comTkCoorCon[i].x+1][comTkCoorCon[i].y].type = comTkCoorCon[i].type;
							mcc[comTkCoorCon[i].x+1][comTkCoorCon[i].y+1].type = comTkCoorCon[i].type;
					} else {
						cmove = 1;
					}
				} else if(comTkCoorCon[i].dir==LEFT) {
					if((comTkCoorCon[i].left-COM_TANK_SPEED)>=MAP_MOVE_LEFT_END && 
						(comTkCoorCon[i].left-COM_TANK_SPEED)>=comTkCoorCon[i].y*DRAW_MAP_SIZE) {
							comTkCoorCon[i].left -= COM_TANK_SPEED;
					} else if((comTkCoorCon[i].left-COM_TANK_SPEED)>=MAP_MOVE_UP_END && 
						(comTkCoorCon[i].left-COM_TANK_SPEED)<comTkCoorCon[i].y*DRAW_MAP_SIZE && 
						mcc[comTkCoorCon[i].x][comTkCoorCon[i].y-1].type==NONE && mcc[comTkCoorCon[i].x+1][comTkCoorCon[i].y-1].type==NONE) {
							mcc[comTkCoorCon[i].x][comTkCoorCon[i].y].type = NONE;
							mcc[comTkCoorCon[i].x][comTkCoorCon[i].y+1].type = NONE;
							mcc[comTkCoorCon[i].x+1][comTkCoorCon[i].y].type = NONE;
							mcc[comTkCoorCon[i].x+1][comTkCoorCon[i].y+1].type = NONE;
							comTkCoorCon[i].left -= COM_TANK_SPEED;
							comTkCoorCon[i].y -= 1;
							mcc[comTkCoorCon[i].x][comTkCoorCon[i].y].type = comTkCoorCon[i].type;
							mcc[comTkCoorCon[i].x][comTkCoorCon[i].y+1].type = comTkCoorCon[i].type;
							mcc[comTkCoorCon[i].x+1][comTkCoorCon[i].y].type = comTkCoorCon[i].type;
							mcc[comTkCoorCon[i].x+1][comTkCoorCon[i].y+1].type = comTkCoorCon[i].type;
					} else {
						cmove = 1;
					}
				}
				if(cmove && turnWay==0) {
					comTkCoorCon[i].dir = UP;
					comTkCoorCon[i].pimage = comTank;
				} else if(cmove && turnWay==1) {
					comTkCoorCon[i].dir = DOWN;
					comTkCoorCon[i].pimage = comTank+1;
				} else if(cmove && turnWay==2) {
					comTkCoorCon[i].dir = LEFT;
					comTkCoorCon[i].pimage = comTank+2;
				} else if(cmove && turnWay==3) {
					comTkCoorCon[i].dir = RIGHT;
					comTkCoorCon[i].pimage = comTank+3;
				}
				if(comTkCoorCon[i].moveDis<COM_TANK_MOVE_TIMES && bullet[i].update==0) {
					comTkCoorCon[i].moveDis++;
				} else if(comTkCoorCon[i].moveDis==COM_TANK_MOVE_TIMES && bullet[i].update==0) {
					comTkCoorCon[i].moveDis = 0;
					bullet[i].dir = comTkCoorCon[i].dir;
					bullet[i].update = 1;
					bullet[i].width = BULLET_WIDTH;
					bullet[i].height = BULLET_HEIGHT;
					if(bullet[i].dir==UP) {
						bullet[i].x = comTkCoorCon[i].x;
						bullet[i].y = comTkCoorCon[i].y;
						bullet[i].left = bullet[i].y*DRAW_MAP_SIZE+BULLET_WIDTH_DISTANCE;
						bullet[i].top = bullet[i].x*DRAW_MAP_SIZE+BULLET_HEIGHT_DISTANCE;
					} else if(bullet[i].dir==DOWN) {
						bullet[i].x = comTkCoorCon[i].x;
						bullet[i].y = comTkCoorCon[i].y;
						bullet[i].left = bullet[i].y*DRAW_MAP_SIZE+BULLET_WIDTH_DISTANCE;
						bullet[i].top = bullet[i].x*DRAW_MAP_SIZE+BULLET_HEIGHT_DISTANCE;
					} else if(bullet[i].dir==LEFT) {
						bullet[i].x = comTkCoorCon[i].x;
						bullet[i].y = comTkCoorCon[i].y;
						bullet[i].left = bullet[i].y*DRAW_MAP_SIZE+BULLET_HEIGHT_DISTANCE;
						bullet[i].top = bullet[i].x*DRAW_MAP_SIZE+BULLET_WIDTH_DISTANCE;
					} else if(bullet[i].dir==RIGHT) {
						bullet[i].x = comTkCoorCon[i].x;
						bullet[i].y = comTkCoorCon[i].y;
						bullet[i].left = bullet[i].y*DRAW_MAP_SIZE+BULLET_HEIGHT_DISTANCE;
						bullet[i].top = bullet[i].x*DRAW_MAP_SIZE+BULLET_WIDTH_DISTANCE;
					}
				}
			} else {
				comTimer++;
			}
		}
		//bullet update
		for(i=0; i<SCREEN_BULLET_MAX; i++) {
			if(bullet[i].explode==1) {
				bullet[i].explode = 0;
				bullet[i].display = 0;
				bullet[i].update = 0;
			}
			//BULLET_SPEED MAIN_BULLET_POS BULLET_TO_LEFT_DISTANCE BULLET_TO_TOP_DISTANCE
			if(bullet[i].update==1) {
				bullet[i].display = 1;
				if(bullet[i].dir==UP) {
					if(bullet[i].top<=MAP_MOVE_UP_END) {
						bullet[i].pimage = bulletBomb;
						bullet[i].width = COMMON_BOMB_WIDTH;
						bullet[i].height = COMMON_BOMB_HEIGHT;
						bullet[i].explode = 1;
					} else if(bullet[i].top>MAP_MOVE_UP_END &&  
						(mcc[bullet[i].x][bullet[i].y].type==BRICK || mcc[bullet[i].x][bullet[i].y+1].type==BRICK) || 
						(mcc[bullet[i].x][bullet[i].y].type==STEEL || mcc[bullet[i].x][bullet[i].y+1].type==STEEL)) {
							if(mcc[bullet[i].x][bullet[i].y].type==BRICK) {
								mcc[bullet[i].x][bullet[i].y].display = 0;
								mcc[bullet[i].x][bullet[i].y].type = NONE;
							}
							if(mcc[bullet[i].x][bullet[i].y+1].type==BRICK) {
								mcc[bullet[i].x][bullet[i].y+1].display = 0;
								mcc[bullet[i].x][bullet[i].y+1].type = NONE;
							}
							bullet[i].pimage = bulletBomb;
							bullet[i].width = COMMON_BOMB_WIDTH;
							bullet[i].height = COMMON_BOMB_HEIGHT;
							bullet[i].explode = 1;
					} else if(bullet[i].top>MAP_MOVE_UP_END && i<MAIN_BULLET_POS && 
						(mcc[bullet[i].x][bullet[i].y].type==MAINTANK || mcc[bullet[i].x][bullet[i].y+1].type==MAINTANK)) {
							mcc[mainTkCoorCon->x][mainTkCoorCon->y].type = NONE;
							mcc[mainTkCoorCon->x][mainTkCoorCon->y+1].type = NONE;
							mcc[mainTkCoorCon->x+1][mainTkCoorCon->y].type = NONE;
							mcc[mainTkCoorCon->x+1][mainTkCoorCon->y+1].type = NONE;
							mainTankLife--;
							mainTkCoorCon->flickerTimes = 0;
							mainTkCoorCon->display = 0;
							mainTkCoorCon->move = 0;
							bullet[i].pimage = bulletBomb;
							bullet[i].width = TANK_BOMB_WIDTH;
							bullet[i].height = TANK_BOMB_HEIGHT;
							bullet[i].explode = 1;
					} else if(bullet[i].top>MAP_MOVE_UP_END && i==MAIN_BULLET_POS && 
						(mcc[bullet[i].x][bullet[i].y].type==COMTANK1 || mcc[bullet[i].x][bullet[i].y+1].type==COMTANK1 || 
						mcc[bullet[i].x][bullet[i].y].type==COMTANK2 || mcc[bullet[i].x][bullet[i].y+1].type==COMTANK2 || 
						mcc[bullet[i].x][bullet[i].y].type==COMTANK3 || mcc[bullet[i].x][bullet[i].y+1].type==COMTANK3 || 
						mcc[bullet[i].x][bullet[i].y].type==COMTANK4 || mcc[bullet[i].x][bullet[i].y+1].type==COMTANK4)) {
							if(mcc[bullet[i].x][bullet[i].y].type!=NONE) {
								comTkCoorCon[mcc[bullet[i].x][bullet[i].y].type-RESTORE_COM_TANK_POSITION].flickerTimes = 0;
								comTkCoorCon[mcc[bullet[i].x][bullet[i].y].type-RESTORE_COM_TANK_POSITION].display = 0;
								comTkCoorCon[mcc[bullet[i].x][bullet[i].y].type-RESTORE_COM_TANK_POSITION].move = 0;
								mcc[comTkCoorCon[mcc[bullet[i].x][bullet[i].y].type-RESTORE_COM_TANK_POSITION].x][comTkCoorCon[mcc[bullet[i].x][bullet[i].y].type-RESTORE_COM_TANK_POSITION].y].type = NONE;
								mcc[comTkCoorCon[mcc[bullet[i].x][bullet[i].y].type-RESTORE_COM_TANK_POSITION].x][comTkCoorCon[mcc[bullet[i].x][bullet[i].y].type-RESTORE_COM_TANK_POSITION].y+1].type = NONE;
								mcc[comTkCoorCon[mcc[bullet[i].x][bullet[i].y].type-RESTORE_COM_TANK_POSITION].x+1][comTkCoorCon[mcc[bullet[i].x][bullet[i].y].type-RESTORE_COM_TANK_POSITION].y].type = NONE;
								mcc[comTkCoorCon[mcc[bullet[i].x][bullet[i].y].type-RESTORE_COM_TANK_POSITION].x+1][comTkCoorCon[mcc[bullet[i].x][bullet[i].y].type-RESTORE_COM_TANK_POSITION].y+1].type = NONE;
							} else if(mcc[bullet[i].x][bullet[i].y+1].type!=NONE) {
								comTkCoorCon[mcc[bullet[i].x][bullet[i].y+1].type-RESTORE_COM_TANK_POSITION].flickerTimes = 0;
								comTkCoorCon[mcc[bullet[i].x][bullet[i].y+1].type-RESTORE_COM_TANK_POSITION].display = 0;
								comTkCoorCon[mcc[bullet[i].x][bullet[i].y+1].type-RESTORE_COM_TANK_POSITION].move = 0;
								mcc[comTkCoorCon[mcc[bullet[i].x][bullet[i].y+1].type-RESTORE_COM_TANK_POSITION].x][comTkCoorCon[mcc[bullet[i].x][bullet[i].y+1].type-RESTORE_COM_TANK_POSITION].y].type = NONE;
								mcc[comTkCoorCon[mcc[bullet[i].x][bullet[i].y+1].type-RESTORE_COM_TANK_POSITION].x][comTkCoorCon[mcc[bullet[i].x][bullet[i].y+1].type-RESTORE_COM_TANK_POSITION].y+1].type = NONE;
								mcc[comTkCoorCon[mcc[bullet[i].x][bullet[i].y+1].type-RESTORE_COM_TANK_POSITION].x+1][comTkCoorCon[mcc[bullet[i].x][bullet[i].y+1].type-RESTORE_COM_TANK_POSITION].y].type = NONE;
								mcc[comTkCoorCon[mcc[bullet[i].x][bullet[i].y+1].type-RESTORE_COM_TANK_POSITION].x+1][comTkCoorCon[mcc[bullet[i].x][bullet[i].y+1].type-RESTORE_COM_TANK_POSITION].y+1].type = NONE;
							}
							mcc[bullet[i].x][bullet[i].y].type = NONE;
							mcc[bullet[i].x][bullet[i].y+1].type = NONE;
							bullet[i].pimage = bulletBomb;
							bullet[i].width = TANK_BOMB_WIDTH;
							bullet[i].height = TANK_BOMB_HEIGHT;
							bullet[i].explode = 1;
					} else if(bullet[i].top>MAP_MOVE_UP_END && 
						(bullet[i].top-BULLET_SPEED)>=bullet[i].x*DRAW_MAP_SIZE) {
							bullet[i].top -= BULLET_SPEED;
							bullet[i].pimage = tankBullet;
					} else if(bullet[i].top>MAP_MOVE_UP_END && 
						(bullet[i].top-BULLET_SPEED)<bullet[i].x*DRAW_MAP_SIZE) {
							bullet[i].top -= BULLET_SPEED;
							bullet[i].x -= 1;
							bullet[i].pimage = tankBullet;
					}
					/*------------------------------*/
				} else if(bullet[i].dir==DOWN) {
					if(bullet[i].top>=MAP_MOVE_DOWN_END) {
						bullet[i].pimage = bulletBomb;
						bullet[i].width = COMMON_BOMB_WIDTH;
						bullet[i].height = COMMON_BOMB_HEIGHT;
						bullet[i].explode = 1;
					} else if(bullet[i].top<MAP_MOVE_DOWN_END && 
						(mcc[bullet[i].x][bullet[i].y].type==BRICK || mcc[bullet[i].x][bullet[i].y+1].type==BRICK) || 
						(mcc[bullet[i].x][bullet[i].y].type==STEEL || mcc[bullet[i].x][bullet[i].y+1].type==STEEL)) {
							if(mcc[bullet[i].x][bullet[i].y].type==BRICK) {
								mcc[bullet[i].x][bullet[i].y].display = 0;
								mcc[bullet[i].x][bullet[i].y].type = NONE;
							}
							if(mcc[bullet[i].x][bullet[i].y+1].type==BRICK) {
								mcc[bullet[i].x][bullet[i].y+1].display = 0;
								mcc[bullet[i].x][bullet[i].y+1].type = NONE;
							}
							bullet[i].pimage = bulletBomb;
							bullet[i].width = COMMON_BOMB_WIDTH;
							bullet[i].height = COMMON_BOMB_HEIGHT;
							bullet[i].explode = 1;
					} else if(bullet[i].top<MAP_MOVE_DOWN_END && i<MAIN_BULLET_POS && 
						(mcc[bullet[i].x][bullet[i].y].type==MAINTANK || mcc[bullet[i].x][bullet[i].y+1].type==MAINTANK)) {
							mcc[mainTkCoorCon->x][mainTkCoorCon->y].type = NONE;
							mcc[mainTkCoorCon->x][mainTkCoorCon->y+1].type = NONE;
							mcc[mainTkCoorCon->x+1][mainTkCoorCon->y].type = NONE;
							mcc[mainTkCoorCon->x+1][mainTkCoorCon->y+1].type = NONE;
							mainTankLife--;
							mainTkCoorCon->flickerTimes = 0;
							mainTkCoorCon->display = 0;
							mainTkCoorCon->move = 0;
							bullet[i].pimage = bulletBomb;
							bullet[i].width = TANK_BOMB_WIDTH;
							bullet[i].height = TANK_BOMB_HEIGHT;
							bullet[i].explode = 1;
					} else if(bullet[i].top<MAP_MOVE_DOWN_END && i==MAIN_BULLET_POS && 
						((mcc[bullet[i].x][bullet[i].y].type==COMTANK1 || mcc[bullet[i].x][bullet[i].y+1].type==COMTANK1) || 
						(mcc[bullet[i].x][bullet[i].y].type==COMTANK2 || mcc[bullet[i].x][bullet[i].y+1].type==COMTANK2) || 
						(mcc[bullet[i].x][bullet[i].y].type==COMTANK3 || mcc[bullet[i].x][bullet[i].y+1].type==COMTANK3) || 
						(mcc[bullet[i].x][bullet[i].y].type==COMTANK4 || mcc[bullet[i].x][bullet[i].y+1].type==COMTANK4))) {
							if(mcc[bullet[i].x][bullet[i].y].type!=NONE) {
								comTkCoorCon[mcc[bullet[i].x][bullet[i].y].type-RESTORE_COM_TANK_POSITION].flickerTimes = 0;
								comTkCoorCon[mcc[bullet[i].x][bullet[i].y].type-RESTORE_COM_TANK_POSITION].display = 0;
								comTkCoorCon[mcc[bullet[i].x][bullet[i].y].type-RESTORE_COM_TANK_POSITION].move = 0;
								mcc[comTkCoorCon[mcc[bullet[i].x][bullet[i].y].type-RESTORE_COM_TANK_POSITION].x][comTkCoorCon[mcc[bullet[i].x][bullet[i].y].type-RESTORE_COM_TANK_POSITION].y].type = NONE;
								mcc[comTkCoorCon[mcc[bullet[i].x][bullet[i].y].type-RESTORE_COM_TANK_POSITION].x][comTkCoorCon[mcc[bullet[i].x][bullet[i].y].type-RESTORE_COM_TANK_POSITION].y+1].type = NONE;
								mcc[comTkCoorCon[mcc[bullet[i].x][bullet[i].y].type-RESTORE_COM_TANK_POSITION].x+1][comTkCoorCon[mcc[bullet[i].x][bullet[i].y].type-RESTORE_COM_TANK_POSITION].y].type = NONE;
								mcc[comTkCoorCon[mcc[bullet[i].x][bullet[i].y].type-RESTORE_COM_TANK_POSITION].x+1][comTkCoorCon[mcc[bullet[i].x][bullet[i].y].type-RESTORE_COM_TANK_POSITION].y+1].type = NONE;
							} else if(mcc[bullet[i].x][bullet[i].y+1].type!=NONE) {
								comTkCoorCon[mcc[bullet[i].x][bullet[i].y+1].type-RESTORE_COM_TANK_POSITION].flickerTimes = 0;
								comTkCoorCon[mcc[bullet[i].x][bullet[i].y+1].type-RESTORE_COM_TANK_POSITION].display = 0;
								comTkCoorCon[mcc[bullet[i].x][bullet[i].y+1].type-RESTORE_COM_TANK_POSITION].move = 0;
								mcc[comTkCoorCon[mcc[bullet[i].x][bullet[i].y+1].type-RESTORE_COM_TANK_POSITION].x][comTkCoorCon[mcc[bullet[i].x][bullet[i].y+1].type-RESTORE_COM_TANK_POSITION].y].type = NONE;
								mcc[comTkCoorCon[mcc[bullet[i].x][bullet[i].y+1].type-RESTORE_COM_TANK_POSITION].x][comTkCoorCon[mcc[bullet[i].x][bullet[i].y+1].type-RESTORE_COM_TANK_POSITION].y+1].type = NONE;
								mcc[comTkCoorCon[mcc[bullet[i].x][bullet[i].y+1].type-RESTORE_COM_TANK_POSITION].x+1][comTkCoorCon[mcc[bullet[i].x][bullet[i].y+1].type-RESTORE_COM_TANK_POSITION].y].type = NONE;
								mcc[comTkCoorCon[mcc[bullet[i].x][bullet[i].y+1].type-RESTORE_COM_TANK_POSITION].x+1][comTkCoorCon[mcc[bullet[i].x][bullet[i].y+1].type-RESTORE_COM_TANK_POSITION].y+1].type = NONE;
							}
							mcc[bullet[i].x][bullet[i].y].type = NONE;
							mcc[bullet[i].x][bullet[i].y+1].type = NONE;
							bullet[i].pimage = bulletBomb;
							bullet[i].width = TANK_BOMB_WIDTH;
							bullet[i].height = TANK_BOMB_HEIGHT;
							bullet[i].explode = 1;
					} else if(bullet[i].top<MAP_MOVE_DOWN_END && 
						(bullet[i].top+BULLET_HEIGHT+BULLET_SPEED)<=bullet[i].x*DRAW_MAP_SIZE) {
							bullet[i].top += BULLET_SPEED;
							bullet[i].pimage = tankBullet+1;
					} else if(bullet[i].top<MAP_MOVE_DOWN_END && 
						(bullet[i].top+BULLET_HEIGHT+BULLET_SPEED)>bullet[i].x*DRAW_MAP_SIZE) {
							bullet[i].top += BULLET_SPEED;
							bullet[i].x += 1;
							bullet[i].pimage = tankBullet+1;
					}
					/*------------------------------*/
				} else if(bullet[i].dir==LEFT) {
					if(bullet[i].left<=MAP_MOVE_LEFT_END) {
						bullet[i].pimage = bulletBomb;
						bullet[i].width = COMMON_BOMB_WIDTH;
						bullet[i].height = COMMON_BOMB_HEIGHT;
						bullet[i].explode = 1;
					} else if(bullet[i].left>MAP_MOVE_LEFT_END && 
						(mcc[bullet[i].x][bullet[i].y].type==BRICK || mcc[bullet[i].x+1][bullet[i].y].type==BRICK) || 
						(mcc[bullet[i].x][bullet[i].y].type==STEEL || mcc[bullet[i].x+1][bullet[i].y].type==STEEL)) {
							if(mcc[bullet[i].x][bullet[i].y].type==BRICK) {
								mcc[bullet[i].x][bullet[i].y].display = 0;
								mcc[bullet[i].x][bullet[i].y].type = NONE;
							}
							if(mcc[bullet[i].x+1][bullet[i].y].type==BRICK) {
								mcc[bullet[i].x+1][bullet[i].y].display = 0;
								mcc[bullet[i].x+1][bullet[i].y].type = NONE;
							}
							bullet[i].pimage = bulletBomb;
							bullet[i].width = COMMON_BOMB_WIDTH;
							bullet[i].height = COMMON_BOMB_HEIGHT;
							bullet[i].explode = 1;
					} else if(bullet[i].left>MAP_MOVE_LEFT_END && i<MAIN_BULLET_POS && 
						(mcc[bullet[i].x][bullet[i].y].type==MAINTANK || mcc[bullet[i].x+1][bullet[i].y].type==MAINTANK)) {
							mcc[mainTkCoorCon->x][mainTkCoorCon->y].type = NONE;
							mcc[mainTkCoorCon->x][mainTkCoorCon->y+1].type = NONE;
							mcc[mainTkCoorCon->x+1][mainTkCoorCon->y].type = NONE;
							mcc[mainTkCoorCon->x+1][mainTkCoorCon->y+1].type = NONE;
							mainTankLife--;
							mainTkCoorCon->flickerTimes = 0;
							mainTkCoorCon->display = 0;
							mainTkCoorCon->move = 0;
							bullet[i].pimage = bulletBomb;
							bullet[i].width = TANK_BOMB_WIDTH;
							bullet[i].height = TANK_BOMB_HEIGHT;
							bullet[i].explode = 1;
					} else if(bullet[i].left>MAP_MOVE_LEFT_END && i==MAIN_BULLET_POS && 
						((mcc[bullet[i].x][bullet[i].y].type==COMTANK1 || mcc[bullet[i].x+1][bullet[i].y].type==COMTANK1) || 
						(mcc[bullet[i].x][bullet[i].y].type==COMTANK2 || mcc[bullet[i].x+1][bullet[i].y].type==COMTANK2) || 
						(mcc[bullet[i].x][bullet[i].y].type==COMTANK3 || mcc[bullet[i].x+1][bullet[i].y].type==COMTANK3) || 
						(mcc[bullet[i].x][bullet[i].y].type==COMTANK4 || mcc[bullet[i].x+1][bullet[i].y].type==COMTANK4))) {
							if(mcc[bullet[i].x][bullet[i].y].type!=NONE) {
								comTkCoorCon[mcc[bullet[i].x][bullet[i].y].type-RESTORE_COM_TANK_POSITION].flickerTimes = 0;
								comTkCoorCon[mcc[bullet[i].x][bullet[i].y].type-RESTORE_COM_TANK_POSITION].display = 0;
								comTkCoorCon[mcc[bullet[i].x][bullet[i].y].type-RESTORE_COM_TANK_POSITION].move = 0;
								mcc[comTkCoorCon[mcc[bullet[i].x][bullet[i].y].type-RESTORE_COM_TANK_POSITION].x][comTkCoorCon[mcc[bullet[i].x][bullet[i].y].type-RESTORE_COM_TANK_POSITION].y].type = NONE;
								mcc[comTkCoorCon[mcc[bullet[i].x][bullet[i].y].type-RESTORE_COM_TANK_POSITION].x][comTkCoorCon[mcc[bullet[i].x][bullet[i].y].type-RESTORE_COM_TANK_POSITION].y+1].type = NONE;
								mcc[comTkCoorCon[mcc[bullet[i].x][bullet[i].y].type-RESTORE_COM_TANK_POSITION].x+1][comTkCoorCon[mcc[bullet[i].x][bullet[i].y].type-RESTORE_COM_TANK_POSITION].y].type = NONE;
								mcc[comTkCoorCon[mcc[bullet[i].x][bullet[i].y].type-RESTORE_COM_TANK_POSITION].x+1][comTkCoorCon[mcc[bullet[i].x][bullet[i].y].type-RESTORE_COM_TANK_POSITION].y+1].type = NONE;
							} else if(mcc[bullet[i].x+1][bullet[i].y].type!=NONE) {
								comTkCoorCon[mcc[bullet[i].x+1][bullet[i].y].type-RESTORE_COM_TANK_POSITION].flickerTimes = 0;
								comTkCoorCon[mcc[bullet[i].x+1][bullet[i].y].type-RESTORE_COM_TANK_POSITION].display = 0;
								comTkCoorCon[mcc[bullet[i].x][bullet[i].y].type-RESTORE_COM_TANK_POSITION].move = 0;
								mcc[comTkCoorCon[mcc[bullet[i].x+1][bullet[i].y+1].type-RESTORE_COM_TANK_POSITION].x][comTkCoorCon[mcc[bullet[i].x+1][bullet[i].y].type-RESTORE_COM_TANK_POSITION].y].type = NONE;
								mcc[comTkCoorCon[mcc[bullet[i].x+1][bullet[i].y+1].type-RESTORE_COM_TANK_POSITION].x][comTkCoorCon[mcc[bullet[i].x+1][bullet[i].y].type-RESTORE_COM_TANK_POSITION].y+1].type = NONE;
								mcc[comTkCoorCon[mcc[bullet[i].x+1][bullet[i].y+1].type-RESTORE_COM_TANK_POSITION].x+1][comTkCoorCon[mcc[bullet[i].x+1][bullet[i].y].type-RESTORE_COM_TANK_POSITION].y].type = NONE;
								mcc[comTkCoorCon[mcc[bullet[i].x+1][bullet[i].y+1].type-RESTORE_COM_TANK_POSITION].x+1][comTkCoorCon[mcc[bullet[i].x+1][bullet[i].y].type-RESTORE_COM_TANK_POSITION].y+1].type = NONE;
							}
							mcc[bullet[i].x][bullet[i].y].type = NONE;
							mcc[bullet[i].x+1][bullet[i].y].type = NONE;
							bullet[i].pimage = bulletBomb;
							bullet[i].width = TANK_BOMB_WIDTH;
							bullet[i].height = TANK_BOMB_HEIGHT;
							bullet[i].explode = 1;
					} else if(bullet[i].left>MAP_MOVE_LEFT_END && 
						(bullet[i].left-BULLET_SPEED)>=bullet[i].y*DRAW_MAP_SIZE) {
							bullet[i].left -= BULLET_SPEED;
							bullet[i].pimage = tankBullet+2;
					} else if(bullet[i].left>=MAP_MOVE_LEFT_END && 
						(bullet[i].left-BULLET_SPEED)<bullet[i].y*DRAW_MAP_SIZE) {
							bullet[i].left -= BULLET_SPEED;
							bullet[i].y -= 1;
							bullet[i].pimage = tankBullet+2;
					}
					/*------------------------------*/
				} else if(bullet[i].dir==RIGHT) {
					if(bullet[i].left>=MAP_MOVE_RIGHT_END) {
						bullet[i].pimage = bulletBomb;
						bullet[i].width = COMMON_BOMB_WIDTH;
						bullet[i].height = COMMON_BOMB_HEIGHT;
						bullet[i].explode = 1;
					} else if(bullet[i].left<MAP_MOVE_RIGHT_END && 
						(mcc[bullet[i].x][bullet[i].y].type==BRICK || mcc[bullet[i].x+1][bullet[i].y].type==BRICK) || 
						(mcc[bullet[i].x][bullet[i].y].type==STEEL || mcc[bullet[i].x+1][bullet[i].y].type==STEEL)) {
							if(mcc[bullet[i].x][bullet[i].y].type==BRICK) {
								mcc[bullet[i].x][bullet[i].y].display = 0;
								mcc[bullet[i].x][bullet[i].y].type = NONE;
							}
							if(mcc[bullet[i].x+1][bullet[i].y].type==BRICK) {
								mcc[bullet[i].x+1][bullet[i].y].display = 0;
								mcc[bullet[i].x+1][bullet[i].y].type = NONE;
							}
							bullet[i].pimage = bulletBomb;
							bullet[i].width = COMMON_BOMB_WIDTH;
							bullet[i].height = COMMON_BOMB_HEIGHT;
							bullet[i].explode = 1;
					} else if(bullet[i].left<MAP_MOVE_RIGHT_END && i<MAIN_BULLET_POS && 
						(mcc[bullet[i].x][bullet[i].y].type==MAINTANK || mcc[bullet[i].x+1][bullet[i].y].type==MAINTANK)) {
							mcc[mainTkCoorCon->x][mainTkCoorCon->y].type = NONE;
							mcc[mainTkCoorCon->x][mainTkCoorCon->y+1].type = NONE;
							mcc[mainTkCoorCon->x+1][mainTkCoorCon->y].type = NONE;
							mcc[mainTkCoorCon->x+1][mainTkCoorCon->y+1].type = NONE;
							mainTankLife--;
							mainTkCoorCon->flickerTimes = 0;
							mainTkCoorCon->display = 0;
							mainTkCoorCon->move = 0;
							bullet[i].pimage = bulletBomb;
							bullet[i].width = TANK_BOMB_WIDTH;
							bullet[i].height = TANK_BOMB_HEIGHT;
							bullet[i].explode = 1;
					} else if(bullet[i].left<MAP_MOVE_RIGHT_END && i==MAIN_BULLET_POS && 
						((mcc[bullet[i].x][bullet[i].y].type==COMTANK1 || mcc[bullet[i].x+1][bullet[i].y].type==COMTANK1) || 
						(mcc[bullet[i].x][bullet[i].y].type==COMTANK2 || mcc[bullet[i].x+1][bullet[i].y].type==COMTANK2) || 
						(mcc[bullet[i].x][bullet[i].y].type==COMTANK3 || mcc[bullet[i].x+1][bullet[i].y].type==COMTANK3) || 
						(mcc[bullet[i].x][bullet[i].y].type==COMTANK4 || mcc[bullet[i].x+1][bullet[i].y].type==COMTANK4))) {
							if(mcc[bullet[i].x][bullet[i].y].type!=NONE) {
								comTkCoorCon[mcc[bullet[i].x][bullet[i].y].type-RESTORE_COM_TANK_POSITION].flickerTimes = 0;
								comTkCoorCon[mcc[bullet[i].x][bullet[i].y].type-RESTORE_COM_TANK_POSITION].display = 0;
								comTkCoorCon[mcc[bullet[i].x][bullet[i].y].type-RESTORE_COM_TANK_POSITION].move = 0;
								mcc[comTkCoorCon[mcc[bullet[i].x][bullet[i].y].type-RESTORE_COM_TANK_POSITION].x][comTkCoorCon[mcc[bullet[i].x][bullet[i].y].type-RESTORE_COM_TANK_POSITION].y].type = NONE;
								mcc[comTkCoorCon[mcc[bullet[i].x][bullet[i].y].type-RESTORE_COM_TANK_POSITION].x][comTkCoorCon[mcc[bullet[i].x][bullet[i].y].type-RESTORE_COM_TANK_POSITION].y+1].type = NONE;
								mcc[comTkCoorCon[mcc[bullet[i].x][bullet[i].y].type-RESTORE_COM_TANK_POSITION].x+1][comTkCoorCon[mcc[bullet[i].x][bullet[i].y].type-RESTORE_COM_TANK_POSITION].y].type = NONE;
								mcc[comTkCoorCon[mcc[bullet[i].x][bullet[i].y].type-RESTORE_COM_TANK_POSITION].x+1][comTkCoorCon[mcc[bullet[i].x][bullet[i].y].type-RESTORE_COM_TANK_POSITION].y+1].type = NONE;
							} else if(mcc[bullet[i].x+1][bullet[i].y].type!=NONE) {
								comTkCoorCon[mcc[bullet[i].x+1][bullet[i].y].type-RESTORE_COM_TANK_POSITION].flickerTimes = 0;
								comTkCoorCon[mcc[bullet[i].x+1][bullet[i].y].type-RESTORE_COM_TANK_POSITION].display = 0;
								comTkCoorCon[mcc[bullet[i].x][bullet[i].y].type-RESTORE_COM_TANK_POSITION].move = 0;
								mcc[comTkCoorCon[mcc[bullet[i].x+1][bullet[i].y+1].type-RESTORE_COM_TANK_POSITION].x][comTkCoorCon[mcc[bullet[i].x+1][bullet[i].y].type-RESTORE_COM_TANK_POSITION].y].type = NONE;
								mcc[comTkCoorCon[mcc[bullet[i].x+1][bullet[i].y+1].type-RESTORE_COM_TANK_POSITION].x][comTkCoorCon[mcc[bullet[i].x+1][bullet[i].y].type-RESTORE_COM_TANK_POSITION].y+1].type = NONE;
								mcc[comTkCoorCon[mcc[bullet[i].x+1][bullet[i].y+1].type-RESTORE_COM_TANK_POSITION].x+1][comTkCoorCon[mcc[bullet[i].x+1][bullet[i].y].type-RESTORE_COM_TANK_POSITION].y].type = NONE;
								mcc[comTkCoorCon[mcc[bullet[i].x+1][bullet[i].y+1].type-RESTORE_COM_TANK_POSITION].x+1][comTkCoorCon[mcc[bullet[i].x+1][bullet[i].y].type-RESTORE_COM_TANK_POSITION].y+1].type = NONE;
							}
							mcc[bullet[i].x][bullet[i].y].type = NONE;
							mcc[bullet[i].x+1][bullet[i].y].type = NONE;
							bullet[i].pimage = bulletBomb;
							bullet[i].width = TANK_BOMB_WIDTH;
							bullet[i].height = TANK_BOMB_HEIGHT;
							bullet[i].explode = 1;
					} else if(bullet[i].left<MAP_MOVE_RIGHT_END && 
						(bullet[i].left+BULLET_WIDTH+BULLET_SPEED)<=bullet[i].y*DRAW_MAP_SIZE) {
							bullet[i].left += BULLET_SPEED;
							bullet[i].pimage = tankBullet+3;
					} else if(bullet[i].left<MAP_MOVE_RIGHT_END && 
						(bullet[i].left+BULLET_WIDTH+BULLET_SPEED)>bullet[i].y*DRAW_MAP_SIZE) {
							bullet[i].left += BULLET_SPEED;
							bullet[i].y += 1;
							bullet[i].pimage = tankBullet+3;
					}
					/*------------------------------*/
				} 
			}
		}
	} else {
		gameOver->display = 1;
		gameOver->x = 8;
		gameOver->y = 4;
		gameOver->left = gameOver->y*DRAW_MAP_SIZE;
		gameOver->top = gameOver->x*DRAW_MAP_SIZE;
		gameOver->width = GAME_OVER_WIDTH;
		gameOver->height = GAME_OVER_HEIGHT;
		gameOver->pimage = gameInterface+5;
	}
}
void timerEvent(int timerID) {
	drawMap();
	updateData();
}
void keyboardEvent (int key, int event) {
	if(mainTkCoorCon->flickerTimes>=4 && mainTkCoorCon->move==1) {
		if(key==VK_UP) {
			if((mainTkCoorCon->top-MAIN_TANK_SPEED)>=MAP_MOVE_UP_END && 
				(mainTkCoorCon->top-MAIN_TANK_SPEED)>=mainTkCoorCon->x*DRAW_MAP_SIZE) {
					mainTkCoorCon->top -= MAIN_TANK_SPEED;
			} else if((mainTkCoorCon->top-MAIN_TANK_SPEED)>=MAP_MOVE_UP_END && 
				(mainTkCoorCon->top-MAIN_TANK_SPEED)<mainTkCoorCon->x*DRAW_MAP_SIZE && 
				mcc[mainTkCoorCon->x-1][mainTkCoorCon->y].type==NONE && mcc[mainTkCoorCon->x-1][mainTkCoorCon->y+1].type==NONE) {
					mcc[mainTkCoorCon->x][mainTkCoorCon->y].type = NONE;
					mcc[mainTkCoorCon->x][mainTkCoorCon->y+1].type = NONE;
					mcc[mainTkCoorCon->x+1][mainTkCoorCon->y].type = NONE;
					mcc[mainTkCoorCon->x+1][mainTkCoorCon->y+1].type = NONE;
					mainTkCoorCon->top -= MAIN_TANK_SPEED;
					mainTkCoorCon->x -= 1;
					mcc[mainTkCoorCon->x][mainTkCoorCon->y].type = MAINTANK;
					mcc[mainTkCoorCon->x][mainTkCoorCon->y+1].type = MAINTANK;
					mcc[mainTkCoorCon->x+1][mainTkCoorCon->y].type = MAINTANK;
					mcc[mainTkCoorCon->x+1][mainTkCoorCon->y+1].type = MAINTANK;
			}
			mainTkCoorCon->dir = UP;
			mainTkCoorCon->pimage = mainTank;
		} else if(key==VK_DOWN) {
			if((mainTkCoorCon->top+TANK_HEIGHT+MAIN_TANK_SPEED)<=MAP_MOVE_DOWN_END && 
				(mainTkCoorCon->top+TANK_HEIGHT+MAIN_TANK_SPEED)<=(mainTkCoorCon->x+2)*DRAW_MAP_SIZE) {
					mainTkCoorCon->top += MAIN_TANK_SPEED;
			} else if((mainTkCoorCon->top+TANK_HEIGHT+MAIN_TANK_SPEED)<=MAP_MOVE_DOWN_END && 
				(mainTkCoorCon->top+TANK_HEIGHT+MAIN_TANK_SPEED)>(mainTkCoorCon->x+2)*DRAW_MAP_SIZE && 
				mcc[mainTkCoorCon->x+2][mainTkCoorCon->y].type==NONE && mcc[mainTkCoorCon->x+2][mainTkCoorCon->y+1].type==NONE) {
					mcc[mainTkCoorCon->x][mainTkCoorCon->y].type = NONE;
					mcc[mainTkCoorCon->x][mainTkCoorCon->y+1].type = NONE;
					mcc[mainTkCoorCon->x+1][mainTkCoorCon->y].type = NONE;
					mcc[mainTkCoorCon->x+1][mainTkCoorCon->y+1].type = NONE;
					mainTkCoorCon->top += MAIN_TANK_SPEED;
					mainTkCoorCon->x += 1;
					mcc[mainTkCoorCon->x][mainTkCoorCon->y].type = MAINTANK;
					mcc[mainTkCoorCon->x][mainTkCoorCon->y+1].type = MAINTANK;
					mcc[mainTkCoorCon->x+1][mainTkCoorCon->y].type = MAINTANK;
					mcc[mainTkCoorCon->x+1][mainTkCoorCon->y+1].type = MAINTANK;
			}
			mainTkCoorCon->dir = DOWN;
			mainTkCoorCon->pimage = mainTank+1;
		} else if(key==VK_LEFT) {
			if((mainTkCoorCon->left-MAIN_TANK_SPEED)>=MAP_MOVE_LEFT_END && 
				(mainTkCoorCon->left-MAIN_TANK_SPEED)>=mainTkCoorCon->y*DRAW_MAP_SIZE) {
					mainTkCoorCon->left -= MAIN_TANK_SPEED;
			} else if((mainTkCoorCon->left-MAIN_TANK_SPEED)>=MAP_MOVE_UP_END && 
				(mainTkCoorCon->left-MAIN_TANK_SPEED)<mainTkCoorCon->y*DRAW_MAP_SIZE && 
				mcc[mainTkCoorCon->x][mainTkCoorCon->y-1].type==NONE && mcc[mainTkCoorCon->x+1][mainTkCoorCon->y-1].type==NONE) {
					mcc[mainTkCoorCon->x][mainTkCoorCon->y].type = NONE;
					mcc[mainTkCoorCon->x][mainTkCoorCon->y+1].type = NONE;
					mcc[mainTkCoorCon->x+1][mainTkCoorCon->y].type = NONE;
					mcc[mainTkCoorCon->x+1][mainTkCoorCon->y+1].type = NONE;
					mainTkCoorCon->left -= MAIN_TANK_SPEED;
					mainTkCoorCon->y -= 1;
					mcc[mainTkCoorCon->x][mainTkCoorCon->y].type = MAINTANK;
					mcc[mainTkCoorCon->x][mainTkCoorCon->y+1].type = MAINTANK;
					mcc[mainTkCoorCon->x+1][mainTkCoorCon->y].type = MAINTANK;
					mcc[mainTkCoorCon->x+1][mainTkCoorCon->y+1].type = MAINTANK;
			}
			mainTkCoorCon->dir = LEFT;
			mainTkCoorCon->pimage = mainTank+2;
		} else if(key==VK_RIGHT) {
			if((mainTkCoorCon->left+TANK_WIDTH+MAIN_TANK_SPEED)<=MAP_MOVE_RIGHT_END && 
				(mainTkCoorCon->left+TANK_WIDTH+MAIN_TANK_SPEED)<=(mainTkCoorCon->y+2)*DRAW_MAP_SIZE) {
					mainTkCoorCon->left += MAIN_TANK_SPEED;
			} else if((mainTkCoorCon->left+TANK_WIDTH+MAIN_TANK_SPEED)<=MAP_MOVE_RIGHT_END && 
				(mainTkCoorCon->left+TANK_WIDTH+MAIN_TANK_SPEED)>(mainTkCoorCon->y+2)*DRAW_MAP_SIZE && 
				mcc[mainTkCoorCon->x][mainTkCoorCon->y+2].type==NONE && mcc[mainTkCoorCon->x+1][mainTkCoorCon->y+2].type==NONE) {
					mcc[mainTkCoorCon->x][mainTkCoorCon->y].type = NONE;
					mcc[mainTkCoorCon->x][mainTkCoorCon->y+1].type = NONE;
					mcc[mainTkCoorCon->x+1][mainTkCoorCon->y].type = NONE;
					mcc[mainTkCoorCon->x+1][mainTkCoorCon->y+1].type = NONE;
					mainTkCoorCon->left += MAIN_TANK_SPEED;
					mainTkCoorCon->y += 1;
					mcc[mainTkCoorCon->x][mainTkCoorCon->y].type = MAINTANK;
					mcc[mainTkCoorCon->x][mainTkCoorCon->y+1].type = MAINTANK;
					mcc[mainTkCoorCon->x+1][mainTkCoorCon->y].type = MAINTANK;
					mcc[mainTkCoorCon->x+1][mainTkCoorCon->y+1].type = MAINTANK;
			}
			mainTkCoorCon->dir = RIGHT;
			mainTkCoorCon->pimage = mainTank+3;
		} else if(key==VK_SPACE) {
			if(bullet[MAIN_BULLET_POS].update==0) {
				bullet[MAIN_BULLET_POS].dir = mainTkCoorCon->dir;
				bullet[MAIN_BULLET_POS].update = 1;
				bullet[MAIN_BULLET_POS].width = BULLET_WIDTH;
				bullet[MAIN_BULLET_POS].height = BULLET_HEIGHT;
				if(bullet[MAIN_BULLET_POS].dir==UP) {
					bullet[MAIN_BULLET_POS].x = mainTkCoorCon->x;
					bullet[MAIN_BULLET_POS].y = mainTkCoorCon->y;
					bullet[MAIN_BULLET_POS].left = bullet[MAIN_BULLET_POS].y*DRAW_MAP_SIZE+BULLET_WIDTH_DISTANCE;
					bullet[MAIN_BULLET_POS].top = bullet[MAIN_BULLET_POS].x*DRAW_MAP_SIZE+BULLET_HEIGHT_DISTANCE;
				} else if(bullet[MAIN_BULLET_POS].dir==DOWN) {
					bullet[MAIN_BULLET_POS].x = mainTkCoorCon->x;
					bullet[MAIN_BULLET_POS].y = mainTkCoorCon->y;
					bullet[MAIN_BULLET_POS].left = bullet[MAIN_BULLET_POS].y*DRAW_MAP_SIZE+BULLET_WIDTH_DISTANCE;
					bullet[MAIN_BULLET_POS].top = bullet[MAIN_BULLET_POS].x*DRAW_MAP_SIZE+BULLET_HEIGHT_DISTANCE;
				} else if(bullet[MAIN_BULLET_POS].dir==LEFT) {
					bullet[MAIN_BULLET_POS].x = mainTkCoorCon->x;
					bullet[MAIN_BULLET_POS].y = mainTkCoorCon->y;
					bullet[MAIN_BULLET_POS].left = bullet[MAIN_BULLET_POS].y*DRAW_MAP_SIZE+BULLET_HEIGHT_DISTANCE;
					bullet[MAIN_BULLET_POS].top = bullet[MAIN_BULLET_POS].x*DRAW_MAP_SIZE+BULLET_WIDTH_DISTANCE;
				} else if(bullet[MAIN_BULLET_POS].dir==RIGHT) {
					bullet[MAIN_BULLET_POS].x = mainTkCoorCon->x;
					bullet[MAIN_BULLET_POS].y = mainTkCoorCon->y;
					bullet[MAIN_BULLET_POS].left = bullet[MAIN_BULLET_POS].y*DRAW_MAP_SIZE+BULLET_HEIGHT_DISTANCE;
					bullet[MAIN_BULLET_POS].top = bullet[MAIN_BULLET_POS].x*DRAW_MAP_SIZE+BULLET_WIDTH_DISTANCE;
				}
			}
		}
	}
}
int Setup() {
//	initConsole();
	beginInit();
	registerTimerEvent(timerEvent);
	registerKeyboardEvent(keyboardEvent);
	srand((unsigned int)time(NULL));		//seed random number
	startTimer(0, REFRESH_SCREEN_TIME);
	return 0;
}