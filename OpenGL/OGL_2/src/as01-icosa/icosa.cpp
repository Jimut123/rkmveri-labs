#include <iostream>
#include <climits>
// https://stackoverflow.com/a/776550/3770260
template <typename INT>
#if __cplusplus > 201100L // Apply constexpr to C++ 11 to ease optimization
constexpr
#endif // See also https://stackoverflow.com/a/7269693/3770260
INT rol(INT val, size_t len) {
#if __cplusplus > 201100L && _wp_force_unsigned_rotate // Apply unsigned check C++ 11 to make sense
    static_assert(std::is_unsigned<INT>::value,
                  "Rotate Left only makes sense for unsigned types");
#endif
    return (val << len) | ((unsigned) val >> (-len & (sizeof(INT) * CHAR_BIT - 1)));
}

int main()
{
    std::cout<<rol(123,3)<<std::endl;
    return EXIT_SUCCESS;
}