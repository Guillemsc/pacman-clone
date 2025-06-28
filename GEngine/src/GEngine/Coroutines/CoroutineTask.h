//
// Created by guillem on 6/28/25.
//

#ifndef COROUTINETASK_H
#define COROUTINETASK_H

namespace GEngine
{
	class CoroutineTask
	{
		friend class CoroutineRunner;

	public:
		void Cancel();

		bool GetIsCancelled() const;
		bool GetIsFinished() const;

	private:
		bool _isCancelled;
		bool _isFinished;
	};
}

#endif //COROUTINETASK_H
