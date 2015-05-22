// from http://www.erlang.org/doc/tutorial/c_port.html#id57564
#include <stdlib.h>

typedef unsigned char byte;

int read_exact(byte *buf, int len);

int write_exact(byte *buf, int len);

int read_cmd(byte *buf);

int write_cmd(byte *buf, int len);

int input_available();

void get_str_arg(byte *buf, char *arg, int bytes_read);

int get_int_arg(byte *buf, int bytes_read);

