#include "calc.h"

double from_infix_to_postfix(char *exp) {
    queue *exp_q = create_queue(exp);
    queue *postfix = make_posfix_queue(exp_q);
    print_queue(postfix);
    double res = calculation_process(postfix);
    destroy(exp_q);
    destroy(postfix);
    return res;
}

void destroy(queue *root) {
    while (root) {
        root = root->next;
        free(root);
    }
}

void print_queue(queue *q) {
    while (q != NULL) {
        if (q->op[0] != '0') {
            if (q->op[1] != '0') {
                printf("%c%c ", q->op[0], q->op[1]);
            } else {
                printf("%c ", q->op[0]);
            }
        } else {
            printf("%.1f ", q->volume);
        }
        q = q->next;
    }
    printf("\n");
}
