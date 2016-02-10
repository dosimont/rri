#ifndef CONSTANTS_H
#define CONSTANTS_H

//File extensions
#define FILE_EXT_RRI "callerdata"

//RRI file csv fields
#define CSV_RRI_ID 0
#define CSV_RRI_SAMPLE 1
#define CSV_RRI_TS_PERCENTAGE 2
#define CSV_RRI_TS_ABSOLUTE 3
#define CSV_RRI_CALLSTACK_LVL 4
#define CSV_RRI_ROUTINE_ID 5
#define CSV_RRI_CODELINE_ID 6

//Default parameters
#define DEFAULT_PARAMETER_NORMALIZE true
#define DEFAULT_PARAMETER_THRESHOLD 0.0001
#define DEFAULT_PARAMETER_PARAMETER 0
#define DEFAULT_PARAMETER_TIMESLICENUMBER 200

//Analysis type
namespace InputData {
    enum DataType { RRI, DEFAULT };
}

#endif // CONSTANTS_H
