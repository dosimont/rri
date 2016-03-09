#ifndef PRV_CONSTANTS_H
#define PRV_CONSTANTS_H

#define EXT_PRV ".prv"
#define EXT_PCF ".pcf"
#define EXT_ROW ".row"

//Region file csv fields
#define CSV_REGION_NAME 0
#define CSV_REGION_APPL 1
#define CSV_REGION_TASK 2
#define CSV_REGION_THREAD 3
#define CSV_REGION_START 4
#define CSV_REGION_END 5

#define CSV_REGION_SIZE 6

#define BASENAME_RRI 123456000

#define RETURN_OK 0
#define RETURN_ERR_INVALID_PCF -1
#define RETURN_ERR_INVALID_PRV -2
#define RETURN_ERR_INVALID_ROW -3
#define RETURN_ERR_COPY -4


#endif // PRV_CONSTANTS_H
