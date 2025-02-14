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

#pragma once //QAbstractGrpcClient

#include <memory>
#include <functional>
#include <type_traits>

#include <QObject>
#include <QByteArray>

#include <qtprotobuflogging.h>
#include <qabstractprotobufserializer.h>

#include "qabstractgrpcchannel.h"

#include "qtgrpcglobal.h"

namespace QtProtobuf {

class QGrpcAsyncReply;
class QAbstractGrpcChannel;
class QAbstractGrpcClientPrivate;
/*!
 * \ingroup QtGrpc
 * \brief The QAbstractGrpcClient class is bridge between gRPC clients and channels. QAbstractGrpcClient provides set of
 *        bridge functions for client classes generated out of protobuf services.
 */
class Q_GRPC_EXPORT QAbstractGrpcClient : public QObject
{
    Q_OBJECT
public:
    /*!
     * \brief Attaches \a channel to client as transport layer for gRPC. Parameters and return values will be serialized
     *        to supported by channel format.
     * \see QAbstractGrcpChannel
     * \param channel Shared pointer to channel will be used as transport layer for gRPC
     */
    void attachChannel(const std::shared_ptr<QAbstractGrpcChannel> &channel);

signals:
    /*!
     * \brief error signal is emited by client when error occured in channel or while serialization/deserialization
     * \param[out] code gRPC channel StatusCode
     * \param[out] errorText Error description from channel or from QGrpc
     */
    void error(const QGrpcStatus &status);

protected:
    QAbstractGrpcClient(const QString &service, QObject *parent = nullptr);
    virtual ~QAbstractGrpcClient();

    /*!
     * \private
     * \brief Calls \p method of service client synchronously
     * \param[in] method Name of the method to be called
     * \param[in] arg Protobuf message argument for \p method
     * \param[out] ret A pointer to memory with protobuf message to write an gRPC reply to
     */
    template<typename A, typename R>
    QGrpcStatus call(const QString &method, const A &arg, const QPointer<R> &ret) {
        QGrpcStatus status{QGrpcStatus::Ok};
        if (ret.isNull()) {
            static const QString errorString("Unable to call method: %1. Pointer to return data is null");
            status = QGrpcStatus{QGrpcStatus::InvalidArgument, errorString.arg(method)};
            error(status);
            qProtoCritical() << errorString.arg(method);
            return status;
        }

        QByteArray retData;
        status = call(method, arg.serialize(serializer()), retData);
        if (status == QGrpcStatus::StatusCode::Ok) {
            return tryDeserialize(*ret, retData);
        }
        return status;
    }

    /*!
     * \private
     * \brief Calls \p method of service client asynchronously and returns pointer to assigned to call AsyncReply
     * \param[in] method Name of the method to be called
     * \param[in] arg Protobuf message argument for \p method
     */
    template<typename A>
    QGrpcAsyncReply *call(const QString &method, const A &arg) {
        return call(method, arg.serialize(serializer()));
    }

    /*!
     * \private
     * \brief Subscribes to message notifications from server-stream with given message argument \a arg
     * \param[in] method Name of the method to be called
     * \param[in] arg Protobuf message argument for \p method
     * \param[out] signal Callback with return-message as input parameter that will be called each time message
     *             update recevied from server-stream
     */
    template<typename A, typename R, typename C,
             typename std::enable_if_t<std::is_base_of<QAbstractGrpcClient, C>::value, int> = 0>
    void subscribe(const QString &method, const A &arg, void(C::*signal)(const R &)) {
        subscribe(method, arg.serialize(serializer()), [this, signal](const QByteArray &data) {
            R ret;
            tryDeserialize(ret, data);
            C *client = static_cast<C *>(this);
            (client->*signal)(ret);
        });
    }

    /*!
     * \private
     * \brief Subscribes to message notifications from server-stream with given message argument \a arg
     * \param[in] method Name of the method to be called
     * \param[in] arg Protobuf message argument for \p method
     * \param[out] ret Pointer to preallocated return-message structure. \p ret Structure fields will be update each
     *        time message update recevied from server-stream.
     * \note If \p ret is used as property-fiels in other object, property NOTIFY signal won't be called in case of
     *       updated message recevied from server-stream
     */
    template<typename A, typename R>
    void subscribe(const QString &method, const A &arg, const QPointer<R> &ret) {
        if (ret.isNull()) {
            static const QString nullPointerError("Unable to subscribe method: %1. Pointer to return data is null");
            error({QGrpcStatus::InvalidArgument, nullPointerError.arg(method)});
            qProtoCritical() << nullPointerError.arg(method);
            return;
        }

        subscribe(method, arg.serialize(serializer()), [ret, this](const QByteArray &data) {
            if (!ret.isNull()) {
                tryDeserialize(*ret, data);
            } else {
                static const QLatin1String nullPointerError("Pointer to return data is null while subscription update received");
                error({QGrpcStatus::InvalidArgument, nullPointerError});
                qProtoCritical() << nullPointerError;
            }
        });
    }

    QAbstractProtobufSerializer *serializer() const;

    friend class QGrpcAsyncReply;
private:
    /*!
     * \private
     */
    QGrpcStatus call(const QString &method, const QByteArray &arg, QByteArray &ret);

    /*!
     * \private
     */
    QGrpcAsyncReply *call(const QString &method, const QByteArray &arg);

    /*!
     * \private
     */
    void subscribe(const QString &method, const QByteArray &arg, const std::function<void(const QByteArray &)> &handler);

    /*!
     * \private
     * \brief Deserialization helper
     */
    template<typename R>
    QGrpcStatus tryDeserialize(R &ret, const QByteArray &retData) {
        QGrpcStatus status{QGrpcStatus::Ok};
        try {
            ret.deserialize(serializer(), retData);
        } catch (std::invalid_argument &) {
            static const QLatin1String invalidArgumentErrorMessage("Response deserialization failed invalid field found");
            status = {QGrpcStatus::InvalidArgument, invalidArgumentErrorMessage};
            error(status);
            qProtoCritical() << invalidArgumentErrorMessage;
        } catch (std::out_of_range &) {
            static const QLatin1String outOfRangeErrorMessage("Invalid size of received buffer");
            status = {QGrpcStatus::OutOfRange, outOfRangeErrorMessage};
            error(status);
            qProtoCritical() << outOfRangeErrorMessage;
        } catch (...) {
            status = {QGrpcStatus::Internal, QLatin1String("Unknown exception caught during deserialization")};
            error(status);
        }
        return status;
    }

    Q_DISABLE_COPY_MOVE(QAbstractGrpcClient)

    std::unique_ptr<QAbstractGrpcClientPrivate> d_ptr;
};
}
