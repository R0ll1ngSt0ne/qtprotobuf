/*
 * MIT License
 *
 * Copyright (c) 2019 Alexey Edelev <semlanik@gmail.com>
 *
 * This file is part of QtProtobuf project https://git.semlanik.org/semlanik/qtprotobuf
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this
 * software and associated documentation files (the "Software"), to deal in the Software
 * without restriction, including without limitation the rights to use, copy, modify,
 * merge, publish, distribute, sublicense, and/or sell copies of the Software, and
 * to permit persons to whom the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies
 * or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 * PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
 * FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#include "qgrpcstatus.h"

namespace QtProtobuf {

class QGrpcStatusPrivate {
public:
    QGrpcStatusPrivate(QGrpcStatus::StatusCode code, const QString &message) : m_code(code)
      , m_message(message)
    {}

    ~QGrpcStatusPrivate() = default;

    QGrpcStatus::StatusCode m_code;
    QString m_message;
};

QGrpcStatus::QGrpcStatus(StatusCode code, const QString &message) :
    d_ptr(std::make_unique<QGrpcStatusPrivate>(code, message))
{}

QGrpcStatus::QGrpcStatus(const QGrpcStatus &other) : d_ptr(std::make_unique<QGrpcStatusPrivate>(other.d_ptr->m_code, other.d_ptr->m_message))
{}

QGrpcStatus::QGrpcStatus(QGrpcStatus &&other) : d_ptr(std::move(other.d_ptr))
{
}

QGrpcStatus &QGrpcStatus::operator =(const QGrpcStatus &other)
{
    d_ptr->m_code = other.d_ptr->m_code;
    d_ptr->m_message = other.d_ptr->m_message;
    return *this;
}

QGrpcStatus &QGrpcStatus::operator =(QGrpcStatus &&other)
{
    d_ptr = std::move(other.d_ptr);
    return *this;
}

QGrpcStatus::~QGrpcStatus()
{}

QString QGrpcStatus::message() const
{
    return d_ptr->m_message;
}

QGrpcStatus::StatusCode QGrpcStatus::code() const
{
    return d_ptr->m_code;
}

bool QGrpcStatus::operator ==(StatusCode code) const
{
    return d_ptr->m_code == code;
}

bool QGrpcStatus::operator !=(StatusCode code) const
{
    return d_ptr->m_code != code;
}

bool QGrpcStatus::operator ==(const QGrpcStatus &other) const
{
    return d_ptr->m_code == other.d_ptr->m_code;
}

}

bool operator ==(QtProtobuf::QGrpcStatus::StatusCode code, const QtProtobuf::QGrpcStatus &status)
{
    return status == code;
}
bool operator !=(QtProtobuf::QGrpcStatus::StatusCode code, const QtProtobuf::QGrpcStatus &status)
{
    return status != code;
}
