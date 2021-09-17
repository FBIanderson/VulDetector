operator delete(void *ptr, std::size_t size) noexcept {
	if (unlikely(ptr == nullptr)) {
