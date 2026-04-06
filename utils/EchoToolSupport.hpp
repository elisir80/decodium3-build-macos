#ifndef ECHO_TOOL_SUPPORT_HPP
#define ECHO_TOOL_SUPPORT_HPP

#include <QString>

#include <array>
#include <complex>
#include <vector>

namespace decodium
{
namespace echo_tools
{

constexpr int kEchoSampleRate = 12000;
constexpr int kEchoNsps = 4096;
constexpr int kEchoTxSamples = 6 * kEchoNsps;
constexpr int kEchoFileSamples = 3 * kEchoSampleRate;

std::array<int, 6> generate_echo_call_tones (QString const& callsign);
void apply_lorentz_fading (std::vector<std::complex<float>>& cdat, float fspread);
std::vector<short> make_echo_call_wave (QString const& callsign, double f0, double fdop,
                                        float fspread, int ndf, float snrdb);
std::vector<short> make_echo_measure_wave (double f0, double fdop, float fspread,
                                           float snrdb, float gain_linear);
QString timestamped_wave_name (int ifile, int seconds_per_file);
bool write_pcm16_mono_wav (QString const& path, std::vector<short> const& samples);
std::vector<short> read_pcm16_mono_wav (QString const& path, QString* error_out = nullptr);

}
}

#endif // ECHO_TOOL_SUPPORT_HPP
