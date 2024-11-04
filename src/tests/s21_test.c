#include "s21_test.h"

int main() {
  int failed = 0;

  Suite* s21_calc_test[] = {s21_calculation_test(), s21_err_test(), NULL};

  for (int i = 0; s21_calc_test[i] != NULL; i++) {
    printf("-----------------------------------------------\n");

    SRunner* sr = srunner_create(s21_calc_test[i]);
    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_NORMAL);

    failed += srunner_ntests_failed(sr);

    srunner_free(sr);
  }

  if (failed == 0) {
    printf(
        "\033[32m------------------- SUCCESS -------------------\033[0m\n\n");
  } else {
    printf("\033[31m------------------ FAILED: %d -----------------\033[0m\n\n",
           failed);
  }

  return (failed == 0) ? 0 : 1;
}