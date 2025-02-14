/*
 * MIT License
 *
 * Copyright (c) 2019 Alexey Edelev <semlanik@gmail.com>, Viktor Kopp <vifactor@gmail.com>
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

#pragma once

#include <QObject>
#include <QSharedPointer>

#include <memory>
#include <type_traits>

#include "qtprotobuflogging.h"
#include "qprotobufselfcheckiterator.h"
#include "qabstractprotobufserializer.h"

#include "qtprotobufglobal.h"

namespace QtProtobuf {

class QProtobufSerializerRegistryPrivate;
/*!
 * \ingroup QtProtobuf
 * \private
 * \brief The QProtobufSerializerRegistry class provides api to register serializers
 *        Loads serializer plugins and constructs serializer based on identifier.
 *
 */

class Q_PROTOBUF_EXPORT QProtobufSerializerRegistry final
{
public:
    std::shared_ptr<QAbstractProtobufSerializer> getSerializer(const QString &id);
    std::unique_ptr<QAbstractProtobufSerializer> acquireSerializer(const QString &id);

    static QProtobufSerializerRegistry &instance() {
        static QProtobufSerializerRegistry _instance;
        return _instance;
    }

private:
    QProtobufSerializerRegistry();
    ~QProtobufSerializerRegistry();

    Q_DISABLE_COPY_MOVE(QProtobufSerializerRegistry)

    std::unique_ptr<QProtobufSerializerRegistryPrivate> d;
};
}
