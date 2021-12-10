#include <iostream>

/**
 * @brief Declares a new variable of the passed type "dataType" with
 *        the passed name "varType" and defines two functions, a getter
 *        and a setter, with names depending on the passed variable name.
 *        '##' is used to concatenate the name to 'set_', without '##' 
 *        the function name would simply be 'set_varType'.
 *  
 */
#define MAKEVAR(varType, dataType) dataType varType; \
                void set_##varType(dataType val) { varType = val; }; \
                dataType get_##varType(void) { return varType; };

MAKEVAR(weight, int)
MAKEVAR(price, float)

int main(void) {
  set_weight(100);
  set_price(1.25);
  std::cout << "Weight: " << get_weight() << ", Price: " << get_price() << std::endl;
}
