//
// Created by guillem on 12/8/25.
//

#include "CancellationToken.h"

namespace GEngine
{
    void CancellationTokenSource::Cancel()
    {
        _isCancelled = true;
    }

    bool CancellationTokenSource::IsCancelled() const
    {
        return _isCancelled;
    }

    CancellationToken CancellationTokenSource::GetToken()
    {
        return CancellationToken(weak_from_this());
    }

    CancellationToken::CancellationToken()
    {
        _isNonCancellable = true;
    }

    CancellationToken::CancellationToken(const std::weak_ptr<CancellationTokenSource>& source)
    {
        _source = source;
    }

    CancellationToken CancellationToken::None()
    {
        return CancellationToken();
    }

    bool CancellationToken::IsCancelled() const
    {
        if (_isNonCancellable) return false;

        const std::shared_ptr<CancellationTokenSource> lSource = _source.lock();
        if (!lSource) return true;

        return lSource->IsCancelled();
    }
}
