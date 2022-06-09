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
stud *searchRecordByName(const char *, const char *);
stud *searchRecordByStream(const char *, const char *);
stud searchRecordByMIS(const char *, const int);
stud *searchRecordByCGPA(const char *, const float);
int deleteRecordDummy(const char *, const int);
void deleteRecordFile(const char *, const int);
void displayRecords(const char *);
char *getStreamName(const int );
int getStreamIndex(const char *);
void displayStreamCount(const char *);
void generateDatabase(const char *, const char *);

#endif