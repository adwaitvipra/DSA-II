#ifndef SERIALIZE_H
#define SERIALIZE_H

typedef struct
{
    int mis;
    char name[128];
    char stream[128];
    float cgpa;
} student;

void insertRecord(const char *, int);
void searchRecordByName(const char *, const char *);
void searchRecordByStream(const char *, const char *);
bool searchRecordByMIS(const char *, const int);
bool searchRecordByCGPA(const char *, const float);
bool deleteRecordDummy(const char *, const int);
void deleteRecordFile(const char *, const int);
void displayRecords(const char *);
void displayStreamCount(const char *);

#endif // SERIALIZE_H
