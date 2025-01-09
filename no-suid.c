#include <stdlib.h>
#include <unistd.h>
#include <signal.h>


/*@
  terminates \true;
  exits 1 == \exit_status;
  assigns \nothing;
*/
static void catch_alrm(const int signal){
  // This is a signal handler. Code checkers may erroneously detect it as dead code.
  (void) signal;      // Suppress unused parameter warning
  exit(EXIT_FAILURE);
}

/*@
  terminates \true;
  assigns \result;
  ensures \result == 0 ∨ \result == 1;
*/
int main(void){
  const unsigned int ONE_SECOND = (unsigned int) 1;
  signal(SIGALRM, catch_alrm);  // Send timer issues to catch_alrm()
  alarm(ONE_SECOND);
  const uid_t real = getuid();
  const uid_t effective = geteuid();
  const int value = (int)!(real == effective);
  return value;
}

