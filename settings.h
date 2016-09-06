/******************************************************************************
 * Copyright (C) 2016 Kitsune Ral <kitsune-ral@users.sf.net>
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

#pragma once

#include <QtCore/QSettings>
#include <QtCore/QVector>

class QVariant;
class QUrl;

namespace QMatrixClient
{
    class Settings: public QSettings
    {
        public:
            using QSettings::QSettings;
            virtual ~Settings();

            Q_INVOKABLE void setValue(const QString &key,
                                      const QVariant &value);
            Q_INVOKABLE QVariant value(const QString &key,
                                       const QVariant &defaultValue = {}) const;
    };

    class SettingsGroup: public Settings
    {
        public:
            template <typename... ArgTs>
            explicit SettingsGroup(const QString& path, ArgTs... qsettingsArgs)
                : Settings(qsettingsArgs...)
                , groupPath(path)
            { }
            virtual ~SettingsGroup();

            Q_INVOKABLE bool contains(const QString& key) const;
            Q_INVOKABLE QVariant value(const QString &key,
                                       const QVariant &defaultValue = {}) const;
            Q_INVOKABLE QString group() const;
            Q_INVOKABLE QStringList childGroups() const;
            Q_INVOKABLE void setValue(const QString &key,
                                      const QVariant &value);

            Q_INVOKABLE void remove(const QString& key);

        private:
            QString groupPath;
    };

    class AccountSettings: public SettingsGroup
    {
            Q_OBJECT
            Q_PROPERTY(QString userId READ userId)
            Q_PROPERTY(QUrl homeserver READ homeserver WRITE setHomeserver)
            Q_PROPERTY(bool keepLoggedIn READ keepLoggedIn WRITE setKeepLoggedIn)
            Q_PROPERTY(QString accessToken READ accessToken WRITE setAccessToken)
        public:
            template <typename... ArgTs>
            AccountSettings(const QString& accountId, ArgTs... qsettingsArgs)
                : SettingsGroup("Accounts/" + accountId, qsettingsArgs...)
            { }
            virtual ~AccountSettings();

            QString userId() const;

            QUrl homeserver() const;
            void setHomeserver(const QUrl& url);

            bool keepLoggedIn() const;
            void setKeepLoggedIn(bool newSetting);

            QString accessToken() const;
            void setAccessToken(const QString& accessToken);
            Q_INVOKABLE void clearAccessToken();
    };
}
