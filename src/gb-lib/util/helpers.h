#ifndef HELPERS_H
#define HELPERS_H

#include "mem/mem_defines.h"
#include "location/location.h"


namespace hlp
{

address_type indirect(const LocationUP<address_type> location);

}

#endif // HELPERS_H
