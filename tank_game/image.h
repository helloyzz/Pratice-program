#ifndef _IMAGE_HEAD_H_
#define _IMAGE_HEAD_H_

#include "acllib.h"

//main battle tank picture of grade 1
#define MAIN_TANK_1_U "./tank_fright/tank/main_tk_1/yel_1_u.bmp"
#define MAIN_TANK_1_D "./tank_fright/tank/main_tk_1/yel_1_d.bmp"
#define MAIN_TANK_1_L "./tank_fright/tank/main_tk_1/yel_1_l.bmp"
#define MAIN_TANK_1_R "./tank_fright/tank/main_tk_1/yel_1_r.bmp"
//main battle tank picture of grade 2
#define MAIN_TANK_2_U "./tank_fright/tank/main_tk_2/yel_2_u.bmp"
#define MAIN_TANK_2_D "./tank_fright/tank/main_tk_2/yel_2_d.bmp"
#define MAIN_TANK_2_L "./tank_fright/tank/main_tk_2/yel_2_l.bmp"
#define MAIN_TANK_2_R "./tank_fright/tank/main_tk_2/yel_2_r.bmp"
//main battle tank picture of grade 3
#define MAIN_TANK_3_U "./tank_fright/tank/main_tk_3/yel_3_u.bmp"
#define MAIN_TANK_3_D "./tank_fright/tank/main_tk_3/yel_3_d.bmp"
#define MAIN_TANK_3_L "./tank_fright/tank/main_tk_3/yel_3_l.bmp"
#define MAIN_TANK_3_R "./tank_fright/tank/main_tk_3/yel_3_r.bmp"
//computer tank picture of gray
#define COM_TANK_GREY_1_U "./tank_fright/tank/com_tk_1/gray/gray_1_u.bmp"
#define COM_TANK_GREY_1_D "./tank_fright/tank/com_tk_1/gray/gray_1_d.bmp"
#define COM_TANK_GREY_1_L "./tank_fright/tank/com_tk_1/gray/gray_1_l.bmp"
#define COM_TANK_GREY_1_R "./tank_fright/tank/com_tk_1/gray/gray_1_r.bmp"
//computer tank picture of red
#define COM_TANK_RED_1_U "./tank_fright/tank/com_tk_1/red/red_1_u.bmp"
#define COM_TANK_RED_1_D "./tank_fright/tank/com_tk_1/red/red_1_d.bmp"
#define COM_TANK_RED_1_L "./tank_fright/tank/com_tk_1/red/red_1_l.bmp"
#define COM_TANK_RED_1_R "./tank_fright/tank/com_tk_1/red/red_1_r.bmp"
//computer tank picture of green
#define COM_TANK_GREEN_3_U "./tank_fright/tank/com_tk_3/green/gre_3_u.bmp"
#define COM_TANK_GREEN_3_D "./tank_fright/tank/com_tk_3/green/gre_3_d.bmp"
#define COM_TANK_GREEN_3_L "./tank_fright/tank/com_tk_3/green/gre_3_l.bmp"
#define COM_TANK_GREEN_3_R "./tank_fright/tank/com_tk_3/green/gre_3_r.bmp"
//tank initialize
#define TANK_INIT_1 "./tank_fright/tank/init_tk/com_tk_init_1.bmp"
#define TANK_INIT_2 "./tank_fright/tank/init_tk/com_tk_init_2.bmp"
#define TANK_INIT_3 "./tank_fright/tank/init_tk/com_tk_init_3.bmp"
#define TANK_INIT_4 "./tank_fright/tank/init_tk/com_tk_init_4.bmp"
//map picture position
#define MAP_BRICK "./tank_fright/map/brick.bmp"
#define MAP_STEEL "./tank_fright/map/steel.bmp"
#define MAP_HOME "./tank_fright/map/home.bmp"
#define MAP_GRASS "./tank_fright/map/grass.bmp"
#define MAP_WATER "./tank_fright/map/water.bmp"
//tank bullet
#define TANK_BULLET_U "./tank_fright/bullet/bullet_u.bmp"
#define TANK_BULLET_D "./tank_fright/bullet/bullet_d.bmp"
#define TANK_BULLET_L "./tank_fright/bullet/bullet_l.bmp"
#define TANK_BULLET_R "./tank_fright/bullet/bullet_r.bmp"
//tank bomb
#define  TANK_BOMB "./tank_fright/bomb/bomb.bmp"
//tank tools
#define  LEFT_ARROW "./tank_fright/tools/left_arrow.bmp"
#define  RIGHT_ARROW "./tank_fright/tools/right_arrow.bmp"
#define  GAME_START "./tank_fright/tools/start_game.bmp"
#define  BANNER "./tank_fright/tools/banner.bmp"
#define  ENEMY_TANK_COUNT "./tank_fright/tools/enemy_tk_count.bmp"
#define  GAME_OVER "./tank_fright/tools/game_over.bmp"
//tank update
#define  ADD_LIFE "./tank_fright/update/add_life.bmp"
#define  PAUSE "./tank_fright/update/pause.bmp"
#define  UPGRADE "./tank_fright/update/upgrade.bmp"
#define  CONSTRUCTOR "./tank_fright/update/constructor.bmp"
#define  DESTROY_ENEMY "./tank_fright/update/destroy_enemy.bmp"
#define  UNBEATABLE "./tank_fright/update/unbeatable.bmp"

