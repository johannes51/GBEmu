#include "helpers.h"

address_type hlp::indirect(const LocationUP<address_type> location) {
  return **location;
}
