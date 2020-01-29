//informatii despre filme
//Informatii despre actori,regizori,platou,durata de filmare,rularea in cinematograf
#include <stdio.h>
#include <stdlib.h>

struct actor{
char nume[30],prenume[30];
};

struct regizor{
char nume[30],prenume[30];
};

struct platou{
char tara[30],orasul[30],tema[30];
}

struct durata_de_filmare{
int durata;
};

struct rularea_in_cinema{
int data_premiera;
char cinematograf[30],tara[30];
};

int main()
{
    return 0;
}
