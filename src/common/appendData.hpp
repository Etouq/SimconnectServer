#ifndef __APPEND_DATA_HPP__
#define __APPEND_DATA_HPP__

#include "dataIdentifiers.hpp"

#include <QByteArray>

#include <type_traits>


namespace util
{

template<typename T>
requires std::is_arithmetic_v<T> || std::is_enum_v<T>
inline void appendData(PfdIdentifier id, T value, QByteArray &bytes)
{
    constexpr DataGroupIdentifier groupId = DataGroupIdentifier::PFD_DATA;

    char data[sizeof(groupId) + sizeof(id) + sizeof(value)];
    std::memcpy(data, &groupId, sizeof(groupId));
    std::memcpy(data + sizeof(groupId), &id, sizeof(id));
    std::memcpy(data + sizeof(groupId) + sizeof(id), &value, sizeof(value));

    bytes.append(data, sizeof(groupId) + sizeof(id) + sizeof(value));
}

template<typename T>
requires std::is_arithmetic_v<T> || std::is_enum_v<T>
inline QByteArray createMessage(PfdIdentifier id, T value)
{
    constexpr DataGroupIdentifier groupId = DataGroupIdentifier::PFD_DATA;

    char data[sizeof(groupId) + sizeof(id) + sizeof(value)];
    std::memcpy(data, &groupId, sizeof(groupId));
    std::memcpy(data + sizeof(groupId), &id, sizeof(id));
    std::memcpy(data + sizeof(groupId) + sizeof(id), &value, sizeof(value));

    return QByteArray(data, sizeof(groupId) + sizeof(id) + sizeof(value));
}

inline void appendData(PfdIdentifier id, const QByteArray &str, QByteArray &bytes)
{
    constexpr DataGroupIdentifier groupId = DataGroupIdentifier::PFD_DATA;
    uint8_t size = str.size();

    char data[sizeof(groupId) + sizeof(id) + sizeof(size)];
    std::memcpy(data, &groupId, sizeof(groupId));
    std::memcpy(data + sizeof(groupId), &id, sizeof(id));
    std::memcpy(data + sizeof(groupId) + sizeof(id), &size, sizeof(size));

    bytes.append(data, sizeof(groupId) + sizeof(id) + sizeof(size)).append(str);
}

inline QByteArray createMessage(PfdIdentifier id, const QByteArray &str)
{
    constexpr DataGroupIdentifier groupId = DataGroupIdentifier::PFD_DATA;
    uint8_t size = str.size();

    char data[sizeof(groupId) + sizeof(id) + sizeof(size)];
    std::memcpy(data, &groupId, sizeof(groupId));
    std::memcpy(data + sizeof(groupId), &id, sizeof(id));
    std::memcpy(data + sizeof(groupId) + sizeof(id), &size, sizeof(size));

    QByteArray ret(data, sizeof(groupId) + sizeof(id) + sizeof(size));
    return ret.append(str);
}

template<typename T>
requires std::is_arithmetic_v<T> || std::is_enum_v<T>
inline void appendData(MfdIdentifier id, T value, QByteArray &bytes)
{
    constexpr DataGroupIdentifier groupId = DataGroupIdentifier::MFD_DATA;

    char data[sizeof(groupId) + sizeof(id) + sizeof(value)];
    std::memcpy(data, &groupId, sizeof(groupId));
    std::memcpy(data + sizeof(groupId), &id, sizeof(id));
    std::memcpy(data + sizeof(groupId) + sizeof(id), &value, sizeof(value));

    bytes.append(data, sizeof(groupId) + sizeof(id) + sizeof(value));
}

template<typename T>
requires std::is_arithmetic_v<T> || std::is_enum_v<T>
inline QByteArray createMessage(MfdIdentifier id, T value)
{
    constexpr DataGroupIdentifier groupId = DataGroupIdentifier::MFD_DATA;

    char data[sizeof(groupId) + sizeof(id) + sizeof(value)];
    std::memcpy(data, &groupId, sizeof(groupId));
    std::memcpy(data + sizeof(groupId), &id, sizeof(id));
    std::memcpy(data + sizeof(groupId) + sizeof(id), &value, sizeof(value));

    return QByteArray(data, sizeof(groupId) + sizeof(id) + sizeof(value));
}

inline void appendData(MfdIdentifier id, QByteArray &bytes)
{
    constexpr DataGroupIdentifier groupId = DataGroupIdentifier::MFD_DATA;

    char data[sizeof(groupId) + sizeof(id)];
    std::memcpy(data, &groupId, sizeof(groupId));
    std::memcpy(data + sizeof(groupId), &id, sizeof(id));

    bytes.append(data, sizeof(groupId) + sizeof(id));
}

inline QByteArray createMessage(MfdIdentifier id)
{
    constexpr DataGroupIdentifier groupId = DataGroupIdentifier::MFD_DATA;

    char data[sizeof(groupId) + sizeof(id)];
    std::memcpy(data, &groupId, sizeof(groupId));
    std::memcpy(data + sizeof(groupId), &id, sizeof(id));

    return QByteArray(data, sizeof(groupId) + sizeof(id));
}

inline void appendData(MfdIdentifier id, const QByteArray &str, QByteArray &bytes)
{
    constexpr DataGroupIdentifier groupId = DataGroupIdentifier::MFD_DATA;
    uint8_t size = str.size();

    char data[sizeof(groupId) + sizeof(id) + sizeof(size)];
    std::memcpy(data, &groupId, sizeof(groupId));
    std::memcpy(data + sizeof(groupId), &id, sizeof(id));
    std::memcpy(data + sizeof(groupId) + sizeof(id), &size, sizeof(size));

    bytes.append(data, sizeof(groupId) + sizeof(id) + sizeof(size)).append(str);
}

inline QByteArray createMessage(MfdIdentifier id, const QByteArray &str)
{
    constexpr DataGroupIdentifier groupId = DataGroupIdentifier::MFD_DATA;
    uint8_t size = str.size();

    char data[sizeof(groupId) + sizeof(id) + sizeof(size)];
    std::memcpy(data, &groupId, sizeof(groupId));
    std::memcpy(data + sizeof(groupId), &id, sizeof(id));
    std::memcpy(data + sizeof(groupId) + sizeof(id), &size, sizeof(size));

    QByteArray ret(data, sizeof(groupId) + sizeof(id) + sizeof(size));
    return ret.append(str);
}

template<typename T>
requires std::is_arithmetic_v<T> || std::is_enum_v<T>
inline void appendData(MfdIdentifier id, uint8_t engineIdx, T value, QByteArray &bytes)
{
    constexpr DataGroupIdentifier groupId = DataGroupIdentifier::MFD_DATA;

    char data[sizeof(groupId) + sizeof(id) + sizeof(engineIdx) + sizeof(value)];
    std::memcpy(data, &groupId, sizeof(groupId));
    std::memcpy(data + sizeof(groupId), &id, sizeof(id));
    std::memcpy(data + sizeof(groupId) + sizeof(id), &engineIdx, sizeof(engineIdx));
    std::memcpy(data + sizeof(groupId) + sizeof(id) + sizeof(engineIdx), &value, sizeof(value));

    bytes.append(data, sizeof(groupId) + sizeof(id) + sizeof(engineIdx) + sizeof(value));
}

template<typename T>
requires std::is_arithmetic_v<T> || std::is_enum_v<T>
inline QByteArray createMessage(MfdIdentifier id, uint8_t engineIdx, T value)
{
    constexpr DataGroupIdentifier groupId = DataGroupIdentifier::MFD_DATA;

    char data[sizeof(groupId) + sizeof(id) + sizeof(engineIdx) + sizeof(value)];
    std::memcpy(data, &groupId, sizeof(groupId));
    std::memcpy(data + sizeof(groupId), &id, sizeof(id));
    std::memcpy(data + sizeof(groupId) + sizeof(id), &engineIdx, sizeof(engineIdx));
    std::memcpy(data + sizeof(groupId) + sizeof(id) + sizeof(engineIdx), &value, sizeof(value));

    return QByteArray(data, sizeof(groupId) + sizeof(id) + sizeof(engineIdx) + sizeof(value));
}

inline void appendData(MfdIdentifier id, uint8_t engineIdx, const QByteArray &str, QByteArray &bytes)
{
    constexpr DataGroupIdentifier groupId = DataGroupIdentifier::MFD_DATA;
    uint8_t size = str.size();

    char data[sizeof(groupId) + sizeof(id) + sizeof(engineIdx) + sizeof(size)];
    std::memcpy(data, &groupId, sizeof(groupId));
    std::memcpy(data + sizeof(groupId), &id, sizeof(id));
    std::memcpy(data + sizeof(groupId) + sizeof(id), &engineIdx, sizeof(engineIdx));
    std::memcpy(data + sizeof(groupId) + sizeof(id) + sizeof(engineIdx), &size, sizeof(size));

    bytes.append(data, sizeof(groupId) + sizeof(id) + sizeof(engineIdx) + sizeof(size)).append(str);
}

inline QByteArray createMessage(MfdIdentifier id, uint8_t engineIdx, const QByteArray &str)
{
    constexpr DataGroupIdentifier groupId = DataGroupIdentifier::MFD_DATA;
    uint8_t size = str.size();

    char data[sizeof(groupId) + sizeof(id) + sizeof(engineIdx) + sizeof(size)];
    std::memcpy(data, &groupId, sizeof(groupId));
    std::memcpy(data + sizeof(groupId), &id, sizeof(id));
    std::memcpy(data + sizeof(groupId) + sizeof(id), &engineIdx, sizeof(engineIdx));
    std::memcpy(data + sizeof(groupId) + sizeof(id) + sizeof(engineIdx), &size, sizeof(size));

    QByteArray ret(data, sizeof(groupId) + sizeof(id) + sizeof(engineIdx) + sizeof(size));
    return ret.append(str);
}

template<typename T>
requires std::is_arithmetic_v<T> || std::is_enum_v<T>
inline void appendData(TscIdentifier id, T value, QByteArray &bytes)
{
    constexpr DataGroupIdentifier groupId = DataGroupIdentifier::TSC_DATA;

    char data[sizeof(groupId) + sizeof(id) + sizeof(value)];
    std::memcpy(data, &groupId, sizeof(groupId));
    std::memcpy(data + sizeof(groupId), &id, sizeof(id));
    std::memcpy(data + sizeof(groupId) + sizeof(id), &value, sizeof(value));

    bytes.append(data, sizeof(groupId) + sizeof(id) + sizeof(value));
}

template<typename T>
requires std::is_arithmetic_v<T> || std::is_enum_v<T>
inline QByteArray createMessage(TscIdentifier id, T value)
{
    constexpr DataGroupIdentifier groupId = DataGroupIdentifier::TSC_DATA;

    char data[sizeof(groupId) + sizeof(id) + sizeof(value)];
    std::memcpy(data, &groupId, sizeof(groupId));
    std::memcpy(data + sizeof(groupId), &id, sizeof(id));
    std::memcpy(data + sizeof(groupId) + sizeof(id), &value, sizeof(value));

    return QByteArray(data, sizeof(groupId) + sizeof(id) + sizeof(value));
}

inline void appendData(TscIdentifier id, const QByteArray &str, QByteArray &bytes)
{
    constexpr DataGroupIdentifier groupId = DataGroupIdentifier::TSC_DATA;
    uint8_t size = str.size();

    char data[sizeof(groupId) + sizeof(id) + sizeof(size)];
    std::memcpy(data, &groupId, sizeof(groupId));
    std::memcpy(data + sizeof(groupId), &id, sizeof(id));
    std::memcpy(data + sizeof(groupId) + sizeof(id), &size, sizeof(size));

    bytes.append(data, sizeof(groupId) + sizeof(id) + sizeof(size)).append(str);
}

inline QByteArray createMessage(TscIdentifier id, const QByteArray &str)
{
    constexpr DataGroupIdentifier groupId = DataGroupIdentifier::TSC_DATA;
    uint8_t size = str.size();

    char data[sizeof(groupId) + sizeof(id) + sizeof(size)];
    std::memcpy(data, &groupId, sizeof(groupId));
    std::memcpy(data + sizeof(groupId), &id, sizeof(id));
    std::memcpy(data + sizeof(groupId) + sizeof(id), &size, sizeof(size));

    QByteArray ret(data, sizeof(groupId) + sizeof(id) + sizeof(size));
    return ret.append(str);
}


inline void appendData(ServerMessageIdentifier id, QByteArray &bytes)
{
    constexpr DataGroupIdentifier groupId = DataGroupIdentifier::SERVER_DATA;

    char data[sizeof(groupId) + sizeof(id)];
    std::memcpy(data, &groupId, sizeof(groupId));
    std::memcpy(data + sizeof(groupId), &id, sizeof(id));

    bytes.append(data, sizeof(groupId) + sizeof(id));
}

inline QByteArray createMessage(ServerMessageIdentifier id)
{
    constexpr DataGroupIdentifier groupId = DataGroupIdentifier::SERVER_DATA;

    char data[sizeof(groupId) + sizeof(id)];
    std::memcpy(data, &groupId, sizeof(groupId));
    std::memcpy(data + sizeof(groupId), &id, sizeof(id));

    return QByteArray(data, sizeof(groupId) + sizeof(id));
}

template<typename T>
requires std::is_arithmetic_v<T> || std::is_enum_v<T>
inline void appendData(ServerMessageIdentifier id, T value, QByteArray &bytes)
{
    constexpr DataGroupIdentifier groupId = DataGroupIdentifier::SERVER_DATA;

    char data[sizeof(groupId) + sizeof(id) + sizeof(value)];
    std::memcpy(data, &groupId, sizeof(groupId));
    std::memcpy(data + sizeof(groupId), &id, sizeof(id));
    std::memcpy(data + sizeof(groupId) + sizeof(id), &value, sizeof(value));

    bytes.append(data, sizeof(groupId) + sizeof(id) + sizeof(value));
}

template<typename T>
requires std::is_arithmetic_v<T> || std::is_enum_v<T>
inline QByteArray createMessage(ServerMessageIdentifier id, T value)
{
    constexpr DataGroupIdentifier groupId = DataGroupIdentifier::SERVER_DATA;

    char data[sizeof(groupId) + sizeof(id) + sizeof(value)];
    std::memcpy(data, &groupId, sizeof(groupId));
    std::memcpy(data + sizeof(groupId), &id, sizeof(id));
    std::memcpy(data + sizeof(groupId) + sizeof(id), &value, sizeof(value));

    return QByteArray(data, sizeof(groupId) + sizeof(id) + sizeof(value));
}

inline void appendData(ServerMessageIdentifier id, const QByteArray &str, QByteArray &bytes)
{
    constexpr DataGroupIdentifier groupId = DataGroupIdentifier::SERVER_DATA;
    uint8_t size = str.size();

    char data[sizeof(groupId) + sizeof(id) + sizeof(size)];
    std::memcpy(data, &groupId, sizeof(groupId));
    std::memcpy(data + sizeof(groupId), &id, sizeof(id));
    std::memcpy(data + sizeof(groupId) + sizeof(id), &size, sizeof(size));

    bytes.append(data, sizeof(groupId) + sizeof(id) + sizeof(size)).append(str);
}

inline QByteArray createMessage(ServerMessageIdentifier id, const QByteArray &str)
{
    constexpr DataGroupIdentifier groupId = DataGroupIdentifier::SERVER_DATA;
    uint8_t size = str.size();

    char data[sizeof(groupId) + sizeof(id) + sizeof(size)];
    std::memcpy(data, &groupId, sizeof(groupId));
    std::memcpy(data + sizeof(groupId), &id, sizeof(id));
    std::memcpy(data + sizeof(groupId) + sizeof(id), &size, sizeof(size));

    QByteArray ret(data, sizeof(groupId) + sizeof(id) + sizeof(size));
    return ret.append(str);
}

}  // namespace util

#endif  // __APPEND_DATA_HPP__
