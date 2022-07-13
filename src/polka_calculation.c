#include "calc.h"

double calculation_process(queue *exp) {
    double res = 0;
    queue *stack = NULL;
    if (exp != NULL) {
        while (exp != NULL) {
            if (exp->op[0] == '0') {
                stack_calc_push(&stack, exp->volume);
            } else {
                stack_calc_pop(&stack, exp->op);
            }
            exp = exp->next;
        }
        res = stack->volume;
        destroy(stack);
    }
    return res;
}

void stack_calc_push(queue **stack, double num) {
    queue *tmp = create_node();
    if (tmp != NULL) {
        tmp->volume = num;
        if (*stack == NULL) {
            *stack = tmp;
        } else {
            tmp->next = *stack;
            *stack = tmp;
        }
    }
}

void stack_calc_pop(queue **stack, char *op) {
    if (*stack != NULL) {
        double second = (*stack)->volume;
        queue *tmp = *stack;
        *stack = (*stack)->next;
        free(tmp);
        if (*stack == NULL || !is_op_char(op[0])) {
            stack_calc_push(stack, calc_parser(0, second, op));
        } else {
            double first = (*stack)->volume;
            queue *tmp = *stack;
            *stack = (*stack)->next;
            free(tmp);
            stack_calc_push(stack, calc_parser(first, second, op));
        }
    }
}

double calc_parser(double first, double second, char *op) {
    double res = 0;
    if (op[0] == '+') {
        res = first + second;
    } else if (op[0] == '-') {
        res = first - second;
    } else if (op[0] == '~') {
        res = first - second;
    } else if (op[0] == '^') {
        res = pow(first, second);
    } else if (op[0] == '*') {
        res = first * second;
    } else if (op[0] == '/') {
        res = first / second;
    } else if (op[0] == '%') {
        res = fmod(first, second);
    } else if (memcmp(op, "co", 2) == 0) {
        res = cos(second - first);
    } else if (memcmp(op, "si", 2) == 0) {
        res = sin(second - first);
    } else if (memcmp(op, "ta", 2) == 0) {
        res = tan(second - first);
    } else if (memcmp(op, "ac", 2) == 0) {
        res = acos(second - first);
    } else if (memcmp(op, "as", 2) == 0) {
        res = asin(second - first);
    } else if (memcmp(op, "at", 2) == 0) {
        res = atan(second - first);
    } else if (memcmp(op, "sq", 2) == 0) {
        res = sqrt(second - first);
    } else if (memcmp(op, "ln", 2) == 0) {
        res = log(second - first);
    } else if (memcmp(op, "lo", 2) == 0) {
        res = log10(second - first);
    }
    printf("%f %c %f = %f\n", first, op[0], second, res);
    return res;
}
