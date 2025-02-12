#include "Util.hpp"

#include <stdexcept>
#include <cstring>

void Util::ThrowErrno() {
	error_t e = errno;
	errno = 0;
	std::string msg = std::string(strerror(errno));
	if (errno != 0) {
		msg = "failed to retrieve error string. Errno value: ";
		msg += e;
	}
	throw std::runtime_error(msg);
}
