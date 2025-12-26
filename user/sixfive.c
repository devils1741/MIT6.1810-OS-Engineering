#include "kernel/fcntl.h"
#include "kernel/types.h"
#include "user/user.h"

int char_to_int(const char *c)
{
    int res = 0;
    for (int i = 0;; ++i)
    {
        if (c[i] >= '0' && c[i] <= '9')
        {
            res = res * 10 + (c[i] - '0');
        }
        else if (c[i] == '\0')
        {
            return res;
        }
        else
        {
            return -1;
        }
    }
    return -1;
}

int read_line(char *buf, int fd, int max_char)
{
    char c;
    int i = 0;
    int read_char;
    for (; i < max_char;)
    {
        read_char = read(fd, &c, 1);
        if (read_char <= 0)
        {
            break;
        }
        if (c == '\n' || c == '\0')
        {
            break;
        }
        else
        {
            buf[i] = c;
            ++i;
        }
    }
    buf[++i] = '\0';
    return --i;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(2, "Support and only support one file\n");
        exit(1);
    }
    int fd = open(argv[1], O_RDONLY);
    if (fd < 0)
    {
        fprintf(2, "open file failed!\n");
        exit(2);
    }
    char buf[128];
    int cc = 0;
    int temp = 0;
    for (;;)
    {
        memset(buf, 0, sizeof(buf));
        cc = read_line(buf, fd, 127);
        // printf("read %d char, buf=%s \n", cc, buf);
        if (cc <= 0)
        {
            break;
        }
        else
        {
            temp = char_to_int(buf);
            // printf("%d\n", temp);
            if (temp != -1 && (temp % 5 == 0 || temp % 6 == 0))
            {
                printf("%d\n", temp);
            }
        }
    }
    exit(0);
}
