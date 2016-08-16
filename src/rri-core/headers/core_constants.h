/*  RRI - Relevant Routine Identifier
*  Copyright (C) 2016  Damien Dosimont
*  
*  This file is part of RRI.
*  
*  RRI is free software: you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation, either version 3 of the License, or
*  (at your option) any later version.
*  
*  This program is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*  
*  You should have received a copy of the GNU General Public License
*  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

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

//Default lpaggreg parameters
#define DEFAULT_PARAMETER_NORMALIZE true
#define DEFAULT_PARAMETER_THRESHOLD 0.0001
#define DEFAULT_PARAMETER_PARAMETER 0
#define DEFAULT_PARAMETER_TIMESLICENUMBER -1

//Default rendering parameters
#define DEFAULT_ROUTINE_MINPROP 0.8

//Best p minimum gain
#define NORM_BEST_MIN_GAIN 0.1

namespace rri {

//Analysis type
    enum InputFileType { RRI, DEFAULT };

//P default value
    enum PDefaultValue { MAX, MIN, NORM_INFLECT, NORM_INFLECT2, NORM_BEST };
}




#endif // CONSTANTS_H
