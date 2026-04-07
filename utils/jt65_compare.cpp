#include <QByteArray>
#include <QCoreApplication>
#include <QString>
#include <QStringList>

#include <cstdio>

#include "Modulator/FtxMessageEncoder.hpp"

namespace
{

QByteArray fixed_22 (QString const& text)
{
  QByteArray latin = text.left (22).toLatin1 ();
  if (latin.size () < 22)
    {
      latin.append (QByteArray (22 - latin.size (), ' '));
    }
  return latin;
}

bool test_message (QString const& message, bool check_only)
{
  QByteArray const input = fixed_22 (message);

  decodium::txmsg::EncodedMessage const encoded =
      decodium::txmsg::encodeJt65 (QString::fromLatin1 (input.constData (), 22), check_only);

  if (!encoded.ok)
    {
      std::fprintf (stderr, "C++ JT65 encoder failed for '%s'\n", input.constData ());
      return false;
    }

  if (!check_only && encoded.tones.size () != 126)
    {
      std::fprintf (stderr,
                    "tone count mismatch for '%s': expected 126 got %d\n",
                    input.constData (), static_cast<int> (encoded.tones.size ()));
      return false;
    }

  return true;
}

}  // namespace

int main (int argc, char** argv)
{
  QCoreApplication app {argc, argv};

  QStringList const kMessages {
    QStringLiteral ("CQ WB9XYZ EN34"),
    QStringLiteral ("CQ DX WB9XYZ EN34"),
    QStringLiteral ("QRZ WB9XYZ EN34"),
    QStringLiteral ("KA1ABC WB9XYZ EN34"),
    QStringLiteral ("KA1ABC WB9XYZ RO"),
    QStringLiteral ("KA1ABC WB9XYZ -21"),
    QStringLiteral ("KA1ABC WB9XYZ R-19"),
    QStringLiteral ("KA1ABC WB9XYZ RRR"),
    QStringLiteral ("KA1ABC WB9XYZ 73"),
    QStringLiteral ("KA1ABC WB9XYZ"),
    QStringLiteral ("CQ 010 WB9XYZ EN34"),
    QStringLiteral ("CQ 999 WB9XYZ EN34"),
    QStringLiteral ("CQ EU WB9XYZ EN34"),
    QStringLiteral ("CQ WY WB9XYZ EN34"),
    QStringLiteral ("1A/KA1ABC WB9XYZ"),
    QStringLiteral ("E5/KA1ABC WB9XYZ"),
    QStringLiteral ("KA1ABC 1A/WB9XYZ"),
    QStringLiteral ("KA1ABC E5/WB9XYZ"),
    QStringLiteral ("KA1ABC/P WB9XYZ"),
    QStringLiteral ("KA1ABC/A WB9XYZ"),
    QStringLiteral ("KA1ABC WB9XYZ/P"),
    QStringLiteral ("KA1ABC WB9XYZ/A"),
    QStringLiteral ("CQ KA1ABC/P"),
    QStringLiteral ("CQ WB9XYZ/A"),
    QStringLiteral ("QRZ KA1ABC/P"),
    QStringLiteral ("QRZ WB9XYZ/A"),
    QStringLiteral ("DE KA1ABC/P"),
    QStringLiteral ("DE WB9XYZ/A"),
    QStringLiteral ("CQ 1A/KA1ABC"),
    QStringLiteral ("CQ E5/KA1ABC"),
    QStringLiteral ("DE 1A/KA1ABC"),
    QStringLiteral ("DE E5/KA1ABC"),
    QStringLiteral ("QRZ 1A/KA1ABC"),
    QStringLiteral ("QRZ E5/KA1ABC"),
    QStringLiteral ("CQ WB9XYZ/1A"),
    QStringLiteral ("CQ WB9XYZ/E5"),
    QStringLiteral ("QRZ WB9XYZ/1A"),
    QStringLiteral ("QRZ WB9XYZ/E5"),
    QStringLiteral ("DE WB9XYZ/1A"),
    QStringLiteral ("DE WB9XYZ/E5"),
    QStringLiteral ("CQ A000/KA1ABC FM07"),
    QStringLiteral ("CQ ZZZZ/KA1ABC FM07"),
    QStringLiteral ("QRZ W4/KA1ABC FM07"),
    QStringLiteral ("DE W4/KA1ABC FM07"),
    QStringLiteral ("CQ W4/KA1ABC -22"),
    QStringLiteral ("DE W4/KA1ABC -22"),
    QStringLiteral ("QRZ W4/KA1ABC -22"),
    QStringLiteral ("CQ W4/KA1ABC R-22"),
    QStringLiteral ("DE W4/KA1ABC R-22"),
    QStringLiteral ("QRZ W4/KA1ABC R-22"),
    QStringLiteral ("DE W4/KA1ABC 73"),
    QStringLiteral ("CQ KA1ABC FM07"),
    QStringLiteral ("QRZ KA1ABC FM07"),
    QStringLiteral ("DE KA1ABC/VE6 FM07"),
    QStringLiteral ("CQ KA1ABC/VE6 -22"),
    QStringLiteral ("DE KA1ABC/VE6 -22"),
    QStringLiteral ("QRZ KA1ABC/VE6 -22"),
    QStringLiteral ("CQ KA1ABC/VE6 R-22"),
    QStringLiteral ("DE KA1ABC/VE6 R-22"),
    QStringLiteral ("QRZ KA1ABC/VE6 R-22"),
    QStringLiteral ("DE KA1ABC 73"),
    QStringLiteral ("HELLO WORLD"),
    QStringLiteral ("ZL4/KA1ABC 73"),
    QStringLiteral ("KA1ABC XL/WB9XYZ"),
    QStringLiteral ("KA1ABC WB9XYZ/W4"),
    QStringLiteral ("DE KA1ABC/QRP 2W"),
    QStringLiteral ("KA1ABC/1 WB9XYZ/1"),
    QStringLiteral ("123456789ABCDEFGH"),
    QStringLiteral ("KA1ABC WB9XYZ EN34 OOO"),
    QStringLiteral ("KA1ABC WB9XYZ OOO"),
    QStringLiteral ("RO"),
    QStringLiteral ("RRR"),
    QStringLiteral ("73"),
  };

  int failures = 0;
  for (QString const& message : kMessages)
    {
      if (!test_message (message, false)) ++failures;
      if (!test_message (message, true)) ++failures;
    }

  if (failures != 0)
    {
      std::fprintf (stderr, "JT65 encoder test failed: %d errors\n", failures);
      return 1;
    }

  std::printf ("JT65 encoder test passed for %d messages\n", kMessages.size ());
  return 0;
}
