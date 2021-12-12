#ifndef REGISTERBANKADAPTER_H
#define REGISTERBANKADAPTER_H

#include "iregisteradapter.h"

#include "mem/registerbank.h"

class RegisterBankAdapter : public IRegisterAdapter {
public:
  RegisterBankAdapter(RegisterBank& bank);

private:
  RegisterBank& bank_;
};

#endif // REGISTERBANKADAPTER_H
