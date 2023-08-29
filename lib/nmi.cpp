#include "kb.hpp"

extern "C" __attribute__((interrupt)) void nmi()
{
    kb_handle_nmi();
    
}