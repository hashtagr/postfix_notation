#include "calc.h"

queue *make_posfix_queue(queue *exp) {
    queue *head = NULL;
    queue *process = NULL;
    queue *stack = NULL;

    if (exp != NULL) {
        while (exp != NULL) {
            if (exp->volume != -1) {
                create_process_node(&process);
                process->volume = exp->volume;
            } else if ((stack == NULL && exp->op[0] != '0') || exp->priority == 1) {
                stack_push(&stack, exp);
            } else if (stack->op[0] == '^' && exp->op[0] == '^') {
                stack_push(&stack, exp);
            } else if (exp->priority != 6 && stack->priority < exp->priority) {
                stack_push(&stack, exp);
            } else if (exp->priority == 6) {
                stack_pop(&stack, &process, exp->priority);
            } else if (stack->priority >= exp->priority) {
                stack_pop(&stack, &process, exp->priority);
                stack_push(&stack, exp);
            }
            if (head == NULL) {
                head = process;
            }
            exp = exp->next;
        }
    }
    while (stack != NULL) {
        process->next = stack;
        stack = stack->next;
        process = process->next;
    }
    destroy(exp);
    return head;
}

void stack_push(queue **stack, queue *exp) {
    queue *tmp = create_node();
    if (tmp != NULL) {
        tmp->op[0] = exp->op[0];
        tmp->op[1] = exp->op[1];
        tmp->priority = exp->priority;
        if (*stack == NULL) {
            *stack = tmp;
        } else {
            tmp->next = *stack;
            *stack = tmp;
        }
    }
}

void stack_pop(queue **stack, queue **process, int priority) {
    if (stack != NULL && process != NULL) {
        if (priority == 6) {
            while ((*stack)->op[0] != '(') {
                (*process)->next = *stack;
                *stack = (*stack)->next;
                *process = (*process)->next;
            }
            queue *tmp = *stack;
            *stack = (*stack)->next;
            free(tmp);
        } else {
            while (*stack != NULL && (*stack)->priority >= priority) {
                (*process)->next = *stack;
                *stack = (*stack)->next;
                *process = (*process)->next;
            }
        }
    }
}

void create_process_node(queue **process) {
    if (*process == NULL) {
        *process = create_node();
    } else {
        (*process)->next = create_node();
        *process = (*process)->next;
    }
}
