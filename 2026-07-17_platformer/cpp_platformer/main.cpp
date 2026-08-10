#include <cmath>
#include <cstddef>
#include <cstdio>
#include <vector>
#include <windows.h>

#define MAP_WIDTH 90
#define MAP_HEIGHT 25


struct Object {
	float x, y;
	float width, height;
	char type;
	float horizontal_speed, vertical_speed;
	bool is_fly = false; //Или TRUE?
	bool is_alive = true;
};

struct Level {
	std::vector<Object> bricks;
	std::vector<Object> moving;
};

struct GameState {
	char map[MAP_HEIGHT][MAP_WIDTH + 1];
	Object character;
	Level current_level;
	int level_number = 1;
	bool level_complete = false;
};


void clear_map(char (&map)[][MAP_WIDTH + 1]);
void show_map(const char(&map)[][MAP_WIDTH + 1]);
void set_cursor(int x = 0, int y = 0);
void put_object_on_map(char(&map)[][MAP_WIDTH + 1], const Object& obj);
bool is_pos_in_map(int x, int y);
Object init_object(float x_pos, float y_pos, float o_width, float o_height, char in_type);
void init_level(int level_number, Level& current_level);
bool is_collision(const Object& obj1, const Object& obj2);
//Level init_level(int level);
void apply_gravity(Object& obj);
void vertical_move(Object& obj);
int find_brick_collision(const std::vector<Object>& bricks, const Object& obj);
void resolve_vertical_collision(Object& obj, const Object& brick);
void update_vertical(GameState& game, Object& obj);
void horizontal_move_map(GameState& game, float dx);
void handle_input(GameState& game);
void update_player(GameState& game);
void update_moving(GameState& game);
void update(GameState& game);
void render(GameState& game);
void update_horizontal(GameState& game, Object& obj);
void handle_contacts(GameState& game);
void clear_dead_objects(std::vector<Object>& moving);
void process_events(GameState& game);



/*Может быть во всех функциях (или не во всех), что проверяют контакт персонажа с чем-то, лучше сделать
принудительную проверку всех элементов вектора через цикл do while?*/
//Надо будет "причесать" параметры функций, чтобы избежать слишком длинных обращений
int main() {
	GameState game;
	game.character = init_object(39, 10, 3, 3, '@');
	init_level(game.level_number, game.current_level);
	//game.current_level = init_level(game.level);
	do {
		handle_input(game);
		update(game);
		render(game);
	} while (GetKeyState(VK_ESCAPE) >= 0);
	
	return 0;
}



void clear_map(char(&map)[][MAP_WIDTH + 1]) {
	for (int i = 0; i < MAP_WIDTH; i++) {
		map[0][i] = '.';
	}
	map[0][MAP_WIDTH] = '\0';
	for (int j = 1; j < MAP_HEIGHT; j++) {
		sprintf(map[j], map[0]);
	}
}

void show_map(const char(&map)[][MAP_WIDTH + 1]) {
	for (int j = 0; j < MAP_HEIGHT; j++) {
		printf("%s", map[j]);
	}
}

