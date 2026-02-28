#ifndef FOX_WAVE_GUARD_HPP
#define FOX_WAVE_GUARD_HPP

#include <QReadWriteLock>

inline QReadWriteLock& fox_wave_lock ()
{
  static QReadWriteLock lock;
  return lock;
}

#endif // FOX_WAVE_GUARD_HPP
