/*
    This file is part of the Zero Reserve Plugin for Retroshare.

    Zero Reserve is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Zero Reserve is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with Zero Reserve.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef ZERORESERVEPLUGIN_H
#define ZERORESERVEPLUGIN_H


#include <retroshare/rsplugin.h>
#include <retroshare-gui/mainpage.h>
#include "util/rsthreads.h"

#include <string>


class OrderBook;
class p3ZeroReserveRS;
class ConfigPage;
class ZeroReserveDialog;

class ZeroReservePlugin: public RsPlugin
{
public:
    ZeroReservePlugin() ;
    virtual ~ZeroReservePlugin() {}

    virtual MainPage       *qt_page() const	;
    virtual QIcon          *qt_icon() const	;
    virtual QTranslator    *qt_translator(QApplication *app, const QString& languageCode, const QString& externalDir) const;
    virtual QDialog * qt_about_page() const;
    virtual ConfigPage *qt_config_page() const ;
    virtual void stop();

    virtual void getPluginVersion(int& major,int& minor,int& svn_rev) const ;
    virtual void setPlugInHandler(RsPluginHandler *pgHandler);

    virtual std::string configurationFileName() const { return "zeroreserve.cfg" ; }

    virtual std::string getShortPluginDescription() const ;
    virtual std::string getPluginName() const;
    virtual RsPQIService * rs_pqi_service() const;
    virtual void setInterfaces(RsPlugInInterfaces& interfaces);

    /** interface between a worker thread and the GUI thread. Only GUI thread can open a dialog */
    void placeMsg( const std::string & _msg );
    void displayMsg();

    bool isStopped(){ return m_stopped; }

private:

    mutable RsPluginHandler *mPlugInHandler;
    mutable ZeroReserveDialog * mainpage ;
    mutable QIcon* mIcon ;
    mutable RsPeers* m_peers;
    OrderBook * m_asks;
    OrderBook * m_bids;
    mutable p3ZeroReserveRS * m_ZeroReserve;

    static RsMutex widget_creation_mutex;

    QList< QString > m_messages;
    RsMutex m_messages_mutex;

    bool m_stopped;
};

extern ZeroReservePlugin * g_ZeroReservePlugin;


#endif

