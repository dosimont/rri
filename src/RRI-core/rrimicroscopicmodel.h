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

#ifndef RRIMICROSCOPICMODEL_H
#define RRIMICROSCOPICMODEL_H

#include <QObject>
#include <QFile>
#include <QVector>
#include <QString>
#include <QStringList>
#include <QTextStream>
#include <QDebug>
#include <vector>
#include "microscopicmodel.h"
#include "rriobject.h"
#include "dummystreamreader.h"
#include "biqmap.h"
#include "core_constants.h"
#include "debug.h"
#include "rritimeslice.h"

using std::vector;

class RRIMicroscopicModel : public MicroscopicModel
{
public:
    RRIMicroscopicModel();
    RRIMicroscopicModel(MicroscopicModel);
    ~RRIMicroscopicModel();
    void generate(QTextStream *stream, int timeSlices);
    BiQMap<int, QString> getMatrixIndexToRoutineId() const;
    QVector<RRITimeSlice*> getTimeSlices() const;
    bool hasVoid() const;

private:
    RRIObject* buildRRIObject(QStringList fields);
    RRIObject* buildRRIObject(QStringList fields, int line);
    void build(int timeSlices);
    void addToMicroscopicModel(RRIObject* object, int timeSlice);
    QVector<RRIObject*> objects;
    QVector<RRITimeSlice*> timeSlices;
    BiQMap<int, QString> matrixIndexToRoutineId;
    bool hv;
};

#endif // RRIMICROSCOPICMODEL_H
