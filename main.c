#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <malloc.h>

typedef struct DateTime
{
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;

} DateTime;

typedef struct Log
{
    char *message;
    DateTime date;
    char *fileName;
    char *errorCode;
    char *functionName;
} Log;

void getLogLine(char *line, Log *log);
char *toString(DateTime d);
void formateDate(DateTime *d, char *string);
void searchInterval(Log *logs, int logCounter);
void displayLog(Log l);

int main()
{
    FILE *myLogFile = fopen("log.text", "r");
    if (myLogFile == NULL)
    {
        myLogFile = fopen("../log.text", "r");
    }
    if (myLogFile == NULL)
    {
        perror("Error opening file");
        return 1;
    }
    char line[256];
    Log *logs = NULL;
    int logCounter = 0;

    while (fgets(line, sizeof(line), myLogFile))
    {
        logCounter++;
        logs = (Log *)realloc(logs, logCounter * sizeof(Log));
        getLogLine(line, &logs[logCounter - 1]);
    }
    searchInterval(logs, logCounter);
    getchar();
}

void searchInterval(Log *logs, int logCounter)
{
    int year_start, month_start, day_start;
    int year_end, month_end, day_end;
    printf("\nEnter start date respecting formate (2002-19-07) : ");
    scanf("%d-%d-%d", &year_start, &day_start, &month_start);
    printf("\nEnter end date respecting formate (2002-19-07) : ");
    scanf("%d-%d-%d", &year_end, &day_end, &month_end);

    for (int i = 0; i < logCounter; i++)
    {
        if ((logs[i].date.year > year_start || (logs[i].date.year == year_start && logs[i].date.month > month_start) ||
             (logs[i].date.year == year_start && logs[i].date.month == month_start && logs[i].date.day >= day_start)) &&
            (logs[i].date.year < year_end || (logs[i].date.year == year_end && logs[i].date.month < month_end) ||
             (logs[i].date.year == year_end && logs[i].date.month == month_end && logs[i].date.day <= day_end)))
        {
            displayLog(logs[i]);
        }
    }
}

void formateDate(DateTime *d, char *string)
{
    sscanf(string, "%d/%d/%d-%d:%d:%d", &(d->month), &(d->day), &(d->year), &(d->hour), &(d->minute), &(d->second));
}

char *toString(DateTime d)
{
    char *result = (char *)malloc(20);
    sprintf(result, "%04d-%02d-%02d %02d:%02d:%02d", d.year, d.month, d.day, d.hour, d.minute, d.second);
    return result;
}

void displayLog(Log l)
{
    printf("%s %s %s %s %s \n",
           l.fileName, toString(l.date),
           l.errorCode, l.functionName, l.message);
}

void getLogLine(char *line, Log *log)
{
    char *token = strtok(line, "#");
    // File name
    log->fileName = strdup(token);
    // Date
    token = strtok(NULL, "#");
    formateDate(&(log->date), strdup(token));
    // Error code
    token = strtok(NULL, "#");
    log->errorCode = strdup(token);
    // Function name
    token = strtok(NULL, "#");
    log->functionName = strdup(token);
    // Message
    token = strtok(NULL, "#");
    log->message = strdup(token);
}
