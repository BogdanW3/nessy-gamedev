#ifndef IRQ_HPP
#define IRQ_HPP

extern "C"
#ifndef NONES
__attribute__((interrupt))
#endif
void irq();

#endif // !IRQ_HPP