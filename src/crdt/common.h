#ifndef COMMON_H
#define COMMON_H

#include <QDebug>

#define WARNING_T(message) qWarning() << QString("VoiceCall W: %1: %2").arg(Q_FUNC_INFO).arg(message);

#ifndef WANT_TRACE
#   define TRACE
#   define DEBUG (message) if (false) { };
#else
#   define TRACE qDebug() << QString("T: %1:%2%").arg(Q_FUNC_INFO).arg(__LINE__);
#   define DEBUG (message) qDebug("%s", QString("D: %1: %2").arg(Q_FUNC_INFO).arg(message).toUtf8().constData());
#endif

#endif // COMMON_H
