#include "calc.h"

queue *create_queue(char *exp) {
    queue *head = NULL;
    if (exp != NULL) {
        queue *process = NULL;
        char *final = exp + strlen(exp);
        for (char *p = exp; p <= final; p++) {
            if (!is_space(*p) && *p != '\n' && *p != '\0') {
                queue *tmp = create_node();
                if (tmp != NULL) {
                    if (p == exp) {
                        head = tmp;
                    }
                    if (is_num_char(*p)) {
                        tmp->volume = get_num_from_string(&p);
                    } else if (is_op_char(*p)) {
                        if (is_un_min(p, exp)) {
                            tmp->op[0] = '~';
                            tmp->priority = 5;
                        } else {
                            tmp->priority = priority_parser(*p);
                            tmp->op[0] = *p;
                        }
                    } else {
                        function_parser(&p, &tmp);
                    }
                    if (tmp == head) {
                        process = head;
                    } else {
                        process->next = tmp;
                        process = process->next;
                    }
                }
            }
        }
    }
    return head;
}

void function_parser(char **exp, queue **process) {
    if (memcmp(*exp, "cos", 3) == 0) {
        (*process)->op[0] = 'c';
        (*process)->op[1] = 'o';
        (*exp) += 2;
        (*process)->priority = 4.5;
    } else if (memcmp(*exp, "sin", 3) == 0) {
        (*process)->op[0] = 's';
        (*process)->op[1] = 'i';
        (*exp) += 2;
        (*process)->priority = 4.5;
    } else if (memcmp(*exp, "tan", 3) == 0) {
        (*process)->op[0] = 't';
        (*process)->op[1] = 'a';
        (*exp) += 2;
        (*process)->priority = 4.5;
    } else if (memcmp(*exp, "acos", 4) == 0) {
        (*process)->op[0] = 'a';
        (*process)->op[1] = 'c';
        (*exp) += 3;
        (*process)->priority = 4.5;
    } else if (memcmp(*exp, "asin", 4) == 0) {
        (*process)->op[0] = 'a';
        (*process)->op[1] = 's';
        (*exp) += 3;
        (*process)->priority = 4.5;
    } else if (memcmp(*exp, "atan", 4) == 0) {
        (*process)->op[0] = 'a';
        (*process)->op[1] = 't';
        (*exp) += 3;
        (*process)->priority = 4.5;
    } else if (memcmp(*exp, "sqrt", 4) == 0) {
        (*process)->op[0] = 's';
        (*process)->op[1] = 'q';
        (*exp) += 3;
        (*process)->priority = 4.5;
    } else if (memcmp(*exp, "ln", 2) == 0) {
        (*process)->op[0] = 'l';
        (*process)->op[1] = 'n';
        (*exp) += 1;
        (*process)->priority = 4.5;
    } else if (memcmp(*exp, "log", 3) == 0) {
        (*process)->op[0] = 'l';
        (*process)->op[1] = 'o';
        (*exp) += 2;
        (*process)->priority = 4.5;
    }
}

int is_un_min(const char *p, const char *head) {
    int res = INCORRECT;
    if (*p == '-' && (p == head || *(p-1) == '(')) {
        res = CORRECT;
    }
    return res;
}

int priority_parser(char operation) {
    int pr_num = 0;
    switch (operation) {
        case '(':
            pr_num = 1;
            break;
        case '+':
        case '-':
            pr_num = 2;
            break;
        case '*':
        case '/':
        case '%':
            pr_num = 3;
            break;
        case '^':
            pr_num = 4;
            break;
        case ')':
            pr_num = 6;
            break;
    }
    return pr_num;
}

queue *create_node() {
    queue *new_queue = (queue *)calloc(1, sizeof(queue));
    if (new_queue != NULL) {
        new_queue->op[0] = '0';
        new_queue->op[1] = '0';
        new_queue->volume = -1;
        new_queue->priority = 0;
        new_queue->next = NULL;
    }
    return new_queue;
}

int is_op_char(char exp) {
    int res = INCORRECT;
    if (exp == '%' || exp == '+' || exp == '-' || exp == '/' || exp == '*' || exp == '^' ||
        exp == '(' || exp == ')') {
        res = CORRECT;
    }
    return res;
}

int is_num_char(char c) {
    int res = INCORRECT;
    if ((48 <= (int)(c) && (int)(c) <= 57) || c == '.') {
        res = CORRECT;
    }
    return res;
}

int is_space(char c) {
    int res = INCORRECT;
    if (c == ' ') {
        res = CORRECT;
    }
    return res;
}

double get_num_from_string(char **exp) {
    double res = 0;
    char *num = (char *)malloc(sizeof(char));
    if (num != NULL) {
        int size = 1;
        while (is_num_char(**exp)) {
            num[size - 1] = **exp;
            size++;
            char *tmp = (char *)realloc(num, size);
            if (tmp != NULL) {
                num = tmp;
            }
            (*exp)++;
        }
        if (num != NULL) {
            num[size - 1] = '\0';
            res = atof(num);
            free(num);
        }
        (*exp)--;
    }
    return res;
}
