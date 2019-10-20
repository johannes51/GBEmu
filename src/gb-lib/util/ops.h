#ifndef OPS_H
#define OPS_H

#include "cpu/operation.h"
#include "mem/mem_defines.h"
#include "location/location_defines.h"


namespace ops
{

template<class T>
void increment(LocationUP<T> location)
{
  *location << **location + 1;
}

}

#endif // OPS_H
