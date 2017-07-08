/*
 *  $Id$
 */
#include <iomanip>
#include "TU/simd/cvt_iterator.h"
#include "TU/simd/load_store_iterator.h"

namespace TU
{
namespace simd
{
template <class S, class T> void
doJob()
{
    using value_type
	= typename cvt_mask_iterator<T, load_iterator<S> >::value_type;
    
    constexpr S	f = S(~0);
    S		src[] = {0, f, 0, f, 0, 0, f, f,
			 0, 0, 0, 0, f, f, f, f,
			 0, f, 0, f, 0, 0, f, f,
			 0, 0, 0, 0, f, f, f, f};

    std::cout << std::hex;
    std::copy(make_cvt_mask_iterator<T>(make_accessor(std::cbegin(src))),
	      make_cvt_mask_iterator<T>(make_accessor(std::cend(src))),
	      std::ostream_iterator<value_type>(std::cout, " "));
    std::cout << std::endl;
    empty();
}
    
}
}

int
main()
{
    using namespace	std;
    using namespace	TU;
    
    cerr << "--- src: u_int8_t, dst: unsinged ---" << endl;
    simd::doJob<u_int8_t,  u_int8_t >();
    simd::doJob<u_int8_t,  u_int16_t>();
    simd::doJob<u_int8_t,  u_int32_t>();
    simd::doJob<u_int8_t,  u_int64_t>();

    cerr << "--- src: u_int16_t, dst: unsinged ---" << endl;
    simd::doJob<u_int16_t, u_int8_t >();
    simd::doJob<u_int16_t, u_int16_t>();
    simd::doJob<u_int16_t, u_int32_t>();
    simd::doJob<u_int16_t, u_int64_t>();

    cerr << "--- src: u_int32_t, dst: unsinged ---" << endl;
    simd::doJob<u_int32_t, u_int8_t >();
    simd::doJob<u_int32_t, u_int16_t>();
    simd::doJob<u_int32_t, u_int32_t>();
    simd::doJob<u_int32_t, u_int64_t>();

    cerr << "--- src: u_int64_t, dst: unsinged ---" << endl;
#if defined(NEON)
    simd::doJob<u_int64_t, u_int8_t >();
    simd::doJob<u_int64_t, u_int16_t>();
    simd::doJob<u_int64_t, u_int32_t>();
#endif
    simd::doJob<u_int64_t, u_int64_t>();

#if defined(SSE2) || defined(NEON)
    cerr << "--- src: unsigned, dst: float ---" << endl;
    simd::doJob<u_int8_t,  float>();
    simd::doJob<u_int16_t, float>();
#  if !defined(AVX) || defined(AVX2)
    simd::doJob<u_int32_t, float>();
#  endif
    cerr << "--- src: float, dst: unsigned ---" << endl;
    simd::doJob<float, u_int8_t >();
    simd::doJob<float, u_int16_t>();
#  if !defined(AVX) || defined(AVX2)
    simd::doJob<float, u_int32_t>();
#  endif
#endif

#if defined(SSE2)
    cerr << "--- src: unsigned, dst: double ---" << endl;
    simd::doJob<u_int8_t,  double>();
    simd::doJob<u_int16_t, double>();
    simd::doJob<u_int32_t, double>();
#  if !defined(AVX) || defined(AVX2)
    simd::doJob<u_int64_t, double>();

    cerr << "--- src: double, dst: unsigned ---" << endl;
    simd::doJob<double, u_int64_t>();
#  endif
#endif

    return 0;
}
