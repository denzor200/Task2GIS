#include "config.hpp"
#include "value_def.hpp"

namespace json_client {
namespace parser {
    BOOST_SPIRIT_INSTANTIATE(value_type, iterator_type, context_type);
} // end of namespace parser
} // end of namespace json_client