void set_cursor(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void put_object_on_map (char(&map)[][MAP_WIDTH + 1], const Object& obj) {
	int i_x = static_cast<int>(round(obj.x));
	int i_y = static_cast<int>(round(obj.y));
	int i_width = static_cast<int>(round(obj.width));
	int i_height = static_cast<int>(round(obj.height));
	
	for (int i = i_x; i < i_x + i_width; i++) {
		for (int j = i_y; j < i_y + i_height; j++) {
			if (is_pos_in_map(i, j)) {
				map[j][i] = obj.type;
			}
		}
	}
}

bool is_pos_in_map(int x, int y) {
	return (x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT);
}

Object init_object(float x_pos, float y_pos, float o_width, float o_height, char in_type) { //добавить сюда параметры горизонтальной и вертикальной скоростей, установленные значениями по умолчанию
	return Object {x_pos, y_pos, o_width, o_height, in_type, 0.2, 0};
}

void add_object(std::vector<Object>& recipient, Object obj) {
	recipient.push_back(obj);
}

//Возможно, нужно будет переделать с использованием функции выше (когда она понадобится) 
//Вот так: add_object (current_level.bricks, init_object(...))

void init_level(int level_number, Level& current_level) {
	switch (level_number) {
		case 1:
			add_object(current_level.bricks, init_object(20, 20, 40, 5, '#'));
			add_object(current_level.bricks, init_object(60, 15, 40, 10, '#'));
			add_object(current_level.bricks, init_object(100, 20, 20, 5, '#'));
			add_object(current_level.bricks, init_object(120, 15, 10, 10, '#'));
			add_object(current_level.bricks, init_object(150, 20, 40, 5, '#'));
			add_object(current_level.bricks, init_object(60, 5, 10, 3, '-'));
			add_object(current_level.bricks, init_object(75, 5, 5, 3, '-'));
			add_object(current_level.bricks, init_object(85, 5, 10, 3, '-'));
			add_object(current_level.bricks, init_object(30, 10, 5, 3, '?'));
			add_object(current_level.bricks, init_object(50, 10, 5, 3, '?'));
			add_object(current_level.bricks, init_object(70, 5, 5, 3, '?'));
			add_object(current_level.bricks, init_object(80, 5, 5, 3, '?'));
			add_object(current_level.bricks, init_object(210, 15, 10, 10, '+'));
			
			add_object(current_level.moving, init_object(25, 10, 3, 2, 'o'));
			add_object(current_level.moving, init_object(80, 10, 3, 2, 'o'));
			
			break;
			
		case 2:
			add_object(current_level.bricks, init_object(20, 20, 40, 5, '#'));
			add_object(current_level.bricks, init_object(60, 15, 10, 10, '#'));
			add_object(current_level.bricks, init_object(80, 20, 20, 5, '#'));
			add_object(current_level.bricks, init_object(120, 15, 10, 10, '#'));
			add_object(current_level.bricks, init_object(150, 20, 40, 5, '#'));
			add_object(current_level.bricks, init_object(210, 15, 10, 10, '+'));
			
			add_object(current_level.moving, init_object(25, 10, 3, 2, 'o'));
			add_object(current_level.moving, init_object(80, 10, 3, 2, 'o'));
			add_object(current_level.moving, init_object(65, 10, 3, 2, 'o'));
			add_object(current_level.moving, init_object(120, 10, 3, 2, 'o'));
			add_object(current_level.moving, init_object(160, 10, 3, 2, 'o'));
			add_object(current_level.moving, init_object(175, 10, 3, 2, 'o'));
			
			break;
			
		case 3:
			add_object(current_level.bricks, init_object(20, 20, 40, 5, '#'));
			add_object(current_level.bricks, init_object(80, 20, 15, 5, '#'));
			add_object(current_level.bricks, init_object(120, 15, 15, 10, '#'));
			add_object(current_level.bricks, init_object(160, 10, 15, 15, '+'));
			
			add_object(current_level.moving, init_object(25, 10, 3, 2, 'o'));
			add_object(current_level.moving, init_object(50, 10, 3, 2, 'o'));
			add_object(current_level.moving, init_object(80, 10, 3, 2, 'o'));
			add_object(current_level.moving, init_object(90, 10, 3, 2, 'o'));
			add_object(current_level.moving, init_object(120, 10, 3, 2, 'o'));
			add_object(current_level.moving, init_object(130, 10, 3, 2, 'o'));
			
			break;
	}
}

/*
void init_level(int level_number, Level& current_level) {
	switch (level_number) {
		case 1:
			current_level.bricks.push_back(init_object(20, 20, 40, 5, '#'));
			current_level.bricks.push_back(init_object(60, 15, 40, 10, '#'));
			current_level.bricks.push_back(init_object(100, 20, 20, 5, '#'));
			current_level.bricks.push_back(init_object(120, 15, 10, 10, '#'));
			current_level.bricks.push_back(init_object(150, 20, 40, 5, '#'));
			current_level.bricks.push_back(init_object(210, 15, 10, 10, '+'));
			
			current_level.moving.push_back(init_object(25, 10, 3, 2, 'o'));
			current_level.moving.push_back(init_object(80, 10, 3, 2, 'o'));
			
			break;
			
		case 2:
			current_level.bricks.push_back(init_object(20, 20, 40, 5, '#'));
			current_level.bricks.push_back(init_object(60, 15, 10, 10, '#'));
			current_level.bricks.push_back(init_object(80, 20, 20, 5, '#'));
			current_level.bricks.push_back(init_object(120, 15, 10, 10, '#'));
			current_level.bricks.push_back(init_object(150, 20, 40, 5, '#'));
			current_level.bricks.push_back(init_object(210, 15, 10, 10, '+'));
			
			current_level.moving.push_back(init_object(25, 10, 3, 2, 'o'));
			current_level.moving.push_back(init_object(80, 10, 3, 2, 'o'));
			current_level.moving.push_back(init_object(65, 10, 3, 2, 'o'));
			current_level.moving.push_back(init_object(120, 10, 3, 2, 'o'));
			current_level.moving.push_back(init_object(160, 10, 3, 2, 'o'));
			current_level.moving.push_back(init_object(175, 10, 3, 2, 'o'));
			
			break;
		
		case 3:
			current_level.bricks.push_back(init_object(20, 20, 40, 5, '#'));
			current_level.bricks.push_back(init_object(80, 20, 15, 5, '#'));
			current_level.bricks.push_back(init_object(120, 15, 15, 10, '#'));
			current_level.bricks.push_back(init_object(160, 10, 15, 15, '+'));
			
			current_level.moving.push_back(init_object(25, 10, 3, 2, 'o'));
			current_level.moving.push_back(init_object(50, 10, 3, 2, 'o'));
			current_level.moving.push_back(init_object(80, 10, 3, 2, 'o'));
			current_level.moving.push_back(init_object(90, 10, 3, 2, 'o'));
			current_level.moving.push_back(init_object(120, 10, 3, 2, 'o'));
			current_level.moving.push_back(init_object(130, 10, 3, 2, 'o'));
			
			break;
	}
}
*/

bool is_collision(const Object& obj1, const Object& obj2) {
	return (obj1.x + obj1.width > obj2.x && obj1.x < obj2.x + obj2.width &&
			obj1.y + obj1.height > obj2.y && obj1.y < obj2.y + obj2.height);
}

void apply_gravity(Object& obj) {
	obj.is_fly = true;
	obj.vertical_speed += 0.05;
}

void vertical_move(Object& obj) {
	obj.y += obj.vertical_speed;
}

int find_brick_collision(const std::vector<Object>& bricks, const Object& obj) {
	for (size_t i = 0; i != bricks.size(); ++i) {
		if (is_collision(obj, bricks[i])) {
			return i;
		}
	}
	return -1;
}

void resolve_vertical_collision(Object& obj, Object& brick) {
	if (obj.vertical_speed > 0) {
		obj.y = brick.y - obj.height;
		obj.is_fly = false;
	} else if (obj.vertical_speed < 0) {
		obj.y = brick.y + brick.height;
	}
	obj.vertical_speed = 0;
}

void update_vertical(GameState& game, Object& obj) {
	apply_gravity(obj);
	vertical_move(obj);
	
	int brick_index = find_brick_collision(game.current_level.bricks, obj);
	
	if (brick_index >= 0) {
		resolve_vertical_collision(obj, game.current_level.bricks[brick_index]);
	}
}

void horizontal_move_map(GameState& game, float dx) {
	game.character.x -= dx;
	
	int brick_index = find_brick_collision(game.current_level.bricks, game.character);
	if (brick_index >= 0) {
		game.character.x += dx;
		return;
	}
	game.character.x += dx;
	
	for (size_t i = 0; i != game.current_level.bricks.size(); ++i) {
		game.current_level.bricks[i].x += dx;
	}
	for (size_t i = 0; i != game.current_level.moving.size(); ++i) {
		game.current_level.moving[i].x += dx;
	}
}

void handle_input(GameState& game) {
	if (GetKeyState('A') < 0) horizontal_move_map(game, 1);
	if (GetKeyState('D') < 0) horizontal_move_map(game, -1);
	if (game.character.is_fly == false && GetKeyState(VK_SPACE) < 0) {
		game.character.vertical_speed = -1;
	}
}

void update_player(GameState& game) {
	update_vertical (game, game.character);
	if (game.character.y > MAP_HEIGHT) {
		game.character.is_alive = false;
	}
}

void update_moving(GameState& game) {
	for (size_t i = 0; i != game.current_level.moving.size(); ++i) {
		update_vertical(game, game.current_level.moving[i]);
		update_horizontal(game, game.current_level.moving[i]);
	}
}

void update(GameState& game) {
	update_player(game);
	update_moving(game);
	handle_contacts(game);
	clear_dead_objects(game.current_level.moving);
	process_events(game);
}

void render(GameState& game) {
	clear_map(game.map);
	set_cursor();
	
	put_object_on_map(game.map, game.character);
	for (size_t i = 0; i != game.current_level.bricks.size(); ++i) {
		put_object_on_map(game.map, game.current_level.bricks[i]);
	}
	for (size_t i = 0; i != game.current_level.moving.size(); ++i) {
		put_object_on_map(game.map, game.current_level.moving[i]);
		//update_vertical(game, game.current_level.moving[i]); //А зачем это надо?
	}
	
	show_map(game.map);
	Sleep(10);
}

void update_horizontal(GameState& game, Object& obj) {
	obj.x += obj.horizontal_speed;
	
	int brick_index = find_brick_collision(game.current_level.bricks, obj);
	if (brick_index >= 0) {
		obj.x -= obj.horizontal_speed;
		obj.horizontal_speed = -obj.horizontal_speed;
	}
	
	if (obj.type == 'o') {
		Object tmp = obj;
		tmp.y += 1;
		if (find_brick_collision(game.current_level.bricks, tmp) < 0) {
			obj.x -= obj.horizontal_speed;
			obj.horizontal_speed = -obj.horizontal_speed;
		}
	}
}

void handle_contacts(GameState& game) {
	for (size_t i = 0; i < game.current_level.moving.size(); ++i) {
		if (is_collision(game.character, game.current_level.moving[i])) {
			if (game.current_level.moving[i].type == 'o') {
				if (game.character.is_fly && game.character.vertical_speed > 0 &&
					game.character.y + game.character.height < 
						game.current_level.moving[i].y + 
						game.current_level.moving[i].height * 0.5) {
					game.current_level.moving[i].is_alive = false;
				} else {
					game.character.is_alive = false;
				}
			}
			//Здесь нужно будет дообавить взаимодействия с монетой
		}
	}
	
	Object tmp = game.character;
	tmp.y += 1;
	for (size_t i = 0; i < game.current_level.bricks.size(); ++i) {
		if (game.current_level.bricks[i].type == '+') {
			if (is_collision(tmp, game.current_level.bricks[i])) {
				game.level_complete = true;
			}
		}
	}
	tmp.y -= 2;
	for (size_t i = 0; i < game.current_level.bricks.size(); ++i) {
		if (game.current_level.bricks[i].type == '?') {
			if (is_collision(tmp, game.current_level.bricks[i])) {
				game.current_level.bricks[i].type = '-';
				//Добавить монету
			}
		}
	}
	//Проверка на касание блоков '?'
	//Добавить сюда проход по всем блокам, определение коллизий с + и ?
	//в случае ? блоков проверять, что персонаж снизу (character.y < brick[i].y)
	//(Всегда можно перенести это в функцию движения)
}
/*

void handle_contacts(GameState& game) {
	//переименовать функцию find_brick_collision в find_object_collision?
	int moving_index = find_brick_collision(game.current_level.moving, game.character);
	
	if (moving_index >= 0) {
		if (game.current_level.moving[moving_index].type == '$') {
			//TO DO
		}
		if (game.current_level.moving[moving_index].type == 'o') {
			if (game.character.is_fly &&
				game.character.vertical_speed > 0 &&
				game.character.y + game.character.height < 
					game.current_level.moving[moving_index].y + 
					game.current_level.moving[moving_index].height * 0.5) {
				game.current_level.moving[moving_index].is_alive = false;
			}
		}
	}
}
*/

void clear_dead_objects(std::vector<Object>& moving) {
	for (size_t i = 0; i < moving.size(); ) {
		if (!moving[i].is_alive) {
			moving[i] = moving.back();
			moving.pop_back();
		} else {
			i++;
		}
	}
}

void clear_level(Level& current_level) {
	current_level.bricks.clear();
	current_level.moving.clear();
}

void process_events(GameState& game) {
	if (!game.character.is_alive) {
		clear_level(game.current_level);
		game.character = init_object(39, 10, 3, 3, '@');
		game.character.is_alive = true; //Может быть дорабоать функцию инициализации объектов?
		init_level(game.level_number, game.current_level);
	}
	if (game.level_complete) {
		game.level_number++;
		if (game.level_number > 3) game.level_number = 1;
		clear_level(game.current_level);
		game.character = init_object(39, 10, 3, 3, '@');
		init_level(game.level_number, game.current_level);
		game.level_complete = false;
	}
}
/*



void delete_moving(std::vector<Object>& moving, int moving_index) {
	
}
*/
//void vertical_brick_contact()
/*
Понадобится функция, которая будет принимать Object и делать push_back к game.current_level.moving, чтобы добавлять
монеты; возможно стоит сделать через такую же функцию заполнение и bricks тоже, это будет так:
Передаём game (или сразу current_level (или вообще bricks)) (по ссылке?) и номер уровня в функцию, которая будет вызывать
функцию, состоящую из game.current_level.bricks.push_back(init_object(20, 20, 40, 5, '#')) нужное количество раз и 
с нужными параметрами в зависимости от уровня
А может и так оставлю
Понадобится функция, которая будет менять местами удаляемый Object с последним, после чего делать pop_back

Я придумал: нужна функция, которая принимает вектор объектов и объект (от init_object) и делает push_back; её будет
вызывать другая функция нужное количество раз с нужными параметрами 
*/

/*
Level init_level(int level) {
	if (level == 1) {
		return Level {
			{
				init_object(20, 20, 40, 5, '#'),
				init_object(60, 15, 40, 10, '#'),
				init_object(100, 20, 20, 5, '#'),
				init_object(120, 15, 10, 10, '#'),
				init_object(150, 20, 40, 5, '#'),
				init_object(210, 15, 10, 10, '+')
			}, {
				init_object(25, 10, 3, 2, 'o'),
				init_object(80, 10, 3, 2, 'o')
			}
		};
	}
	if (level == 2) {
		return Level {
			{
				init_object(20, 20, 40, 5, '#'),
				init_object(60, 15, 10, 10, '#'),
				init_object(80, 20, 20, 5, '#'),
				init_object(120, 15, 10, 10, '#'),
				init_object(150, 20, 40, 5, '#'),
				init_object(210, 15, 10, 10, '+')
			}, {
				init_object(25, 10, 3, 2, 'o'),
				init_object(80, 10, 3, 2, 'o'),
				init_object(65, 10, 3, 2, 'o'),
				init_object(120, 10, 3, 2, 'o'),
				init_object(160, 10, 3, 2, 'o'),
				init_object(175, 10, 3, 2, 'o')
			}
		};
	}
	if (level == 3) {
		return Level {
			{
				init_object(20, 20, 40, 5, '#'),
				init_object(80, 20, 15, 5, '#'),
				init_object(120, 15, 15, 10, '#'),
				init_object(160, 10, 15, 15, '+'),
				
			}, {
				init_object(25, 10, 3, 2, 'o'),
				init_object(50, 10, 3, 2, 'o'),
				init_object(80, 10, 3, 2, 'o'),
				init_object(90, 10, 3, 2, 'o'),
				init_object(120, 10, 3, 2, 'o'),
				init_object(130, 10, 3, 2, 'o')
			}
		};
	}
}
*/
