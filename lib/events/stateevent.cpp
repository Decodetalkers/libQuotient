/******************************************************************************
* Copyright (C) 2018 Kitsune Ral <kitsune-ral@users.sf.net>
*
* This library is free software; you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public
* License as published by the Free Software Foundation; either
* version 2.1 of the License, or (at your option) any later version.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
* Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public
* License along with this library; if not, write to the Free Software
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "stateevent.h"

using namespace QMatrixClient;

[[gnu::unused]] static auto stateEventTypeInitialised =
        RoomEvent::factory_t::chainFactory<StateEventBase>();

bool StateEventBase::repeatsState() const
{
    const auto prevContentJson = unsignedJson().value(PrevContentKeyL);
    return fullJson().value(ContentKeyL) == prevContentJson;
}

void StateEventBase::dumpTo(QDebug dbg) const
{
    if (unsignedJson().contains(PrevContentKeyL))
        dbg << QJsonDocument(unsignedJson()[PrevContentKeyL].toObject())
               .toJson(QJsonDocument::Compact) << " -> ";
    RoomEvent::dumpTo(dbg);
}
