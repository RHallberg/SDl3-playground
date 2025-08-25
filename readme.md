
Playing around with SDL3.

To compile and run:

```bash
 # On Linux
 gcc menu.c -o menu $(pkg-config --cflags --libs sdl3) && ./menu
 # On OSX 
 clang menu.c -I/usr/local/include/SDL3 -L/usr/local/lib -lSDL3 -Wl,-rpath,/usr/local/lib -o menu
```

To quit, press 'q' or just kill the program.
