#include "panic.h"

static bool panicking = false;

void _khalt(int reason, const char* msg, const char* fcn, const char* file, const char* line) {
  // recursive panic
  if(panicking) {
    __KHALT;
  }
  panicking = true;

  // re-initialize video, in case something fails pre-init
  kinit_video();
  ktextcolor(KBLACK, KRED);
  kclear();
  
#define TEN "          "
#define TWENTY TEN TEN
#define THIRTY TEN TWENTY
#define FIFTY TWENTY THIRTY

  /* RED SCREEN OF CERTAIN DOOM */
  kputs("Despite your violent" " behavior, the only " TEN "  ####   ####       \n"
        "thing you've managed" " to break so far is " TEN " ###### ######      \n"
        "my heart.           " THIRTY                     " #############      \n"
                                               FIFTY      "  ###########       \n"
                                               FIFTY      "   #########        \n"
                                               FIFTY      "    #######         \n"
                                               FIFTY      "     #####          \n"
                                               FIFTY      "      ###           \n"
                                               FIFTY      "       #            \n");
#undef TEN
#undef TWENTY
#undef THIRTY
#undef FIFTY

  kputs(STOP_MSG "\n\n");

  /* this is why I need printf :( */

  if(reason == UNHANDLED_EXCEPTION) {
    kputs("KERNEL PANIC: ");
    kputs(msg);
    kputs("\n  Called from "); kputs(fcn); kputs(" ("); kputs(file); kputs(":"); kputs(line); kputs(")\n");
  } else if(reason == ASSERTION_FAILED) {
    kputs("ASSERTION FAILED: ");
    kputs(msg);
    kputs("\n  in "); kputs(fcn); kputs(" ("); kputs(file); kputs(":"); kputs(line); kputs(")\n");
  } else if(reason == UNKNOWN_FAILURE) {
    kputs("UNKNOWN FAILURE: ");
    kputs(msg);
  }

  __KHALT;

}
