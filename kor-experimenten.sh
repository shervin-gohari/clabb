rm -rf resultat a.out

gcc hashfunc.c lista.c test.c hashfunktioner/tilpro-and.c && ./a.out
gcc hashfunc.c lista.c test.c hashfunktioner/tilpro-modulo.c && ./a.out
gcc hashfunc.c lista.c test.c hashfunktioner/djb2.c && ./a.out
gcc hashfunc.c lista.c test.c hashfunktioner/naiv.c && ./a.out
