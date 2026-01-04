#include <cmath>

namespace XSynth {

inline float sine(float phase) { return std::sin(phase); }
inline float square(float phase) { return (sine(phase) > 0) ? 1 : 0; }

} // namespace XSynth
