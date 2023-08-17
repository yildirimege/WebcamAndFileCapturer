#pragma once
#include "VideoManagerInterface.h"

using namespace VideoManagerLib;

/**
* @brief Delegate for handling engine state change events.
* @brief The delegate signature takes an `EngineState` parameter.
*/
delegate void EngineStateChangedEventHandler(VideoManagerLib::EngineState);

/**
* @brief Class that defines an event and raises engine state change events.
*/
ref class EventSource 
{
public:
	/**
	* @brief Event that is raised when the engine state changes.
	* @brief Subscribers can attach event handlers to this event.
	*/
	event EngineStateChangedEventHandler^ OnEngineStateChanged;

	/**
	* @brief Changes the state of the engine and raises the corresponding event.
	* 
	* @param newEngineState The new state to which the engine is changing.
	*/
	void ChangeState(VideoManagerLib::EngineState newEngineState)
	{
		OnEngineStateChanged(newEngineState); // Raises the engine state change event.
	}
};
