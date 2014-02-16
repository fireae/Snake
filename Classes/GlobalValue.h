#ifndef GLOBAL_VALUE_H
#define GLOBAL_VALUE_H

class GlobalValue
{
public:
  static GlobalValue *sharedValue();
  static void destroy();
public:
  bool m_bMusicOn;
  
private:
  static GlobalValue *pValue;
  GlobalValue(){ m_bMusicOn = true;}
  ~GlobalValue(){}
};

#endif //GLOBAL_VALUE_H