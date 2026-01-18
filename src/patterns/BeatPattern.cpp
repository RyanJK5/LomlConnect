#include <array>

#include "patterns/BeatPattern.hpp"

namespace Loml {
	BeatPattern::BeatPattern() 
		: LEDPattern(5)
	{ }
	
	void BeatPattern::Display(LEDStrip& led) {
		mStripIndex = (mStripIndex + 1) % Colors.size();
		
	}
}