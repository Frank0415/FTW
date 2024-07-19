// Copyright (C) 2022 Zijun Yang <zijun.yang@outlook.com>
//
// This file is part of Tank War Game with CLI.
//
// Tank War Game with CLI is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Tank War Game with CLI is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Tank War Game with CLI.  If not, see <http://www.gnu.org/licenses/>.

#ifndef D006ACF8_6C3E_4ECF_B81B_8150B9BD023B
#define D006ACF8_6C3E_4ECF_B81B_8150B9BD023B
#define bltMAXSIZE 200

#define RESET "\033[0m"
#define BLACK "\033[30m"   /* Black */
#define RED "\033[31m"     /* Red */
#define GREEN "\033[32m"   /* Green */
#define YELLOW "\033[33m"  /* Yellow */
#define BLUE "\033[34m"    /* Blue */
#define MAGENTA "\033[35m" /* Magenta */
#define CYAN "\033[36m"    /* Cyan */
#define WHITE "\033[37m"   /* White */
typedef enum {
    Up,
    Right,
    Down,
    Left
} Direction;
const char icon[4] = {'A', '>', 'V', '<'};
int dx(Direction d);
int dy(Direction d);

class Player {
   public:
    int x, y;
    int life;
    int dx, dy;
    Direction dir;
    int isTurned;
    /**
     * @brief update the player's dx and dy based on act
     *
     * @param act
     */
    void turn(int act);
    /**
     * @brief move this player according to its direction
     *
     */
    void move();
    /**
     * @brief init a player
     *
     * @param x
     * @param y
     * @param life
     * @param dx
     * @param dy
     * @param dir
     * @param isTurned this variable can be used if a player cannot move after turning, but in this set of rule it's useless
     */
    void init(int x, int y, int life, int dx, int dy, Direction dir, int isTurned);
};
class Bullet {
   public:
    int x, y;
    Direction dir;
    int dx, dy;
    /**
     * @brief init a bullet
     *
     * @param x
     * @param y
     * @param dir
     * @param dx
     * @param dy
     */
    void init(int x, int y, Direction dir, int dx, int dy);
};
class Game {
   public:
    Player p[2];
    int turn;
    int bltCnt;
    Bullet blt[bltMAXSIZE];
    int canCollide;  // is it possible for the tanks to collide
    char* fileLog;
    /**
     * @brief Construct a new Game:: Game object
     *
     * @param x0 x=x0+1
     * @param y0 y=t0+1
     * @param x1 same
     * @param y1 same
     * @param dir0 direction of p0
     * @param dir1 direction of p1
     * @param life init life
     * @param logFile where to store the log file
     */
    Game(int x0, int y0, int x1, int y1, Direction dir0, Direction dir1, int life, char* logFile);
    /**
     * @brief p[0] takes act1 and p[1] takes act2, update the game by 1 turn by calling other methods in Game class
     *
     * @return 1: game continues 0: game ends
     *
     * @param act0 0: move 1/2: turn left/right
     * @param act1 same as act1
     * @param doPrint whether to print the result or not
     */
    int processOneTurn(int act1, int act2, int doPrint);
    /**
     * @brief generate the game's bullet
     *
     */
    void generateBullet();
    /**
     * @brief judge tank collision
     *
     * @return int 1: a collision happens 0: no collision
     */
    int tankTankCollision();
    /**
     * @brief move bullets according to its direction
     *
     */
    void moveBullet();
    /**
     * @brief judge whether (x,y) is in the boundary
     *
     * @param x
     * @param y
     * @return int 0 if it's out and 1 if it's in
     */
    int isIn(int x, int y);
    /**
     * @brief judge whether a bullet is too far away from the boundary
     *
     * @param x x of the bullet
     * @param y y of the bullet
     * @return int 1 if it's too far 0 if it's not
     */
    int isBulletOut(int x, int y);
    /**
     * @brief print the game
     *
     */
    void print();
    /**
     * @brief print the game in log
     *
     */
    void printLog();
    /**
     * @brief judge whether the game ends or not
     *
     * @return int 1 if end 0 if not
     */
    int gameEnd();
    /**
     * @brief print final result when game ends
     *
     */
    void showFinalResult();
    /**
     * @brief Get the Bound Min object
     *
     * @return int min boundary
     */
    int getBoundMin();
    /**
     * @brief Get the Bound Max object
     *
     * @return int max boundary
     */
    int getBoundMax();
};
#endif /* D006ACF8_6C3E_4ECF_B81B_8150B9BD023B */
