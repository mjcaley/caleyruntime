// #pragma once

// #include <stdbool.h>
// #include <stdlib.h>


// struct alloc;

// typedef struct shadow_stack
// {
//     size_t top;
//     size_t length;
//     alloc* stack[];
// } shadow_stack;


// shadow_stack* shadow_stack_new(int stack_size, bool* success)
// {
//     shadow_stack* stack = calloc(1, sizeof(*stack) + sizeof(alloc*) * stack_size);
//     if (stack)
//     {
//         *success = true;
//         stack->top = 0;
//         stack->length = stack_size;
//     }
//     else
//     {
//         *success = false;
//     }
//     return stack;
// }


// bool shadow_stack_push(shadow_stack* stack, alloc* allocation)
// {
//     if (stack->top == stack->length)
//     {
//         return false;
//     }

//     stack->top += 1;
//     stack->stack[stack->top] = allocation;

//     return true;
// }


// bool shadow_stack_pop(shadow_stack* stack)
// {
//     if (stack->top == 0)
//     {
//         return false;
//     }

//     stack->stack[stack->top] = NULL;
//     stack->top -= 1;

//     return true;
// }


// alloc* shadow_stack_top(shadow_stack* stack)
// {
//     if (stack->top == 0)
//     {
//         return NULL;
//     }
//     else
//     {
//         return stack->stack[stack->top];
//     }
// }
