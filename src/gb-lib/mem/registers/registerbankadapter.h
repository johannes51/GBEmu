#ifndef REGISTERBANKADAPTER_H
#define REGISTERBANKADAPTER_H

#include "iregisteradapter.h"

#include "mem/registerbank.h"

class RegisterBankAdapter : public IRegisterAdapter {
public:
  explicit RegisterBankAdapter(RegisterBank& bank);

  // TODO: machen!
private:
  RegisterBank& bank_;
};

#endif // REGISTERBANKADAPTER_H
