#include "main.h"
#include <unistd.h>
#include <stdarg.h>

int _printf(const char *format, ...);

/**
 * _printf - Produces output according to a format.
 * @format: Input value format string
 * Return: Number of characters printed
 */
int _printf(const char *format, ...)
{
	int printed_chars = 0;
	va_list args;

	va_start(args, format);

	while (*format != '\0')
	{
		if (*format == '%')
		{
			format++;

			if (*format == '\0')
				break;

			if (*format == 'c')
			{
				char c = (char)va_arg(args, int);

				write(1, &c, 1);
				printed_chars++;
			}

				else if (*format == 's')
				{
					char *str = va_arg(args, char *);
					int len = 0;

					while (str[len] != '\0')
						len++;

					write(1, str, len);
					printed_chars += len;
				}

				else if (*format == '%')
				{
					char percent = '%';

					write(1, &percent, 1);
					printed_chars++;
				}

				else
				{
					write(1, format - 1, 1);
					printed_chars++;
				}
			}

			else
			{
				write(1, format, 1);
				printed_chars++;
			}

			format++;
		}

		va_end(args);
		return (printed_chars);
}

int main(void)
{
	int num = 42;
	char str[] = "Printing the Output!";

	_printf("Integer: %d, String: %s, Character: %c, Percent: %%\n",
			num, str, 'X');
	return (0);
}
