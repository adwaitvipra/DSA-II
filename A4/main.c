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
    traverse(tree);
    return 0;
}
