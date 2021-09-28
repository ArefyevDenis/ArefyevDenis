#ifndef NON_COPYABLE_H
#define NON_COPYABLE_H


class Non_copyable
{
public:
  Non_copyable();

  Non_copyable(const Non_copyable&) = delete;
  Non_copyable& operator = (const Non_copyable&) = delete;

  Non_copyable(Non_copyable&&) = delete;
  Non_copyable& operator = (Non_copyable&&)= delete;

   ~Non_copyable();

};

#endif // NON_COPYABLE_H
