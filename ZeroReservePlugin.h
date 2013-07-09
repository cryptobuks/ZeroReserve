/*
    This file is part of the Zero Reserve Plugin for Retroshare.

    Zero Reserve is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Zero Reserve is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Zero Reserve.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef ZERORESERVEPLUGIN_H
#define ZERORESERVEPLUGIN_H

#include <retroshare/rsplugin.h>
#include <retroshare-gui/mainpage.h>

class ZeroReservePlugin: public RsPlugin
{
	public:
		ZeroReservePlugin() ;
		virtual ~ZeroReservePlugin() {}

		virtual MainPage       *qt_page()       			const	;
		virtual QIcon          *qt_icon()       			const	;
		virtual QTranslator    *qt_translator(QApplication *app, const QString& languageCode, const QString& externalDir) const;

		virtual void getPluginVersion(int& major,int& minor,int& svn_rev) const ;
		virtual void setPlugInHandler(RsPluginHandler *pgHandler);

		virtual std::string configurationFileName() const { return std::string() ; }

		virtual std::string getShortPluginDescription() const ;
		virtual std::string getPluginName() const;
		virtual void setInterfaces(RsPlugInInterfaces& interfaces);
	private:
		mutable RsPluginHandler *mPlugInHandler;
		mutable RsFiles* mFiles;
		mutable RsPeers* mPeers;
		mutable MainPage* mainpage ;
		mutable QIcon* mIcon ;
};

#endif

