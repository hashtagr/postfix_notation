#include "calc.h"
#include <limits.h>
#include <ctype.h>
#include <check.h>

START_TEST(s21_smart_TEST) {
    double res = from_infix_to_postfix("1+2-3");
    ck_assert_double_eq(res, 0);

    res = from_infix_to_postfix("1-2*12-3^2");
    ck_assert_double_eq(res, -32);

    res = from_infix_to_postfix("sin(12)-3");
    ck_assert_double_eq(res, (sin(12)-3));

    res = from_infix_to_postfix("ln(12)^3-1*(-12+5)");
    ck_assert_double_eq(res, pow(log(12), 3.0) - 1 * (-12 + 5));

    res = from_infix_to_postfix("1+2-3");
    ck_assert_double_eq(res, 0);

    res = from_infix_to_postfix("cos(1)");
    ck_assert_double_eq(res, cos(1));

    res = from_infix_to_postfix("tan( 5 )");
    ck_assert_ldouble_eq_tol(res, tan(5), 1e-6);
    
    res = from_infix_to_postfix("atan(1)");
    ck_assert_double_eq(res, atan(1));

    res = from_infix_to_postfix("acos(1)");
    ck_assert_double_eq(res, acos(1));

    res = from_infix_to_postfix("5%2");
    ck_assert_double_eq(res, 1);

    res = from_infix_to_postfix("sqrt(-3)");
    ck_assert_ldouble_nan(res);

    res = from_infix_to_postfix("log(18)");
    ck_assert_double_eq(res, log10(18));

    res = from_infix_to_postfix("123/13");
    ck_assert_double_eq(res, 123.0/13);

    res = from_infix_to_postfix("1+2-3");
    ck_assert_double_eq(res, 1+2-3);

    res = from_infix_to_postfix("cos(cos(12))-3-5");
    ck_assert_double_eq(res, cos(cos(12))-3-5);

    res = from_infix_to_postfix("sin(3^3-ln(12))-12+(-11+20)");
    ck_assert_double_eq(res, sin(27-log(12))-12+(-11+20));

    res = from_infix_to_postfix("sqrt(atan(12))");
    ck_assert_double_eq(res, sqrt(atan(12)));

    res = from_infix_to_postfix("2^2^3");
    ck_assert_double_eq(res, 256);

    res = from_infix_to_postfix("asin(1)");
    ck_assert_double_eq(res, asin(1));
}
END_TEST

int main(void) {
    Suite *suite = suite_create("S21_Debuger");
    SRunner *srunner = srunner_create(suite);

    TCase *s21_smart_calc = tcase_create("s21_smart_calc");
    suite_add_tcase(suite, s21_smart_calc);
    tcase_add_test(s21_smart_calc, s21_smart_TEST);

    srunner_run_all(srunner, CK_VERBOSE);
    int number_failed = srunner_ntests_failed(srunner);
    srunner_free(srunner);

    return number_failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
