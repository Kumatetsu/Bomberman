#include <math.h>
#include "time_tick.h"

static int SEC_SLEEP = 0;
// hardcoded tick_time
// set it to 0 to allow dynamic definition
// avec un tick à 5000ms, ca s'affiche bien, ca tourne
// avec un tick à 4600ms, ca s'affiche presque bien, ca blink un peu
// avec un tick à 4500ms, ca blink, le joueur connecté s'affiche, les autres aussi en blinkant...
// avec un tick à 4000ms, le bomber ne s'affiche plus
// avec un tick à 1000 ms soit 10 ticks par secondes
// je suis monté à + de 4 millions sur 20 min sans soucis
static int MILLI_SLEEP = 4550;
static int SEC_TO_MILLI = 0;
static int NANO_SLEEP = 0;
static int SLEEP_MS = 0;
static int SEC_IN_TICK = 0;

// définis et retourne la static des secondes
// composant le temps entre 2 ticks
int	sec_sleep(int seconds)
{
  if (SEC_SLEEP == 0)
    SEC_SLEEP = seconds;
  return SEC_SLEEP;
}

// définis et retourne la static des milliseconds
// composant le temps entre 2 ticks
int	milli_sleep(int milliseconds)
{
  if (MILLI_SLEEP == 0)
    MILLI_SLEEP = milliseconds;
  return MILLI_SLEEP;
}

// retourne SEC_SLEEP en ms
// n'initialise pas car passe par le singleton sec_sleep
int	sec_to_milli()
{
  SEC_TO_MILLI = sec_sleep(0) * 1000;
  return SEC_TO_MILLI;
}

// retourne SEC_SLEEP + MILLI_SLEEP en nanosecond
// passe par les singletons
int	nano_sleep()
{
  int	sec;
  int	ms;

  sec = sec_to_milli(0);
  ms = milli_sleep(0);
  NANO_SLEEP = (sec + ms) * 1000000;
  return NANO_SLEEP;
}

// défini et retourne le sleep d'un tick en millisecondes
// si les fonctions sec_sleep et/ou milli_sleep ont déjà
// été appellées, les paramètres correspondants seront ignorés
int	sleep_ms(int sec, int ms)
{
  sec_sleep(sec);
  SLEEP_MS = sec_to_milli() + milli_sleep(ms);
  return SLEEP_MS;
}

// Doit être appellé après la définition du sleep
// retourne le nombre de tick pour une seconde (truncate + 1)
int	sec_in_tick()
{
  SEC_IN_TICK = trunc(1000 / sleep_ms(0, 0)) + 1;
  return SEC_IN_TICK;
}
