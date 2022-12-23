#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include "SERIALIZE.h"

void printRecord(student *rec);
int getStreamIndex(const char *);
char *getStreamName(const int );
void displayStreamCount(const char *);
void generateDatabase(const char *, const char *);

// #######################################################################################################################
// Inserting the record
// #######################################################################################################################
void insertRecord(const char *filename, int cnt)
{
    FILE *fh;
    fh = fopen(filename, "ab");
    if(!fh)
	    return;
    student rec;

    for (int i = 0; i < cnt; i++)
    {
        printf("\nRecord No. %d\n", i + 1);
        // init record
        printf("\nEnter MIS:");
        scanf("%d", &rec.mis);
        printf("\nEnter Name:");
        scanf(" %s", rec.name);
        printf("\nEnter Stream:");
        scanf(" %s", rec.stream);
        printf("\nEnter CGPA:");
        scanf(" %f", &rec.cgpa);
        // write record
        fwrite(&rec, sizeof(student), 1, fh);
    }
    fclose(fh);
    return;
}
// #######################################################################################################################
// Search Record by any Field, if the field is not unique returns the array of structs
// #######################################################################################################################
void printRecord(student *rec)
{

    printf("\n\nMIS             : %d\n", rec->mis);
    printf("NAME            : %s\n", rec->name);
    printf("STREAM          : %s\n", rec->stream);
    printf("CGPA            : %.2f\n\n", rec->cgpa);
    return;
}

void searchRecordByName(const char *filename, const char *query)
{
    // student *recArr = NULL;
    student rec;
    // int recIdx = -1;
    // int recCnt = 0;
    FILE *fh = fopen(filename, "rb");
    if(!fh)
	    return ;

    while (fread(&rec, sizeof(student), 1, fh))
    {

        if (!strcmp(query, rec.name))
        {
            // recArr = (student *)realloc(recArr, sizeof(student) * (++recCnt));
            // recArr[++recIdx] = rec;
            printRecord(&rec);
        }
    }
    // printf("cnt:%d\n", recCnt);
    fclose(fh);
    return;
}

void searchRecordByStream(const char *filename, const char *query)
{
    student rec;
    // student *recArr = NULL;
    // int recIdx = -1;
    // int recCnt = 0;
    FILE *fh=NULL;

    if(getStreamIndex(query) == -1)
	    ;
    else if((fh = fopen(filename, "rb")))  
    {
  	  while (fread(&rec, sizeof(student), 1, fh))
	    {
        	if (!strcmp(query, rec.stream))
        	{
           	 // recArr = (student *)realloc(recArr, sizeof(student) * (++recCnt));
          	  // recArr[++recIdx] = rec;
           	 printRecord(&rec);
        	}
	    }
    	fclose(fh);
    }
    // printf("cnt:%d\n", recCnt);
    return;
}

bool searchRecordByMIS(const char *filename, const int key)
{
    student rec;
    FILE *fh = NULL; 
    if(key < 0)
	    ;
    else if((fh = fopen(filename, "rb")))
    {
	    while (fread(&rec, sizeof(student), 1, fh))
   	 	{
			if (key == rec.mis)
			{
            			printRecord(&rec);
            			fclose(fh);
            			return true;
        		}
    		}
    	fclose(fh);
    }
    return false;
}

bool searchRecordByCGPA(const char *filename, const float key)
{
    student rec;
    // student *recArr = NULL;
    // int recIdx = -1;
    // int recCnt = 0;
    FILE *fh = NULL;
    if(key < 0.0 && key > 10.0 )
	    ;
    else if((fh = fopen(filename, "rb")))
    {
   	 while (fread(&rec, sizeof(student), 1, fh))
    	{

        	if (key == rec.cgpa)
        	{
            		// recArr = (student *)realloc(recArr, sizeof(student) * (++recCnt));
            		// recArr[++recIdx] = rec;
           		 printRecord(&rec);
			 return true;
        	}
    	}
    	fclose(fh);
    }
    // printf("cnt:%d\n", recCnt);
    return false;
}
// #######################################################################################################################
// Delete the record, by unique identifier (MIS in this case) {Better to replace the record to be deleted by the dummy}
// #######################################################################################################################
bool deleteRecordDummy(const char *filename, const int key)
{
    FILE *fh = NULL;
    student rec;
    student null_rec = { -1, "NA", "NA", -1}; 
    long offset;

    if(key < 0)
	    ;
    else if((fh = fopen(filename, "rb+")))
    {
	    while (fread(&rec, sizeof(student), 1, fh))
	    {
        	if (key == rec.mis)
        	{
        		offset = (ftell(fh)-sizeof(student));
           	 	fseek(fh,offset, SEEK_SET);
           	 	fwrite(&null_rec, sizeof(student), 1, fh);
           	 	fclose(fh);
            		return true;
		}
	    }
    	fclose(fh);
    }
    return false;
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

    FILE *fold = NULL; 
    FILE *fnew = NULL; 
    student rec;
    char *newname = NULL;

    if((searchRecordByMIS(filename, key)) && (fold = fopen(filename, "rb"))
		    && (fnew = fopen("temp.dat", "ab")))
    {
	    while (fread(&rec, sizeof(student), 1, fold))
        	{
            		if (key == rec.mis)
                		;
            		else
                		fwrite(&rec, sizeof(student), 1, fnew);
        	}
	    newname = strdup(filename);
	    newname = strcat(newname, "old.dat");
	    rename(filename, newname);
	    rename("temp.dat", filename);
	    free(newname);
	    fclose(fold);
	    fclose(fnew);
    }
    else
    {
	if(fold)
		fclose(fold);
        printf("\n\nRECORD NOT FOUND!\nOR OPEN FAILED\n\n");
    }
    return;
}
// #######################################################################################################################
// Display all the records
// #######################################################################################################################
void displayRecords(const char *filename)
{
    FILE *fh = fopen(filename, "rb");
    student rec;
    int cnt = 0;

    printf("\t\t\t\tSTUDENT'S RECORD\t\t\t\t\n");
    while (fread(&rec, sizeof(student), 1, fh))
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
    // create arr of student cnt per stream
    // read every rec from file and inc cnt of corresponding stream
    // display count as per the stream
    FILE *fh = fopen(filename, "rb");
    int streamCntArr[8] = {0};
    int streamIdx;
    int total=0;
    char tempStream[128];
    student rec;

    if(!fh)
	    return ;

    // get stream count
    while (fread(&rec, sizeof(student), 1, fh))
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
        printf("%-10s : %10d\n", tempStream, streamCntArr[i]);
        total += streamCntArr[i];
    }
    printf("\n\nTOTAL NUMBER OF RECORDS : %d\n\n", total);
    fclose(fh);
    return;
}

