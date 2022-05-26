#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>
#include "AVL.h"
int main()
{
    AVL tree;
    initAVL(&tree);
    insertNode(&tree, "JANUARY");
    insertNode(&tree, "FEBRUARY");
    insertNode(&tree, "MARCH");
    insertNode(&tree, "APRIL");
    insertNode(&tree, "MAY");
    insertNode(&tree, "JUNE");
    insertNode(&tree, "JULY");
    insertNode(&tree, "AUGUST");
    insertNode(&tree, "SEPTEMBER");
    insertNode(&tree, "OCTOBER");
    insertNode(&tree, "NOVEMBER");
    insertNode(&tree, "DECEMBER");
    traverse(tree);
    return 0;
}
