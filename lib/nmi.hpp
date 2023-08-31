#ifndef NMI_HPP
#define NMI_HPP

extern "C"
#ifndef NONES
__attribute__((interrupt))
#endif
void nmi();

#endif // !NMI_HPP