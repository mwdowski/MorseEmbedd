#include <stdlib.h>
#include <stdio.h>
#include <gpiod.h>
#include "morse.h"
#include <time.h>

#define PRINT_ERROR(source) (perror(source), \
                             fprintf(stderr, "%s:%d\n", __FILE__, __LINE__))

#define CHIP_NAME "gpiochip0"
#define LINE_LED0 24
#define LINE_LED1 22
#define LINE_LED2 23
#define LINE_LED3 27
static const int LINES_LED_SIZE = 4;
static const unsigned int LINES_LED[] = {LINE_LED0, LINE_LED1, LINE_LED2, LINE_LED3};

#define LINE_BUTTON0 25
#define LINE_BUTTON1 10
#define LINE_BUTTON2 17
#define LINE_BUTTON3 18
#define CONSUMER "Consumer"

void set_leds_off();
int test_leds();

void sleep_in_miliseconds(int miliseconds)
{
    struct timespec timer = {miliseconds, 0};
    nanosleep(&timer, NULL);
}

int main(int argc, char **argv)
{
    test_leds();

    return EXIT_SUCCESS;
}

void set_leds_off()
{
}

int test_leds()
{
    struct gpiod_chip *chip;
    struct gpiod_line *line;

    chip = gpiod_chip_open_by_name(CHIP_NAME);
    if (!chip)
    {
        PRINT_ERROR("Open chip failed");
        goto end;
    }

    for (int i = 0; i < LINES_LED_SIZE; i++)
    {
        line = gpiod_chip_get_line(chip, LINES_LED[i]);
        if (!line)
        {
            PRINT_ERROR("Open line failed");
            goto close_chip;
        }

        if (gpiod_line_request_output(line, CONSUMER, 0) < 0)
        {
            PRINT_ERROR("Could not request line output");
            goto release_line;
        }

        if (gpiod_line_set_value(line, 1) < 0)
        {
            PRINT_ERROR("Could not set line value");
            goto release_line;
        }

        sleep_in_miliseconds(2000);

        if (gpiod_line_set_value(line, 0) < 0)
        {
            PRINT_ERROR("Could not set line value");
            goto release_line;
        }

    release_line:
        gpiod_line_release(line);
    }

close_chip:
    gpiod_chip_close(chip);
end:
    return 0;
}
