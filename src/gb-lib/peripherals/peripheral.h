#ifndef PERIPHERAL_H
#define PERIPHERAL_H

class Peripheral {
public:
  virtual ~Peripheral() = default;

  virtual void clock() = 0;

protected:
  Peripheral() = default;
};

#endif // PERIPHERAL_H
