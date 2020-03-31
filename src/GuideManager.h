/*
 *  Copyright (C) 2015-2020 Team Kodi (https://kodi.tv)
 *  Copyright (C) 2016 Jamal Edey
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSE.md for more information.
 */

#pragma once

#include <memory>

#include "base/GuideManager.h"
#include "client.h"
#include "ChannelManager.h"
#include "HTTPSocket.h"
#include "SAPI.h"
#include "Settings.h"
#include "XMLTV.h"

namespace SC {
    struct Event : Base::Event {
        std::string plot;
        std::string cast;
        std::string directors;
        std::string writers;
        int year = 0;
        std::string iconPath;
        int genreType = 0;
        std::string genreDescription;
        time_t firstAired = 0;
        int starRating = 0;
        int episodeNumber = EPG_TAG_INVALID_SERIES_EPISODE;
        std::string episodeName;
    };

    class GuideManager : public Base::GuideManager<Event> {
    public:
        GuideManager();

        virtual ~GuideManager();

        virtual void SetAPI(SAPI *api) {
            m_api = api;
        }

        virtual void SetGuidePreference(Settings::GuidePreference guidePreference) {
            m_guidePreference = guidePreference;
        }

        virtual void SetCacheOptions(bool useCache, unsigned int expiry) {
            m_useCache = useCache;
            m_expiry = expiry;
        }

        virtual SError LoadGuide(time_t start, time_t end);

        virtual SError LoadXMLTV(HTTPSocket::Scope scope, const std::string &path);

        virtual std::vector<Event> GetChannelEvents(Channel &channel, time_t start = 0, time_t end = 0);

        virtual void Clear();

    private:
        int AddEvents(int type, std::vector<Event> &events, Channel &channel, time_t start, time_t end);

        SAPI *m_api;
        Settings::GuidePreference m_guidePreference;
        bool m_useCache;
        unsigned int m_expiry;
        std::shared_ptr<XMLTV> m_xmltv;
        Json::Value m_epgData;
    };
}
