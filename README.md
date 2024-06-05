*Date: April 28th


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


*Date: May 5th

Features:
-Created a simple oscilator
-Implemented Sine wave sound
-Implemented user MIDI input to hertz

Lessons Learned:
-fun juce objects that do the math for waves like sine, saw, square, etc. 
-Starting a stopping notes
-the importance of rendering next block


*Date: May 8th

Features:
-Attack, Decay, Sustain, Release parameters wired to GUI.

Lessons Learned:
-using * to de-reference pointer 


*Date: May 28th

Features:
-Can open the VST3 file in Ableton to use plugin 
-All ADSR parameters are verified working
-Producing sounds with hertz signal from MIDI input verified

Lessons Learned:
-How to compile the project properly to work on a DAW
-How to pass audio from the DAW to OBS to grab proper screen recording

*Date: June 4th

Features:
-Modified GUI of ADSR sliders. They now are longer to make slighter adjustments. Also positioned to the right. 
-Added ComboBox for selecting different wave patterns for your oscilator.
-Added seperate classes for components to make code cleaner overall

Lessons Learned:
-How to create new classes with their own cpp and header files, and to #include them in the necessary files. 
-How to switch between seperate waves when prompted by user
-More general GUI within JUCE framework