// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Location.hpp"

namespace app
{
Location::Location()
    : QObject{nullptr}
{
}


void Location::setData(const Data &data)
{
    m_data = data;
    emit dataChanged();
}


QString Location::ip() const
{
    return m_data.ip;
}


QString Location::countryName() const
{
    return m_data.countryName;
}


QString Location::regionName() const
{
    return m_data.regionName;
}

}  // namespace app
