//
// Created by guillem on 12/8/25.
//

#ifndef CANCELLATIONTOKEN_H
#define CANCELLATIONTOKEN_H
#include <memory>

namespace GEngine
{
    class CancellationToken;

    class CancellationTokenSource : public std::enable_shared_from_this<CancellationTokenSource>
    {
    public:
        void Cancel();
        bool IsCancelled() const;
        CancellationToken GetToken();

    private:
        bool _isCancelled = false;
    };

    class CancellationToken
    {
    public:
        explicit CancellationToken(const std::weak_ptr<CancellationTokenSource>& source);

        static CancellationToken None();

        bool IsCancelled() const;

    private:
        explicit CancellationToken();

    private:
        bool _isNonCancellable = false;
        std::weak_ptr<CancellationTokenSource> _source;
    };
}

#endif //CANCELLATIONTOKEN_H
