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

void operator delete(void* p, std::size_t)
{
  operator delete(p);
}

void operator delete[](void* p, std::size_t)
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

/**
  \brief   Enable IRQ Interrupts
  \details Enables IRQ interrupts by clearing the I-bit in the CPSR.
           Can only be executed in Privileged modes.
           This is a shorter instruction to set the PRIMASK bit to 1.
 */
__attribute__((always_inline)) static inline void enable_irq(void)
{
  __asm volatile ("cpsie i" : : : "memory");
}


/**
  \brief   Disable IRQ Interrupts
  \details Disables IRQ interrupts by setting the I-bit in the CPSR.
           Can only be executed in Privileged modes.
           This is a shorter instruction to set the PRIMASK bit to 0.
 */
__attribute__((always_inline)) static inline void disable_irq(void)
{
  __asm volatile ("cpsid i" : : : "memory");
}

void __malloc_lock(struct _reent*)
{
  disable_irq();
}

void __malloc_unlock(struct _reent*)
{
  enable_irq();
}
