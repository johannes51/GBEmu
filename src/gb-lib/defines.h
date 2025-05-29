#ifndef DEFINES_H
#define DEFINES_H

#define DISABLE_COPY(ClassName)                                                                                        \
  ClassName(const ClassName&) = delete;                                                                                \
  ClassName& operator=(const ClassName&) = delete;
#define DISABLE_MOVE(ClassName)                                                                                        \
  ClassName(ClassName&&) = delete;                                                                                     \
  ClassName& operator=(ClassName&&) = delete;
#define DISABLE_COPY_AND_MOVE(ClassName)                                                                               \
  ClassName(const ClassName&) = delete;                                                                                \
  ClassName& operator=(const ClassName&) = delete;                                                                     \
  ClassName(ClassName&&) = delete;                                                                                     \
  ClassName& operator=(ClassName&&) = delete;

#define DEFAULT_COPY_AND_MOVE(ClassName)                                                                               \
  ClassName(const ClassName&) = default;                                                                               \
  ClassName& operator=(const ClassName&) = default;                                                                    \
  ClassName(ClassName&&) = default;                                                                                    \
  ClassName& operator=(ClassName&&) = default;
#define DEFAULT_COPY(ClassName)                                                                                        \
  ClassName(const ClassName&) = default;                                                                               \
  ClassName& operator=(const ClassName&) = default;

#endif // DEFINES_H
