# postfix_notation
Обратная польская нотация на Си

Переводит строку с выражением в инфиксной нотации в посфиксную нотацию, после чего считает выражение и возвращает результат. Предполагается, что строка, передающаяся в код полностью корректна и обработка ошибок производится во внешнем коде.

Принимает указатель на строку, возвращает число `double`.

Библиотека calc.h собирается целью `make`. Вызов функции `double res = from_infix_to_postfix(char *expression)`.
