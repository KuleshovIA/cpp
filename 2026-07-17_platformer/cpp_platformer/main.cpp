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
	bool is_fly = true;
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
	int score = 0;
};


void add_object(std::vector<Object>& recipient, const Object& obj);
void apply_gravity(Object& obj);
void bricks_contacts(GameState& game);
void clear_dead_objects(std::vector<Object>& moving);
void clear_level(Level& current_level);
void clear_map(char (&map)[][MAP_WIDTH + 1]);
int find_brick_collision(const std::vector<Object>& bricks, const Object& obj);
void handle_contacts(GameState& game);
void handle_input(GameState& game);
void horizontal_move_map(GameState& game, float dx);
void init_level(int level_number, Level& current_level);
Object init_object(float x_pos, float y_pos, float o_width, float o_height, char in_type,
				   float vertical_speed = 0, float horizontal_speed = 0.2);
bool is_collision(const Object& obj1, const Object& obj2);
bool is_pos_in_map(int x, int y);
void moving_contacts(GameState& game);
void process_events(GameState& game);
void put_object_on_map(char(&map)[][MAP_WIDTH + 1], const Object& obj);
void put_score_on_map(char(&map)[][MAP_WIDTH + 1], int score);
void render(GameState& game);
void resolve_vertical_collision(Object& obj, const Object& brick);
void set_cursor(int x = 0, int y = 0);
void show_map(const char(&map)[][MAP_WIDTH + 1]);
void spawn_coin(std::vector<Object>& moving, const Object& brick);
void update(GameState& game);
void update_horizontal(const GameState& game, Object& obj);
void update_moving(GameState& game);
void update_player(GameState& game);
void update_vertical(const GameState& game, Object& obj);
void vertical_move(Object& obj);



int main() {
	GameState game;
	game.character = init_object(39, 10, 3, 3, '@');
	init_level(game.level_number, game.current_level);
	system("color 9F");
	do {
		handle_input(game);
		update(game);
		render(game);
	} while (GetKeyState(VK_ESCAPE) >= 0);
	
	return 0;
}



void add_object(std::vector<Object>& recipient, const Object& obj) {
	recipient.push_back(obj);
}

void apply_gravity(Object& obj) {
	obj.is_fly = true;
	obj.vertical_speed += 0.05;
}

void bricks_contacts(GameState& game) {
	Object tmp = game.character;
	tmp.y -= 1;
	tmp.height += 2;
	for (size_t i = 0; i < game.current_level.bricks.size(); ++i) {
		if (game.current_level.bricks[i].type == '+') {
			if (is_collision(tmp, game.current_level.bricks[i])) {
				game.level_complete = true;
			}
		}
		if (game.current_level.bricks[i].type == '?') {
			if (is_collision(tmp, game.current_level.bricks[i]) &&
				game.character.y > game.current_level.bricks[i].y) {
				game.current_level.bricks[i].type = '-';
				spawn_coin(game.current_level.moving, game.current_level.bricks[i]);
			}
		}
	}
} 

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

void clear_map(char(&map)[][MAP_WIDTH + 1]) {
	for (int i = 0; i < MAP_WIDTH; i++) {
		map[0][i] = ' ';
	}
	map[0][MAP_WIDTH] = '\0';
	for (int j = 1; j < MAP_HEIGHT; j++) {
		sprintf(map[j], map[0]);
	}
}

int find_brick_collision(const std::vector<Object>& bricks, const Object& obj) {
	for (size_t i = 0; i != bricks.size(); ++i) {
		if (is_collision(obj, bricks[i])) {
			return i;
		}
	}
	return -1;
}

void handle_contacts(GameState& game) {
	moving_contacts(game);
	bricks_contacts(game);
}

