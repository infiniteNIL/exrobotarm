// from http://www.erlang.org/doc/tutorial/c_port.html#id57564
#include "erl_comm.h"
#include <stdlib.h>
#include <fcntl.h>
#include <sys/select.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int read_exact(byte *buf, int len)
{
    int got = 0;

    do {
        int i = read(0, buf + got, len - got);
        if (i <= 0) {
            return i;
        }
        got += i;
    }
    while (got < len);

    return len;
}

int write_exact(byte *buf, int len)
{
  int i, wrote = 0;

  do {
    if ((i = write(1, buf+wrote, len-wrote)) <= 0)
      return (i);
    wrote += i;
  } while (wrote<len);

  return (len);
}

int read_cmd(byte *buf)
{
    if (read_exact(buf, 2) != 2) {
        return -1;
    }

    int len = (buf[0] << 8) | buf[1];
    return read_exact(buf, len);
}

int write_cmd(byte *buf, int len)
{
  byte li;

  li = (len >> 8) & 0xff;
  write_exact(&li, 1);

  li = len & 0xff;
  write_exact(&li, 1);

  return write_exact(buf, len);
}

int input_available()
{
    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 500;

    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);
    return FD_ISSET(0, &fds);
}

void get_str_arg(byte *buf, char *arg, int bytes_read) {
  buf[bytes_read] = '\0';
  strcpy(arg, (char *) &buf[1]);
}

int get_int_arg(byte *buf, int bytes_read) {
  char tmp[1024];
  get_str_arg(buf, tmp, bytes_read);
  return atoi(tmp);
}

