/****************************************************************************
**
** Copyright (C) 2018 N7 Space sp. z o. o.
** Contact: http://n7space.com
**
** This file is part of ASN.1/ACN MalTester - Tool for generating test cases
** based on ASN.1/ACN models and simulating malformed or malicious data.
**
** Tool was developed under a programme and funded by
** European Space Agency.
**
** This Tool is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** This Tool is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program.  If not, see <http://www.gnu.org/licenses/>.
**
****************************************************************************/
#pragma once

#include <memory>

#include <QString>

#include <data/expressiontree/expressionnode.h>

namespace MalTester {
namespace Data {
namespace ExpressionTree {

template<typename T>
class ConstrainingOperatorNode : public ExpressionNode<T>
{
public:
    ConstrainingOperatorNode(const QString &type)
        : m_type(stringToOperatorType(type))
        , m_child(nullptr)
    {}

    ConstrainingOperatorNode(const ConstrainingOperatorNode &other)
    {
        m_child = other.m_child ? other.m_child->clone() : nullptr;
    }

    std::unique_ptr<ExpressionNode<T>> clone() const override
    {
        return std::make_unique<ConstrainingOperatorNode<T>>(*this);
    }

    void appendChild(std::unique_ptr<ExpressionNode<T>> child) override;
    bool isFull() const override;
    QString asString() const override;

private:
    enum class NodeType { SIZE, FROM, UNKNOWN };
    static NodeType stringToOperatorType(const QString &name);

    NodeType m_type;
    std::unique_ptr<ExpressionNode<T>> m_child;
};

template<typename T>
inline void ConstrainingOperatorNode<T>::appendChild(std::unique_ptr<ExpressionNode<T>> child)
{
    m_child = std::move(child);
}

template<typename T>
inline bool ConstrainingOperatorNode<T>::isFull() const
{
    return m_child != nullptr;
}

template<typename T>
inline QString ConstrainingOperatorNode<T>::asString() const
{
    if (m_type == NodeType::SIZE)
        return QStringLiteral("(SIZE (") + m_child->asString() + QStringLiteral("))");

    if (m_type == NodeType::FROM)
        return QStringLiteral("(FROM (") + m_child->asString() + QStringLiteral("))");

    return {};
}

template<typename T>
inline typename ConstrainingOperatorNode<T>::NodeType
ConstrainingOperatorNode<T>::stringToOperatorType(const QString &name)
{
    if (name == QStringLiteral("SIZE"))
        return NodeType::SIZE;
    if (name == QStringLiteral("ALPHA"))
        return NodeType::FROM;

    return NodeType::UNKNOWN;
}

} // namespace ExpressionTree
} // namespace Data
} // namespace MalTester