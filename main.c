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
static const int LINES_SIZE = 4;
static const unsigned int LINES_LED[] = {LINE_LED0, LINE_LED1, LINE_LED2, LINE_LED3};

#define LINE_BUTTON0 25
#define LINE_BUTTON1 10
#define LINE_BUTTON2 17
#define LINE_BUTTON3 18
static const unsigned int LINES_BUTTONS[] = {LINE_BUTTON0, LINE_BUTTON1, LINE_BUTTON2, LINE_BUTTON3};
#define CONSUMER "Consumer2137"

void set_leds_off();
int test_leds();
void await_buttons(struct gpiod_chip *chip);

void sleep_in_miliseconds(int miliseconds)
{
    struct timespec timer = {0, miliseconds * 1000000};
    nanosleep(&timer, NULL);
}

int main(int argc, char **argv)
{
    struct gpiod_chip *chip = NULL;
    chip = gpiod_chip_open_by_name(CHIP_NAME);
    if (!chip)
    {
        PRINT_ERROR("Open chip failed");
        goto end;
    }

    await_buttons(chip);

close_chip:
    gpiod_chip_close(chip);
    chip = NULL;
end:
    return EXIT_SUCCESS;
}

void await_buttons(struct gpiod_chip *chip)
{
    struct gpiod_line_bulk line_bulk;
    gpiod_line_bulk_init(&line_bulk);

    for (int i = 0; i < LINES_SIZE; i++)
    {
        struct gpiod_line *line = NULL;
        line = gpiod_chip_get_line(chip, LINES_BUTTONS[i]);
        if (!line)
        {
            PRINT_ERROR("Open line failed");
            continue;
        }

        if (gpiod_line_request_falling_edge_events(line, CONSUMER) < 0)
        {
            PRINT_ERROR("Could not request line input");
            continue;
        }

        /*
        if (gpiod_line_request_input(line, CONSUMER) < 0)
        {
            PRINT_ERROR("Could not request line input");
            continue;
        }
        */

        gpiod_line_bulk_add(&line_bulk, line);
    }

    struct timespec timer = {3600, 0};
    struct gpiod_line_bulk event_bulk;
    gpiod_line_bulk_init(&event_bulk);

    morse_decoding_tree_node *cur = &morse_root;

    while (gpiod_line_event_wait_bulk(&line_bulk, &timer, &event_bulk) == 1)
    {
        int curline;
        for (int i = 0; i < event_bulk.num_lines && event_bulk.lines[i] != NULL; i++)
        {
            struct gpiod_line_event event;
            if (gpiod_line_event_read(event_bulk.lines[i], &event) < 0)
            {
                PRINT_ERROR("err");
            }
            else
            {
                curline = i;
                /*
                
                */
            }
        }
        
        // debouncing
        struct timespec timer_cl = {0, 100L * 1000000L};
        struct gpiod_line_bulk event_bulk_cl;
        while (gpiod_line_event_wait_bulk(&line_bulk, &timer_cl, &event_bulk_cl) == 1)
        {
            for (int i = 0; i < event_bulk_cl.num_lines && event_bulk_cl.lines[i] != NULL; i++)
            {
                struct gpiod_line_event event;
                if (gpiod_line_event_read(event_bulk_cl.lines[i], &event) < 0)
                {
                    PRINT_ERROR("err");
                }
                else
                {
                    printf("Ignored bouncing\n");
                }
            }
        }

        if (gpiod_line_get_value(event_bulk.lines[curline]) == 0)
        {
            if (cur == NULL)
            {
                printf("Unrecognized symbol\n");
                test_leds(chip);
                cur = &morse_root;
            }
            else
            {
                switch (gpiod_line_offset(event_bulk.lines[curline]))
                {
                    case LINE_BUTTON0:
                        printf("Short\n");
                        cur = cur->short_child;
                        break;
                    case LINE_BUTTON1:
                        printf("Long\n");
                        cur = cur->long_child;
                        break;
                    case LINE_BUTTON2:
                        printf("%c\n", cur->letter);
                        cur = &morse_root;
                        break;
                    case LINE_BUTTON3:
                        cur = &morse_root;
                        printf("Word break\n");
                        break;
                }
            }
        }

        gpiod_line_bulk_init(&event_bulk);
    }
}

int test_leds(struct gpiod_chip *chip)
{
    struct gpiod_line *line = NULL;

    for (int i = 0; i < LINES_SIZE; i++)
    {
        line = gpiod_chip_get_line(chip, LINES_LED[i]);
        if (!line)
        {
            PRINT_ERROR("Open line failed");
            continue;
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

        sleep_in_miliseconds(1);

        if (gpiod_line_set_value(line, 0) < 0)
        {
            PRINT_ERROR("Could not set line value");
            goto release_line;
        }

    release_line:
        gpiod_line_release(line);
        line = NULL;
    }

    return 0;
}
