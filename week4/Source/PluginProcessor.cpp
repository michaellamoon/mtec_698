/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Week4AudioProcessor::Week4AudioProcessor()

     : AudioProcessor (BusesProperties()
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true))
{
    /* declare a vector of parameters */
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> parameters;

    /* loop through our parameter defines and add the parameters to the vector */
    for (int i = 0; i < TotalNumberParameters; i++) {
        parameters.push_back(std::make_unique<juce::AudioParameterFloat>(PARAMETER_NAMES[i], PARAMETER_NAMES[i], PARAMETER_RANGES[i], 1.f));
    }

    /* construct the parameter tree object -- this will actually add all the parameters to our plugin */
    mParameterState.reset(new juce::AudioProcessorValueTreeState(*this, nullptr, "PARAMETER_STATE", { parameters.begin(), parameters.end() }));

    /* now lets get pointers which point to the current values of the parameters, we can use these in our processing loops */
    for (int i = 0; i < TotalNumberParameters; i++) {
        mParameterValues[i] = mParameterState->getRawParameterValue(PARAMETER_NAMES[i]);
    }
    
}
Week4AudioProcessor::~Week4AudioProcessor()
{
}

//==============================================================================
const juce::String Week4AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Week4AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Week4AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Week4AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Week4AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Week4AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Week4AudioProcessor::getCurrentProgram()
{
    return 0;
}

void Week4AudioProcessor::setCurrentProgram (int index)
{
}

const juce::String Week4AudioProcessor::getProgramName (int index)
{
    return {};
}

void Week4AudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void Week4AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Initialize our sine wave--------------------------------------
        mSineWavePlug.initialize(442, sampleRate);
        fSineWavePlug.initialize(442, sampleRate);
        m2SineWavePlug.initialize(600, sampleRate);
        f2SineWavePlug.initialize(600, sampleRate);
}

void Week4AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Week4AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void Week4AudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
         buffer.clear (i, 0, buffer.getNumSamples());
    
    //---------
    mSineWavePlug.setGain(mParameterValues[GAIN_AMOUNT]->load());
    fSineWavePlug.setGain(mParameterValues[FM_AMOUNT]->load());
    
    m2SineWavePlug.setGain(mParameterValues[GAIN_AMOUNT2]->load());
    f2SineWavePlug.setGain(mParameterValues[FM_AMOUNT2]->load());
    
    switchButtons.setClickingTogglesState(mParameterValues[BUTT]->load());
     
     // FOR EACH SAMPLE IN THE INCOMING AUDIO BUFFER
     for (int sample_index = 0; sample_index < buffer.getNumSamples(); sample_index++) {
         
         float fm_operator = fSineWavePlug.getNextSample();
         float fm2_operator = f2SineWavePlug.getNextSample();
         
         if (switchButtons.isToggleable() == true){
             float outputR = mSineWavePlug.getNextSampleWithFM(fm_operator);
             float outputL = m2SineWavePlug.getNextSampleWithFM(fm2_operator);
             
             // STORE THE OUTPUT TO THE LEFT AND RIGHT CHANNELS OF THE AUDIO BUFFER
             buffer.setSample(0, sample_index, outputR);
             buffer.setSample(1, sample_index, outputL);
         }
         else {
             float output = mSineWavePlug.getNextSampleWithFM(fm_operator) * m2SineWavePlug.getNextSampleWithFM(fm2_operator);
             
             // STORE THE OUTPUT TO THE LEFT AND RIGHT CHANNELS OF THE AUDIO BUFFER
             buffer.setSample(0, sample_index, output);
             buffer.setSample(1, sample_index, output);
         }
     }
    
}
juce::AudioProcessorValueTreeState& Week4AudioProcessor::getValueTreeState()
{
    return *mParameterState.get();
}

//==============================================================================
bool Week4AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* Week4AudioProcessor::createEditor()
{
    return new Week4AudioProcessorEditor (*this);
}

//==============================================================================
void Week4AudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // Get the underlying ValueTree from out "Parameter Value Tree"
    auto tree_state = mParameterState->copyState();
    
    // Convert the value tree into an XML object which can be saved on disk to as binary
    std::unique_ptr<juce::XmlElement> xml(tree_state.createXml());
    
    /* */
    DBG(xml->toString());

    /* store as binary */
    copyXmlToBinary(*xml, destData);
}

void Week4AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

    if (xmlState.get()) {
        
        DBG(xmlState->toString());
        
        juce::ValueTree parameter_tree = juce::ValueTree::fromXml(*xmlState);
        mParameterState->replaceState(parameter_tree);
    }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Week4AudioProcessor();
}
