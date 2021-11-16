#pragma once

#include "Irq.h"

namespace core
{

    void setInterruptGroupPriority();
    void setIrqPriorityConfig(Irq irq, uint32_t priority);

}
