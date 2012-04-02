/*
 * algo for dynamic programming
 */
#ifndef DP_ARRAY_H_
#define DP_ARRAY_H_
#include <cassert>
template<class T>
class TwoDArray {

  public:
    TwoDArray(unsigned int m, unsigned int n) : 
        _m(m), _n(n), _dat(NULL) {
      _dat = new T[m*n];
    }

    inline const T& get(int i, int j) {
      assert(i >= 0 && i < _m);
      assert(j >= 0 && j < _n);
      return _dat[i*_n+j];
    }

    inline void set(int i, int j, const T& val) {
      assert(i >= 0 && i < _m);
      assert(j >= 0 && j < _n);
      _dat[i*_n+j] = val;
    }

    inline T& operator() (int i, int j) {
      assert(i >= 0 && i < _m);
      assert(j >= 0 && j < _n);
      return _dat[i*_n+j];
    }

    inline T operator() (int i, int j) const {
      assert(i >= 0 && i < _m);
      assert(j >= 0 && j < _n);
      return _dat[i*_n+j];
    }

    ~TwoDArray() {
      if (_dat) {
        delete _dat;
        _dat = NULL;
      }
    }

  private:
    int _m;
    int _n;
    T* _dat;
};

#endif // DP_ARRAY_H_
