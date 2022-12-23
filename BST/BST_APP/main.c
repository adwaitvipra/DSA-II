
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include "BST.h"
#define MAX_BST 10

// driver code for program

int main()
{
    char name[128];
    bst trees[MAX_BST]={0}; // creating a array of BST's
    int num_bst = 0;
    int isInit[MAX_BST] = {0};
    int choice=INT_MIN;
    int x = INT_MIN;

    printf("**************** Binary Search Tree ****************\n");
    do
    {
        // driver menu
        printf("**************** Main Menu ****************\n");
        printf("1. Create a BST\n");
        printf("2. Initialize a BST\n");
        printf("3. Traverse a BST\n");
        printf("4. Insert a Node\n");
        printf("5. Remove a Node\n");
        printf("6. Search a Node\n");
        printf("7. Display Nodes on a level\n");
        printf("8. Destroy a BST\n");
        printf("9. Show Available BST's\n");
        printf("10. Exit\n");
        printf("Enter Your Choice:");

        scanf(" %d", &choice);

        switch (choice)
        {
		
        case 1:
		{

            		if (num_bst < MAX_BST)
            		{
                		printf("BST Created Succesfully\nBST No.: %d\n\n", num_bst);
                		num_bst++;
           	 }
            	else
                	printf("Overflow!\n\n");
            break;
		}
        case 2:
		{

            printf("Enter BST No.:");
            scanf(" %d", &x);
            if ((x >= 0 && x <= num_bst) && !isInit[x]) // check for valid index and if it is initialized already
            {
                initBST(&trees[x]);
                isInit[x]++;
                printf("BST Initialized Succesfully\n\n");
            }
            else
                printf("BST not Found or BST initialized already!\n\n");
            break;
		}
        case 3:
		{
            printf("Enter BST No.:");
            scanf(" %d", &x);
            if (x >= 0 && x <= num_bst && isInit[x])
            {
                if (!trees[x])
                    printf("Empty Tree!\n");
                else
                    postorder(trees[x]);
                printf("\n\n");
            }
            else
                printf("BST not Found or BST uninitialized!\n\n");
            break;
		}
        case 4:
		{
            printf("Enter BST No.:");
            scanf(" %d", &x);
            if (x >= 0 && x <= num_bst && isInit[x])
            {
                int d;
                printf("Enter MIS:");
                scanf(" %d", &d);
                printf("Enter Name:");
                scanf("%s", name);
                insertNode(&trees[x], d, name);
            }
            else
                printf("BST not Found or BST uninitialized!\n\n");
            break;
		}
        case 5:
		{
            printf("Enter BST No.:");
            scanf(" %d", &x);
            if (x >= 0 && x <= num_bst && isInit[x])
            {
                int d;
                printf("Enter MIS:");
                scanf(" %d", &d);
                trees[x] = removeNode(&trees[x], d);
            }
            else
                printf("BST not Found or BST uninitialized!\n\n");
            break;
		}
        case 6:
		{
            printf("Enter BST No.:");
            scanf(" %d", &x);
            if (x >= 0 && x <= num_bst && isInit[x])
            {
                int d;
                printf("Enter MIS:");
                scanf(" %d", &d);
                node *temp = searchNode(trees[x], d);
                if (!temp)
                    printf("Not Found!\n");
                else
                    printf("%d : %s\t\tfound in BST\n", temp->mis, temp->name);
            }
            else
                printf("BST not Found or BST uninitialized!\n\n");
            break;
		}
        case 7:
		{
            printf("Enter BST No.:");
            scanf(" %d", &x);
            if (x >= 0 && x <= num_bst && isInit[x])
            {
                int d;
                printf("Enter Level No.:");
                scanf(" %d", &d);
                displayLevel(trees[x], d);
            }
            else
                printf("BST not Found or BST uninitialized!\n\n");
            break;
		}
        case 8:
		{
            printf("Enter BST No.:");
            scanf(" %d", &x);
            if (x >= 0 && x <= num_bst && isInit[x])
            {
                destroyTree(trees[x]);
                printf("BST No. : %d, Destroyed...\n\n", x);
                isInit[x]--;
                trees[x] = NULL;
            }
            else
                printf("BST not Found or BST uninitialized!\n\n");
            break;
		}
        case 9:
		{
            if (num_bst >= 0)
            {
                for (int i = 0; i <= num_bst; i++)
                {
                    if (trees[i] != NULL)
                        printf("BST No. :%d\n", i);
                }
            }
            break;
		}
        default:
		{
            if (choice != 10)
                printf("Wrong Choice!\nTry Again!\n\n");
            else
                printf("Thank You!\n\n");
            break;
		}
        }
        getchar();
        printf("\nPress Any Key\n");
        getchar();
        system("clear");
    } while (choice != 10);
    return 0;
}
