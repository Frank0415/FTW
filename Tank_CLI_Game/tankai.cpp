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

#include "tankai.h"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "gameProcess.h"

int idiotAct(Game game, int me, int depth, int lifeMe, int lifeYou) {
    // srand(time(NULL));
    // if (rand() % 7 != 0) {
    //     return bestAct(game, me, depth, lifeMe, lifeYou);
    // } else {
    //     return rand() % 3;
    // }
    return bestAct(game, me, depth, lifeMe, lifeYou);
}

int bestAct(Game game, int me, int depth, int lifeMe, int lifeYou) {
    double bestRes = -99999999;
    int res = 0;
    for (int i = 0; i <= 2; i++) {
        double eval = evaluateAct(game, me, i, depth, lifeMe, lifeYou);
        if (eval > bestRes || ((abs(eval - bestRes) < 0.00001) && rand() % 3 == 0)) {
            bestRes = eval;
            res = i;
        }
    }
    return res;
}

// =================== standard for evaluation ====================
// lose game: 100000
// hurt: 1000/blood
// risk: <50

double evaluateAct(Game game, int me, int act, int depth, int lifeMe, int lifeYou) {
    double res = 99999999;
    int you = 1 - me;
    if (game.gameEnd() || depth == 0) {
        res = 0;
        Player pMe = game.p[me], pYou = game.p[you];

        if (game.gameEnd()) {
            if (pMe.life > 0) {
                res = 1000000;
            } else if (pYou.life > 0) {
                res = -1000000;
            } else {
                res = -100;
            }
            return res;
        }

        res -= 2000 * ((lifeMe - pMe.life) - (lifeYou - pYou.life));

        return res + evaluatePlayer(game, me) - evaluatePlayer(game, you) + 0.2 * evaluateAggressiveness(game, me);

    } else {
        for (int i = 0; i <= 2; i++) {
            Game tempGame = game;
            double tempRes = -99999999;
            if (me == 0) {
                tempGame.processOneTurn(act, i, 0);
            } else {
                tempGame.processOneTurn(i, act, 0);
            }
            for (int j = 0; j <= 2; j++) {
                double eval = evaluateAct(tempGame, me, j, depth - 1, lifeMe, lifeYou);
                tempRes = tempRes < eval ? eval : tempRes;  // I want myself to act best
            }
            res = tempRes < res ? tempRes : res;  // opponent wants me to act worse
        }
    }
    return res;
}

double evaluatePlayer(Game game, int me) {
    int you = 1 - me;

    double res = 0;
    res -= 1 * (bulletHit(game, me) - bulletHit(game, you));
    res -= 1 * (boundaryPenalty(game, me) - boundaryPenalty(game, you));
    if (game.canCollide) {
        res -= 0.5 * (crashPenalty(game, me) - crashPenalty(game, you));
    }
    return res;
}

double bulletHit(Game game, int me) {
    double res = 0;
    Player p = game.p[me];
    for (int i = 1; i <= game.bltCnt; i++) {
        int possibleHitStep = 0, possibleHit = 0;
        Bullet b = game.blt[i];
        while (!game.isBulletOut(b.x, b.y)) {
            possibleHitStep++;
            if (abs(b.x - p.x) + abs(b.y - p.y) <= possibleHitStep) {
                possibleHit = 1;
                break;
            }
            b.x += 1 * b.dx;
            b.y += 1 * b.dy;
            if (abs(b.x - p.x) + abs(b.y - p.y) <= possibleHitStep) {
                possibleHit = 1;
                break;
            }
            b.x += 1 * b.dx;
            b.y += 1 * b.dy;
            if (abs(b.x - p.x) + abs(b.y - p.y) <= possibleHitStep) {
                possibleHit = 1;
                break;
            }
        }
        res += possibleHit * (20 - possibleHitStep);
    }
    return res;
}

double boundaryPenalty(Game game, int me) {
    Player pMe = game.p[me];
    double res = 0;
    if (game.getBoundMin() > game.getBoundMax()) {
        return 0;
    }
    if (!game.isIn(pMe.x, pMe.y)) {
        res += (pMe.x < game.getBoundMin()) ? game.getBoundMin() - pMe.x : 0;
        res += (pMe.y < game.getBoundMin()) ? game.getBoundMin() - pMe.y : 0;
        res += (pMe.x > game.getBoundMax()) ? pMe.x - game.getBoundMax() : 0;
        res += (pMe.y > game.getBoundMax()) ? pMe.y - game.getBoundMax() : 0;
        return 1000 * res;
    }
    int sensitivity = 4;
    res += (pMe.x < game.getBoundMin() + sensitivity) ? game.getBoundMin() + sensitivity - pMe.x : 0;
    res += (pMe.y < game.getBoundMin() + sensitivity) ? game.getBoundMin() + sensitivity - pMe.y : 0;
    res += (pMe.x > game.getBoundMax() - sensitivity) ? pMe.x + sensitivity - game.getBoundMax() : 0;
    res += (pMe.y > game.getBoundMax() - sensitivity) ? pMe.y + sensitivity - game.getBoundMax() : 0;
    return 5 * res;
}

double crashPenalty(Game game, int me) {
    int you = 1 - me;
    Player pMe = game.p[me], pYou = game.p[you];
    double factor = 3;
    if (pMe.life < pYou.life) {
        factor = 1;
    } else if (pMe.life > pYou.life) {
        factor = -1;
    }
    if (abs(pMe.x - pYou.x) + abs(pMe.y - pYou.y) <= 4) {
        return factor * (4 - (abs(pMe.x - pYou.x) + abs(pMe.y - pYou.y)));
    }
    return 0;
}

double evaluateAggressiveness(Game game, int me) {
    Player pMe = game.p[me], pYou = game.p[1 - me];
    double res = abs(pMe.x - pYou.x) + abs(pMe.y - pYou.y);
    // res==3/4: best return 35
    return res < 4 ? res * 2 + 36 - 4 * 2 : 39 - res;
}
