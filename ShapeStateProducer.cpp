#include "ShapeStateProducer.h"

QVector<ShapeProducer::coordinateOffset> ShapeProducer::produceState ( const int state_number, const ShapeType type )
{
    switch ( type ) {
    case ShapeType::i_type:
        return ShapeProducer::typeIOffset ( state_number );
    case ShapeType::j_type:
        return ShapeProducer::typeJOffset ( state_number );
    case ShapeType::l_type:
        return ShapeProducer::typeLOffset ( state_number );
    case ShapeType::o_type:
        return ShapeProducer::typeOOffset ( state_number );
    case ShapeType::s_type:
        return ShapeProducer::typeSOffset ( state_number );
    case ShapeType::z_type:
        return ShapeProducer::typeZOffset ( state_number );
    case ShapeType::t_type:
        return ShapeProducer::typeTOffset ( state_number );
    }
}

ShapeProducer::offsetsList ShapeProducer::typeIOffset ( const int state_number )
{
    if ( state_number == 0 || state_number == 2 ) {
        return { { 0, 0 }, { 0, -2 }, { 0, -1 }, { 0, 1 } };
    } else {
        return { { 0, 0 }, { -2, 0 }, { -1, 0 }, { 1, 0 } };
    }
}

ShapeProducer::offsetsList ShapeProducer::typeJOffset ( const int state_number )
{
    switch ( state_number ) {
    case 0:
        return { { 0, 0 }, { 0, -1 }, { 0, 1 }, { -1, 1 } };
    case 1:
        return { { 0, 0 }, { 1, 0 }, { -1, 0 }, { -1, -1 } };
    case 2:
        return { { 0, 0 }, { 0, 1 }, { 0, -1 }, { 1, -1 } };
    case 3:
        return { { 0, 0 }, { -1, 0 }, { 1, 0}, { 1, 1 } };
    }
}

ShapeProducer::offsetsList ShapeProducer::typeLOffset ( const int state_number )
{
    switch ( state_number ) {
    case 0:
        return { { 0, 0 }, { 0, -1 }, { 0, 1 }, { 1, 1 } };
    case 1:
        return { { 0, 0 }, { 1, 0 }, { -1, 0 }, { -1, 1 } };
    case 2:
        return { { 0, 0 }, { 0, 1 }, { 0, -1 }, { -1, -1 } };
    case 3:
        return { { 0, 0 }, { -1, 0 }, { 1, 0}, { 1, -1 } };
    }
}

ShapeProducer::offsetsList ShapeProducer::typeOOffset ( const int state_number )
{
    return { { 0, 0 }, { 1, 0 }, { 1, 1 }, { 0, 1 } };
}

ShapeProducer::offsetsList ShapeProducer::typeSOffset ( const int state_number )
{
    if ( state_number == 0 || state_number == 2 ) {
        return { { 0, 0 }, { 1, 0 }, { 0, 1 }, { -1, 1 } };
    } else {
        return { { 0, 0 }, { 0, 1 }, { -1, 0 }, { -1, -1 } };
    }
}

ShapeProducer::offsetsList ShapeProducer::typeTOffset ( const int state_number )
{
    switch ( state_number ) {
    case 0:
        return { { 0, 0 }, { 0, -1 }, { 1, 0 }, { -1, 0 } };
    case 1:
        return { { 0, 0 }, { 1, 0 }, { 0, 1 }, { 0, -1 } };
    case 2:
        return { { 0, 0 }, { 0, 1 }, { -1, 0 }, { 1, 0 } };
    case 3:
        return { { 0, 0 }, { -1, 0 }, { 0, -1 }, { 0, 1 } };
    }
}

ShapeProducer::offsetsList ShapeProducer::typeZOffset ( const int state_number )
{
    if ( state_number == 0 || state_number == 2 ) {
        return { { 0, 0 }, { -1, 0 }, { 0, 1 }, { 1, 1 } };
    } else {
        return { { 0, 0 }, { 0, -1 }, { -1, 0 }, { -1, 1 } };
    }
}

