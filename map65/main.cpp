#include <fftw3.h>
#ifdef QT5
#include <QtWidgets>
#else
#include <QtGui>
#endif
#include <QApplication>

#include "Detector/FftCompat.hpp"
#include "revision_utils.hpp"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
  QApplication a {argc, argv};
  // Override programs executable basename as application name.
  a.setApplicationName ("MAP65");
  a.setApplicationVersion ("3.1");
  // switch off as we share an Info.plist file with WSJT-X
  a.setAttribute (Qt::AA_DontUseNativeMenuBar);
  MainWindow w;
  w.show ();
  QObject::connect (&a, &QApplication::lastWindowClosed, &a, &QApplication::quit);
  auto result = a.exec ();

  // clean up lazily initialized FFTW3 resources
  {
    decodium::fft_compat::cleanup ();
  }
  fftwf_forget_wisdom ();
  fftwf_cleanup ();

  return result;
}
