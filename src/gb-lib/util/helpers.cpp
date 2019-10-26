#include "helpers.h"

address_type hlp::indirect(Location<address_type> location) {
  return location.get();
}
