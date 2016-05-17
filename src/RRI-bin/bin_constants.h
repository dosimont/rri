/*  RRI - Relevant Routine Identifier
*   Copyright (C) 2016  Damien Dosimont
*
*   This file is part of RRI.
*
*   RRI is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef BIN_CONSTANTS_H
#define BIN_CONSTANTS_H

#define TSNUMBER 200
#define MIN_TSNUMBER_NOVOID 10
#define THRESHOLD 0.0001
#define MINPROP 0.8

#define CSV_FILES "*.csv"
#define RRI_DIR_PATTERN ".rri"
#define RRI_PRV_PATTERN ".prv"
#define CALLERDATA_FILES "*.callerdata"
#define CALLERDATA_REGIONS_FILE "*.callerdata.regions"
#define STATS_FILE "*.stats"
#define SLOPE_FILE "*slope.csv"
#define PRV_INPUT_FILE "*.codeblocks.fused.folded.prv"

#define INFO_FILE "info.csv"
#define QUALITY_FILE "qualities.csv"
#define PARTITION_FILE "partitions.csv"
#define DETAIL_FILE "detailed_partition.csv"
#define ROUTINE_FILE "routines.csv"

#define PROFILING_FILE "profiling.csv"

#define SEP ","

#define RETURN_OK 0
#define RETURN_ERR_CMD 1
#define RETURN_ERR_OTHER 2
#define RETURN_ERR_INVALID_INPUT_DIR -1
#define RETURN_ERR_INVALID_INPUT_FILE -2
#define RETURN_ERR_INVALID_OUTPUT_DIR -3
#define RETURN_ERR_EXISTING_OUTPUT_DIR -4
#define RETURN_ERR_INVALID_REGION_FILE -5
#define RETURN_ERR_INVALID_SLOPE_FILE -12
#define RETURN_ERR_INVALID_STATS_FILE -13
#define RETURN_ERR_INVALID_PROFILING_FILE -14
#define RETURN_ERR_INVALID_OUTPUT_STREAM -6
#define RETURN_ERR_INVALID_INPUT_STREAM -7
#define RETURN_ERR_INVALID_INPUT_TRACE -8
#define RETURN_ERR_COPY_TRACE -9
#define RETURN_ERR_INVALID_OUTPUT_TRACE -10
#define RETURN_ERR_COPY_CSV -11



#endif // BIN_CONSTANTS_H
