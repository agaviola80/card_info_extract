/*
 * Copyright (c) 2024 Archimedes Gaviola <archimedes.gaviola@gmail.com>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
 * REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
 * INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 * LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
 * OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int i, n, m, o, p;
    char str[200];
    char buff[200];
    char cnbuff[30];
    char edbuff[5];

    while (1) {
        buff[0] = '\0';
        printf("SWIPE ATM CARD IN THE CARD READER: \n");
        system("stty -echo");
        gets_s(str, sizeof(str));

        /*
         * Extract all characters and saved in a memory
         * buffer.
         */
        for (i = 0; str[i] != '\0'; i++) {
                strlcat(buff, &str[i], sizeof(buff));
        }

        /*
         * Determine character patterns to extract card number,
         * card holder and expiry date.
         */
        for (n = 0; buff[n] != '\0'; n++) {
            if (buff[n] == ';') {
                cnbuff[0] = '\0';    /* clear cnbuff */
                for (n = 1; buff[n] != '='; n++) {
                    strlcat(cnbuff, &buff[n], sizeof(cnbuff));
                }
                char nbuff[n];
                snprintf(nbuff, sizeof(nbuff), "%s", cnbuff);
                printf("CARD NUMBER: %s\n", nbuff);
            }
            if (buff[n] == '=') {
                edbuff[0] = '\0';    /* clear edbuff */
                for (n = 1; buff[n] != '='; n++) {}
                n = n + 1;
                strlcat(edbuff, &buff[n], sizeof(edbuff));
                printf("EXPIRY DATE: %s\n", edbuff);
            }
            if (buff[n] == '?')
                break;
            if (buff[n] == '%') {
                cnbuff[0] = '\0';    /* clear cnbuff */
                for (n = 2; buff[n] != '^'; n++) {
                    strlcat(cnbuff, &buff[n], sizeof(cnbuff));
                }
                n = n - 1;
                char nbuff[n];
                snprintf(nbuff, sizeof(nbuff), "%s", cnbuff);
                printf("CARD NUMBER: %s\n", nbuff);
            }
            if (buff[n] == '^') {
                /* card holder information */
                for (n = 0; buff[n] != '^'; n++) {}
                n = n + 1;
                char chbuff[n];
                chbuff[0] = '\0';    /* clear chbuff */
                for (m = n; buff[m] != '^'; m++) {
                    strlcat(chbuff, &buff[m], sizeof(chbuff));
                }
                printf("CARD HOLDER: %s\n", chbuff);

                /* expiry date information */
                edbuff[0] = '\0';    /* clear edbuff */
                m = m + 1;
                p = m + 4;
                for (o = m; o <= p; o++) {
                    strlcat(edbuff, &buff[o], sizeof(edbuff));
                }
                printf("EXPIRY DATE: %s\n", edbuff);
                break;
            }
        }
        printf("OK\n");
    }
    return 0;
}
