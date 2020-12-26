# JayMatrix
*Custom ncurses implementation of the cmatrix program, in C*  

## Building
A CMakeLists.txt file is given for easy-building. Just use ``cmake`` together with ``make`` and you'll be on your way in no time! Alternatively, here's a single command to just build everything from scratch:  
```sh
gcc -o matrix -lncurses default.c main.c coordinates.c
```

## Running
JayMatrix supports some CLI arguments, to make the matrix experience as great as possible!  

Argument | Options | Effect | Default  
--- | --- | --- | ---  
``--fps`` (``-f``) | any positive integer | sets the renderer's fps | ``24``  
``--color`` (``-c``) | OFF, SINGLE, RAINBOW | uses no colors (OFF), green-on-black (SINGLE) or random colors (RAINBOW) | ``SINGLE``  
``--exit`` (``-e``) | multiple possible keys | sets the exit keybinding | ``q``  
``--help`` (``-h``) | - | Shows the help & exits | -  

In short, the command ``./matrix`` is equivalent to either of the following:  
```sh
./matrix --fps 24 --color SINGLE --exit q
./matrix -f 24 -c SINGLE -e q
```

The key options are:
 - any letter  
 - any number  
 - space  
 - return  
 - tab  
 - FKEY``number``: binds to F``number`` (e.g: FKEY4 binds to F4)
