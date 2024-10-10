#pragma once
#include <iostream>
#include <string>

/*时间类*/
class Timestamp
{
private:
    /* data */
    int64_t microSecondsSinceEpoch_;
public:
    Timestamp();
    explicit Timestamp(int64_t microSecondsSinceEpoch); // 防止隐式转换 （一般带参构造会加）
    static Timestamp now();
  void swap(Timestamp& that)
  {
    std::swap(microSecondsSinceEpoch_, that.microSecondsSinceEpoch_);
  }
    std::string toString() const;
};