// Implement following operations on a Binary db having student records (MIS, Name, Stream, CGPA
// etc):
// Insert Record
// Search Record by any field
// Delete Record
// Display all records
// Display Count of students from each stream
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SERIALIZE.h"

int main()
{
    const char *db = "students.dat";
    const char *testdb = "test.dat";
    generateDatabase(db, testdb);
    displayStreamCount(db);
    deleteRecordDummy(db, 2);
    searchRecordByMIS(db, 2);
    displayStreamCount(db);
    return 0;
}
