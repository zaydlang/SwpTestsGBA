#include <gba_console.h>
#include <gba_dma.h>
#include <gba_timers.h>
#include <gba_video.h>
#include <gba_input.h>
#include <stdio.h>

uint32_t dma_source = 0xCAFEBABE;

__attribute((section(".ewram"))) 
uint32_t test_result;

__attribute__((naked)) 
__attribute__((target("arm"))) 
__attribute__((section(".iwram")))
int run_swp_test() {\
__asm__(\
    "push {r4 - r8}\n"\
\
    "ldr r0, =#0x040000D4\n"\
    "ldr r2, =#0xDEADBEEF\n"\
\
    "ldr r1, =dma_source\n"\
    "str r1, [r0], #4\n"\
\
    "ldr r3, =test_result\n"\
    "str r3, [r0], #4\n"\
\
    "ldr r1, =#0x84000001\n"\
    "str r1, [r0]\n"\
\
    "swp r0, r2, [r3]\n"\
\
    "ldr r0, [r3]\n"\
    "bx lr\n"\
);
}

int main(void) {
	consoleDemoInit();

    uint32_t result = run_swp_test();
    printf("%08lx", result);

    while (1);
}