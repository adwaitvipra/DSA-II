// Implement following operations on a Binary db having student records (MIS, Name, Stream, CGPA
// etc):
// Insert Record
// Search Record by any field
// Delete Record
// Display all records
// Display Count of students from each stream

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include "SERIALIZE.h"

void testing(const char *db)
{
    printf("\t\t\t\tDisplaying Records:\n\n");
    displayRecords(db);
    printf("\n\n\t\t\t\tInsert Two Records To Be Deleted\n(SAMPLE, 12345)\n(TESTING, 54321)\n\n");
    insertRecord(db, 2);
    printf("\n\n\t\tSearching Record By Name --> (SAMPLE)\n\n");
    searchRecordByName(db, "SAMPLE");
    printf("\n\n\t\tSearching Record By Stream --> (COMP)\n\n");
    searchRecordByStream(db, "COMP");
    printf("\n\n\t\tSearching Record By MIS --> (12345)\n\n");
    searchRecordByMIS(db, 12345);
    printf("\n\n\t\tSearching Record By CGPA --> (9.0)\n\n");
    searchRecordByCGPA(db, 9.0);
    printf("\n\n\t\tDisplaying Stream Count Before Deletion Of New Records\n\n");
    displayStreamCount(db);
    printf("\n\n\t\tDeleting Record By Dummy Replace --> (12345)\n\n");
    deleteRecordDummy(db, 12345);
    printf("\n\n\t\tDeleting Record By File Copy --> (54321)\n\n");
    deleteRecordFile(db, 54321);
    printf("\n\n\t\tDisplaying Stream Count After Deletion of New Records\n\n");
    displayStreamCount(db);

    return ;
}

int main()
{
    const char *db = "test.dat";
    testing(db);
    return 0;
}
