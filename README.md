Date: April 28th


Features: 
-Implemented synth voice and sound subclass
-Ability to call JUCE objects
-SynthSound class inherit juce::SynthesiserSound and applied necessary functions
-Include SynthSound header into SynthVoice header
-SynthVoice class inherit juce::SynthesiserSound and applied necessary functions
-Implented SynthVoice methods in SynthVoice.cpp
-Included SynthSound, SynthVoice and JuceHeader into PluginProcesorr.h (which is responsible for playing sounds)
-added new SynthSound & SynthVoice to PluginProcesorr.cpp
-Set SampleRate in PluginProcesorr.cpp

Lessons Learned:
-Difference between .cpp and .h
-#include implentation
-syntax for inheritance and functions/methods
-implement a single synth voice for a monophonic synth


Date: May 5th

Features:
-Created a simple oscilator
-Implemented Sine wave sound
-Implemented user MIDI input to hertz

Lessons Learned:
-fun juce objects that do the math for waves like sine, saw, square, etc. 
-Starting a stopping notes
-the importance of rendering next block
