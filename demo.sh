gcc decoder.c -o decoder
gcc openimage.c `sdl2-config --cflags --libs` -o openimage
./decoder && ./openimage
