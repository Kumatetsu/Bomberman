#include <windows.h>    /* WinAPI */

/* Windows sleep in 100ns units */
int windowsNanoSleep(long ns){
    /* Declarations */
    HANDLE timer;    /* Timer handle */
    LARGE_INTEGER li;    /* Time defintion */
    /* Create timer */
    if (!(timer = CreateWaitableTimer(NULL, TRUE, NULL)))
        return 0;
    /* Set timer properties */
    li.QuadPart = -ns;
    if (!SetWaitableTimer(timer, &li, 0, NULL, NULL, FALSE)) {
        CloseHandle(timer);
        return 0;
    }
    /* Start & wait for timer */
    WaitForSingleObject(timer, INFINITE);
    /* Clean resources */
    CloseHandle(timer);
    /* Slept without problems */
    return 1;
}