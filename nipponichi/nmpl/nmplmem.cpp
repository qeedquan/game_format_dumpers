#include <cstdio>
#include <cstdlib>

#if defined(_MSC_VER)
#define aligned_alloc _aligned_malloc
#endif

namespace Nmpl::MemoryInterface
{

__declspec(dllexport) void *allocateMemory(size_t size)
{
	return calloc(1, size);
}

__declspec(dllexport) bool onHeap(void const *mem)
{
	return false;
}

__declspec(dllexport) bool onLargeHeap(void const *mem)
{
	return false;
}

__declspec(dllexport) bool onSmallHeap(void const *mem)
{
	return false;
}

__declspec(dllexport) bool memoryActive()
{
	return false;
}

__declspec(dllexport) size_t heapSizeSmall(void)
{
	return 0;
}

__declspec(dllexport) void outputLargeMemoryList()
{
}

__declspec(dllexport) void *allocateMemoryAligned(size_t size, size_t alignment)
{
	return aligned_alloc(alignment, size);
}

__declspec(dllexport) void *reallocateMemory(void *ptr, size_t newsize)
{
	return nullptr;
}

__declspec(dllexport) void freeMemory(void *ptr)
{
}

__declspec(dllexport) void memoryTerminate(void)
{
}

__declspec(dllexport) void outputSmallMemoryList(void)
{
}

__declspec(dllexport) size_t heapSizeLarge(void)
{
	return 0;
}

__declspec(dllexport) void memoryInitialize(void *, size_t const &, void *, size_t const &, size_t)
{
}

__declspec(dllexport) size_t allocatedSize(void const *)
{
	return 0;
}

__declspec(dllexport) void *heapAddrLarge(void)
{
	return nullptr;
}

__declspec(dllexport) void *heapAddrSmall(void)
{
	return nullptr;
}

__declspec(dllexport) void setEveryLarge(bool)
{
}

__declspec(dllexport) void invariant(void)
{
}

} // namespace Nmpl::MemoryInterface
