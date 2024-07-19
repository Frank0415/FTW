# Tank War

A simple tank war game with CLI that supports PVP, PVE and DEMO.

## Compile the program

To compile it, you need to install:

- `g++`, a cpp compiler. Remember to add it to PATH if you are using Windows.
- `CMake`, a build process manager.
- `GNU Make`, a tool which controls the generation of executables and other non-source files of a program from the program's source files.

or you can use IDEs such as `CLion`.

### The recommended way

The recommended way of compiling it (also the way I compile it) is with the help of a plug-in in `VSCode` called `CMake Tools`.

If you open the project folder in `VSCode` and you have successfully install `g++`, `CMake` and `CMake Tools`, you can find a `build` button in the bottom bar. By clicking it, the executable will be compiled under `./build/tankwar.exe`.

### Other ways

You may refer to [docs for CMake command line](https://cmake.org/cmake/help/latest/manual/cmake.1.html) to checkout how to compile it with command line (it should be `cmake -b build`, `cd build` and `make`, I believe).

Or, you may refer to [docs for CMake in CLion](https://www.jetbrains.com/help/clion/quick-cmake-tutorial.html) to checkout how to compile it in `CLion`.

## Run the program

This is a command line game so you can run it in terminal.

I'll take how it can be run in `Linux Mint` as an example.

After generate the executable `tankwar`, type `./tankwar` in the terminal to enter the default mode which is PVP and has the default life of 5 and default log file `tankwar.log`.

You can type `./tankwar -h` to check the help page of the game and learn how to have access to other mode and how to change the life and log file.

The game-play instruction is built into the game itself and you can see it during the game.

The game's interface has colored texts so you need to run it in a supported terminal. In Windows, for example, you need to run it in `Windows Terminal` or the terminal in `VSCode`.

## Layer of the program

The program consists of 5 layers listed from low level to high level:

- `Object` layer. It includes every player, bullet and the whole game. It is responsible for some basic tasks like moving a tank or a bullet or judge collision. This part of the program is primarily in `gameProcess.cpp`.
- `Game processing` layer. It includes the logic of the game. By utilizing the `object` layer, it is responsible for how the game goes on, such as processing one turn and printing the result. This part of the program is primarily in `gameProcess.cpp`.
- `Input` layer. The `game processing` layer needs input actions to process one turn, and to the `game processing` layer, human input and AI input are of no difference. The `input` layer gathers input actions from human and/or AI based on game mode and passes the information to the `game processing` layer. This part of the program is primarily in `gameControl.cpp`.
- `AI` layer. This layer takes in a game status and returns the best action for a particular player. This part of the program is primarily in `tankai.cpp`.
- `Global control` layer. This layer handles the command line arguments and organizes the whole program. This part of the program is primarily in `gameControl.cpp` and `tankwar.cpp`.

## Objects

Three objects are defined in the game's program.

### `Bullet`

It contains all the information of one bullet, including its coordinates and direction.

The method `init` is used to initialize a bullet.

You can find its declaration in `gameProcess.h`.

### `Player`

It contains all the information of one player, including its coordinates, direction and life.

The method:

`turn` is used to turn the player in place;

`move` is used to move the player straight forward;

`init` is used to initialize the playher.

You can find its declaration in `gameProcess.h`.

### `Game`

It contains all the information of a game status, including two players and all the bullets.

The number of methods of this class is too large, but you can check out comments in `gameProcess.h` to see what each method do.

You can find the declaration of `Game` in `gameProcess.h`.

## I/O format

The I/O format of this tank war game has three features to improve user experience.

![Screenshot of the game](https://s1.ax1x.com/2022/08/06/vnL8YT.png)

1. The map is colored. Players are painted with red and cyan and the boundary is painted yellow. This greatly reduces the difficulty of recognizing the location of the tanks and the boundary.
2. The directions of the bullets and tanks are presented by arrows. This is also a great improvement in user experience because now the directions are clearly shown.
3. All kinds of inputs in the game (except command line argument) are considered, i.e. if the input is not valid, the program won't crash. Instead, it will provide you with a notification and let you input again. I am fully aware the pain when you are about to win but crash the game just because you accidentally type `-` instead of `0`.

## AI

The strategy of the AI is quite conservative for it assume its opponent is cleaver enough.

Every turn, AI can take one action and so does its opponent. The AI will take the action that the minimal `scores` when its opponent takes one action is the highest.

`score` is measured by a quite complex algorithm involving searching tree. It evaluates whether an action will lead to the end of the game, cause damage and result in a either good or bad situation.

Also, it's often boring to see two tanks with the same life collide with each other resulting in a draw. So I also add some deduction in score for this kind of behavior. But the AI won't stay away from its component because of another evaluation standard that rewards aggressive behavior.

The overall result that I can never win it shows that the AI is quite powerful.
