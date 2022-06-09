// Implement following operations on a Binary File having student records (MIS, Name, Stream, CGPA
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
    displayRecords("students.dat");
    displayStreamCount("students.dat");
    return 0;
}
