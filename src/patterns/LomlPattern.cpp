#include <array>

#include "patterns/LomlPattern.hpp"

namespace Loml {
	LomlPattern::LomlPattern() 
		: LEDPattern(100)
	{ }
	
	void LomlPattern::Display(LEDStrip& led) { }
}