void handle_input(GameState& game) {
	if (GetKeyState('A') < 0) horizontal_move_map(game, 1);
	if (GetKeyState('D') < 0) horizontal_move_map(game, -1);
	if (game.character.is_fly == false && GetKeyState(VK_SPACE) < 0) {
		game.character.vertical_speed = -1;
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

Object init_object(float x_pos, float y_pos, float o_width, float o_height, char in_type, 
				   float vertical_speed, float horizontal_speed) {
	return Object {x_pos, y_pos, o_width, o_height, in_type, horizontal_speed, vertical_speed};
}

bool is_collision(const Object& obj1, const Object& obj2) {
	return (obj1.x + obj1.width > obj2.x && obj1.x < obj2.x + obj2.width &&
			obj1.y + obj1.height > obj2.y && obj1.y < obj2.y + obj2.height);
}

bool is_pos_in_map(int x, int y) {
	return (x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT);
}

void moving_contacts(GameState& game) {
	for (size_t i = 0; i < game.current_level.moving.size(); ++i) {
		if (is_collision(game.character, game.current_level.moving[i])) {
			if (game.current_level.moving[i].type == 'o') {
				if (game.character.is_fly && game.character.vertical_speed > 0 &&
					game.character.y + game.character.height < 
					game.current_level.moving[i].y + game.current_level.moving[i].height * 0.5) {
						game.current_level.moving[i].is_alive = false;
						game.score += 50;
				} else {
					game.character.is_alive = false;
				}
			}
			if (game.current_level.moving[i].type == '$') {
				game.current_level.moving[i].is_alive = false;
				game.score += 100;
			}
		}
	}
}

void process_events(GameState& game) {
	if (!game.character.is_alive) {
		clear_level(game.current_level);
		game.character = init_object(39, 10, 3, 3, '@');
		game.character.is_alive = true;
		init_level(game.level_number, game.current_level);
		system("color 4F");
		Sleep(500);
		system("color 9F");
	}
	if (game.level_complete) {
		game.level_number++;
		if (game.level_number > 3) game.level_number = 1;
		clear_level(game.current_level);
		game.character = init_object(39, 10, 3, 3, '@');
		init_level(game.level_number, game.current_level);
		game.score = 0;
		game.level_complete = false;
		system("color 2F");
		Sleep(500);
		system("color 9F");
	}
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

void put_score_on_map(char(&map)[][MAP_WIDTH + 1], int score) {
	char c[15];
	sprintf (c, "Score: %d", score);
	int len = strlen(c);
	for (int i = 0; i < len; i++) {
		map[1][i + 5] = c[i];
	}
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
	}
	put_score_on_map(game.map, game.score);
	
	show_map(game.map);
	Sleep(10);
}

void resolve_vertical_collision(Object& obj, const Object& brick) {
	if (obj.vertical_speed > 0) {
		obj.y = brick.y - obj.height;
		obj.is_fly = false;
	} else if (obj.vertical_speed < 0) {
		obj.y = brick.y + brick.height;
	}
	obj.vertical_speed = 0;
}

void set_cursor(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void show_map(const char(&map)[][MAP_WIDTH + 1]) {
	for (int j = 0; j < MAP_HEIGHT; j++) {
		printf("%s", map[j]);
	}
}

void spawn_coin(std::vector<Object>& moving, const Object& brick) {
	add_object(moving, init_object(brick.x, brick.y - 3, 3, 2, '$', -0.7));
}

void update(GameState& game) {
	update_player(game);
	update_moving(game);
	handle_contacts(game);
	clear_dead_objects(game.current_level.moving);
	process_events(game);
}

void update_horizontal(const GameState& game, Object& obj) {
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

void update_moving(GameState& game) {
	for (size_t i = 0; i != game.current_level.moving.size(); ++i) {
		update_vertical(game, game.current_level.moving[i]);
		update_horizontal(game, game.current_level.moving[i]);
	}
}

void update_player(GameState& game) {
	update_vertical (game, game.character);
	if (game.character.y > MAP_HEIGHT) {
		game.character.is_alive = false;
	}
}

void update_vertical(const GameState& game, Object& obj) {
	apply_gravity(obj);
	vertical_move(obj);
	
	int brick_index = find_brick_collision(game.current_level.bricks, obj);
	
	if (brick_index >= 0) {
		resolve_vertical_collision(obj, game.current_level.bricks[brick_index]);
	}
}

void vertical_move(Object& obj) {
	obj.y += obj.vertical_speed;
}
