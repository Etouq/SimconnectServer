#ifndef __APPEND_DATA_HPP__
#define __APPEND_DATA_HPP__

#include "dataIdentifiers.hpp"

#include <QByteArray>

#include <type_traits>


namespace util
{

template<typename T>
requires std::is_arithmetic_v<T> || std::is_enum_v<T>
inline void appendData(PfdIdentifier id, T value, QByteArray &data)
{
    constexpr DataGroupIdentifier groupId = DataGroupIdentifier::PFD_DATA;
    data.append(reinterpret_cast<const char *>(&groupId), sizeof(groupId))
      .append(reinterpret_cast<const char *>(&id), sizeof(id))
      .append(reinterpret_cast<const char *>(&value), sizeof(value));
}

inline void appendData(PfdIdentifier id, const QByteArray &str, QByteArray &data)
{
    constexpr DataGroupIdentifier groupId = DataGroupIdentifier::PFD_DATA;
    uint8_t size = str.size();
    data.append(reinterpret_cast<const char *>(&groupId), sizeof(groupId))
      .append(reinterpret_cast<const char *>(&id), sizeof(id))
      .append(reinterpret_cast<const char *>(&size), sizeof(size))
      .append(str.constData(), size);
}

template<typename T>
requires std::is_arithmetic_v<T> || std::is_enum_v<T>
inline void appendData(MfdIdentifier id, T value, QByteArray &data)
{
    constexpr DataGroupIdentifier groupId = DataGroupIdentifier::MFD_DATA;
    data.append(reinterpret_cast<const char *>(&groupId), sizeof(groupId))
      .append(reinterpret_cast<const char *>(&id), sizeof(id))
      .append(reinterpret_cast<const char *>(&value), sizeof(value));
}

inline void appendData(MfdIdentifier id, QByteArray &data)
{
    constexpr DataGroupIdentifier groupId = DataGroupIdentifier::MFD_DATA;
    data.append(reinterpret_cast<const char *>(&groupId), sizeof(groupId))
      .append(reinterpret_cast<const char *>(&id), sizeof(id));
}

inline void appendData(MfdIdentifier id, const QByteArray &str, QByteArray &data)
{
    constexpr DataGroupIdentifier groupId = DataGroupIdentifier::MFD_DATA;
    uint8_t size = str.size();
    data.append(reinterpret_cast<const char *>(&groupId), sizeof(groupId))
      .append(reinterpret_cast<const char *>(&id), sizeof(id))
      .append(reinterpret_cast<const char *>(&size), sizeof(size))
      .append(str.constData(), size);
}
template<typename T>
requires std::is_arithmetic_v<T> || std::is_enum_v<T>
inline void appendData(MfdIdentifier id, uint8_t engineIdx, T value, QByteArray &data)
{
    constexpr DataGroupIdentifier groupId = DataGroupIdentifier::MFD_DATA;
    data.append(reinterpret_cast<const char *>(&groupId), sizeof(groupId))
      .append(reinterpret_cast<const char *>(&id), sizeof(id))
      .append(reinterpret_cast<const char *>(&engineIdx), sizeof(engineIdx))
      .append(reinterpret_cast<const char *>(&value), sizeof(value));
}

inline void appendData(MfdIdentifier id, uint8_t engineIdx, const QByteArray &str, QByteArray &data)
{
    constexpr DataGroupIdentifier groupId = DataGroupIdentifier::MFD_DATA;
    uint8_t size = str.size();
    data.append(reinterpret_cast<const char *>(&groupId), sizeof(groupId))
      .append(reinterpret_cast<const char *>(&id), sizeof(id))
      .append(reinterpret_cast<const char *>(&engineIdx), sizeof(engineIdx))
      .append(reinterpret_cast<const char *>(&size), sizeof(size))
      .append(str.constData(), size);
}

template<typename T>
requires std::is_arithmetic_v<T> || std::is_enum_v<T>
inline void appendData(TscIdentifier id, T value, QByteArray &data)
{
    constexpr DataGroupIdentifier groupId = DataGroupIdentifier::TSC_DATA;
    data.append(reinterpret_cast<const char *>(&groupId), sizeof(groupId))
      .append(reinterpret_cast<const char *>(&id), sizeof(id))
      .append(reinterpret_cast<const char *>(&value), sizeof(value));
}

inline void appendData(TscIdentifier id, const QByteArray &str, QByteArray &data)
{
    constexpr DataGroupIdentifier groupId = DataGroupIdentifier::TSC_DATA;
    uint8_t size = str.size();
    data.append(reinterpret_cast<const char *>(&groupId), sizeof(groupId))
      .append(reinterpret_cast<const char *>(&id), sizeof(id))
      .append(reinterpret_cast<const char *>(&size), sizeof(size))
      .append(str.constData(), size);
}


inline void appendData(ServerMessageIdentifier id, QByteArray &data)
{
    constexpr DataGroupIdentifier groupId = DataGroupIdentifier::SERVER_DATA;
    data.append(reinterpret_cast<const char *>(&groupId), sizeof(groupId))
      .append(reinterpret_cast<const char *>(&id), sizeof(id));
}

template<typename T>
requires std::is_arithmetic_v<T> || std::is_enum_v<T>
inline void appendData(ServerMessageIdentifier id, T value, QByteArray &data)
{
    constexpr DataGroupIdentifier groupId = DataGroupIdentifier::SERVER_DATA;
    data.append(reinterpret_cast<const char *>(&groupId), sizeof(groupId))
      .append(reinterpret_cast<const char *>(&id), sizeof(id))
      .append(reinterpret_cast<const char *>(&value), sizeof(value));
}

inline void appendData(ServerMessageIdentifier id, const QByteArray &str, QByteArray &data)
{
    constexpr DataGroupIdentifier groupId = DataGroupIdentifier::SERVER_DATA;
    uint8_t size = str.size();
    data.append(reinterpret_cast<const char *>(&groupId), sizeof(groupId))
      .append(reinterpret_cast<const char *>(&id), sizeof(id))
      .append(reinterpret_cast<const char *>(&size), sizeof(size))
      .append(str.constData(), size);
}

}  // namespace util

#endif  // __APPEND_DATA_HPP__
