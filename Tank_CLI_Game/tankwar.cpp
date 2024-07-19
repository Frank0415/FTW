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

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include "gameControl.h"
#include "gameProcess.h"
#include "tankai.h"

int optionMatch(char* s, char option[]);
char* getArg(char* s);

int main(int argc, char* argv[]) {
    srand(time(NULL));
    if (argc == 2) {
        if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
            puts("  -h|--help print this help message");
            puts("  --log-file filename write the logs in filename (default: tankwar.log)");
            puts("  -m m|--mode=m play tank war in m (PVP/PVE/DEMO) mode (default: PVP)");
            puts("  -p p|--initial-life=p each tank has p life points initially, p >= 1 (default: 5)");
            return 0;
        }
    }
    int life = 5;
    Mode mode = PvP;
    int i = 1;
    char logFile[100] = "tankwar.log";
    char modeOption[] = "--mode=", lifeOption[] = "--initial-life=";
    while (i <= argc - 1) {
        char *s = argv[i], *arg = NULL;
        if (i + 1 <= argc - 1) {
            arg = argv[i + 1];
            // printf("%s|%s\n", s, arg);
        }
        if (strcmp(s, "-m") == 0) {
            mode = PvP;
            if (strcmp(arg, "DEMO") == 0) {
                mode = Demo;
            }
            if (strcmp(arg, "PVE") == 0) {
                mode = PvE;
            }
            i += 2;
        } else if (strcmp(s, "-p") == 0) {
            life = atoi(arg);
            i += 2;
        } else if (strcmp(s, "--log-file") == 0) {
            strcpy(logFile, arg);
            i += 2;
        } else if (optionMatch(s, modeOption)) {
            char* arg = getArg(s);
            mode = PvP;
            if (strcmp(arg, "DEMO") == 0) {
                mode = Demo;
            }
            if (strcmp(arg, "PVE") == 0) {
                mode = PvE;
            }
            i++;
        } else if (optionMatch(s, lifeOption)) {
            char* arg = getArg(s);
            life = atoi(arg);
            i++;
        }
    }
    mainLoop(mode, life, logFile);
    return 0;
}

/**
 * @brief judge whether s starts with option
 *
 * @param s
 * @param option
 * @return int
 */
int optionMatch(char* s, char* option) {
    int lenO = strlen(option), lenS = strlen(s);
    if (lenO >= lenS) {
        return 0;
    }
    for (int i = 0; i <= lenO - 1; i++) {
        if (s[i] != option[i]) {
            return 0;
        }
    }
    return 1;
}

/**
 * @brief return a pointer points to the argument part in s
 *
 * @param s
 * @return char*
 */
char* getArg(char* s) {
    int i = strlen(s);
    while (s[i - 1] != '=') {
        i--;
    }
    return &(s[i]);
}
