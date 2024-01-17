# GLIBC Gobject Example

This is an example of how to implement a glib object that parses a small json file.


# How to build and run
gcc my_example.c -Wall -o example `pkg-config --cflags --libs glib-2.0 gobject-2.0 json-glib-1.0`
./example
