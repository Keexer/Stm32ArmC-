#include <cstdlib>
#include <stdint.h>
#include <new>

void* operator new(size_t size) noexcept
{
    return malloc(size);
}

void operator delete(void* p) noexcept
{
    free(p);
}

void* operator new[](size_t size) noexcept
{
    return operator new(size);
}

void operator delete[](void* p) noexcept
{
    operator delete(p);
}

void* operator new(size_t size, std::nothrow_t) noexcept
{
    return operator new(size);
}

void operator delete(void* p, std::nothrow_t) noexcept
{
    operator delete(p);
}

void* operator new[](size_t size, std::nothrow_t) noexcept
{
    return operator new(size);
}

void operator delete[](void* p, std::nothrow_t) noexcept
{
    operator delete(p);
}

extern "C" void _exit(int)
{
  while (1);
}

extern "C" void* _sbrk(int incr)
{
  extern uint32_t _end;
  static uint32_t* heap_end;
  uint32_t* prev_heap_end;

  if (heap_end == 0)
  {
    heap_end = &_end;
  }

  prev_heap_end = heap_end;

  heap_end += incr;
  return (void*)prev_heap_end;
}
extern "C" int _kill(int, int)
{
  return -1;
}
extern "C" int _getpid()
{
  return 1;
}

#define DRN_ENTER_CRITICAL_SECTION(_usis) { _usis = taskENTER_CRITICAL_FROM_ISR(); }
#define DRM_EXIT_CRITICAL_SECTION(_usis) { taskEXIT_CRITICAL_FROM_ISR(_usis); }

void __malloc_lock(struct _reent* r)
{
  // lock recursive mutex
}

void __malloc_unlock(struct _reent* r)
{
  // unlock recursive mutex
}
