#ifndef _generic_exception_h
#define _generic_exception_h

#include "lib_base.h"

class generic_exception : public std::exception
{

  public:

    generic_exception( std::string where, int err_code , bool fatal ) : where_(where) , errcode_(err_code) ,fatal_(fatal) {}

      inline int get_errcode()
        {
            return errcode_;
        }

      inline bool is_fatal()
        {
          return (fatal_ == true ? true : false);
        }

      inline std::string get_where()
        {
          return where_;
        }

        ~generic_exception() throw () { }

  private:

    std::string where_;
    int errcode_;
    bool fatal_;

};

#endif /* _generic_exception_h */
