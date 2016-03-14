#ifndef CONSTANTS_H
#define CONSTANTS_H

//RRI file csv fields
#define CSV_RRI_ID 0
#define CSV_RRI_SAMPLE 1
#define CSV_RRI_TS_PERCENTAGE 2
#define CSV_RRI_TS_ABSOLUTE 3
#define CSV_RRI_CALLSTACK_LVL 4
#define CSV_RRI_ROUTINE_ID 5
#define CSV_RRI_ROUTINE_NAME 6
#define CSV_RRI_CODELINE_ID 7
#define CSV_RRI_FILE_NAME 8
#define CSV_RRI_CODELINE 9

#define CSV_RRI_SIZE 10

#define CSV_DEFAULT_SEPARATOR ';'

//Default lpaggreg parameters
#define DEFAULT_PARAMETER_NORMALIZE true
#define DEFAULT_PARAMETER_THRESHOLD 0.0001
#define DEFAULT_PARAMETER_PARAMETER 0
#define DEFAULT_PARAMETER_TIMESLICENUMBER -1

//Default rendering parameters
#define DEFAULT_ROUTINE_MIN_PROP 0.8

namespace rri {

//Analysis type
    enum InputFileType { RRI, DEFAULT };

//P default value
    enum PDefaultValue { MAX, MIN, NORM_INFLECT, NORM_INFLECT2 };
}




#endif // CONSTANTS_H
