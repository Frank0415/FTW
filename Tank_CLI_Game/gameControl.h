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

#ifndef A2AD3DBA_1A39_4DA7_98E8_082561A0C1AA
#define A2AD3DBA_1A39_4DA7_98E8_082561A0C1AA
typedef enum {
    PvP,
    PvE,
    Demo
} Mode;
/**
 * @brief judge whether the two actions are valid
 *
 * @param f0
 * @param f1
 * @return int
 */
int isValidDirection(int f0, int f1);
/**
 * @brief judge whether an act is valid
 *
 * @param act
 * @return int
 */
int isValidAct(int act);
/**
 * @brief judge whether the user inputs too many command
 *
 * @return int
 */
int somethingLeft();
/**
 * @brief judge whether (x,y) is in the initial board
 *
 * @param x
 * @param y
 * @return int
 */
int isIn20(int x, int y);
/**
 * @brief handle the game's loop
 *
 * @param mode what mode is it
 * @param life init life
 * @param logFile where to store the log file
 */
void mainLoop(Mode mode, int life, char* logFile);
void pvp();
void pve();
/**
 * @brief this is the demo mode
 *
 */
void eVIdiot();
#endif /* A2AD3DBA_1A39_4DA7_98E8_082561A0C1AA */
