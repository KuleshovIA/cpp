#include <stdio.h>
#include <stdlib.h>

#include <math.h>
#include <windows.h>

#define mapWidth 90
#define mapHeight 25

typedef struct SObject { //0.5 МБ на первом уровне
	float x, y;
	float width, height;
	float vertSpeed;
	bool isFly;
	char cType;
	float horizonSpeed;
} TObject;

char map[mapHeight][mapWidth + 1];
TObject mario;

TObject *brick = NULL;
int brickLength;

TObject *moving = NULL;
int movingLength;

int level = 1;
int score;
int maxLvl;

void ClearMap() {
	for (int i = 0; i < mapWidth; i++) {
		map[0][i] = ' ';
	}
	map[0][mapWidth] = '\0';
	for (int j = 1; j < mapHeight; j++) {
		sprintf(map[j], map[0]);
	}
}

void ShowMap() {
	map[mapHeight - 1][mapWidth - 1] = '\0';
	for (int j = 0; j < mapHeight; j++) {
		printf("%s", map[j]);
	}
}

void SetObjectPos(TObject *obj, float xPos, float yPos) {
	(*obj).x = xPos;
	(*obj).y = yPos;
}

void InitObject(TObject *obj, float xPos, float yPos, float oWidth, float oHeight, char inType) {
	SetObjectPos(obj, xPos, yPos);
	(*obj).width = oWidth;
	(*obj).height = oHeight;
	(*obj).vertSpeed = 0;
	(*obj).cType = inType;
	(*obj).horizonSpeed = 0.2;
}
void CreateLevel(int lvl);

void PlayerDead() {
	system("color 4F");
	Sleep(500);
	CreateLevel(level);
}

bool IsCollision(TObject o1, TObject o2);

TObject* GetNewMoving();

void VertMoveObject(TObject *obj) {
	(*obj).isFly = true;
	(*obj).vertSpeed += 0.05;
	SetObjectPos(obj, (*obj).x, (*obj).y + (*obj).vertSpeed);
	
	for (int i = 0; i < brickLength; i++) {
		if (IsCollision(*obj, brick[i])) {
			if (obj[0].vertSpeed > 0) {
				obj[0].isFly = false;
			}
			if ((brick[i].cType == '?') && (obj[0].vertSpeed < 0) && (obj == &mario)) {
				brick[i].cType = '-';
				InitObject(GetNewMoving(), brick[i].x, brick[i].y - 3, 3, 2, '$');
				moving[movingLength - 1].vertSpeed = -0.7;
			}
			(*obj).y -= (*obj).vertSpeed;
			(*obj).vertSpeed = 0;
			if (brick[i].cType == '+') {
				level++;
				if (level > maxLvl) level = 1;
				
				system("color 2F");
				Sleep(500);
				CreateLevel(level);
			}
			break;
		}
	}
}

void DeleteMoving (int i) {
	movingLength--;
	moving[i] = moving[movingLength];
	moving = realloc(moving, sizeof(*moving) * movingLength);
}

void MarioCollision() {
	for (int i = 0; i < movingLength; i++) {
		if (IsCollision(mario, moving[i])) {
			if (moving[i].cType == 'o') {
				if ((mario.isFly == true) 
					&& (mario.vertSpeed > 0)
					&& (mario.y + mario.height < moving[i].y + moving[i].height * 0.5)
				) {
					score += 50;
					DeleteMoving(i);
					i--;
					continue;
				} else {
					PlayerDead();
				}
			}
			if (moving[i].cType == '$') {
				score += 100;
				DeleteMoving(i);
				i--;
				continue;
			}
		}
	}
}

void HorizonMoveObject(TObject *obj) {
	obj[0].x += obj[0].horizonSpeed;
	for (int i = 0; i < brickLength; i++) {
		if (IsCollision(obj[0], brick[i])) {
			obj[0].x -= obj[0].horizonSpeed;
			obj[0].horizonSpeed = -obj[0].horizonSpeed;
			return;
		}
	}
	
	if (obj[0].cType == 'o') {
		TObject tmp = *obj;
		VertMoveObject(&tmp);
		if (tmp.isFly == true) {
			obj[0].x -= obj[0].horizonSpeed;
			obj[0].horizonSpeed = -obj[0].horizonSpeed;
		}
	}
}

bool IsPosInMap(int x, int y) {
	return ((x >= 0) && (x < mapWidth) && (y >= 0) && (y < mapHeight));
}

