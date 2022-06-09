#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "SERIALIZE.h"
#define _OPEN_SYS_ITOA_EXT
// #######################################################################################################################
// Inserting the record
// #######################################################################################################################
void insertRecord(const char *filename, int x)
{
    FILE *fh;
    fh = fopen(filename, "ab");
    stud rec;
    for (int i = 0; i < x; i++)
    {
        printf("\nRecord No. %d\n", i + 1);
        // init records
        printf("\nEnter MIS:");
        scanf("%d", &rec.mis);
        printf("\nEnter Name:");
        scanf(" %s", rec.name);
        printf("\nEnter Stream:");
        scanf(" %s", rec.stream);
        printf("\nEnter CGPA:");
        scanf(" %f", &rec.cgpa);
        // write records
        fwrite(&rec, sizeof(stud), 1, fh);
    }
    fclose(fh);
    return;
}
// #######################################################################################################################
// Search Record by any Field, if the field is not unique returns the array of structs
// #######################################################################################################################
stud *searchRecordByName(const char *filename, const char *key)
{
    FILE *fh = fopen(filename, "rb");
    stud *recArr = NULL;
    stud rec;
    int recIdx = -1;
    int recCnt = 0;
    while (fread(&rec, sizeof(stud), 1, fh))
    {

        if (!strcmp(key, rec.name))
        {
            recArr = (stud *)realloc(recArr, sizeof(stud *) * (++recCnt));
            recArr[++recIdx] = rec;
        }
    }
    fclose(fh);
    return recArr;
}
stud *searchRecordByStream(const char *filename, const char *key)
{
    FILE *fh = fopen(filename, "rb");
    stud rec, *recArr = NULL;
    int recIdx = -1;
    int recCnt = 0;
    while (fread(&rec, sizeof(stud), 1, fh))
    {
        if (!strcmp(key, rec.name))
        {
            recArr = (stud *)realloc(recArr, sizeof(stud *) * (++recCnt));
            recArr[++recIdx] = rec;
        }
    }
    fclose(fh);
    return recArr;
}
stud searchRecordByMIS(const char *filename, const int key)
{
    FILE *fh = fopen(filename, "rb");
    stud rec;
    stud nil = {-1, "", "", -1};
    while (fread(&rec, sizeof(stud), 1, fh))
    {

        if (key == rec.mis)
        {
            fclose(fh);
            return rec;
        }
    }
    fclose(fh);
    return nil;
}
stud *searchRecordByCGPA(const char *filename, const float key)
{
    FILE *fh = fopen(filename, "rb");
    stud rec, *recArr = NULL;
    int recIdx = -1;
    int recCnt = 0;
    while (fread(&rec, sizeof(stud), 1, fh))
    {

        if (key == rec.cgpa)
        {
            recArr = (stud *)realloc(recArr, sizeof(stud *) * (++recCnt));
            recArr[++recIdx] = rec;
        }
    }
    fclose(fh);
    return recArr;
}
// #######################################################################################################################
// Delete the record, by unique identifier (MIS in this record) {Better to replace the record to be deleted by the dummy }
// #######################################################################################################################
int deleteRecordDummy(const char *filename, const int key)
{
    FILE *fh = fopen(filename, "wb");
    stud rec;
    while (fread(&rec, sizeof(stud), 1, fh))
    {

        if (key == rec.mis)
        {
            rec.mis = -1;
            strcpy(rec.name, "");
            strcpy(rec.stream, "");
            rec.cgpa = -1;
            fseek(fh, -1, SEEK_CUR);
            fwrite(&rec, sizeof(stud), 1, fh);
            fclose(fh);
            return 1;
        }
    }
    fclose(fh);
    return 0;
}
// #######################################################################################################################
// Delete the record with the use of new file in which only record to be deleted is not written, rename the new file.
// #######################################################################################################################
void deleteRecordFile(const char *filename, const int key)
{
    // take old file
    // create new file
    // read old file and write to new file until you encounter the key record, ignore the record to be deleted, continue
    // rename the old file with old.dat name (legacy data) and rename new file with filename (old)
    FILE *fold = fopen(filename, "rb");
    FILE *fnew = fopen("temp.dat", "ab");
    stud rec;
    while (fread(&rec, sizeof(stud), 1, fold))
    {
        if (key == rec.mis)
            ;
        else
            fwrite(&rec, sizeof(stud), 1, fnew);
    }
    fclose(fold);
    fclose(fnew);
    rename(filename, "old.dat");
    rename("temp.dat", filename);
    return;
}
// #######################################################################################################################
// Display all the records
// #######################################################################################################################
void displayRecords(const char *filename)
{
    FILE *fh = fopen(filename, "rb");
    stud rec;
    int cnt = 0;

    printf("\t\t\t\tStudent Records\t\t\t\t\n");
    while (fread(&rec, sizeof(stud), 1, fh))
    {
        if (rec.mis == -1)
            ;
        else
        {

            printf("\nRECORD NUMBER   : %d\n", ++cnt);
            printf("MIS             : %d\n", rec.mis);
            printf("NAME            : %s\n", rec.name);
            printf("STREAM          : %s\n", rec.stream);
            printf("CGPA            : %.2f\n", rec.cgpa);
        }
    }
    fclose(fh);
    return;
}
// #######################################################################################################################
// Display count of students from each stream
// #######################################################################################################################
int getStreamIndex(const char *stream)
{
    if (!strcmp(stream, "COMP"))
        return 0;
    else if (!strcmp(stream, "ELEC"))
        return 1;
    else if (!strcmp(stream, "ENTC"))
        return 2;
    else if (!strcmp(stream, "MECH"))
        return 3;
    else if (!strcmp(stream, "CIVIL"))
        return 4;
    else if (!strcmp(stream, "META"))
        return 5;
    else if (!strcmp(stream, "INSTRU"))
        return 6;
    else if (!strcmp(stream, "PROD"))
        return 7;
    else
        return -1;
}
char *getStreamName(const int key)
{
    if (key == 0)
        return "COMP";
    else if (key == 1)
        return "ELEC";
    else if (key == 2)
        return "ENTC";
    else if (key == 3)
        return "MECH";
    else if (key == 4)
        return "CIVIL";
    else if (key == 5)
        return "META";
    else if (key == 6)
        return "INSTRU";
    else if (key == 7)
        return "PROD";
    else
        return "";
}
void displayStreamCount(const char *filename)
{
    // create arr of stud cnt per stream
    // read every rec from file and inc cnt of corresponding stream
    // display count as per the stream
    FILE *fh = fopen(filename, "rb");
    int streamCntArr[8] = {0};
    int streamIdx;
    char tempStream[128];
    stud rec;
    // get stream count
    while (fread(&rec, sizeof(stud), 1, fh))
    {
        streamIdx = getStreamIndex(rec.stream);
        if (streamIdx == -1)
            ;
        else
            streamCntArr[streamIdx]++;
    }
    // display the stream count
    printf("\n\t\t\t\tSTREAMWISE COUNT OF STUDENTS\t\t\t\t\n");
    for (int i = 0; i < 8; i++)
    {
        strcpy(tempStream, getStreamName(i));
        printf("%s  :   %d\n", tempStream, streamCntArr[i]);
    }
    fclose(fh);
    return;
}

void generateDatabase(const char *tofile, const char *fromfile)
{
    FILE *ftest=fopen(fromfile, "r");
    FILE *fdb=fopen(tofile, "wb");
    stud rec;
    while(fread(&rec, sizeof(stud), 1, ftest))
    {
        fwrite(&rec, sizeof(stud), 1,fdb);
    }
    fclose(ftest);
    fclose(fdb);
    return ;
}