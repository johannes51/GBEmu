#ifndef ILAYER_H
#define ILAYER_H

class IPixelBuffer;

class ILayer {
public:
  virtual ~ILayer() = default;

  virtual void draw(IPixelBuffer& buffer) = 0;

protected:
  ILayer() = default;
};

#endif // ILAYER_H
