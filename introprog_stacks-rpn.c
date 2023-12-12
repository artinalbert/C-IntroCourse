#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "introprog_stacks-rpn.h"
#include "introprog_input_stacks-rpn.h"

void stack_push(stack* calc_stack, float value) {
    stack_element* new_element = (stack_element*) malloc(sizeof(stack_element));
    new_element->value = value;
    new_element->next = calc_stack->top;
    calc_stack->top = new_element;
}

float stack_pop(stack* calc_stack) {
    if (calc_stack->top == NULL) {
        return NAN;
    } else {
        stack_element* current_element = calc_stack->top;
        float popped_value = current_element->value;
        calc_stack->top = current_element->next;
        free(current_element);
        return popped_value;
    }
}

void process(stack* calc_stack, char* token) {
    if (is_number(token)) {
        stack_push(calc_stack, atof(token));
    } else if (is_add(token)) {
        float first = stack_pop(calc_stack);
        float second = stack_pop(calc_stack);
        stack_push(calc_stack, first + second);
    } else if (is_sub(token)) {
        float first = stack_pop(calc_stack);
        float second = stack_pop(calc_stack);
        stack_push(calc_stack, second - first); // Note the order for correct subtraction
    } else if (is_mult(token)) {
        float first = stack_pop(calc_stack);
        float second = stack_pop(calc_stack);
        stack_push(calc_stack, first * second);
    }
}

stack* create_stack() {
    stack* new_stack = (stack*) malloc(sizeof(stack));
    new_stack->top = NULL;
    return new_stack;
}
