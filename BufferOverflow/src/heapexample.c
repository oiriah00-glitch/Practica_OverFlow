/*
 * heapexample.c - heap overflow de la practica.
 * Compilar: make
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct sdata {
    char buffer[64];
};

struct sfp {
    void (*fp)(void);
};

__attribute__((noinline, used))
void fentrar(void)
{
    puts("Pasando");
}

__attribute__((noinline, used))
void fesperofuera(void)
{
    puts("Esperando fuera");
}

int main(int argc, char **argv)
{
    struct sdata *smidat;
    struct sfp *f;

    setvbuf(stdout, NULL, _IONBF, 0);

    if (argc < 2) {
        fprintf(stderr, "Uso: %s <cadena>\n", argv[0]);
        return 1;
    }

    smidat = malloc(sizeof(*smidat));
    f = malloc(sizeof(*f));
    if (smidat == NULL || f == NULL) {
        perror("malloc");
        return 1;
    }

    f->fp = fesperofuera;

    printf("[+] smidat (buffer)      = %p\n", (void *)smidat);
    printf("[+] f (struct sfp)       = %p\n", (void *)f);
    printf("[+] &smidat->buffer      = %p\n", (void *)&smidat->buffer);
    printf("[+] &f->fp               = %p\n", (void *)&f->fp);
    printf("[+] offset (f - smidat)  = %td\n", (char *)f - (char *)smidat);
    printf("[+] offset (fp - buffer) = %td\n",
           (char *)&f->fp - (char *)smidat->buffer);
    printf("[+] &fentrar             = %p\n", (void *)fentrar);
    printf("[+] &fesperofuera        = %p\n", (void *)fesperofuera);
    printf("[+] argv[1] (stack)      = %p\n", (void *)argv[1]);

    strcpy(smidat->buffer, argv[1]);   /* vulnerable */
    f->fp();

    return 0;
}
