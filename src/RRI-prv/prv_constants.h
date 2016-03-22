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

#include "eventtypeitem.h"
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