void PutObjectOnMap(TObject obj) {
	int ix = (int)round(obj.x);
	int iy = (int)round(obj.y);
	int iWidth = (int)round(obj.width);
	int iHeight = (int)round(obj.height);
	
	for (int i = ix; i < (ix + iWidth); i++) {
		for (int j = iy; j < (iy + iHeight); j++) {
			if (IsPosInMap(i, j)) {
				map[j][i] = obj.cType;
			}
		}
	}
}

void SetCur(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void HorizonMoveMap(float dx) {
	mario.x -= dx;
	for (int i = 0; i < brickLength; i++) {
		if (IsCollision(mario, brick[i])) {
			mario.x += dx;
			return;
		}
	}
	mario.x += dx;
	
	for (int i = 0; i < brickLength; i++) {
		brick[i].x += dx;
	}
	for (int i = 0; i < movingLength; i++) {
		moving[i].x += dx;
	}
}

bool IsCollision(TObject o1, TObject o2) {
	return ((o1.x + o1.width) > o2.x) && (o1.x < (o2.x + o2.width)) && 
		   ((o1.y + o1.height) > o2.y) && (o1.y < (o2.y + o2.height));
}

TObject* GetNewBrick() {
	brickLength++;
	brick = realloc(brick, sizeof(*brick) * brickLength);
	return brick + brickLength - 1;
}

TObject* GetNewMoving() {
	movingLength++;
	moving = realloc(moving, sizeof(*moving) * movingLength);
	return moving + movingLength - 1;
}

void PutScoreOnMap() {
	char c[30];
	sprintf(c, "Score: %d", score);
	int len = strlen(c);
	for (int i = 0; i < len; i++) {
		map[1][i + 5] = c[i];
	}
}

void CreateLevel(int lvl) {
	system("color 9F");
	
	brickLength = 0;
	brick = realloc(brick, 0);
	movingLength = 0;
	moving = realloc(moving, 0);
	
	InitObject(&mario, 39, 10, 3, 3, '@');
	score = 0;
	
	if (lvl == 1) {
		InitObject(GetNewBrick(), 20, 20, 40, 5, '#');
		InitObject(GetNewBrick(), 60, 15, 40, 10, '#');
		InitObject(GetNewBrick(), 30, 10, 5, 3, '?');
		InitObject(GetNewBrick(), 50, 10, 5, 3, '?');
		InitObject(GetNewBrick(), 100, 20, 20, 5, '#');
		InitObject(GetNewBrick(), 60, 5, 10, 3, '-');
		InitObject(GetNewBrick(), 70, 5, 5, 3, '?');
		InitObject(GetNewBrick(), 75, 5, 5, 3, '-');
		InitObject(GetNewBrick(), 80, 5, 5, 3, '?');
		InitObject(GetNewBrick(), 85, 5, 10, 3, '-');
		InitObject(GetNewBrick(), 120, 15, 10, 10, '#');
		InitObject(GetNewBrick(), 150, 20, 40, 5, '#');
		InitObject(GetNewBrick(), 210, 15, 10, 10, '+');
		InitObject(GetNewMoving(), 25, 10, 3, 2, 'o');
		InitObject(GetNewMoving(), 80, 10, 3, 2, 'o');
	}
	if (lvl == 2) {
		InitObject(GetNewBrick(), 20, 20, 40, 5, '#');
		InitObject(GetNewBrick(), 60, 15, 10, 10, '#');
		InitObject(GetNewBrick(), 80, 20, 20, 5, '#');
		InitObject(GetNewBrick(), 120, 15, 10, 10, '#');
		InitObject(GetNewBrick(), 150, 20, 40, 5, '#');
		InitObject(GetNewBrick(), 210, 15, 10, 10, '+');
		InitObject(GetNewMoving(), 25, 10, 3, 2, 'o');
		InitObject(GetNewMoving(), 80, 10, 3, 2, 'o');
		InitObject(GetNewMoving(), 65, 10, 3, 2, 'o');
		InitObject(GetNewMoving(), 120, 10, 3, 2, 'o');
		InitObject(GetNewMoving(), 160, 10, 3, 2, 'o');
		InitObject(GetNewMoving(), 175, 10, 3, 2, 'o');
	}
	if (lvl == 3) {
		InitObject(GetNewBrick(), 20, 20, 40, 5, '#');
		InitObject(GetNewBrick(), 80, 20, 15, 5, '#');
		InitObject(GetNewBrick(), 120, 15, 15, 10, '#');
		InitObject(GetNewBrick(), 160, 10, 15, 15, '+');
		InitObject(GetNewMoving(), 25, 10, 3, 2, 'o');
		InitObject(GetNewMoving(), 50, 10, 3, 2, 'o');
		InitObject(GetNewMoving(), 80, 10, 3, 2, 'o');
		InitObject(GetNewMoving(), 90, 10, 3, 2, 'o');
		InitObject(GetNewMoving(), 120, 10, 3, 2, 'o');
		InitObject(GetNewMoving(), 130, 10, 3, 2, 'o');
	}
	if (lvl == 4)
    {
        InitObject(GetNewBrick(),  0, 21, 207, 4, '#');

            InitObject(GetNewBrick(), 48, 13, 3, 2, '?');
            InitObject(GetNewBrick(), 60, 13, 3, 2, '#');
            InitObject(GetNewBrick(), 63, 13, 3, 2, '?');
            InitObject(GetNewBrick(), 66, 13, 3, 2, '#');
            InitObject(GetNewBrick(), 69, 13, 3, 2, '?');
            InitObject(GetNewBrick(), 72, 13, 3, 2, '#');
            InitObject(GetNewBrick(), 66, 5, 3, 2, '?');

        InitObject(GetNewBrick(), 84, 17, 6, 2, '#');
        InitObject(GetNewBrick(), 85, 19, 4, 2, '#');

        InitObject(GetNewBrick(), 114, 15, 6, 2, '#');
        InitObject(GetNewBrick(), 115, 17, 4, 4, '#');

        InitObject(GetNewBrick(), 138, 13, 6, 2, '#');
        InitObject(GetNewBrick(), 139, 15, 4, 6, '#');

        InitObject(GetNewBrick(), 171, 13, 6, 2, '#');
        InitObject(GetNewBrick(), 172, 15, 4, 6, '#');
        
        InitObject(GetNewBrick(),  213, 21, 45, 4, '#');
            InitObject(GetNewBrick(), 231, 13, 3, 2, '#');
            InitObject(GetNewBrick(), 234, 13, 3, 2, '?');
            InitObject(GetNewBrick(), 237, 13, 3, 2, '#');
                InitObject(GetNewBrick(), 240, 5, 24, 2, '#');
        
        InitObject(GetNewBrick(),  267, 21, 192, 4, '#');
                InitObject(GetNewBrick(), 273, 5, 9, 2, '#');
                InitObject(GetNewBrick(), 282, 5, 3, 2, '?');
            InitObject(GetNewBrick(), 282, 13, 3, 2, '?');
            InitObject(GetNewBrick(), 300, 13, 6, 2, '#');
            InitObject(GetNewBrick(), 318, 13, 3, 2, '?');
            InitObject(GetNewBrick(), 327, 13, 3, 2, '?');
                InitObject(GetNewBrick(), 327, 5, 3, 2, '?');
            InitObject(GetNewBrick(), 336, 13, 3, 2, '?');
            InitObject(GetNewBrick(), 354, 13, 3, 2, '#');
                InitObject(GetNewBrick(), 363, 5, 9, 2, '#');
                InitObject(GetNewBrick(), 384, 5, 3, 2, '#');
                InitObject(GetNewBrick(), 387, 5, 3, 2, '?');
                InitObject(GetNewBrick(), 390, 5, 3, 2, '?');
                InitObject(GetNewBrick(), 393, 5, 3, 2, '#');
            InitObject(GetNewBrick(), 387, 13, 6, 2, '#');
            
            InitObject(GetNewBrick(), 402, 19, 12, 2, '#');
            InitObject(GetNewBrick(), 405, 17, 9, 2, '#');
            InitObject(GetNewBrick(), 408, 15, 6, 2, '#');
            InitObject(GetNewBrick(), 411, 13, 3, 2, '#');

            InitObject(GetNewBrick(), 420, 13, 3, 2, '#');
            InitObject(GetNewBrick(), 420, 15, 6, 2, '#');
            InitObject(GetNewBrick(), 420, 17, 9, 2, '#');
            InitObject(GetNewBrick(), 420, 19, 12, 2, '#');

            InitObject(GetNewBrick(), 444, 19, 15, 2, '#');
            InitObject(GetNewBrick(), 447, 17, 12, 2, '#');
            InitObject(GetNewBrick(), 450, 15, 9, 2, '#');
            InitObject(GetNewBrick(), 453, 13, 6, 2, '#');
        
        InitObject(GetNewBrick(), 465, 21, 165, 4, '#');
            InitObject(GetNewBrick(), 465, 13, 3, 2, '#');
            InitObject(GetNewBrick(), 465, 15, 6, 2, '#');
            InitObject(GetNewBrick(), 465, 17, 9, 2, '#');
            InitObject(GetNewBrick(), 465, 19, 12, 2, '#');

            InitObject(GetNewBrick(), 489, 17, 6, 2, '#');
            InitObject(GetNewBrick(), 490, 19, 4, 2, '#');

            InitObject(GetNewBrick(), 504, 13, 6, 2, '#');
            InitObject(GetNewBrick(), 510, 13, 3, 2, '?');
            InitObject(GetNewBrick(), 513, 13, 3, 2, '#');

            InitObject(GetNewBrick(), 537, 17, 6, 2, '#');
            InitObject(GetNewBrick(), 538, 19, 4, 2, '#');
            
            InitObject(GetNewBrick(), 543, 19, 27, 2, '#');
            InitObject(GetNewBrick(), 546, 17, 24, 2, '#');
            InitObject(GetNewBrick(), 549, 15, 21, 2, '#');
            InitObject(GetNewBrick(), 552, 13, 18, 2, '#');
            InitObject(GetNewBrick(), 555, 11, 15, 2, '#');
            InitObject(GetNewBrick(), 558,  9, 12, 2, '#');
            InitObject(GetNewBrick(), 561,  7,  9, 2, '#');
            InitObject(GetNewBrick(), 564,  5,  6, 2, '#');

            
            InitObject(GetNewBrick(), 600, 16, 10, 5, '+');
                InitObject(GetNewBrick(), 600, 15, 1, 1, '+');
                InitObject(GetNewBrick(), 609, 15, 1, 1, '+');
                InitObject(GetNewBrick(), 604, 17, 2, 4, '-');
            InitObject(GetNewBrick(), 602, 12, 6, 4, '+');
                InitObject(GetNewBrick(), 602, 11, 1, 1, '+');
                InitObject(GetNewBrick(), 604, 11, 2, 1, '+');
                InitObject(GetNewBrick(), 607, 11, 1, 1, '+');
                InitObject(GetNewBrick(), 603, 13, 1, 2, '-');
                InitObject(GetNewBrick(), 606, 13, 1, 2, '-');

        InitObject(GetNewMoving(), 66, 16, 3, 2, 'o');
        InitObject(GetNewMoving(), 121, 16, 3, 2, 'o');
        InitObject(GetNewMoving(), 153, 16, 3, 2, 'o');
        InitObject(GetNewMoving(), 159, 16, 3, 2, 'o');

            InitObject(GetNewMoving(), 238, 1, 3, 2, 'o');
            InitObject(GetNewMoving(), 246, 1, 3, 2, 'o');
        InitObject(GetNewMoving(), 288, 16, 3, 2, 'o');
        InitObject(GetNewMoving(), 294, 16, 3, 2, 'o');
        InitObject(GetNewMoving(), 321, 16, 3, 2, 'o');
        InitObject(GetNewMoving(), 342, 16, 3, 2, 'o');
        InitObject(GetNewMoving(), 348, 16, 3, 2, 'o');
        InitObject(GetNewMoving(), 370, 16, 3, 2, 'o');
        InitObject(GetNewMoving(), 376, 16, 3, 2, 'o');
        InitObject(GetNewMoving(), 385, 16, 3, 2, 'o');
        InitObject(GetNewMoving(), 391, 16, 3, 2, 'o');

        InitObject(GetNewMoving(), 522, 16, 3, 2, 'o');
        InitObject(GetNewMoving(), 526, 16, 3, 2, 'o');

    }
	maxLvl = 4;
}

int main() {
	CreateLevel(level);
	
	do {
		ClearMap();
		
		if ((mario.isFly == false) && (GetKeyState(VK_SPACE) < 0)) mario.vertSpeed = -1;
		if (GetKeyState('A') < 0) HorizonMoveMap(1);
		if (GetKeyState('D') < 0) HorizonMoveMap(-1);
		
		if (mario.y > mapHeight) PlayerDead();
		
		VertMoveObject(&mario);
		MarioCollision();
		
		for (int i = 0; i < brickLength; i++) {
			PutObjectOnMap(brick[i]);
		}
		for (int i = 0; i < movingLength; i++) {
			VertMoveObject(moving + i);
			HorizonMoveObject(moving + i);
			if (moving[i].y > mapHeight) {
				DeleteMoving(i);
				i--;
				continue;
			}
			PutObjectOnMap(moving[i]);
		}
		PutObjectOnMap(mario);
		PutScoreOnMap();
		
		SetCur(0, 0);
		ShowMap();
		
		Sleep(10);
	} while (GetKeyState(VK_ESCAPE) >= 0);
	
	return 0;
}