#ifndef AUTHCHECKER_LINUX_H
#define AUTHCHECKER_LINUX_H

#include <QProcess>
#include "iauthchecker.h"

class AuthChecker_linux : public IAuthChecker
{
    Q_OBJECT
    Q_INTERFACES(IAuthChecker)
public:
    explicit AuthChecker_linux(QObject *parent = nullptr);
    ~AuthChecker_linux() override { delete process_; }
    AuthCheckerError authenticate() override;
private:
    QProcess *process_;
};

#endif // AUTHCHECKER_LINUX_H
