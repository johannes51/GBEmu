#ifndef DEFINES_H
#define DEFINES_H

#define DISABLE_COPY(X)                                                        \
  X(const X &) = delete;                                                       \
  const X &operator=(const X &) = delete;
#define DISABLE_MOVE(X)                                                        \
  X(const X &&) = delete;                                                      \
  const X &operator=(const X &&) = delete;

#endif // DEFINES_H
