#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include "main.h"

/**
 * _printf - Custom printf function
 * @format: A pointer to a string with format specifiers
 *
 * Return: The number of characters printed (excluding the null byte).
 */

int _printf(const char *format, ...)
{
    va_list args;
    va_start(args, format);

    int chars_printed = 0;
    char c;
    char *output_buffer = NULL;
    int output_buffer_size = 0;
    int buffer_index = 0;

    while ((c = *format++))
    {
        if (c != '%')
        {
            if (buffer_index >= output_buffer_size - 1)
            {
                output_buffer_size += 1024;
                output_buffer = (char *)realloc(output_buffer, output_buffer_size);
            }
            output_buffer[buffer_index++] = c;
            chars_printed++;
        }
        else
        {
            c = *format++;
            switch (c)
            {
                case 'c':
                {
                    char ch = (char)va_arg(args, int);
                    if (buffer_index >= output_buffer_size - 1)
                    {
                        output_buffer_size += 1024;
                        output_buffer = (char *)realloc(output_buffer, output_buffer_size);
                    }
                    output_buffer[buffer_index++] = ch;
                    chars_printed++;
                    break;
                }
                case 's':
                {
                    char *str = va_arg(args, char*);
                    while (*str)
                    {
                        if (buffer_index >= output_buffer_size - 1)
                        {
                            output_buffer_size += 1024;
                            output_buffer = (char *)realloc(output_buffer, output_buffer_size);
                        }
                        output_buffer[buffer_index++] = *str++;
                        chars_printed++;
                    }
                    break;
                }
                case '%':
                {
                    if (buffer_index >= output_buffer_size - 1)
                    {
                        output_buffer_size += 1024;
                        output_buffer = (char *)realloc(output_buffer, output_buffer_size);
                    }
                    output_buffer[buffer_index++] = '%';
                    chars_printed++;
                    break;
                }
                default:
                {
                    if (buffer_index >= output_buffer_size - 2)
                    {
                        output_buffer_size += 1024;
                        output_buffer = (char *)realloc(output_buffer, output_buffer_size);
                    }
                    output_buffer[buffer_index++] = '%';
                    output_buffer[buffer_index++] = c;
                    chars_printed += 2;
                    break;
                }
            }
        }
    }

    va_end(args);

    write(STDOUT_FILENO, output_buffer, buffer_index);

    free(output_buffer);

    return chars_printed;
}

