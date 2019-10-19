#ifndef _SHAPE_PRODUCER_
#define _SHAPE_PRODUCER_

#include <QVector>
#include <QPair>
#include "TetrixShape.h"

class ShapeProducer
{
    using coordinateOffset = QPair<int, int>;
    using offsetsList = QVector<coordinateOffset>;
private:
    
    static offsetsList typeIOffset ( const int state_number );
    static offsetsList typeJOffset ( const int state_number );
    static offsetsList typeLOffset ( const int state_number );
    static offsetsList typeTOffset ( const int state_number );
    static offsetsList typeOOffset ( const int state_number );
    static offsetsList typeZOffset ( const int state_number );
    static offsetsList typeSOffset ( const int state_number );  
public:
    ShapeProducer() = delete;
    static offsetsList produceState( const int state_number, const ShapeType type ); 
    
};


#endif
