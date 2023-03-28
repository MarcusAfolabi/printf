#include <stdio.h>
#include <stdarg.h>

int _printf(const char *format, ...)
{
    va_list args;
    int count = 0;
    char c;

    va_start(args, format);

    while ((c = *format++) != '\0')
    {
        if (c != '%') // normal character
        {
            putchar(c);
            count++;
            continue;
        }

        // handle the conversion specifier
        switch (*format++)
        {
            case 'c': // character
                putchar(va_arg(args, int));
                count++;
                break;

            case 's': // string
            {
                const char *s = va_arg(args, const char *);
                while (*s != '\0')
                {
                    putchar(*s++);
                    count++;
                }
                break;
            }

            case '%': // percent sign
                putchar('%');
                count++;
                break;

            case 'd': // decimal integer
            case 'i': // integer
            {
                int n = va_arg(args, int);
                if (n < 0)
                {
                    putchar('-');
                    count++;
                    n = -n;
                }
                int digit_count = 1;
                int tmp = n;
                while ((tmp /= 10) != 0)
                {
                    digit_count++;
                }
                while (digit_count-- > 0)
                {
                    putchar('0' + n / pow(10, digit_count));
                    count++;
                    n %= (int) pow(10, digit_count);
                }
                break;
            }

            default: // invalid format specifier
                return -1;
        }
    }

    va_end(args);

    return count;
}

