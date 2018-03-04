#ifndef AVAKAR_BIGINT_TRAITS_H
#define AVAKAR_BIGINT_TRAITS_H

#if defined(_MSC_VER)

#include "msvc_x86_traits.h"
namespace avakar {
namespace _bigint {

using bigint_traits = msvc_x86_traits;

}
}

#else

#include "generic_traits.h"
#include <stdint.h>

namespace avakar {
namespace _bigint {

using bigint_traits = generic_traits<uint32_t, uint64_t>;

}
}

#endif

#endif // AVAKAR_BIGINT_TRAITS_H