//timer refresh constant
#define REFRESH_SCREEN_TIME 80
//window constant
#define DEFAULT_VALUE 0
#define WINDOW_TO_SCREEN_LEFT 350
#define WINDOW_TO_SCREEN_TOP 80
#define SCREEN_WIDTH 520
#define SCREEN_HEIGHT 560
//container constant
#define COORDINATE_ROW_SIZE 30
#define COORDINATE_LIST_SIZE 28
#define COORDINATE_ROW 28
#define COORDINATE_LIST 26
//map constant
#define DRAW_MAP_SIZE 20
#define DRAW_OTHER_SIZE 40
#define MAP_MOVE_DOWN_END 560
#define MAP_MOVE_UP_END 0
#define MAP_MOVE_LEFT_END 0
#define MAP_MOVE_RIGHT_END 520
//tank constant
#define TANK_WIDTH 28
#define TANK_HEIGHT 28
#define TANK_TO_LEFT_DISTANCE 6
#define TANK_TO_TOP_DISTANCE 6
#define MAIN_TANK_INIT_X 26
#define MAIN_TANK_INIT_Y 8
#define MAIN_TANK_SPEED 4
#define COM_TANK_SPEED 6
#define SCREEN_COM_TANK_MAX 4
#define COM_TANK_INIT_INTERVAL 25
#define COM_TANK_MOVE_TIMES 3
#define RESTORE_COM_TANK_POSITION 7
//bullet constant
#define SCREEN_BULLET_MAX 5
#define BULLET_SPEED 12
#define MAIN_BULLET_POS 4
#define BULLET_WIDTH 6
#define BULLET_HEIGHT 6
#define COMMON_BOMB_WIDTH 10
#define COMMON_BOMB_HEIGHT 10
#define TANK_BOMB_WIDTH 30
#define TANK_BOMB_HEIGHT 30
#define BULLET_WIDTH_DISTANCE 17
#define BULLET_HEIGHT_DISTANCE 17
//game over constant
#define GAME_OVER_WIDTH 360
#define GAME_OVER_HEIGHT 280
//represent coorCondition type
typedef enum {
	NONE, BRICK, STEEL, HOME, GRASS, WATER, MAINTANK, COMTANK1, COMTANK2, COMTANK3, COMTANK4, BULLET
} OBJ_CONDITION;
//represent tank direction
typedef enum {
	UP, DOWN, LEFT, RIGHT
} OBJ_DIRECTION;

//map coordinate condition
typedef struct {
	int x;				//x coordinate
	int y;				//y coordinate
	int left;			//distance to left
	int top;			//distance to top
	int type;			//pincture type
	int width;			//picture width
	int height;			//picture height
	int display;		//whether or not to shown
	ACL_Image* pimage;	//picture object
} mapCoorCon;
//bullet structure
typedef struct {
	int x;					//x coordinate
	int y;					//y coordinate
	int left;				//distance to left
	int top;				//distance to top
	int type;				//pincture type
	int width;				//picture width
	int height;				//picture height
	int dir;				//represent bullet direction
	int display;			//whether or not to shown
	int update;				//whether or not to update
	int explode;			//whether or not to explode
	ACL_Image* pimage;		//picture object
} bulletCoorCon;
//tank structure
typedef struct tankObj {
	int x;					//x coordinate
	int y;					//y coordinate
	int left;				//distance to left
	int top;				//distance to top
	int type;				//pincture type
	int width;				//picture width
	int height;				//picture height
	int dir;				//represent tank direction
	int display;			//whether or not to shown
	int flickerTimes;		//initial flicker times
	int move;				//whether or not computer tank move
	int moveDis;			//move distance
	ACL_Image* pimage;		//picture object
} tankCoorCon;

#endif
