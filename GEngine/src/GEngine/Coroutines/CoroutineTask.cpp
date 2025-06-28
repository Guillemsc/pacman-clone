//
// Created by guillem on 6/28/25.
//

#include "CoroutineTask.h"

namespace GEngine
{
	void CoroutineTask::Cancel()
	{
		_isCancelled = true;
	}

	bool CoroutineTask::GetIsCancelled() const
	{
		return _isCancelled;
	}

	bool CoroutineTask::GetIsFinished() const
	{
		return _isFinished;
	}
} // GEngineCore