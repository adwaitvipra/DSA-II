#ifndef SERIALIZE_H
#define SERIALIZE_H

typedef struct
{
    int mis;
    char name[64];
    char stream[128];
    float cgpa;
} stud;

void insertRecord(const char *, int);
void searchRecordByName(const char *, const char *);
void searchRecordByStream(const char *, const char *);
stud searchRecordByMIS(const char *, const int);
void searchRecordByCGPA(const char *, const float);
int deleteRecordDummy(const char *, const int);
void deleteRecordFile(const char *, const int);
void displayRecords(const char *);
void displayStreamCount(const char *);
void generateDatabase(const char *, const char *);
#endif