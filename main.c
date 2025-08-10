#define _GNU_SOURCE
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

int main()
{
    // stdin => buffer => lines
    char* buffer = NULL;
    size_t length = 0;
    size_t line_count = 0;
    ssize_t read_bytes;
    ssize_t lines_bytes = 0;
    char** lines = NULL;
    while ((read_bytes = getline(&buffer, &length, stdin)) != -1)
    {
        if (buffer[read_bytes - 1] == '\n') {
            buffer[read_bytes - 1] = '\0';
            char* line = malloc(sizeof(*line) * read_bytes);
            // buffer => line
            line = strdup(buffer);
            lines_bytes = lines_bytes + read_bytes;
            lines = realloc(lines, lines_bytes);
            lines[line_count] = line;
            line_count++;
        }
    }
    if (line_count == 0)
    {
        fprintf(stderr, "No input\n");
        return EXIT_SUCCESS;
    }
    free(buffer);

    // tui
    fclose(stdin);
    FILE* tty = fopen("/dev/tty", "r+");
    if (tty == NULL)
    {
        perror("Failed to fopen /dev/tty");
        return EXIT_FAILURE;
    }
    SCREEN* screen = newterm(NULL, tty, tty);
    set_term(screen);

    cbreak();
    noecho();
    // support special keys
    keypad(stdscr, TRUE);
    curs_set(0);

    int top_line_number = 0;
    for (;;)
    {
        int rows, cols;
        // get the size of screen
        getmaxyx(stdscr, rows, cols);

        clear();

        // show the first line
        // mvaddnstr(y, x, string, char_size)
        int y = 0;
        mvaddnstr(y, 0, lines[0], cols - 1);
        // reverse the color of text
        mvchgat(y, 0, -1, A_REVERSE, 0, NULL);

        // show the rest of the lines
        for (y = 1; y < rows; y++)
        {
            int current_line_number = top_line_number + y;
            if (current_line_number >= (int)line_count) {
                break;
            }
            mvaddnstr(y, 0, lines[current_line_number], cols - 1);
        }
        refresh();

        // handle keyboard events
        int ch = getch();
        switch (ch)
        {
        case KEY_UP:
            if (top_line_number > 0) {
                top_line_number--;
            }
            break;
        case KEY_DOWN:
            if (top_line_number < (int)line_count - (rows - 1)) {
                top_line_number++;
            }
            break;
        case 'g':
            top_line_number = 0;
            break;
        case 'G':
            top_line_number = (int)line_count - (rows - 1);
            break;
        case 'q':
            // quit
            reset_shell_mode();
            endwin();
            delscreen(screen);
            for (size_t i = 0; i < line_count; i++) {
                free(lines[i]);
            }
            free(lines);
            return 0;
        }
    }
}