#ifndef BIN_CONSTANTS_H
#define BIN_CONSTANTS_H

#define TS_NUMBER 200

#define RRI_DIR_PATTERN ".rri"
#define RRI_PRV_PATTERN ".prv"
#define CALLERDATA_FILES "*.callerdata"
#define CALLERDATA_REGIONS_FILE "*.callerdata.regions"
#define PRV_INPUT_FILE "*.codeblocks.fused.folded.prv"

#define INFO_FILE "info.csv"
#define QUALITY_FILE "qualities.csv"
#define PARTITION_FILE "partitions.csv"
#define DETAIL_FILE "detailed_partition.csv"
#define ROUTINE_FILE "routines.csv"

#define SEP ","

#define RETURN_OK 0
#define RETURN_ERR_CMD 1
#define RETURN_ERR_INVALID_INPUT_DIR -1
#define RETURN_ERR_INVALID_INPUT_FILE -2
#define RETURN_ERR_INVALID_OUTPUT_DIR -3
#define RETURN_ERR_EXISTING_OUTPUT_DIR -4
#define RETURN_ERR_INVALID_REGION_FILE -5
#define RETURN_ERR_INVALID_OUTPUT_STREAM -6
#define RETURN_ERR_INVALID_INPUT_STREAM -7
#define RETURN_ERR_INVALID_INPUT_TRACE -8
#define RETURN_ERR_COPY_TRACE -9
#define RETURN_ERR_INVALID_OUTPUT_TRACE -10



#endif // BIN_CONSTANTS_H
